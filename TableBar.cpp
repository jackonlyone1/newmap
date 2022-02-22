// TableBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TableBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

/////////////////////////////////////////////////////////////////////////////
// CTableBar

CTableBar::CTableBar()
{
}

CTableBar::~CTableBar()
{
}


#define ID_TREE 2093

BEGIN_MESSAGE_MAP(CTableBar, CFOPControlBar)
	//{{AFX_MSG_MAP(CTableBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTableBar message handlers

int CTableBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFOPControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_AUTOARRANGE;
	if (!m_TreeCtrl.Create(dwStyle, CRect(0,0,0,0), this, ID_TREE))
		return -1;      // failed to create tree control
	
	VERIFY(m_ContextImageSmall.Create(IDB_IMAGELIST,16,0,RGB(255,0,255)));
	m_ContextImageSmall.SetBkColor(GetSysColor(COLOR_WINDOW));
	// ... Associate the image lists with the context list
	m_TreeCtrl.SetImageList(&m_ContextImageSmall, LVSIL_SMALL);

	DWORD dwExStyle = WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_TreeCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));
	
	CString strText;
	strText = _T("Item Name");
	m_TreeCtrl.InsertColumn ( 0, strText, LVCFMT_CENTER, 600 );

	m_TreeCtrl.ShowWindow(SW_SHOW);

	return 0;
}

void CTableBar::SelectItem(CFODrawShape *pShape)
{
	if(pShape == NULL)
	{
		return;
	}
	
	int nCount = m_TreeCtrl.GetItemCount();
	for(int x = 0; x < nCount; x++)
	{
		CFODrawShape *pObj = (CFODrawShape *)m_TreeCtrl.GetItemData(x);
		if(pObj == pShape)
		{
			m_TreeCtrl.SetItemState(x,  LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
			m_TreeCtrl.EnsureVisible(x, FALSE);
		}
	}
}

void CTableBar::InitShapes(CFODataModel *pDataModel)
{
	if(pDataModel == NULL)
	{
		return;
	}
	m_TreeCtrl.DeleteAllItems();

	int x = 0;
	CFODrawShape *pObject = NULL;
	int nCount = pDataModel->GetFormObjects()->GetCount();
	for(int y = 0; y < nCount; y++)
	{
		pObject = (CFODrawShape*)(pDataModel->GetFormObjects()->GetObject(y));
		if(!pObject->IsKindOf(RUNTIME_CLASS(CFOLinkShape)))
		{
			CString strDB = pObject->GetObjectCaption();
			if(strDB.IsEmpty())
			{
				strDB.Format(_T("State %u"), y);
				pObject->SetObjectCaption(strDB);
			}

			CString strX = strDB;
			int nItem = m_TreeCtrl.InsertItem(x, strX, 1);
			m_TreeCtrl.SetItemData(nItem, (DWORD) pObject);
			x++;
		}
	}
	
	//	m_TreeCtrl.Expand(hRoot,TVE_EXPAND);
//	m_TreeCtrl.ShowWindow(SW_SHOW);
}

void CTableBar::OnSize(UINT nType, int cx, int cy) 
{
	CFOPControlBar::OnSize(nType, cx, cy);
	if( m_TreeCtrl.GetSafeHwnd() != NULL )
	{
		CRect r;
		GetFullRect(r);
		m_TreeCtrl.SetWindowPos( NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER|SWP_NOACTIVATE );
	}
}

BOOL CTableBar::OnEraseBkgnd( CDC* pDC )
{
	CFOPControlBar::OnEraseBkgnd(pDC);
	return TRUE;
}
