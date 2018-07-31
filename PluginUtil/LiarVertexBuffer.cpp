#include "LiarVertexBuffer.h"

namespace Liar
{

	LiarVertexBuffer::LiarVertexBuffer():position(nullptr), normal(nullptr), color(nullptr), uv(nullptr)
	{
	}


	LiarVertexBuffer::~LiarVertexBuffer()
	{
		if (position) delete position;
		if (normal) delete normal;
		if (color) delete color;
		if (uv) delete uv;
	}

#ifndef PLUGINS
	void LiarVertexBuffer::Upload(size_t start)
	{
		size_t positionSize = Liar::LiarVertexBuffer::GetPositionSize();
		size_t normalSize = LiarVertexBuffer::GetNormalSize();
		size_t colorSize = Liar::LiarVertexBuffer::GetColorSize();
		size_t uvSize = Liar::LiarVertexBuffer::GetUVSize();

		size_t normalOffSize = positionSize;
		size_t colorOffSize = positionSize + normalOffSize;
		size_t uvOffSize = colorOffSize + colorSize;

		glBufferSubData(GL_ARRAY_BUFFER, start, positionSize, position);
		glBufferSubData(GL_ARRAY_BUFFER, start + normalOffSize, normalSize, normal);
		glBufferSubData(GL_ARRAY_BUFFER, start + colorOffSize, colorSize, color);
		glBufferSubData(GL_ARRAY_BUFFER, start + uvOffSize, uvSize, uv);
	}
#endif // !PLUGINS


}
