#pragma once
#include "LiarNodeParse.h"
#include "LiarMesh.h"
#include <LiarPluginUtil.h>

namespace Liar
{
	class LiarMeshParse
	{
	public:
		LiarMeshParse();
		~LiarMeshParse();

	private:
		ExpInterface*	m_pExpInterface;				// 导出插件接口指针
		Interface*		m_pInterface;					// 3ds max 接口指针
		BOOL			m_exportSelect;					// 是否只导出选择项
		std::string		m_szExportPath;		// 导出目录

	private:
		std::vector<Liar::LiarMesh*>* m_allMeshs;
		int m_meshSize;

	public:
		void SetControl(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options);
		int ParseNode();

		std::string& GetExportPathName() { return m_szExportPath; };

	private:
		void EraseMeshIndex(int);

	public:
		Interface* GetInterface() { return m_pInterface; };
		ExpInterface* GetExpInterface() { return m_pExpInterface; };
		int GetMeshSize() const { return m_meshSize; };

		Liar::LiarMesh* GetOrNewMesh(int&);
		Liar::LiarMesh* GetMesh(int);

	private:
		void ParseLiarGeometry(Liar::LiarGeometry*, Mesh*);
		void ParseLiarGeometryBuffers(Liar::LiarGeometry*, Mesh*);
		void ParseLiarVertexBuffer(Liar::LiarVertexBuffer*, Mesh*, int, bool zy = true);
		void ParseLiarGeometryColor(Liar::LiarGeometry*, Mesh*);
		void ParseLiarGeometryUV(Liar::LiarGeometry*, Mesh*);

		void ParseLiarMaterial(Liar::LiarMaterial*, INode*);
		void ParseLiarTexture(Liar::LiarTexture*, Mtl*, int, BOOL backFace = FALSE);

	public:
		void ParseLiarMesh(Liar::LiarMesh*, INode*, Mesh*);

	};
}

