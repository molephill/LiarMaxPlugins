#pragma once
#include "LiarNodeParse.h"
#include "LiarMesh.h"
#include <LiarPluginUtil.h>
#include "PluginCfg.h"

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
		int ParseNode(bool zy = true);

	public:
		void EraseMeshIndex(int);

	public:
		Interface* GetInterface() { return m_pInterface; };
		ExpInterface* GetExpInterface() { return m_pExpInterface; };
		int GetMeshSize() const { return m_meshSize; };
		std::string& GetExportPathName() { return m_szExportPath; };

		Liar::PluginCfg* liarPluginCfg;

		Liar::LiarMesh* GetOrNewMesh(int&);
		Liar::LiarMesh* GetMesh(int);

	public:
		Liar::LiarNode* rootNode;
		int vertexOpen;

	private:
		void ParseLiarGeometry(Liar::LiarGeometry*, Mesh*, bool zy = true);
		void ParseLiarGeometryBuffers(Liar::LiarGeometry*, Mesh*, bool zy = true);
		void ParseLiarVertexBuffer(Liar::LiarVertexBuffer*, Mesh*, int, bool zy = true);
		void ParseLiarGeometryColor(Liar::LiarGeometry*, Mesh*, bool zy = true);
		void ParseLiarGeometryUV(Liar::LiarGeometry*, Mesh*, bool dv = true);

		void ParseLiarMaterial(Liar::LiarMaterial*, INode*, BOOL backFace = FALSE);
		void ParseLiarTexture(Liar::LiarTexture*, Mtl*, int, BOOL backFace = FALSE);

	public:
		void ParseLiarMesh(Liar::LiarMesh*, INode*, Mesh*, bool zy = true);

	};
}

