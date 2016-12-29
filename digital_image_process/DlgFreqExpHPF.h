#pragma once
// CDlgFreqExpHPF 对话框
class CDlgFreqExpHPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqExpHPF)
public:
	CDlgFreqExpHPF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqExpHPF();
	enum { IDD = IDD_DLG_FREQ_EXPHPF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;										// 指数滤波器截止频率
	int n;												// 指数滤波器阶数
};