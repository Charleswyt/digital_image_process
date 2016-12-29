#pragma once
// CDlgNoiseSaltPepper 对话框

class CDlgNoiseSaltPepper : public CDialog
{
	DECLARE_DYNAMIC(CDlgNoiseSaltPepper)
public:
	CDlgNoiseSaltPepper(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgNoiseSaltPepper();
	enum { IDD = IDD_DLG_NOISE_SALTPEPPER };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_dRate;										// 椒盐噪声强度
};