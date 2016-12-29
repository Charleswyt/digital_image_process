// DlgFreqAlphaMeanF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqAlphaMeanF.h"


// CDlgFreqAlphaMeanF 对话框

IMPLEMENT_DYNAMIC(CDlgFreqAlphaMeanF, CDialog)

CDlgFreqAlphaMeanF::CDlgFreqAlphaMeanF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqAlphaMeanF::IDD, pParent), m_iSize(3),m_iMove(1),m_iDotCount(2)
{
}

CDlgFreqAlphaMeanF::~CDlgFreqAlphaMeanF()
{
}

void CDlgFreqAlphaMeanF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iSize);
	DDV_MinMaxDouble(pDX, m_iSize, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_iMove);
	DDV_MinMaxDouble(pDX, m_iMove, 0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_iDotCount);
	DDV_MinMaxDouble(pDX, m_iDotCount, 0, 128);
}

BEGIN_MESSAGE_MAP(CDlgFreqAlphaMeanF, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
