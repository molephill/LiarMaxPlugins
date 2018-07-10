//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "MeshExport.h"

// =========================================== self ======================================
// 列表框句柄
HWND G_hListBox = nullptr;
void AddStrToOutPutListBox(const char* szText)
{
	if (G_hListBox)
	{
		SendMessage(G_hListBox, LB_ADDSTRING, 0, (LPARAM)szText);
	}
}

ClassDesc2* GetMeshExportDesc() {
	static Liar::MeshExportClassDesc MeshExportDesc;
	return &MeshExportDesc;
}

INT_PTR CALLBACK MeshExportOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static Liar::MeshExport* imp = nullptr;

	switch(message) {
		case WM_INITDIALOG:
			{
				CenterWindow(hWnd, GetParent(hWnd));
				imp = (Liar::MeshExport *)lParam;
				// 初始化
				G_hListBox = ::GetDlgItem(hWnd, IDC_LIST_EXPORT_INFO);

				
				std::string strFileName = Liar::StringUtil::GetLast(imp->GetExportPathName());
				//去掉扩展名
				std::string strFileName_NoExt = Liar::StringUtil::GetHead(strFileName);
				//将字符串设为模型名
				HWND hNameEdit = ::GetDlgItem(hWnd, IDC_STATIC_MODEL_NAME);
				wchar_t ws[MAX_PATH];
				MultiByteToWideChar(CP_ACP, 0, strFileName_NoExt.c_str(), -1, ws, MAX_PATH);
				SetWindowText(hNameEdit, ws);
				return TRUE;
			}
		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case IDC_BUTTON_EXPORT_CANCEL:
					EndDialog(hWnd, 0);
					return TRUE;
				case IDC_BUTTON_EXPORT_OK:
					if (imp)
					{
						HWND hNameEdit = ::GetDlgItem(hWnd, IDC_STATIC_MODEL_NAME);
						WStr szMeshName;
						GetWindowText(hNameEdit, szMeshName);
						//导出场景
						std::string tmp("");
						Liar::StringUtil::GetWSTR2Char(szMeshName, tmp);
						imp->ExportMesh(tmp.c_str());
					}
					return TRUE;
				default:
					break;
			}
		}
		break;
	}
	return 0;
}


//--- MeshExport -------------------------------------------------------
namespace Liar
{
	MeshExport::MeshExport():
		m_pExpInterface(nullptr), m_pInterface(nullptr)
		, m_exportSelect(false), m_szExportPath("")
		, m_materialSize(0)
	{
		m_allMaterials = new std::vector<Liar::SubMaterial*>();
	}

	MeshExport::~MeshExport()
	{

	}

// ==================================== self =====================================
	int MeshExport::ExportMesh(const char* szName)
	{
		//通过m_pInterface取得场景中的材质库
		MtlBaseLib * scenemats = m_pInterface->GetSceneMtls();

		if (scenemats)
		{
			char	tText[200];
			int tCount = scenemats->Count();

			sprintf(tText, "共有材质%d个", tCount);
			AddStrToOutPutListBox(tText);

			if (tCount > 0)
			{
				ClearAll();
				//取得材质数量
				int matrialSize = 0;
				for (int i = 0; i < tCount; i++)
				{
					MtlBase * vMtl = (*scenemats)[i];
					if (IsMtl(vMtl))
					{
						Liar::SubMaterial* pParseMaterial = nullptr;
						if (matrialSize >= m_materialSize)
						{
							pParseMaterial = new Liar::SubMaterial();
						}
						else
						{
							pParseMaterial = m_allMaterials->at(i);
						}
						memset(pParseMaterial, 0, sizeof(SubMaterial));

						pParseMaterial->SetID(matrialSize++);
						Liar::StringUtil::GetWSTR2Char(vMtl->GetName(), pParseMaterial->GetName());
						
						////遍历材质所用的贴图
						pParseMaterial->SubTextureEnum(vMtl, matrialSize);
						m_allMaterials->push_back(pParseMaterial);
					}
				}

				m_materialSize = matrialSize;
			}
		}

		return 0;
	}

	void MeshExport::ClearAll()
	{
	}
// ==================================== self =====================================

	int MeshExport::ExtCount()
	{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
		return 1;
	}

	const TCHAR *MeshExport::Ext(int /*i*/)
	{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
		return _T("Mesh");
	}

	const TCHAR *MeshExport::LongDesc()
	{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
		return _T("");
	}

	const TCHAR *MeshExport::ShortDesc()
	{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
		return _T("LiarMesh");
	}

	const TCHAR *MeshExport::AuthorName()
	{
#pragma message(TODO("Return ASCII Author name"))
		return _T("Liar");
	}

	const TCHAR *MeshExport::CopyrightMessage()
	{
#pragma message(TODO("Return ASCII Copyright message"))
		return _T("");
	}

	const TCHAR *MeshExport::OtherMessage1()
	{
		//TODO: Return Other message #1 if any
		return _T("");
	}

	const TCHAR *MeshExport::OtherMessage2()
	{
		//TODO: Return other message #2 in any
		return _T("");
	}

	unsigned int MeshExport::Version()
	{
		#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
		return 100;
	}

	void MeshExport::ShowAbout(HWND /*hWnd*/)
	{
		// Optional
	}

	BOOL MeshExport::SupportsOptions(int /*ext*/, DWORD /*options*/)
	{
		#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
		return TRUE;
	}


	int	MeshExport::DoExport(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options)
	{
		#pragma message(TODO("Implement the actual file Export here and"))

		// 保存变量
		Liar::StringUtil::GetTChar2Char(name, m_szExportPath);

		m_pExpInterface = ei;
		m_pInterface = ip;
		m_exportSelect = (options & SCENE_EXPORT_SELECTED);

		if (!suppressPrompts)
			DialogBoxParam(hInstance,
				MAKEINTRESOURCE(IDD_PANEL),
				GetActiveWindow(),
				MeshExportOptionsDlgProc, (LPARAM)this);

		#pragma message(TODO("return TRUE If the file is exported properly"))
		return FALSE;
	}
}