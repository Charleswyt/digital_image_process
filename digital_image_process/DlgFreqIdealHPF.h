#pragma once
// CDlgFreqIdealHPF 对话框
class CDlgFreqIdealHPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqIdealHPF)
public:
	CDlgFreqIdealHPF(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgFreqIdealHPF();
	enum { IDD = IDD_DLG_FREQ_IDEALHPF };				// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;		// 截止频率
};