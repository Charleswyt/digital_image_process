#pragma once
// DlgEnhaLpf4.h 对话框

class CDlgEnhaLpf4 : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaLpf4)
public:
	CDlgEnhaLpf4(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaLpf4();
	enum { IDD = IDD_DLG_ENHA_LPF4 };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 超限邻域滤波器尺寸，平移大小，消去点数
	int m_iThreshold;									// 灰度差值
};