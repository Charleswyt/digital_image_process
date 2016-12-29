#pragma once
// CDlgFreqExpLPF 对话框
class CDlgFreqExpLPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqExpLPF)
public:
	CDlgFreqExpLPF(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgFreqExpLPF();
	enum { IDD = IDD_DLG_FREQ_EXPLPF };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;										// 指数滤波器截止频率
	int n;												// 指数滤波器阶数
};