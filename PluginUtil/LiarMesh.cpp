#include "LiarMesh.h"

namespace Liar
{
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
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, m_bufferSize * sizeof(Liar::LiarVertexBuffer), m_allVertexBuffers->data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->size() * sizeof(unsigned int), m_indices->data(), GL_STATIC_DRAW);

		size_t len = sizeof(Liar::LiarVertexBuffer);
		// set the vertex attribute pointers
		// vertex Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, len, (void*)0);
		glEnableVertexAttribArray(0);
		// vertex normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, len, (void*)offsetof(LiarVertexBuffer, normal));
		glEnableVertexAttribArray(1);
		// vertex color
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, len, (void*)offsetof(LiarVertexBuffer, color));
		glEnableVertexAttribArray(2);
		// vertex texture coords
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, len, (void*)offsetof(LiarVertexBuffer, uv));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);

	}

	void LiarGeometry::Render()
	{
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

#endif // !PLUGINS

	// =============================== Geometory ===============================

	LiarMesh::LiarMesh():
		m_geometry(new Liar::LiarGeometry())
		,m_material(new Liar::LiarMaterial())
	{
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
	}

#endif // PLUGINS


}
