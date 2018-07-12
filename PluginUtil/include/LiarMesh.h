#pragma once
#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarStringUtil.h>
#include <LiarMaterial.h>
#include "LiarVertexBuffer.h"

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

		std::vector<unsigned int>* m_indices;

	public:
		std::vector<Liar::LiarVertexBuffer*>* GetBuffes() { return m_allVertexBuffers; };
		std::vector<unsigned int>* GetIndices() { return m_indices; };
		unsigned int GetBufferSize() { return m_bufferSize; };
		void SetBufferSize(unsigned int v) { m_bufferSize = v; };

		void EraseIndexBuff(int);
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
		Liar::LiarGeometry* GetGeo() { return m_geometry; };
		Liar::LiarMaterial* GetMat() { return m_material; };

#ifdef PLUGINS
		std::string nodeName;
		int vertexNum;
		int faceNum;

		std::string& GetMaterialName() { return m_material->name; };
#endif // !PLUGINS

	};
}

