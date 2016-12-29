#pragma once
// CDlgFreqLadderLPF 对话框
class CDlgFreqLadderLPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqLadderLPF)
public:
	CDlgFreqLadderLPF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqLadderLPF();
	enum { IDD = IDD_DLG_FREQ_LADDERLPF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;										// 梯形滤波器截止频率D0
	int m_nF;											// 梯形滤波器频率D1
};