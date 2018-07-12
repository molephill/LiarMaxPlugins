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
		// �Ȱ��Լ��Ľ���
		ParseSubNode(node, ctr, index, zy);

		int numChild = node->NumberOfChildren();
		for (int i = 0; i < numChild; ++i)
		{
			ParseSubNode(node->GetChildNode(i), ctr, index, zy);
		}
	}

	void LiarNodeParse::ParseSubNode(INode* node, Liar::LiarMeshParse* ctr, int& index, bool zy)
	{
		// ȡ��0֡ʱ������
		TimeValue tTime = 0;
		ObjectState os = node->EvalWorldState(tTime);

		// ��ѡ��ĵ�������
		if (os.obj)
		{
			//char tText[200];
			//sprintf(tText,"����<%s>----------------------<%d : %d>",node->GetName(),os.obj->SuperClassID(),os.obj->ClassID());
			//AddStrToOutPutListBox(tText);
			//ȡ����Ⱦ���������ID
			DWORD	SuperclassID = os.obj->SuperClassID();
			switch (SuperclassID)
			{
				//����ͼ��
			case SHAPE_CLASS_ID:
				//����ģ��
			case GEOMOBJECT_CLASS_ID:
				ParseGeometry(node, ctr, index, zy);
				break;
			default:
				break;
			}
		}
	}

	void LiarNodeParse::ParseGeometry(INode* node, Liar::LiarMeshParse* ctr, int& index, bool zy)
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

					Liar::LiarMesh* liarMesh = ctr->GetOrNewMesh(index);
					ctr->ParseLiarMesh(liarMesh, node, mesh, zy);
					
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
