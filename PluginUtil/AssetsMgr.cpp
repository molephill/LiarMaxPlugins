//
//  AssetsMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "AssetsMgr.hpp"

namespace Liar
{
    AssetsMgr::AssetsMgr()
    {
    }
    
    AssetsMgr::~AssetsMgr()
    {
    }

	Liar::LiarMesh* AssetsMgr::GetMesh(const char* fileName)
	{
		if (!m_allMeshes) m_allMeshes = new std::vector<Liar::LiarMesh*>();
		size_t len = m_allMeshes->size();
		Liar::LiarMesh* ret = nullptr;
		for (size_t i = 0; i < len; i++)
		{
			Liar::LiarMesh* mesh = m_allMeshes->at(i);
			if (std::strcmp(fileName, mesh->meshName.data()) == 0)
			{
				ret = mesh;
				break;
			}
		}

		if (ret == nullptr)
		{
			ret = Liar::LiarMeshRead::ReadMesh(fileName);
			ret->meshName = fileName;
			ret->Upload();
			m_allMeshes->push_back(ret);
		}

		ret->AddRef();
		
		return ret;
	}

	Liar::LiarMesh* AssetsMgr::GetMesh(const std::string& fileName)
	{
		return GetMesh(fileName.data());
	}

	Liar::LiarTexture* AssetsMgr::GetTexture(const char* fileName)
	{
		if (!m_allTextures) m_allTextures = new std::vector<Liar::LiarTexture*>();
		size_t len = m_allTextures->size();
		Liar::LiarTexture* ret = nullptr;
		for (size_t i = 0; i < len; ++i)
		{
			Liar::LiarTexture* texture = m_allTextures->at(i);
			if (std::strcmp(fileName, texture->GetName().data()) == 0)
			{
				ret = texture;
				break;
			}
		}

		if (ret == nullptr)
		{				
			ret = new Liar::LiarTexture();
			ret->Upload(fileName);
			ret->AddRef();
			m_allTextures->push_back(ret);
		}

		return ret;
	}

	Liar::LiarTexture* AssetsMgr::GetTexture(const std::string& fileName)
	{
		return GetTexture(fileName.data());
	}

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}
