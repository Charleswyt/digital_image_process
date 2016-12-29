#pragma once
// CDlgFreqGaussLPF 对话框
class CDlgFreqButterworthLPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqButterworthLPF)
public:
	CDlgFreqButterworthLPF(CWnd* pParent = NULL);		// 标准构造函数
	virtual ~CDlgFreqButterworthLPF();
	enum { IDD = IDD_DLG_FREQ_BUTTERWORTHLPF };			// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;										// 巴特沃斯滤波器截止频率
	int n;												// 巴特沃斯滤波器阶数
};