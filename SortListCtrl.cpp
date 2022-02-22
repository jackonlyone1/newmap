#include "stdafx.h"
#include "SortListCtrl.h"
#include "MapDemoDoc.h"
#include "MapDemoView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


struct ItemData
{
public:
	ItemData() : arrpsz( NULL ), dwData( NULL ) {}
	
	LPTSTR* arrpsz;
	DWORD dwData;
	
private:
	// ban copying.
	ItemData( const ItemData& );
	ItemData& operator=( const ItemData& );
};


CSortListCtrl::CSortListCtrl()
{
}


CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CFOBaseGridListCtrl)
//{{AFX_MSG_MAP(CSortListCtrl)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
ON_NOTIFY_REFLECT(NM_CLICK, OnDblclkList1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers

void CSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;
	
	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
//	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );

	*pResult = 0;
}


void CSortListCtrl::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW*   pNMListView   =   (NM_LISTVIEW*)pNMHDR;  
	
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	
	if (pNMListView->iItem != -1)   
	{   
		CFODrawShape *pData = (CFODrawShape*)GetItemData(pNMListView->iItem);
		
		CMapDemoView *pView = (CMapDemoView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SelectNewShape(pData);
			pView->SetLogCenter(pData->GetSnapRect().CenterPoint());
		}
	}
	
	*pResult = 0;

}
