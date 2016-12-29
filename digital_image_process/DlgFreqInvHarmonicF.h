#pragma once
// DlgFreqInvHarmonicF.h 对话框

class CDlgFreqInvHarmonicF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqInvHarmonicF)
public:
	CDlgFreqInvHarmonicF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqInvHarmonicF();
	enum { IDD = IDD_DLG_FREQ_INVHARMONICF };			// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove, m_iLevel;						// 逆谐波均值滤波器尺寸，平移距离和阶数
};