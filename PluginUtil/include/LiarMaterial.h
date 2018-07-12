#pragma once

#include <string>
#include <vector>

#include <PluginDefine.h>
#include <LiarVertexBuffer.h>
#include <LiarStringUtil.h>

#ifdef PLUGINS
#include <triobj.h>
#include <stdmat.h>
#endif // PLUGINS

namespace Liar
{
	// ====================  Œ∆¿Ì ================

	class LiarTexture
	{
	public:
		LiarTexture();
		~LiarTexture();

	private:
		std::string m_path;

		Liar::LiarPoint3* m_ambient;
		Liar::LiarPoint3* m_diffuse;
		Liar::LiarPoint3* m_specular;
		float m_shininess;

	public:
		std::string& GetPath() { return m_path; };
		void SetPath(char* v) { m_path = v; };
		void SetPath(const std::string& v) { m_path = v; };

		Liar::LiarPoint3* GetAmbient() { return m_ambient; };
		Liar::LiarPoint3* GetDiffuse() { return m_diffuse; };
		Liar::LiarPoint3* GetSpecular() { return m_specular; };
		void SetShininess(float v) { m_shininess = v; };

#ifdef PLUGINS
	public:
		void ParseMaxMap(Mtl*, int, BOOL back = FALSE);
#endif // PLUGINS

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
		int GetTexSize() { return m_textureSize; };
		void SetTexSize(int v) { m_textureSize = v; };

#ifdef PLUGINS
	public:
		std::string name;
		void ParseNode(INode*);
#endif // PLUGINS

	};
}

