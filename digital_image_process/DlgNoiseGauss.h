#pragma once
// CDlgNoiseGauss 对话框
class CDlgNoiseGauss : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseGauss)
public:
	CDlgNoiseGauss(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgNoiseGauss();
	enum { IDD = IDD_DLG_NOISE_GAUSS };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dRate, m_dSigma;							// 高斯噪声均值和方差
};