#include "LiarMaterialParse.h"

namespace Liar
{
	// ====================  纹理 ================
	LiarTextureParse::LiarTextureParse() :
		m_index(0), m_fileName("")
	{

	}

	LiarTextureParse::~LiarTextureParse()
	{
		m_bmtPtr = nullptr;
	}

	void LiarTextureParse::SetBmtPtr(BitmapTex* ptr)
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

				char tmp[512];
				sprintf(tmp, "%s.%s", name.c_str(), strExt.c_str());
				m_fileName = tmp;
			}
		}
	}

	// ====================  材质 ================
	LiarMaterialParse::LiarMaterialParse():
		m_textureSize(0)
	{
		m_allTextures = new std::vector<Liar::LiarTextureParse*>();
		m_textureSize = 0;
	}


	LiarMaterialParse::~LiarMaterialParse()
	{
		EraseIndex(0);
		std::vector<Liar::LiarTextureParse*>().swap(*m_allTextures);
		delete m_allTextures;
	}

	BOOL LiarMaterialParse::SubTextureEnum(MtlBase* vMtl, int&)
	{
		// 名字
		Liar::StringUtil::GetWSTR2Char(vMtl->GetName(), m_name);

		int tTextureNum = vMtl->NumSubTexmaps();
		int curIndex = 0;
		for (int i = 0; i < tTextureNum; ++i)
		{
			Texmap* tmap = vMtl->GetSubTexmap(i);
			if (tmap && tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0))
			{
				Liar::LiarTextureParse* texture = nullptr;
				if (curIndex >= m_textureSize)
				{
					texture = new Liar::LiarTextureParse();
					m_allTextures->push_back(texture);
					++m_textureSize;
				}
				else
				{
					texture = m_allTextures->at(curIndex);
				}

				BitmapTex *bmt = (BitmapTex*)tmap;

				texture->SetIndex(curIndex);
				texture->SetBmtPtr(bmt);
				++curIndex;
			}
		}
		EraseIndex(curIndex);
		return TRUE;
	}

	void LiarMaterialParse::EraseIndex(int index)
	{
		for (std::vector<Liar::LiarTextureParse*>::iterator it = m_allTextures->begin() + index; it != m_allTextures->end();)
		{
			delete *it;
			it = m_allTextures->erase(it);
			--m_textureSize;
		}
	}
}
