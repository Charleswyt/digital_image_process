#pragma once
// DlgEnhaHpf1.h 对话框

class CDlgEnhaHpf1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaHpf1)
public:
	CDlgEnhaHpf1(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaHpf1();
	enum { IDD = IDD_DLG_ENHA_HPF1 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 基本高通滤波器尺寸，平移大小
};