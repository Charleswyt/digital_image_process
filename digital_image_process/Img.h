#ifndef __GRAY_H__
#define __GRAY_H__

#include "math.h"

// 处理图像的类

// 在计算图像大小时，采用公式：biSizeImage = biWidth' × biHeight。
// 是biWidth'，而不是biWidth，这里的biWidth'必须是4的整倍数，表示
// 大于或等于biWidth的，离4最近的整倍数。WIDTHBYTES就是用来计算
// biWidth'
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

//  0 -> 255  黑->白

class CImg
{
public:
	CImg();												// 构造函数
	CImg(CImg& gray);									// Copy构造函数
	// 重载“=”操作符来创建新的对象
	void operator = (CImg& gray);						// 图像赋值
	BOOL operator == (CImg& gray) const;				// 判断2幅图像是否相同
	CImg operator & (CImg& gray);						// 图像按位与
	CImg operator | (CImg& gray);						// 图像按位或
	CImg operator + (CImg gray);						// 图像相加
	CImg operator - (CImg& gray);						// 图像减法
	CImg operator ! ();									// 图像反色
	virtual ~CImg();									// 析构函数

public:
	BOOL IsValidate() const								// 判断位图是否有效
	{
		return m_pBMIH != NULL;
	}

	void InitPixels(BYTE color);						// 将所有像素的值初始化为color
	BOOL AttachFromFile(LPCTSTR lpcPathName);			// 从文件加载位图
	BOOL AttachFromFile(CFile &file);
	BOOL SaveToFile(LPCTSTR lpcPathName);				// 将位图保存到文件
	BOOL SaveToFile(CFile &file);
	BOOL Draw(CDC* pDC);								// 在DC上绘制修改后的图
	BOOL Draw(CDC* pDC, CRect rt);
	BOOL Draw2(CDC* pDC);								// 在DC上绘制原始图像
	BOOL Draw_originalPic(CDC* pDC);					// 在DC上绘制原图
	BOOL Draw_originalPic(CDC* pDC, CRect rt);
	void SetPixel(int x, int y, COLORREF color);		// 设置像素的值
	COLORREF GetPixel(int x, int y) const;				// 获取像素的值
	BYTE GetGray(int x, int y) const;					// 获取灰度值
	int GetWidthByte() const;							// 获取一行的字节数
	int GetWidthPixel() const;							// 获取一行的像素数
	int GetHeight() const;								// 获取高度
	void ImResize(int nHeight, int nWidth);				// 改变位图的尺寸
public:
	// 绘画函数
	void Line(POINT ptStart, POINT ptEnd);				// 绘制直线
	void Line(POINT ptStart, int nLen, int nWide, BOOL bHor);
	void Rectangle(int x, int y, int r = 5);			// 绘制矩形
	void Rectangle(POINT ptLT, int r = 5);
	void Rectangle(POINT ptLT, POINT ptRB);
	void Circle(int x, int y, int r = 5) {};

public:
	BOOL IsBinaryImg() const;							// 判断是否是二值图像
	BOOL IsIndexedImg() const;							// 判断是否是索引图像
	bool Index2Gray();									// 256色索引图像转灰度图像
	LPVOID GetColorTable() const
	{
		return m_lpvColorTable;
	}
	int GetColorTableEntriesNum() const
	{
		return m_nColorTableEntries;
	}

private:
	void CleanUp();

public:
	// 文件数据
	BITMAPINFOHEADER* m_pBMIH;
	LPBYTE*  m_lpData;
protected:
	int m_nColorTableEntries;
	LPVOID m_lpvColorTable;
};

/**************************************************
	inline int CImg::GetWidthByte()

	功能：
	返回CImg实例中的图像每行占用的字节数
	限制：
	无

	参数：
	无
	返回值：
	int类型，返回图像每行占用的字节数
***************************************************/
inline int CImg::GetWidthByte() const
{
	return WIDTHBYTES((m_pBMIH->biWidth) * m_pBMIH->biBitCount);
}

/**************************************************
	inline int CImg::GetWidthPixel()

	功能：
	返回CImg实例中的图像每行的像素数目，即横向分辨率或宽度
	限制：
	无

	参数：
	无
	返回值：
	int类型，返回图像每行的像素数目
***************************************************/
inline int CImg::GetWidthPixel() const
{
	return m_pBMIH->biWidth;
}

/**************************************************
	inline int CImg::GetHeight()

	功能：
	返回CImg实例中的图像每列的像素数目，即纵向分辨率或高度
	限制：
	无

	参数：
	无
	返回值：
	int类型，返回图像每列的像素数目
***************************************************/
inline int CImg::GetHeight() const
{
	return m_pBMIH->biHeight;
}

/**************************************************
	inline BYTE CImg::GetGray(int x, int y)

	功能：
	返回指定坐标位置像素的灰度值

	参数：
	int x, int y
		指定的像素横、纵坐标值
	返回值：
	给定像素位置的灰度值
***************************************************/
inline BYTE CImg::GetGray(int x, int y) const
{
	COLORREF ref = GetPixel(x, y);
	BYTE r, g, b, byte;
	r = GetRValue(ref);
	g = GetGValue(ref);
	b = GetBValue(ref);

	if (r == g && r == b)
		return r;

	double dGray = (0.299 * r + 0.587 * g + 0.114 * b);
	byte = (int)dGray;			// 灰度化
	return byte;
}

/**************************************************
	inline COLORREF CImg::GetPixel(int x, int y)

	功能：
	返回指定坐标位置像素的颜色值

	参数：
	int x, int y
		指定像素位置的坐标
	返回值：
	COLERREF类型，返回用RGB形式表示的指定位置的颜色值
***************************************************/
inline COLORREF CImg::GetPixel(int x, int y) const
{
	if (m_pBMIH->biBitCount == 8)						 // 256色图
	{
		BYTE byte = m_lpData[m_pBMIH->biHeight - y - 1][x];
		return RGB(byte, byte, byte);
	}
	else
		if (m_pBMIH->biBitCount == 1)					// 单色图
		{
			BYTE ret = (1 << (7 - x % 8) & m_lpData[m_pBMIH->biHeight - y - 1][x / 8]);

			RGBQUAD* p = (RGBQUAD*)m_lpvColorTable;		// 0代表黑

			if (p[0].rgbBlue != 0)
				ret = !ret;

			if (ret)
				return RGB(255, 255, 255); // 白色

			else
				return RGB(0, 0, 0);       // 黑色
		}

		else
			if (m_pBMIH->biBitCount == 24) // 真彩图
			{
				COLORREF color = RGB(m_lpData[m_pBMIH->biHeight - y - 1][x * 3 + 2],
					m_lpData[m_pBMIH->biHeight - y - 1][x * 3 + 1],
					m_lpData[m_pBMIH->biHeight - y - 1][x * 3]);
				return color;
			}

			else
			{
				throw "not support now";
				return 0;
			}
}

inline BOOL CImg::IsBinaryImg() const
{
	int i, j;

	for (i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (j = 0; j < m_pBMIH->biWidth; j++)
		{
			if ((GetGray(j, i) != 0) && (GetGray(j, i) != 255)) //存在0和255之外的灰度值
				return FALSE;
		}//for j
	}//for i

	return TRUE;
}

inline BOOL CImg::IsIndexedImg() const
{
	if ((m_lpvColorTable != NULL) && (m_nColorTableEntries != 0))
		return true;
	else
		return false;
}
#endif // __GRAY_H__