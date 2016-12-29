#include "stdafx.h"
#include "DIP.h"

#include "DIPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDIPDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIPDoc, CDocument)
	//{{AFX_MSG_MAP(CDIPDoc)
	ON_COMMAND(ID_FILE_REOPEN, OnFileReopen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDIPDoc::CDIPDoc()
{
	m_sizeDoc = CSize(1, 1);
	m_pPalette = NULL;
	// 默认背景色，灰色
	m_refColorBKG = 0x00808080;
}

CDIPDoc::~CDIPDoc()
{
	
	if (m_pPalette != NULL)				// 判断调色板是否存在
	{
		
		delete m_pPalette;// 清除调色板
	}
}

BOOL CDIPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void CDIPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

BOOL CDIPDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	return CDocument::CanCloseFrame(pFrame);
}

void CDIPDoc::DeleteContents()
{
	if (m_pPalette != NULL)
		m_pPalette->DeleteObject();

	CDocument::DeleteContents();
}


void CDIPDoc::Init()
{
	if (!m_Image.IsValidate())								// 如果图像无效，直接返回
		return;

	// 设置文档大小
	m_sizeDoc = CSize(m_Image.GetWidthPixel(), m_Image.GetHeight());

	if (m_pPalette != NULL)									// 判断调色板是否为空
	{
		delete m_pPalette;									// 删除调色板对象
		m_pPalette = NULL;									// 重置调色板为空
	}

	CClientDC dc(NULL);										// 不是调色板显示模式，则直接返回
	if ((dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE) == 0)
		return;

	m_pPalette = new CPalette;								// 创建新调色板
	int nEntries = m_Image.GetColorTableEntriesNum();

	if (nEntries == 0)
		return;

	LOGPALETTE* lpPal = (LOGPALETTE*) new BYTE[sizeof(LOGPALETTE)
		+ (sizeof(PALETTEENTRY) * (nEntries - 1))];

	lpPal->palVersion = 0x300;								// 设置版本号

	lpPal->palNumEntries = (WORD)nEntries;
	RGBQUAD* pPal = (RGBQUAD*)(m_Image.GetColorTable());	// 设置颜色数目
	int i;

	for (i = 0; i < nEntries; i++)							// 创建调色板
	{
		lpPal->palPalEntry[i].peRed = pPal[i].rgbRed;		// 读取红色分量
		lpPal->palPalEntry[i].peGreen = pPal[i].rgbGreen;	// 读取绿色分量
		lpPal->palPalEntry[i].peBlue = pPal[i].rgbBlue;		// 读取蓝色分量
		lpPal->palPalEntry[i].peFlags = 0;					// 保留位
	}
	m_pPalette->CreatePalette(lpPal);						// 按照逻辑调色板创建调色板，并返回指针
	delete[] lpPal;
}


BOOL CDIPDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	DeleteContents();
	BeginWaitCursor();										// 更改光标形状
	if (!m_Image.AttachFromFile(lpszPathName))				// 读取图像并附加到m_Image上
	{
		EndWaitCursor();
		AfxMessageBox(L"打开文件时出错!请确保正确的位图(*.bmp)文件类型。");
		return FALSE;
	}
	EndWaitCursor();										// 恢复光标形状
	if (!m_Image.m_lpData)									// 判断读取成功否
	{
		CString strMsg;
		strMsg = L"读取图像时出错！可能是不支持该类型的图像文件！";
		MessageBox(NULL, strMsg, L"系统提示",
			MB_ICONINFORMATION | MB_OK);					// 提示出错
		return FALSE;										// 返回FALSE
	}

	Init();													// 对图像的尺寸和调色板信息进行初始化
	SetPathName(lpszPathName);								// 设置文件名称
	m_OImage = m_Image;										// 拷贝当前m_Image到m_OImage
	SetModifiedFlag(FALSE);									// 初始化胀标记为FALSE
	return TRUE;											// 返回TRUE
}

void CDIPDoc::OnFileReopen()							// 重新打开图像，放弃所有修改
{
	if (IsModified())										// 判断当前图像是否已经被改动
		if (MessageBox(NULL,								// 提示用户该操作将丢失所有当前的修改
			L"重新打开图像将丢失所有改动！是否继续？",
			L"系统提示", MB_ICONQUESTION | MB_YESNO) == IDNO)
			return;											// 用户取消操作，直接返回

	CString strPathName;
	strPathName = GetPathName();							// 获取当前文件路径
	BeginWaitCursor();										// 更改光标形状
	if (!m_Image.AttachFromFile(strPathName))
	{
		EndWaitCursor();
		AfxMessageBox(L"打开文件时出错!请确保正确的位图(*.bmp)文件类型。");
		return;
	}

	if (!m_Image.m_lpData)									// 判断读取成功否
	{
		CString strMsg;										// 失败，可能非BMP格式
		strMsg = L"读取图像时出错！可能是不支持该类型的图像文件！";
		MessageBox(NULL, strMsg, L"系统提示",
			MB_ICONINFORMATION | MB_OK);					// 提示出错

		return;												// 返回
	}
	Init();													//对图像的尺寸和调色板信息进行初始化
	SetModifiedFlag(FALSE);									// 初始化修改标识为FALSE
	UpdateAllViews(NULL);									// 刷新
	EndWaitCursor();										// 恢复光标形状
	return;													// 返回
}

BOOL CDIPDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if (!m_Image.SaveToFile(lpszPathName))
	{
		CString strMsg;
		strMsg = L"无法保存BMP图像！";

		MessageBox(NULL, strMsg, L"系统提示",
			MB_ICONINFORMATION | MB_OK);					// 提示出错
		return FALSE;
	}
	EndWaitCursor();										// 恢复光标形状
	SetModifiedFlag(FALSE);									// 重置胀标记为FALSE
	return TRUE;
}