#include "LiarVertexBuffer.h"

namespace Liar
{

	LiarVertexBuffer::LiarVertexBuffer()
	{
		position = new Liar::Vector3D();
		normal = new Liar::Vector3D();
		color = new Liar::Vector3D();
		uv = new Liar::Vector2D();
	}


	LiarVertexBuffer::~LiarVertexBuffer()
	{
		delete position;
		delete normal;
		delete color;
		delete uv;
	}

}
