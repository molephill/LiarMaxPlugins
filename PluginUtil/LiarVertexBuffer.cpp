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
		//位置，要注意的是在3ds max中z值是朝上的，y值是朝前的，而在我们的游戏中,y值朝上，z值朝前。所以要做下处理。
		position->ParseMaxPoint3(mesh->verts[index], zy);
		normal->ParseMaxPoint3(mesh->getNormal(index), zy);
	}
#endif // PLUGINS

}
