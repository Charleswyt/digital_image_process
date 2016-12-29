#pragma once
// CDlgNoiseRayleigh 对话框
class CDlgNoiseRayleigh : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseRayleigh)
public:
	CDlgNoiseRayleigh(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgNoiseRayleigh();
	enum { IDD = IDD_DLG_NOISE_RAYLEIGH };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dRate, m_dSigma;							// 指数噪声均值和方差
};