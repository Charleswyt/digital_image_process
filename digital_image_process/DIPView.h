#if !defined(AFX_DIPDemoVIEW_H__60AAD957_ED0B_48FF_834E_78C547411B15__INCLUDED_)
#define AFX_DIPDemoVIEW_H__60AAD957_ED0B_48FF_834E_78C547411B15__INCLUDED_

#include "Img.h"
#include "ImgProcess.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDIPView : public CScrollView
{
// create from serialization only
protected: 	
	CDIPView();
	DECLARE_DYNCREATE(CDIPView)

// Attributes
public:
	CDIPDoc* GetDocument();

// Operations
public:

// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CDIPView)
public:
	virtual void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual void OnDraw2(CDC* pDC);		// overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIPView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGeomTran();
	afx_msg void OnGeomMirv();
	afx_msg void OnGeomMirh();
	afx_msg void OnGeomRota();
	afx_msg void OnGeomTrpo();
	afx_msg void OnGeomZoom1();
	afx_msg void OnGeomZoom2();
	afx_msg void OnPointEqua();
	afx_msg void OnPointLiner();
	afx_msg void OnPointWind();
	afx_msg void OnPointThre();
	afx_msg void OnViewIntensity();
	afx_msg void OnGetBitLayerI();
	afx_msg void OnGetBitLayerII();
	afx_msg void OnGetBitLayerIII();
	afx_msg void OnGetBitLayerIV();
	afx_msg void OnGetBitLayerV();
	afx_msg void OnGetBitLayerVI();
	afx_msg void OnGetBitLayerVII();
	afx_msg void OnGetBitLayerVIII();
	afx_msg void OnFreqFour();
	afx_msg void OnFreqIFour();
	afx_msg void OnFreqDct();
	afx_msg void OnFreqIdct();

	afx_msg void OnEnhaSmooth();
	afx_msg void OnEnhaMidianF();
	afx_msg void OnEnhaLPF1();
	afx_msg void OnEnhaLPF2();
	afx_msg void OnEnhaLPF3();
	afx_msg void OnEnhaLPF4();
	afx_msg void OnEnhaLPF5();
	afx_msg void OnEnhaLPF6();
	afx_msg void OnEnhaLPF7();
	afx_msg void OnEnhaLPF8();
	afx_msg void OnEnhaLPF9();
	afx_msg void OnEnhaMidF();
	afx_msg void OnEnhaHPF1();
	afx_msg void OnEnhaHPF2();
	afx_msg void OnEnhaSharp();
	afx_msg void OnEnhaGradsharp();
	afx_msg void OnEnhaMaxF();
	afx_msg void OnEnhaMinF();
	afx_msg void OnENHAAdaptMidianF();
	afx_msg void OnEnhaHighenha();
	afx_msg void OnEnhaGaussianF();
	afx_msg void OnEnhaAdapativeSmooth();

	afx_msg void OnMorphErosion();
	afx_msg void OnMorphDilation();
	afx_msg void OnMorphOpen();
	afx_msg void OnMorphClose();
	afx_msg void OnMorphThining();

	afx_msg void OnAddGaussian();
	afx_msg void OnAddSalt();
	afx_msg void OnAddRayleigh();
	afx_msg void OnAddGamma();
	afx_msg void OnAddExp();
	afx_msg void OnAddUniform();

	afx_msg void OnGeomCali();
	afx_msg void OnFileClean();
	afx_msg void OnFileInfoShow();

	afx_msg void OnColorRGB2GrayMax();
	afx_msg void OnColorRGB2GrayEven();
	afx_msg void OnColorRGB2GrayWeight();
	afx_msg void OnColorGray2RGBPseudo();
	afx_msg void OnColorGray2RGBRainbow();
	afx_msg void OnColorGetRLevel();
	afx_msg void OnColorGetGLevel();
	afx_msg void OnColorGetBLevel();
	afx_msg void OnColorRGB2CMY();
	afx_msg void OnColorCMY2RGB();
	afx_msg void OnColorRGB2HSI();
	afx_msg void OnColorHSI2RGB();
	afx_msg void OnColorRGB2HSV();
	afx_msg void OnColorHSV2RGB();
	afx_msg void OnColorRGB2YUV();
	afx_msg void OnColorYUV2RGB();
	afx_msg void OnColorRGB2YIQ();
	afx_msg void OnColorYIQ2RGB();

	afx_msg void OnRecTemplate();
	afx_msg void OnFeaGraymat();
	afx_msg void OnMorphTrace();
	afx_msg void OnFileReverse();
	afx_msg void OnMorphFillrgn();
	afx_msg void OnMorphLabelconnrgn();
	afx_msg void OnMorphPixel();
	afx_msg void OnMorphConvex();
	afx_msg void OnMorphGraydilate();
	afx_msg void OnMorphGrayerode();
	afx_msg void OnMorphGrayopen();
	afx_msg void OnMorphGrayclose();
	afx_msg void OnMorphTophat();

	afx_msg void OnPicAdd();
	afx_msg void OnPicSub();
	afx_msg void OnPicMul();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPointStdlin();
	afx_msg void OnPointLog();
	afx_msg void OnPointGamma();
	afx_msg void OnPointHistst();
	afx_msg void OnFileRotate();
	afx_msg void OnEdgeRobert();
	afx_msg void OnEdgeSobel();
	afx_msg void OnEdgePrewitt();
	afx_msg void OnEdgeLog();
	afx_msg void OnEdgeSimpthre();
	afx_msg void OnEdgeAutothre();
	afx_msg void OnFreqIdeallpf();
	afx_msg void OnFreqIdealhpf();
	afx_msg void OnFreqButterworthlpf();
	afx_msg void OnFreqButterworthhpf();
	afx_msg void OnFreqGausslpf();
	afx_msg void OnFreqGausshpf();
	afx_msg void OnFreqExplpf();
	afx_msg void OnFreqExphpf();
	afx_msg void OnFreqLadderlpf();
	afx_msg void OnFreqLadderhpf();
	afx_msg void OnFreqLapl();
	afx_msg void OnFreqGaussbr();
	afx_msg void OnEdgeCanny();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEdgeRegionGrow();
	afx_msg void OnEdgeHough();
	afx_msg void OnFileConvertgray();
	afx_msg void OnViewRGBIntensity();
	afx_msg void OnMatchingRGBHist();

public:
	// 左键在主窗口客户区双击对应所需服务的代码
	BYTE m_bLBtnDblClkSrv;
};

#ifndef _DEBUG  // debug version in DIPDemoView.cpp
inline CDIPDoc* CDIPView::GetDocument()
{
	return (CDIPDoc*)m_pDocument;
}
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DIPDemoVIEW_H__60AAD957_ED0B_48FF_834E_78C547411B15__INCLUDED_)