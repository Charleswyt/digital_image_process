// DlgNoiseGamma.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgNoiseGamma.h"


// CDlgNoiseGamma 对话框

IMPLEMENT_DYNAMIC(CDlgNoiseGamma, CDialog)

CDlgNoiseGamma::CDlgNoiseGamma(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNoiseGamma::IDD, pParent), m_dA(1.0), m_dB(2.0)
{
}

CDlgNoiseGamma::~CDlgNoiseGamma()
{
}

void CDlgNoiseGamma::DoDataExchange(
	CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dA);
	DDV_MinMaxDouble(pDX, m_dA, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, m_dB);
	DDV_MinMaxDouble(pDX, m_dB, 0, 256);
}


BEGIN_MESSAGE_MAP(CDlgNoiseGamma, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
