#pragma once

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
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include <iparamm2.h>
#include <iparamb2.h>
#include <stdmat.h>
//SIMPLE TYPE

#include <LiarStringUtil.h>


extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

#define MeshExport_CLASS_ID	Class_ID(0x9bab1aef, 0x5cc0d2f2)

namespace Liar
{
	class LiarMeshParse;

	class MeshExport : public SceneExport {
	public:
		//Constructor/Destructor
		MeshExport();
		~MeshExport();

		int				ExtCount();					// Number of extensions supported
		const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		const TCHAR *	AuthorName();				// ASCII Author name
		const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		const TCHAR *	OtherMessage1();			// Other message #1
		const TCHAR *	OtherMessage2();			// Other message #2
		unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

		BOOL SupportsOptions(int ext, DWORD options);
		int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);

	private:
		LiarMeshParse* m_meshParse;

	public:
		int ExportMesh(const char* szMeshName);
		LiarMeshParse* GetMeshExport() { return m_meshParse; };
		void SetExportParam(WPARAM, int state = BST_CHECKED);
	};

	class MeshExportClassDesc : public ClassDesc2
	{
	public:
		virtual int IsPublic() { return TRUE; }
		virtual void* Create(BOOL /*loading = FALSE*/) { return new MeshExport(); }
		virtual const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
		virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
		virtual Class_ID ClassID() { return MeshExport_CLASS_ID; }
		virtual const TCHAR* Category() { return GetString(IDS_CATEGORY); }

		virtual const TCHAR* InternalName() { return _T("MeshExport"); }	// returns fixed parsable name (scripter-visible name)
		virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle
	};
}

