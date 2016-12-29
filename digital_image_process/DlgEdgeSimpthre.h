#pragma once
// CDlgEdgeSimpthre 对话框

class CDlgEdgeSimpthre : public CDialog
{
	DECLARE_DYNAMIC(CDlgEdgeSimpthre)
public:
	CDlgEdgeSimpthre(CWnd* pParent = NULL);				// 标准构造函数
	virtual ~CDlgEdgeSimpthre();
	enum { IDD = IDD_DLG_EDGE_SIMPTHRE };				// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	double m_iThreshold;								// 阈值
};