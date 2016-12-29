// DlgEnhaGaussionF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEnhaGaussianF.h"
// DlgEnhaGaussionF 对话框

IMPLEMENT_DYNAMIC(CDlgEnhaGaussianF, CDialog)

CDlgEnhaGaussianF::CDlgEnhaGaussianF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnhaGaussianF::IDD, pParent), m_iSize(3), m_iMove(1)
{
}

CDlgEnhaGaussianF::~CDlgEnhaGaussianF()
{
}

void CDlgEnhaGaussianF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 6);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
}

BEGIN_MESSAGE_MAP(CDlgEnhaGaussianF, CDialog)
END_MESSAGE_MAP()


// CDlgEnhaHpf1 消息处理程序
