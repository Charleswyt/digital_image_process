#pragma once
// DlgEnhaLpf3.h 对话框

class CDlgEnhaLpf3 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf3)
public:
	CDlgEnhaLpf3(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf3();
	enum { IDD = IDD_DLG_ENHA_LPF3 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 梯度倒数加权均值滤波器尺寸，平移大小
};