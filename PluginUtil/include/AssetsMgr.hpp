//
//  TextureDataMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef TextureDataMgr_hpp
#define TextureDataMgr_hpp

#include <stdio.h>

#include <string>
#include <vector>

#ifndef __APPLE__
#include <functional>
#endif // !__APPLE__

#include <LiarMesh.h>
#include <LiarMaterial.h>
#include <LiarMeshRead.h>

namespace Liar
{
    class AssetsMgr
    {
    public:
		static AssetsMgr& GetInstance() 
		{  
			//全局访问点
			static InstanceCreator creator;  //有non-local static对象依赖时确保初始化顺序。
			return *m_instance;
		}
        
	private:
		AssetsMgr();
		AssetsMgr(const AssetsMgr &);
		~AssetsMgr();

		struct InstanceCreator 
		{  
			//真正负责单例的构造和析构
			InstanceCreator() 
			{
				AssetsMgr::m_instance = new AssetsMgr;
			}

			~InstanceCreator() 
			{
				delete AssetsMgr::m_instance;
				AssetsMgr::m_instance = nullptr;
			}
		};

		struct InstanceConfirm 
		{  
			//没有non-loacl static对象依赖时，保证在main函数前初始化
			InstanceConfirm() 
			{
				AssetsMgr::GetInstance();
			}
		};

	private:
		friend struct InstanceCreator;
		friend struct InstanceConfirm;
		static AssetsMgr* m_instance;
		static InstanceConfirm m_confirm;  //最后保证main函数之前完成初始化

	public:
		LiarMesh* GetMesh(const char*);
		LiarMesh* GetMesh(const std::string&);

		Liar::LiarTexture* GetTexture(const char*);
		Liar::LiarTexture* GetTexture(const std::string&);

	private:
		std::vector<Liar::LiarTexture*>* m_allTextures;
		std::vector<Liar::LiarMesh*>* m_allMeshes;
    };

	
}

#endif /* TextureDataMgr_hpp */
