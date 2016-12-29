// DlgRGBHist.cpp : 实现文件
//

#include "stdafx.h"
#include "DIP.h"
#include "DlgRGBHist.h"

// CDlgRGBHist 对话框

IMPLEMENT_DYNAMIC(CDlgRGBHist, CDialog)

CDlgRGBHist::CDlgRGBHist(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRGBHist::IDD, pParent)
	, m_pdHistR(NULL), m_pdHistG(NULL), m_pdHistB(NULL)
{
}

CDlgRGBHist::~CDlgRGBHist()
{
}

void CDlgRGBHist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRGBHist, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDlgRGBHist::OnPaint()
{
	CPaintDC dc(this);
	CString str;
	CWnd* pWnd = GetDlgItem(IDC_HIST);						// 获取绘制坐标的控件
	CDC* pDC = pWnd->GetDC();								// 指针
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0, 0, 320, 250);
	CPen* pPenBlack = new CPen;								// 创建画笔对象
	pPenBlack->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));		// 黑色画笔
	CPen* pPenRed = new CPen;								// 创建画笔对象
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));		// 红色画笔
	CPen* pPenBlue = new CPen;								// 创建画笔对象
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));		// 蓝色画笔
	CPen* pPenGreen = new CPen;								// 创建画笔对象
	pPenGreen->CreatePen(PS_SOLID, 1, RGB(0, 255, 0));		// 绿色画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenBlack);		// 选中当前黑色画笔，并保存以前的画笔
	
	/*************************** 混合分量 ***************************/

	pDC->MoveTo(10, 10);									// 绘制坐标轴	
	pDC->LineTo(10, 240);									// 垂直轴
	pDC->LineTo(310, 240);									// 水平轴

	// 写X轴刻度值
	str.Format(L"0");
	pDC->TextOut(10, 243, str);
	str.Format(L"50");
	pDC->TextOut(60, 243, str);
	str.Format(L"100");
	pDC->TextOut(110, 243, str);
	str.Format(L"150");
	pDC->TextOut(160, 243, str);
	str.Format(L"200");
	pDC->TextOut(210, 243, str);
	str.Format(L"255");
	pDC->TextOut(260, 243, str);

	int i;
	for (i = 0; i < 256; i += 5)							// 绘制X轴刻度
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 240);
			pDC->LineTo(i + 10, 234);
		}

		else
		{
			// 5的倍数
			pDC->MoveTo(i + 10, 240);
			pDC->LineTo(i + 10, 236);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(305, 235);
	pDC->LineTo(310, 240);
	pDC->LineTo(305, 245);
	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);
	
	double maxHistR = 0;
	double maxHistG = 0;
	double maxHistB = 0;

	for (i = 0; i < 256; i++)
	{
		maxHistR = max(maxHistR, m_pdHistR[i]);
		maxHistG = max(maxHistG, m_pdHistG[i]);
		maxHistB = max(maxHistB, m_pdHistB[i]);
	}

	pDC->SelectObject(pPenRed);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 10, 240);
		pDC->LineTo(i + 10, int(240 - m_pdHistR[i] / maxHistB * 240));
	}

	pDC->SelectObject(pPenGreen);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 10, 240);
		pDC->LineTo(i + 10, int(240 - m_pdHistG[i] / maxHistB * 240));
	}

	pDC->SelectObject(pPenBlue);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 10, 240);
		pDC->LineTo(i + 10, int(240 - m_pdHistB[i] / maxHistB * 240));
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);



	/*************************** R分量 ***************************/

	pDC->MoveTo(410, 10);									// 绘制坐标轴	
	pDC->LineTo(410, 240);									// 垂直轴
	pDC->LineTo(710, 240);									// 水平轴

	// 写X轴刻度值
	str.Format(L"0");
	pDC->TextOut(410, 243, str);
	str.Format(L"50");
	pDC->TextOut(460, 243, str);
	str.Format(L"100");
	pDC->TextOut(510, 243, str);
	str.Format(L"150");
	pDC->TextOut(560, 243, str);
	str.Format(L"200");
	pDC->TextOut(610, 243, str);
	str.Format(L"255");
	pDC->TextOut(660, 243, str);

	for (i = 0; i < 256; i += 5)							// 绘制X轴刻度
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 400, 240);
			pDC->LineTo(i + 400, 234);
		}

		else
		{
			// 5的倍数
			pDC->MoveTo(i + 400, 240);
			pDC->LineTo(i + 400, 236);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(705, 235);
	pDC->LineTo(710, 240);
	pDC->LineTo(705, 245);
	// 绘制X轴箭头
	pDC->MoveTo(410, 10);
	pDC->LineTo(405, 15);
	pDC->MoveTo(410, 10);
	pDC->LineTo(415, 15);

	for (i = 0; i < 256; i++)
		maxHistR = max(maxHistR, m_pdHistG[i]);

	pDC->SelectObject(pPenRed);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 400, 240);
		pDC->LineTo(i + 400, int(240 - m_pdHistR[i] / maxHistR * 240));
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);


	/*************************** G分量 ***************************/

	pDC->MoveTo(10, 300);									// 绘制坐标轴	
	pDC->LineTo(10, 530);									// 垂直轴
	pDC->LineTo(310, 530);									// 水平轴

															// 写X轴刻度值
	str.Format(L"0");
	pDC->TextOut(10, 533, str);
	str.Format(L"50");
	pDC->TextOut(60, 533, str);
	str.Format(L"100");
	pDC->TextOut(110, 533, str);
	str.Format(L"150");
	pDC->TextOut(160, 533, str);
	str.Format(L"200");
	pDC->TextOut(210, 533, str);
	str.Format(L"255");
	pDC->TextOut(260, 533, str);

	for (i = 0; i < 256; i += 5)							// 绘制X轴刻度
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 530);
			pDC->LineTo(i + 10, 524);
		}

		else
		{
			// 5的倍数
			pDC->MoveTo(i + 10, 530);
			pDC->LineTo(i + 10, 526);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(305, 525);
	pDC->LineTo(310, 530);
	pDC->LineTo(305, 535);
	// 绘制X轴箭头
	pDC->MoveTo(10, 300);
	pDC->LineTo(5, 305);
	pDC->MoveTo(10, 300);
	pDC->LineTo(15, 305);

	for (i = 0; i < 256; i++)
		maxHistG = max(maxHistB, m_pdHistG[i]);

	pDC->SelectObject(pPenGreen);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 10, 530);
		pDC->LineTo(i + 10, int(530 - m_pdHistG[i] / maxHistG * 240));
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	/*************************** B分量 ***************************/

	pDC->MoveTo(410, 300);									// 绘制坐标轴	
	pDC->LineTo(410, 530);									// 垂直轴
	pDC->LineTo(710, 530);									// 水平轴

	// 写X轴刻度值
	str.Format(L"0");
	pDC->TextOut(410, 533, str);
	str.Format(L"50");
	pDC->TextOut(460, 533, str);
	str.Format(L"100");
	pDC->TextOut(510, 533, str);
	str.Format(L"150");
	pDC->TextOut(560, 533, str);
	str.Format(L"200");
	pDC->TextOut(610, 533, str);
	str.Format(L"255");
	pDC->TextOut(660, 533, str);

	for (i = 0; i < 256; i += 5)							// 绘制X轴刻度
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 410, 530);
			pDC->LineTo(i + 410, 524);
		}

		else
		{
			// 5的倍数
			pDC->MoveTo(i + 410, 530);
			pDC->LineTo(i + 410, 526);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(705, 525);
	pDC->LineTo(710, 530);
	pDC->LineTo(705, 535);
	// 绘制X轴箭头
	pDC->MoveTo(410, 300);
	pDC->LineTo(405, 305);
	pDC->MoveTo(410, 300);
	pDC->LineTo(415, 305);
	

	for (i = 0; i < 256; i++)
		maxHistB = max(maxHistB, m_pdHistB[i]);

	pDC->SelectObject(pPenBlue);

	for (i = 0; i < 256; i++)
	{
		pDC->MoveTo(i + 410, 530);
		pDC->LineTo(i + 410, int(530 - m_pdHistB[i] / maxHistB * 240));
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);


	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}
