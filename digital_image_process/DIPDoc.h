#if !defined(AFX_DIPDemoDOC_H__766DD4EA_BF18_426A_BA52_B747D78F541C__INCLUDED_)
#define AFX_DIPDemoDOC_H__766DD4EA_BF18_426A_BA52_B747D78F541C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Img.h"
#include "ImgProcess.h"

class CDIPDoc : public CDocument
{
protected: // create from serialization only
	CDIPDoc();
	DECLARE_DYNCREATE(CDIPDoc)


	// Operations
public:
	CSize GetDocSize() const 
	{
		return m_sizeDoc;
	}
	CPalette* GetDocPalette() const 
	{	//返回逻辑调色板，在256色显示模式下需要
		return m_pPalette;
	}

// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CDIPDoc)
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CImgProcess m_Image;	// 对应的CImgProcess对象（当前）
	CImgProcess m_OImage;	// 对应的CImgProcess对象（后台）
	CPalette* m_pPalette;	// 逻辑调色板，在256色显示模式下需要
	void Init();			// 初始化
	virtual ~CDIPDoc();	// DIPDemoDoc
	COLORREF m_refColorBKG; // 背景色
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
protected:
	afx_msg void OnFileReopen();//{{AFX_MSG(CDIPDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CSize m_sizeDoc;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DIPDemoDOC_H__766DD4EA_BF18_426A_BA52_B747D78F541C__INCLUDED_)
