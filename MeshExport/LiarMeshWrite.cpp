#include "LiarMeshWrite.h"

namespace Liar
{
	void LiarMeshWrite::WriteMesh(Liar::LiarMeshParse* parse, const char* path, unsigned int ver)
	{
		int meshSize = parse->GetMeshSize();
		for (int i = 0; i < meshSize; ++i)
		{
			Liar::LiarMesh* mesh = parse->GetMesh(i);

			std::string folder, last;
			Liar::StringUtil::GetHeadAndLast(path, folder, last, "//");

			std::string baseName, ext;
			Liar::StringUtil::GetHeadAndLast(path, baseName, ext, ".");

			Liar::StringUtil::StringToLower(baseName);
			Liar::StringUtil::StringToLower(ext);

			WriteLiarMesh(mesh, baseName.c_str(), folder.c_str(), ext.c_str(), meshSize == 1, ver);
		}
	}

	void LiarMeshWrite::WriteLiarMesh(Liar::LiarMesh* mesh, const char* baseName, const char* path, const char* ext, bool useBase, unsigned int ver)
	{
		std::string& meshName = mesh->meshName;
		Liar::StringUtil::StringToLower(meshName);

		char fullName[MAX_PATH];
		if (useBase)
		{
			sprintf_s(fullName, "%s%s.%s", path, baseName, ext);
		}
		else
		{
			sprintf_s(fullName, "%s%s_%s.%s", path, baseName, meshName.c_str(), ext);
		}

		FILE* hFile = fopen(fullName, "wb");

		// write ver
		fwrite(&ver, sizeof(unsigned int), 1, hFile);
		// write mesh`s name
		fwrite(&meshName, sizeof(meshName), 1, hFile);
		// write mesh`s geometery
		WriteLiarGeometery(mesh->GetGeo(), hFile);
		// write mesh`s material
		WriteLiarMaterial(mesh->GetMat(), hFile);

		fclose(hFile);
	}

	void LiarMeshWrite::WriteLiarGeometery(Liar::LiarGeometry* geo, FILE* hFile)
	{
		int bufferSize = geo->GetBufferSize();
		// write bufferSize;
		fwrite(&bufferSize, sizeof(int), 1, hFile);
		// write indices
		fwrite(&(geo->GetIndices()->front()), sizeof(unsigned int), geo->GetIndicesSize(), hFile);
		// write buffer
		for (int i = 0; i < bufferSize; ++i)
		{
			WriteLiarVertexBuffer(geo->GetBuffer(i), hFile);
		}
	}

	void LiarMeshWrite::WriteLiarMaterial(Liar::LiarMaterial* mat, FILE* hFile)
	{
		int texSize = mat->GetTexSize();
		// write texSize;
		fwrite(&texSize, sizeof(int), 1, hFile);
		// write texture
		for (int i = 0; i < texSize; ++i)
		{
			WriteLiarTexture(mat->GetTexture(i), hFile);
		}
	}

	void LiarMeshWrite::WriteLiarVertexBuffer(Liar::LiarVertexBuffer* buff, FILE* hFile)
	{
		// write pos
		fwrite(buff->position, sizeof(Liar::LiarPoint3), 1, hFile);
		// write normal
		fwrite(buff->normal, sizeof(Liar::LiarPoint3), 1, hFile);
		// write color
		fwrite(buff->color, sizeof(Liar::LiarPoint3), 1, hFile);
		// write uv
		fwrite(buff->uv, sizeof(Liar::LiarPoint2), 1, hFile);
	}

	void LiarMeshWrite::WriteLiarTexture(Liar::LiarTexture* tex, FILE* hFile)
	{
		// wirte name
		std::string& texName = tex->GetName();
		fwrite(&texName, sizeof(texName), 1, hFile);
		// write Ambient
		fwrite(tex->GetAmbient(), sizeof(Liar::LiarPoint3), 1, hFile);
		// write Diffuse
		fwrite(tex->GetDiffuse(), sizeof(Liar::LiarPoint3), 1, hFile);
		// write Specular
		fwrite(tex->GetSpecular(), sizeof(Liar::LiarPoint3), 1, hFile);
		// write Shininess
		float shininess = tex->GetShininess();
		fwrite(&shininess, sizeof(float), 1, hFile);
	}

}