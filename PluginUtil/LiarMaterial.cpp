#include "LiarMaterial.h"

namespace Liar
{

	// ====================  Œ∆¿Ì ================

	LiarTexture::LiarTexture():m_name(""), m_shininess(0.0f)
	{
		m_ambient = new Liar::Vector3D();
		m_diffuse = new Liar::Vector3D();
		m_specular = new Liar::Vector3D();
	}

	LiarTexture::~LiarTexture()
	{
		delete m_ambient;
		delete m_diffuse;
		delete m_specular;
	}

	// ====================  Œ∆¿Ì ================

	LiarMaterial::LiarMaterial()
	{
		m_allTextures = new std::vector<Liar::LiarTexture*>();
		m_textureSize = 0;
	}


	LiarMaterial::~LiarMaterial()
	{
		EraseIndex(0);
		std::vector<Liar::LiarTexture*>().swap(*m_allTextures);
		delete m_allTextures;
	}

	void LiarMaterial::EraseIndex(int index)
	{
		for (std::vector<Liar::LiarTexture*>::iterator it = m_allTextures->begin() + index; it != m_allTextures->end();)
		{
			delete *it;
			it = m_allTextures->erase(it);
			--m_textureSize;
		}
	}

}
