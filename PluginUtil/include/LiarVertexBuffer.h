#pragma once

#include "Vectors.h"

#ifndef PLUGINS
#include <glad/glad.h>
#endif // !PLUGINS


namespace Liar
{
	class LiarVertexBuffer
	{
	public:
		LiarVertexBuffer();
		~LiarVertexBuffer();

	public:
		Liar::Vector3D* position;
		Liar::Vector3D* normal;
		Liar::Vector3D* color;
		Liar::Vector2D* uv;

#ifndef PLUGINS
	public:
		static size_t GetPositionSize() { return sizeof(Liar::Vector3D); };
		static size_t GetNormalSize() { return sizeof(Liar::Vector3D); };
		static size_t GetColorSize() { return sizeof(Liar::Vector3D); };
		static size_t GetUVSize() { return sizeof(Liar::Vector2D); };

		static size_t GetPositionOffSize() { return 0; };
		static size_t GetNormalOffSize() { return Liar::LiarVertexBuffer::GetPositionSize(); };
		static size_t GetColorOffSize() 
		{
			return Liar::LiarVertexBuffer::GetNormalOffSize() + Liar::LiarVertexBuffer::GetNormalSize();
		}

		static size_t GetUVOffSize() 
		{
			return Liar::LiarVertexBuffer::GetColorOffSize() + Liar::LiarVertexBuffer::GetColorSize();
		}

		static size_t GetBuffSize() 
		{
			return Liar::LiarVertexBuffer::GetPositionSize() + Liar::LiarVertexBuffer::GetNormalSize()
				+ Liar::LiarVertexBuffer::GetColorSize() + Liar::LiarVertexBuffer::GetUVSize();
		}

	public:
		void Upload(size_t);
#endif // !PLUGINS

	};
}

