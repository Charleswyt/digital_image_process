#pragma once
// DlgEnhaHpf2.h 对话框

class CDlgEnhaHpf2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaHpf2)
public:
	CDlgEnhaHpf2(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaHpf2();
	enum { IDD = IDD_DLG_ENHA_HPF2 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 高增益滤波器尺寸，平移大小
	int m_dGain;										// 高增益滤波系数
};