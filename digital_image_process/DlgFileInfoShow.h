#pragma once
// CDlgFileInfoShow 对话框
class CDlgFileInfoShow : public CDialog
{
	DECLARE_DYNAMIC(CDlgFileInfoShow)
public:
	CDlgFileInfoShow(CWnd* pParent = NULL);			// 标准构造函数
	virtual ~CDlgFileInfoShow();
	enum { IDD = IDD_DLG_ShowInfo };				// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int m_iWidth;									// 图像宽度
	int m_iHeight;									// 图像高度
	int m_iBitCount;								// 图像位深
	int m_iSize;									// 图像大小
};