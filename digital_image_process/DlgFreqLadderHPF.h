#pragma once
// CDlgFreqLadderHPF 对话框
class CDlgFreqLadderHPF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqLadderHPF)
public:
	CDlgFreqLadderHPF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqLadderHPF();
	enum { IDD = IDD_DLG_FREQ_LADDERHPF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;										// 梯形滤波器截止频率D0
	int m_nF;											// 梯形滤波器频率D1
};