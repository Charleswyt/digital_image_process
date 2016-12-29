#if !defined(AFX_DLGGEOZOOM2_H__3B544968_7588_433E_AD96_40D6120A6E79__INCLUDED_)
#define AFX_DLGGEOZOOM2_H__3B544968_7588_433E_AD96_40D6120A6E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgGeoZoom2 : public CDialog
{
	// Construction
public:
	CDlgGeoZoom2(CWnd* pParent = NULL); // standard constructor

	// Dialog Data
	//{{AFX_DATA(CDlgGeoZoom)
	enum { IDD = IDD_DLG_GEOZoom2 };
	double m_ZoomX, m_ZoomY;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGeoZoom)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgGeoZoom)
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DLGGEOZOOM_H__3B544968_7588_433E_AD96_40D6120A6E79__INCLUDED_)