#pragma once
#include "LiarMaterialParse.h"
#include "LiarNodeParse.h"
#include "LiarMesh.h"

namespace Liar
{
	class LiarMeshParse
	{
	public:
		LiarMeshParse();
		~LiarMeshParse();

	private:
		ExpInterface*	m_pExpInterface;				// ��������ӿ�ָ��
		Interface*		m_pInterface;					// 3ds max �ӿ�ָ��
		BOOL			m_exportSelect;					// �Ƿ�ֻ����ѡ����
		std::string		m_szExportPath;		// ����Ŀ¼

	private:
		std::vector<Liar::LiarMaterialParse*>* m_allMaterials;
		int m_materialSize;

		std::vector<Liar::LiarMesh*>* m_allMeshs;
		int m_meshSize;

	public:
		void SetControl(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options);

		int ParseMatrial();
		int ParseNode();

		std::string& GetExportPathName() { return m_szExportPath; };

	private:
		void EraseMatrialIndex(int);
		void EraseMeshIndex(int);

	public:
		Interface* GetInterface() { return m_pInterface; };
		ExpInterface* GetExpInterface() { return m_pExpInterface; };
		int GetMeshSize() const { return m_meshSize; };

		Liar::LiarMesh* GetOrNewMesh(int&);
		Liar::LiarMesh* GetMesh(int);
	};
}

