// MyExtDataModel.h: interface for the CMyExtDataModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXTDATAMODEL_H__1D050F57_6EB3_11DF_A473_525400EA266C__INCLUDED_)
#define AFX_MYEXTDATAMODEL_H__1D050F57_6EB3_11DF_A473_525400EA266C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 
//===========================================================================
// Summary:
//     The CMyExtDataModel class derived from CFODataModel
//      My Extend Data Model
//===========================================================================

class CMyExtDataModel  : public CFODataModel
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CMyExtDataModel---My Extend Data Model, Specifies a CMyExtDataModel object.
	DECLARE_SERIAL(CMyExtDataModel);
public:

	// Constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Extend Data Model, Constructs a CMyExtDataModel object.
	//		Returns A  value.
	CMyExtDataModel();

	// Copy constructor. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Extend Data Model, Constructs a CMyExtDataModel object.
	//		Returns A  value.  
	// Parameters:
	//		source---Specifies a const CMyExtDataModel& source object.
	CMyExtDataModel(const CMyExtDataModel& source);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C My Extend Data Model, Destructor of class CMyExtDataModel
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CMyExtDataModel();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODataModel,or NULL if the call failed
	// Create a duplicate copy of this object. 
	virtual CFODataModel* Copy() const;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Create Shape By Type, Do create a new shape,override this method to add your own custom shape creating.See sample UserDefine shows.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		m_drawshape---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		&rcCreate---&rcCreate, Specifies A CRect type value.  
	//		strFileName---File Name, Specifies A CString type value.  
	//		*pCurItem---Cur Item, A pointer to the CFOToolBoxItem  or NULL if the call failed.
	virtual CFODrawShape *DoCreateShapeByType(UINT m_drawshape,CRect &rcCreate,CString strFileName = "",CFOToolBoxItem *pCurItem = NULL);
	
};

#endif // !defined(AFX_MYEXTDATAMODEL_H__1D050F57_6EB3_11DF_A473_525400EA266C__INCLUDED_)
