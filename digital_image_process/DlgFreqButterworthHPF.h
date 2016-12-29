#pragma once
// CDlgFreqButterworthHPF 对话框
class CDlgFreqButterworthHPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqButterworthHPF)
public:
	CDlgFreqButterworthHPF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqButterworthHPF();
	enum { IDD = IDD_DLG_FREQ_BUTTERWORTHHPF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);		// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;											// 巴特沃斯滤波器截止频率
	int n;													// 巴特沃斯滤波器阶数
};