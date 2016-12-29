// DlgFreqInvHarmonicF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqInvHarmonicF.h"


// CDlgFreqInvHarmonicF 对话框

IMPLEMENT_DYNAMIC(CDlgFreqInvHarmonicF, CDialog)

CDlgFreqInvHarmonicF::CDlgFreqInvHarmonicF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqInvHarmonicF::IDD, pParent), m_iSize(3), m_iMove(1),m_iLevel(5)
{
}

CDlgFreqInvHarmonicF::~CDlgFreqInvHarmonicF()
{
}

void CDlgFreqInvHarmonicF::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_iLevel);
	DDV_MinMaxDouble(pDX, m_iLevel, 0, 100);
}

BEGIN_MESSAGE_MAP(CDlgFreqInvHarmonicF, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
