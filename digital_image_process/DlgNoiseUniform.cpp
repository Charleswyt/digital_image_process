// CDlgNoiseUniform.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgNoiseUniform.h"


// CDlgNoiseUniform 对话框

IMPLEMENT_DYNAMIC(CDlgNoiseUniform, CDialog)

CDlgNoiseUniform::CDlgNoiseUniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNoiseUniform::IDD, pParent), m_dLow(-20.0), m_dHigh(20.0)
{

}

CDlgNoiseUniform::~CDlgNoiseUniform()
{

}

void CDlgNoiseUniform::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dLow);
	DDV_MinMaxDouble(pDX, m_dLow, -256, 0);
	DDX_Text(pDX, IDC_EDIT2, m_dHigh);
	DDV_MinMaxDouble(pDX, m_dHigh, 0, 256);
}

BEGIN_MESSAGE_MAP(CDlgNoiseUniform, CDialog)
END_MESSAGE_MAP()

// CDlgFreqGaussLPF 消息处理程序