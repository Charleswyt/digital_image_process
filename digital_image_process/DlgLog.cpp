#include "stdafx.h"
#include "DIP.h"
#include "DlgLog.h"

// CDlgLog ¶Ô»°¿ò

IMPLEMENT_DYNAMIC ( CDlgLog, CDialog )

CDlgLog::CDlgLog ( CWnd* pParent /*=NULL*/ ) : CDialog ( CDlgLog::IDD, pParent ), m_dC ( 0 )
{

}

CDlgLog::~CDlgLog()
{

}

void CDlgLog::DoDataExchange ( CDataExchange* pDX )
{
    CDialog::DoDataExchange ( pDX );
    DDX_Text ( pDX, IDC_EDIT1, m_dC );
    DDV_MinMaxDouble ( pDX, m_dC, 0, 255 );
}

BEGIN_MESSAGE_MAP ( CDlgLog, CDialog )
END_MESSAGE_MAP()
