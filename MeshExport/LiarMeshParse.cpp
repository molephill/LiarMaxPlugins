#include "LiarMeshParse.h"

namespace Liar
{
	LiarMeshParse::LiarMeshParse()
	{
		m_allMeshs = new std::vector<Liar::LiarMesh*>();
		m_meshSize = 0;
	}


	LiarMeshParse::~LiarMeshParse()
	{
		EraseMeshIndex(0);
		std::vector<Liar::LiarMesh*>().swap(*m_allMeshs);
		delete m_allMeshs;
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
	int LiarMeshParse::ParseNode()
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

				meshNodeParse->ParseNode(node, this, curMeshIndex);
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
}
