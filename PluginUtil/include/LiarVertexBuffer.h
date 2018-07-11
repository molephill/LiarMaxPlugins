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
		// λ��
		float x;
		float y;
		float z;

		// ����
		float nx;
		float ny;
		float nz;

		// ��ɫ
		float r;
		float g;
		float b;

		// ��������
		float u;
		float v;

#ifdef PLUGINS
	public:
		void ParseMesh(Mesh*, int);
#endif // PLUGINS

	};
}

