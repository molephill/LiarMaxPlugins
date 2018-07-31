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
		void ParseRootNode(INode*, LiarMeshParse*, bool zy = true);

	private:
		void ParseChildren(INode*, LiarMeshParse*, int&, Liar::LiarNode* p = nullptr, bool zy = true);
		void ParseNode(INode*, LiarMeshParse*, int&, Liar::LiarNode* p = nullptr, bool zy = true);
		void ParseGeometry(INode*, LiarMeshParse*, int&, Liar::LiarNode* p = nullptr, bool zy = true);
	};
}