#include "LiarMeshParse.h"

namespace Liar
{
	LiarMeshParse::LiarMeshParse()
	{
		m_allMeshs = new std::vector<Liar::LiarMesh*>();
		m_meshSize = 0;

		liarPluginCfg = new Liar::PluginCfg();
	}


	LiarMeshParse::~LiarMeshParse()
	{
		EraseMeshIndex(0);
		std::vector<Liar::LiarMesh*>().swap(*m_allMeshs);
		delete m_allMeshs;

		delete liarPluginCfg;
	}

	void LiarMeshParse::SetControl(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options)
	{
		// �������
		Liar::StringUtil::GetTChar2Char(name, m_szExportPath);

		m_pExpInterface = ei;
		m_pInterface = ip;
		m_exportSelect = (options & SCENE_EXPORT_SELECTED);

	}

	// ==================== �����ڵ� =======================
	int LiarMeshParse::ParseNode(bool zy)
	{
		int numChildren = m_pInterface->GetRootNode()->NumberOfChildren();
		if (numChildren > 0)
		{
			int curMeshIndex = 0;
			Liar::LiarNodeParse* meshNodeParse = new Liar::LiarNodeParse();

			for (int idx = 0; idx < numChildren; idx++)
			{
				//�оٶ�Ӧ�ڵ���Ϣ
				INode* node = m_pInterface->GetRootNode()->GetChildNode(idx);
				if (!node) continue;

				meshNodeParse->ParseNode(node, this, curMeshIndex, zy);
			}
			EraseMeshIndex(curMeshIndex);
			delete meshNodeParse;
		}
		return 0;
	}

	Liar::LiarMesh* LiarMeshParse::GetOrNewMesh(int& index)
	{
		Liar::LiarMesh* mesh = nullptr;
		if (index >= m_meshSize)
		{
			m_meshSize = ++index;
			mesh = new Liar::LiarMesh();
			m_allMeshs->push_back(mesh);
		}
		else
		{
			mesh = m_allMeshs->at(index);
		}
		return mesh;
	}

	Liar::LiarMesh* LiarMeshParse::GetMesh(int index)
	{
		if (index >= m_meshSize)
		{
			return nullptr;
		}
		else
		{
			return m_allMeshs->at(index);
		}
	}

	// ==================== �ͷŶ�������� =================
	void LiarMeshParse::EraseMeshIndex(int index)
	{
		for (std::vector<Liar::LiarMesh*>::iterator it = m_allMeshs->begin() + index; it != m_allMeshs->end();)
		{
			delete *it;
			it = m_allMeshs->erase(it);
			--m_meshSize;
		}
	}


	// ========================= ����Ҫ�õ��Ľṹ ==========================
	void LiarMeshParse::ParseLiarMesh(Liar::LiarMesh* lmesh, INode* node, Mesh* mesh, bool zy)
	{
		lmesh->faceNum = mesh->getNumFaces();
		lmesh->vertexNum = mesh->getNumVerts();

		ParseLiarGeometry(lmesh->GetGeo(), mesh, zy);
		ParseLiarMaterial(lmesh->GetMat(), node);
	}

	void LiarMeshParse::ParseLiarGeometry(Liar::LiarGeometry* geo, Mesh* mesh, bool zy)
	{
		std::vector<unsigned int>().swap(*(geo->GetIndices()));
		ParseLiarGeometryBuffers(geo, mesh, zy);
		ParseLiarGeometryColor(geo, mesh, zy);
		ParseLiarGeometryUV(geo, mesh, zy);
	}

	void LiarMeshParse::ParseLiarGeometryBuffers(Liar::LiarGeometry* geo, Mesh* mesh, bool zy)
	{
		int tVertexNum = mesh->getNumVerts();
		for (int i = 0; i < tVertexNum; ++i)
		{
			Liar::LiarVertexBuffer* buff = nullptr;
			int bufferSize = geo->GetBufferSize();
			if (i >= bufferSize)
			{
				buff = new Liar::LiarVertexBuffer();
				geo->GetBuffes()->push_back(buff);
				geo->SetBufferSize(++bufferSize);
			}
			else
			{
				buff = geo->GetBuffes()->at(i);
			}

			ParseLiarVertexBuffer(buff, mesh, i, zy);
		}

		geo->EraseIndexBuff(tVertexNum);

		int tFaceNum = mesh->getNumFaces();
		for (int i = 0; i < tFaceNum; ++i)
		{
			//��������������Ϣ���浽�����С�
			geo->GetIndices()->push_back(mesh->faces[i].v[0]);
			geo->GetIndices()->push_back(mesh->faces[i].v[1]);
			geo->GetIndices()->push_back(mesh->faces[i].v[2]);
		}
	}

	void LiarMeshParse::ParseLiarVertexBuffer(Liar::LiarVertexBuffer* buff, Mesh* mesh, int index, bool zy)
	{
		//λ�ã�Ҫע�������3ds max��zֵ�ǳ��ϵģ�yֵ�ǳ�ǰ�ģ��������ǵ���Ϸ��,yֵ���ϣ�zֵ��ǰ������Ҫ���´���
		Liar::LiarStructUtil::ParsePoint3(buff->position, mesh->verts[index], zy);
		Liar::LiarStructUtil::ParsePoint3(buff->normal, mesh->getNormal(index), zy);
	}

	void LiarMeshParse::ParseLiarGeometryColor(Liar::LiarGeometry* geo, Mesh* mesh, bool zy)
	{
		//��ȡ����ɫ��Ϣ
		//����ж�����ɫ�ʸ�ֵ��
		if (mesh->numCVerts > 0)
		{
			int tFaceNum = mesh->getNumFaces();
			//����ÿ��������
			for (int i = 0; i < tFaceNum; i++)
			{
				//ɫ����ϢҲ�����ƶ���ķ�ʽ�����ģ�͵�ɫ����Ϣ����vertCol�У�������ÿ����������������㶼��Ӧɫ����Ϣ������ĸ�ֵ��Ҳ����������������Ϣ�ṹTVFace�����ģ�͵�vcFace�����С�
				TVFace& tface = mesh->vcFace[i];
				//ȡ��ɫ�������ж�Ӧ�����������ɫ��ֵ������������
				int tSrcColorIndex1 = tface.getTVert(0);
				int tSrcColorIndex2 = tface.getTVert(1);
				int	 tSrcColorIndex3 = tface.getTVert(2);
				//ȡ��ģ�������������������
				int tDestColorIndex1 = mesh->faces[i].v[0];
				int tDestColorIndex2 = mesh->faces[i].v[1];
				int	tDestColorIndex3 = mesh->faces[i].v[2];

				//��ɫ������vertCol�ж�Ӧ�����������ɫ�ʵ�ֵ��ֵ����Ӧ�Ķ��㡣
				Liar::LiarVertexBuffer* buff1 = geo->GetBuffes()->at(tDestColorIndex1);
				Liar::LiarStructUtil::ParsePoint3(buff1->color, mesh->vertCol[tSrcColorIndex1], zy);

				Liar::LiarVertexBuffer* buff2 = geo->GetBuffes()->at(tDestColorIndex2);
				Liar::LiarStructUtil::ParsePoint3(buff2->color, mesh->vertCol[tSrcColorIndex2], zy);

				Liar::LiarVertexBuffer* buff3 = geo->GetBuffes()->at(tDestColorIndex3);
				Liar::LiarStructUtil::ParsePoint3(buff3->color, mesh->vertCol[tSrcColorIndex3], zy);
			}
		}
	}

	void LiarMeshParse::ParseLiarGeometryUV(Liar::LiarGeometry* geo, Mesh* mesh, bool zy)
	{
		int tFaceNum = mesh->getNumFaces();

		//��ȡ������������
		//����ж������������긳ֵ��
		if (mesh->numTVerts > 0)
		{
			//����
			for (int i = 0; i < tFaceNum; i++)
			{
				//����������ϢҲ�����ƶ���ķ�ʽ�����ģ�͵�ɫ����Ϣ����tVerts�У�������ÿ����������������㶼��Ӧ����������Ϣ������ĸ�ֵ��Ҳ����������������Ϣ�ṹTVFace�����ģ�͵�tvFace�����С�
				TVFace& tface = mesh->tvFace[i];
				//ȡ���������������ж�Ӧ�������������������ֵ������������
				int tSrcTexIndex1 = tface.getTVert(0);
				int tSrcTexIndex2 = tface.getTVert(1);
				int tSrcTexIndex3 = tface.getTVert(2);
				//ȡ��ģ�������������������	
				int tDestTexIndex1 = mesh->faces[i].v[0];
				int	tDestTexIndex2 = mesh->faces[i].v[1];
				int	tDestTexIndex3 = mesh->faces[i].v[2];

				//��������������tVerts�ж�Ӧ��������������������ֵ��ֵ����Ӧ�Ķ��㡣
				Liar::LiarVertexBuffer* buff1 = geo->GetBuffes()->at(tDestTexIndex1);
				Liar::LiarVertexBuffer* buff2 = geo->GetBuffes()->at(tDestTexIndex2);
				Liar::LiarVertexBuffer* buff3 = geo->GetBuffes()->at(tDestTexIndex3);
				//ע�⣺������������ϣ�3ds max��������Ϸ���Ƿ��ģ�Ҳ��Ҫ���´���
				Liar::LiarStructUtil::ParsePoint3(buff1->uv, mesh->tVerts[tSrcTexIndex1], zy);
				Liar::LiarStructUtil::ParsePoint3(buff2->uv, mesh->tVerts[tSrcTexIndex2], zy);
				Liar::LiarStructUtil::ParsePoint3(buff3->uv, mesh->tVerts[tSrcTexIndex3], zy);
			}
		}
	}

	void LiarMeshParse::ParseLiarMaterial(Liar::LiarMaterial* mat, INode* node, BOOL backFace)
	{
		Mtl* nodemtl = node->GetMtl();
		Liar::StringUtil::WChar_tToString(nodemtl->GetName(), mat->name);
		int tTextureNum = nodemtl->NumSubTexmaps();
		int curIndex = 0;
		for (int i = 0; i < tTextureNum; ++i)
		{
			Texmap* tmap = nodemtl->GetSubTexmap(i);
			if (tmap && tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0))
			{
				Liar::LiarTexture* texture = nullptr;
				int textureSize = mat->GetTexSize();
				if (curIndex >= textureSize)
				{
					texture = new Liar::LiarTexture();
					mat->GetTextures()->push_back(texture);
					mat->SetTexSize(++textureSize);
				}
				else
				{
					texture = mat->GetTextures()->at(curIndex);
				}
				ParseLiarTexture(texture, nodemtl, i, backFace);
				++curIndex;
			}
		}

		mat->EraseIndex(curIndex);
	}

	void LiarMeshParse::ParseLiarTexture(Liar::LiarTexture* tex, Mtl* nodemtl, int index, BOOL backFace)
	{
		Texmap* tmap = nodemtl->GetSubTexmap(index);
		BitmapTex *bmt = (BitmapTex*)tmap;
		if (bmt)
		{
			std::string& path = tex->GetPath();
			const MCHAR* mapName = bmt->GetMapName();
			Liar::StringUtil::WChar_tToString(mapName, path);

			if (!path.empty())
			{
				// �õ��ļ���
				std::string fullName = Liar::StringUtil::GetLast(path);
				// �õ���չ��
				std::string strExt, name;
				Liar::StringUtil::GetHeadAndLast(fullName, name, strExt);

				//// ��չ��Сд
				std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);

				char tmp[512];
				sprintf(tmp, "%s.%s", name.c_str(), strExt.c_str());
				tex->SetPath(tmp);
			}
		}

		Liar::LiarStructUtil::ParseColor(tex->GetAmbient(), nodemtl->GetAmbient(index, backFace));
		Liar::LiarStructUtil::ParseColor(tex->GetDiffuse(), nodemtl->GetDiffuse(index, backFace));
		Liar::LiarStructUtil::ParseColor(tex->GetSpecular(), nodemtl->GetSpecular(index, backFace));
		tex->SetShininess(nodemtl->GetShininess());
	}
}
