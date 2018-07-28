#pragma once

#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarVertexBuffer.h>
#include <LiarStringUtil.h>

#ifndef PLUGINS
#include "Shader.hpp"
#endif // !PLUGINS

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

		Liar::Vector3D* m_ambient;
		Liar::Vector3D* m_diffuse;
		Liar::Vector3D* m_specular;
		float m_shininess;

	public:
		std::string& GetName() { return m_name; };
		void SetPath(const char* v) { m_name = v; };
		void SetPath(const std::string& v) { m_name = v; };

		Liar::Vector3D* GetAmbient() { return m_ambient; };
		Liar::Vector3D* GetDiffuse() { return m_diffuse; };
		Liar::Vector3D* GetSpecular() { return m_specular; };
		float GetShininess() { return m_shininess; };
		void SetShininess(float v) { m_shininess = v; };

#ifndef PLUGINS
	private:
		unsigned int m_refCount;
		unsigned int m_textureId;

	public:
		void AddRef() { ++m_refCount; };
		unsigned int SubRef() { return --m_refCount; };

		void Upload(const char*);
		void Upload(const std::string&);
        
        unsigned int GetTextureId() {return m_textureId;};

		void Render(Liar::Shader&, int);
#endif // ! PLUGINS

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
#else
	public:
		void Render(Liar::Shader&);
#endif // PLUGINS

	};
}

