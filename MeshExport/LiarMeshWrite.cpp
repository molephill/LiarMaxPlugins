#include "LiarMeshWrite.h"

namespace Liar
{
	void LiarMeshWrite::WriteModelHierarchy(Liar::LiarMeshParse* parse, const std::string& path, unsigned int ver)
	{
		Liar::LiarNode* rootNode = parse->rootNode;
		// ignore root

		std::string folder, last;
		Liar::StringUtil::GetHeadAndLast(path, folder, last, "\\");

		std::string baseName, ext;
		Liar::StringUtil::GetHeadAndLast(last, baseName, ext, ".");

		char fullName[MAX_PATH];
		sprintf_s(fullName, "%s\\%s.model", folder.c_str(), baseName.c_str());
		FILE* hFile = fopen(fullName, "wb");

		// write ver
		fwrite(&ver, sizeof(unsigned int), 1, hFile);

		// set rootNode`name = baseName;
		rootNode->SetNodeName(baseName);
		Liar::StringUtil::StringToLower(ext);

		WriteNode(parse, rootNode, ext.c_str(), hFile);

		fclose(hFile);
	}

	void LiarMeshWrite::WriteNode(Liar::LiarMeshParse* parse, Liar::LiarNode* curNode, const char* ext, FILE* hFile)
	{
		int size = 0;
		std::vector<Liar::LiarNode*>* children = curNode->GetChildren();
		if (children) size = static_cast<int>(children->size());
		// write nodeSize;
		fwrite(&size, sizeof(int), 1, hFile);
		for (int i = 0; i < size; ++i)
		{
			char saveName[MAX_PATH];
			Liar::LiarNode* subNode = children->at(i);

			std::string& curNodeName = curNode->GetNodeName();
			std::string& subNodeName = subNode->GetNodeName();

			Liar::StringUtil::StringToLower(curNodeName);
			Liar::StringUtil::StringToLower(subNodeName);

			sprintf_s(saveName, "%s_%s.%s", curNodeName.c_str(), subNodeName.c_str(), ext);

			// set mesh`s saveName
			SetMeshSaveName(parse, subNode->meshIndex, saveName);

			// write self`s name;
			std::string szStr = saveName;
			WriteString(szStr, hFile);

			// change self`s name
			sprintf_s(saveName, "%s_%s", curNodeName.c_str(), subNodeName.c_str());
			subNode->SetNodeName(saveName);

			// write children;
			WriteNode(parse, subNode, ext, hFile);
		}
	}

	void LiarMeshWrite::SetMeshSaveName(Liar::LiarMeshParse* parse, int index, const char* saveName)
	{
		int meshSize = parse->GetMeshSize();
		for (int i = 0; i < meshSize; ++i)
		{
			if (i == index)
			{
				Liar::LiarMesh* mesh = parse->GetMesh(i);
				mesh->saveName = saveName;
				return;
			}
		}
	}

	void LiarMeshWrite::WriteMesh(Liar::LiarMeshParse* parse, const std::string& path, unsigned int ver)
	{
		// get vertex_open_status
		Liar::LiarMeshWrite::GetVertexVer(parse);

		// write ModelHierarchy
		WriteModelHierarchy(parse, path, ver);

		std::string folder = Liar::StringUtil::GetHead(path, "\\");
		int meshSize = parse->GetMeshSize();
		for (int i = 0; i < meshSize; ++i)
		{
			Liar::LiarMesh* mesh = parse->GetMesh(i);

			WriteLiarMesh(parse, mesh, folder.c_str(), ver);
		}

		delete parse->rootNode;
	}

	void LiarMeshWrite::WriteLiarMesh(Liar::LiarMeshParse* parse, Liar::LiarMesh* mesh, const char* path, unsigned int ver)
	{
		std::string& meshName = mesh->saveName;
		char fullName[MAX_PATH];

		sprintf_s(fullName, "%s\\%s", path, meshName.c_str());

		FILE* hFile = fopen(fullName, "wb");

		// write ver
		fwrite(&ver, sizeof(unsigned int), 1, hFile);
		// write vertex open status
		fwrite(&parse->vertexOpen, sizeof(int), 1, hFile);
		// write mesh`s name
		Liar::StringUtil::StringToLower(mesh->meshName);
		WriteString(mesh->meshName, hFile);
		// write mesh`s geometery
		WriteLiarGeometery(parse, mesh->GetGeo(), hFile);
		// write mesh`s material
		WriteLiarMaterial(mesh->GetMat(), hFile);

		fclose(hFile);
	}

	void LiarMeshWrite::WriteLiarGeometery(Liar::LiarMeshParse* parse, Liar::LiarGeometry* geo, FILE* hFile)
	{
		// write indices count;
		int indiceSize = static_cast<int>(geo->GetIndicesSize());
		fwrite(&indiceSize, sizeof(int), 1, hFile);
		// write indices
		fwrite(&(geo->GetIndices()->front()), sizeof(unsigned int), indiceSize, hFile);

		int bufferSize = geo->GetBufferSize();
		// write bufferSize;
		fwrite(&bufferSize, sizeof(int), 1, hFile);
		// write buffer
		for (int i = 0; i < bufferSize; ++i)
		{
			WriteLiarVertexBuffer(parse, geo->GetBuffer(i), hFile);
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

	void LiarMeshWrite::WriteLiarVertexBuffer(Liar::LiarMeshParse* parse, Liar::LiarVertexBuffer* buff, FILE* hFile)
	{
		// write pos
		size_t p3Size = sizeof(Liar::Vector3D);
		if (parse->liarPluginCfg->exportPos)
		{
			fwrite(buff->position, p3Size, 1, hFile);
		}
		// write normal
		if (parse->liarPluginCfg->exportNormal)
		{
			fwrite(buff->normal, p3Size, 1, hFile);
		}
		// write color
		if (parse->liarPluginCfg->exportColor)
		{
			fwrite(buff->color, p3Size, 1, hFile);
		}
		// write uv
		if (parse->liarPluginCfg->exportUV)
		{
			size_t p2Size = sizeof(Liar::Vector2D);
			fwrite(buff->uv, p2Size, 1, hFile);
		}
	}

	void LiarMeshWrite::WriteLiarTexture(Liar::LiarTexture* tex, FILE* hFile)
	{
		// wirte name
		std::string& texName = tex->GetName();
		//fwrite(&texName, sizeof(std::string), 1, hFile);
		WriteString(texName, hFile);
		size_t p3Size = sizeof(Liar::Vector3D);
		// write Ambient
		fwrite(tex->GetAmbient(), p3Size, 1, hFile);
		// write Diffuse
		fwrite(tex->GetDiffuse(), p3Size, 1, hFile);
		// write Specular
		fwrite(tex->GetSpecular(), p3Size, 1, hFile);
		// write Shininess
		float shininess = tex->GetShininess();
		fwrite(&shininess, sizeof(float), 1, hFile);
	}

	void LiarMeshWrite::WriteString(std::string& s, FILE* hFile)
	{
		int size = static_cast<int>(s.size());
		// wirte char num;
		fwrite(&size, sizeof(int), 1, hFile);
		fwrite(&s.front(), sizeof(char), size, hFile);
	}

	void LiarMeshWrite::GetVertexVer(Liar::LiarMeshParse* parse)
	{
		int ver = 0;
		if (parse->liarPluginCfg->exportPos)
		{
			ver |= (1 << LIAR_POSITION);
		}

		if (parse->liarPluginCfg->exportNormal)
		{
			ver |= (1 << LIAR_NORMAL);
		}

		if (parse->liarPluginCfg->exportColor)
		{
			ver |= (1 << LIAR_COLOR);
		}

		if (parse->liarPluginCfg->exportUV)
		{
			ver |= (1 << LIAR_UV);
		}

		parse->vertexOpen = ver;
	}

}