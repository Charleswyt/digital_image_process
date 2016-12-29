#pragma once
// CDlgGamma 对话框
class CDlgGamma : public CDialog 
{
	DECLARE_DYNAMIC(CDlgGamma)
public:
	CDlgGamma(CWnd* pParent = NULL);// 标准构造函数
	virtual ~CDlgGamma();
	enum { IDD = IDD_DLG_GAMMA };	// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dEsp;	// 补偿系数
	double m_dGamma;// 指数系数
};
