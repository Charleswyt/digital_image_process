#pragma once
// DlgEnhaEnhanceF.h 对话框

class CDlgEnhaEnhanceF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaEnhanceF)
public:
	CDlgEnhaEnhanceF(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgEnhaEnhanceF();
	enum { IDD = IDD_DLG_ENHA_ENHANCEF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 高提升滤波器尺寸，平移大小
	int m_dGain;										// 高提升滤波系数
};