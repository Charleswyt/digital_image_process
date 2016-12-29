// DlgGeoZoom2.cpp : implementation file
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgGeoZoom2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**********************************************/
// CDlgGeoZoom dialog

CDlgGeoZoom2::CDlgGeoZoom2(CWnd* pParent /*=NULL*/) : CDialog(CDlgGeoZoom2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGeoZoom)
	m_ZoomX = 0.5; 
	m_ZoomY = 0.3;
	//}}AFX_DATA_INIT
}

void CDlgGeoZoom2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGeoZoom)
	DDX_Text(pDX, IDC_EDIT_Zoom1, m_ZoomX);
	DDV_MinMaxFloat(pDX, m_ZoomX, 0.25f, 4.f);
	DDX_Text(pDX, IDC_EDIT_Zoom2, m_ZoomY);
	DDV_MinMaxFloat(pDX, m_ZoomY, 0.25f, 4.f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgGeoZoom2, CDialog)
	//{{AFX_MSG_MAP(CDlgGeoZoom)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**********************************************/
// CDlgGeoZoom message handlers