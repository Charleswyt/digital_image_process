// DlgEnhaEnhanceF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaEnhanceF.h"
// DlgEnhaEnhanceF 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaEnhanceF, CDialog)

CDlgEnhaEnhanceF::CDlgEnhaEnhanceF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaEnhanceF::IDD, pParent), m_iSize(3), m_iMove(1), m_dGain(0.2)
{
}

CDlgEnhaEnhanceF::~CDlgEnhaEnhanceF()
{
}

void CDlgEnhaEnhanceF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 6);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_dGain);
	DDV_MinMaxDouble(pDX, m_dGain, 0, 2);
}

BEGIN_MESSAGE_MAP(CDlgEnhaEnhanceF, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaEnhanceF 消息处理程序
