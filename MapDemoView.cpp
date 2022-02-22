// MapDemoView.cpp : implementation of the CMapDemoView class
//

#include "stdafx.h"
#include "MapDemo.h"

#include "MapDemoDoc.h"
#include "MapDemoView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView

IMPLEMENT_DYNCREATE(CMapDemoView, CFODrawView)
BEGIN_MESSAGE_MAP(CMapDemoView,CFODrawView)
	//{{AFX_MSG_MAP(CMapDemoView)
	ON_COMMAND(ID_FO_MAP_ITEM1, OnFoMapItem1)
	ON_UPDATE_COMMAND_UI(ID_FO_MAP_ITEM1, OnUpdateFoMapItem1)
	ON_COMMAND(ID_FO_MAP_ITEM2, OnFoMapItem2)
	ON_UPDATE_COMMAND_UI(ID_FO_MAP_ITEM2, OnUpdateFoMapItem2)
	ON_COMMAND(ID_FO_MAP_ITEM3, OnFoMapItem3)
	ON_UPDATE_COMMAND_UI(ID_FO_MAP_ITEM3, OnUpdateFoMapItem3)
	ON_COMMAND(ID_FO_MAP_ITEM4, OnFoMapItem4)
	ON_UPDATE_COMMAND_UI(ID_FO_MAP_ITEM4, OnUpdateFoMapItem4)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_TEST, OnTest)
#if _MFC_VER >= 0x0421
	ON_WM_MOUSEWHEEL()
#endif
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFODrawView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFODrawView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFODrawView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView construction/destruction

CMapDemoView::CMapDemoView()
{
	// TODO: add construction code here
	EnableShowSelectionAlways(TRUE);
}

CMapDemoView::~CMapDemoView()
{
}

BOOL CMapDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs
	return CFODrawView::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView drawing

void CMapDemoView::OnDraw(CDC* pDC)
{
	CMapDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Draw(pDC);
	// TODO: add draw code for native data here
}

void CMapDemoView::DoChangeModel(CFODataModel * pModel)
{
//	CSize szCanvas = CSize(1000,1000);
//	pModel->SetCanvasSize(szCanvas);
}

void CMapDemoView::OnInitialUpdate()
{
	SetCurrentModel(GetDocument()->m_pDataModel);
	CFODrawView::OnInitialUpdate();
	GetCurrentModel()->SetBorderShow(FALSE);

	UpdateScrollBarSize();

	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	//	if(pParent->IsWindowVisible())
	{
		pParent->m_wndTableBar.InitShapes(GetCurrentModel());
	}
	GetCurrentModel()->SetDesignMode(FALSE);
	ShowRulers(FALSE);
	SetLogCenter(GetCurrentModel()->GetPagePosition().CenterPoint());
//	ZoomToFitPageWidth();
}

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView printing

BOOL CMapDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return CFODrawView::OnPreparePrinting(pInfo);
}

void CMapDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	// E-XD++ Library Add line.
	CFODrawView::OnBeginPrinting(pDC,pInfo);
}

void CMapDemoView::DoChangeHitShape(CFODrawShape *pShape)
{
	CFODrawShape *pOld = m_pCurRunModelHitShape;
	if(pOld != pShape && pShape != NULL)
	{
		CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
		ASSERT_VALID(pParent);
		//	if(pParent->IsWindowVisible())
		{
			pParent->m_wndTableBar.SelectItem(pShape);
			pParent->m_wndTableBar.m_TreeCtrl.UpdateWindow();
		}
	}
	m_pCurRunModelHitShape = pShape;
}

void CMapDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView diagnostics

#ifdef _DEBUG
void CMapDemoView::AssertValid() const
{

//E-XD++ Library add lines.
	CFODrawView::AssertValid();

	//CView::AssertValid();
}

void CMapDemoView::Dump(CDumpContext& dc) const
{

//E-XD++ Library add lines.
	CFODrawView::Dump(dc);

	//CView::Dump(dc);
}

CMapDemoDoc* CMapDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapDemoDoc)));
	return (CMapDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView message handlers
//E-XD++ Library add line.
void CMapDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFODrawView::OnPrint(pDC, pInfo);
}

void CMapDemoView::SelectNewShape(CFODrawShape *pShapeX)
{
	if(GetCurrentModel()->IsDesignMode())
	{
		CFODrawShape *pShape = NULL;
		CFODrawShapeList lstUpdate;
		POSITION pos = m_listSelectComp.GetHeadPosition();
		while(pos != NULL)
		{
			pShape = (CFODrawShape *)m_listSelectComp.GetNext(pos);
			lstUpdate.AddTail(pShape);
			pShape->SetSelectedMode(FALSE);
		}
		
		if(pShapeX != NULL && pShapeX->IsKindOf(RUNTIME_CLASS(CFODrawShape)))
		{
			m_listSelectComp.RemoveAll();
			AddToSelection(pShapeX);
			
			if(lstUpdate.Find(pShapeX) == NULL)
			{
				lstUpdate.AddTail(pShapeX);
			}
		}
		
		if(lstUpdate.GetCount() >0)
		{
			DoCorrectTabOrder();
			UpdateShapes(&lstUpdate);
		}
	}
	else
	{
		CFODrawShape *pShape = m_pCurRunModelHitShape;
		CFODrawShapeList lstUpdate;
		
		if(pShape != NULL)
		{
			lstUpdate.AddTail(pShape);
		}
		
		if(pShapeX != NULL)
		{
			lstUpdate.AddTail(pShapeX);
		}
		m_pCurRunModelHitShape = pShapeX;
		
		if(lstUpdate.GetCount() >0)
		{
			DoCorrectTabOrder();
			UpdateShapes(&lstUpdate);
		}
	}
	
}

#if _MFC_VER >= 0x0421

BOOL CMapDemoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	
	if (zDelta > 0)
		ZoomIn();
	else if (zDelta < 0)
		ZoomOut();
	
	return TRUE;
}
#endif

void CMapDemoView::OnFoMapItem1() 
{
	// TODO: Add your action handler code here
	if(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES1)
	{
		m_action_state = State_SelectNone;
		m_drawshape = FO_COMP_NONE;
		FOSetSystemCursor(IDC_ARROW);
		return;
	}
	StartCustomShapeID(IDR_COMPSRES1);
	AddShapePort(0.5,0.5);
}

void CMapDemoView::OnUpdateFoMapItem1(CCmdUI* pCmdUI) 
{
	// TODO: Add your action update UI handler code here
	BOOL bDesign = GetCurrentModel()->IsDesignMode();
	pCmdUI->Enable(bDesign);

	pCmdUI->SetCheck(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES1);

}

void CMapDemoView::OnFoMapItem2() 
{
	// TODO: Add your action handler code here
	if(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES2)
	{
		m_action_state = State_SelectNone;
		m_drawshape = FO_COMP_NONE;
		FOSetSystemCursor(IDC_ARROW);
		return;
	}
	StartCustomShapeID(IDR_COMPSRES2);
	AddShapePort(0.5,0.5);
}

void CMapDemoView::OnUpdateFoMapItem2(CCmdUI* pCmdUI) 
{
	// TODO: Add your action update UI handler code here
	BOOL bDesign = GetCurrentModel()->IsDesignMode();
	pCmdUI->Enable(bDesign);

	pCmdUI->SetCheck(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES2);

}

void CMapDemoView::OnFoMapItem3() 
{
	// TODO: Add your action handler code here
	if(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES3)
	{
		m_action_state = State_SelectNone;
		m_drawshape = FO_COMP_NONE;
		FOSetSystemCursor(IDC_ARROW);
		return;
	}
	StartCustomShapeID(IDR_COMPSRES3);
	AddShapePort(0.5,0.5);
}

void CMapDemoView::OnUpdateFoMapItem3(CCmdUI* pCmdUI) 
{
	// TODO: Add your action update UI handler code here
	BOOL bDesign = GetCurrentModel()->IsDesignMode();
	pCmdUI->Enable(bDesign);

	pCmdUI->SetCheck(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES3);

}

void CMapDemoView::OnFoMapItem4() 
{
	// TODO: Add your action handler code here
	if(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES4)
	{
		m_action_state = State_SelectNone;
		m_drawshape = FO_COMP_NONE;
		FOSetSystemCursor(IDC_ARROW);
		return;
	}
	StartCustomShapeID(IDR_COMPSRES4);
	AddShapePort(0.5,0.5);
}

void CMapDemoView::OnUpdateFoMapItem4(CCmdUI* pCmdUI) 
{
	// TODO: Add your action update UI handler code here
	BOOL bDesign = GetCurrentModel()->IsDesignMode();
	pCmdUI->Enable(bDesign);

	pCmdUI->SetCheck(m_drawshape == FO_COMP_COMPOSITE && m_nCurShapeResID == IDR_COMPSRES4);

}

void CMapDemoView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	FOPrintPreview(this);
}

void CMapDemoView::Serialize(CArchive& ar)
{
//	CFODrawPortsShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.
	}
	else
	{
		//FODO:Add your own code here.
		int nCount;
		ar >> nCount;
		for(int x = 0; x < nCount; x++)
		{
			CFOPolygonShape *pPoly = new CFOPolygonShape;
			pPoly->AddRef();

			CArray<CPoint,CPoint> arPoint;
			int nTotal;
			ar >> nTotal;
			
			for(int y = 0; y < nTotal; y++)
			{
				CPoint pt;
				ar >> pt;
				arPoint.Add(pt);
			}

			COLORREF crColor;
			ar >> crColor;

			pPoly->SetPoints(arPoint);
			pPoly->TrackUpdatePoints();
			pPoly->UpdateDataManager();
			pPoly->UpdateComp();
			pPoly->SetBkColor(crColor);

			GetCurrentModel()->AddChildAtTail(pPoly);
			pPoly->Release();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapDemoView serialization
CFile* CMapDemoView::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
								 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CMapDemoView::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CMapDemoView::OpenDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
	return TRUE;
}

BOOL CMapDemoView::SaveDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
			
	return TRUE;        // success
}

void CMapDemoView::OnTest() 
{
	// TODO: Add your command handler code here
	OpenDocument("C:\\Temp\\2.data");
	FOPInvalidate();
}
