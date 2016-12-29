#pragma once
// CDlgFreqIdealLPF 对话框
class CDlgFreqIdealLPF : public CDialog 
{
	DECLARE_DYNAMIC(CDlgFreqIdealLPF)
public:
	CDlgFreqIdealLPF(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgFreqIdealLPF();
	enum { IDD = IDD_DLG_FREQ_IDEALLPF };				// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;		// 截止频率
};