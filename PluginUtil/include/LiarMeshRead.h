#pragma once

#include <LiarMesh.h>

#include <string>
#include <stdio.h>

namespace Liar
{
	class LiarMeshRead
	{
	public:
		static Liar::LiarMesh* ReadMesh(const char* path);

	private:
		static void ReadLiarMesh(Liar::LiarMesh*, FILE*);
		static void ReadLiarGeometery(Liar::LiarGeometry*, FILE*);
		static void ReadLiarMaterial(Liar::LiarMaterial*, FILE*);

		static void ReadLiarVertexBuffer(Liar::LiarVertexBuffer*, FILE*);
		static Liar::LiarTexture* ReadLiarTexture(FILE*);

		static void ReadString(std::string&, FILE*);

		static std::string basePath;
	};
}

