#include "SubMaterial.h"

namespace Liar
{
	// ====================  纹理 ================
	LiarTexture::LiarTexture() :
		m_index(0), m_fileName("")
	{

	}

	LiarTexture::~LiarTexture()
	{
		m_bmtPtr = nullptr;
	}

	void LiarTexture::SetBmtPtr(BitmapTex* ptr)
	{
		m_bmtPtr = ptr;
		if (m_bmtPtr)
		{
			const MCHAR* mapName = m_bmtPtr->GetMapName();
			Liar::StringUtil::WChar_tToString(mapName, m_fileName);

			if (!m_fileName.empty())
			{
				// 得到文件名
				std::string fullName = Liar::StringUtil::GetLast(m_fileName);
				// 得到扩展名
				std::string strExt, name;
				Liar::StringUtil::GetHeadAndLast(fullName, name, strExt);

				//// 扩展名小写
				std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);

				char* tmp = new char[name.length() + strExt.length() + 1];
				sprintf(tmp, "%s.%s", name.c_str(), strExt.c_str());
				m_fileName = tmp;
				delete[] tmp;
			}
		}
	}

	// ====================  材质 ================
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

	BOOL SubMaterial::SubTextureEnum(MtlBase* vMtl, int&)
	{
		int tTextureNum = vMtl->NumSubTexmaps();
		for (int i = 0; i < tTextureNum; ++i)
		{
			Texmap* tmap = vMtl->GetSubTexmap(i);
			if (tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0))
			{
				Liar::LiarTexture* texture = nullptr;
				if (i >= m_textureSize)
				{
					texture = new Liar::LiarTexture();
					m_allTextures->push_back(texture);
				}
				else
				{
					texture = m_allTextures->at(i);
				}

				BitmapTex *bmt = (BitmapTex*)tmap;

				texture->SetIndex(i);
				texture->SetBmtPtr(bmt);
			}
		}
		EraseIndex(tTextureNum);
		m_textureSize = tTextureNum;
		return TRUE;
	}

	void SubMaterial::EraseIndex(int index)
	{
		for (std::vector<Liar::LiarTexture*>::iterator it = m_allTextures->begin() + index; it != m_allTextures->end();)
		{
			delete *it;
			m_allTextures->erase(it);
			++it;
		}
	}
}
