#pragma once
// DlgEnhaLpf2.h 对话框

class CDlgEnhaLpf2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf2)
public:
	CDlgEnhaLpf2(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf2();
	enum { IDD = IDD_DLG_ENHA_LPF2 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 算数均值滤波器尺寸，平移大小
};