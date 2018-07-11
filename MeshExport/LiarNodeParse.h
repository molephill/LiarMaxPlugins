#pragma once
#include <iparamm2.h>
#include <iparamb2.h>
#include <triobj.h>
#include <maxapi.h>

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
		void ParseNode(INode*, LiarMeshParse*, int&);

	private:
		void ParseSubNode(INode*, LiarMeshParse*, int&);
		void ParseGeometry(INode*, LiarMeshParse*, int&);
	};
}