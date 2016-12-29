// DlgFreqButterworthHPF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqButterworthHPF.h"


// CDlgFreqButterworthHPF 对话框

IMPLEMENT_DYNAMIC(CDlgFreqButterworthHPF, CDialog)

CDlgFreqButterworthHPF::CDlgFreqButterworthHPF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqButterworthHPF::IDD, pParent)
	, m_nFreq(128), n(2)
{
}

CDlgFreqButterworthHPF::~CDlgFreqButterworthHPF()
{
}

void CDlgFreqButterworthHPF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nFreq);
	DDV_MinMaxDouble(pDX, m_nFreq, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, n);
	DDV_MinMaxDouble(pDX, n, 0, 20);
}


BEGIN_MESSAGE_MAP(CDlgFreqButterworthHPF, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
