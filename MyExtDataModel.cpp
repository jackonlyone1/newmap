// MyExtDataModel.cpp: implementation of the CMyExtDataModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyExtDataModel.h"
#include "MapDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMyExtDataModel, CFODataModel, 0)

CMyExtDataModel::CMyExtDataModel()
{
}

CMyExtDataModel::CMyExtDataModel(const CMyExtDataModel& source)
{
	*this			= source;
}

CMyExtDataModel::~CMyExtDataModel()
{
}

CFODataModel* CMyExtDataModel::Copy() const
{
	return (new CMyExtDataModel(*this));
}

CFODrawShape *CMyExtDataModel::DoCreateShapeByType(UINT m_drawshape,CRect &rcCreate,CString strFileName,CFOToolBoxItem *pCurItem)
{
	return CFODataModel::DoCreateShapeByType(m_drawshape,rcCreate,strFileName,pCurItem);
}
