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

	private:
		void EraseIndex(int);

#ifdef PLUGINS
	public:
		std::string name;
		void ParseNode(INode*);
#endif // PLUGINS

	};
}

