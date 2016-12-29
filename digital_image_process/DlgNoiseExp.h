#pragma once
// CDlgNoiseExp 对话框
class CDlgNoiseExp : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseExp)
public:
	CDlgNoiseExp(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgNoiseExp();
	enum { IDD = IDD_DLG_NOISE_EXP };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dA;										// 指数噪声均值和方差
};