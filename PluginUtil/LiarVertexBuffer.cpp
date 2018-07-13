#include "LiarVertexBuffer.h"

namespace Liar
{
	LiarVertexBuffer::LiarVertexBuffer()
	{
		position = new Liar::LiarPoint3();
		normal = new Liar::LiarPoint3();
		color = new Liar::LiarPoint3();
		uv = new LiarPoint2();
	}


	LiarVertexBuffer::~LiarVertexBuffer()
	{
		delete position;
		delete normal;
		delete color;
		delete uv;
	}

}
