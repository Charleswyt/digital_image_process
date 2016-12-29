#pragma once
// DlgEnhaGaussianF.h 对话框

class CDlgEnhaGaussianF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaGaussianF)
public:
	CDlgEnhaGaussianF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgEnhaGaussianF();
	enum { IDD = IDD_DLG_ENHA_GAUSSIANF };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 高斯平滑滤波器尺寸，平移大小
};