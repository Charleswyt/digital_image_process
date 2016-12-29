// DlgEnhaLpf4.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaLpf4.h"


// CDlgEnhaLpf4 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaLpf4, CDialog)

CDlgEnhaLpf4::CDlgEnhaLpf4(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaLpf4::IDD, pParent), m_iSize(3), m_iMove(1), m_iThreshold(5)
{
}

CDlgEnhaLpf4::~CDlgEnhaLpf4()
{
}

void CDlgEnhaLpf4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_iThreshold);
	DDV_MinMaxDouble(pDX, m_iThreshold, 0, 50);
}

BEGIN_MESSAGE_MAP(CDlgEnhaLpf4, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaLpf4 消息处理程序
