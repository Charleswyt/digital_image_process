#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqLadderHPF.h"

// CDlgFreqLadderHPF 对话框
IMPLEMENT_DYNAMIC(CDlgFreqLadderHPF, CDialog)

CDlgFreqLadderHPF::CDlgFreqLadderHPF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqLadderHPF::IDD, pParent)
	, m_nFreq(20), m_nF(100)
{
}

CDlgFreqLadderHPF::~CDlgFreqLadderHPF()
{
}

void CDlgFreqLadderHPF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nFreq);
	DDV_MinMaxDouble(pDX, m_nFreq, 0, 256);
	DDX_Text(pDX, IDC_EDIT2, m_nF);
	DDV_MinMaxDouble(pDX, m_nF, 0, 256);
}


BEGIN_MESSAGE_MAP(CDlgFreqLadderHPF, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussHPF 消息处理程序
