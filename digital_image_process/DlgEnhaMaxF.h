#pragma once
// DlgEnhaMaxF.h 对话框

class CDlgEnhaMaxF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaMaxF)
public:
	CDlgEnhaMaxF(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaMaxF();
	enum { IDD = IDD_DLG_ENHA_MAXF };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 最大值滤波器尺寸，平移大小
};