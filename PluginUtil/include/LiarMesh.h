#pragma once
#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarStringUtil.h>
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

#ifdef PLUGINS
	public:
		void ParseNode(Mesh*);

	private:
		void ParseVertexData(Mesh*);
		void CollectColor(Mesh*);
		void CollectUV(Mesh*);
#endif // PLUGINS


	private:
		void EraseIndexBuff(int);
	};

	class LiarMesh
	{
	public:
		LiarMesh();
		~LiarMesh();

	private:
		std::string m_materialName;
		Liar::LiarGeometry* m_geometry;

	public:
		std::string nodeName;
#ifdef PLUGINS
		INode* ctrNode;
		int vertexNum;
		int faceNum;
#endif // !PLUGINS


	public:
		std::string& GetMaterialName() { return m_materialName; };

#ifdef PLUGINS
		void ParseNode(INode*, Mesh*);
#endif // PLUGINS

	};
}

