#pragma once
// CDlgNoiseUniform 对话框
class CDlgNoiseUniform : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseUniform)
public:
	CDlgNoiseUniform(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgNoiseUniform();
	enum { IDD = IDD_DLG_NOISE_UNIFORM };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dLow, m_dHigh;								// 均匀噪声上界和下界
};