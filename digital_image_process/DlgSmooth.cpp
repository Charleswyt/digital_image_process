// DlgSmooth.cpp : implementation file
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgSmooth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**********************************************/
// CDlgSmooth dialog

CDlgSmooth::CDlgSmooth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSmooth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSmooth)
	m_intType = -1;
	m_iTempH = 0;
	m_iTempW = 0;
	m_iTempMX = 0;
	m_iTempMY = 0;
	m_fTempC = 0.0f;
	//}}AFX_DATA_INIT
}

void CDlgSmooth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSmooth)
	DDX_Radio(pDX, IDC_RAD1, m_intType);
	DDX_Text(pDX, IDC_EDIT_TEMPH, m_iTempH);
	DDV_MinMaxInt(pDX, m_iTempH, 2, 5);
	DDX_Text(pDX, IDC_EDIT_TEMPW, m_iTempW);
	DDV_MinMaxInt(pDX, m_iTempW, 2, 5);
	DDX_Text(pDX, IDC_EDIT_MX, m_iTempMX);
	DDX_Text(pDX, IDC_EDIT_MY, m_iTempMY);
	DDX_Text(pDX, IDC_EDIT_TEMPC, m_fTempC);
	DDX_Text(pDX, IDC_EDIT_V0, m_fpArray[0]);
	DDX_Text(pDX, IDC_EDIT_V1, m_fpArray[1]);
	DDX_Text(pDX, IDC_EDIT_V2, m_fpArray[2]);
	DDX_Text(pDX, IDC_EDIT_V3, m_fpArray[3]);
	DDX_Text(pDX, IDC_EDIT_V4, m_fpArray[4]);
	DDX_Text(pDX, IDC_EDIT_V5, m_fpArray[5]);
	DDX_Text(pDX, IDC_EDIT_V6, m_fpArray[6]);
	DDX_Text(pDX, IDC_EDIT_V7, m_fpArray[7]);
	DDX_Text(pDX, IDC_EDIT_V8, m_fpArray[8]);
	DDX_Text(pDX, IDC_EDIT_V9, m_fpArray[9]);
	DDX_Text(pDX, IDC_EDIT_V10, m_fpArray[10]);
	DDX_Text(pDX, IDC_EDIT_V11, m_fpArray[11]);
	DDX_Text(pDX, IDC_EDIT_V12, m_fpArray[12]);
	DDX_Text(pDX, IDC_EDIT_V13, m_fpArray[13]);
	DDX_Text(pDX, IDC_EDIT_V14, m_fpArray[14]);
	DDX_Text(pDX, IDC_EDIT_V15, m_fpArray[15]);
	DDX_Text(pDX, IDC_EDIT_V16, m_fpArray[16]);
	DDX_Text(pDX, IDC_EDIT_V17, m_fpArray[17]);
	DDX_Text(pDX, IDC_EDIT_V18, m_fpArray[18]);
	DDX_Text(pDX, IDC_EDIT_V19, m_fpArray[19]);
	DDX_Text(pDX, IDC_EDIT_V20, m_fpArray[20]);
	DDX_Text(pDX, IDC_EDIT_V21, m_fpArray[21]);
	DDX_Text(pDX, IDC_EDIT_V22, m_fpArray[22]);
	DDX_Text(pDX, IDC_EDIT_V23, m_fpArray[23]);
	DDX_Text(pDX, IDC_EDIT_V24, m_fpArray[24]);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSmooth, CDialog)
	//{{AFX_MSG_MAP(CDlgSmooth)
	ON_BN_CLICKED(IDC_RAD1, OnRad1)
	ON_BN_CLICKED(IDC_RAD2, OnRad2)
	ON_BN_CLICKED(IDC_RAD3, OnRad3)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPH, OnKillfocusEditTemph)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPW, OnKillfocusEditTempw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**********************************************/
// CDlgSmooth message handlers

void CDlgSmooth::OnRad1()
{
	// 3×3平均模板
	m_intType = 0;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (double)(1.0 / 9.0);
	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 1.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 1.0;
	m_fpArray[6] = 1.0;
	m_fpArray[7] = 1.0;
	m_fpArray[8] = 0.0;
	m_fpArray[9] = 0.0;
	m_fpArray[10] = 1.0;
	m_fpArray[11] = 1.0;
	m_fpArray[12] = 1.0;
	m_fpArray[13] = 0.0;
	m_fpArray[14] = 0.0;
	m_fpArray[15] = 0.0;
	m_fpArray[16] = 0.0;
	m_fpArray[17] = 0.0;
	m_fpArray[18] = 0.0;
	m_fpArray[19] = 0.0;
	m_fpArray[20] = 0.0;
	m_fpArray[21] = 0.0;
	m_fpArray[22] = 0.0;
	m_fpArray[23] = 0.0;
	m_fpArray[24] = 0.0;
	
	UpdateEdit();					// 更新文本框状态
	UpdateData(FALSE);				// 更新
}

void CDlgSmooth::OnRad2()
{
	// 3×3高斯模板
	m_intType = 1;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (double)(1.0 / 16.0);
	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 2.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 2.0;
	m_fpArray[6] = 4.0;
	m_fpArray[7] = 2.0;
	m_fpArray[8] = 0.0;
	m_fpArray[9] = 0.0;
	m_fpArray[10] = 1.0;
	m_fpArray[11] = 2.0;
	m_fpArray[12] = 1.0;
	m_fpArray[13] = 0.0;
	m_fpArray[14] = 0.0;
	m_fpArray[15] = 0.0;
	m_fpArray[16] = 0.0;
	m_fpArray[17] = 0.0;
	m_fpArray[18] = 0.0;
	m_fpArray[19] = 0.0;
	m_fpArray[20] = 0.0;
	m_fpArray[21] = 0.0;
	m_fpArray[22] = 0.0;
	m_fpArray[23] = 0.0;
	m_fpArray[24] = 0.0;
	
	UpdateEdit();					// 更新文本框状态
	UpdateData(FALSE);				// 更新
}

void CDlgSmooth::OnRad3()
{
	m_intType = 2;					// 自定义模板
	UpdateEdit();					// 更新文本框状态
}

void CDlgSmooth::OnOK()
{
	UpdateData(TRUE);				// 获取用户设置（更新）

	// 判断设置是否有效
	if ((m_iTempMX < 0) || (m_iTempMX > m_iTempW - 1) || (m_iTempMY < 0) || (m_iTempMY > m_iTempH - 1))
	{
		// 提示用户参数设置错误
		MessageBox(L"中心元素参数设置错误！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		return;
	}

	// 更新模板元素数组（将有效元素放置在数组的前面）
	for (int i = 0; i < m_iTempH; i++)
		for (int j = 0; j < m_iTempW; j++)
			m_fpArray[i * m_iTempW + j] = m_fpArray[i * 5 + j];

	UpdateData(FALSE);				// 更新
	CDialog::OnOK();				// 退出
}

void CDlgSmooth::UpdateEdit()
{
	BOOL bEnable;
	int i, j;

	// 判断是不是自定义模板
	if (m_intType == 2)
		bEnable = TRUE;

	else
		bEnable = FALSE;

	// 设置文本框可用状态
	(CEdit*)GetDlgItem(IDC_EDIT_TEMPH)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_TEMPW)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_TEMPC)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_MX)->EnableWindow(bEnable);
	(CEdit*)GetDlgItem(IDC_EDIT_MY)->EnableWindow(bEnable);

	// IDC_EDIT_V0等ID其实是一个整数，它的数值定义在Resource.h中定义。

	// 设置模板元素文本框Enable状态
	for (i = IDC_EDIT_V0; i <= IDC_EDIT_V24; i++)
		(CEdit*)GetDlgItem(i)->EnableWindow(bEnable);							// 设置文本框不可编辑

	// 显示应该可见的模板元素文本框
	for (i = 0; i < m_iTempH; i++)
		for (j = 0; j < m_iTempW; j++)	
			(CEdit*)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_SHOW);	// 设置文本框可见

	// 隐藏应该不可见的模板元素文本框（前m_iTempH行的后几列）
	for (i = 0; i < m_iTempH; i++)
		for (j = m_iTempW; j < 5; j++)
			(CEdit*)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);	// 设置不可见

	// 隐藏应该不可见的模板元素文本框（后几行）
	for (i = m_iTempH; i < 5; i++)
		for (j = 0; j < 5; j++)
			(CEdit*) GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);	// 设置不可见
}

void CDlgSmooth::OnKillfocusEditTemph()
{
	UpdateData(TRUE);				// 更新
	UpdateEdit();					// 更新文本框状态
}

void CDlgSmooth::OnKillfocusEditTempw()
{
	UpdateData(TRUE);				// 更新
	UpdateEdit();					// 更新文本框状态
}