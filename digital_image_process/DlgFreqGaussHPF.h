#pragma once
// CDlgFreqGaussHPF 对话框
class CDlgFreqGaussHPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqGaussHPF)
public:
	CDlgFreqGaussHPF(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgFreqGaussHPF();
	enum { IDD = IDD_DLG_FREQ_GAUSSHPF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dSigma;									// 高斯滤波器Sigma参数
};
