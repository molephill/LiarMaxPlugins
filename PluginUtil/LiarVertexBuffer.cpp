#include "LiarVertexBuffer.h"

namespace Liar
{
	LiarVertexBuffer::LiarVertexBuffer()
	{
		position = new Liar::LiarPoint3();
		normal = new Liar::LiarPoint3();
		color = new Liar::LiarPoint3();
		uv = new LiarPoint2();
	}


	LiarVertexBuffer::~LiarVertexBuffer()
	{
		delete position;
		delete normal;
		delete color;
		delete uv;
	}

#ifdef PLUGINS
	void LiarVertexBuffer::ParseMesh(Mesh* mesh, int index, bool zy)
	{
		//λ�ã�Ҫע�������3ds max��zֵ�ǳ��ϵģ�yֵ�ǳ�ǰ�ģ��������ǵ���Ϸ��,yֵ���ϣ�zֵ��ǰ������Ҫ���´���
		position->ParseMaxPoint3(mesh->verts[index], zy);
		normal->ParseMaxPoint3(mesh->getNormal(index), zy);
	}
#endif // PLUGINS

}
