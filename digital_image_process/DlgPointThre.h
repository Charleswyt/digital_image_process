#pragma once
// CDlgPointThre 对话框

class CDlgPointThre : public CDialog
{
	DECLARE_DYNAMIC(CDlgPointThre)
public:
	CDlgPointThre(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDlgPointThre();
	enum { IDD = IDD_DLG_PointThre };		// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	BYTE m_bThre;							// 阈值
};
