#pragma once

#include <vector>

namespace Liar
{
	class LiarPoint3
	{
	public:
		LiarPoint3() :x(0.0f), y(0.0f), z(0.0f) {};

	public:
		float x;
		float y;
		float z;
	};

	class LiarPoint2
	{
	public:
		LiarPoint2() :x(0.0f), y(0.0f) {};

	public:
		float x;
		float y;

	};

	class LiarVertexBuffer
	{
	public:
		LiarVertexBuffer();
		~LiarVertexBuffer();

	public:
		Liar::LiarPoint3* position;
		Liar::LiarPoint3* normal;
		Liar::LiarPoint3* color;
		Liar::LiarPoint2* uv;

	};
}

