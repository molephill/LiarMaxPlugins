#pragma once
#include "LiarMeshParse.h"
#include <LiarStringUtil.h>

#include <stdio.h>

namespace Liar
{
	class LiarMeshWrite
	{
	public:
		static void WriteMesh(Liar::LiarMeshParse*, const std::string&, unsigned int ver = 0);
		
	private:

		static void WriteModelHierarchy(Liar::LiarMeshParse*, const std::string&, unsigned int ver);
		static void WriteNode(Liar::LiarMeshParse*, Liar::LiarNode*, const char*, FILE*);
		static void SetMeshSaveName(Liar::LiarMeshParse*, int, const char*);

		static void WriteLiarMesh(Liar::LiarMeshParse*, Liar::LiarMesh*, const char*, unsigned int ver = 0);
		static void WriteLiarGeometery(Liar::LiarMeshParse*, Liar::LiarGeometry*, FILE*);
		static void WriteLiarMaterial(Liar::LiarMaterial*, FILE*);

		static void WriteLiarVertexBuffer(Liar::LiarMeshParse*, Liar::LiarVertexBuffer*, FILE*);
		static void WriteLiarTexture(Liar::LiarTexture*, FILE*);

		static void WriteString(std::string&, FILE*);

		static void GetVertexVer(Liar::LiarMeshParse*);
	};
}