#pragma once
// DlgEnhaLpf6.h 对话框

class CDlgEnhaLpf6 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf6)
public:
	CDlgEnhaLpf6(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf6();
	enum { IDD = IDD_DLG_ENHA_LPF6 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 几何均值滤波器尺寸，平移大小
};