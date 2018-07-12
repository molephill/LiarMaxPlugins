#include "LiarMaterial.h"

namespace Liar
{

	// ====================  纹理 ================

	LiarTexture::LiarTexture():m_path(""), m_shininess(0.0f)
	{
		m_ambient = new Liar::LiarPoint3();
		m_diffuse = new Liar::LiarPoint3();
		m_specular = new Liar::LiarPoint3();
	}

	LiarTexture::~LiarTexture()
	{
		delete m_ambient;
		delete m_diffuse;
		delete m_specular;
	}

#ifdef PLUGINS
	void LiarTexture::ParseMaxMap(Mtl* nodemtl, int index, BOOL back)
	{
		Texmap* tmap = nodemtl->GetSubTexmap(index);
		BitmapTex *bmt = (BitmapTex*)tmap;
		if (bmt)
		{
			const MCHAR* mapName = bmt->GetMapName();
			Liar::StringUtil::WChar_tToString(mapName, m_path);

			if (!m_path.empty())
			{
				// 得到文件名
				std::string fullName = Liar::StringUtil::GetLast(m_path);
				// 得到扩展名
				std::string strExt, name;
				Liar::StringUtil::GetHeadAndLast(fullName, name, strExt);

				//// 扩展名小写
				std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);

				char tmp[512];
				sprintf(tmp, "%s.%s", name.c_str(), strExt.c_str());
				m_path = tmp;
			}
		}

		m_ambient->ParseMaxColor(nodemtl->GetAmbient(index, back));
		m_diffuse->ParseMaxColor(nodemtl->GetDiffuse(index, back));
		m_specular->ParseMaxColor(nodemtl->GetSpecular(index, back));
		m_shininess = nodemtl->GetShininess();
	}
#endif // PLUGINS


	// ====================  纹理 ================

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

#ifdef PLUGINS
	void LiarMaterial::ParseNode(INode* node)
	{
		Mtl* nodemtl = node->GetMtl();
		Liar::StringUtil::WChar_tToString(nodemtl->GetName(), name);
		int tTextureNum = nodemtl->NumSubTexmaps();
		int curIndex = 0;
		for (int i = 0; i < tTextureNum; ++i)
		{
			Texmap* tmap = nodemtl->GetSubTexmap(i);
			if (tmap && tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0))
			{
				Liar::LiarTexture* texture = nullptr;
				if (curIndex >= m_textureSize)
				{
					texture = new Liar::LiarTexture();
					m_allTextures->push_back(texture);
					++m_textureSize;
				}
				else
				{
					texture = m_allTextures->at(curIndex);
				}
				texture->ParseMaxMap(nodemtl, i);
				++curIndex;
			}
		}

		EraseIndex(curIndex);
	}
#endif // PLUGINS
}
