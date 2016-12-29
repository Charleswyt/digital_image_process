// DlgEnhaHpf2.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaHpf2.h"
// CDlgEnhaLpf7 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaHpf2, CDialog)

CDlgEnhaHpf2::CDlgEnhaHpf2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaHpf2::IDD, pParent), m_iSize(3), m_iMove(1), m_dGain(1.2)
{
}

CDlgEnhaHpf2::~CDlgEnhaHpf2()
{
}

void CDlgEnhaHpf2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 6);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_dGain);
	DDV_MinMaxDouble(pDX, m_dGain, 0, 2);
}

BEGIN_MESSAGE_MAP(CDlgEnhaHpf2, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaHpf2 消息处理程序
