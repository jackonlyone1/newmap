// MapDemo.h : main header file for the MAPDEMO application
//

#if !defined(AFX_MAPDEMO_H__4C38D0C7_A044_11D6_A617_0050BAE30439__INCLUDED_)
#define AFX_MAPDEMO_H__4C38D0C7_A044_11D6_A617_0050BAE30439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapDemoApp:
// See MapDemo.cpp for the implementation of this class
//

 
//===========================================================================
// Summary:
//     The CMapDemoApp class derived from CWinApp
//      Map Demo Application
//===========================================================================

class CMapDemoApp : public CWinApp
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Map Demo Application, Constructs a CMapDemoApp object.
	//		Returns A  value.
	CMapDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapDemoApp)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Instance, Override to perform Windows instance initialization, such as creating your window objects.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMapDemoApp)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Application About, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDEMO_H__4C38D0C7_A044_11D6_A617_0050BAE30439__INCLUDED_)
