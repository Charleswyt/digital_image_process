#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqExpLPF.h"

// CDlgFreqExpHPF 对话框
IMPLEMENT_DYNAMIC(CDlgFreqExpLPF, CDialog)

CDlgFreqExpLPF::CDlgFreqExpLPF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqExpLPF::IDD, pParent)
	, m_nFreq(128),n(2)
{
}

CDlgFreqExpLPF::~CDlgFreqExpLPF()
{
}

void CDlgFreqExpLPF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nFreq);
	DDV_MinMaxDouble(pDX, m_nFreq, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, n);
	DDV_MinMaxDouble(pDX, n, 0, 20);
}


BEGIN_MESSAGE_MAP(CDlgFreqExpLPF, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussHPF 消息处理程序
