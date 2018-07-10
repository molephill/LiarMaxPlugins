#include "SubMaterial.h"

namespace Liar
{
	SubMaterial::SubMaterial():
		m_textureSize(0),m_id(0)
	{
		m_allTextures = new std::vector<Liar::LiarTexture*>();
	}


	SubMaterial::~SubMaterial()
	{
		for (std::vector<Liar::LiarTexture*>::iterator it = m_allTextures->begin(); it != m_allTextures->end(); it++)
		if (*it)
		{
			delete *it;
			*it = NULL;
		}
		m_allTextures->clear();
		delete m_allTextures;
	}

	BOOL SubMaterial::SubTextureEnum(MtlBase* vMtl, int& matrialSize)
	{
		//int tTextureNum = vMtl->NumSubTexmaps();
		return TRUE;
	}


	// ====================  Œ∆¿Ì ================
	LiarTexture::LiarTexture() :
		index(0), fileName("")
	{

	}

	LiarTexture::~LiarTexture()
	{

	}
}
