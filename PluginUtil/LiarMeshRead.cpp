#include "LiarMeshRead.h"


namespace Liar
{
	Liar::LiarMesh* LiarMeshRead::ReadMesh(const char* path, const char* texBasePath)
	{
		FILE* pFile;
#ifndef __APPLE__
		fopen_s(&pFile, path, "rb+");
#else
        pFile = fopen(path, "rb+");
#endif
		if (!pFile)
		{
			return nullptr;
		}
		else
		{
			if (!texBasePath)
			{
				basePath = path;
				basePath = Liar::StringUtil::GetHead(basePath, "/");
			}
			else
			{
				basePath = texBasePath;
			}

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
		//fread(&(mesh->meshName), sizeof(std::string), 1, pFile);
		ReadString(mesh->meshName, pFile);
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
			Liar::LiarTexture* tex = ReadLiarTexture(pFile);
			mat->GetTextures()->push_back(tex);
		}
	}

	void LiarMeshRead::ReadLiarVertexBuffer(Liar::LiarVertexBuffer* buff, FILE* pFile)
	{
		size_t p3Size = sizeof(Liar::Vector3D);
		// write pos
		fread(buff->position, p3Size, 1, pFile);
		// write normal
		fread(buff->normal, p3Size, 1, pFile);
		// write color
		fread(buff->color, p3Size, 1, pFile);
		// write uv
		size_t p2Size = sizeof(Liar::Vector2D);
		fread(buff->uv, p2Size, 1, pFile);
	}

	Liar::LiarTexture* LiarMeshRead::ReadLiarTexture(FILE* pFile)
	{
		Liar::LiarTexture* tex = new Liar::LiarTexture();

		// read name
		//fread(&(tex->GetName()), sizeof(std::string), 1, pFile);
		std::string baseName;
		ReadString(baseName, pFile);
		baseName = basePath + baseName;

		// set name
		tex->SetPath(baseName);
		size_t p3Size = sizeof(Liar::Vector3D);
		// write Ambient
		fread(tex->GetAmbient(), p3Size, 1, pFile);
		// write Diffuse
		fread(tex->GetDiffuse(), p3Size, 1, pFile);
		// read Specular
		fread(tex->GetSpecular(), p3Size, 1, pFile);
		// read Shininess
		float shininess = 0;
		fread(&shininess, sizeof(float), 1, pFile);
		tex->SetShininess(shininess);

		return tex;
	}

	void LiarMeshRead::ReadString(std::string& s, FILE* pFile)
	{
		int size = 0;
		fread(&size, sizeof(int), 1, pFile);
		for (int i = 0; i < size; ++i)
		{
			char a ;
			fread(&a, sizeof(char), 1, pFile);
			s.push_back(a);
		}
	}

	std::string LiarMeshRead::basePath = "";
}
