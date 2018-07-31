#pragma once

#include <Model.h>

#include <string>
#include <stdio.h>

namespace Liar
{
	class LiarMeshRead
	{
	public:
		static Liar::Model* ReadModel(const char*, const char* texBasePath = nullptr);
		static void ReadNode(const char*, Liar::LiarNode&);
		static Liar::LiarMesh* ReadMesh(const char* path, const char* basePath=nullptr);

	private:

		// ================================ read child model ===============================
		static void ReadChildModel(Liar::Model&, const Liar::LiarNode&, const char* basePath = nullptr);
		// ================================ read child model ===============================

		// ================================ read child node ===============================
		static void ReadChildNode(Liar::LiarNode&, std::string&, FILE*);
		// ================================ read child node ===============================

		static void ReadLiarMesh(Liar::LiarMesh*, FILE*);
		static void ReadLiarGeometery(Liar::LiarGeometry*, FILE*);
		static void ReadLiarMaterial(Liar::LiarMaterial*, FILE*);

		static void ReadLiarVertexBuffer(Liar::LiarVertexBuffer*, FILE*);
		static Liar::LiarTexture* ReadLiarTexture(FILE*);

		static void ReadString(std::string&, FILE*);

		static std::string basePath;
	};
}

