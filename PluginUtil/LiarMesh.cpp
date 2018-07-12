#include "LiarMesh.h"

namespace Liar
{
	// =============================== Geometory ===============================

	LiarGeometry::LiarGeometry()
	{
		m_allVertexBuffers = new std::vector<Liar::LiarVertexBuffer*>();
		m_bufferSize = 0;

		m_indices = new std::vector<int>();
	}

	LiarGeometry::~LiarGeometry()
	{
		EraseIndexBuff(0);
		std::vector<Liar::LiarVertexBuffer*>().swap(*m_allVertexBuffers);
		delete m_allVertexBuffers;

		std::vector<int>().swap(*m_indices);
		delete m_indices;
	}

	void LiarGeometry::EraseIndexBuff(int index)
	{
		for (std::vector<Liar::LiarVertexBuffer*>::iterator it = m_allVertexBuffers->begin() + index; it != m_allVertexBuffers->end();)
		{
			delete *it;
			it = m_allVertexBuffers->erase(it);
			--m_bufferSize;
		}
	}

#ifdef PLUGINS
	void LiarGeometry::ParseNode(Mesh* mesh)
	{
		std::vector<int>().swap(*m_indices);

		ParseVertexData(mesh);
		CollectColor(mesh);
		CollectUV(mesh);
	}

	void LiarGeometry::ParseVertexData(Mesh* mesh)
	{
		int tVertexNum = mesh->getNumVerts();
		for (int i = 0; i < tVertexNum; ++i)
		{
			Liar::LiarVertexBuffer* buff = nullptr;
			if (i >= m_bufferSize)
			{
				buff = new Liar::LiarVertexBuffer();
				m_allVertexBuffers->push_back(buff);
				++m_bufferSize;
			}
			else
			{
				buff = m_allVertexBuffers->at(i);
			}

			buff->ParseMesh(mesh, i);
		}

		EraseIndexBuff(tVertexNum);

		int tFaceNum = mesh->getNumFaces();
		for (int i = 0; i < tFaceNum; ++i)
		{
			//��������������Ϣ���浽�����С�
			m_indices->push_back(mesh->faces[i].v[0]);
			m_indices->push_back(mesh->faces[i].v[1]);
			m_indices->push_back(mesh->faces[i].v[2]);
		}

	}

	// =============== ������ɫ ====================
	void LiarGeometry::CollectColor(Mesh* mesh)
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
				Liar::LiarVertexBuffer* buff1 = m_allVertexBuffers->at(tDestColorIndex1);
				buff1->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex1], true);

				Liar::LiarVertexBuffer* buff2 = m_allVertexBuffers->at(tDestColorIndex2);
				buff2->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex2], true);

				Liar::LiarVertexBuffer* buff3 = m_allVertexBuffers->at(tDestColorIndex3);
				buff3->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex3], true);
			}
		}
	}

	// =============== UV���� ====================
	void LiarGeometry::CollectUV(Mesh* mesh)
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
				Liar::LiarVertexBuffer* buff1 = m_allVertexBuffers->at(tDestTexIndex1);
				Liar::LiarVertexBuffer* buff2 = m_allVertexBuffers->at(tDestTexIndex2);
				Liar::LiarVertexBuffer* buff3 = m_allVertexBuffers->at(tDestTexIndex3);
				//ע�⣺������������ϣ�3ds max��������Ϸ���Ƿ��ģ�Ҳ��Ҫ���´���
				buff1->uv->ParseMaxPoint3(mesh->tVerts[tSrcTexIndex1], true);
				buff2->uv->ParseMaxPoint3(mesh->tVerts[tSrcTexIndex2], true);
				buff3->uv->ParseMaxPoint3(mesh->tVerts[tSrcTexIndex3], true);
			}
		}
	}
#endif // PLUGINS


	// =============================== Geometory ===============================

	LiarMesh::LiarMesh():
		m_geometry(new Liar::LiarGeometry())
		,m_material(new Liar::LiarMaterial())
	{
	}


	LiarMesh::~LiarMesh()
	{
		delete m_geometry;
		delete m_material;
	}

#ifdef PLUGINS
	void LiarMesh::ParseNode(INode* node, Mesh* mesh)
	{
		ctrNode = node;
		Liar::StringUtil::WChar_tToString(node->GetName(), nodeName);

		faceNum = mesh->getNumFaces();
		vertexNum = mesh->getNumVerts();

		m_geometry->ParseNode(mesh);
		m_material->ParseNode(node);


		//ȡ�õ�ǰ�����������ĵ�ľ�����Ϣ��
		//Matrix3 tTMAfterWSMM = node->GetNodeTM(tTime);
		//��չ��4X4����
		//GMatrix		tGMeshTM(tTMAfterWSMM);
		////���浽ģ����Ϣ�ṹ�ľ�����Ϣ�С�
		//for (int m = 0; m < 4; m++)
		//{
		//	for (int n = 0; n < 4; n++)
		//	{
		//		tSubMesh.m_SubMeshMatrix.m[m * 4 + n] = tGMeshTM[m][n];
		//	}
		//}
	}

#endif // PLUGINS

}
