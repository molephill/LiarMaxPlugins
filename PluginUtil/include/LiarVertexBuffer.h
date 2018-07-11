#pragma once

#include <vector>
#include <PluginDefine.h>

#ifdef PLUGINS
#include <triobj.h>
#endif // !PLUGINS


namespace Liar
{
	class LiarVertexBuffer
	{
	public:
		LiarVertexBuffer();
		~LiarVertexBuffer();

	public:
		// 位置
		float x;
		float y;
		float z;

		// 法线
		float nx;
		float ny;
		float nz;

		// 颜色
		float r;
		float g;
		float b;

		// 纹理坐标
		float u;
		float v;

#ifdef PLUGINS
	public:
		void ParseMesh(Mesh*, int);
#endif // PLUGINS

	};
}

