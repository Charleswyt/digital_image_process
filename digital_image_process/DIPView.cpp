#include "stdafx.h"
#include "DIP.h"

#include "DIPDoc.h"
#include "DIPView.h"
#include "mainfrm.h"

#include "DlgFileInfoShow.h"
#include "DlgLinerPara.h"
#include "DlgPointThre.h"
#include "DlgPointWin.h"
#include "DlgPointThre.h"
#include "DlgGeoTran.h"
#include "DlgGeoZoom.h"
#include "DlgGeoZoom2.h"
#include "DlgGeoRota.h"
#include "DlgProjRestore.h"
#include "DlgSmooth.h"
#include "DlgMidFilter.h"
#include "DlgSharpThre.h"
#include "DlgColor.h"

#include "DlgHist.h"
#include "DlgLinTrans.h"
#include "DlgLog.h"
#include "DlgGamma.h"
#include "DlgWndTran.h"
#include "DlgGrayScaling.h"
#include "DlgFreqGaussBRF.h"
#include "DlgFreqGaussHPF.h"
#include "DlgFreqGaussLPF.h"
#include "DlgFreqHighGain.h"
#include "DlgFreqIdealLPF.h"
#include "DlgEdgeSobelPrewitt.h"
#include "DlgHough.h"
#include "DlgNoiseGauss.h"
#include "DlgNoiseSaltPepper.h"
#include "DlgNoiseGamma.h"
#include "DlgNOiseExp.h"
#include "DlgNoiseUniform.h"
#include "DlgNoiseRayleigh.h"
#include "DlgEdgeSimpthre.h"
#include "DlgFreqButterworthLPF.h"
#include "DlgFreqButterworthHPF.h"
#include "DlgFreqExpLPF.h"
#include "DlgFreqExpHPF.h"
#include "DlgFreqInvHarmonicF.h"
#include "DlgFreqAlphaMeanF.h"
#include "DlgEnhaLpf1.h"
#include "DlgEnhaLpf2.h"
#include "DlgEnhaLpf3.h"
#include "DlgEnhaLpf4.h"
#include "DlgEnhaLpf5.h"
#include "DlgEnhaLpf6.h"
#include "DlgEnhaLpf7.h"
#include "DlgEnhaHpf1.h"
#include "DlgEnhaHpf2.h"
#include "DlgEnhaMediaF.h"
#include "DlgEnhaMinF.h"
#include "DlgEnhaMaxF.h"
#include "DlgEnhaMidF.h"
#include "DlgEnhaAdapativeMediaF.h"
#include "DlgEnhaEnhanceF.h"
#include "DlgEnhaAdapativeSmooth.h"
#include "DlgEnhaGaussianF.h"
#include "DlgRGBHist.h"
#include "DlgFreqLadderLpf.h"
#include "DlgFreqLadderHpf.h"

#include "DlgMorph.h"
#include "DlgMorphErosion.h"
#include "DlgMorphDilation.h"
#include "DlgMorphOpen.h"
#include "DlgMorphClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**********************************************/
// CDIPView

IMPLEMENT_DYNCREATE(CDIPView, CScrollView)

BEGIN_MESSAGE_MAP(CDIPView, CScrollView)
	//{{AFX_MSG_MAP(CDIPView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_GEOM_TRAN, OnGeomTran)
	ON_COMMAND(ID_GEOM_MIRV, OnGeomMirv)
	ON_COMMAND(ID_GEOM_MIRH, OnGeomMirh)
	ON_COMMAND(ID_GEOM_ROTA, OnGeomRota)
	ON_COMMAND(ID_GEOM_TRPO, OnGeomTrpo)
	ON_COMMAND(ID_GEOM_ZOOM1, OnGeomZoom1)
	ON_COMMAND(ID_GEOM_ZOOM2, OnGeomZoom2)
	ON_COMMAND(ID_POINT_EQUA, OnPointEqua)
	ON_COMMAND(ID_POINT_LINER, OnPointLiner)
	ON_COMMAND(ID_POINT_WIND, OnPointWind)
	ON_COMMAND(ID_VIEW_INTENSITY, OnViewIntensity)
	ON_COMMAND(ID_VIEW_RGB_HIST, OnViewRGBIntensity)
	ON_COMMAND(ID_BITLAYER_I, OnGetBitLayerI)
	ON_COMMAND(ID_BITLAYER_II, OnGetBitLayerII)
	ON_COMMAND(ID_BITLAYER_III, OnGetBitLayerIII)
	ON_COMMAND(ID_BITLAYER_IV, OnGetBitLayerIV)
	ON_COMMAND(ID_BITLAYER_V, OnGetBitLayerV)
	ON_COMMAND(ID_BITLAYER_VI, OnGetBitLayerVI)
	ON_COMMAND(ID_BITLAYER_VII, OnGetBitLayerVII)
	ON_COMMAND(ID_BITLAYER_VIII, OnGetBitLayerVIII)
	ON_COMMAND(ID_FREQ_FOUR, OnFreqFour)
	ON_COMMAND(ID_FREQ_IFOUR, OnFreqIFour)
	ON_COMMAND(ID_FREQ_DCT, OnFreqDct)
	ON_COMMAND(ID_FREQ_IDCT, OnFreqIdct)
	ON_COMMAND(ID_POINT_THRE, OnPointThre)
	ON_COMMAND(ID_ENHA_SMOOTH, OnEnhaSmooth)
	ON_COMMAND(ID_ENHA_MidianF, OnEnhaMidianF)
	ON_COMMAND(ID_ENHA_MINF, OnEnhaMinF)
	ON_COMMAND(ID_ENHA_MAXF, OnEnhaMaxF)
	
	ON_COMMAND(ID_ENHA_LPF1, OnEnhaLPF1)
	ON_COMMAND(ID_ENHA_LPF2, OnEnhaLPF2)
	ON_COMMAND(ID_ENHA_LPF3, OnEnhaLPF3)
	ON_COMMAND(ID_ENHA_LPF4, OnEnhaLPF4)
	ON_COMMAND(ID_ENHA_LPF5, OnEnhaLPF5)
	ON_COMMAND(ID_ENHA_LPF6, OnEnhaLPF6)
	ON_COMMAND(ID_ENHA_LPF7, OnEnhaLPF7)
	ON_COMMAND(ID_ENHA_LPF8, OnEnhaLPF8)
	ON_COMMAND(ID_ENHA_LPF9, OnEnhaLPF9)
	ON_COMMAND(ID_ENHA_MIDF, OnEnhaMidF)

	ON_COMMAND(ID_ENHA_HPF1, OnEnhaHPF1)
	ON_COMMAND(ID_ENHA_HPF2, OnEnhaHPF2)
	ON_COMMAND(ID_ENHA_AdaptMidianF, OnENHAAdaptMidianF)
	ON_COMMAND(ID_ENHA_HIGHENHA, OnEnhaHighenha)
	ON_COMMAND(ID_ENHA_GAUSSIANF, OnEnhaGaussianF)
	ON_COMMAND(ID_ENHA_ADAPATIVE_SMOOTH, OnEnhaAdapativeSmooth)

	ON_COMMAND(ID_PIC_ADD, OnPicAdd)
	ON_COMMAND(ID_PIC_SUB, OnPicSub)
	ON_COMMAND(ID_PIC_MUL, OnPicMul)
	
	ON_COMMAND(ID_ENHA_GRADSHARP, OnEnhaGradsharp)
	ON_COMMAND(ID_MORPH_EROSION, OnMorphErosion)
	ON_COMMAND(ID_MORPH_DILATION, OnMorphDilation)
	ON_COMMAND(ID_MORPH_OPEN, OnMorphOpen)
	ON_COMMAND(ID_MORPH_CLOSE, OnMorphClose)
	ON_COMMAND(ID_MORPH_THINING, OnMorphThining)
	ON_COMMAND(ID_GEOM_CALI, OnGeomCali)
	ON_COMMAND(ID_FILE_CLEAN, OnFileClean)
	ON_COMMAND(ID_FILE_SHOWINFO, OnFileInfoShow)
	ON_COMMAND(ID_COLOR_RGB2GRAY_MAX, OnColorRGB2GrayMax)
	ON_COMMAND(ID_COLOR_RGB2GRAY_EVEN, OnColorRGB2GrayEven)
	ON_COMMAND(ID_COLOR_RGB2GRAY_WEIGHT, OnColorRGB2GrayWeight)
	ON_COMMAND(ID_COLOR_GRAY2RGB_PSEUDO, OnColorGray2RGBPseudo)
	ON_COMMAND(ID_COLOR_GRAY2RGB_RAINBOW, OnColorGray2RGBRainbow)
	ON_COMMAND(ID_COLOR_RGBLEVEL_R, OnColorGetRLevel)
	ON_COMMAND(ID_COLOR_RGBLEVEL_G, OnColorGetGLevel)
	ON_COMMAND(ID_COLOR_RGBLEVEL_B, OnColorGetBLevel)
	ON_COMMAND(ID_COLOR_RGB2CMY, OnColorRGB2CMY)
	ON_COMMAND(ID_COLOR_CMY2RGB, OnColorCMY2RGB)
	ON_COMMAND(ID_COLOR_RGB2HSI, OnColorRGB2HSI)
	ON_COMMAND(ID_COLOR_HSI2RGB, OnColorHSI2RGB)
	ON_COMMAND(ID_COLOR_RGB2HSV, OnColorRGB2HSV)
	ON_COMMAND(ID_COLOR_HSV2RGB, OnColorHSV2RGB)
	ON_COMMAND(ID_COLOR_RGB2YUV, OnColorRGB2YUV)
	ON_COMMAND(ID_COLOR_YUV2RGB, OnColorYUV2RGB)
	ON_COMMAND(ID_COLOR_RGB2YIQ, OnColorRGB2YIQ)
	ON_COMMAND(ID_COLOR_YIQ2RGB, OnColorYIQ2RGB)
	
	ON_COMMAND(ID_REC_TEMPLATE, OnRecTemplate)
	ON_COMMAND(ID_FEA_GRAYMAT, OnFeaGraymat)
	ON_COMMAND(ID_MORPH_TRACE, OnMorphTrace)
	ON_COMMAND(ID_FILE_REVERSE, OnFileReverse)
	ON_COMMAND(ID_MORPH_FILLRGN, OnMorphFillrgn)
	ON_COMMAND(ID_MORPH_LABELCONNRGN, OnMorphLabelconnrgn)
	ON_COMMAND(ID_MORPH_PIXEL, OnMorphPixel)
	ON_COMMAND(ID_MORPH_CONVEX, OnMorphConvex)
	ON_COMMAND(ID_MORPH_GRAYDILATE, OnMorphGraydilate)
	ON_COMMAND(ID_MORPH_GRAYERODE, OnMorphGrayerode)
	ON_COMMAND(ID_MORPH_GRAYOPEN, OnMorphGrayopen)
	ON_COMMAND(ID_MORPH_GRAYCLOSE, OnMorphGrayclose)
	ON_COMMAND(ID_MORPH_TOPHAT, OnMorphTophat)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_POINT_STDLIN, CDIPView::OnPointStdlin)
	ON_COMMAND(ID_POINT_LOG, CDIPView::OnPointLog)
	ON_COMMAND(ID_POINT_GAMMA, CDIPView::OnPointGamma)
	ON_COMMAND(ID_POINT_HISTST, CDIPView::OnPointHistst)
	ON_COMMAND(ID_FILE_ROTATE, CDIPView::OnFileRotate)
	ON_COMMAND(ID_EDGE_ROBERT, CDIPView::OnEdgeRobert)
	ON_COMMAND(ID_EDGE_SOBEL, CDIPView::OnEdgeSobel)
	ON_COMMAND(ID_EDGE_PREWITT, CDIPView::OnEdgePrewitt)
	ON_COMMAND(ID_EDGE_LOG, CDIPView::OnEdgeLog)
	ON_COMMAND(ID_EDGE_SIMPTHRE, CDIPView::OnEdgeSimpthre)
	ON_COMMAND(ID_EDGE_AUTOTHRE, CDIPView::OnEdgeAutothre)
	ON_COMMAND(ID_NOISE_GAUSS, CDIPView::OnAddGaussian)
	ON_COMMAND(ID_NOISE_SALTPEPPER, CDIPView::OnAddSalt)
	ON_COMMAND(ID_NOISE_RAYLEIGH, CDIPView::OnAddRayleigh)
	ON_COMMAND(ID_NOISE_GAMMA, CDIPView::OnAddGamma)
	ON_COMMAND(ID_NOISE_EXP, CDIPView::OnAddExp)
	ON_COMMAND(ID_NOISE_UNIFORM, CDIPView::OnAddUniform)
	ON_COMMAND(ID_FREQ_IDEALLPF, CDIPView::OnFreqIdeallpf)
	ON_COMMAND(ID_FREQ_IDEALHPF, CDIPView::OnFreqIdealhpf)
	ON_COMMAND(ID_FREQ_BUTTERWORTHLPF, CDIPView::OnFreqButterworthlpf)
	ON_COMMAND(ID_FREQ_BUTTERWORTHHPF, CDIPView::OnFreqButterworthhpf)
	ON_COMMAND(ID_FREQ_GAUSSLPF, CDIPView::OnFreqGausslpf)
	ON_COMMAND(ID_FREQ_GAUSSHPF, CDIPView::OnFreqGausshpf)
	ON_COMMAND(ID_FREQ_EXPLPF, CDIPView::OnFreqExplpf)
	ON_COMMAND(ID_FREQ_EXPHPF, CDIPView::OnFreqExphpf)
	ON_COMMAND(ID_FREQ_LADDER_LPF, CDIPView::OnFreqLadderlpf)
	ON_COMMAND(ID_FREQ_LADDER_HPF, CDIPView::OnFreqLadderhpf)
	ON_COMMAND(ID_FREQ_LAPL, CDIPView::OnFreqLapl)
	ON_COMMAND(ID_FREQ_GAUSSBR, CDIPView::OnFreqGaussbr)
	ON_COMMAND(ID_EDGE_CANNY, CDIPView::OnEdgeCanny)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDGE_REGION_GROW, CDIPView::OnEdgeRegionGrow)
	ON_COMMAND(ID_EDGE_HOUGH, CDIPView::OnEdgeHough)
	ON_COMMAND(ID_FILE_CONVERTGRAY, CDIPView::OnFileConvertgray)
	ON_COMMAND(ID_MATCHING_RGB_HIST, CDIPView::OnMatchingRGBHist)

END_MESSAGE_MAP()

/**********************************************/
// CDIPView construction/destruction

CDIPView::CDIPView() : m_bLBtnDblClkSrv(0)
{

}

CDIPView::~CDIPView()
{

}

BOOL CDIPView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/**********************************************/
// CDIPView drawing

void CDIPView::OnDraw(CDC* pDC)
{
	BeginWaitCursor();								// 显示等待光标
	CDIPDoc* pDoc = GetDocument();					// 获取文档
	ASSERT_VALID(pDoc);

	if (pDoc->m_Image.IsValidate())
	{
		CPalette* pOldPalette;
		CPalette* pPalette = pDoc->GetDocPalette();

		if (pPalette != NULL)
		{
			pOldPalette = pDC->SelectPalette(pPalette, FALSE);
			pDC->RealizePalette();					//更新系统调色板
		}
		pDoc->m_Image.Draw(pDC);					//绘制图像

		if (pPalette != NULL)
			pDC->SelectPalette(pOldPalette, FALSE);
	}
	EndWaitCursor();								// 恢复正常光标
}

void CDIPView::OnDraw2(CDC* pDC)
{
	BeginWaitCursor();								// 显示等待光标
	CDIPDoc* pDoc = GetDocument();					// 获取文档
	ASSERT_VALID(pDoc);

	if (pDoc->m_Image.IsValidate())
		pDoc->m_Image.Draw2(pDC);					//绘制图像

	EndWaitCursor();								// 恢复正常光标
}

BOOL CDIPView::OnPreparePrinting( CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);							// 设置总页数为一
	return DoPreparePrinting(pInfo);
}

void CDIPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CDIPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

#ifdef _DEBUG
void CDIPView::AssertValid() const
{
	CView::AssertValid();
}

void CDIPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIPDoc* CDIPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIPDoc)));
	return (CDIPDoc*)m_pDocument;
}
#endif //_DEBUG

/**********************************************/
// CDIPView message handlers

BOOL CDIPView::OnEraseBkgnd(CDC* pDC)
{
	// 主要是为了设置子窗体默认的背景色
	// 背景色由文档成员变量m_refColorBKG指定
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CBrush brush(pDoc->m_refColorBKG);		// 创建一个Brush
	CBrush* pOldBrush = pDC->SelectObject(&brush);	// 保存以前的Brush
	CRect rectClip;							// 获取重绘区域
	pDC->GetClipBox(&rectClip);				// 重绘
	pDC->PatBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);			// 恢复以前的Brush
	return TRUE;
}

void CDIPView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CDIPView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
	CScrollView::OnInitialUpdate();
	ASSERT(GetDocument() != NULL);
	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());
}

void CDIPView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		ASSERT(pActivateView == this);
		Invalidate();						// 激活该视图时进行重绘
	}
}

void CDIPView::OnViewIntensity()
{
	// 查看当前图像灰度直方图
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	double hist[256];						// 直方图数组
	BeginWaitCursor();						// 设置忙状态
	imgInput.GenHist(hist);					// 求取直方图数组
	CDlgHist dlg;
	dlg.m_pdHist = hist;

	if (dlg.DoModal() != IDOK)
		return;								// 返回

	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnViewRGBIntensity()
{
	// 查看当前图像灰度直方图
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 24)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是24-bpp图像，无法处理！");
		return;
	}

	// 直方图数组
	double histR[256];
	double histG[256];
	double histB[256];
	
	BeginWaitCursor();						// 设置忙状态
	imgInput.GenRGBHist(histR, 1);			// 求R分量分布直方图
	imgInput.GenRGBHist(histG, 2);			// 求G分量分布直方图
	imgInput.GenRGBHist(histB, 3);			// 求B分量分布直方图

	CDlgRGBHist dlg;
	dlg.m_pdHistR = histR;
	dlg.m_pdHistG = histG;
	dlg.m_pdHistB = histB;

	if (dlg.DoModal() != IDOK)
		return;								// 返回

	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnMatchingRGBHist()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	CImgProcess* pStdImage = new CImgProcess();	// 标准图像

	// 通过打开对话框获取标准图像
	CString filePath;							// 文件路径
	CFileDialog openDlg(TRUE, 0, 0, 4 | 2,
		L"Bitmap Files (*.bmp)||");				// 打开文件对话框，如果用户点击取消则返回
	if (openDlg.DoModal() == IDOK)
		filePath = openDlg.GetPathName();
	else
		return;

	double* dResult1 = new double[9];
	double* dResult2 = new double[9];
	double dResult = 0;
	pStdImage->AttachFromFile(filePath);		// 获取标准图像

	dResult1 = imgInput.StatisticRGBMoment(&imgInput);		// 获取图像1的颜色矩计算结果
	dResult2 = pStdImage->StatisticRGBMoment(pStdImage);	// 获取图像1的颜色矩计算结果

	for (int i = 0; i < 9; i++)
		dResult += abs(dResult2[i] - dResult1[i]);
	
	if(dResult == 0.0)
		AfxMessageBox(L"完全一样！");

	else if (dResult != 0 && dResult <= 200.0)
		AfxMessageBox(L"十分相似！");

	else if (dResult > 200.0 && dResult <= 400.0)
		AfxMessageBox(L"较为相似！");

	else
		AfxMessageBox(L"不相似！");

	pDoc->m_Image = *pStdImage;					// 将结果返回给文档类
	delete pStdImage;
	delete[] dResult1;
	delete[] dResult2;
}

void CDIPView::OnGetBitLayerI()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput,1);		// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerII()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 2);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerIII()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 3);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerIV()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 4);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerV()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 5);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerVI()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 6);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerVII()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 7);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGetBitLayerVIII()
{
	// 获取位面I
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GetBitLayer(&imgOutput, 8);	// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnPointLiner()
{
	// 线性变换
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	// 检查图像是灰度图
	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgLinerPara dlgPara;					// 创建对话框
	double fA;								// 线性变换的斜率
	double fB;								// 线性变换的截距
	dlgPara.m_fA = 1.0;						// 初始化变量值
	dlgPara.m_fB = 0.0;
	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定参数
		return;								// 返回
	fA = dlgPara.m_fA;						// 获取用户设定的参数
	fB = dlgPara.m_fB;
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.LinTran(&imgOutput, fA, fB);	// 调用LinTran()函数进行线性变换
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnPointThre()
{
	// 阈值变换
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	BYTE bThre;								// 阈值
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	// 检查图像是灰度图
	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgPointThre dlgPara;					// 参数对话框

	// 显示对话框，提示用户设定阈值
	if (dlgPara.DoModal() != IDOK)
		return;								// 返回

	//bThre = dlgPara.m_bThre;				// 获取用户设定的阈值
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Threshold(&imgOutput, 
		dlgPara.m_bThre);					// 调用Threshold方法进行阈值变换
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnPointWind()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	// 检查图像是灰度图
	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	double dpHist[256];						// 直方图数组
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.GenHist(dpHist);				// 求取直方图数组
	CDlgWndTran dlg;						// 创建参数输入对话框
	dlg.m_bLower = 0;
	dlg.m_bUpper = 255;
	dlg.m_dHist = dpHist;

	if (dlg.DoModal() != IDOK)
		return;

	// 窗口变换
	imgInput.WindowTran(&imgOutput, dlg.m_bLower, dlg.m_bUpper);
	// 将结果返回给文档类
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPointEqua()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	// 检查图像是灰度图
	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Histeq(&imgOutput);			// 直方图均衡化
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnGeomTran()
{
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	LONG lXOffset;
	LONG lYOffset;
	CDlgGeoTran dlgPara;					// 创建对话框
	dlgPara.m_XOffset = 100;				// 初始化变量值
	dlgPara.m_YOffset = 100;

	// 显示对话框，提示用户设定参数
	if (dlgPara.DoModal() != IDOK)
		return;// 返回

	lXOffset = dlgPara.m_XOffset;			// 获取用户设定的参数
	lYOffset = dlgPara.m_YOffset;
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.ImMove(&imgOutput,
		lXOffset, lYOffset);				// 调用ImMove()函数实现图像平移
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomMirv()
{
	// 竖直镜像
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.VerMirror(&imgOutput);			// 调用VerMirror()函数实现图像竖直镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomMirh()
{
	// 水平镜像
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.HorMirror(&imgOutput);			// 调用HorMirror()函数实现图像水平镜像
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomTrpo()
{
	// 图像转置
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Transpose(&imgOutput);			// 调用Transpose()函数实现图像转置
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomZoom1()
{
	// 图像缩放
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	
	double fZoomRatio;						// 缩放比率
	CDlgGeoZoom dlgPara;					// 创建对话框

	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定参数
		return;// 返回

	fZoomRatio = dlgPara.m_Zoom;			// 获取用户设定的参数
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Scale1(&imgOutput, fZoomRatio);// 调用Scale()函数实现图像缩放
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomZoom2()
{
	// 图像缩放
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	double dZoomRatioX, dZoomRatioY;		// 缩放比率
	CDlgGeoZoom2 dlgPara;					// 创建对话框

	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定参数
		return;// 返回

	dZoomRatioX = dlgPara.m_ZoomX;			// 获取用户设定的参数
	dZoomRatioY = dlgPara.m_ZoomY;			// 获取用户设定的参数
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Scale2(&imgOutput, 
		dZoomRatioX, dZoomRatioY);			// 调用Scale()函数实现图像缩放
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomRota()
{
	// 图像旋转
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	
	int iRotateAngle;						// 旋转角度
	CDlgGeoRota dlgPara;					// 创建对话框
	dlgPara.m_iRotateAngle = 30;			// 初始化变量值
	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定旋转角度
		return;// 返回

	iRotateAngle = dlgPara.m_iRotateAngle;	// 获取用户设定的参数
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.Rotate(&imgOutput,
		(double)iRotateAngle);				// 调用Rotate()函数实现图像旋转
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 将结果返回给文档类
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnGeomCali()
{
	// 投影校正
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	CPoint pBasePts[4];						// 基准图像基准点数组
	CPoint pSrcPts[4];						// 输入图像基准点数组
	CDlgProjRestore dlgPara;				// 创建对话框
	// 初始化输入图像基准点
	dlgPara.m_xPt1 = 108;
	dlgPara.m_yPt1 = 135;
	dlgPara.m_xPt2 = 274;
	dlgPara.m_yPt2 = 51;
	dlgPara.m_xPt3 = 295;
	dlgPara.m_yPt3 = 119;
	dlgPara.m_xPt4 = 158;
	dlgPara.m_yPt4 = 248;
	// 初始化基准图像基准点
	dlgPara.m_xBPt1 = 0;
	dlgPara.m_yBPt1 = 0;
	dlgPara.m_xBPt2 = 310;
	dlgPara.m_yBPt2 = 0;
	dlgPara.m_xBPt3 = 310;
	dlgPara.m_yBPt3 = 100;
	dlgPara.m_xBPt4 = 0;
	dlgPara.m_yBPt4 = 100;

	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定参数
		return;								// 返回

	// 获取用户设定的参数
	pBasePts[0] = CPoint(dlgPara.m_xBPt1, dlgPara.m_yBPt1);
	pBasePts[1] = CPoint(dlgPara.m_xBPt2, dlgPara.m_yBPt2);
	pBasePts[2] = CPoint(dlgPara.m_xBPt3, dlgPara.m_yBPt3);
	pBasePts[3] = CPoint(dlgPara.m_xBPt4, dlgPara.m_yBPt4);
	pSrcPts[0]  = CPoint(dlgPara.m_xPt1, dlgPara.m_yPt1);
	pSrcPts[1]  = CPoint(dlgPara.m_xPt2, dlgPara.m_yPt2);
	pSrcPts[2]  = CPoint(dlgPara.m_xPt3, dlgPara.m_yPt3);
	pSrcPts[3]  = CPoint(dlgPara.m_xPt4, dlgPara.m_yPt4);
	BeginWaitCursor();						// 更改光标形状
	imgInput.ImProjRestore(&imgOutput, pBasePts,
		pSrcPts, 1);						// 使用双线性插值的投影校正
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类		
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识	
	pDoc->UpdateAllViews(NULL);				// 更新视图	
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnAddGaussian()				// 高斯噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseGauss dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;
	imgInput.AddGaussian(&imgOutput, dlg.m_dRate, dlg.m_dSigma);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnAddSalt()					// 椒盐噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseSaltPepper dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if(dlg.m_dRate >= 0.5)
	{
		AfxMessageBox(L"不建议强度超过0.5，请重新设置！");
		return;
	}
	CImgProcess imgOutput = imgInput;
	imgInput.AddSalt_Pepper(&imgOutput, dlg.m_dRate);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnAddRayleigh()				// 瑞利噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseRayleigh dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;
	imgInput.AddRayleigh(&imgOutput,dlg.m_dRate,dlg.m_dSigma);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnAddGamma()					// 伽马噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseGamma dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;
	imgInput.AddGamma(&imgOutput,dlg.m_dA,dlg.m_dB);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnAddExp()					// 指数噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseExp dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;
	imgInput.AddExp(&imgOutput,dlg.m_dA);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnAddUniform()				// 均匀噪声
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;

	if (imgInput.m_pBMIH->biBitCount != 8)
	{
		AfxMessageBox(L"对不起，当前还未实现彩色图像的加噪处理！");
		return;
	}

	CDlgNoiseUniform dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;
	imgInput.AddUniform(&imgOutput, dlg.m_dLow, dlg.m_dHigh);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新图像显示
}

void CDIPView::OnEnhaSmooth()
{
	// 平滑滤波
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	int nTempH;								// 模板高度
	int nTempW;								// 模板宽度
	int nTempMX;							// 模板中心元素X坐标
	int nTempMY;							// 模板中心元素Y坐标
	double fTempC;							// 模板系数
	double aValue[25] =						// 模板元素数组赋初值（默认为平均模板）
	{ 1.0, 1.0, 1.0, 0.0, 0.0,
	  1.0, 1.0, 1.0, 0.0, 0.0,
	  1.0, 1.0, 1.0, 0.0, 0.0,
	  0.0, 0.0, 0.0, 0.0, 0.0,
	  0.0, 0.0, 0.0, 0.0, 0.0,
	};
	CDlgSmooth dlgPara;						// 创建对话框
	dlgPara.m_intType = 0;					// 初始化对话框变量值
	dlgPara.m_iTempH = 3;
	dlgPara.m_iTempW = 3;
	dlgPara.m_iTempMX = 1;
	dlgPara.m_iTempMY = 1;
	dlgPara.m_fTempC = (double)(1.0 / 9.0);
	dlgPara.m_fpArray = aValue;

	if (dlgPara.DoModal() != IDOK)			// 显示对话框，提示用户设定参数
		return;								// 返回
	nTempH = dlgPara.m_iTempH;				// 获取用户设定的参数
	nTempW = dlgPara.m_iTempW;
	nTempMX = dlgPara.m_iTempMX;
	nTempMY = dlgPara.m_iTempMY;
	fTempC = dlgPara.m_fTempC;
	BeginWaitCursor();						// 更改光标形状
	imgInput.Template(&imgOutput, nTempH, nTempW,
		nTempMY, nTempMX, aValue, fTempC);	// 调用Template()函数实现平滑滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaMidianF()
{
	// 中值滤波
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	CDlgEnhaMediaF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	imgInput.MedianFilter(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用MedianFilter()函数中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF1()
{
	// 邻域均值滤波
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	CDlgEnhaLpf1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	imgInput.LowFilter1(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用LowFilter1()函数滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF2()
{
	// 简单加权平均法
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgEnhaLpf2 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3)
	{
		AfxMessageBox(L"当前仅设计了尺寸为3的模板！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.LowFilter2(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用LowFilter2()函数滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF3()
{
	// 梯度倒数加权平均法
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	
	CDlgEnhaLpf3 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	imgInput.LowFilter3(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用LowFilter3()函数滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF4()
{
	// 超限邻域均值滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	CDlgEnhaLpf4 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标
	int nThreshold = dlg.m_iThreshold;		// 灰度差值

	imgInput.LowFilter4(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX, nThreshold);	// 调用LowFilter4()函数滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF5()
{
	// 噪声门限法
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgEnhaLpf5 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标
	int nThreshold = dlg.m_iThreshold;		// 灰度差值
	int nCnt = dlg.m_iCnt;					// 误差门限值

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	if(nCnt > (dlg.m_iSize * dlg.m_iSize + 1) / 2)
	{
		AfxMessageBox(L"不建议误差门限值大于模板值的一半！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.LowFilter5(&imgOutput, nFilterH, nFilterW, nFilterMY, nFilterMX, 
		nThreshold, nCnt);					// 调用LowFilter5()函数滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF6()
{
	// 几何均值滤波器
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaLpf6 dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.LowFilter6(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用LowFilter6()函数几何均值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF7()
{
	// 谐波均值滤波器
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	
	CDlgEnhaLpf7 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.LowFilter7(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用LowFilter7()函数谐波均值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF8()
{
	// 逆谐波均值滤波器
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	CDlgFreqInvHarmonicF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	imgInput.LowFilter8(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX, dlg.m_iLevel);// 调用LowFilter8()函数逆谐波均值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaLPF9()
{
	// 修正阿尔法均值滤波器
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgFreqAlphaMeanF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	int iDotCount = (dlg.m_iSize * dlg.m_iSize + 1) / 2;
	
	if(dlg.m_iDotCount >= iDotCount)
	{
		AfxMessageBox(L"删去点数过多，应小于模板值的一半！");
		return;
	}
	
	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.LowFilter9(&imgOutput, nFilterH, nFilterW, nFilterMY, 
		nFilterMX , dlg.m_iDotCount);		// 调用LowFilter9()函数修正阿尔法均值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaMidF()
{
	// 中点滤波
	CDIPDoc* pDoc = GetDocument();			// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaMidF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.MidFilter(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用MedianFilter()函数中点滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaHPF1()
{
	// 基本高通滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaHpf1 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3 || dlg.m_iSize != 5)
	{
		AfxMessageBox(L"当前仅设计了尺寸为3和5的模板！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.HighFilter1(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用MedianFilter()函数中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaHPF2()
{
	// 高增益滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaHpf2 dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3 || dlg.m_iSize != 5)
	{
		AfxMessageBox(L"当前仅设计了尺寸为3和5的模板！");
		return;
	}
	

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	if(dlg.m_dGain < 1)
	{
		AfxMessageBox(L"系数值应大于1");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.HighFilter2(&imgOutput, nFilterH, nFilterW, nFilterMY, 
		nFilterMX, dlg.m_dGain);			// 调用MedianFilter()函数中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnENHAAdaptMidianF()
{
	// 自适应中值滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaAdapativeMediaF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.AdaptiveMedianFilter(&imgOutput, nFilterH, nFilterW,
		nFilterMX, nFilterMY);				// 调用AdaptiveMedianFilter()函数自适应中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaGaussianF()
{
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaGaussianF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3)
	{
		AfxMessageBox(L"当前只设计出尺寸为3的模板！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.EnhaGaussianF(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用EnhaGaussianF()函数中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaAdapativeSmooth()
{
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaAdapativeSmooth dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3)
	{
		AfxMessageBox(L"当前只设计出尺寸为3的模板！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标

	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.EnhaAdaptiveSmooth(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用EnhaAdaptiveSmooth()函数中值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaGradsharp()
{
	// Sobel梯度锐化
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象
	imgInput.FilterSobel(&imgOutput);		// 调用FilterSobel()函数进行Sobel梯度锐化
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaMaxF()
{
	// 最大值滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaMaxF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标
	
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.MaxFilter(&imgOutput, nFilterH, nFilterW, 
		nFilterMY, nFilterMX);				// 调用MaxFilter()函数最大值滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaMinF()
{
	// 最小值滤波
	CDIPDoc* pDoc = GetDocument();		// 获取文档
	CImgProcess imgInput = pDoc->m_Image;	// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaMinF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize % 2 == 0 || dlg.m_iSize == 1)
	{
		AfxMessageBox(L"模板尺寸应为大于1的奇数！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;				// 滤波器的高度
	int nFilterW = dlg.m_iSize;				// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;			// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;			// 中心元素的Y坐标
	
	BeginWaitCursor();						// 更改光标形状
	CImgProcess imgOutput = imgInput;		// 输出的临时对象

	imgInput.MinFilter(&imgOutput, nFilterH, nFilterW,
		nFilterMY, nFilterMX);				// 调用MinFilter()函数最小滤波
	pDoc->m_Image = imgOutput;				// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);			// 设置修改标识
	pDoc->UpdateAllViews(NULL);				// 更新视图
	EndWaitCursor();						// 恢复光标
}

void CDIPView::OnEnhaSharp()
{
	// 拉普拉斯锐化
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	int nTempH;									// 滤波器的高度
	int nTempW;									// 滤波器的宽度
	int nTempMX;								// 中心元素的X坐标
	int nTempMY;								// 中心元素的Y坐标
	double   fCoef;								// 模板系数
	BeginWaitCursor();							// 更改光标形状
	nTempW = 3;									// 设置拉普拉斯模板参数
	nTempH = 3;
	fCoef = 1.0;
	nTempMX = 1;
	nTempMY = 1;

	imgInput.Template(&imgOutput, nTempH, nTempW, nTempMY, nTempMX,
		Template_Laplacian2, fCoef);			// 调用Template()函数用拉普拉斯模板锐化
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);				// 设置修改标识
	pDoc->UpdateAllViews(NULL);					// 更新视图
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnEnhaHighenha()
{
	// 基于3*3的Laplacian模板的高提升滤波
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEnhaEnhanceF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_iSize != 3)
	{
		AfxMessageBox(L"当前仅设计了尺寸为3的模板！");
		return;
	}

	if (dlg.m_iMove >= dlg.m_iSize - 1)
	{
		AfxMessageBox(L"平移距离过大，和当前模板大小不相匹配！");
		return;
	}

	int nFilterH = dlg.m_iSize;					// 滤波器的高度
	int nFilterW = dlg.m_iSize;					// 滤波器的宽度
	int nFilterMX = dlg.m_iMove;				// 中心元素的X坐标
	int nFilterMY = dlg.m_iMove;				// 中心元素的Y坐标
	double dGain = dlg.m_dGain;					// 相关参数设定

	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	
	imgInput.EnhanceFilter(&imgOutput, dGain, nFilterH, nFilterW, nFilterMY, nFilterMX,
		Template_Laplacian2, 1);				// 调用EnhanceFilter()函数进行高提升滤波，采用3*3的Laplacian模板，混合系数为1.8
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(TRUE);				// 设置修改标识
	pDoc->UpdateAllViews(NULL);					// 更新视图
	EndWaitCursor();							// 恢复光标
}

/**********************************************/
// 图像正交变换
void CDIPView::OnFreqFour()
{
	CDIPDoc* pDoc = GetDocument();				// 快速傅立叶变换
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.FFT2(&imgOutput, 1);				// 执行FFT2
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnFreqIFour()
{
	CDIPDoc* pDoc = GetDocument();				// 快速傅立叶变换
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	
	imgInput.FFT2(&imgOutput, 1);				// 执行FFT2
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnFreqDct()
{
	CDIPDoc* pDoc = GetDocument();				// 离散余弦变换
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.DCT(&imgOutput);					// 执行DCT
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnFreqIdct()
{
	CDIPDoc* pDoc = GetDocument();				// 离散余弦反变换
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.IDCT(&imgOutput);					// 执行IDCT
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

/**********************************************/
//  形态学变换
void CDIPView::OnMorphErosion()
{
	// 腐蚀运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回
	int se[3][3];								// 3*3结构元素
	se[0][0] = dlgPara.m_se00;					//根据用户输入设定结构元素
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Erode(&imgOutput, se);				// 调用Erode()实现图像腐蚀
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphOpen()
{
	// 开运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回
	int se[3][3];								// 3*3结构元素
	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;

	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Open(&imgOutput, se);				// 调用Open()实现图像腐蚀
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphTrace()
{
	// 边界跟踪
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.TraceBoundary(&imgOutput);			// 调用TraceBoundary()函数实现边界跟踪
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphFillrgn()
{
	// 区域的种子填充
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	// 需要根据实际情况设置种子点的坐标，这里简单地取种子点为图像的中心点
	POINT ptStart;
	ptStart.x = imgInput.GetWidthPixel() / 2;
	ptStart.y = imgInput.GetHeight() / 2;
	imgInput.FillRgn(&imgOutput, ptStart);		// 调用FillRgn()函数实现种子填充
	//POINT型参数ptStart为种子点，可以是区域当中的任意一点
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphLabelconnrgn()
{
	// 标注连通区域
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.LabelConnRgn(&imgOutput);			// 调用LabelConnRgn()函数标注连通区域
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphThining()
{
	//细化
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgOutput.Thining();						// 调用Thining()实现图像细化
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphPixel()
{
	// 像素化
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	int nLowThres;								// 连通数低于此阈值的连通区被滤除
	int nHighThres;								// 连通数高于此阈值的连通区被滤除
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	//这里设定低阈值为10，高阈值为100,连通数<10和连通数>300的连通区被滤除，之间的被像素化
	nLowThres = 10;
	nHighThres = 300;
	imgInput.PixelImage(&imgOutput, nLowThres,
		nHighThres);							// 调用PixelImage()实现图像细化
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphConvex()
{
	// 凸壳
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Convex(&imgOutput, 1);				// 调用Convex()函数计算凸集
	//第2个参数为1表示需要限制凸壳的生长
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphClose()
{
	// 闭运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回

	int se[3][3];								// 3*3结构元素
	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;

	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Close(&imgOutput, se);				// 调用Close()实现图像闭运算
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);

	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphDilation()
{
	// 膨胀运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回

	int se[3][3];								// 3*3结构元素
	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;

	BeginWaitCursor();							// 更改光标形状

	CImgProcess imgOutput = imgInput;			// 输出的临时对象

	imgInput.Dilate(&imgOutput, se);			//调用Dilate()实现图像膨胀

	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);

	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphGraydilate()
{
	// 灰度膨胀
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回

	int** se;									// 结构元素
	se = new int*[3];

	for (int i = 0; i < 3; i++)
		se[i] = new int[3];

	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GrayDilate(&imgOutput, 3, 3, 1,
		1, se);									// 调用GrayDilate()实现灰度膨胀
	//这里se是一个int **指针，表示结构元素。这里采用了3*3原点位于中心的结构元素
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphGrayerode()
{
	// 灰度腐蚀
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回

	int** se;									//结构元素
	se = new int*[3];

	for (int i = 0; i < 3; i++)
		se[i] = new int[3];

	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;

	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GrayErode(&imgOutput, 3, 3,
		1, 1, se);								// 调用GrayErode()实现灰度腐蚀
	//这里se是一个int **指针，表示结构元素。这里采用了3*3原点位于中心的结构元素
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphGrayopen()
{
	// 灰度开运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回

	int** se;									// 结构元素
	se = new int*[3];
	for (int i = 0; i < 3; i++)
		se[i] = new int[3];

	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GrayOpen(&imgOutput, 3, 3, 1, 1, se);//调用GrayOpen()实现灰度开
	//这里se是一个int **指针，表示结构元素。这里采用了3*3原点位于中心的结构元素
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphGrayclose()
{
	//灰度闭运算
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回
	int** se;									// 结构元素
	se = new int*[3];
	for (int i = 0; i < 3; i++)
		se[i] = new int[3];

	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GrayClose(&imgOutput, 3, 3, 1, 1, se);//调用GrayClose()实现灰度闭
	//这里se是一个int **指针，表示结构元素。这里采用了3*3原点位于中心的结构元素
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnMorphTophat()
{
	// 顶帽变换
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgMorph dlgPara;							// 创建对话框
	if (dlgPara.DoModal() != IDOK)				// 显示对话框，提示用户设定结构元素
		return;									// 返回
	int** se;									// 结构元素
	se = new int*[3];

	for (int i = 0; i < 3; i++)
		se[i] = new int[3];
	//根据用户输入设定结构元素
	se[0][0] = dlgPara.m_se00;
	se[0][1] = dlgPara.m_se01;
	se[0][2] = dlgPara.m_se02;
	se[1][0] = dlgPara.m_se10;
	se[1][1] = dlgPara.m_se11;
	se[1][2] = dlgPara.m_se12;
	se[2][0] = dlgPara.m_se20;
	se[2][1] = dlgPara.m_se21;
	se[2][2] = dlgPara.m_se22;
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Tophat(&imgOutput, 3, 3, 1, 1, se);// 调用Tophat()实现顶帽变换
	//这里se是一个int **指针，表示结构元素。这里采用了3*3原点位于中心的结构元素
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);

	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnPicAdd()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	CImgProcess* pStdImage = new CImgProcess();	// 标准图像

	// 通过打开对话框获取标准图像
	CString filePath;							// 文件路径
	CFileDialog openDlg(TRUE, 0, 0, 4 | 2,
		L"Bitmap Files (*.bmp)||");				// 打开文件对话框，如果用户点击取消则返回
	if (openDlg.DoModal() == IDOK)
		filePath = openDlg.GetPathName();
	else
		return;

	pStdImage->AttachFromFile(filePath);		// 获取标准图像

	if (imgInput.m_pBMIH->biWidth != pStdImage->m_pBMIH->biWidth
		|| imgInput.m_pBMIH->biHeight != pStdImage->m_pBMIH->biHeight)
		AfxMessageBox(L"提醒：图像尺寸不一致，效果可能不理想！");

	if (   (imgInput.m_pBMIH->biBitCount == 8 && pStdImage->m_pBMIH->biBitCount != 8)
		|| (imgInput.m_pBMIH->biBitCount == 24 && pStdImage->m_pBMIH->biBitCount != 24))
	{
		AfxMessageBox(L"图像位数不相匹配，不能相加！");
		return;
	}

	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.PicAdd(&imgOutput, pStdImage);		// 图像相加
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete pStdImage;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPicSub()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	CImgProcess* pStdImage = new CImgProcess();	// 标准图像

	// 通过打开对话框获取标准图像
	CString filePath;							// 文件路径
	CFileDialog openDlg(TRUE, 0, 0, 4 | 2,
		L"Bitmap Files (*.bmp)||");				// 打开文件对话框，如果用户点击取消则返回
	if (openDlg.DoModal() == IDOK)
		filePath = openDlg.GetPathName();
	else
		return;

	pStdImage->AttachFromFile(filePath);		// 获取标准图像
	
	if (imgInput.m_pBMIH->biWidth != pStdImage->m_pBMIH->biWidth
		|| imgInput.m_pBMIH->biHeight != pStdImage->m_pBMIH->biHeight)
		AfxMessageBox(L"提醒：图像尺寸不一致，效果可能不理想！");

	if (imgInput.m_pBMIH->biBitCount == 8 && pStdImage->m_pBMIH->biBitCount != 8
		|| imgInput.m_pBMIH->biBitCount == 24 && pStdImage->m_pBMIH->biBitCount != 24)
	{
		AfxMessageBox(L"位数不相匹配，不能相加！");
		return;
	}

	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.PicSub(&imgOutput, pStdImage);		// 图像相减
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete pStdImage;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPicMul()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	CImgProcess* pStdImage = new CImgProcess();	// 标准图像

												// 通过打开对话框获取标准图像
	CString filePath;							// 文件路径
	CFileDialog openDlg(TRUE, 0, 0, 4 | 2,
		L"Bitmap Files (*.bmp)||");				// 打开文件对话框，如果用户点击取消则返回
	if (openDlg.DoModal() == IDOK)
		filePath = openDlg.GetPathName();
	else
		return;

	pStdImage->AttachFromFile(filePath);		// 获取标准图像
	
	if (imgInput.m_pBMIH->biWidth != pStdImage->m_pBMIH->biWidth
		|| imgInput.m_pBMIH->biHeight != pStdImage->m_pBMIH->biHeight)
		AfxMessageBox(L"提醒：图像尺寸不一致，效果可能不理想！");
	
	if (!pStdImage->IsBiImg(pStdImage))
	{
		AfxMessageBox(L"当前图像不是二值图像不能相乘！");
		return;
	}

	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.PicSub(&imgOutput, pStdImage);		// 图像相乘
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete pStdImage;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPointStdlin()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgLinTrans dlg;							// 创建参数输入对话框
	dlg.m_bS1 = 64;
	dlg.m_bS2 = 192;
	dlg.m_bT1 = 32;
	dlg.m_bT2 = 224;

	if (dlg.DoModal() != IDOK)
		return;
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.ParLinTran(&imgOutput, dlg.m_bS1,
		dlg.m_bS2, dlg.m_bT1, dlg.m_bT2);		// 分段线性变换
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}
void CDIPView::OnPointLog()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgLog dlg;								// 创建参数输入对话框
	dlg.m_dC = 20;
	if (dlg.DoModal() != IDOK)
		return;
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.LogTran(&imgOutput, dlg.m_dC);		// 使用对数变换方法
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPointGamma()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgGamma dlg;								// 创建参数输入对话框
	dlg.m_dEsp = 0;
	dlg.m_dGamma = 1;
	if (dlg.DoModal() != IDOK)
		return;
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GammaTran(&imgOutput, dlg.m_dGamma,
		dlg.m_dEsp);							// 调用GammaTran方法执行伽玛变换
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnPointHistst()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CImgProcess* pStdImage = new CImgProcess();	// 标准图像
	double pdStdHist[256];						// 定义标准图像和原图像的灰度直方图缓冲区
	// 通过打开对话框获取标准图像
	CString filePath;							// 文件路径
	CFileDialog openDlg(TRUE, 0, 0, 4 | 2,
		L"Bitmap Files (*.bmp)||");				// 打开文件对话框，如果用户点击取消则返回
	if (openDlg.DoModal() == IDOK)
		filePath = openDlg.GetPathName();
	else
		return;
	pStdImage->AttachFromFile(filePath);		// 获取标准图像
	if (pStdImage->m_pBMIH->biBitCount != 8)	// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	pStdImage->GenHist(pdStdHist);				// 计算并显示标准图像的直方图，如果用户点击取消则返回
	CDlgHist histDlg;
	histDlg.m_pdHist = pdStdHist;
	if (histDlg.DoModal() != IDOK)
		return;
	delete histDlg;
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Histst(&imgOutput, pdStdHist);		// 直方图规定化
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete pStdImage;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnFileRotate()
{
	CDIPDoc* pdoc = GetDocument();				// 交换前、后台图像
	CImgProcess tmp = pdoc->m_Image;
	pdoc->m_Image = pdoc->m_OImage;
	pdoc->m_OImage = tmp;
	delete &tmp;
	pdoc->SetModifiedFlag(true);
	pdoc->UpdateAllViews(NULL);
}

void CDIPView::OnFileReverse()
{
	// 图像反色
	CDIPDoc* pDoc = GetDocument();				// 获取文档
	CImgProcess imgInput = pDoc->m_Image;		// 输入图像
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgOutput = !imgOutput;
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnEdgeRobert()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEdgeSobelPrewitt dlg;
	dlg.isRobert = true;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.EdgeRoberts(&imgOutput, dlg.m_bThre, dlg.m_nEdgeType, dlg.m_bThining,
		dlg.m_bGratOnly);
	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnEdgeSobel()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEdgeSobelPrewitt dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.EdgeSobel(&imgOutput, dlg.m_bThre, dlg.m_nEdgeType, dlg.m_bThining,
		dlg.m_bGratOnly);						// Sobel边缘检测
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnEdgePrewitt()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgEdgeSobelPrewitt dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.EdgePrewitt(&imgOutput, dlg.m_bThre, dlg.m_nEdgeType, dlg.m_bThining,
		dlg.m_bGratOnly);
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标
}

void CDIPView::OnEdgeLog()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.EdgeLoG(&imgOutput);
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnEdgeSimpthre()
{
	CDIPDoc* pDoc = GetDocument();				// 简单阈值分割
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}

	CDlgEdgeSimpthre dlg;
	if (dlg.DoModal() != IDOK)
		return;

	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.SimpThreshold(&imgOutput, 
		dlg.m_iThreshold);						// 分段线性变换
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnEdgeAutothre()
{
	CDIPDoc* pDoc = GetDocument();				// 自动阈值分割
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.AutoThreshold(&imgOutput);			// 自动阈值化
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnFreqIdeallpf()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqIdealLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的宽度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的高度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqIdealLPF(pdFreqFilt, dlg.m_nFreq);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqIdealhpf()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqIdealLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的宽度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的高度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqIdealHPF(pdFreqFilt, dlg.m_nFreq);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqGausslpf()
{
	CDIPDoc* pDoc = GetDocument();				// 高斯低通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqGaussLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的宽度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的高度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqGaussLPF(pdFreqFilt, dlg.m_dSigma);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqGausshpf()
{
	CDIPDoc* pDoc = GetDocument();				// 高斯高通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqGaussHPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();							// 输出的临时对象
	CImgProcess imgOutput = imgInput;			// 计算需要生成滤镜的大小
	LONG w = imgInput.GetFreqWidth();
	LONG h = imgInput.GetFreqHeight();
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqGaussHPF(pdFreqFilt, dlg.m_dSigma);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqExplpf()
{
	CDIPDoc* pDoc = GetDocument();				// 指数低通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqExpLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的宽度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的高度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqExpLPF(pdFreqFilt, dlg.m_nFreq, dlg.n);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqExphpf()
{
	CDIPDoc* pDoc = GetDocument();				// 指数高通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqExpHPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();							// 输出的临时对象
	CImgProcess imgOutput = imgInput;			// 计算需要生成滤镜的大小
	LONG w = imgInput.GetFreqWidth();
	LONG h = imgInput.GetFreqHeight();
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqExpHPF(pdFreqFilt, dlg.m_nFreq, dlg.n);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqLadderlpf()
{
	CDIPDoc* pDoc = GetDocument();				// 指数高通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqLadderLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_nFreq > dlg.m_nF)
	{
		AfxMessageBox(L"截止频率大于可调频率，请重新设置！");
		return;
	}

	BeginWaitCursor();							// 输出的临时对象
	CImgProcess imgOutput = imgInput;			// 计算需要生成滤镜的大小
	LONG w = imgInput.GetFreqWidth();
	LONG h = imgInput.GetFreqHeight();
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqLadderLPF(pdFreqFilt, dlg.m_nFreq, dlg.m_nF);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqLadderhpf()
{
	CDIPDoc* pDoc = GetDocument();				// 指数高通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqLadderHPF dlg;
	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_nFreq > dlg.m_nF)
	{
		AfxMessageBox(L"截止频率大于可调频率，请重新设置！");
		return;
	}

	BeginWaitCursor();							// 输出的临时对象
	CImgProcess imgOutput = imgInput;			// 计算需要生成滤镜的大小
	LONG w = imgInput.GetFreqWidth();
	LONG h = imgInput.GetFreqHeight();
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqLadderHPF(pdFreqFilt, dlg.m_nFreq, dlg.m_nF);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqButterworthlpf()
{
	CDIPDoc* pDoc = GetDocument();				// 巴特沃斯低通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqButterworthLPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的宽度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的高度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqButterworthLPF(pdFreqFilt, dlg.m_nFreq, dlg.n);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqButterworthhpf()
{
	CDIPDoc* pDoc = GetDocument();				// 巴特沃斯高通滤波
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqButterworthHPF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();							// 输出的临时对象
	CImgProcess imgOutput = imgInput;			// 计算需要生成滤镜的大小
	LONG w = imgInput.GetFreqWidth();
	LONG h = imgInput.GetFreqHeight();
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqButterworthHPF(pdFreqFilt, dlg.m_nFreq, dlg.n);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqLapl()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的高度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的宽度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqLaplace(pdFreqFilt);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	//　应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnFreqGaussbr()
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CDlgFreqGaussBRF dlg;
	dlg.m_nFreq = 0;
	dlg.m_nWidth = 0;
	if (dlg.DoModal() != IDOK)
		return;
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	LONG w = imgInput.GetFreqWidth();			// 计算需要生成滤镜的高度
	LONG h = imgInput.GetFreqHeight();			// 计算需要生成滤镜的宽度
	double* pdFreqFilt = new double[w * h];		// 生成频域滤镜
	imgInput.FreqGaussBRF(pdFreqFilt, dlg.m_nFreq, dlg.m_nWidth);
	imgInput.FreqFilt(&imgOutput, pdFreqFilt);	// 应用滤镜
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	delete[] pdFreqFilt;						// 删除临时变量
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnEdgeCanny()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档对象
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	BeginWaitCursor();
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.EdgeCanny(&imgOutput);
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();
}

void CDIPView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDIPDoc* pDoc = GetDocument();
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象

	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	CDlgPointThre* dlgPara;						// 参数对话框

	switch (m_bLBtnDblClkSrv)
	{
	case 0:
		break;

	case 1:
		BYTE    bThre;							// 阈值
		dlgPara = new CDlgPointThre();			// 初始化对话框和变量
		dlgPara->m_bThre = 16;
		if (dlgPara->DoModal() != IDOK)			// 显示对话框，提示用户设定阈值
			return;								// 返回

		bThre = dlgPara->m_bThre;				// 获取用户设定的阈值
		delete dlgPara;							// 删除对话框
		imgInput.RegionGrow(&imgOutput, point.x, point.y, bThre);// 执行区域生长
		break;

	default:
		AfxMessageBox((LPCTSTR)L"错误的参数设置，检查设定的服务参数");
	}

	pDoc->m_Image = imgOutput;
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	m_bLBtnDblClkSrv = 0;
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDIPView::OnEdgeRegionGrow()
{
	// 区域生长
	AfxMessageBox((LPCTSTR)L"双击图像中的区域以设定区域生长起始点。");
	m_bLBtnDblClkSrv = 1;						//置1使得双击消息触发区域生长
}

void CDIPView::OnEdgeHough()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档对象
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (!imgInput.IsBinaryImg())				// 检查图像是二值图像
	{
		AfxMessageBox(L"不是二值图像，无法处理！");
		return;
	}
	CDlgHough dlg;
	dlg.m_nNum = 0;

	if (dlg.DoModal() != IDOK)
		return;
	int nLineCount = dlg.m_nNum;					// 要找到的直线数目
	SLineInfo* pLines = new SLineInfo[nLineCount];	// 直线保存临时对象
	CImgProcess imgOutput = imgInput;				// 输出的临时对象
	imgInput.Hough(pLines, nLineCount);				// Hough变换

	// 输出结果
	for (int k = 0; k < nLineCount; k++)			//处理第k条直线
	{
		//扫描图像绘制直线
		for (int i = 0; i < imgInput.GetHeight(); i++)
		{
			for (int j = 0; j < imgInput.GetWidthPixel(); j++)
			{
				int nDist;
				nDist = (int)(j * cos(pLines[k].nAngle * PI / 180.0) 
					+ i * sin(pLines[k].nAngle * PI 
						/ 180.0));				// 根据theta计算rho
				if (nDist == pLines[k].nDist)	//如果点（j, i）在直线上
					imgOutput.SetPixel(j, i, RGB(255, 255, 255));
			}//for j
		}//for i
	}//for k
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnFileConvertgray()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档对象
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是256色图
	{
		AfxMessageBox(L"不是256色图像，无法处理！");
		return;
	}
	imgInput.Index2Gray();						// 256色索引图转灰度
	pDoc->m_Image = imgInput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}


void CDIPView::OnFileClean()
{
	CDIPDoc* pDoc = GetDocument();				// 获取文档对象
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	
	imgInput.InitPixels(0x00808080);			// 清空图像（和背景颜色相同）
	pDoc->m_Image = imgInput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);				// 设置脏标志
	pDoc->UpdateAllViews(NULL);					// 设置客户区域无效，激发重绘事件
}

void CDIPView::OnFileInfoShow()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	int iWidth, iHeight, iBitCount, iSize;		// 图像的宽度、高度、位深和大小
	iWidth = imgInput.m_pBMIH->biWidth;			// 图像宽度
	iHeight = imgInput.m_pBMIH->biHeight;		// 图像高度
	iBitCount = imgInput.m_pBMIH->biBitCount;	// 位深
	iSize = imgInput.m_pBMIH->biSize;			// 尺寸

	CDlgFileInfoShow dlg;
	if (dlg.DoModal() != IDOK)
		return;

}

void CDIPView::OnColorRGB2GrayMax()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2Gray(&imgOutput,1);			// RGB2Gray
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2GrayEven()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2Gray(&imgOutput, 2);			// RGB2Gray
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2GrayWeight()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2Gray(&imgOutput, 3);			// RGB2Gray
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorGray2RGBPseudo()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是灰度图，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Gray2RGB(&imgOutput,1);			// Gray2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorGray2RGBRainbow()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是灰度图，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.Gray2RGB(&imgOutput,2);			// Gray2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorGetRLevel()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GetRGBLevel(&imgOutput, 1);		// 获取R、G、B平面
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorGetGLevel()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GetRGBLevel(&imgOutput, 2);		// 获取R、G、B平面
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorGetBLevel()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.GetRGBLevel(&imgOutput, 3);		// 获取R、G、B平面
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2CMY()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2CMY(&imgOutput);				// RGB2CMY
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorCMY2RGB()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.CMY2RGB(&imgOutput);				// CMY2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2HSI()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2HSI(&imgOutput);				// RGB2HSI
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorHSI2RGB()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.HSI2RGB(&imgOutput);				// HSI2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2HSV()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2HSV(&imgOutput);				// RGB2HSV
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorHSV2RGB()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.HSV2RGB(&imgOutput);				// HSV2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2YUV()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2YUV(&imgOutput);				// RGB2YUV
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorYUV2RGB()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.YUV2RGB(&imgOutput);				// YUV2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorRGB2YIQ()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是RGB图像
	{
		AfxMessageBox(L"不是RGB图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.RGB2YIQ(&imgOutput);				// RGB2YIQ
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnColorYIQ2RGB()
{
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 24)		// 检查图像是24位图像
	{
		AfxMessageBox(L"不是24位图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	imgInput.YIQ2RGB(&imgOutput);				// YIQ2RGB
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
}

void CDIPView::OnRecTemplate()
{
	//模板匹配
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图像
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	CImgProcess imgOutput = imgInput;			// 输出的临时对象
	CImgProcess TplImage;						// 模板图像
	CFileDialog dlg(TRUE, L"bmp", L"*.bmp");	// 弹出对话框让用户选择模板图像
	if (dlg.DoModal() == IDOK)
	{
		CString strPathName;
		strPathName = dlg.GetPathName();
		TplImage.AttachFromFile(strPathName);
	}
	else
		return;
	int nHeight = imgInput.GetHeight();
	int nWidth = imgInput.GetWidthPixel();
	int nTplHeight = TplImage.GetHeight();
	int nTplWidth = TplImage.GetWidthPixel();
	if (nTplHeight > nHeight || nTplWidth > nWidth)
	{
		// 提示用户
		MessageBox(L"模板尺寸大于源图像尺寸！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		return;
	}
	BeginWaitCursor();							// 更改光标形状
	imgInput.TemplateMatch(&imgOutput,
		&TplImage);								// 进行模板匹配
	pDoc->m_Image = imgOutput;					// 将结果返回给文档类
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	EndWaitCursor();							// 恢复光标形状
}

void CDIPView::OnFeaGraymat()
{
	//计算灰度共现矩阵
	CDIPDoc* pDoc = GetDocument();				// 获得文档类指针
	CImgProcess imgInput = pDoc->m_Image;		// 输入对象
	if (imgInput.m_pBMIH->biBitCount != 8)		// 检查图像是灰度图像
	{
		AfxMessageBox(L"不是8-bpp灰度图像，无法处理！");
		return;
	}
	POINT ptD1, ptD2;							//设定两个点的位置关系
	/*  //水平灰度共现矩阵
		ptD1.x = 1;
		ptD1.y = 0;
		ptD2.x = -1;
		ptD2.y = 0;
	*/
	//+45度灰度共现矩阵
	ptD1.x = +1;
	ptD1.y = -1;
	ptD2.x = -1;
	ptD2.y = +1;
	//计算灰度共现矩阵
	vector<vector<int>> GrayMat = imgInput.GetGrayMatrix(ptD1, ptD2);
	CString str;
	int m = GrayMat.size();
	int n = GrayMat[0].size();
	//弹出对话框，显示灰度共现矩阵
	str.Format(L"{%d %d %d;%d %d %d;%d %d %d}",
		GrayMat[0][0], GrayMat[0][1], GrayMat[0][2],
		GrayMat[1][0], GrayMat[1][1], GrayMat[1][2],
		GrayMat[2][0], GrayMat[2][1], GrayMat[2][2]);
	AfxMessageBox(str);
}