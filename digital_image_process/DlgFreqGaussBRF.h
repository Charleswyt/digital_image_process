#pragma once
// CDlgFreqGaussBRF 对话框
class CDlgFreqGaussBRF : public CDialog
{
	DECLARE_DYNAMIC(CDlgFreqGaussBRF)
public:
	CDlgFreqGaussBRF(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFreqGaussBRF();
	enum { IDD = IDD_DLG_FREQ_GAUSSBRF };			// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;	// 阻带中心频率
	int m_nWidth;	// 阻带宽度
};