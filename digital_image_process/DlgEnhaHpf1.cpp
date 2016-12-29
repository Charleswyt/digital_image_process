// DlgEnhaHpf1.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaHpf1.h"
// CDlgEnhaLpf7 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaHpf1, CDialog)

CDlgEnhaHpf1::CDlgEnhaHpf1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaHpf1::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaHpf1::~CDlgEnhaHpf1()
{
}

void CDlgEnhaHpf1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 6);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaHpf1, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaHpf1 消息处理程序
