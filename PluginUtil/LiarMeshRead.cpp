#include "LiarMeshRead.h"

namespace Liar
{
	Liar::LiarMesh* LiarMeshRead::ReadMesh(const char* path)
	{
		FILE* pFile;
		fopen_s(&pFile, path, "rb+");
		if (!pFile)
		{
			return nullptr;
		}
		else
		{
			Liar::LiarMesh* mesh = new Liar::LiarMesh();
			ReadLiarMesh(mesh, pFile);
			fclose(pFile);
			return mesh;
		}
	}

	void LiarMeshRead::ReadLiarMesh(Liar::LiarMesh* mesh, FILE* pFile)
	{
		// read ver
		unsigned int ver = 0;
		fread(&ver, sizeof(unsigned int), 1, pFile);
		// read mesh`s name
		fread(&(mesh->meshName), sizeof(std::string), 1, pFile);
		// read mesh`s Geometery
		ReadLiarGeometery(mesh->GetGeo(), pFile);
		// read mesh`s material
		ReadLiarMaterial(mesh->GetMat(), pFile);
	}

	void LiarMeshRead::ReadLiarGeometery(Liar::LiarGeometry* geo, FILE* pFile)
	{
		// read indices count;
		int indiceSize = 0;
		fread(&indiceSize, sizeof(int), 1, pFile);
		// read indices
		for (int i = 0; i < indiceSize; ++i)
		{
			unsigned int index = 0;
			fread(&index, sizeof(unsigned int), 1, pFile);
			geo->GetIndices()->push_back(index);
		}

		// read bufferSize
		int bufferSize = 0;
		fread(&bufferSize, sizeof(int), 1, pFile);
		geo->SetBufferSize(bufferSize);
		// read buffer
		for (int i = 0; i < bufferSize; ++i)
		{
			Liar::LiarVertexBuffer* buffer = new Liar::LiarVertexBuffer();
			geo->GetBuffers()->push_back(buffer);
			ReadLiarVertexBuffer(buffer, pFile);
		}
	}

	void LiarMeshRead::ReadLiarMaterial(Liar::LiarMaterial* mat, FILE* pFile)
	{
		int texSize = 0;
		// read texSize;
		fread(&texSize, sizeof(int), 1, pFile);
		mat->SetTexSize(texSize);
		// read texture
		for (int i = 0; i < texSize; ++i)
		{
			Liar::LiarTexture* tex = new Liar::LiarTexture();
			mat->GetTextures()->push_back(tex);
			ReadLiarTexture(tex, pFile);
		}
	}

	void LiarMeshRead::ReadLiarVertexBuffer(Liar::LiarVertexBuffer* buff, FILE* pFile)
	{
		// write pos
		fread(buff->position, sizeof(Liar::LiarPoint3), 1, pFile);
		// write normal
		fread(buff->normal, sizeof(Liar::LiarPoint3), 1, pFile);
		// write color
		fread(buff->color, sizeof(Liar::LiarPoint3), 1, pFile);
		// write uv
		fread(buff->uv, sizeof(Liar::LiarPoint2), 1, pFile);
	}

	void LiarMeshRead::ReadLiarTexture(Liar::LiarTexture* tex, FILE* pFile)
	{
		// read name
		fread(&(tex->GetName()), sizeof(std::string), 1, pFile);
		// write Ambient
		fread(tex->GetAmbient(), sizeof(Liar::LiarPoint3), 1, pFile);
		// write Diffuse
		fread(tex->GetDiffuse(), sizeof(Liar::LiarPoint3), 1, pFile);
		// read Specular
		fread(tex->GetSpecular(), sizeof(Liar::LiarPoint3), 1, pFile);
		// read Shininess
		float shininess = 0;
		fread(&shininess, sizeof(float), 1, pFile);
		tex->SetShininess(shininess);
	}
}
