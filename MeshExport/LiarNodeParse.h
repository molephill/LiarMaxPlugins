#pragma once
#include <iparamm2.h>
#include <iparamb2.h>
#include <triobj.h>
#include <maxapi.h>

#include <LiarMesh.h>

namespace Liar
{
	class LiarMeshParse;

	class CMaxNullView:public View
	{
	public:
		Point2 ViewToScreen(Point3 p) {
			return Point2(p.x, p.y);
		}
	};

	class LiarNodeParse
	{
	public:
		LiarNodeParse();
		~LiarNodeParse();

	private:
		// 临时导出变量
		CMaxNullView* m_maxView;

	public:
		void ParseNode(INode*, LiarMeshParse*, int&, bool zy = true);

	private:
		Liar::LiarMesh* ParseSubNode(INode*, LiarMeshParse*, int&, Liar::LiarMesh* p = nullptr, bool zy = true);
		void ParseChild(INode*, LiarMeshParse*, int&, Liar::LiarMesh* p = nullptr, bool zy = true);
		Liar::LiarMesh* ParseGeometry(INode*, LiarMeshParse*, int&, Liar::LiarMesh* p = nullptr, bool zy = true);
	};
}