#pragma once
// DlgEnhaMinF.h 对话框

class CDlgEnhaMinF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaMinF)
public:
	CDlgEnhaMinF(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaMinF();
	enum { IDD = IDD_DLG_ENHA_MINF };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 最小值滤波器尺寸，平移大小
};