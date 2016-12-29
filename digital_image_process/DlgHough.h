#pragma once
// CDlgHough 对话框
class CDlgHough : public CDialog
{
	DECLARE_DYNAMIC(CDlgHough)

public:
	CDlgHough(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDlgHough();
	enum { IDD = IDD_HOUGH };			// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	int m_nNum;
};