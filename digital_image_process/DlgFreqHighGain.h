#pragma once
// CDlgFreqHighGain 对话框
class CDlgFreqHighGain : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqHighGain)
public:
	CDlgFreqHighGain(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgFreqHighGain();
	enum { IDD = IDD_DLG_ENHA_HPF2 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dCofficient;								// 高增益滤波器系数
};
