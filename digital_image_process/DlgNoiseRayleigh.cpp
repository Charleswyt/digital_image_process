// CDlgNoiseRayleigh.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgNoiseRayleigh.h"


// CDlgFreqGaussLPF 对话框

IMPLEMENT_DYNAMIC(CDlgNoiseRayleigh, CDialog)

CDlgNoiseRayleigh::CDlgNoiseRayleigh(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNoiseRayleigh::IDD, pParent), m_dRate(0.99), m_dSigma(10.0)
{
}

CDlgNoiseRayleigh::~CDlgNoiseRayleigh()
{
}

void CDlgNoiseRayleigh::DoDataExchange(
	CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dRate);
	DDV_MinMaxDouble(pDX, m_dRate, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, m_dSigma);
	DDV_MinMaxDouble(pDX, m_dSigma, 0, 256);
}


BEGIN_MESSAGE_MAP(CDlgNoiseRayleigh, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
