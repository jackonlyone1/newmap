// MapDemoDoc.cpp : implementation of the CMapDemoDoc class
//

#include "stdafx.h"
#include "MapDemo.h"

#include "MapDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDemoDoc

IMPLEMENT_DYNCREATE(CMapDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CMapDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDemoDoc construction/destruction

CMapDemoDoc::CMapDemoDoc()
{
	// TODO: add one-time construction code here

	//E-XD++ Library add lines.
	m_pDataModel = new CMyExtDataModel;
}

CMapDemoDoc::~CMapDemoDoc()
{

	//E-XD++ Library add lines.
	if(m_pDataModel != NULL)
	{
		delete m_pDataModel;
		m_pDataModel = NULL;
	}
}

BOOL CMapDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMapDemoDoc serialization

void CMapDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//E-XD++ Library add lines.	
		m_pDataModel->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		//E-XD++ Library add lines.	
		m_pDataModel->Serialize(ar);
	}
}

//E-XD++ Library add lines.
//added override
void CMapDemoDoc::SetTitle(LPCTSTR lpszTitle)
{
	m_pDataModel->SetDocTitle(lpszTitle);
	CDocument::SetTitle(lpszTitle);
}
void CMapDemoDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDataModel->ResetContent();
	CDocument::DeleteContents();
}

//added override
BOOL CMapDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnSaveDocument(lpszPathName))
	{
		return FALSE;
	}
	m_pDataModel->SetClean();		// Tells the command history that the document is "clean" at this point
	SetModifiedFlag(FALSE);
	return TRUE;
}
//added override (optional as long as you never call this member)
void CMapDemoDoc::SetModifiedFlag(BOOL b)
{
	// Do nothing
	m_pDataModel->SetModifiedFlag(b);
}

//added override
BOOL CMapDemoDoc::IsModified()
{
	return m_pDataModel->IsModified();
}

BOOL CMapDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if(!CDocument::OnOpenDocument(lpszPathName))
	{
		return FALSE;
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMapDemoDoc diagnostics

#ifdef _DEBUG
void CMapDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapDemoDoc commands
