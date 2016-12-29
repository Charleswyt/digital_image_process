// DlgEnhaAdapativeSmooth.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaAdapativeSmooth.h"
// DlgEnhaAdapativeMediaF 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaAdapativeSmooth, CDialog)

CDlgEnhaAdapativeSmooth::CDlgEnhaAdapativeSmooth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaAdapativeSmooth::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaAdapativeSmooth::~CDlgEnhaAdapativeSmooth()
{
}

void CDlgEnhaAdapativeSmooth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaAdapativeSmooth, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaAdapativeSmooth 消息处理程序
