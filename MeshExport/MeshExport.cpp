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

ClassDesc2* GetMeshExportDesc() {
	static Liar::MeshExportClassDesc MeshExportDesc;
	return &MeshExportDesc;
}

INT_PTR CALLBACK MeshExportOptionsDlgProc(HWND hWnd,UINT message,WPARAM,LPARAM lParam) {
	static Liar::MeshExport* imp = nullptr;

	switch(message) {
		case WM_INITDIALOG:
			imp = (Liar::MeshExport *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- MeshExport -------------------------------------------------------
namespace Liar
{
	MeshExport::MeshExport()
	{

	}

	MeshExport::~MeshExport()
	{

	}

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


	int	MeshExport::DoExport(const TCHAR* /*name*/, ExpInterface* /*ei*/, Interface* /*ip*/, BOOL suppressPrompts, DWORD /*options*/)
	{
		#pragma message(TODO("Implement the actual file Export here and"))

		if (!suppressPrompts)
			DialogBoxParam(hInstance,
				MAKEINTRESOURCE(IDD_PANEL),
				GetActiveWindow(),
				MeshExportOptionsDlgProc, (LPARAM)this);

		#pragma message(TODO("return TRUE If the file is exported properly"))
		return FALSE;
	}
}