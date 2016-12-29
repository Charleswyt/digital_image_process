// CDlgNoiseGauss.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgNoiseGauss.h"


// CDlgFreqGaussLPF 对话框

IMPLEMENT_DYNAMIC(CDlgNoiseGauss, CDialog)

CDlgNoiseGauss::CDlgNoiseGauss(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNoiseGauss::IDD, pParent), m_dRate(0.99), m_dSigma(10.0)
{
}

CDlgNoiseGauss::~CDlgNoiseGauss()
{
}

void CDlgNoiseGauss::DoDataExchange(
	CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dRate);
	DDV_MinMaxDouble(pDX, m_dRate, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, m_dSigma);
	DDV_MinMaxDouble(pDX, m_dSigma, 0, 256);
}


BEGIN_MESSAGE_MAP(CDlgNoiseGauss, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
