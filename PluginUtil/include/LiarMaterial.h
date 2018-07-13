#pragma once

#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarVertexBuffer.h>
#include <LiarStringUtil.h>

namespace Liar
{
	// ====================  Œ∆¿Ì ================

	class LiarTexture
	{
	public:
		LiarTexture();
		~LiarTexture();

	private:
		std::string m_name;

		Liar::LiarPoint3* m_ambient;
		Liar::LiarPoint3* m_diffuse;
		Liar::LiarPoint3* m_specular;
		float m_shininess;

	public:
		std::string& GetName() { return m_name; };
		void SetPath(char* v) { m_name = v; };
		void SetPath(const std::string& v) { m_name = v; };

		Liar::LiarPoint3* GetAmbient() { return m_ambient; };
		Liar::LiarPoint3* GetDiffuse() { return m_diffuse; };
		Liar::LiarPoint3* GetSpecular() { return m_specular; };
		float GetShininess() { return m_shininess; };
		void SetShininess(float v) { m_shininess = v; };

	};

	// ====================  Œ∆¿Ì ================

	class LiarMaterial
	{
	public:
		LiarMaterial();
		~LiarMaterial();

	private:
		std::vector<Liar::LiarTexture*>* m_allTextures;
		int m_textureSize;

	public:
		void EraseIndex(int);

		std::vector<Liar::LiarTexture*>* GetTextures() { return m_allTextures; };
		Liar::LiarTexture* GetTexture(int index) { return m_allTextures->at(index); };

		int GetTexSize() { return m_textureSize; };
		void SetTexSize(int v) { m_textureSize = v; };

#ifdef PLUGINS
	public:
		std::string name;
#endif // PLUGINS

	};
}

