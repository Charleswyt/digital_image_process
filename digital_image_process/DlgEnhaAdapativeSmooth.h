#pragma once
// DlgEnhaAdapativeSmooth.h 对话框

class CDlgEnhaAdapativeSmooth : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaAdapativeSmooth)
public:
	CDlgEnhaAdapativeSmooth(CWnd* pParent = NULL);		// 标准构造函数
	virtual ~CDlgEnhaAdapativeSmooth();
	enum { IDD = IDD_DLG_ENHA_ADAPATIVE_SMOOTH };		// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 自适应中值滤波器尺寸，平移大小
};