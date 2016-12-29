#pragma once
// CDlgNoiseGamma 对话框
class CDlgNoiseGamma : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseGamma)
public:
	CDlgNoiseGamma(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgNoiseGamma();
	enum { IDD = IDD_DLG_NOISE_GAMMA };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dA, m_dB;									// 伽马（爱尔兰）噪声均值和方差
};