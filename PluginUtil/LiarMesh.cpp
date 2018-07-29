#include "LiarMesh.h"

namespace Liar
{

	// =============================== Nodes ===============================

	LiarNode::LiarNode(const char* nodeName)
		:m_nodeName(nodeName)
	{

	}

	LiarNode::~LiarNode()
	{

	}

	// =============================== Nodes ===============================

	// =============================== Geometory ===============================

	LiarGeometry::LiarGeometry()
	{
		m_allVertexBuffers = new std::vector<Liar::LiarVertexBuffer*>();
		m_bufferSize = 0;

		m_indices = new std::vector<unsigned int>();
	}

	LiarGeometry::~LiarGeometry()
	{
		EraseIndexBuff(0);
		std::vector<Liar::LiarVertexBuffer*>().swap(*m_allVertexBuffers);
		delete m_allVertexBuffers;

		std::vector<unsigned int>().swap(*m_indices);
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

#ifndef PLUGINS
	void LiarGeometry::Upload()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		size_t positionSize = Liar::LiarVertexBuffer::GetPositionSize();
		size_t normalSize = Liar::LiarVertexBuffer::GetNormalSize();
		size_t colorSize = Liar::LiarVertexBuffer::GetColorSize();
		size_t uvSize = Liar::LiarVertexBuffer::GetUVSize();

		size_t oneSize = Liar::LiarVertexBuffer::GetBuffSize();
		size_t totalSize = m_bufferSize * oneSize;

		size_t positionOffSize = Liar::LiarVertexBuffer::GetPositionOffSize();
		size_t normalOffSize = Liar::LiarVertexBuffer::GetNormalOffSize();
		size_t colorOffSize = Liar::LiarVertexBuffer::GetColorOffSize();
		size_t uvOffSize = Liar::LiarVertexBuffer::GetUVOffSize();

		glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
		for (int i = 0; i < m_bufferSize; ++i)
		{
			size_t start = i * oneSize;
			Liar::LiarVertexBuffer* buffData = m_allVertexBuffers->at(i);
			glBufferSubData(GL_ARRAY_BUFFER, start + positionOffSize, positionSize, buffData->position);
			glBufferSubData(GL_ARRAY_BUFFER, start + normalOffSize, normalSize, buffData->normal);
			glBufferSubData(GL_ARRAY_BUFFER, start + colorOffSize, colorSize, buffData->color);
			glBufferSubData(GL_ARRAY_BUFFER, start + uvOffSize, uvSize, buffData->uv);
		}

		size_t indiceSize1 = GetIndicesSize() * sizeof(unsigned int);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize1, m_indices->data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)positionOffSize);
		glEnableVertexAttribArray(0);
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)normalOffSize);
		glEnableVertexAttribArray(1);
		// color attribute
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, oneSize, (void*)colorOffSize);
		glEnableVertexAttribArray(2);
		// texture coord attribute
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, oneSize, (void*)uvOffSize);
		glEnableVertexAttribArray(3);

	}

	void LiarGeometry::Render()
	{
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, GetIndicesSize(), GL_UNSIGNED_INT, 0);
	}

#endif // !PLUGINS

	// =============================== Geometory ===============================

	LiarMesh::LiarMesh() :
		m_geometry(new Liar::LiarGeometry())
		, m_material(new Liar::LiarMaterial())
	{
#ifndef PLUGINS
		m_refCount = 0;
#endif // !PLUGINS

	}


	LiarMesh::~LiarMesh()
	{
		delete m_geometry;
		delete m_material;
	}

#ifndef PLUGINS
	void LiarMesh::Upload()
	{
		m_geometry->Upload();
	}


	void LiarMesh::Render(Liar::Shader& shader)
	{
		m_geometry->Render();
		m_material->Render(shader);
	}

#endif // PLUGINS


}
