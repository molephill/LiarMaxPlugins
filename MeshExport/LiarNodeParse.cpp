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

	void LiarNodeParse::ParseRootNode(INode* node, Liar::LiarMeshParse* ctr, bool zy)
	{
		ctr->rootNode = new Liar::LiarNode();
		ctr->rootNode->SetNodeName("root_node");

		int meshIndex = 0;
		ParseChildren(node, ctr, meshIndex, ctr->rootNode, zy);
		ctr->EraseMeshIndex(meshIndex);
	}

	void LiarNodeParse::ParseChildren(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarNode* parentNode, bool zy)
	{
		int numChild = node->NumberOfChildren();
		for (int i = 0; i < numChild; ++i)
		{
			Liar::LiarNode* subNode = parentNode->AddChild();
			ParseNode(node->GetChildNode(i), ctr, index, subNode, zy);
		}

	}

	void LiarNodeParse::ParseNode(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarNode* parent, bool zy)
	{
		// ȡ��0֡ʱ������
		TimeValue tTime = 0;
		ObjectState os = node->EvalWorldState(tTime);

		// ��ѡ��ĵ�������
		if (os.obj)
		{
			//ȡ����Ⱦ���������ID
			DWORD	SuperclassID = os.obj->SuperClassID();
			switch (SuperclassID)
			{
				//����ͼ��
			case SHAPE_CLASS_ID:
				//����ģ��
			case GEOMOBJECT_CLASS_ID:
				ParseGeometry(node, ctr, index, parent, zy);
				break;
			default:
				break;
			}
		}
	}

	void LiarNodeParse::ParseGeometry(INode* node, Liar::LiarMeshParse* ctr, int& index, Liar::LiarNode* parent, bool zy)
	{
		//��ȡ��Ⱦ����
		TimeValue tTime = 0;
		ObjectState os = node->EvalWorldState(tTime);
		if (!os.obj)
			return;
		//���������Ч����ģ�͸�ʽ���򷵻ء�
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
			return;

		//���ģ������
		bool delMesh = false;
		Object* obj = os.obj;
		if (obj)
		{
			//�����ǰ��Ⱦ������ת��Ϊ����ģ��
			if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
			{
				//����ǰ��Ⱦ������ת��Ϊ����ģ��
				TriObject* tri = (TriObject*)obj->ConvertToType(0, Class_ID(TRIOBJ_CLASS_ID, 0));
				//�����ǰ��Ⱦ���屾����������ģ�����ͣ�������ת����������µ�����ģ�͡������ڴ��������Ҫ�����ͷš�
				if (obj != tri)
				{
					delMesh = true;
				}

				if (tri)
				{

					BOOL bDelete = TRUE;
					//ͨ��GetRenderMesh����ȡģ����Ϣ�ṹ��
					Mesh* mesh = tri->GetRenderMesh(tTime, node, *m_maxView, bDelete);
					assert(mesh);
					//�ؽ�����
					mesh->buildNormals();
					//�ؽ����ߺ�Ҫ����һ��checkNormals��鷨�ߡ�
					mesh->checkNormals(TRUE);

					// ���õ�ǰmesh������
					parent->meshIndex = index;

					Liar::LiarMesh* liarMesh = ctr->GetOrNewMesh(index);
					Liar::StringUtil::WChar_tToString(node->GetName(), liarMesh->meshName);

					ctr->ParseLiarMesh(liarMesh, node, mesh, zy);

					// ��ʼ��������
					parent->SetNodeName(liarMesh->meshName);
					ParseChildren(node, ctr, index, parent, zy);
					
					//�����ת��ʱ���µ���Ⱦģ�����ɣ�����������ͷš�
					if (delMesh)
					{
						delete tri;
					}
				}
			}
		}
	}

}
