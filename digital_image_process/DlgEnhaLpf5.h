#pragma once
// DlgEnhaLpf5.h 对话框

class CDlgEnhaLpf5 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf5)
public:
	CDlgEnhaLpf5(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf5();
	enum { IDD = IDD_DLG_ENHA_LPF5 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 噪声门限法均值滤波器尺寸，平移大小，消去点数
	int m_iCnt, m_iThreshold;							// 误差计数器、计算器门限值
};