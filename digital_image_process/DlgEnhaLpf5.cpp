// DlgEnhaLpf5.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaLpf5.h"


// CDlgEnhaLpf5 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaLpf5, CDialog)

CDlgEnhaLpf5::CDlgEnhaLpf5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaLpf5::IDD, pParent), m_iSize(3), m_iMove(1), m_iThreshold(5), m_iCnt(4)
{
}

CDlgEnhaLpf5::~CDlgEnhaLpf5()
{
}

void CDlgEnhaLpf5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_iThreshold);
	DDV_MinMaxDouble(pDX, m_iThreshold, 0, 50);
	DDX_Text(pDX, IDC_EDIT4, m_iCnt);
	DDV_MinMaxDouble(pDX, m_iCnt, 0, 256);
}

BEGIN_MESSAGE_MAP(CDlgEnhaLpf5, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaLpf5 消息处理程序
