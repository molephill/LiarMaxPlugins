#pragma once
#include "LiarMeshParse.h"
#include <LiarStringUtil.h>

#include <stdio.h>

namespace Liar
{
	class LiarMeshWrite
	{
	public:
		static void WriteMesh(Liar::LiarMeshParse*, const char*, unsigned int ver = 0);
		
	private:
		static void WriteLiarMesh(Liar::LiarMesh*, const char*, const char*, const char*, bool, unsigned int ver = 0);
		static void WriteLiarGeometery(Liar::LiarGeometry*, FILE*);
		static void WriteLiarMaterial(Liar::LiarMaterial*, FILE*);

		static void WriteLiarVertexBuffer(Liar::LiarVertexBuffer*, FILE*);
		static void WriteLiarTexture(Liar::LiarTexture*, FILE*);
	};
}