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
			//将三角面索引信息保存到容器中。
			m_indices->push_back(mesh->faces[i].v[0]);
			m_indices->push_back(mesh->faces[i].v[1]);
			m_indices->push_back(mesh->faces[i].v[2]);
		}

	}

	// =============== 顶点颜色 ====================
	void LiarGeometry::CollectColor(Mesh* mesh)
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
				Liar::LiarVertexBuffer* buff1 = m_allVertexBuffers->at(tDestColorIndex1);
				buff1->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex1], true);

				Liar::LiarVertexBuffer* buff2 = m_allVertexBuffers->at(tDestColorIndex2);
				buff2->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex2], true);

				Liar::LiarVertexBuffer* buff3 = m_allVertexBuffers->at(tDestColorIndex3);
				buff3->color->ParseMaxPoint3(mesh->vertCol[tSrcColorIndex3], true);
			}
		}
	}

	// =============== UV坐标 ====================
	void LiarGeometry::CollectUV(Mesh* mesh)
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
				Liar::LiarVertexBuffer* buff1 = m_allVertexBuffers->at(tDestTexIndex1);
				Liar::LiarVertexBuffer* buff2 = m_allVertexBuffers->at(tDestTexIndex2);
				Liar::LiarVertexBuffer* buff3 = m_allVertexBuffers->at(tDestTexIndex3);
				//注意：在纹理的纵向上，3ds max与我们游戏中是反的，也需要做下处理。
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


		//取得当前结点相对于中心点的矩阵信息。
		//Matrix3 tTMAfterWSMM = node->GetNodeTM(tTime);
		//扩展成4X4矩阵
		//GMatrix		tGMeshTM(tTMAfterWSMM);
		////保存到模型信息结构的矩阵信息中。
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
