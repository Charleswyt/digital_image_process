// CDlgEdgeSimpthre.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgEdgeSimpthre.h"


// CDlgFreqGaussLPF 对话框

IMPLEMENT_DYNAMIC(CDlgEdgeSimpthre, CDialog)

CDlgEdgeSimpthre::CDlgEdgeSimpthre(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEdgeSimpthre::IDD, pParent), m_iThreshold(128)
{
}

CDlgEdgeSimpthre::~CDlgEdgeSimpthre()
{
}

void CDlgEdgeSimpthre::DoDataExchange(
	CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iThreshold);
	DDV_MinMaxDouble(pDX, m_iThreshold, 0, 256);
}

BEGIN_MESSAGE_MAP(CDlgEdgeSimpthre, CDialog)
END_MESSAGE_MAP()


// CDlgFreqGaussLPF 消息处理程序
