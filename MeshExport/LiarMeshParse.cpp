#include "LiarMeshParse.h"

namespace Liar
{
	LiarMeshParse::LiarMeshParse()
	{
		m_allMaterials = new std::vector<Liar::LiarMaterialParse*>();
		m_materialSize = 0;
		m_allMeshs = new std::vector<Liar::LiarMesh*>();
		m_meshSize = 0;
	}


	LiarMeshParse::~LiarMeshParse()
	{
		EraseMatrialIndex(0);
		std::vector<Liar::LiarMaterialParse*>().swap(*m_allMaterials);
		delete m_allMaterials;

		EraseMeshIndex(0);
		std::vector<Liar::LiarMesh*>().swap(*m_allMeshs);
		delete m_allMeshs;
	}

	void LiarMeshParse::SetControl(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options)
	{
		// �������
		Liar::StringUtil::GetTChar2Char(name, m_szExportPath);

		m_pExpInterface = ei;
		m_pInterface = ip;
		m_exportSelect = (options & SCENE_EXPORT_SELECTED);

	}

	int LiarMeshParse::ParseMatrial()
	{
		//ͨ��m_pInterfaceȡ�ó����еĲ��ʿ�
		MtlBaseLib * scenemats = m_pInterface->GetSceneMtls();

		int matrialSize = 0;
		if (scenemats)
		{
			int matrialCount = scenemats->Count();
			if (matrialCount > 0)
			{
				//ȡ�ò�������
				for (int i = 0; i < matrialCount; i++)
				{
					MtlBase* vMtl = (*scenemats)[i];
					if (IsMtl(vMtl))
					{
						Liar::LiarMaterialParse* pParseMaterial = nullptr;
						if (matrialSize >= m_materialSize)
						{
							pParseMaterial = new Liar::LiarMaterialParse();
							m_allMaterials->push_back(pParseMaterial);
							++m_materialSize;
						}
						else
						{
							pParseMaterial = m_allMaterials->at(i);
						}
						//memset(pParseMaterial, 0, sizeof(SubMaterial));
						//pParseMaterial->SetID(matrialSize++);
						++matrialSize;

						////�����������õ���ͼ
						pParseMaterial->SubTextureEnum(vMtl, matrialSize);
					}
				}
			}
		}

		EraseMatrialIndex(matrialSize);
		return matrialSize;
	}

	// ==================== �����ڵ� =======================
	int LiarMeshParse::ParseNode()
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

	// ==================== �ͷŶ�������� =================
	void LiarMeshParse::EraseMatrialIndex(int index)
	{
		for (std::vector<Liar::LiarMaterialParse*>::iterator it = m_allMaterials->begin() + index; it != m_allMaterials->end();)
		{
			delete *it;
			it = m_allMaterials->erase(it);
			--m_materialSize;
		}
	}

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
