#pragma once
// DlgEnhaLpf7.h 对话框

class CDlgEnhaLpf7 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf7)
public:
	CDlgEnhaLpf7(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf7();
	enum { IDD = IDD_DLG_ENHA_LPF7 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 谐波均值滤波器尺寸，平移大小
};