#pragma once
// DlgEnhaMidF.h 对话框

class CDlgEnhaMidF : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnhaMidF)
public:
	CDlgEnhaMidF(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgEnhaMidF();
	enum { IDD = IDD_DLG_ENHA_MIDF };					// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iSize, m_iMove;								// 中值滤波器尺寸，平移大小
};