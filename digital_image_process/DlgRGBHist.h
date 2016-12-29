#pragma once
// CDlgRGBHist 对话框

class CDlgRGBHist : public CDialog
{
	DECLARE_DYNAMIC(CDlgRGBHist)

public:
	CDlgRGBHist(CWnd* pParent = NULL);					// 标准构造函数
	virtual ~CDlgRGBHist();
	enum { IDD = IDD_DLG_HIST_RGB };					// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	// 传入的灰度直方图数据
	double* m_pdHistR;
	double* m_pdHistG;
	double* m_pdHistB;	
};