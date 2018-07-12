#pragma once
#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarStringUtil.h>
#include <LiarMaterial.h>
#include "LiarVertexBuffer.h"

#ifdef PLUGINS
#include <triobj.h>
#endif // PLUGINS


namespace Liar
{

	class LiarGeometry
	{
	public:
		LiarGeometry();
		~LiarGeometry();

	private:
		std::vector<Liar::LiarVertexBuffer*>* m_allVertexBuffers;
		int m_bufferSize;

		std::vector<int>* m_indices;

	private:
		void EraseIndexBuff(int);

#ifdef PLUGINS
	public:
		void ParseNode(Mesh*);

	private:
		void ParseVertexData(Mesh*);
		void CollectColor(Mesh*);
		void CollectUV(Mesh*);
#endif // PLUGINS
	};

	class LiarMesh
	{
	public:
		LiarMesh();
		~LiarMesh();

	private:
		Liar::LiarGeometry* m_geometry;
		Liar::LiarMaterial* m_material;

	public:
		std::string nodeName;
#ifdef PLUGINS
		INode* ctrNode;
		int vertexNum;
		int faceNum;

		void ParseNode(INode*, Mesh*);
		std::string& GetMaterialName() { return m_material->name; };
#endif // !PLUGINS

	};
}

