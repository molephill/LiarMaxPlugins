#include "LiarNodeParse.h"
#include "LiarMeshParse.h"

namespace Liar
{

	LiarNodeParse::LiarNodeParse():m_maxView(new Liar::CMaxNullView())
	{
	}


	LiarNodeParse::~LiarNodeParse()
	{
		delete m_maxView;
	}

	void LiarNodeParse::ParseNode(INode* node, Liar::LiarMeshParse* ctr, int& index, bool zy)
	{
		// 先把自己的解析
		Liar::LiarMesh* parentMesh = ParseSubNode(node, ctr, index, nullptr, zy);

		switch (ctr->liarPluginCfg->meshExportType)
		{
			case LiarMeshExportType::INGORE_CHIRLD:
				break;
			case LiarMeshExportType::INDEPENDENT_CHIRLD:
				ParseChild(node, ctr, index, nullptr, zy);
				break;
			case LiarMeshExportType::NORMAL_CHIRLD:
				ParseChild(node, ctr, index, parentMesh, zy);
				break;
			default:
				break;
		}
	}

	void LiarNodeParse::ParseChild(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarMesh* parent, bool zy)
	{
		int numChild = node->NumberOfChildren();
		for (int i = 0; i < numChild; ++i)
		{
			ParseSubNode(node->GetChildNode(i), ctr, index, parent, zy);
		}
	}

	Liar::LiarMesh* LiarNodeParse::ParseSubNode(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarMesh* parent, bool zy)
	{
		// 取得0帧时的物体
		TimeValue tTime = 0;
		ObjectState os = node->EvalWorldState(tTime);

		// 有选择的导出物体
		if (os.obj)
		{
			//取得渲染物体的类型ID
			DWORD	SuperclassID = os.obj->SuperClassID();
			switch (SuperclassID)
			{
				//基础图形
			case SHAPE_CLASS_ID:
				//网格模型
			case GEOMOBJECT_CLASS_ID:
				return ParseGeometry(node, ctr, index, parent, zy);
				break;
			default:
				break;
			}
		}

		return nullptr;
	}

	Liar::LiarMesh* LiarNodeParse::ParseGeometry(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarMesh* parent, bool zy)
	{
		//获取渲染对象
		TimeValue tTime = 0;
		ObjectState os = node->EvalWorldState(tTime);
		if (!os.obj)
			return nullptr;
		//如果不是有效网格模型格式，则返回。
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
			return nullptr;

		//如果模型是由
		bool delMesh = false;
		Object* obj = os.obj;
		if (obj)
		{
			//如果当前渲染物体能转换为网格模型
			if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
			{
				//将当前渲染物体能转换为网格模型
				TriObject* tri = (TriObject*)obj->ConvertToType(0, Class_ID(TRIOBJ_CLASS_ID, 0));
				//如果当前渲染物体本身来是网格模型类型，它经过转换后会生成新的网格模型。所以在处理结束后要进行释放。
				if (obj != tri)
				{
					delMesh = true;
				}

				if (tri)
				{

					BOOL bDelete = TRUE;
					//通过GetRenderMesh来获取模型信息结构。
					Mesh* mesh = tri->GetRenderMesh(tTime, node, *m_maxView, bDelete);
					assert(mesh);
					//重建法线
					mesh->buildNormals();
					//重建法线后要调用一下checkNormals检查法线。
					mesh->checkNormals(TRUE);

					Liar::LiarMesh* liarMesh = parent;
					if (!liarMesh)
					{
						liarMesh = ctr->GetOrNewMesh(index);
						Liar::StringUtil::WChar_tToString(node->GetName(), liarMesh->meshName);
					}
					ctr->ParseLiarMesh(liarMesh, node, mesh, zy);
					
					//如果在转换时有新的渲染模型生成，在这里进行释放。
					if (delMesh)
					{
						delete tri;
					}

					return liarMesh;
				}
			}
		}

		return nullptr;

	}
}
