// DlgFreqGaussBRF.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgFreqGaussBRF.h"


// CDlgFreqGaussBRF 对话框

IMPLEMENT_DYNAMIC ( CDlgFreqGaussBRF, CDialog )

CDlgFreqGaussBRF::CDlgFreqGaussBRF (
    CWnd* pParent /*=NULL*/ )
    : CDialog ( CDlgFreqGaussBRF::IDD, pParent )
    , m_nFreq ( 128 )
    , m_nWidth ( 64 )
{
}

CDlgFreqGaussBRF::~CDlgFreqGaussBRF()
{
}

void CDlgFreqGaussBRF::DoDataExchange (
    CDataExchange* pDX )
{
    CDialog::DoDataExchange ( pDX );
    DDX_Text ( pDX, IDC_EDIT1, m_nFreq );
    DDV_MinMaxInt ( pDX, m_nFreq, 0, 256 );
    DDX_Text ( pDX, IDC_EDIT2, m_nWidth );
    DDV_MinMaxInt ( pDX, m_nWidth, 0, 256 );
}


BEGIN_MESSAGE_MAP ( CDlgFreqGaussBRF, CDialog )
END_MESSAGE_MAP()


// CDlgFreqGaussBRF 消息处理程序
