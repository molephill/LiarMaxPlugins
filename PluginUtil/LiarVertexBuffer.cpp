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
		//位置，要注意的是在3ds max中z值是朝上的，y值是朝前的，而在我们的游戏中,y值朝上，z值朝前。所以要做下处理。
		Point3 vert = mesh->verts[index];
		x = vert.x;
		y = vert.z;
		z = vert.y;

		//法线，同样Y轴和Z轴要切换下。
		Point3 norm = mesh->getNormal(index);
		nx = norm.x;
		ny = norm.z;
		nz = norm.y;
	}
#endif // PLUGINS

}
