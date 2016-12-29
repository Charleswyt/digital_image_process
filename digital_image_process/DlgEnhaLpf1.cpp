// DlgEnhaLpf1.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaLpf1.h"
// CDlgEnhaLpf1 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaLpf1, CDialog)

CDlgEnhaLpf1::CDlgEnhaLpf1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaLpf1::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaLpf1::~CDlgEnhaLpf1()
{
}

void CDlgEnhaLpf1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaLpf1, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaLpf1 消息处理程序
