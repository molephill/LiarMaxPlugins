#pragma once

#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarVertexBuffer.h>
#include <LiarStringUtil.h>

#ifndef PLUGINS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
		void SetPath(char* v) { m_name = v; };
		void SetPath(const std::string& v) { m_name = v; };

		Liar::Vector3D* GetAmbient() { return m_ambient; };
		Liar::Vector3D* GetDiffuse() { return m_diffuse; };
		Liar::Vector3D* GetSpecular() { return m_specular; };
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
        
    public:
        void Upload();

#ifdef PLUGINS
	public:
		std::string name;
#endif // PLUGINS

	};
}

