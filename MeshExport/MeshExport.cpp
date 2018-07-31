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
#include "LiarMeshParse.h"

// =========================================== self ======================================
// 列表框句柄
HWND G_hListBox = nullptr;
void AddStrToOutPutListBox(const char* szText)
{
	if (G_hListBox)
	{
		SendMessageA(G_hListBox, LB_ADDSTRING, 0, (LPARAM)szText);
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

				// 初始化导出项
				if (imp)
				{
					Liar::PluginCfg* cfg = imp->GetMeshExport()->liarPluginCfg;
					SetCheckBox(hWnd, IDC_CHECK_POS, cfg->exportPos);
					SetCheckBox(hWnd, IDC_CHECK_NORMAL, cfg->exportNormal);
					SetCheckBox(hWnd, IDC_CHECK_UV, cfg->exportUV);
					SetCheckBox(hWnd, IDC_CHECK_COLOR, cfg->exportColor);
					SetCheckBox(hWnd, IDC_CHECK_POS_NOR, cfg->posNormalize);
					SetCheckBox(hWnd, IDC_CHECK_RE_ZY, cfg->revertZY);
					SetCheckBox(hWnd, IDC_CHECK_RE_UV, cfg->revertUV);
					SetCheckBox(hWnd, IDC_CHECK_SINGLE_MODEL, cfg->singleExportModel);
				}

				std::string strFileName = Liar::StringUtil::GetLast(imp->GetMeshExport()->GetExportPathName());
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
					EndDialog(hWnd, IDOK);
					return TRUE;
				case IDC_CHECK_POS:
				case IDC_CHECK_NORMAL:
				case IDC_CHECK_COLOR:
				case IDC_CHECK_UV:
				case IDC_CHECK_POS_NOR:
				case IDC_CHECK_RE_ZY:
				case IDC_CHECK_RE_UV:
				case IDC_CHECK_SINGLE_MODEL:
					if (imp)
					{
						int state = GetCheckBox(hWnd, wParam);
						imp->SetExportParam(wParam, state);
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
	MeshExport::MeshExport():m_meshParse(new Liar::LiarMeshParse())
	{
	}

	MeshExport::~MeshExport()
	{
		delete m_meshParse;
	}

// ==================================== self =====================================
	int MeshExport::ExportMesh(const char*)
	{
		// =============== 解析材质 ==================		
		m_meshParse->ParseNode(m_meshParse->liarPluginCfg->revertZY);

		int meshSize = m_meshParse->GetMeshSize();
		char tText[512];
		for (int i = 0; i < meshSize; ++i)
		{
			Liar::LiarMesh* mesh = m_meshParse->GetMesh(i);
			if (mesh)
			{
				sprintf(tText, "导出对象<%s>.............", mesh->meshName.c_str());
				AddStrToOutPutListBox(tText);
				sprintf(tText, "对应材质<%s>", mesh->GetMaterialName().c_str());
				AddStrToOutPutListBox(tText);
				sprintf(tText, "模型<%s> 顶点数 :<%d> 面数:<%d>", mesh->meshName.c_str(), mesh->vertexNum, mesh->faceNum);
				AddStrToOutPutListBox(tText);
			}
		}

		return 0;
	}

	void MeshExport::SetExportParam(WPARAM wParam, int state)
	{
		bool status = state == BST_CHECKED ? true : false;
		switch (wParam)
		{
		case IDC_CHECK_POS:
			GetMeshExport()->liarPluginCfg->exportPos = status;
			break;
		case IDC_CHECK_NORMAL:
			GetMeshExport()->liarPluginCfg->exportNormal = status;
			break;
		case IDC_CHECK_COLOR:
			GetMeshExport()->liarPluginCfg->exportColor = status;
			break;
		case IDC_CHECK_UV:
			GetMeshExport()->liarPluginCfg->exportUV = status;
			break;
		case IDC_CHECK_POS_NOR:
			GetMeshExport()->liarPluginCfg->posNormalize = status;
			break;
		case IDC_CHECK_RE_ZY:
			GetMeshExport()->liarPluginCfg->revertZY = status;
			break;
		case IDC_CHECK_RE_UV:
			GetMeshExport()->liarPluginCfg->revertUV = status;
			break;
		case IDC_CHECK_SINGLE_MODEL:
			GetMeshExport()->liarPluginCfg->singleExportModel = status;
			break;
		default:
			break;
		}
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

		m_meshParse->SetControl(name, ei, ip, suppressPrompts, options);

		if (!suppressPrompts)
			DialogBoxParam(hInstance,
				MAKEINTRESOURCE(IDD_PANEL),
				GetActiveWindow(),
				MeshExportOptionsDlgProc, (LPARAM)this);

		#pragma message(TODO("return TRUE If the file is exported properly"))
		return FALSE;
	}
}