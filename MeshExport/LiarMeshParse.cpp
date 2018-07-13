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
		// 保存变量
		Liar::StringUtil::GetTChar2Char(name, m_szExportPath);

		m_pExpInterface = ei;
		m_pInterface = ip;
		m_exportSelect = (options & SCENE_EXPORT_SELECTED);

	}

	// ==================== 解析节点 =======================
	int LiarMeshParse::ParseNode(bool zy)
	{
		int numChildren = m_pInterface->GetRootNode()->NumberOfChildren();
		if (numChildren > 0)
		{
			int curMeshIndex = 0;
			Liar::LiarNodeParse* meshNodeParse = new Liar::LiarNodeParse();

			for (int idx = 0; idx < numChildren; idx++)
			{
				//列举对应节点信息
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

	// ==================== 释放多余的数组 =================
	void LiarMeshParse::EraseMeshIndex(int index)
	{
		for (std::vector<Liar::LiarMesh*>::iterator it = m_allMeshs->begin() + index; it != m_allMeshs->end();)
		{
			delete *it;
			it = m_allMeshs->erase(it);
			--m_meshSize;
		}
	}


	// ========================= 解析要用到的结构 ==========================
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
			//将三角面索引信息保存到容器中。
			geo->GetIndices()->push_back(mesh->faces[i].v[0]);
			geo->GetIndices()->push_back(mesh->faces[i].v[1]);
			geo->GetIndices()->push_back(mesh->faces[i].v[2]);
		}
	}

	void LiarMeshParse::ParseLiarVertexBuffer(Liar::LiarVertexBuffer* buff, Mesh* mesh, int index, bool zy)
	{
		//位置，要注意的是在3ds max中z值是朝上的，y值是朝前的，而在我们的游戏中,y值朝上，z值朝前。所以要做下处理。
		Liar::LiarStructUtil::ParsePoint3(buff->position, mesh->verts[index], zy);
		Liar::LiarStructUtil::ParsePoint3(buff->normal, mesh->getNormal(index), zy);
	}

	void LiarMeshParse::ParseLiarGeometryColor(Liar::LiarGeometry* geo, Mesh* mesh, bool zy)
	{
		//获取顶点色信息
		//如果有顶点有色彩赋值。
		if (mesh->numCVerts > 0)
		{
			int tFaceNum = mesh->getNumFaces();
			//遍历每个三角面
			for (int i = 0; i < tFaceNum; i++)
			{
				//色彩信息也以类似顶点的方式存放在模型的色彩信息数组vertCol中，而描述每个三角面的三个顶点都对应色彩信息数组的哪个值，也有类似面索引的信息结构TVFace存放在模型的vcFace数组中。
				TVFace& tface = mesh->vcFace[i];
				//取得色彩数组中对应三角面各顶点色彩值的三个索引。
				int tSrcColorIndex1 = tface.getTVert(0);
				int tSrcColorIndex2 = tface.getTVert(1);
				int	 tSrcColorIndex3 = tface.getTVert(2);
				//取得模型三角面的三个索引。
				int tDestColorIndex1 = mesh->faces[i].v[0];
				int tDestColorIndex2 = mesh->faces[i].v[1];
				int	tDestColorIndex3 = mesh->faces[i].v[2];

				//将色彩数组vertCol中对应三角面各顶点色彩的值赋值给相应的顶点。
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

		//获取顶点纹理坐标
		//如果有顶点有纹理坐标赋值。
		if (mesh->numTVerts > 0)
		{
			//顶点
			for (int i = 0; i < tFaceNum; i++)
			{
				//纹理坐标信息也以类似顶点的方式存放在模型的色彩信息数组tVerts中，而描述每个三角面的三个顶点都对应纹理坐标信息数组的哪个值，也有类似面索引的信息结构TVFace存放在模型的tvFace数组中。
				TVFace& tface = mesh->tvFace[i];
				//取得纹理坐标数组中对应三角面各顶点纹理坐标值的三个索引。
				int tSrcTexIndex1 = tface.getTVert(0);
				int tSrcTexIndex2 = tface.getTVert(1);
				int tSrcTexIndex3 = tface.getTVert(2);
				//取得模型三角面的三个索引。	
				int tDestTexIndex1 = mesh->faces[i].v[0];
				int	tDestTexIndex2 = mesh->faces[i].v[1];
				int	tDestTexIndex3 = mesh->faces[i].v[2];

				//将纹理坐标数组tVerts中对应三角面各顶点纹理坐标的值赋值给相应的顶点。
				Liar::LiarVertexBuffer* buff1 = geo->GetBuffes()->at(tDestTexIndex1);
				Liar::LiarVertexBuffer* buff2 = geo->GetBuffes()->at(tDestTexIndex2);
				Liar::LiarVertexBuffer* buff3 = geo->GetBuffes()->at(tDestTexIndex3);
				//注意：在纹理的纵向上，3ds max与我们游戏中是反的，也需要做下处理。
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
				// 得到文件名
				std::string fullName = Liar::StringUtil::GetLast(path);
				// 得到扩展名
				std::string strExt, name;
				Liar::StringUtil::GetHeadAndLast(fullName, name, strExt);

				//// 扩展名小写
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
