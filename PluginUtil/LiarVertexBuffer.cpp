#include "LiarVertexBuffer.h"

namespace Liar
{
	LiarVertexBuffer::LiarVertexBuffer()
		:x(0.0f),y(0.0f),z(0.0f)
		,nx(0.0f),ny(0.0f),nz(0.0f)
		,r(0.0f),g(0.0f),b(0.0f)
		,u(0.0f),v(0.0f)
	{
	}


	LiarVertexBuffer::~LiarVertexBuffer()
	{
	}

#ifdef PLUGINS
	void LiarVertexBuffer::ParseMesh(Mesh* mesh, int index)
	{
		//λ�ã�Ҫע�������3ds max��zֵ�ǳ��ϵģ�yֵ�ǳ�ǰ�ģ��������ǵ���Ϸ��,yֵ���ϣ�zֵ��ǰ������Ҫ���´���
		Point3 vert = mesh->verts[index];
		x = vert.x;
		y = vert.z;
		z = vert.y;

		//���ߣ�ͬ��Y���Z��Ҫ�л��¡�
		Point3 norm = mesh->getNormal(index);
		nx = norm.x;
		ny = norm.z;
		nz = norm.y;
	}
#endif // PLUGINS

}
