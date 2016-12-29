#include "stdafx.h"
#include "DIP.h"
#include "DlgColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgColor::CDlgColor(CWnd* pParent /*=NULL*/) : CDialog(CDlgColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgColor)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgColor::DoDataExchange(CDataExchange*
	pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgColor)
	DDX_Control(pDX, IDC_COLOR_LIST, m_lstColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgColor, CDialog)
	//{{AFX_MSG_MAP(CDlgColor)
	ON_LBN_DBLCLK(IDC_COLOR_LIST, OnDblclkColorList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgColor::OnInitDialog()
{
	int i;								// 循环变量
	CDialog::OnInitDialog();			// 调用默认OnInitDialog函数
	for (i = 0; i < m_nColorCount; i++)	// 添加伪彩色编码
		m_lstColor.AddString(m_lpColorName + i * m_nNameLen);
	m_lstColor.SetCurSel(m_nColor);		// 选中初始编码表
	
	return TRUE;
}

void CDlgColor::OnDblclkColorList()
{
	OnOK();								// 双击事件，直接调用OnOK()成员函数
}

void CDlgColor::OnOK()
{
	m_nColor = m_lstColor.GetCurSel();	// 用户单击确定按钮
	CDialog::OnOK();					// 调用默认的OnOK()函数
}