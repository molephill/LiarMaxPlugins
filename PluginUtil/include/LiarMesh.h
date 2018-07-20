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
		std::vector<Liar::LiarVertexBuffer*>* GetBuffers() { return m_allVertexBuffers; };
		std::vector<unsigned int>* GetIndices() { return m_indices; };


		unsigned int GetBufferSize() { return m_bufferSize; };
		int GetIndicesSize() { return static_cast<int>(m_indices->size()); };

		void SetBufferSize(unsigned int v) { m_bufferSize = v; };
		LiarVertexBuffer* GetBuffer(int index) { return m_allVertexBuffers->at(index); };

		void EraseIndexBuff(int);
        
    public:
        void Upload();
        void Render();
        
#ifndef PLUGINS
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
#endif
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

		std::string meshName;
        
    public:
        void Upload();
        void Render();

#ifdef PLUGINS
		int vertexNum;
		int faceNum;

		std::string& GetMaterialName() { return m_material->name; };
#endif // !PLUGINS

	};
}

