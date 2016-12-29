// DlgEnhaLpf2.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaLpf2.h"
// CDlgEnhaLpf7 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaLpf2, CDialog)

CDlgEnhaLpf2::CDlgEnhaLpf2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaLpf2::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaLpf2::~CDlgEnhaLpf2()
{
}

void CDlgEnhaLpf2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 6);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaLpf2, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaLpf2 消息处理程序
