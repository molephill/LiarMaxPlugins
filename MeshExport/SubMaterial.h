#pragma once

#include <iparamb2.h>
//SIMPLE TYPE

#include "SubMaterial.h"

#include <vector>

namespace Liar
{
	// ====================  Œ∆¿Ì ================
	class LiarTexture
	{
	public:
		LiarTexture();
		~LiarTexture();

	public:
		int index;
		std::string fileName;
	};

	class SubMaterial
	{
	public:
		SubMaterial();
		~SubMaterial();

	private:
		std::vector<Liar::LiarTexture*>* m_allTextures;
		int m_textureSize;
		int m_id;
		std::string m_name;

	public:
		void SetID(int v) { m_id = v; };
		BOOL SubTextureEnum(MtlBase*, int& size);
		void SetName(const std::string& v) { m_name = v; };
		std::string& GetName() { return m_name; };
	};

}

