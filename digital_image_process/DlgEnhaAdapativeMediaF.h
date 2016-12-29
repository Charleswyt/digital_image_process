#pragma once
// DlgEnhaAdapativeMediaF.h 对话框

class CDlgEnhaAdapativeMediaF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaAdapativeMediaF)
public:
	CDlgEnhaAdapativeMediaF(CWnd* pParent = NULL);		// 标准构造函数
	virtual ~CDlgEnhaAdapativeMediaF();
	enum { IDD = IDD_DLG_ENHA_ADAPATIVEMEDIAF };		// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 自适应中值滤波器尺寸，平移大小
};