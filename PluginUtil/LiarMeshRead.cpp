#include "LiarMeshRead.h"
#include <LiarStringUtil.h>

namespace Liar
{

#ifndef PLUGINS
	// ======================= read model ===========================
	Liar::Model* LiarMeshRead::ReadModel(const char* path, const char* texBasePath)
	{
		Liar::LiarNode* node = new Liar::LiarNode();
		Liar::LiarMeshRead::ReadNode(path, *node);
		Liar::Model* model = new Liar::Model();
		ReadChildModel(*model, *node, texBasePath);
		delete node;
		return model;
	}

	void LiarMeshRead::ReadChildModel(Liar::Model& model, const Liar::LiarNode& node, const char* basePath)
	{
		std::vector<Liar::LiarNode*>* children = node.GetChildren();
		if (children)
		{
			size_t size = children->size();
			for (size_t i = 0; i < size; ++i)
			{
				Liar::LiarNode* subNode = children->at(i);
				std::string& nodeName = subNode->GetNodeName();
				model.AddMesh(nodeName, basePath);

				// add child nodes
				ReadChildModel(model, *subNode, basePath);
			}
		}
	}
#endif // !PLUGINS

	// ======================= read model ===========================

	void LiarMeshRead::ReadNode(const char* path, Liar::LiarNode& node)
	{
		FILE* pFile;
#ifndef __APPLE__
		fopen_s(&pFile, path, "rb+");
#else
		pFile = fopen(path, "rb+");
#endif
		std::string basePath = path;
		basePath = Liar::StringUtil::GetHead(basePath, "/");

		unsigned int ver = 0;
		// read version
		fread(&ver, sizeof(unsigned int), 1, pFile);

		// read root
		basePath += "/";
		ReadChildNode(node, basePath, pFile);

		fclose(pFile);
	}

	void LiarMeshRead::ReadChildNode(Liar::LiarNode& node, std::string& basePath, FILE* pFile)
	{
		// read size;
		int size = 0;
		fread(&size, sizeof(int), 1, pFile);

		for (int i = 0; i < size; ++i)
		{
			std::string nodeName;
			Liar::LiarNode* subNode = node.AddChild();
			ReadString(nodeName, pFile);

			nodeName = basePath + nodeName;
			subNode->SetNodeName(nodeName);

			// read children
			ReadChildNode(*subNode, basePath, pFile);
		}
	}

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
				basePath += "/";
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
		// read vertex open status
		int vertexOpen = 0;
		fread(&vertexOpen, sizeof(int), 1, pFile);
		// read mesh`s name
		//fread(&(mesh->meshName), sizeof(std::string), 1, pFile);
		ReadString(mesh->meshName, pFile);
		// read mesh`s Geometery
		ReadLiarGeometery(vertexOpen, mesh->GetGeo(), pFile);
		// read mesh`s material
		ReadLiarMaterial(mesh->GetMat(), pFile);
	}

	void LiarMeshRead::ReadLiarGeometery(int vertexOpen, Liar::LiarGeometry* geo, FILE* pFile)
	{
		// set vertex open
		geo->SetVertexOpen(vertexOpen);

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
		// check vertexopen
		bool pos = Liar::LairVersionCtr::CheckVertexOpen(vertexOpen, LIAR_POSITION);
		bool normal = Liar::LairVersionCtr::CheckVertexOpen(vertexOpen, LIAR_NORMAL);
		bool color = Liar::LairVersionCtr::CheckVertexOpen(vertexOpen, LIAR_COLOR);
		bool uv = Liar::LairVersionCtr::CheckVertexOpen(vertexOpen, LIAR_UV);
		// read buffer
		for (int i = 0; i < bufferSize; ++i)
		{
			Liar::LiarVertexBuffer* buffer = new Liar::LiarVertexBuffer();
			geo->GetBuffers()->push_back(buffer);
			ReadLiarVertexBuffer(buffer, pFile, pos, normal, color, uv);
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

	void LiarMeshRead::ReadLiarVertexBuffer(Liar::LiarVertexBuffer* buff, FILE* pFile, bool pos, bool normal, bool color, bool uv)
	{
		size_t p3Size = sizeof(Liar::Vector3D);
		// read pos
		if (pos)
		{
			buff->position = new Liar::Vector3D();
			fread(buff->position, p3Size, 1, pFile);
		}
		// read normal
		if (normal)
		{
			buff->normal = new Liar::Vector3D();
			fread(buff->normal, p3Size, 1, pFile);
		}
		// read color
		if (color)
		{
			buff->color = new Liar::Vector3D();
			fread(buff->color, p3Size, 1, pFile);
		}
		// read uv
		if (uv)
		{
			size_t p2Size = sizeof(Liar::Vector2D);
			buff->uv = new Liar::Vector2D();
			fread(buff->uv, p2Size, 1, pFile);
		}
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
