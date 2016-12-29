#pragma once
// DlgFreqAlphaMeanF.h 对话框

class CDlgFreqAlphaMeanF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqAlphaMeanF)
public:
	CDlgFreqAlphaMeanF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqAlphaMeanF();
	enum { IDD = IDD_DLG_FREQ_ALPHAMEANF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove, m_iDotCount;					// 修正阿尔法均值滤波器尺寸，平移大小，消去点数
};