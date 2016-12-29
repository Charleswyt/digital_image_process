// DlgPointWin.cpp : implementation file
#include "stdafx.h"
#include "DIP.h"
#include "DlgPointWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**********************************************/
// CDlgPointWin dialog

CDlgPointWin::CDlgPointWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPointWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPointWin)
	m_bLow = 0;
	m_bUp = 0;
	//}}AFX_DATA_INIT
}

void CDlgPointWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPointWin)
	DDX_Text(pDX, IDC_EDIT_Low, m_bLow);
	DDV_MinMaxByte(pDX, m_bLow, 0, 255);
	DDX_Text(pDX, IDC_EDIT_Up, m_bUp);
	DDV_MinMaxByte(pDX, m_bUp, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgPointWin, CDialog)
	//{{AFX_MSG_MAP(CDlgPointWin)
	ON_EN_KILLFOCUS(IDC_EDIT_Low, OnKillfocusEDITLow)
	ON_EN_KILLFOCUS(IDC_EDIT_Up, OnKillfocusEDITUp)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**********************************************/
// CDlgPointWin message handlers

BOOL CDlgPointWin::OnInitDialog()
{
	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();
	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);
	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	m_iIsDraging = 0;											// 初始化拖动状态
	return TRUE;
}

void CDlgPointWin::OnKillfocusEDITLow()
{
	UpdateData(TRUE);											// 更新
	if (m_bLow > m_bUp)											// 判断是否下限超过上限
	{
		// 互换
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;
		
		UpdateData(FALSE);										// 更新
	}

	InvalidateRect(m_MouseRect, TRUE);							// 重绘
}

void CDlgPointWin::OnKillfocusEDITUp()
{
	
	UpdateData(TRUE);											// 更新
	if (m_bLow > m_bUp)											// 判断是否下限超过上限
	{
		// 互换
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;
		
		UpdateData(FALSE);										// 更新
	}

	InvalidateRect(m_MouseRect, TRUE);							// 重绘
}

void CDlgPointWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_MouseRect.PtInRect(point))							// 当用户单击鼠标左键开始拖动
	{
		if (point.x == (m_MouseRect.left + m_bLow))
		{
			m_iIsDraging = 1;									// 设置拖动状态1，拖动下限
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));		// 更改光标
		}

		else
			if (point.x == (m_MouseRect.left + m_bUp))
			{
				m_iIsDraging = 2;								// 设置拖动状态为2，拖动上限
				::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));	// 更改光标
			}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPointWin::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_MouseRect.PtInRect(point))							// 判断当前光标是否在绘制区域
	{
		if (m_iIsDraging != 0)									// 判断是否正在拖动
		{
			if (m_iIsDraging == 1)								// 判断正在拖动上限还是下限
			{
				if (point.x - m_MouseRect.left < m_bUp)			// 判断是否下限<上限
					m_bLow = (BYTE)(point.x - m_MouseRect.left);// 更改下限

				else
				{
					m_bLow = m_bUp - 1;							// 下限拖过上限，设置为上限-1
					point.x = m_MouseRect.left + m_bUp - 1;		// 重设鼠标位置
				}
			}

			else
			{
				// 正在拖动上限
				if (point.x - m_MouseRect.left > m_bLow)		// 判断是否上限>下限					
					m_bUp = (BYTE)(point.x - m_MouseRect.left);	// 更改下限

				else
				{
					m_bUp = m_bLow + 1;							// 下限拖过上限，设置为下限＋1
					point.x = m_MouseRect.left + m_bLow + 1;	// 重设鼠标位置
				}
			}
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));		// 更改光标
			UpdateData(FALSE);									// 更新
			InvalidateRect(m_MouseRect, TRUE);					// 更新
		}

		else
			if (point.x == (m_MouseRect.left + m_bLow) || point.x == (m_MouseRect.left + m_bUp))
				::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));	// 更改光标
	}

	CDialog::OnMouseMove(nFlags, point);						// 默认鼠标移动处理事件
}

void CDlgPointWin::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_iIsDraging != 0)										// 当用户释放鼠标左键停止拖动
		m_iIsDraging = 0;										// 重置拖动状态

	CDialog::OnLButtonUp(nFlags, point);						// 默认释放鼠标左键处理事件
}

void CDlgPointWin::OnPaint()
{
	CString str;												// 字符串
	CPaintDC dc(this);											// 设备上下文
	CWnd* pWnd = GetDlgItem(IDC_COORD);							// 获取绘制坐标的文本框
	CDC* pDC = pWnd->GetDC();									// 指针
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0, 0, 330, 300);
	CPen* pPenRed = new CPen;									// 创建画笔对象
	pPenRed->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));				// 红色画笔
	CPen* pPenBlue = new CPen;// 创建画笔对象
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));				// 蓝色画笔
	CPen* pPenGreen = new CPen;									// 创建画笔对象
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));				// 绿色画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);			// 选中当前红色画笔，并保存以前的画笔
	pDC->MoveTo(10, 10);										// 绘制坐标轴
	pDC->LineTo(10, 280);										// 垂直轴
	pDC->LineTo(320, 280);										// 水平轴
	str.Format(L"0");											// 写坐标
	pDC->TextOut(10, 281, str);
	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	pDC->LineTo(315, 275);										// 绘制X轴箭头
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	pDC->MoveTo(10, 10);										// 绘制X轴箭头
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);
	pDC->SelectObject(pPenGreen);								// 更改成绿色画笔
	pDC->MoveTo(m_bLow + 10, 25);								// 绘制窗口上下限
	pDC->LineTo(m_bLow + 10, 280);
	pDC->MoveTo(m_bUp + 10, 25);
	pDC->LineTo(m_bUp + 10, 280);
	pDC->SelectObject(pPenBlue);								// 更改成蓝色画笔
	str.Format(L"(%d, %d)", m_bLow, m_bLow);					// 绘制坐标值
	pDC->TextOut(m_bLow + 10, 281 - m_bLow, str);
	str.Format(L"(%d, %d)", m_bUp, m_bUp);
	pDC->TextOut(m_bUp + 10, 281 - m_bUp, str);
	pDC->MoveTo(10, 280);										// 绘制用户指定的窗口（注意转换坐标系）
	pDC->LineTo(m_bLow + 10, 280);
	pDC->LineTo(m_bLow + 10, 280 - m_bLow);
	pDC->LineTo(m_bUp + 10, 280 - m_bUp);
	pDC->LineTo(m_bUp + 10, 25);
	pDC->LineTo(265, 25);
	pDC->SelectObject(pOldPen);									// 恢复以前的画笔
	pDC->MoveTo(10, 25);										// 绘制边缘
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	delete pPenRed;												// 删除新的画笔
	delete pPenBlue;
	delete pPenGreen;
}

void CDlgPointWin::OnOK()
{
	// 判断是否下限超过上限
	if (m_bLow > m_bUp)											// 互换
	{
		BYTE bTemp = m_bLow;
		m_bLow = m_bUp;
		m_bUp = bTemp;
	}
	CDialog::OnOK();											// 默认处理事件
}

