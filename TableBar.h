#if !defined(AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_)
#define AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl window
#include "SortListCtrl.h"
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableBar
 
//===========================================================================
// Summary:
//     The CTableBar class derived from CFOPControlBar
//      Table Bar
//===========================================================================

class CTableBar : public CFOPControlBar
{

	// Construction
public:
	// constructor
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Table Bar, Constructs a CTableBar object.
	//		Returns A  value.
	CTableBar();

 
	// Tree , This member specify CSortListCtrl object.  
	CSortListCtrl m_TreeCtrl;
 
	// Context Image Small, This member is a collection of same-sized images.  
	CImageList m_ContextImageSmall;
	// Init shapes.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Shapes, Call InitShapes after creating a new object.
	// Parameters:
	//		*pDataModel---Data Model, A pointer to the CFODataModel  or NULL if the call failed.
	void InitShapes(CFODataModel *pDataModel);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Select Item, Call this function to select the given item.
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	void SelectItem(CFODrawShape *pShape);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableBar)
	//}}AFX_VIRTUAL

// Implementation
public:

	// destructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Table Bar, Destructor of class CTableBar
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CTableBar();

	// Generated message map functions
protected:

	//{{AFX_MSG(CTableBar)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		lpCreateStruct---Create Struct, Specifies a LPCREATESTRUCT lpCreateStruct object.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Size, Called after the size of CWnd has changed.
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		cx---Specifies A integer value.  
	//		cy---Specifies A integer value.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Erase Background, Called when the window background needs erasing.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
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

#endif // !defined(AFX_TABLEBAR_H__432237DD_75B1_4E05_AC55_E7E1D036303A__INCLUDED_)
