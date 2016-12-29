// DlgEnhaLpf6.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaLpf6.h"
// CDlgEnhaLpf6 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaLpf6, CDialog)

CDlgEnhaLpf6::CDlgEnhaLpf6(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaLpf6::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaLpf6::~CDlgEnhaLpf6()
{
}

void CDlgEnhaLpf6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaLpf6, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaLpf6 消息处理程序
