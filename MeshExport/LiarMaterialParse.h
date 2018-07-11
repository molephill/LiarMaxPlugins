#pragma once

#include <iparamm2.h>
#include <iparamb2.h>
#include <stdmat.h>
//SIMPLE TYPE

#include <vector>

#include <LiarStringUtil.h>

#include "LiarMaterialParse.h"

namespace Liar
{
	// ====================  Œ∆¿Ì ================
	class LiarTextureParse
	{
	public:
		LiarTextureParse();
		~LiarTextureParse();

	private:
		int m_index;
		std::string m_fileName;
		BitmapTex* m_bmtPtr;

	public:
		void SetIndex(int v) { m_index = v; };
		void SetName(const std::string& v) { m_fileName = v; };
		void SetBmtPtr(BitmapTex*);
		std::string& GetName() { return m_fileName; };
	};

	class LiarMaterialParse
	{
	public:
		LiarMaterialParse();
		~LiarMaterialParse();

	private:
		std::vector<Liar::LiarTextureParse*>* m_allTextures;
		int m_textureSize;
		//int m_id;
		std::string m_name;

	public:
		//void SetID(int v) { m_id = v; };
		BOOL SubTextureEnum(MtlBase*, int& size);
		void SetName(const std::string& v) { m_name = v; };
		std::string& GetName() { return m_name; };

	private:
		void EraseIndex(int);
	};

}

