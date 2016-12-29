#include "stdafx.h"

#include "ImgProcess.h"

#include <vector>

#include <queue>
#include <math.h>

#define _EdgeAll 0;
#define _EdgeH 1;
#define _EdgeV 2;
#define _EdgeCW 3;
#define _EdgeCCW 4;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/* 常用模板数组 */

// 平均平滑  1/9
double Template_Smooth_Avg[9] =
{ 1, 1, 1,
  1, 1, 1,
  1, 1, 1 };

// Gauss平滑  1/16
double Template_Smooth_Gauss[9] =
{ 1, 2, 1,
  2, 4, 2,
  1, 2, 1 };

// Sobel垂直边缘检测
double Template_HSobel[9] =
{ -1, 0, 1,
  -2, 0, 2,
  -1 ,0, 1 };

// Sobel水平边缘检测
double Template_VSobel[9] =
{ -1, -2, -1,
   0, 0, 0,
   1, 2, 1 };

// LOG边缘检测
double Template_Log[25] =
{ 0,  0, -1,  0,  0,
  0, -1, -2, -1,  0,
 -1, -2, 16, -2, -1,
  0, -1, -2, -1,  0,
  0,  0, -1,  0,  0 };

//Sigma = 2，较平滑
double Template_Log1[25] =
{ 0.0448, 0.0468,  0.0564, 0.0468, 0.0448,
  0.0468, 0.3167,  0.7146, 0.3167, 0.0468,
  0.0564, 0.7146, -4.9048, 0.7146, 0.0564,
  0.0468, 0.3167,  0.7146, 0.3167, 0.0468,
  0.0448, 0.0468,  0.0564, 0.0468, 0.0448
};

// Laplacian边缘检测
double Template_Laplacian1[9] =
{ 0, -1,  0,
 -1,  4, -1,
  0, -1,  0
};

double Template_Laplacian2[9] =
{ -1, -1, -1,
  -1,  8, -1,
  -1, -1, -1
};

// 带参构造函数
CImgProcess::CImgProcess()
{
	m_nBasePt = 4;
}

CImgProcess::~CImgProcess()
{

}

void CImgProcess::SimpThreshold(CImgProcess *pTo, int iThreshold)
{
	Threshold(pTo, iThreshold);		//阈值分割
}

void CImgProcess::AutoThreshold(CImgProcess *pTo)
{
	int nDiffGray;
	int nThres = DetectThreshold(100, nDiffGray);//取得分割阈值，最大迭代次数为100

	Threshold(pTo, nThres); //阈值分割
}

void CImgProcess::Erode(CImgProcess *pTo, int se[3][3])
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;				//图像循环变量
	int k, l;				//结构元素循环变量

	BOOL bMatch;			//结构元素是否与局部图像匹配

	pTo->InitPixels(255);	//清空目标输出图像

	//逐行扫描图像，为防止访问越界，四周留出一个像素宽的空边
	for (i = 1; i < nHeight - 1; i++)
	{
		for (j = 1; j < nWidth - 1; j++)
		{
			//由于使用的是3*3的结构元素，为防止越界，不处理最上和最下的两行像素以及最左和最右的两列像素
			bMatch = true;
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					if (se[k][l] == -1)		//不关心
						continue;

					if (se[k][l] == 1)		//前景
					{
						if (GetGray(j - 1 + l, i - 1 + k) != 0)
						{
							bMatch = false;
							break;
						}
					}
					else if (se[k][l] == 0) //背景
					{
						if (GetGray(j - 1 + l, i - 1 + k) != 255)
						{
							bMatch = false;
							break;
						}
					}
					else
					{
						AfxMessageBox(L"结构元素含有非法值！请检查后重新设定。");
						return;
					}
				}//for l
			}//for k

			if (bMatch)
				pTo->SetPixel(j, i, RGB(0, 0, 0));
		}// for j
	}// for i
}

void CImgProcess::Dilate(CImgProcess *pTo, int se[3][3])
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i, j;		//图像循环变量
	int k, l;		//结构元素循环变量

	//计算se关于中心的对称集
	int nTmp;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3 - i; j++)
		{
			nTmp = se[i][j];
			se[i][j] = se[2 - i][2 - j];
			se[2 - i][2 - j] = nTmp;
		}
	}
	pTo->InitPixels(255); //清空目标输出图像

	//逐行扫描图像，为防止访问越界，四周留出一个像素宽的空边
	for (i = 1; i < nHeight - 1; i++)
	{
		for (j = 1; j < nWidth - 1; j++)
		{
			//由于使用的是3*3的结构元素，为防止越界，不处理最上和最下的两行像素以及最左和最右的两列像素
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					if (se[k][l] == -1) // 不关心
						continue;

					if (se[k][l] == 1)
					{
						if (GetGray(j - 1 + l, i - 1 + k) == 0)
						{
							//原图中对应结构元素的局部区域有一点为1，就将目标图像对应于结构元素中心的像素置0
							pTo->SetPixel(j, i, RGB(0, 0, 0));
							break;
						}
					}
					else
					{
						AfxMessageBox(L"结构元素含有非法值！请检查后重新设定。");
						return;
					}
				}//for l
			}//for k
		}// for j
	}// for i
}

void CImgProcess::Open(CImgProcess* pTo, int se[3][3])
{
	pTo->InitPixels(255);
	Erode(pTo, se);
	*this = *pTo;
	Dilate(pTo, se);
}

void CImgProcess::Close(CImgProcess* pTo, int se[3][3])
{
	pTo->InitPixels(255);
	Dilate(pTo, se);
	*this = *pTo;
	Erode(pTo, se);
}

void CImgProcess::Convex(CImgProcess* pTo, BOOL bConstrain)
{
	//计算凸壳需要的4个结构元素
	/*
	se1 = 1 -1 -1	se2 = 1  1  1	se3 = -1 -1  1	se4 = -1 -1 -1
		  1	 0 -1		 -1  0 -1		  -1  0  1		  -1  0 -1
		  1 -1  1		 -1 -1 -1		  -1 -1  1		   1  1  1
	*/
	int se1[3][3] = { { 1, -1, -1 },{ 1, 0, -1 },{ 1, -1, -1 } }; //弥补右侧的凸缺
	int se2[3][3] = { { 1, 1, 1 },{ -1, 0, -1 },{ -1, -1, -1 } }; //弥补下侧的凸缺
	int se3[3][3] = { { -1, -1, 1 },{ -1, 0, 1 },{ -1, -1, 1 } }; //弥补左侧的凸缺
	int se4[3][3] = { { -1, -1, -1 },{ -1, 0, -1 },{ 1, 1, 1 } }; //弥补上侧的凸缺

	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i, j;						//图像循环变量
	pTo->InitPixels(255);			//清空目标输出图像

	// 采用第1个结构元素
	CImgProcess tmpImg1 = *this;	//暂存上一次的运算结果

	while (true)
	{
		tmpImg1.Erode(pTo, se1);	//不完全背景包围的击中击不中变换
		*pTo = *pTo | tmpImg1;

		if (tmpImg1 == *pTo)
			break;					//算法收敛终止

		tmpImg1 = *pTo;
	}

	// 采用第2个结构元素
	CImgProcess tmpImg2 = *this;	//暂存上一次的运算结果
	while (true)
	{
		tmpImg2.Erode(pTo, se2);	//不完全背景包围的击中击不中变换
		*pTo = *pTo | tmpImg2;

		if (tmpImg2 == *pTo)
			break;					//算法收敛终止

		tmpImg2 = *pTo;
	}

	// 采用第3个结构元素
	CImgProcess tmpImg3 = *this;	//暂存上一次的运算结果

	while (true)
	{
		tmpImg3.Erode(pTo, se3);	//不完全背景包围的击中击不中变换
		*pTo = *pTo | tmpImg3;

		if (tmpImg3 == *pTo)
			break;					//算法收敛终止
		tmpImg3 = *pTo;
	}

	// 采用第4个结构元素
	CImgProcess tmpImg4 = *this;	//暂存上一次的运算结果

	while (true)
	{
		tmpImg4.Erode(pTo, se4);	//不完全背景包围的击中击不中变换
		*pTo = *pTo | tmpImg4;

		if (tmpImg4 == *pTo)
			break;					//算法收敛终止
		tmpImg4 = *pTo;
	}

	// 计算4次运算结果的并集
	pTo->InitPixels(255);

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if ((tmpImg1.GetGray(j, i) == 0) || (tmpImg2.GetGray(j, i) == 0)
				|| (tmpImg3.GetGray(j, i) == 0) || (tmpImg4.GetGray(j, i) == 0))
				pTo->SetPixel(j, i, RGB(0, 0, 0));
		}
	}

	// 需要限制凸壳的生长
	// 找到原图像中物体的范围（包含物体的最小矩形）
	int nTop = nHeight;
	int nBottom = 0;
	int nLeft = nWidth;
	int nRight = 0;
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (GetGray(j, i) == 0)
			{
				if (i < nTop)
					nTop = i;
				if (i > nBottom)
					nBottom = i;
				if (j < nLeft)
					nLeft = j;
				if (j > nRight)
					nRight = j;
			}
		}
	}

	if (bConstrain)
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				if ((i < nTop) || (i > nBottom) || (j < nLeft) || (j > nRight))
					pTo->SetPixel(j, i, RGB(255, 255, 255));
			}
		}
	}//if(bConstrain)

}

void CImgProcess::GrayDilate(CImgProcess* pTo, int nTempH, int nTempW,
	int nTempMY, int nTempMX, int** se)
{
	// 循环变量
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (i = nTempMY; i < nHeight - nTempH + nTempMY + 1; i++)
	{
		for (j = nTempMX; j < nWidth - nTempW + nTempMX + 1; j++)
		{
			BYTE maxVal = 0; //局部最大值
			for (k = 0; k < nTempH; k++)
			{
				for (l = 0; l < nTempW; l++)
				{
					if (se[k][l] == 1)
					{
						// 图像第i - nTempMY + k行，第j - nTempMX + l个象素的灰度
						BYTE gray = GetGray(j - nTempMX + l, i - nTempMY + k);

						//求局部最大值
						if (gray > maxVal)
							maxVal = gray;
					}
				}//l
			}//k
			pTo->SetPixel(j, i, RGB(maxVal, maxVal, maxVal));
		}// for j
	}//for i
}

void CImgProcess::GrayErode(CImgProcess* pTo, int nTempH, int nTempW,
	int nTempMY, int nTempMX, int** se)
{
	// 循环变量
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (i = nTempMY; i < nHeight - nTempH + nTempMY + 1; i++)
	{
		for (j = nTempMX; j < nWidth - nTempW + nTempMX + 1; j++)
		{
			BYTE minVal = 255;				//局部最小值
			for (k = 0; k < nTempH; k++)
			{
				for (l = 0; l < nTempW; l++)
				{
					if (se[k][l] == 1)
					{
						// 图像第i - nTempMY + k行，第j - nTempMX + l个象素的灰度
						BYTE gray = GetGray(j - nTempMX + l, i - nTempMY + k);
						//求局部最大值
						if (gray < minVal)
							minVal = gray;
					}
				}//l
			}//k
			pTo->SetPixel(j, i, RGB(minVal, minVal, minVal));
		}// for j
	}//for i
}

void CImgProcess::GrayOpen(CImgProcess* pTo, int nTempH, int nTempW, int nTempMY, int nTempMX, int** se)
{
	pTo->InitPixels(255);

	GrayErode(pTo, nTempH, nTempW, nTempMY, nTempMX, se);

	CImgProcess tmpImg = *pTo; //暂存腐蚀图像

	tmpImg.GrayDilate(pTo, nTempH, nTempW, nTempMY, nTempMX, se);
}

void CImgProcess::GrayClose(CImgProcess* pTo, int nTempH, int nTempW,
	int nTempMY, int nTempMX, int** se)
{
	pTo->InitPixels(255);
	GrayDilate(pTo, nTempH, nTempW, nTempMY, nTempMX, se);
	CImgProcess tmpImg = *pTo; //暂存膨胀图像
	tmpImg.GrayErode(pTo, nTempH, nTempW, nTempMY, nTempMX, se);
}

void CImgProcess::Tophat(CImgProcess* pTo, int nTempH, int nTempW, int nTempMY, int nTempMX, int** se)
{
	GrayOpen(pTo, nTempH, nTempW, nTempMY, nTempMX, se);	//灰度开运算
	*pTo = (*this) - (*pTo);								//顶帽变换（原图像减去开运算图像）
}

void CImgProcess::Template(CImgProcess *pTo, int nTempH, int nTempW,
	int nTempMY, int nTempMX, double *pfArray, double fCoef)
{
	pTo->InitPixels(0); //目标图像初始化
	int i, j;			//循环变量

	//扫描图像进行模板操作
	for (i = nTempMY; i < GetHeight() - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < GetWidthPixel() - (nTempW - nTempMX) + 1; j++)
		{
			// (j,i)为中心点
			double fResult = 0;
			for (int k = 0; k < nTempH; k++)
			{
				for (int l = 0; l < nTempW; l++)
					fResult += GetGray(j + l - nTempMX, i + k - nTempMY) * pfArray[k * nTempW + l];
			}
			fResult *= fCoef;		// 乘以系数

			// 取正
			fResult = (double)fabs(fResult); //锐化时有可能出现负值

			BYTE byte;
			if (fResult > 255)
				byte = 255;
			else
				byte = fResult + 0.5; //四舍五入

			pTo->SetPixel(j, i, RGB(byte, byte, byte));
		}//for j
	}//for i
}

int CImgProcess::GetMeanValue(int * pAryGray, int nFilterLen)
{
	int i;
	int nMeanValue;
	int nSum = 0;															// 中间变量

	for (i = 0; i < nFilterLen; i++)										// 求和
			nSum += pAryGray[i];

	nMeanValue = nSum / nFilterLen;											// 计算均值
	return nMeanValue;														// 返回均值
}

int CImgProcess::GetGeoMeanValue(int * pAryGray, int nFilterLen)
{
	int i;
	double dGeoMeanValue;
	int iGeoMeanValue;
	double dProduct = 1;													// 中间变量

	for (i = 0; i < nFilterLen; i++)										// 求乘积
		dProduct *= pAryGray[i];

	dGeoMeanValue = pow(dProduct, 1.0/nFilterLen);							// 计算几何均值
	iGeoMeanValue = dGeoMeanValue + 0.5;				
	return iGeoMeanValue;													// 返回几何均值
}

int CImgProcess::GetHarmonicMeanValue(int * pAryGray, int nFilterLen)
{
	int i;
	double dHarmonicMeanValue;
	int iHarmonicMeanValue;
	double dSum = 0.0;														// 中间变量
	double dTemp;

	for (i = 0; i < nFilterLen; i++)										// 求和
	{
		dTemp = 1.0 / pAryGray[i];
		dSum += dTemp;
	}

	dHarmonicMeanValue = nFilterLen / dSum;									// 计算谐波均值
	iHarmonicMeanValue = dHarmonicMeanValue + 0.5;

	return iHarmonicMeanValue;												// 返回谐波均值
}

int CImgProcess::GetInvHarmonicMeanValue(int * pAryGray, int nFilterLen, int Q)
{
	int i;
	double dInvHarmonicMeanValue;
	int iInvHarmonicMeanValue;
	double dSum1, dSum2;													// 中间变量
	double dTemp;

	dSum1 = 0.0; dSum2 = 0.0;
	for (i = 0; i < nFilterLen; i++)										// 求和
	{
		dSum1 += pow(pAryGray[i], Q + 1);
		dSum2 += pow(pAryGray[i], Q);
	}

	dInvHarmonicMeanValue = dSum1 / dSum2;									// 计算谐波均值
	iInvHarmonicMeanValue = dInvHarmonicMeanValue + 0.5;

	return iInvHarmonicMeanValue;											// 返回谐波均值
}

int CImgProcess::GetAlphaMeanValue(int * pAryGray, int nFilterLen, int d)
{
	int i, j;																// 循环变量
	int iSum = 0;															// 修正模板和值
	int iTemp;																// 用于交换的中间变量
	int iAlphaMeanValue;													// 修正阿尔法均值

	for (i = 0; i < nFilterLen - 1; i++)									// 排序
	{
		for (j = 0; j < nFilterLen - i - 1; j++)
		{
			if (pAryGray[j] > pAryGray[j + 1])
			{
				iTemp = pAryGray[i];
				pAryGray[i] = pAryGray[i + 1];
				pAryGray[i + 1] = iTemp;
			}
		}
	}

	for (i = d; i < nFilterLen - d; i++)
		iSum += pAryGray[i];
	
	iAlphaMeanValue = iSum / (nFilterLen - 2 * d);

	return iAlphaMeanValue;													// 返回谐波均值
}

int CImgProcess::GetGraySum(int * pAryGray, int nFilterLen)
{
	int i;
	int nMeanValue;
	int nSum = 0;															// 中间变量

	for (i = 0; i < nFilterLen; i++)										// 求和
		nSum += pAryGray[i];

	return nSum;															// 返回均值
}

double CImgProcess::GetGradientSum(double * pAryGradient, int nFilterLen)
{
	int i;
	double dSum = 0.0;														// 中间变量

	for (i = 0; i < nFilterLen; i++)										// 求和
		dSum += pAryGradient[i];

	return dSum;															// 返回和值
}

int CImgProcess::GetMidValue(int * pAryGray, int nFilterLen)
{
	int nMeanValue;

	nMeanValue = pAryGray[(nFilterLen + 1) / 2 - 1];						// 计算中间值
	return nMeanValue;														// 返回中间值
}

void CImgProcess::LowFilter1(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 邻域均值法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	pAryGray = new int[nFilterH * nFilterW];

	// 逐行扫描图像，进行领域均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetMeanValue(pAryGray, nFilterH * nFilterW);			// 通过排序获取均值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以算数均值作为响应		
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter2(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 简单加权平均法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 图像灰度、灰度均值和灰度和值
	int iGrayOutput;														// 灰度输出值
	int* pAryGray;															// 邻域像素灰度数组
	pAryGray = new int[nFilterH * nFilterW];								// 邻域像素灰度数组
	double pAryWeight[9] = { 0.025, 0.1, 0.025, 0.1, 0.5, 0.1, 
		0.025, 0.1, 0.025 };												// 权重
	
	// 逐行扫描图像，进行简单加权平均法
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k

				iGrayOutput = 0;
				for (k = 0; k < nFilterH; k++)									// 卷积计算
				{
					for (l = 0; l < nFilterW; l++)
					{
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						iGrayOutput += (pAryWeight[k * nFilterW + l] * nGray);
					}//l
				}//k

				pTo->SetPixel(j, i, RGB(iGrayOutput, iGrayOutput, iGrayOutput));
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter3(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 梯度倒数加权平均法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l, m;														// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nTempletLength, nMidLoc;											// 模板长度、模板中点位置
	int nGray, iGrayMid;													// 图像灰度、模板灰度中值
	int iTemp;																// 临时变量，用于存储两个像素的差
	int dGrayOutput;														// 灰度输出值
	int* pAryGray;															// 邻域像素灰度数组
	double *pAryGrandient;													// 邻域像素梯度数组
	double* pAryWeight;														// 权重数组
	double dGrandientSum;													// 邻域像素梯度之和
	pAryGray = new int[nFilterH * nFilterW];								// 邻域像素灰度数组
	pAryGrandient = new double[nFilterH * nFilterW];						// 邻域像素梯度数组
	pAryWeight = new double[nFilterH * nFilterW];							// 权重数组

	nTempletLength = nFilterH * nFilterW;									// 模板长度
	nMidLoc = (nTempletLength + 1) / 2 - 1;									// 模板中点位置

	// 逐行扫描图像，进行梯度倒数加权平均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k

				iGrayMid = GetMidValue(pAryGray, nTempletLength);				// 获取中点灰度

				for (m = 0; m < nTempletLength; m++)
				{
					iTemp = abs(pAryGray[m] - iGrayMid);						// 计算各点像素值的梯度
					if (m == nMidLoc)											// 计算梯度的倒数
						pAryGrandient[m] = 0.0;
					else if (m != nMidLoc && iTemp == 0)
						pAryGrandient[m] = 0;
					else
						pAryGrandient[m] = 1.0 / iTemp;
				}

				dGrandientSum = GetGradientSum(pAryGrandient, nTempletLength);	// 取得梯度倒数之和

				dGrayOutput = 0.0;
				for (m = 0; m < nTempletLength; m++)							// 取得模板窗口内各点的权重并计算输出像素值
				{
					if (m == 4)
						pAryWeight[m] = 0.5;
					else
						pAryWeight[m] = pAryGrandient[m] / (2.0 * dGrandientSum);
					dGrayOutput += pAryWeight[m] * pAryGray[m];
				}
				int iGrayOutput = dGrayOutput + 0.5;

				if (iGrayOutput < 0)
					iGrayOutput = 0;
				if (iGrayOutput > 255)
					iGrayOutput = 255;

				pTo->SetPixel(j, i, RGB(iGrayOutput, iGrayOutput, iGrayOutput));
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
	delete[] pAryGrandient;
	delete[] pAryWeight;
}

void CImgProcess::LowFilter4(CImgProcess * pTo, int nFilterH, int nFilterW, 
	int nFilterMY, int nFilterMX, int nThreshold)
{
	// 超限邻域均值法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray, iGrayMean, iGrayMid;											// 图像灰度和灰度均值和中点值
	int* pAryGray;															// 邻域像素数组
	int iTemplete = nFilterH * nFilterW;									// 模板灰度长度
	pAryGray = new int[iTemplete];

	// 逐行扫描图像，进行超限邻域均值法
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				iGrayMean = GetMeanValue(pAryGray, iTemplete);					// 获取灰度均值
				iGrayMid = GetMidValue(pAryGray, iTemplete);					// 获取模板灰度中点值

				if (nGray - iGrayMean > nThreshold)
					pTo->SetPixel(j, i, RGB(iGrayMean, iGrayMean, iGrayMean));	// 输出模板灰度均值
				else
					pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));				// 输出当前灰度值
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter5(CImgProcess * pTo, int nFilterH, int nFilterW, 
	int nFilterMY, int nFilterMX, int iThreshold, int iCnt)
{
	// 噪声门限法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l, m;														// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray, iGrayMid, iGrayMean;											// 图像灰度、中点值和均值
	int iCount;																// 误差计数器
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行噪声门限均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k

				iGrayMid  = GetMidValue(pAryGray, nFilterH * nFilterW);			// 获取中点值
				iGrayMean = GetMeanValue(pAryGray, nFilterH * nFilterW);		// 获取平均值

				iCount = 0;
				for (m = 0; m < nTempleteLength; m++)
					if (pAryGray[m] - iGrayMid > iThreshold)
						iCount++;

				if (iCount < iCnt)
					pTo->SetPixel(j, i, RGB(iGrayMid, iGrayMid, iGrayMid));		// 低于门限值填充中间值
				else
					pTo->SetPixel(j, i, RGB(iGrayMean, iGrayMean, iGrayMean));	// 高于门限值填充平均值
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter6(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 几何均值法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行几何均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetGeoMeanValue(pAryGray, nTempleteLength);				// 通过排序获取几何均值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以几何均值法作为响应		
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter7(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 谐波均值法
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行谐波均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetHarmonicMeanValue(pAryGray, nTempleteLength);		// 通过排序获取谐波均值

				if (nGray < 0)
					nGray = 0;
				if (nGray > 255)
					nGray = 255;

				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以谐波均值作为响应
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::LowFilter8(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX, int Q)
{
	// 逆谐波均值滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行逆谐波均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetInvHarmonicMeanValue(pAryGray, nFilterH * nFilterW, Q);	// 通过排序获取逆谐波均值

				if (nGray < 0)
					nGray = 0;
				if (nGray > 255)
					nGray = 255;

				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以逆谐波均值作为响应	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}
	
	delete[] pAryGray;
}

void CImgProcess::LowFilter9(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX, int d)
{
	// 修正阿尔法均值滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，修正阿尔法均值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetAlphaMeanValue(pAryGray, nFilterH * nFilterW, d);	// 通过排序获取阿尔法均值

				if (nGray < 0)
					nGray = 0;
				if (nGray > 255)
					nGray = 255;

				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以阿尔法均值作为响应
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}
	delete[] pAryGray;
}

void CImgProcess::MidFilter(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 中点值滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 灰度值
	int* pAryGray;															// 邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，修正中点值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetMidValue(pAryGray, nFilterH * nFilterW);				// 通过排序获取中点值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以中点值作为响应	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::HighFilter1(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 基本高通滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 图像灰度、灰度均值和灰度和值
	int iGrayOutput;														// 灰度输出值
	int* pAryGray;															// 邻域像素灰度数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 模板
	int pAryWeight3[9] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };				// 3*3卷积模板
	int pAryWeight5[25] = { -1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,8,1,-1,
	-1,1,1,1,-1,-1,-1,-1,-1 };												// 5*5卷积模板

	// 逐行扫描图像，基本高通滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				iGrayOutput = 0;
				if (nFilterH == 3)
				{
					for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
					{
						for (l = 0; l < nFilterW; l++)
						{
							//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
							nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
							iGrayOutput += (pAryWeight3[k * nFilterW + l] * nGray);
						}//l
					}//k
				}

				if (nFilterH == 5)
				{
					for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
					{
						for (l = 0; l < nFilterW; l++)
						{
							//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
							nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
							iGrayOutput += (pAryWeight5[k * nFilterW + l] * nGray);
						}//l
					}//k
				}
				if (iGrayOutput < 0)
					iGrayOutput = 0;
				if (iGrayOutput > 255)
					iGrayOutput = 255;

				pTo->SetPixel(j, i, RGB(iGrayOutput, iGrayOutput, iGrayOutput));
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(0, 0, 0));						// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::HighFilter2(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX, double dGain)
{
	// 高增益滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 图像灰度、灰度均值和灰度和值
	int iGrayOutput;														// 灰度输出值
	int* pAryGray;															// 邻域像素灰度数组
	int nTempleteLength = nFilterH * nFilterW;								// 模板长度
	pAryGray = new int[nTempleteLength];

	// 模板
	int pAryWeight3[9] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };				// 3*3卷积模板
	int pAryWeight5[25] = { -1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,8,1,-1,
		-1,1,1,1,-1,-1,-1,-1,-1 };											// 5*5卷积模板

																			// 逐行扫描图像，高增益滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				iGrayOutput = 0;
				if (nFilterH == 3)
				{
					for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
					{
						for (l = 0; l < nFilterW; l++)
						{
							//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
							nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
							iGrayOutput += (pAryWeight3[k * nFilterW + l] * nGray);
						}//l
					}//k
				}

				if (nFilterH == 5)
				{
					for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
					{
						for (l = 0; l < nFilterW; l++)
						{
							//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
							nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
							iGrayOutput += (pAryWeight5[k * nFilterW + l] * nGray);
						}//l
					}//k
				}

				if (iGrayOutput < 0)
					iGrayOutput = 0;
				if (iGrayOutput > 255)
					iGrayOutput = 255;

				nGray = GetGray(j, i);
				iGrayOutput = (dGain - 1) * nGray + iGrayOutput;
				pTo->SetPixel(j, i, RGB(0, 0, 0));
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

int CImgProcess::GetMedianValue(int * pAryGray, int nFilterLen)
{
	int i, j;
	int nMedianValue;
	int nTemp; //中间变量

	//排序
	for (j = 0; j < nFilterLen - 1; j++)
	{
		for (i = 0; i < nFilterLen - j - 1; i++)
		{
			if (pAryGray[i] > pAryGray[i + 1])
			{
				// 交换位置
				nTemp = pAryGray[i];
				pAryGray[i] = pAryGray[i + 1];
				pAryGray[i + 1] = nTemp;
			}//if
		}//for i
	}//for j

	 // 计算中值
	if ((nFilterLen & 1) > 0)							// 数组有奇数个元素，返回中间一个元素
		nMedianValue = pAryGray[(nFilterLen + 1) / 2];
	else												// 数组有偶数个元素，返回中间两个元素平均值
		nMedianValue = (pAryGray[nFilterLen / 2] + pAryGray[nFilterLen / 2 + 1]) / 2;

	return nMedianValue;								// 返回中值
}

int CImgProcess::GetMaxValue(int * pAryGray, int nFilterLen)
{
	int i, j;
	int nMaxValue;
	int nTemp; //中间变量

	//排序
	for (j = 0; j < nFilterLen - 1; j++)
	{
		for (i = 0; i < nFilterLen - j - 1; i++)
		{
			if (pAryGray[i] > pAryGray[i + 1])
			{
				// 交换位置
				nTemp = pAryGray[i];
				pAryGray[i] = pAryGray[i + 1];
				pAryGray[i + 1] = nTemp;
			}//if
		}//for i
	}//for j

	nMaxValue = pAryGray[nFilterLen - 1];

	// 返回最小值
	return nMaxValue;
}

int CImgProcess::GetMinValue(int * pAryGray, int nFilterLen)
{
	int i, j;
	int nMinValue;
	int nTemp; //中间变量

	//排序
	for (j = 0; j < nFilterLen - 1; j++)
	{
		for (i = 0; i < nFilterLen - j - 1; i++)
		{
			if (pAryGray[i] > pAryGray[i + 1])
			{
				// 交换位置
				nTemp = pAryGray[i];
				pAryGray[i] = pAryGray[i + 1];
				pAryGray[i + 1] = nTemp;
			}//if
		}//for i
	}//for j

	 // 计算中值
	nMinValue = pAryGray[0];

	// 返回最小值
	return nMinValue;
}

void CImgProcess::MedianFilter(CImgProcess *pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	pTo->InitPixels(0); //初始化目标图像
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int nGray;
	int* pAryGray; //邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行中值滤波	
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetMedianValue(pAryGray, nTempleteLength);				// 通过排序获取中值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以中值作为响应	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::MaxFilter(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	pTo->InitPixels(0); //初始化目标图像
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int nGray;
	int* pAryGray; //邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行最大值滤波	
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetMaxValue(pAryGray, nTempleteLength);					// 通过排序获取最大值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以最大值作为响应	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::MinFilter(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	pTo->InitPixels(0); //初始化目标图像
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int nGray;
	int* pAryGray; //邻域像素数组
	int nTempleteLength = nFilterH * nFilterW;
	pAryGray = new int[nTempleteLength];

	// 逐行扫描图像，进行最小值滤波	
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取滤波器数组
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k
				nGray = GetMinValue(pAryGray, nTempleteLength);					// 通过排序获取最小值
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 以最小值作为响应	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::AdaptiveMedianFilter(CImgProcess *pTo, int nFilterH, int nFilterW,
	int nFilterMY, int nFilterMX)
{
	pTo->InitPixels(0);			//初始化目标图像
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int nGray;
	int* pAryGray;				//邻域像素数组
	pAryGray = new int[nFilterH * nFilterW];

	// 逐行扫描图像，进行自适应中值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				// 读取滤波器数组
				for (k = 0; k < nFilterH; k++)
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						// 保存象素值
						pAryGray[k * nFilterW + l] = nGray;
					}//l
				}//k

				nGray = GetMedianValue(pAryGray, nFilterH * nFilterW);		// 通过排序获取中值
																			// 判断当前像素是否是邻域的极大或极小值
				if ((GetGray(j, i) == pAryGray[0]) ||
					(GetGray(j, i) == pAryGray[nFilterH * nFilterW - 1]))
					pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));			// 以中值作为响应
				else
					pTo->SetPixel(j, i, GetGray(j, i));						// 不是极值则不改变原图像的值	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));				// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::FilterSobel(CImgProcess *pTo)
{
	CImgProcess img1, img2;
	img1 = *pTo;
	img2 = *pTo;
	Template(&img1, 3, 3, 1, 1, Template_HSobel, 1);
	Template(&img2, 3, 3, 1, 1, Template_VSobel, 1);
	*pTo = img1 + img2;
}

void CImgProcess::EnhanceFilter(CImgProcess *pTo, double dProportion, int nTempH, int nTempW,
	int nTempMY, int nTempMX, double *pfArray, double fCoef)
{
	int i, j;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	*pTo = *this; //目标图像初始化

	//GrayMat暂存按比例叠加图像（不能在CImg类对象中直接进行像素相加，因为相加的结果可能超出范围[0,255]）
	vector< vector<int> > GrayMat;
	vector<int> vecRow(nWidth, 0); //GrayMat中的一行（初始化为0）
	for (i = 0; i < nHeight; i++)
		GrayMat.push_back(vecRow);

	//锐化图像，输出带符号响应，并与原图像按比例叠加			
	for (i = nTempMY; i < GetHeight() - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < GetWidthPixel() - (nTempW - nTempMX) + 1; j++)
		{
			double fResult = 0;
			for (int k = 0; k < nTempH; k++)
				for (int l = 0; l < nTempW; l++)
					//计算加权和
					fResult += GetGray(j + l - nTempMX, i + k - nTempMY) * pfArray[k * nTempW + l];
			// 乘以系数
			fResult *= fCoef;

			//限制响应值范围
			if (fResult > 255)
				fResult = 255;
			if (fResult < -255)
				fResult = -255;
			GrayMat[i][j] = dProportion * GetGray(j, i) + fResult + 0.5;//求和，结果四舍五入
		}//for j
	}//for i

	int nMax = 0;//最大灰度和值
	int nMin = 65535; //最小灰度和值

	//统计最大、最小值
	for (i = nTempMY; i < GetHeight() - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < GetWidthPixel() - (nTempW - nTempMX) + 1; j++)
		{
			if (GrayMat[i][j] > nMax)
				nMax = GrayMat[i][j];
			if (GrayMat[i][j] < nMin)
				nMin = GrayMat[i][j];
		}// j
	}// i

	 //将GrayMat的取值范围重新归一化到[0, 255]
	int nSpan = nMax - nMin;
	for (i = nTempMY; i < GetHeight() - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j < GetWidthPixel() - (nTempW - nTempMX) + 1; j++)
		{
			BYTE bt;
			if (nSpan > 0)
				bt = (GrayMat[i][j] - nMin) * 255 / nSpan;
			else if (GrayMat[i][j] <= 255)
				bt = GrayMat[i][j];
			else
				bt = 255;
			pTo->SetPixel(j, i, RGB(bt, bt, bt));

		}// for j
	}// for i
}

void CImgProcess::EnhaGaussianF(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	// 高斯平滑滤波
	pTo->InitPixels(0);														// 初始化目标图像
	int i, j, k, l;															// 循环变量
	int nHeight = GetHeight();												// 图像高度
	int nWidth = GetWidthPixel();											// 图像宽度
	int nGray;																// 图像灰度、灰度均值和灰度和值
	int iGrayOutput;														// 灰度输出值
	double dGrayOutput;														// 中间变量
	int* pAryGray;															// 邻域像素灰度数组
	pAryGray = new int[nFilterH * nFilterW];								// 邻域像素灰度数组
	double pAryWeight[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };					// 权重

																			// 逐行扫描图像，进行简单加权平均法
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				for (k = 0; k < nFilterH; k++)									// 读取模板内各点的灰度值
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						pAryGray[k * nFilterW + l] = nGray;						// 保存象素值
					}//l
				}//k

				dGrayOutput = 0;
				for (k = 0; k < nFilterH; k++)									// 卷积计算
				{
					for (l = 0; l < nFilterW; l++)
					{
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						dGrayOutput += (pAryWeight[k * nFilterW + l] * nGray);
					}//l
				}//k

				iGrayOutput = int(dGrayOutput / 16 + 0.5);
				pTo->SetPixel(j, i, RGB(iGrayOutput, iGrayOutput, iGrayOutput));
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));					// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

void CImgProcess::EnhaAdaptiveSmooth(CImgProcess * pTo, int nFilterH, int nFilterW, int nFilterMY, int nFilterMX)
{
	pTo->InitPixels(0);			//初始化目标图像
	int i, j, k, l;
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int nGray;
	int* pAryGray;				//邻域像素数组
	pAryGray = new int[nFilterH * nFilterW];

	// 逐行扫描图像，进行自适应中值滤波
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (i >= nFilterMY && i < nHeight - nFilterH + nFilterMY + 1
				&& j >= nFilterMX && j < nWidth - nFilterW + nFilterMX + 1)
			{
				// 读取滤波器数组
				for (k = 0; k < nFilterH; k++)
				{
					for (l = 0; l < nFilterW; l++)
					{
						//原图像第i + k - nFilterMY行，第j + l - nFilterMX列的像素值
						nGray = GetGray(j + l - nFilterMX, i + k - nFilterMY);
						// 保存象素值
						pAryGray[k * nFilterW + l] = nGray;
					}//l
				}//k

				nGray = GetMeanValue(pAryGray, nFilterH * nFilterW);		// 通过排序获取均值
																			// 判断当前像素是否是邻域的极大或极小值
				if ((GetGray(j, i) == pAryGray[0]) ||
					(GetGray(j, i) == pAryGray[nFilterH * nFilterW - 1]))
					pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));			// 以均值作为响应
				else
					pTo->SetPixel(j, i, GetGray(j, i));						// 不是极值则不改变原图像的值	
			}
			else
			{
				nGray = GetGray(j, i);
				pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));				// 直接填入原始像素值
			}
		}
	}

	delete[] pAryGray;
}

int CImgProcess::DetectThreshold(int nMaxIter, int &nDiffRet)
{
	int nThreshold;
	nDiffRet = 0;
	int nHistogram[256] = { 0 };	// 直方图数组
	int i, j;
	BYTE bt;
	int nMin = 255;
	int nMax = 0;

	// 扫描图像,计算出最大、最小灰度和直方图
	for (j = 0; j < GetHeight(); j++)
	{
		for (i = 0; i < GetWidthPixel(); i++)
		{
			bt = GetGray(i, j);

			if (bt < nMin)
				nMin = bt;
			if (bt > nMax)
				nMax = bt;
			nHistogram[bt] ++;
		}
	}

	int nTotalGray = 0;						// 灰度值的和
	int nTotalPixel = 0;					// 像素数的和
	int nNewThreshold = (nMax + nMin) / 2;	// 初始阈值

	nDiffRet = nMax - nMin;

	if (nMax == nMin)
		nThreshold = nNewThreshold;
	else
	{
		nThreshold = 0;

		// 迭代开始,直到迭代次数达到100或新阈值与上一轮得到的阈值相等，迭代结束
		for (int nIterationTimes = 0; nThreshold != nNewThreshold && nIterationTimes < nMaxIter; nIterationTimes++)
		{
			nThreshold = nNewThreshold;
			nTotalGray = 0;
			nTotalPixel = 0;

			//计算图像中小于当前阈值部分的平均灰度
			for (i = nMin; i < nThreshold; i++)
			{
				nTotalGray += nHistogram[i] * i;
				nTotalPixel += nHistogram[i];
			}
			int nMean1GrayValue = nTotalGray / nTotalPixel;

			nTotalGray = 0;
			nTotalPixel = 0;

			//计算图像中大于当前阈值部分的平均灰度
			for (i = nThreshold + 1; i <= nMax; i++)
			{
				nTotalGray += nHistogram[i] * i;
				nTotalPixel += nHistogram[i];
			}
			int nMean2GrayValue = nTotalGray / nTotalPixel;

			nNewThreshold = (nMean1GrayValue + nMean2GrayValue) / 2; //计算出新的阈值
			nDiffRet = abs(nMean1GrayValue - nMean2GrayValue);
		}
	}

	return nThreshold;
}

void CImgProcess::Threshold(CImgProcess *pTo, BYTE bThre)
{
	int i, j;
	BYTE bt;
	for (j = 0; j < m_pBMIH->biHeight; j++)
	{
		for (i = 0; i < m_pBMIH->biWidth; i++)
		{
			bt = GetGray(i, j);
			if (bt < bThre)
				bt = 0;
			else
				bt = 255;

			pTo->SetPixel(i, j, RGB(bt, bt, bt));
		}
	}
}

struct SMaxValue
{
	int nValue;
	int nDist;
	int nAngle;
};

void CImgProcess::TraceBoundary(CImgProcess *pTo)
{
	pTo->InitPixels(255);//清空目标图像
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i;					//循环变量
	int j;
	POINT ptStart;			//起始边界点与当前边界点
	POINT ptCur;
	//搜索方向数组，{左下，下，右下，右，右上，上，左上，左}
	int Direction[8][2] = { { -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },
		{ -1,-1 },{ -1,0 } };
	int nCurDirect = 0;		//当前探查方向
	int xPos;
	int yPos;

	BOOL bAtStartPt;		//为true表示探查刚刚时开始，为了区别ptCur == ptStart的两种情况（一种开始，一种结束）
	//算法不处理边界上的点，将图像的四周的一圈边界置白
	for (i = 0; i < nHeight; i++)
	{
		SetPixel(0, i, RGB(255, 255, 255));
		SetPixel(nWidth - 1, i, RGB(255, 255, 255));
	}

	for (j = 0; j < nWidth; j++)
	{
		SetPixel(j, 0, RGB(255, 255, 255));
		SetPixel(j, nHeight - 1, RGB(255, 255, 255));
	}

	//逐行扫描
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			if (GetGray(j, i) == 0)//找到最左上的第一个边界点
			{
				ptStart.x = j;
				ptStart.y = i;

				ptCur = ptStart;
				bAtStartPt = true;
				while (((ptCur.x != ptStart.x) || (ptCur.y != ptStart.y)) || bAtStartPt)
				{
					bAtStartPt = false;

					//下一个探查位置
					xPos = ptCur.x + Direction[nCurDirect][0];
					yPos = ptCur.y + Direction[nCurDirect][1];
					int nSearchTimes = 1;

					while (GetGray(xPos, yPos) == 255)
					{
						nCurDirect++; //逆时针旋转45度
						if (nCurDirect >= 8)
							nCurDirect -= 8;

						xPos = ptCur.x + Direction[nCurDirect][0];
						yPos = ptCur.y + Direction[nCurDirect][1];

						if (++nSearchTimes >= 8) //8邻域中都没有边界点，说明是孤立点
						{
							xPos = ptCur.x;
							yPos = ptCur.y;
							break;
						}
					}

					//找到下一个边界点
					ptCur.x = xPos;
					ptCur.y = yPos;
					pTo->SetPixel(ptCur.x, ptCur.y, RGB(0, 0, 0)); //在新图像上标记边界
					nCurDirect -= 2; //将当前探查方向顺时针回转90度作为下一次的探查初始方向
					if (nCurDirect < 0)
						nCurDirect += 8;
				}
				return;
			}// if

			 /************
			 在此处添加适当的代码，并去掉上面的return语句，如果需要跟踪图像中所有物体的边界。
			 ************/

		}// for j
	}// for i

}

/*******************
void CImgProcessProcessing::FillRgn(CImgProcess* pTo, POINT ptStart)

功能：
以 ptStart 作为开始点（种子），对图像进行填充
注：
只能处理2值图象，边界假定为 8 连通，ptStart必须在原图像 *this 的边界之内

参数：
CImgProcess* pTo: 目标输出图像的 CImgProcess 指针
POINT ptStart: 种子点坐标

返回值：
无

*******************/
void CImgProcess::FillRgn(CImgProcess *pTo, POINT ptStart)
{
	int se[3][3] = { { -1, 1, -1 },{ 1, 1, 1 },{ -1, 1, -1 } }; // 十字形结构元素
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	pTo->InitPixels(255);								// 清空目标输出图像
	CImgProcess revImg = (*this);
	revImg = !revImg;									// 原图像的补，用来限制膨胀
	pTo->SetPixel(ptStart.x, ptStart.y, RGB(0, 0, 0));	// 初始化目标图像为只有种子点
	CImgProcess tmpImg = *pTo;							// 暂存上一次的运算结果

	while (true)										// 循环直到图像的受限膨胀不再产生变换
	{
		tmpImg.Dilate(pTo, se);							// 用十字结构元素膨胀
		*pTo = *pTo & revImg;							// 限制膨胀不会超出原始边界
		if (*pTo == tmpImg)								// 不再变化时停止
			break;
		tmpImg = *pTo;
	}

	*pTo = *pTo | (*this);								// 最终的结果为受限膨胀结果与原始边界的并集
}

/*******************
void CImgProcess::LabelConnRgn(CImgProcess* pTo)

功能：标注连通分量

注：只能处理二值图像

参数：
CImgProcess* pTo：目标图像的 CImgProcess 指针
int nConn：取值为4或8，表示4连通或8连通，默认为8

返回值:
int 无
*******************/
void CImgProcess::LabelConnRgn(CImgProcess* pTo, int nConn)
{
	int se[3][3] = { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } }; // 8连通 - 3*3结构元素
	if (nConn == 4)//4连通 - 十字形结构元素
	{
		se[0][0] = -1;
		se[0][2] = -1;
		se[2][0] = -1;
		se[2][2] = -1;
	}

	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j, k, l; //循环变量

	CImgProcess backupImg = *this; //备份原图像以备恢复
	CImgProcess tmpImg = *pTo; //暂存上一次的运算结果的临时图像

	int nConnRgn = 1; //连通分量的标号
	int nGray;

	//算法不处理边界上的点，将图像的四周的一圈边界置白
	for (i = 0; i < nHeight; i++)
	{
		SetPixel(0, i, RGB(255, 255, 255));
		SetPixel(nWidth - 1, i, RGB(255, 255, 255));
	}
	for (j = 0; j < nWidth; j++)
	{
		SetPixel(j, 0, RGB(255, 255, 255));
		SetPixel(j, nHeight - 1, RGB(255, 255, 255));
	}

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			nGray = GetGray(j, i);

			if (nGray == 0)
			{
				pTo->InitPixels(255); // 清空目标输出图像

				// 找到一个前景点，提取其所在的连通分量
				pTo->SetPixel(j, i, RGB(0, 0, 0));		// 初始化目标图像为只有连通区中的一点
				tmpImg = *pTo;							// 暂存图像
				while (true)							// 循环直到图像的受限膨胀不再产生变换
				{
					tmpImg.Dilate(pTo, se);				// 用结构元素膨胀
					*pTo = *pTo & backupImg;			// 计算和原图像的交，限制膨胀不会超出区域
					if (*pTo == tmpImg)					// 如果和上一次处理后的图像相同，说明该连通区已经提取完毕
						break;
					tmpImg = *pTo;						// 暂存图像
				}

				//标注刚刚找到的连通区
				for (k = 0; k < nHeight; k++)
				{
					for (l = 0; l < nWidth; l++)
					{
						nGray = pTo->GetGray(l, k);
						if (nGray == 0)
							SetPixel(l, k, RGB(nConnRgn, nConnRgn, nConnRgn)); //在当前图像上标注第nConnRgn号连通区
					}//for l

				}//for k

				nConnRgn++; //连通区编号加1
				if (nConnRgn > 255)
				{
					AfxMessageBox(L"目前该函数最多支持标注255个连通分量");
					i = nHeight; //强制跳出外层循环
					break;
				}
			}//if
		}//for j
	}//for i


	*pTo = *this; //更新目标图像（我们标注的是 *this）
	*this = backupImg; //恢复原图像

}

/*******************
void CImgProcess::Thining(CImgProcess* pTo)

功能：
细化
注：
只能处理2值图象

参数：
无

返回值：
无
*******************/

void CImgProcess::Thining()
{

	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	//四个条件
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;

	//5×5相邻区域像素值
	unsigned char neighbour[5][5];

	int i, j;
	int m, n;

	BOOL bModified = TRUE;


	while (bModified)
	{
		bModified = FALSE;
		CImgProcess pic = *this;
		pic.InitPixels(255); //清空目标图像

		for (j = 2; j < nHeight - 2; j++)
		{
			for (i = 2; i < nWidth - 2; i++)
			{
				bCondition1 = FALSE;
				bCondition2 = FALSE;
				bCondition3 = FALSE;
				bCondition4 = FALSE;

				BYTE data = GetGray(i, j);
				if (data == 255)
					continue;


				// 获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
				for (m = 0; m < 5; m++)
					for (n = 0; n < 5; n++)
						neighbour[m][n] = (GetGray(i + n - 2, j + m - 2) == 0);
				//逐个判断条件。
				//判断2<=NZ(P1)<=6
				int nCount = neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
					+ neighbour[2][1] + neighbour[2][3] + \
					+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if (nCount >= 2 && nCount <= 6)
					bCondition1 = TRUE;

				//判断Z0(P1)=1
				nCount = 0;
				if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
					nCount++;
				if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
					nCount++;
				if (neighbour[2][1] == 0 && neighbour[3][1] == 1)
					nCount++;
				if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
					nCount++;
				if (neighbour[3][2] == 0 && neighbour[3][3] == 1)
					nCount++;
				if (neighbour[3][3] == 0 && neighbour[2][3] == 1)
					nCount++;
				if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
					nCount++;
				if (neighbour[1][3] == 0 && neighbour[1][2] == 1)
					nCount++;
				if (nCount == 1)
					bCondition2 = TRUE;

				//判断P2*P4*P8=0 or Z0(p2)!=1
				if (neighbour[1][2] * neighbour[2][1] * neighbour[2][3] == 0)
					bCondition3 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[0][2] == 0 && neighbour[0][1] == 1)
						nCount++;
					if (neighbour[0][1] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
						nCount++;
					if (neighbour[2][1] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[2][3] == 1)
						nCount++;
					if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
						nCount++;
					if (neighbour[1][3] == 0 && neighbour[0][3] == 1)
						nCount++;
					if (neighbour[0][3] == 0 && neighbour[0][2] == 1)
						nCount++;
					if (nCount != 1)
						bCondition3 = TRUE;
				}

				//判断P2*P4*P6=0 or Z0(p4)!=1
				if (neighbour[1][2] * neighbour[2][1] * neighbour[3][2] == 0)
					bCondition4 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[1][1] == 0 && neighbour[1][0] == 1)
						nCount++;
					if (neighbour[1][0] == 0 && neighbour[2][0] == 1)
						nCount++;
					if (neighbour[2][0] == 0 && neighbour[3][0] == 1)
						nCount++;
					if (neighbour[3][0] == 0 && neighbour[3][1] == 1)
						nCount++;
					if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
						nCount++;
					if (neighbour[3][2] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[1][2] == 1)
						nCount++;
					if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (nCount != 1)
						bCondition4 = TRUE;
				}

				if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
				{
					pic.SetPixel(i, j, RGB(255, 255, 255));
					bModified = TRUE;
				}
				else
				{
					pic.SetPixel(i, j, RGB(0, 0, 0));
				}

			} //for i
		} //for j

		*this = pic;
	}//while
}

/**************************************************
BOOL CImgProcess::Hough(SLineInfo *pInfoRet, int nLineRet)
功能：
霍夫变换
注：
只能处理二值图像，一般应为经过边缘检测的输出图像（黑色背景，白色前景）
参数：
SLineInfo *pInfoRet
输出的直线信息
int nLineRet
需要寻找的直线数目

返回值：
BOOL类型，true为成功，false为失败
***************************************************/
BOOL CImgProcess::Hough(SLineInfo *pInfoRet, int nLineRet)
{
	int i, j;

	// 极坐标域中的最大Rho和Theta
	int nMaxDist = sqrt(GetHeight()*GetHeight() + GetWidthPixel()*GetWidthPixel());
	int nMaxAngle = 90;

	// 为极坐标域分配空间
	int nAreaNum = nMaxAngle * nMaxDist * 2;
	int *pTransArea = new int[nAreaNum];
	memset(pTransArea, 0, nAreaNum * sizeof(int));

	// 转化到极坐标域
	BYTE bt;
	int nAngle, nDist; //极坐标下的角度和极径
	double fRadian; //弧度
	for (i = 0; i < GetHeight(); i++)
	{
		for (j = 0; j < GetWidthPixel(); j++)
		{
			bt = GetGray(j, i);
			if (bt == 255)
			{
				for (nAngle = 0; nAngle < nMaxAngle; nAngle++)
				{
					fRadian = nAngle * 2 * PI / 180.0; //转化为弧度
					nDist = (j*cos(fRadian) + i*sin(fRadian)); //计算极径

					if (nDist >= 0)//正半周
					{
						pTransArea[nDist*nMaxAngle + nAngle] ++;
					}
					else//负半周
					{
						//nDist = fabs(nDist);
						nDist = nDist > 0 ? nDist : -nDist; //@ran
						pTransArea[nMaxAngle * nMaxDist + nDist*nMaxAngle + nAngle] ++;
					}
				}//for nAngle
			}//if
		}//for j
	}//for i

	SMaxValue MaxValue1;

	//清零时角度和极径的范围
	int nMaxDisAllow = 20;
	int nMaxAngleAllow = 5;

	for (int nLine = 0; nLine < nLineRet; nLine++) //寻找前nLineRet个峰值点
	{
		// 寻找最大点
		MaxValue1.nValue = 0;
		for (i = 0; i < nAreaNum; i++)
		{
			if (pTransArea[i] > MaxValue1.nValue)
			{
				MaxValue1.nValue = pTransArea[i];
				MaxValue1.nAngle = i;
			}
		}

		if (MaxValue1.nValue == 0) //找不到可能的共线点
		{
			return FALSE;
		}

		if (MaxValue1.nAngle < nMaxAngle * nMaxDist)
		{
			MaxValue1.nDist = MaxValue1.nAngle / nMaxAngle;
			MaxValue1.nAngle = MaxValue1.nAngle%nMaxAngle;
		}
		else
		{
			MaxValue1.nAngle -= nMaxAngle * nMaxDist;
			MaxValue1.nDist = MaxValue1.nAngle / nMaxAngle;
			MaxValue1.nDist *= -1;
			MaxValue1.nAngle = MaxValue1.nAngle%nMaxAngle;
		}

		// 将结果保存至pInfoRet结构指针
		pInfoRet[nLine].nAngle = MaxValue1.nAngle * 2;
		pInfoRet[nLine].nDist = MaxValue1.nDist;
		pInfoRet[nLine].nPixels = MaxValue1.nValue;

		if (pInfoRet[nLine].nDist < 0)
		{
			pInfoRet[nLine].nAngle = pInfoRet[nLine].nAngle - 180;
			pInfoRet[nLine].nDist = pInfoRet[nLine].nDist*(-1);

		}

		// 将附近点清零，为寻找下一个峰值做准备
		for (nDist = (-1)*nMaxDisAllow; nDist <= nMaxDisAllow; nDist++)
		{
			for (nAngle = (-1)*nMaxAngleAllow; nAngle <= nMaxAngleAllow; nAngle++)
			{
				int nThisDist = MaxValue1.nDist + nDist;
				int nThisAngle = MaxValue1.nAngle + nAngle;
				nThisAngle *= 2;

				if (nThisAngle < 0 && nThisAngle >= -180)
				{
					nThisAngle += 180;
					nThisDist *= -1;
				}
				if (nThisAngle >= 180 && nThisAngle < 360)
				{
					nThisAngle -= 180;
					nThisDist *= -1;
				}

				nThisDist = nThisDist > 0 ? nThisDist : -nThisDist; //@ran
				if (/*fabs(nThisDist)*/nThisDist <= nMaxDist
					&& nThisAngle >= 0 && nThisAngle <= nMaxAngle * 2)
				{
					nThisAngle /= 2;
					if (nThisDist >= 0)
						pTransArea[nThisDist*nMaxAngle + nThisAngle] = 0;
					else
					{
						//nThisDist = fabs(nThisDist);
						nThisDist = nThisDist > 0 ? nThisDist : -nThisDist;  //@ran
						pTransArea[nMaxDist*nMaxAngle + nThisDist*nMaxAngle + nThisAngle] = 0;
					}
				}
			}//for nAngle
		}//for nDist
	}//for nLine
	delete[]pTransArea; //释放极坐标域空间
	return TRUE;
}
/*
BOOL CImgProcess::Hough(SLineInfo *pInfoRet, int nLineRet)
{
//变换域的尺寸
int iMaxDist;
int iMaxAngleNumber;

//变换域的坐标
int iDist;
int iAngleNumber;

int i, j;//循环变量


//像素值
unsigned char pixel;

//存储变换域中的两个最大值
SMaxValue MaxValue1;
SMaxValue MaxValue2;


//计算变换域的尺寸
//最大距离
iMaxDist = (int) sqrt(GetWidthPixel()*GetWidthPixel() + GetHeight()*GetHeight());

//角度从0－180，每格2度
iMaxAngleNumber = 90;

int nAreaNum = iMaxAngleNumber * iMaxDist;
int *pTransArea = new int[nAreaNum];

memset(pTransArea, 0, nAreaNum * sizeof(int));

for(j = 0; j <GetHeight(); j++)
{
for(i = 0;i <GetWidthPixel(); i++)
{

pixel = GetGray(i, j);
// 指向源图像倒数第j行，第i个象素的指针


//目标图像中含有0和255外的其它灰度值
if(pixel != 255 && pixel != 0)
return FALSE;

//如果是黑点，则在变换域的对应各点上加1
if(pixel == 0)
{
//注意步长是2度
for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
{
iDist = (int) fabs(i*cos(iAngleNumber*2*PI/180.0) + \
j*sin(iAngleNumber*2*PI/180.0));

//变换域的对应点上加1
*(pTransArea+iDist*iMaxAngleNumber+iAngleNumber) = \
*(pTransArea+iDist*iMaxAngleNumber+iAngleNumber) +1;
}
}

}
}

//找到变换域中的两个最大值点
MaxValue1.nValue=0;
MaxValue2.nValue=0;

//找到第一个最大值点
for (iDist=0; iDist<iMaxDist;iDist++)
{
for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
{
if((int)*(pTransArea+iDist*iMaxAngleNumber+iAngleNumber)>MaxValue1.nValue)
{
MaxValue1.nValue = (int)*(pTransArea+iDist*iMaxAngleNumber+iAngleNumber);
MaxValue1.nDist = iDist;
MaxValue1.nAngle = iAngleNumber;
}

}
}

//将第一个最大值点附近清零
for (iDist = -9;iDist < 10;iDist++)
{
for(iAngleNumber=-1; iAngleNumber<2; iAngleNumber++)
{
if(iDist+MaxValue1.nDist>=0 && iDist+MaxValue1.nDist<iMaxDist \
&& iAngleNumber+MaxValue1.nAngle>=0 && iAngleNumber+MaxValue1.nAngle<=iMaxAngleNumber)
{
*(pTransArea+(iDist+MaxValue1.nDist)*iMaxAngleNumber+\
(iAngleNumber+MaxValue1.nAngle))=0;
}
}
}


pInfoRet[0].nAngle = 2*MaxValue1.nAngle;
pInfoRet[0].nDist = MaxValue1.nDist;

for(j = 0; j <GetHeight(); j++)
{
for(i = 0;i <GetWidthPixel(); i++)
{

// 指向缓存图像倒数第j行，第i个象素的指针




//在第一条直线上
iDist = (int) fabs(i*cos(MaxValue1.nAngle*2*PI/180.0) + \
j*sin(MaxValue1.nAngle*2*PI/180.0));
if (iDist == MaxValue1.nDist)
pTo->SetPixel(i, j, RGB(0, 0, 0));
}
}



// 返回
return TRUE;

}

*/


/*******************
void CImgProcess::PixelImage(CImgProcess* pTo, int lowerThres, int upperThres)

功能：
像素化大小介于 upperThres 和 lowerThres 之间的连通区域，像素化的像素位置为原区域的质心；
滤除大小低于 lowerThres 的连通区域
滤除大小超过 upperThres 的连通区域
注：
只能处理2值图象

参数：
CImgProcess* pTo: 目标图像的 CImgProcess 指针
upperThres: 上限阈值
lowerThres: 下限阈值

返回值：
无

*******************/
void CImgProcess::PixelImage(CImgProcess* pTo, int lowerThres, int upperThres)
{
	if (upperThres < lowerThres)
	{
		AfxMessageBox(L"上限阈值必须大于下限阈值！");
		return;
	}

	if (lowerThres < 0)
		lowerThres = 0;
	if (upperThres > 1000)
		upperThres = 1000; //为防止深度递归栈益处，限定upperThres的最大值为1000

	CImgProcess image_bkp = *this;
	CImgProcess image_res = *pTo;
	image_res.InitPixels(255); //存放像素化后的图像，初始为白色（背景）

	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;
	unsigned char pixel;

	LPBYTE lpVisited = new BYTE[nHeight*nWidth]; //标记该位置是否已被访问过

	for (i = 0; i < nHeight*nWidth; i++)
		lpVisited[i] = false; //初始访问标记数组

	int curConnRgnSize = 0; //当前发现的连通区的大小


	int nPtArySize = upperThres + 10; //记录访问点坐标数组的大小，是一个不能小于 upperThres 的量
	CPoint* ptVisited;//记录对于连通区的一次探查中访问过的点的坐标
	ptVisited = new CPoint[nPtArySize];

	int k = 0;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{

			for (k = 0; k < curConnRgnSize; k++)
				lpVisited[ptVisited[k].y*nWidth + ptVisited[k].x] = false;//还原 lpVisited 数组

			curConnRgnSize = 0; //重置为0

			pixel = image_bkp.GetGray(j, i);

			if (pixel == 0) //找到1个黑像素，进而探查该像素所处的连通区域的大小
			{
				int nRet = TestConnRgn(&image_bkp, lpVisited, nWidth, nHeight, j, i, ptVisited, lowerThres, upperThres, curConnRgnSize);
				if (nRet == 0) // lowerThres<= ... <=upperThres
				{
					//计算出区域的质心
					int xMean = 0;
					int yMean = 0;
					for (k = 0; k < curConnRgnSize; k++)
					{
						image_res.SetPixel(ptVisited[k].x, ptVisited[k].y, RGB(255, 255, 255));

						xMean += ptVisited[k].x;
						yMean += ptVisited[k].y;
					}
					xMean = xMean / curConnRgnSize;
					yMean = yMean / curConnRgnSize;

					image_res.SetPixel(xMean, yMean, RGB(0, 0, 0));

				}
				else if ((nRet == 1) || (nRet == -1)) // >upperThres or <lowerThres
				{
					//滤除
					for (k = 0; k < curConnRgnSize; k++)
					{
						image_res.SetPixel(ptVisited[k].x, ptVisited[k].y, RGB(255, 255, 255));
					}
				}
			}

		}// for j
	}// for i


	*pTo = image_res;


	delete[]lpVisited;
	delete[]ptVisited;
}

/*******************
TestConnRgn(CImgProcess* pImage, LPBYTE lpVisited, int nWidth, int nHeight, int x, int y, CPoint ptVisited[], int lowerThres, int upperThres, int &curConnRgnSize)

功能：
利用递归算法统计点 (x, y) 所处的连通区的大小与 lowerThres 和 upperThres 之间的关系
注：
只能处理2值图象

参数：
CImgProcess* pImage; 处理图像的 CImgProcess 指针
LPBYTE lpVisited     标志位数组
int nWidth       图象的宽度
int nHeigh       图象的高度
int x            当前考察点的横坐标
int y            当前考察点的纵坐标
Cpoint ptVisited[]     存放已考察过的点的坐标
int curConnRgnSize     当前为止发现的连通区的大小

返回值：
int
= 0: 连通区大小介于 lowerThres 和 upperThres 之间
= 1: 连通区大小超过 upperThres
=-1: 连通区大小低于 lowerThres

*******************/
int CImgProcess::TestConnRgn(CImgProcess* pImage, LPBYTE lpVisited, int nWidth, int nHeight, int x, int y, CPoint ptVisited[], int lowerThres, int upperThres, int &curConnRgnSize)
{

	if (curConnRgnSize > upperThres) //连通区大小已超过上限阈值upperThres
		return 1;

	curConnRgnSize++; //更新当前为止发现的连通区的大小
	lpVisited[nWidth*y + x] = true; //标记已访问

	ptVisited[curConnRgnSize - 1].x = x;
	ptVisited[curConnRgnSize - 1].y = y; //记录已访问点坐标

	unsigned char gray;

	if (curConnRgnSize >= upperThres)
		return 1;
	else
	{//测试8邻接的点，如果仍为黑色（物体），递归调用自己（连通区大小+1，继续考察邻接点的8邻接点）


		if (y - 1 >= 0)//上面的点
		{
			gray = pImage->GetGray(x, y - 1);
			if (gray == 0 && lpVisited[(y - 1)*nWidth + x] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x, y - 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//左上点
		if (y - 1 >= 0 && x - 1 >= 0)
		{
			gray = pImage->GetGray(x - 1, y - 1);
			if (gray == 0 && lpVisited[(y - 1)*nWidth + x - 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x - 1, y - 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//左边
		if (x - 1 >= 0)
		{
			gray = pImage->GetGray(x - 1, y);
			if (gray == 0 && lpVisited[y*nWidth + x - 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x - 1, y, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//左下
		if (y + 1 < nHeight && x - 1 >= 0)
		{
			gray = pImage->GetGray(x - 1, y + 1);
			if (gray == 0 && lpVisited[(y + 1)*nWidth + x - 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x - 1, y + 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//下方
		if (y + 1 < nHeight)
		{
			gray = pImage->GetGray(x, y + 1);
			if (gray == 0 && lpVisited[(y + 1)*nWidth + x] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x, y + 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//右下
		if (y + 1 < nHeight && x + 1 < nWidth)
		{
			gray = pImage->GetGray(x + 1, y + 1);
			if (gray == 0 && lpVisited[(y + 1)*nWidth + x + 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x + 1, y + 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//右边
		if (x + 1 < nWidth)
		{
			gray = pImage->GetGray(x + 1, y);
			if (gray == 0 && lpVisited[y*nWidth + x + 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x + 1, y, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

		//右上
		if (y - 1 >= 0 && x + 1 < nWidth)
		{
			gray = pImage->GetGray(x + 1, y - 1);
			if (gray == 0 && lpVisited[(y - 1)*nWidth + x + 1] == false)
				TestConnRgn(pImage, lpVisited, nWidth, nHeight, x + 1, y - 1, ptVisited, lowerThres, upperThres, curConnRgnSize);
		}
		if (curConnRgnSize > upperThres)
			return 1;

	}//else

	if (curConnRgnSize < lowerThres)
		return -1; //连通区大小低于 lowerThres


	return 0;//连通区大小介于 lowerThres 和 upperThres 之间
}

//***************************************投影变形校正相关*************************************//

/*******************
void CImgProcess::ProdMat(double** ppDbMat, double *pDbSrc2, double *pDbDest, int y, int x, int z)

功能：计算两矩阵的乘积

注：该函数计算两个矩阵的相乘，然后将相乘的结果存放在pDbDest中。
其中pDbSrc1 *的大小为 x*z，pDbSrc2的大小为 z*y，pDbDest的大小为 x*y

参数：
double  *pDbSrc1	- 指向相乘矩阵1的内存
double  *pDbSrc2	- 指向相乘矩阵2的内存
double  *pDbDest   - 存放矩阵相乘运行结果的内存指针
int     x		- 矩阵的尺寸，具体参见函数注
int     y		- 矩阵的尺寸，具体参见函数注
int     z		- 矩阵的尺寸，具体参见函数注

返回值:
无

*******************/
void CImgProcess::ProdMat(double** ppDbMat, double *pDbSrc2, double *pDbDest, int y, int x, int z)
{
	int nCnt = 0;
	int i, j;
	double * pDbSrc1 = new double[m_nBasePt * m_nBasePt];
	for (i = 0; i < m_nBasePt; i++)
	{
		for (j = 0; j < m_nBasePt; j++)
			pDbSrc1[nCnt++] = ppDbMat[i][j];
	}

	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			pDbDest[i*x + j] = 0;
			for (int m = 0; m < z; m++)
				pDbDest[i*x + j] += pDbSrc1[i*z + m] * pDbSrc2[m*x + j];
		}
	}

	nCnt = 0;
	for (i = 0; i < m_nBasePt; i++)
	{
		for (j = 0; j < m_nBasePt; j++)
			ppDbMat[i][j] = pDbSrc1[nCnt++];
	}

	delete[]pDbSrc1;
}


/*******************
void CImgProcess::GetProjPara(CPoint* pPointBase, CPoint* pPointSampl, double* pDbProjPara)

功能：根据基准点对儿（4对儿）确定变换参数

参数：
CPoint* pPointBase：基准图像的基准点
CPoint* pPointSampl：输入图像的基准点
double* pDbProjPara：变换参数

返回值:
无

*******************/
void CImgProcess::GetProjPara(CPoint* pPointBase, CPoint* pPointSampl, double* pDbProjPara)
{
	int i;

	//投影线性方程的系数矩阵
	double** ppParaMat;
	ppParaMat = new double*[m_nBasePt];
	for (i = 0; i < m_nBasePt; i++)
	{
		ppParaMat[i] = new double[m_nBasePt];
	}

	for (i = 0; i < m_nBasePt; i++)
	{
		ppParaMat[i][0] = pPointBase[i].x;
		ppParaMat[i][1] = pPointBase[i].y;
		ppParaMat[i][2] = pPointBase[i].x * pPointBase[i].y;
		ppParaMat[i][3] = 1;
	}

	double* pResMat;//结果矩阵
	pResMat = new double[m_nBasePt];
	for (i = 0; i < m_nBasePt; i++)//计算前四个系数 c1,c2,c3,c4
	{
		pResMat[i] = pPointSampl[i].x; //投影线性方程的值x'
	}

	// 采用左乘系数矩阵的逆矩阵的方法解出投影变换的前4个系数 c1,c2,c3,c4
	InvMat(ppParaMat, m_nBasePt);
	ProdMat(ppParaMat, pResMat, pDbProjPara, m_nBasePt, 1, m_nBasePt);//求出前4个系数

	for (i = 0; i < m_nBasePt; i++)//计算后四个系数 c5,c6,c7,c8
	{
		pResMat[i] = pPointSampl[i].y; //投影线性方程的值y'
	}
	// 采用左乘系数矩阵的逆矩阵的方法解出投影变换的后4个系数 c5,c6,c7,c8
	ProdMat(ppParaMat, pResMat, pDbProjPara + m_nBasePt, m_nBasePt, 1, m_nBasePt);//求出后4个系数


	 //释放空间
	delete[] pResMat;

	for (i = 0; i < m_nBasePt; i++)
	{
		delete[] ppParaMat[i];
	}
	delete[] ppParaMat;
}


/*******************
BOOL CImgProcess::InvMat(double** ppDbMat, int nLen)

功能：计算ppDbMat的逆矩阵

注：ppDbMat必须为方阵

参数：
double** ppDbMat：输入矩阵
int nLen：矩阵ppDbMat的尺寸

返回值:
BOOL
=true：执行成功
=false：计算过程中出现错误
*******************/
BOOL CImgProcess::InvMat(double** ppDbMat, int nLen)
{
	double* pDbSrc = new double[nLen * nLen];

	int *is, *js, i, j, k;

	//保存要求逆的输入矩阵
	int nCnt = 0;
	for (i = 0; i < nLen; i++)
	{
		for (j = 0; j < nLen; j++)
			pDbSrc[nCnt++] = ppDbMat[i][j];
	}

	double d, p;
	is = new int[nLen];
	js = new int[nLen];
	for (k = 0; k < nLen; k++)
	{
		d = 0.0;
		for (i = k; i < nLen; i++)
			for (j = k; j < nLen; j++)
			{
				p = fabs(pDbSrc[i*nLen + j]); //找到绝对值最大的系数
				if (p > d)
				{
					d = p;

					//记录绝对值最大的系数的行、列索引
					is[k] = i;
					js[k] = j;
				}
			}
		if (d + 1.0 == 1.0)
		{//系数全是0，系数矩阵为0 阵，此时为奇异矩阵
			delete is;
			delete js;
			return FALSE;
		}
		if (is[k] != k) //当前行不包含最大元素
			for (j = 0; j < nLen; j++)
			{
				//交换两行元素
				p = pDbSrc[k*nLen + j];
				pDbSrc[k*nLen + j] = pDbSrc[(is[k] * nLen) + j];
				pDbSrc[(is[k])*nLen + j] = p;
			}
		if (js[k] != k) //当前列不包含最大元素
			for (i = 0; i < nLen; i++)
			{
				//交换两列元素
				p = pDbSrc[i*nLen + k];
				pDbSrc[i*nLen + k] = pDbSrc[i*nLen + (js[k])];
				pDbSrc[i*nLen + (js[k])] = p;
			}

		pDbSrc[k*nLen + k] = 1.0 / pDbSrc[k*nLen + k]; //求主元的倒数 

													   // a[k,j]a[k,k] -> a[k,j]
		for (j = 0; j < nLen; j++)
			if (j != k)
			{
				pDbSrc[k*nLen + j] *= pDbSrc[k*nLen + k];
			}

		// a[i,j] - a[i,k]a[k,j] -> a[i,j]
		for (i = 0; i < nLen; i++)
			if (i != k)
				for (j = 0; j < nLen; j++)
					if (j != k)
					{
						pDbSrc[i*nLen + j] -= pDbSrc[i*nLen + k] * pDbSrc[k*nLen + j];
					}

		// -a[i,k]a[k,k] -> a[i,k]
		for (i = 0; i < nLen; i++)
			if (i != k)
			{
				pDbSrc[i*nLen + k] *= -pDbSrc[k*nLen + k];
			}
	}
	for (k = nLen - 1; k >= 0; k--)
	{
		//恢复列 
		if (js[k] != k)
			for (j = 0; j < nLen; j++)
			{
				p = pDbSrc[k*nLen + j];
				pDbSrc[k*nLen + j] = pDbSrc[(js[k])*nLen + j];
				pDbSrc[(js[k])*nLen + j] = p;
			}
		//恢复行
		if (is[k] != k)
			for (i = 0; i < nLen; i++)
			{
				p = pDbSrc[i*nLen + k];
				pDbSrc[i*nLen + k] = pDbSrc[i*nLen + (is[k])];
				pDbSrc[i*nLen + (is[k])] = p;
			}
	}

	//将结果拷贝回系数矩阵ppDbMat
	nCnt = 0;
	for (i = 0; i < m_nBasePt; i++)
	{
		for (j = 0; j < m_nBasePt; j++)
		{
			ppDbMat[i][j] = pDbSrc[nCnt++];
		}
	}

	//释放空间
	delete is;
	delete js;
	delete[] pDbSrc;

	return TRUE;

}

/*******************
MYPOINT CImgProcess::ProjTrans(CPoint pt, double* pDbProjPara)

功能：根据变换参数对点pt实施投影变换

参数：
CPoint pt：要进行投影变换的点坐标
double* pDbProjPara：变换参数

返回值:
MYPOINT
*******************/
MYPOINT CImgProcess::ProjTrans(CPoint pt, double* pDbProjPara)
{
	MYPOINT retPt;
	retPt.x = pDbProjPara[0] * pt.x + pDbProjPara[1] * pt.y + pDbProjPara[2] * pt.x * pt.y + pDbProjPara[3];
	retPt.y = pDbProjPara[4] * pt.x + pDbProjPara[5] * pt.y + pDbProjPara[6] * pt.x * pt.y + pDbProjPara[7];
	return retPt;
}

/*******************
BOOL CImgProcess::ImProjRestore(CImgProcess* pTo, CPoint *pPointBase, CPoint *pPointSampl, bool bInterp)

功能：实施投影变形校正

参数：
CImgProcess* pTo：校准后图像的 CImgProcess 指针
CPoint *pPointBase：基准图像的基准点数组
CPoint *pPointSampl：输入图像的基准点数组
bool bInterp：是否使用(双线性)插值

返回值:
MYPOINT
*******************/
BOOL CImgProcess::ImProjRestore(CImgProcess* pTo, CPoint *pPointBase, CPoint *pPointSampl, bool bInterp)
{
	double* pDbProjPara = new double[m_nBasePt * 2];
	GetProjPara(pPointBase, pPointSampl, pDbProjPara);

	//用得到的变换系数对图像实施变换
	int i, j;
	pTo->InitPixels(255); //清空目标图像
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			//对每个点(j, i)，计算其投影失真后的点ptProj
			MYPOINT ptProj = ProjTrans(CPoint(j, i), pDbProjPara);

			if (bInterp)
			{
				int nGray = InterpBilinear(ptProj.x, ptProj.y); //输入图像（投影变形图像）的对应点灰度
				if (nGray >= 0)
					pTo->SetPixel(j, i, RGB(nGray, nGray, nGray));
				else
					pTo->SetPixel(j, i, RGB(255, 255, 255)); //超出图像范围，填充白色
			}
			else
			{
				int ii = ptProj.y + 0.5; //四舍五入的最近邻插值
				int jj = ptProj.x + 0.5;
				if (ii > 0 && ii < GetHeight() && jj>0 && jj < GetWidthPixel())
					pTo->SetPixel(j, i, GetPixel(jj, ii));
				else
					pTo->SetPixel(j, i, RGB(255, 255, 255)); //超出图像范围，填充白色
			}
		}
	}

	delete pDbProjPara;
	return TRUE;
}

/**************************************************
BOOL CImgProcess::FFT2(CImgProcess * pTo, BOOL bExpand, complex<double> * pOutput, BYTE bFillColor)
功能：
二维快速傅立叶变换

参数：
CImgProcess * pTo
指向输出图像的指针，设置为NULL则不输出图像
BOOL bExpand
指定使用何种方法将图像高宽整定到2的整数幂：
若设置为true，则使用指定颜色扩大图像；
若设置为false，则从右侧和底部裁剪图像。
默认值取false，即裁剪图像。
complex<double> * pOutput
指向原始输出数组的指针，默认不输出原始数据，即默认为NULL
BYTE bFillColor
当bExpand被设置为true时，这个参数指定使用何种颜色扩大图像；
当bExpand被设置为false时，这个参数被忽略。默认值为255（白色）。

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FFT2(CImgProcess * pTo, BOOL bExpand, complex<double> * pOutput, BYTE bFillColor)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 中间变量
	double	dTemp;

	// 循环变量
	LONG i;
	LONG j;

	// FFT2的宽度和高度（2的整数次方）
	LONG w;
	LONG h;

	int	wp;
	int	hp;

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;

	// 计算进行傅立叶变换的宽度和高度（2的整数次方）
	while (w * 2 <= GetWidthPixel())
	{
		w *= 2;
		wp++;
	}

	while (h * 2 <= GetHeight())
	{
		h *= 2;
		hp++;
	}

	// 检查bExpand参数
	if ((bExpand) && (w != GetWidthPixel()) && (h != GetHeight())) {
		w *= 2; wp++;
		h *= 2; hp++;
	}

	// 分配内存
	complex<double> *TD = new complex<double>[w * h];
	complex<double> *FD = new complex<double>[w * h];

	// 垂直方向
	for (i = 0; i < h; i++)
	{
		// 水平方向
		for (j = 0; j < w; j++)
		{
			// 给时域赋值
			if (bExpand)
			{
				if ((j < GetWidthPixel()) && (i < GetHeight()))
				{
					TD[j + w * i] = complex<double>(GetGray(j, i), 0);
				}
				else
				{
					// 超出原图像范围的使用给定颜色填充
					TD[j + w * i] = complex<double>(bFillColor, 0);
				}
			}
			else
			{
				TD[j + w * i] = complex<double>(GetGray(j, i), 0);
			}
		}
	}

	for (i = 0; i < h; i++)
	{
		// 对y方向进行快速傅立叶变换
		FFT(&TD[w * i], &FD[w * i], wp);
	}

	// 保存变换结果
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
			TD[i + h * j] = FD[j + w * i];

	for (i = 0; i < w; i++)
		FFT(&TD[i * h], &FD[i * h], hp);						// 对x方向进行快速傅立叶变换

	
	if (pOutput)												// 更新输出矩阵	
		for (i = 0; i < h; i++)									// 垂直方向	
			for (j = 0; j < w; j++)								// 水平方向
				pOutput[i * w + j] = FD[j * h + i];

	if (pTo)													// 更新输出图像
	{
		pTo->ImResize(h, w);									// 重设输出图像大小

		// 寻找幅度谱对数变换的最大值与最小值，为优化幅度谱显示输出做准备
		// 幅度谱对数变换后的最大值和最小值分别定义如下
		double dMax = 0, dMin = 1E+006;

		for (i = 0; i < h; i++)
		{
			for (j = 0; j < w; j++)
			{
				// 计算幅度谱
				dTemp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() +
					FD[j * h + i].imag() * FD[j * h + i].imag()) / 100;

				dTemp = log(1 + dTemp);							// 对数变换
				dMax = max(dMax, dTemp);						// 寻找最大值
				dMin = min(dMin, dTemp);						// 寻找最小值
			}
		}

		for (i = 0; i < h; i++)
		{
			for (j = 0; j < w; j++)
			{
				// 计算幅度谱
				dTemp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() +
					FD[j * h + i].imag() * FD[j * h + i].imag()) / 100;

				// 对数变换
				dTemp = log(1 + dTemp);

				// 改变动态范围并归一化到0~255
				dTemp = (dTemp - dMin) / (dMax - dMin) * 255;

				// 更新目标图像
				// 此处不直接取j和i，是为了将变换后的原点移到中心
				pTo->SetPixel((j < w / 2 ? j + w / 2 : j - w / 2), (i < h / 2 ? i + h / 2 : i - h / 2), RGB(dTemp, dTemp, dTemp));
			}
		}
	}

	// 删除临时变量
	delete TD;
	delete FD;

	return true;
}

/**************************************************
BOOL CImgProcess::IFFT2(CImgProcess * pTo, complex<double> * pInput, long lWidth, long lHeight, long lOutW, long lOutH)

功能：
二维快速反傅立叶变换

参数：
CImgProcess * pTo
指向输出图像的指针
complex<double> * pInput
指向输入数组的指针
long lWidth
输入数组中需要进行反傅立叶变换的宽度
long lHeight
输入数组中需要进行反傅立叶变换的高度
long lOutW
指定输出图像的宽度，可以省略，默认与输入数组宽度相同
long lOutH
指定输出图像的高度，可以省略，默认与输入数组高度相同
返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::IFFT2(CImgProcess * pTo, complex<double> * pInput, long lWidth, long lHeight, long lOutW, long lOutH)
{
	if (m_pBMIH->biBitCount != 8) 
		return false;

	double dTemp;											// 中间变量
	LONG i, j;												// 循环变量
	LONG w, h;												// IFFT2的宽度和高度（2的整数次方）
	int	wp, hp;

	// 赋初值
	w = 1;h = 1;
	wp = 0;hp = 0;

	// 输出图像的高宽
	if (lOutH == 0) 
		lOutH = lHeight;
	if (lOutW == 0) 
		lOutW = lWidth;

	// 计算进行反傅立叶变换的宽度和高度（2的整数次方）
	while (w * 2 <= lWidth)
	{
		w *= 2;
		wp++;
	}

	while (h * 2 <= lHeight)
	{
		h *= 2;
		hp++;
	}

	// 分配内存
	complex<double> *TD = new complex<double>[w * h];
	complex<double> *FD = new complex<double>[w * h];

	// 设定输出图像大小
	pTo->ImResize(lOutH, lOutW);

	for (i = 0; i < h; i++)									// 垂直方向
		for (j = 0; j < w; j++)								// 水平方向
			FD[j + w * i] = pInput[j + w * i];				// 给频域赋值

	for (i = 0; i < h; i++)
		IFFT(&FD[w * i], &TD[w * i], wp);					// 对y方向进行快速反傅立叶变换

	// 保存变换结果
	for (i = 0; i < h; i++)									// 垂直方向				
		for (j = 0; j < w; j++)								// 水平方向
			FD[i + h * j] = TD[j + w * i];

	for (i = 0; i < w; i++)									// 对x方向进行快速反傅立叶变换
		IFFT(&FD[i * h], &TD[i * h], hp);

	// 寻找反变换结果对数变换的最大值与最小值，为优化显示输出做准备
	// 对最大值和最小值分别定义如下
	double dMax = 0, dMin = 1E+006;

	for (i = 0; i < lOutH; i++)
	{
		for (j = 0; j < lOutW; j++)
		{
			dTemp = TD[j * h + i].real();
			dMax = max(dMax, dTemp);						// 寻找最大值
			dMin = min(dMin, dTemp);						// 寻找最小值
		}
	}
	for (i = 0; i < lOutH; i++)								// 行
	{
		for (j = 0; j < lOutW; j++)							// 列
		{
			dTemp = TD[j * h + i].real();		
			dTemp = (dTemp - dMin) / (dMax - dMin) * 255;	// 改变动态范围并归一化到0~255
			pTo->SetPixel(j, i, RGB(dTemp, dTemp, dTemp));	// 更新目标图像
		}
	}

	// 删除临时变量
	delete TD;
	delete FD;

	return true;
}

/*******************************
void CImgProcess::dct8x8(double *in, double *out)
功能：执行8x8DCT变换
参数：
double *in:		输入的8x8 double一维数组指针
double *out:	输出的8x8 double一维数组指针
返回值：
无
*******************************/
void CImgProcess::dct8x8(double *in, double *out)
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
			in[i * 8 + j] -= 128;
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			double s = 0;
			int m, n;
			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					s += in[m * 8 + n] * cos((2 * m + 1)*PI*i / 16) * cos((2 * n + 1)*PI*j / 16);

			out[i * 8 + j] = s / 4;
			if (i == 0)
				out[i * 8 + j] = out[i * 8 + j] / sqrt(2.0);
			if (j == 0)
				out[i * 8 + j] = out[i * 8 + j] / sqrt(2.0);
		}
	}
}

/*******************************
void CImgProcess::idct8x8(double *in, double *out)
功能：执行8x8DCT逆变换
参数：
double *in:		输入的8x8 double一维数组指针
double *out:	输出的8x8 double一维数组指针
返回值：
无
*******************************/
void CImgProcess::idct8x8(double *in, double *out)
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			double s = 0;
			int m, n;
			for (m = 0; m < 8; m++)
			{
				for (n = 0; n < 8; n++)
				{
					double f = in[m * 8 + n] * cos((2 * i + 1)*PI*m / 16) * cos((2 * j + 1)*PI*n / 16);
					if (m == 0)
						f = f / sqrt(2.0);
					if (n == 0)
						f = f / sqrt(2.0);

					s += f;
				}
			}
			out[i * 8 + j] = s / 4;
		}
	}
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			out[i * 8 + j] += 128;
}

/*******************************
void CImgProcess::quant(double *in, int *out)
功能：执行量化操作，输入的8x8一维double数组，量化后输出8x8一维int数组
参数：
double *in:		输入的8x8 double一维数组指针
int *out:		输出的8x8 int一维数组指针
返回值：
无
*******************************/
void CImgProcess::quant(double *in, int *out)
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			double f = in[i * 8 + j] / double(Quant_table[i][j]);
			if (in[i * 8 + j] >= 0)
				out[i * 8 + j] = int(floor(f + 0.5));
			else
				out[i * 8 + j] = int(ceil(f - 0.5));
			if (out[i * 8 + j] < -128)
				out[i * 8 + j] = -128;
			if (out[i * 8 + j] > 127)
				out[i * 8 + j] = 127;
		}
	}
}

/*******************************
void CImgProcess::iquant(int *in, double *out)
功能：执行反量化操作，输入的8x8一维int数组，反量化后输出8x8一维double数组
参数：
int *in:		输入的8x8 int一维数组指针
double *out:	输出的8x8 double一维数组指针
返回值：
无
*******************************/
void CImgProcess::iquant(int *in, double *out)
{
	int i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			out[i * 8 + j] = in[i * 8 + j] * double(Quant_table[i][j]);
}

BOOL CImgProcess::DCT(CImgProcess *pTo)
{
	int wn = m_pBMIH->biWidth / 8;
	int hn = m_pBMIH->biHeight / 8;
	int i, j, m, n;

	for (i = 0; i < hn; i++)
	{
		for (j = 0; j < wn; j++)
		{
			// 用GetGray取出元素，转为double数组
			double din[64], dout[64];
			int iout[64];
			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					din[m * 8 + n] = double(GetGray(j * 8 + n, i * 8 + m));

			// 对每个块做变换和量化
			dct8x8(din, dout);
			quant(dout, iout);

			// 调用SetPixel，将结果写入到pTo中
			for (m = 0; m < 8; m++)
			{
				for (n = 0; n < 8; n++)
				{
					unsigned char t = (unsigned char)(iout[m * 8 + n] + 50);
					pTo->SetPixel(j * 8 + n, i * 8 + m, RGB(t, t, t));
				}
			}
		}
	}
	return true;
}

/*******************************
BOOL CImgProcess::IDCT(CImgProcess *pTo)
功能：对当前图像计算反量化和DCT反，再将结果存入pTo指针中
参数：
CImgProcess *pTo:	计算结果保存至pTo中
返回值：
无
*******************************/
BOOL CImgProcess::IDCT(CImgProcess *pTo)
{
	int wn = m_pBMIH->biWidth / 8;
	int hn = m_pBMIH->biHeight / 8;
	int i, j, m, n;
	for (i = 0; i < hn; i++)
	{
		for (j = 0; j < wn; j++)
		{
			// 用GetGray取出元素，转为double数组
			double dout1[64], dout2[64];
			int iin[64];
			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					iin[m * 8 + n] = (int)double(GetGray(j * 8 + n, i * 8 + m)) - 50;

			// 对每个块做反量化和反变换
			iquant(iin, dout1);
			idct8x8(dout1, dout2);

			// 调用SetPixel，将结果写入到pTo中
			for (m = 0; m < 8; m++)
			{
				for (n = 0; n < 8; n++)
				{
					double d = (dout2[m * 8 + n]);
					if (d < 0)
						d = 0.0;
					if (d > 254.5)
						d = 254.0;
					unsigned char t = (unsigned char)(int)(d + 0.5);
					pTo->SetPixel(j * 8 + n, i * 8 + m, RGB(t, t, t));
				}
			}
		}
	}
	return true;
}

/**************************************************
BOOL CImgProcess::FreqFilt(CImgProcess * pTo, double * pdFilter, BYTE bFillColor)

功能：
执行频域滤波操作。请首先使用相应的滤镜生成函数生成dFilter滤镜。

参数：
CImgProcess * pTo
指向输出图像的指针
double * pdFilter
给定的频域滤镜
BYTE bFillColor
用来补齐原图像使用的颜色，默认为255（白色）。
建议与图像右侧和底部边缘附近的颜色尽量保持一致。

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqFilt(CImgProcess * pTo, double * pdFilter, BYTE bFillColor)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 定义临时频域图像（逐行连续存储）
	complex<double> * cdFreqImg = new complex<double>[w*h];

	// 首先对原图像进行傅立叶变换
	FFT2(NULL, 1, cdFreqImg, bFillColor);

	// 然后执行核心滤波操作，将频域图像和滤镜逐元素相乘
	for (LONG i = 0; i < w*h; i++)
		cdFreqImg[i] = cdFreqImg[i] * pdFilter[i];

	// 最后将滤波结果进行傅立叶反变换
	IFFT2(pTo, cdFreqImg, w, h, GetWidthPixel(), GetHeight());

	// 由于动态范围问题，如果原图像存在较明显的灰度分界，
	// 不能完全保证滤波结果在灰度层次上与原图像保持类同，
	// 因此可能需要对输出图像再进行点运算操作。

	// 删除临时频域图像
	delete cdFreqImg;

	return true;
}

/**************************************************
BOOL CImgProcess::FreqIdealLPF(double * pdFilter, int nFreq)

功能：
生成对应于输入图像的频域理想低通滤镜

参数：
double * pdFilter
指向输出滤镜的指针
int nFreq
截止频率

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqIdealLPF(double * pdFilter, int nFreq)
{
	if (m_pBMIH->biBitCount != 8) 
		return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			if (sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) > nFreq)
				// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 0;
			else
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 1;
		}
	}
	return true;
}

BOOL CImgProcess::FreqIdealHPF(double * pdFilter, int nFreq)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			if (sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) < nFreq)
				// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 0;
			else
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 1;
		}
	}
	return true;
}

/**************************************************
BOOL CImgProcess::FreqGaussLPF(double * pdFilter, double dSigma)

功能：
生成对应于输入图像的高斯低通滤镜

参数：
double * pdFilter
指向输出滤镜的指针
double dSigma
高斯滤波器的Sigma参数

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqGaussLPF(double * pdFilter, double dSigma)
{
	if (m_pBMIH->biBitCount != 8) 
		return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				exp(-(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) / 2 / pow(dSigma, 2));
	return true;
}

/**************************************************
BOOL CImgProcess::FreqGaussHPF(double * pdFilter, double dSigma)

功能：
生成对应于输入图像的高斯高通滤镜

参数：
double * pdFilter
指向输出滤镜的指针
double dSigma
高斯滤波器的Sigma参数

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqGaussHPF(double * pdFilter, double dSigma)
{
	if (m_pBMIH->biBitCount != 8) 
		return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				1 - exp(-(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) / 2 / pow(dSigma, 2));
	return true;
}

BOOL CImgProcess::FreqButterworthLPF(double * pdFilter, int nFreq, int n)
{
	if (m_pBMIH->biBitCount != 8)
		return false;
	
	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 
				1 / (pow((double)( 1 + (pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) / nFreq / nFreq), n));
		
	return true;
}

BOOL CImgProcess::FreqButterworthHPF(double * pdFilter, int nFreq, int n)
{
	if (m_pBMIH->biBitCount != 8)
		return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
			1 / (1 + (pow((double)(nFreq * nFreq / (pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2))), n)));

	return true;
}

BOOL CImgProcess::FreqExpLPF(double * pdFilter, int nFreq, int n)
{
	if (m_pBMIH->biBitCount != 8)
		return false;
	double D;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			D = sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) / nFreq;
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				pow(e, -pow(D, n));
		}
	return true;
}

BOOL CImgProcess::FreqExpHPF(double * pdFilter, int nFreq, int n)
{
	if (m_pBMIH->biBitCount != 8)
		return false;
	double D;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			D = nFreq / sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2));
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				pow(e, -pow(D, n));
		}
	return true;
}

BOOL CImgProcess::FreqLadderLPF(double * pdFilter, int nFreq, int nF)
{
	if (m_pBMIH->biBitCount != 8)
		return false;
	double D;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			D = sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2));
			if (D < nFreq)
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 1;
			else if (D >= nFreq && D <= nF)
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				(nF - D) / (nF - nFreq);
			else
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 0;
		}
	return true;
}

BOOL CImgProcess::FreqLadderHPF(double * pdFilter, int nFreq, int nF)
{
	if (m_pBMIH->biBitCount != 8)
		return false;
	double D;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			D = sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2));
			if (D < nFreq)
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 0;
			else if (D >= nFreq && D <= nF)
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				(D - nFreq) / (nF - nFreq);
			else
				pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] = 0;
		}
	return true;
}

/**************************************************
BOOL CImgProcess::FreqLaplace(double * pdFilter)

功能：
生成对应于输入图像的频域拉普拉斯滤波器

参数：
double * pdFilter
指向输出滤镜的指针

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqLaplace(double * pdFilter)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				-(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2));
	return true;
}

/**************************************************
BOOL CImgProcess::FreqGaussBRF(double * pdFilter , int nFreq, int nWidth)

功能：
生成对应于输入图像的高斯带阻滤波器

参数：
double * pdFilter
指向输出滤镜的指针
int nFreq
阻带的中心频率
int nWidth
阻带的宽度

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::FreqGaussBRF(double * pdFilter, int nFreq, int nWidth)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 计算滤镜大小
	LONG w = GetFreqWidth();
	LONG h = GetFreqHeight();

	// 滤镜产生过程
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			// 先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的四个部分
			// 在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i < h / 2 ? i + h / 2 : i - h / 2) * w + (j < w / 2 ? j + w / 2 : j - w / 2)] =
				1 - exp(-0.5 * pow((pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2) - pow((double)nFreq, 2)) /
				(sqrt(pow((double)(i - h / 2), 2) + pow((double)(j - w / 2), 2)) * nWidth), 2));

	return true;
}

/**************************************************
BOOL CImgProcess::EdgeRoberts(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)

功能：
边缘寻找，使用Roberts算子

参数：
CImgProcess * pTo
指向输出图像的指针
BYTE bThre
认定边缘的阈值，默认为0，即自动确定阈值
BYTE bEdgeType
_EdgeAll-所有边缘 _EdgeH-无效 _EdgeV-无效 _EdgeCW-45度边缘 _EdgeCCW-135度边缘 其它-无效
BOOL bThinning
决定是否进行边缘细化，默认为true，即执行边缘细化
BOOL bGOnly
决定是否仅输出梯度图像，默认为false，即输出阈值化后的二值图像。
当此参数为true时，bThre参数和bThinning参数将被忽略

返回值：
布尔类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::EdgeRoberts(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 定义模板数据
	const double cfRobertCW[4] = { -1, 0, 0, 1 };			// 45度边缘
	const double cfRobertCCW[4] = { 0, -1, 1,  0 };			// 135度边缘

	// 临时CImgProcess变量
	CImgProcess imgTemp = *this;
	CImgProcess imgMid = *this;

	// 根据选择的边缘类型应用模板
	switch (bEdgeType) 
	{
	case 0:													// 所有边缘
		Template(&imgTemp, 2, 2, 0, 0, (double*)cfRobertCW, 1);
		Template(&imgMid, 2, 2, 0, 0, (double*)cfRobertCCW, 1);
		imgTemp = imgTemp + imgMid;
		break;
	case 1:													// 水平边缘，错误
		return false;
	case 2:													// 垂直边缘，错误
		return false;
	case 3:													// 45度边缘
		Template(&imgTemp, 2, 2, 0, 0, (double*)cfRobertCW, 1);
		break;
	case 4:													// 135度边缘
		Template(&imgTemp, 2, 2, 0, 0, (double*)cfRobertCCW, 1);
		break;
	default:												// 参数错误
		return false;
	}

	if (bGOnly)
		*pTo = imgTemp;										// 仅输出梯度
	else
	{
		
		if (bThre)											// 根据指定阈值进行阈值化
			imgTemp.Threshold(pTo, bThre);
		else												// 自动阈值化
			imgTemp.AutoThreshold(pTo);

		if (bThinning)
		{
			pTo->LinTran(&imgTemp, -1, 255);				// 第一次反色：为边缘细化准备
			imgTemp.Thining();								// 边缘细化
			imgTemp.LinTran(pTo, -1, 255);					// 第二次反色：得到最终结果
		}
	}

	return true;
}

/**************************************************
BOOL CImgProcess::EdgeSobel(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)

功能：
边缘寻找，使用Sobel算子

参数：
CImgProcess * pTo
指向输出图像的指针
BYTE bThre
认定边缘的阈值，默认为0，即自动确定阈值
BYTE bEdgeType
_EdgeAll-所有边缘 _EdgeH-水平边缘 _EdgeV-垂直边缘 _EdgeCW-45度边缘 _EdgeCCW-135度边缘 其它-无效
BOOL bThinning
决定是否进行边缘细化，默认为true，即执行边缘细化
BOOL bGOnly
决定是否仅输出梯度图像，默认为false，即输出阈值化后的二值图像。
当此参数为true时，bThre参数和bThinning参数将被忽略

返回值：
布尔类型，true为成功，false为失败
***************************************************/
BOOL CImgProcess::EdgeSobel(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 定义模板数据
	
	const double cfSobelH[9] =									// 水平边缘
	{
		-1, -1, -1,
		0,  0,  0,
		1,  1,  1 };

	const double cfSobelV[9] = 									// 垂直边缘
	{
		-1,  0,  1,
		-1,  0,  1,
		-1,  0,  1 };
	
	const double cfSobelCW[9] = 									// 45度边缘
	{
		-1, -1,  0,
		-1,  0,  1,
		 0,  1,  1 };
	
	const double cfSobelCCW[9] = 								// 135度边缘
	{
		0,  1,  1,
		-1,  0,  1,
		-1, -1,  0 };

	// 临时CImgProcess变量
	CImgProcess imgTemp = *this;
	CImgProcess imgMid  = *this;

	// 根据选择的边缘类型应用模板
	switch (bEdgeType) 
	{
	case 0:														// 所有边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfSobelH, 1);
		Template(&imgMid, 3, 3, 1, 1, (double*)cfSobelV, 1);
		imgTemp = imgTemp + imgMid;
		Template(&imgMid, 3, 3, 1, 1, (double*)cfSobelCW, 1);
		imgTemp = imgTemp + imgMid;
		Template(&imgMid, 3, 3, 1, 1, (double*)cfSobelCCW, 1);
		imgTemp = imgTemp + imgMid;
		break;

	case 1:														// 水平边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfSobelH, 1);
		break;

	case 2:														// 垂直边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfSobelV, 1);
		break;

	case 3:														// 45度边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfSobelCW, 1);
		break;

	case 4:														// 135度边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfSobelCCW, 1);
		break;

	default:													// 参数错误
		return false;
	}

	if (bGOnly)
		*pTo = imgTemp;											// 仅输出梯度

	else
	{
		if (bThre)												// 根据指定阈值进行阈值化
			imgTemp.Threshold(pTo, bThre);

		else													// 自动阈值化
			imgTemp.AutoThreshold(pTo);

		if (bThinning)
		{
			pTo->LinTran(&imgTemp, -1, 255);					// 第一次反色：为边缘细化准备
			imgTemp.Thining();									// 边缘细化
			imgTemp.LinTran(pTo, -1, 255);						// 第二次反色：得到最终结果
		}
	}

	return true;
}

/**************************************************
BOOL CImgProcess::EdgePrewitt(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)

功能：
边缘寻找，使用Prewitt算子

参数：
CImgProcess * pTo
指向输出图像的指针
BYTE bThre
认定边缘的阈值，默认为0，即自动确定阈值
BYTE bEdgeType
_EdgeAll-所有边缘 _EdgeH-水平边缘 _EdgeV-垂直边缘 _EdgeCW-45度边缘 _EdgeCCW-135度边缘 其它-无效
BOOL bThinning
决定是否进行边缘细化，默认为true，即执行边缘细化
BOOL bGOnly
决定是否仅输出梯度图像，默认为false，即输出阈值化后的二值图像。
当此参数为true时，bThre参数和bThinning参数将被忽略

返回值：
布尔类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::EdgePrewitt(CImgProcess * pTo, BYTE bThre, BYTE bEdgeType, BOOL bThinning, BOOL bGOnly)
{
	if (m_pBMIH->biBitCount != 8) return false;

	// 定义模板数据
	
	const double cfPrewittH[9] =									// 水平边缘
	{
		-1, -2, -1,
		 0,  0,  0,
		 1,  2,  1 };
	
	const double cfPrewittV[9] =									// 垂直边缘
	{
		-1,  0,  1,
		-2,  0,  2,
		-1,  0,  1 };
	
	const double cfPrewittCW[9] =								// 45度边缘
	{
		-2, -1,  0,
		-1,  0,  1,
		 0,  1,  2 };
	
	const double cfPrewittCCW[9] =								// 135度边缘
	{
		 0,  1,  2,
		-1,  0,  1,
		-2, -1,  0 };

	// 临时CImgProcess变量
	CImgProcess imgTemp = *this;
	CImgProcess imgMid = *this;

	// 根据选择的边缘类型应用模板
	switch (bEdgeType) 
	{
	case 0:														// 所有边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfPrewittH, 1);
		Template(&imgMid, 3, 3, 1, 1, (double*)cfPrewittV, 1);
		imgTemp = imgTemp + imgMid;
		Template(&imgMid, 3, 3, 1, 1, (double*)cfPrewittCW, 1);
		imgTemp = imgTemp + imgMid;
		Template(&imgMid, 3, 3, 1, 1, (double*)cfPrewittCW, 1);
		imgTemp = imgTemp + imgMid;
		break;

	case 1:														// 水平边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfPrewittH, 1);
		break;

	case 2:														// 垂直边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfPrewittV, 1);
		break;

	case 3:														// 45度边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfPrewittCW, 1);
		break;

	case 4:														// 135度边缘
		Template(&imgTemp, 3, 3, 1, 1, (double*)cfPrewittCCW, 1);
		break;

	default:													// 参数错误
		return false;
	}

	if (bGOnly)
		*pTo = imgTemp;											// 仅输出梯度

	else
	{
		if (bThre)												// 根据指定阈值进行阈值化
			imgTemp.Threshold(pTo, bThre);

		else													// 自动阈值化
			imgTemp.AutoThreshold(pTo);

		if (bThinning)
		{
			pTo->LinTran(&imgTemp, -1, 255);					// 第一次反色：为边缘细化准备
			imgTemp.Thining();									// 边缘细化
			imgTemp.LinTran(pTo, -1, 255);						// 第二次反色：得到最终结果
		}
	}

	return true;
}

/**************************************************
void CImgProcess::EdgeLoG(CImgProcess * pTo)

功能：
基于LoG算子的边缘检测

参数：
CImgProcess * pTo
指向输出图像的指针

返回值：
无
***************************************************/

void CImgProcess::EdgeLoG(CImgProcess * pTo)
{
	
	Template(pTo, 5, 5, 2, 2, Template_Log, 1);					// 应用模板到图像
	CImgProcess imgTemp = *pTo;									// 临时CImgProcess变量
	imgTemp.AutoThreshold(pTo);									// 自动阈值化
	pTo->LinTran(&imgTemp, -1, 255);							// 第一次反色：为边缘细化准备
	imgTemp.Thining();											// 边缘细化
	imgTemp.LinTran(pTo, -1, 255);								// 第二次反色：得到最终结果
}

CImgProcess& CImgProcess::operator = (CImg& img)				// 从基类的转换
{
	
	if (IsValidate())											// 拷贝图像大小
		ImResize(img.GetHeight(), img.GetWidthPixel());
	else
	{
		throw "Error in operaor '=': Left hand operand not initialized.";
		return *this;
	}

	for (int i = 0; i < GetHeight(); i++)						// 拷贝图像数据
		memcpy(m_lpData[i], img.m_lpData[i], img.GetWidthByte() * sizeof(BYTE));

	return *this;
}

/**************************************************
BOOL CImgProcess::EdgeCanny(CImgProcess * pTo, BYTE bThreL, BYTE bThreH, BOOL bThinning)

功能：
基于Canny算子的边缘检测

参数：
CImgProcess * pTo
指向输出图像的指针
BYTE bThreL, BYTE bThreH
认定边缘的低阈值和高阈值
将任一设置为0则会被自动生成，生成高阈值时会自动覆盖低阈值
默认值均为0，即自动生成高低阈值
BOOL bThinning
决定是否进行边缘细化，默认为true，即执行边缘细化

返回值：
布尔类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::EdgeCanny(CImgProcess * pTo, BYTE bThreL, BYTE bThreH, BOOL bThinning)
{
	int i, j;

	if (m_pBMIH->biBitCount != 8) return false;

	// 各方向梯度值
	CImgProcess imgGH = *this, imgGV = *this, imgGCW = *this, imgGCCW = *this, imgGratitude = *this;

	// 使用Prewitt模板计算各个方向上的梯度值
	EdgePrewitt(&imgGH, 0, 1, 0, 1);
	EdgePrewitt(&imgGV, 0, 2, 0, 1);
	EdgePrewitt(&imgGCW, 0, 3, 0, 1);
	EdgePrewitt(&imgGCCW, 0, 4, 0, 1);
	
	BYTE * pbDirection = new BYTE[GetHeight() * GetWidthByte()];// 最大梯度方向

	memset(pbDirection, 0, GetHeight() * GetWidthByte() * sizeof(BYTE));

	// 寻找每点的最大梯度方向并写入对应的最大梯度值
	imgGratitude.InitPixels(0);
	for (i = 0; i < GetHeight(); i++)
	{
		for (j = 0; j < GetWidthPixel(); j++)
		{
			BYTE gray = 0;

			if (imgGH.GetGray(j, i) > gray)
			{
				gray = imgGH.GetGray(j, i);
				pbDirection[i * GetWidthPixel() + j] = _EdgeH;
				imgGratitude.SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGV.GetGray(j, i) > gray)
			{
				gray = imgGV.GetGray(j, i);
				pbDirection[i * GetWidthPixel() + j] = _EdgeV;
				imgGratitude.SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGCW.GetGray(j, i) > gray)
			{
				gray = imgGCW.GetGray(j, i);
				pbDirection[i * GetWidthPixel() + j] = _EdgeCW;
				imgGratitude.SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGCCW.GetGray(j, i) > gray)
			{
				gray = imgGCCW.GetGray(j, i);
				pbDirection[i * GetWidthPixel() + j] = _EdgeCCW;
				imgGratitude.SetPixel(j, i, RGB(gray, gray, gray));
			}
		}
	}

	// 阈值化时重用前面的对象
	CImgProcess *pImgThreL = &imgGH, *pImgThreH = &imgGV;

	// 检查阈值参数，如未给出阈值则计算以取得最佳阈值
	if (bThreL > bThreH) 
		return false;

	if (bThreH == 0) {
		const int nMinDiff = 20;
		int nDiffGray;

		bThreH = 1.2 * imgGratitude.DetectThreshold(100, nDiffGray);
		bThreL = 0.4 * bThreH;

		if (nDiffGray < nMinDiff) return false;
	}

	if (bThreL == 0) {
		bThreL = 0.4 * bThreH;
	}

	// 将最大梯度图像按高低值分别进行阈值化
	imgGratitude.Threshold(pImgThreL, bThreL);
	imgGratitude.Threshold(pImgThreH, bThreH);

	// 初始化目标图像
	pTo->InitPixels(0);

	// 根据低阈值图像在高阈值图像上进行边界修补
	for (i = 1; i < GetHeight() - 1; i++)
	{
		for (j = 1; j < GetWidthPixel() - 1; j++)
		{
			if (pImgThreH->GetGray(j, i))
			{
				
				pTo->SetPixel(j, i, RGB(255, 255, 255));		// 高阈值图像上发现点直接确定

				
				switch (pbDirection[i * GetWidthPixel() + j])	// 搜索梯度最大方向上的邻域
				{
				case 1:											// 水平方向
					if (pImgThreL->GetGray(j + 1, i))
						pImgThreH->SetPixel(j + 1, i, RGB(255, 255, 255));

					if (pImgThreL->GetGray(j - 1, i))
						pImgThreH->SetPixel(j - 1, i, RGB(255, 255, 255));

					break;

				case 2:											// 垂直方向
					if (pImgThreL->GetGray(j, i + 1))
						pImgThreH->SetPixel(j, i + 1, RGB(255, 255, 255));

					if (pImgThreL->GetGray(j, i - 1))
						pImgThreH->SetPixel(j, i - 1, RGB(255, 255, 255));
					
					break;

				case 3:											// 45度方向
					if (pImgThreL->GetGray(j + 1, i - 1))
						pImgThreH->SetPixel(j + 1, i - 1, RGB(255, 255, 255));

					if (pImgThreL->GetGray(j - 1, i + 1))
						pImgThreH->SetPixel(j - 1, i + 1, RGB(255, 255, 255));

					break;

				case 4:											// 135度方向
					if (pImgThreL->GetGray(j + 1, i + 1))
						pImgThreH->SetPixel(j + 1, i + 1, RGB(255, 255, 255));

					if (pImgThreL->GetGray(j - 1, i - 1))
						pImgThreH->SetPixel(j - 1, i - 1, RGB(255, 255, 255));
					break;
				}
			}//if
		}//for j
	}//for i

	if (bThinning)
	{
		pImgThreH->LinTran(pImgThreL, -1, 255);					// 第一次反色：为边缘细化准备
		pImgThreL->Thining();									// 边缘细化
		pImgThreL->LinTran(pTo, -1, 255);						// 第二次反色：得到最终结果
	}
	else
		*pTo = *pImgThreH;

	delete pbDirection;

	return true;
}

/**************************************************
BOOL CImgProcess::RegionGrow(CImgProcess * pTo , int nSeedX, int nSeedY, BYTE bThre)

功能：
区域生长算法

参数：
CImgProcess * pTo
指向输出图像的指针
int nSeedX, int nSeedY
种子点的坐标值
BYTE bThre
生长时使用的阈值
返回值：
布尔类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::RegionGrow(CImgProcess * pTo, int nSeedX, int nSeedY, BYTE bThre)
{
	if (m_pBMIH->biBitCount != 8) return false;

	if ((nSeedX < 0) || (nSeedX > GetWidthPixel())) return false;
	if ((nSeedY < 0) || (nSeedY > GetHeight())) return false;

	pTo->InitPixels(0);
	pTo->SetPixel(nSeedX, nSeedY, RGB(255, 255, 255));

	BYTE bSeed = GetGray(nSeedX, nSeedY);						// 生长起始点灰度
	long int lSum = bSeed;										// 生长区域灰度值之和
	int nSuit = 1, nCount = 1;									// 生长区域的点总数和每次八邻域中符合条件点个数
	
	while (nCount > 0)											// 开始区域生长循环操作
	{
		nCount = 0;
		for (int i = 1; i < GetHeight() - 1; i++)				// 纵向
		{	
			for (int j = 1; j < GetWidthPixel() - 1; j++)		// 横向
			{	
				if (pTo->GetGray(j, i) == 255)
				{	// 是种子点
					// 开始8邻域扫描
					for (int m = i - 1; m <= i + 1; m++)
					{
						for (int n = j - 1; n <= j + 1; n++)
						{
							// 判断是否符合阈值条件且未标记
							if ((pTo->GetGray(n, m) == 0) && (abs(GetGray(n, m) - bSeed) <= bThre))
							{
								pTo->SetPixel(n, m, RGB(255, 255, 255));
								nCount++;
								lSum += GetGray(n, m);
							}
						}
					}
				}
			}
		}

		nSuit += nCount;

		// 计算新种子值（这里使用改进的种子值算法为已标记区域的平均灰度）
		bSeed = lSum / nSuit;
	}

	return true;
}

/**************************************************
BOOL CImgProcess::GenHist(double * pdHist, int n)

功能：
生成图像的灰度直方图

参数：
double * pdHist
输出的灰度直方图数组
BYTE n
灰度直方图的灰度级数（段数）
返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::GenHist(double * pdHist, int n)
{
	
	if (m_pBMIH->biBitCount != 8)								// 首先检查图像的类型
		return false;

	if ((n <= 0) || (n > 256))									// 检查n范围
		return false;

	double dDivider;											// 计算分段因子

	memset(pdHist, 0, n * sizeof(double));
	dDivider = 256.0 / (double)n;

	BYTE bGray;													// 临时变量,存储当前光标像素的灰度值
	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			bGray = GetGray(j, i);
			pdHist[(int)(bGray / dDivider)]++;	// 指定的灰度区间自加
		}
	}

	UINT square = m_pBMIH->biWidth * m_pBMIH->biHeight;
	for (int k = 0; k < n; k++)
		pdHist[k] = pdHist[k] / square;

	return true;
}

BOOL CImgProcess::GenRGBHist(double * pdHist, int iType, int n)
{
	if (m_pBMIH->biBitCount != 24)									// 首先检查图像的类型
		return false;

	if ((n <= 0) || (n > 256))										// 检查n范围
		return false;

	if (iType == 1)
	{
		double dDivider;											// 计算分段因子
		
		memset(pdHist, 0, n * sizeof(double));
		dDivider = 256.0 / (double)n;

		BYTE bGray;													// 临时变量,存储当前光标像素的灰度值
		for (int i = 0; i < m_pBMIH->biHeight; i++)
		{
			for (int j = 0; j < m_pBMIH->biWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				bGray = GetRValue(RGBPixel);
				pdHist[(int)(bGray / dDivider)]++;					// 指定的灰度区间自加
			}
		}

		UINT square = m_pBMIH->biWidth * m_pBMIH->biHeight;
		for (int k = 0; k < n; k++)
			pdHist[k] = pdHist[k] / square;

		return true;
	}

	else if (iType == 2)
	{
		double dDivider;											// 计算分段因子

		memset(pdHist, 0, n * sizeof(double));
		dDivider = 256.0 / (double)n;

		BYTE bGray;													// 临时变量,存储当前光标像素的灰度值
		for (int i = 0; i < m_pBMIH->biHeight; i++)
		{
			for (int j = 0; j < m_pBMIH->biWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				bGray = GetGValue(RGBPixel);
				pdHist[(int)(bGray / dDivider)]++;	// 指定的灰度区间自加
			}
		}

		UINT square = m_pBMIH->biWidth * m_pBMIH->biHeight;
		for (int k = 0; k < n; k++)
			pdHist[k] = pdHist[k] / square;

		return true;
	}

	else if (iType == 3)
	{
		double dDivider;											// 计算分段因子

		memset(pdHist, 0, n * sizeof(double));
		dDivider = 256.0 / (double)n;

		BYTE bGray;													// 临时变量,存储当前光标像素的灰度值
		for (int i = 0; i < m_pBMIH->biHeight; i++)
		{
			for (int j = 0; j < m_pBMIH->biWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				bGray = GetBValue(RGBPixel);
				pdHist[(int)(bGray / dDivider)]++;	// 指定的灰度区间自加
			}
		}

		UINT square = m_pBMIH->biWidth * m_pBMIH->biHeight;
		for (int k = 0; k < n; k++)
			pdHist[k] = pdHist[k] / square;

		return true;
	}

	else
		return FALSE;
}

/**************************************************
BOOL CImgProcess::ParLinTran(CImgProcess * pTo, BYTE x1, BYTE x2, BYTE y1, BYTE y2)

功能：
图像的灰度分段线性变换
限制：
x1 < x2

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
BYTE x1
分段线性变换第一点的横坐标
BYTE x2
分段线性变换第二点的横坐标
BYTE y1
分段线性变换第一点的纵坐标
BYTE y2
分段线性变换第二点的纵坐标

返回值：
BOOL类型，true为成功，false为失败
***************************************************/
BOOL CImgProcess::ParLinTran(CImgProcess * pTo, BYTE x1, BYTE x2, BYTE y1, BYTE y2)
{
	
	if (m_pBMIH->biBitCount != 8)								// 首先检查图像的类型
		return false;

	
	if (x1 > x2)												// 检查参数范围
		return false;											// 参数关系错误,返回错误

	BYTE gray;													// 临时变量,存储当前光标像素的灰度值
	int target;													// 临时变量,存储当前光标像素的目标值

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);
			if (gray <= x1)
				target = y1 * gray / x1;
			else if (gray <= x2)
				target = (y2 - y1)*(gray - x1) / (x2 - x1) + y1;
			else
				target = (255 - y2)*(gray - x2) / (255 - x2) + y2;

			if (target < 0) 
				target = 0;
			if (target > 255) 
				target = 255;

			pTo->SetPixel(j, i, RGB(target, target, target));	// 写入目标图像
		}
	}

	return true;
}

/**************************************************
BOOL CImgProcess::LogTran(CImgProcess* pTo, double dC)

功能：
图像的灰度对数变换

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
double dC
灰度对数变换所需的参数
返回值：
BOOL类型，0为成功，其他值为失败
***************************************************/
BOOL CImgProcess::LogTran(CImgProcess* pTo, double dC)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount != 8) return false;

	BYTE gray;		// 临时变量,存储当前光标像素的灰度值
	int target;		// 临时变量,存储当前光标像素的目标值

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);
			target = dC * log((double)(gray + 1));
			
			if (target < 0) 
				target = 0;
			if (target > 255)
				target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return 0;
}

/**************************************************
BOOL CImgProcess::GammaTran(CImgProcess* pTo, double gamma, double comp)

功能：
图像的伽玛变换方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
double gamma
伽玛系数
double comp
补偿系数,默认为0

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::GammaTran(CImgProcess* pTo, double gamma, double comp)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount != 8) 
		return false;

	BYTE gray;		// 临时变量,存储当前光标像素的灰度值
	int target;		// 临时变量,存储当前光标像素的目标值

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);
			target = pow((gray + comp) / 255.0, gamma) * 255;

			if (target < 0) 
				target = 0;
			if (target > 255) 
				target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return 0;
}

/**************************************************
BOOL CImgProcess::WindowTran(CImgProcess* pTo, BYTE lowThre, BYTE highThre)

功能：
图像的窗口变换方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
BYTE lowThre
窗口下限
BYTE highThre
窗口上限

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::WindowTran(CImgProcess* pTo, BYTE lowThre, BYTE highThre)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount != 8) 
		return false;

	BYTE gray;		// 临时变量,存储当前光标像素的灰度值
	int target;		// 临时变量,存储当前光标像素的目标值

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);
			if (gray < lowThre)
				target = 0;
			else if (gray > highThre)
				target = 255;
			else
				target = gray;

			if (target < 0) 
				target = 0;

			if (target > 255) 
				target = 255;

			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return 0;
}

/**************************************************
BOOL CImgProcess::LinTran(CImgProcess* pTo, double dFa, double dFb)

功能：
图像的线性变换方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
double dFa
线性变换斜率
double dFb
线性变换截距

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::LinTran(CImgProcess* pTo, double dFa, double dFb)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount != 8) 
		return false;

	BYTE gray;		// 临时变量,存储当前光标像素的灰度值
	int target;		// 临时变量,存储当前光标像素的目标值

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);

			target = dFa * gray + dFb;

			if (target < 0)
				target = 0;

			if (target > 255) 
				target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return true;
}

/**************************************************
BOOL CImgProcess::Histeq(CImgProcess * pTo)

功能：
图像的灰度直方图均衡化方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针

返回值：
BOOL类型，true为成功，false为失败
***************************************************/
BOOL CImgProcess::Histeq(CImgProcess * pTo)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount != 8)
		return false;

	BYTE gray;					// 临时变量,存储当前光标像素的灰度值
	int target;					// 临时变量,存储当前光标像素的目标值
	double pdHist[256];			// 临时变量,存储灰度直方图
	double dTemp;				// 临时变量,存储累加的直方图数据
	this->GenHist(pdHist);

	for (int i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			dTemp = 0;
			gray = GetGray(j, i);
			for (BYTE k = 0; k < gray; k++)
				dTemp += *(pdHist + k);

			target = int(255 * dTemp);

			if (target < 0) 
				target = 0;
			if (target > 255) 
				target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return true;
}

/**************************************************
BOOL CImgProcess::Histst(CImgProcess* pTo, double* pdStdHist)

功能：
图像的灰度直方图规定化方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
double * pdStdHist
标准直方图数组（要求已经归一化的直方图）

返回值：
BOOL类型，true为成功，false为失败
***************************************************/
BOOL CImgProcess::Histst(CImgProcess* pTo, double* pdStdHist)
{
	int i, j;
	if (m_pBMIH->biBitCount != 8)				// 首先检查图像是否是8位灰度图像
		return false;

	BYTE gray;									// 临时变量,存储当前光标像素的灰度值
	int target;									// 临时变量,存储当前光标像素的目标值

	double pdHist[256];							// 临时变量,存储灰度直方图
	this->GenHist(pdHist);

	double dTemp;								// 临时变量,存储累加的直方图数据
	int pdTran[256];							// 临时变量,存储标准直方图均衡化的变换矩阵
	memset(pdTran, -1, sizeof(int) * 256);

	// 求标准直方图的均衡化变换矩阵
	for (i = 0; i < 256; i++)
	{
		dTemp = 0;
		for (BYTE k = 0; k < i; k++)
			dTemp += *(pdStdHist + k);
		*(pdTran + (int)(0.5 + 255 * dTemp)) = i;
	}
	// 去除均衡化变换矩阵中的间断点——插值
	{
		i = 0, j = 0;
		while (i < 255)
		{
			if (*(pdTran + i + 1) != -1)
			{
				i++;
				continue;
			}
			j = 1;
			while ((*(pdTran + i + j) == -1) && ((i + j) <= 255))
			{
				*(pdTran + i + j) = *(pdTran + i);
				j++;
			}
		}
	}

	// 对原图像首先进行灰度均衡化后再进行规定化
	for (i = 0; i < m_pBMIH->biHeight; i++)
	{
		for (j = 0; j < m_pBMIH->biWidth; j++)
		{
			dTemp = 0;
			gray = GetGray(j, i);
			for (BYTE k = 0; k < gray; k++)
				dTemp += *(pdHist + k);
			target = *(pdTran + (int)(255 * dTemp));
			if (target < 0) 
				target = 0;
			if (target > 255) 
				target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	}
	return true;
}

/**************************************************
BOOL CImgProcess::Histst(CImgProcess* pTo, CImgProcess* pStd)

功能：
图像的灰度直方图规定化方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
CImgProcess* pStd
标准目标图像

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::Histst(CImgProcess* pTo, CImgProcess* pStd)
{
	// 标准图像直方图
	double pdStdHist[256];
	pStd->GenHist(pdStdHist);
	return Histst(pTo, pdStdHist);
}

BOOL CImgProcess::GetBitLayer(CImgProcess * pTo, int iLayerLevel)
{
	if (m_pBMIH->biBitCount != 8)				// 首先检查图像是否是8位灰度图像
		return false;

	if (iLayerLevel > 8 || iLayerLevel < 1)
		return false;							// 位面级别错误

	int i, j;
	int arrGrayLevel[8] = {1,2,4,8,16,32,64,128};
	int iGray;

	for (int i = 0; i < m_pBMIH->biHeight; i++)
		for (int j = 0; j < m_pBMIH->biWidth; j++)
		{
			iGray = GetGray(j, i);
			iGray = iGray & arrGrayLevel[iLayerLevel - 1];
			// 写入目标图像
			pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));
		}
	return true;
}

double* CImgProcess::StatisticRGBMoment(CImgProcess * pTo)
{
	// 计算图像的颜色一阶矩、二阶矩、三阶矩，用于图像匹配
	if (pTo->m_pBMIH->biBitCount != 24)							// 首先检查图像的类型
		return NULL;

	int i, j;													// 循环变量
	int iWidth  = pTo->m_pBMIH->biWidth;						// 图像宽度
	int iHeight = pTo->m_pBMIH->biHeight;						// 图像高度
	int iPixelCount = iWidth * iHeight;							// 图像总像素个数
	double dMeanR = 0, dMeanG = 0, dMeanB = 0;					// 图像1 R,G,B三分量的均值
	double dSigmaR = 0, dSigmaG = 0, dSigmaB = 0;				// 图像1 R,G,B三分量的方差
	double dSkewnessR = 0, dSkewnessG = 0, dSkewnessB = 0;		// 图像1 R,G,B三分量的三阶矩
	double* dResult = new double[9];
	

	// 计算颜色一阶矩
	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			dMeanR += GetRValue(RGBPixel);
			dMeanG += GetGValue(RGBPixel);
			dMeanB += GetBValue(RGBPixel);
		}
	}
	dMeanR /= iPixelCount; dMeanG /= iPixelCount; dMeanB /= iPixelCount;

	// 计算颜色二阶矩
	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			dSigmaR += pow(GetRValue(RGBPixel) - dMeanR,2);
			dSigmaG += pow(GetGValue(RGBPixel) - dMeanG,2);
			dSigmaB += pow(GetBValue(RGBPixel) - dMeanB,2);
		}
	}
	dSigmaR = sqrt(dSigmaR / iPixelCount);
	dSigmaG = sqrt(dSigmaG / iPixelCount);
	dSigmaB = sqrt(dSigmaB / iPixelCount);

	// 计算颜色三阶矩
	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			dSkewnessR += pow(GetRValue(RGBPixel) - dMeanR, 3);
			dSkewnessG += pow(GetGValue(RGBPixel) - dMeanG, 3);
			dSkewnessB += pow(GetBValue(RGBPixel) - dMeanB, 3);
		}
	}
	dSkewnessR = pow(dSkewnessR / iPixelCount, 1 / 3);
	dSkewnessG = pow(dSkewnessG / iPixelCount, 1 / 3);
	dSkewnessB = pow(dSkewnessB / iPixelCount, 1 / 3);

	dResult[0] = dMeanR; dResult[1] = dMeanG; dResult[2] = dMeanB;
	dResult[3] = dSigmaR; dResult[4] = dSigmaG; dResult[5] = dSigmaB;
	dResult[6] = dSkewnessR; dResult[7] = dSkewnessG; dResult[8] = dSkewnessB;

	return dResult;
}

/*******************************
void CImgProcess::AddGaussian(CImgProcess *pTo)
功能：对图像添加高斯噪声，均值为零，方差为10
参数：
CImgProcess *pTo:		输出的图像指针
返回值：
无
*******************************/
void CImgProcess::AddGaussian(CImgProcess *pTo, double dRate, double dSigma)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double a, a1, a2;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < dRate)
			{
				a1 = double(rand()) / RAND_MAX;
				a2 = double(rand()) / RAND_MAX;
				a = log(a1) * cos(2 * PI*a2);
				a *= dSigma;
				unsigned char ch = GetGray(j, i);
				a += ch;
				int it = int(a + 0.5);
				if (it < 0)
					it = 0;
				if (it > 255)
					it = 255;
				ch = it;
				pTo->SetPixel(j, i, RGB(ch, ch, ch));
			}
		}
	}
}

/*******************************
void CImgProcess::AddSalt_Pepper(CImgProcess *pTo)
功能：对图像添加椒盐噪声
参数：
CImgProcess *pTo:		输出的图像指针
返回值：
无
*******************************/
void CImgProcess::AddSalt_Pepper(CImgProcess *pTo, double dRate)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double a;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < dRate)
			{
				a = double(rand()) / RAND_MAX;
				if (a < 0.5)
					pTo->SetPixel(j, i, RGB(0, 0, 0));
				else
					pTo->SetPixel(j, i, RGB(255, 255, 255));
			}
		}
	}
}

/*******************************
void CImgProcess::AddRayleigh(CImgProcess *pTo)
功能：对图像添加瑞利噪声
参数：
CImgProcess *pTo:		输出的图像指针
返回值：
无
*******************************/
void CImgProcess::AddRayleigh(CImgProcess *pTo, double dRate, double dSigma)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double a, a0, a1, a2, a3;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < dRate)
			{
				a0 = double(rand()) / RAND_MAX;
				a1 = double(rand()) / RAND_MAX;
				a2 = log(a0) * cos(2 * PI*a1);
				a3 = log(a1) * cos(2 * PI*a0);
				a2 *= dSigma;
				a3 *= dSigma;
				a = sqrt(a2*a2 + a3*a3);
				unsigned char ch = GetGray(j, i);
				a += ch;
				int it = int(a + 0.5);
				if (it < 0)
					it = 0;
				if (it > 255)
					it = 255;
				ch = it;
				pTo->SetPixel(j, i, RGB(ch, ch, ch));
			}
		}
	}
}

void CImgProcess::AddGamma(CImgProcess *pTo, double dA, double dB)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double a, a1, a2;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < dA)
			{
				a1 = double(rand()) / RAND_MAX;
				a2 = double(rand()) / RAND_MAX;
				a = dA * log(a1) * cos(2 * PI*a2);
				a *= dB;
				unsigned char ch = GetGray(j, i);
				a += ch;
				int it = int(a + 0.5);
				if (it < 0)
					it = 0;
				if (it > 255)
					it = 255;
				ch = it;
				pTo->SetPixel(j, i, RGB(ch, ch, ch));
			}
		}
	}
}

void CImgProcess::AddExp(CImgProcess *pTo, double dA)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double dRate = 0.99;
	double a, a1, a2;
	double mean = 1 / dA;
	double dSigma = mean * mean;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < dRate)
			{
				a1 = double(rand()) / RAND_MAX;
				a2 = double(rand()) / RAND_MAX;
				a = log(a1) * 2 * cos(2 * PI*a2);
				a *= dSigma;
				unsigned char ch = GetGray(j, i);
				a += ch;
				int it = int(a + 0.5);
				if (it < 0)
					it = 0;
				if (it > 255)
					it = 255;
				ch = it;
				pTo->SetPixel(j, i, RGB(ch, ch, ch));
			}
		}
	}
}

/*******************************
void CImgProcess::AddUniform(CImgProcess *pTo)
功能：对图像添加均匀噪声
参数：
CImgProcess *pTo:		输出的图像指针
返回值：
无
*******************************/
void CImgProcess::AddUniform(CImgProcess *pTo, double dLow, double dHigh)
{
	int w = m_pBMIH->biWidth;
	int h = m_pBMIH->biHeight;
	int i, j;
	double rate = 0.99;
	double a;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			double t;
			t = double(rand()) / RAND_MAX;
			if (t < rate)
			{
				a = double(rand()) / RAND_MAX;
				unsigned char ch = GetGray(j, i);
				a *= (dHigh - dLow);
				a += dLow;
				a += ch;
				int it = int(a + 0.5);
				if (it < 0)
					it = 0;
				if (it > 255)
					it = 255;
				ch = it;
				pTo->SetPixel(j, i, RGB(ch, ch, ch));
			}
		}
	}
}

// FFT和IFFT
/**************************************************
void CImgProcess::FFT(complex<double> * TD, complex<double> * FD, int r)

功能：
一维快速傅立叶变换

参数：
complex<double> * TD
指向时域数组的指针
complex<double> * FD
指向频域数组的指针
r
2的幂数，即迭代次数
返回值：
无
***************************************************/
void CImgProcess::FFT(complex<double> * TD, complex<double> * FD, int r)
{
	LONG count;												// 傅立叶变换点数
	int	i, j, k;											// 循环变量
	int	bfsize, p;											// 中间变量
	double	angle;											// 角度
	complex<double> *W, *X1, *X2, *X;						// 复变量
	count = 1 << r;											// 计算傅立叶变换点数

	W = new complex<double>[count / 2];						// 分配运算所需存储器
	X1 = new complex<double>[count];
	X2 = new complex<double>[count];
	for (i = 0; i < count / 2; i++)							// 计算加权系数
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double>(cos(angle), sin(angle));
	}

	memcpy(X1, TD, sizeof(complex<double>) * count);		// 将时域点写入X1

	for (k = 0; k < r; k++)									// 采用蝶形算法进行快速傅立叶变换
	{
		for (j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (r - k);
			for (i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				X2[i + p] = X1[i + p] + X1[i + p + bfsize / 2];
				X2[i + p + bfsize / 2] = (X1[i + p] - X1[i + p + bfsize / 2]) * W[i * (1 << k)];
			}
		}
		X = X1;
		X1 = X2;
		X2 = X;
	}

	for (j = 0; j < count; j++)								// 重新排序
	{
		p = 0;
		for (i = 0; i < r; i++)
			if (j&(1 << i))
				p += 1 << (r - i - 1);
		FD[j] = X1[p];
	}

	delete W;												// 释放内存
	delete X1;
	delete X2;
}

/**************************************************
void CImgProcess::IFFT(complex<double> * FD, complex<double> * TD, int r)

功能：
一维快速傅立叶反变换

参数：
complex<double> * FD
指向频域数组的指针
complex<double> * TD
指向时域数组的指针
r
2的幂数，即迭代次数
返回值：
无
***************************************************/
void CImgProcess::IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	LONG count;												// 傅立叶变换点数
	int	i;													// 循环变量
	complex<double> *X;
	count = 1 << r;											// 计算傅立叶变换点数
	X = new complex<double>[count];							// 分配运算所需存储器
	memcpy(X, FD, sizeof(complex<double>) * count);			// 将频域点写入X
	for (i = 0; i < count; i++)								// 求共轭
		X[i] = complex<double>(X[i].real(), -X[i].imag());

	FFT(X, TD, r);											// 调用快速傅立叶变换

	for (i = 0; i < count; i++)								// 求时域点的共轭
		TD[i] = complex<double>(TD[i].real() / count, -TD[i].imag() / count);

	delete X;												// 释放内存
}

/***************************** 几何变换 *****************************/
/*******************
void CImgProcess::ImMove(CImgProcess* pTo, int x, int y)
功能：	平移图像
注：		图像范围不变
参数：	CImgProcess* pTo：处理后得到的图像的 CImgProcess 指针
int x：水平右移距离
int y：垂直下移距离
返回值： 无
*******************/
void CImgProcess::ImMove(CImgProcess* pTo, int x, int y)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;

	if (x > nWidth || y > nHeight)
	{
		MessageBox(NULL, L"超过图片大小", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

	for (i = 0; i < nWidth; i++)
	{
		for (j = 0; j < nHeight; j++)
		{
			if (i - x > 0 && i - x < nWidth && j - y>0 && j - y < nHeight)
				pTo->SetPixel(i, j, GetPixel(i - x, j - y));
			else
				pTo->SetPixel(i, j, RGB(128, 128, 128));
		}//for j
	}//for i

}

/*******************
void CImgProcess::HorMirror(CImgProcess* pTo)
功能：	图像的水平镜象
注：		图像左右镜象
参数：	CImgProcess* pTo：处理后得到的图像的 CImgProcess 指针
返回值：	无
*******************/
void CImgProcess::HorMirror(CImgProcess* pTo)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;
	int u;
	for (i = 0; i < nWidth; i++)
	{
		u = nWidth - i - 1;
		for (j = 0; j < nHeight; j++)
		{
			pTo->SetPixel(i, j, GetPixel(u, j));
		}//for j
	}//for i
}

/*******************
void CImgProcess::VerMirror(CImgProcess* pTo)
功能：	图像的竖直镜象
注：		图像上下镜象
参数：	CImgProcess* pTo：处理后得到的图像的 CImgProcess 指针
返回值： 无
*******************/
void CImgProcess::VerMirror(CImgProcess* pTo)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;
	int u = 0;
	for (i = 0; i < nWidth; i++)
	{
		for (j = 0; j < nHeight; j++)
		{
			u = nHeight - j - 1;
			pTo->SetPixel(i, j, GetPixel(i, u));
		}//for j
	}//for i
}

/*******************
void CImgProcess::Transpose(CImgProcess * pTo)
功能：	图像的转置
注：		图像水平竖直方向互换，图像大小不变
参数：	CImgProcess * pTo：处理后得到的图像的CImgProcess指针
返回值：	无
*******************/
void CImgProcess::Transpose(CImgProcess* pTo)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;
	for (i = 0; i < nWidth; i++)
	{

		for (j = 0; j < nHeight; j++)
		{
			if (j < nWidth && i < nHeight)
				pTo->SetPixel(i, j, GetPixel(j, i));
			else
				pTo->SetPixel(i, j, RGB(128, 128, 128));
		}//for j
	}//for i
}

/*******************
void CImgProcess::Scale(CImgProcess * pTo,double times)
功能：	图像的等比例缩放
注：		包括扩大缩小，图像大小不变
参数：	CImgProcess * pTo：处理后得到的图像的CImgProcess指针
double times：缩放因子
返回值：	无
*******************/
void CImgProcess::Scale1(CImgProcess* pTo, double times)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;

	for (i = 0; i < nWidth; i++)
	{
		for (j = 0; j < nHeight; j++)
		{
			if (int(i * 1 / times + 0.5) < nWidth && int(j * 1 / times + 0.5) < nHeight)
				pTo->SetPixel(i, j, GetPixel(int(i * 1 / times + 0.5), int(j * 1 / times + 0.5)));
			else
				pTo->SetPixel(i, j, RGB(128, 128, 128));
		}//for j
	}//for i
}

void CImgProcess::Scale2(CImgProcess* pTo, double xTimes, double yTimes)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j;

	for (i = 0; i < nWidth; i++)
	{
		for (j = 0; j < nHeight; j++)
		{
			if (int(i * 1 / xTimes + 0.5) < nWidth && int(j * 1 / yTimes + 0.5) < nHeight)
				pTo->SetPixel(i, j, GetPixel(int(i * 1 / xTimes + 0.5), int(j * 1 / yTimes + 0.5)));
			else
				pTo->SetPixel(i, j, RGB(128, 128, 128));
		}//for j
	}//for i
}

/*******************
void CImgProcess::Rotate(CImgProcess * pTo,double ang)
功能：	以原点为中心的图像旋转
注：		围绕左上顶点顺时针旋转，图像范围不变
参数：	CImgProcess * pTo：处理后得到的图像的CImgProcess指针
double ang：顺时针旋转角度，单位度，要求ang>=0 && ang<=360
返回值： 无
*******************/
void CImgProcess::Rotate(CImgProcess* pTo, double ang)
{
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();

	int i, j; //目标图像坐标
	int u, v; //源图像坐标

	for (i = 0; i < nWidth; i++)
	{

		for (j = 0; j < nHeight; j++)
		{
			u = int(i*cos(ang*PI / 180) + j*sin(ang*PI / 180) + 0.5);
			v = int(j*cos(ang*PI / 180) - i*sin(ang*PI / 180) + 0.5);
			if (u < nWidth && v < nHeight && u >= 0 && v >= 0)
				pTo->SetPixel(i, j, GetPixel(u, v));
			else
				pTo->SetPixel(i, j, RGB(128, 128, 128));
		}//for j
	}//for i
}

int CImgProcess::InterpBilinear(double x, double y)
{
	if (int(y) == 300)
		int cc = 1;

	// 四个最临近象素的坐标(i1, j1), (i2, j1), (i1, j2), (i2, j2)
	int	x1, x2;
	int	y1, y2;

	// 四个最临近象素值
	unsigned char	f1, f2, f3, f4;

	// 二个插值中间值
	unsigned char	f12, f34;

	double	epsilon = 0.0001;

	// 计算四个最临近象素的坐标
	x1 = (int)x;
	x2 = x1 + 1;
	y1 = (int)y;
	y2 = y1 + 1;


	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	if ((x < 0) || (x > nWidth - 1) || (y < 0) || (y > nHeight - 1))
	{
		// 要计算的点不在源图范围内，返回-1
		return -1;
	}
	else
	{
		if (fabs(x - nWidth + 1) <= epsilon)
		{
			// 要计算的点在图像右边缘上
			if (fabs(y - nHeight + 1) <= epsilon)
			{
				// 要计算的点正好是图像最右下角那一个象素，直接返回该点象素值
				f1 = (unsigned char)GetGray(x1, y1);
				return f1;
			}
			else
			{
				// 在图像右边缘上且不是最后一点，直接一次插值即可
				f1 = (unsigned char)GetGray(x1, y1);
				f3 = (unsigned char)GetGray(x1, y2);

				// 返回插值结果
				return ((int)(f1 + (y - y1) * (f3 - f1)));
			}
		}
		else if (fabs(y - nHeight + 1) <= epsilon)
		{
			// 要计算的点在图像下边缘上且不是最后一点，直接一次插值即可
			f1 = (unsigned char)GetGray(x1, y1);
			f2 = (unsigned char)GetGray(x2, y1);

			// 返回插值结果
			return ((int)(f1 + (x - x1) * (f2 - f1)));
		}
		else
		{
			// 计算四个最临近象素值
			f1 = (unsigned char)GetGray(x1, y1);
			f2 = (unsigned char)GetGray(x2, y1);
			f3 = (unsigned char)GetGray(x1, y2);
			f4 = (unsigned char)GetGray(x2, y2);

			// 插值1
			f12 = (unsigned char)(f1 + (x - x1) * (f2 - f1));

			// 插值2
			f34 = (unsigned char)(f3 + (x - x1) * (f4 - f3));

			// 插值3
			return ((int)(f12 + (y - y1) * (f34 - f12)));
		}
	}
}

/***************************** 颜色空间变换 *****************************/
void CImgProcess::RGB2HSI(CImgProcess* pTo)
{
	int nHeight = GetHeight();		// 读取图片高度
	int nWidth = GetWidthPixel();	// 读取图片宽度
	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);

			//抽取RGB分量
			double R = GetRValue(RGBPixel) / 255.0;
			double G = GetGValue(RGBPixel) / 255.0;
			double B = GetBValue(RGBPixel) / 255.0;

			//RGB2HSI的算法转换
			double maxRGB = max(max(R, G), B);
			double minRGB = min(min(R, G), B);
			double H;
			double S;
			double I;
			double Temp1, Temp2, Radians, Angle;

			I = (R + G + B) / 3;

			if (I < 0.078431)
				S = 0;
			else if (I > 0.920000)
				S = 0;
			else
				S = 1.0 - (3.0*minRGB) / (R + G + B);

			if (maxRGB == minRGB)
			{
				H = 0;
				S = 0;
			}

			Temp1 = ((R - G) + (R - B)) / 2;
			Temp2 = (R - G)*(R - G) + (R - B)*(G - B);
			double Q = Temp1 / sqrt(Temp2);
			if (Q > 0.9999999999)
				Radians = 0;
			else if (Q < -0.9999999999)
				Radians = PI;
			else
				Radians = acos(Q);
			Angle = Radians*180.0 / PI;
			if (B > G)
				H = (360.0 - Angle);
			else
				H = Angle;

			I = 255 * I;
			S = 255 * S;

			//将分量联合形成HSI图像
			pTo->SetPixel(j, i, RGB(H, S, I));
		}//for j
	}//for i
}

void CImgProcess::HSI2RGB(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取HSI分量
			double H = GetRValue(RGBPixel);
			double S = GetGValue(RGBPixel) / 255.0;
			double I = GetBValue(RGBPixel) / 255.0;
			double R, G, B;

			//HSI2RGB的算法转换
			if (H >= 0 && H < 120)
			{
				H = H;
				B = I*(1.0 - S);
				R = I*(1.0 + ((S*cos(H)) / cos(60 - H)));
				G = 3.0*I - R - B;
			}
			else if (H >= 120 && H < 240)
			{
				H = H - 120;
				R = I*(1.0 - S);
				G = I*(1.0 + ((S*cos(H)) / cos(60 - H)));
				B = 3.0*I - R - G;
			}
			else
			{
				H = H - 240;
				G = I*(1.0 - S);
				B = I*(1.0 + ((S*cos(H)) / cos(60 - H)));
				R = 3.0*I - B - G;
			}
			R *= 255.0;
			G *= 255.0;
			B *= 255.0;

			//将分量联合形成RGB图像
			pTo->SetPixel(j, i, RGB(R, G, B));
		}
	}
}

void CImgProcess::RGB2Gray(CImgProcess * pTo, int iType)
{
	// 彩色图像灰度化有三种方法：最大值法、平均值法和加权平均值法
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i, j;
	int iGray;

	if (iType == 1)											// 最大值法
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				//抽取RGB分量
				int R = GetRValue(RGBPixel);
				int G = GetGValue(RGBPixel);
				int B = GetBValue(RGBPixel);
				
				if (R > G && R > B)
					iGray = R;
				if(G > B && G > R)
					iGray = G;
				if (B > R && B > G)
					iGray = B;

				//将分量联合形成灰度图像
				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));

			}//for j
		}//for i
	}

	if (iType == 2)											// 平均值法		
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				//抽取RGB分量
				int R = GetRValue(RGBPixel);
				int G = GetGValue(RGBPixel);
				int B = GetBValue(RGBPixel);
				iGray = (R + G + B) / 3;

				//将分量联合形成灰度图像
				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));

			}//for j
		}//for i
	}

	if (iType == 3)											// 加权平均值法
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPixel = GetPixel(j, i);
				//抽取RGB分量
				int R = GetRValue(RGBPixel);
				int G = GetGValue(RGBPixel);
				int B = GetBValue(RGBPixel);
				iGray = 0.299*R + 0.587*G + 0.114*B;

				//将分量联合形成灰度图像
				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));

			}//for j
		}//for i
	}
}

void CImgProcess::Gray2RGB(CImgProcess *pTo, int iType)
{
	// 使用伪彩色、彩虹映射表完成伪彩色增强
	// 低灰度→蓝色、中灰度→绿色、高灰度→红色
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i, j;
	int R, G, B;

	if (iType == 1)
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				int iGray = GetGray(j, i);
				R = abs(0 - iGray);
				G = abs(127 - iGray);
				B = abs(255 - iGray);

				// 将分量联合形成RGB图像
				pTo->SetPixel(j, i, RGB(R, G, B));
			}
		}
	}
	
	if (iType == 2)
	{
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				int iGray = GetGray(j, i);

				if (iGray <= 51)
				{
					R = 0;
					G = iGray * 5;
					B = 255;
				}

				else if (iGray <= 102 && iGray > 51)
				{
					iGray -= 51;
					R = 0;
					G = 255;
					B = 255 - iGray * 5;
				}

				else if (iGray <= 153 && iGray > 102)
				{
					iGray -= 102;
					R = iGray * 5;
					G = 255;
					B = 0;
				}

				else if (iGray <= 204 && iGray > 153)
				{
					iGray -= 153;
					R = 255;
					G = 255 - (128 * iGray / 51 + 0.5);
					B = 0;
				}

				else
				{
					iGray -= 204;
					R = 255;
					G = 127 - (127 * iGray / 51 + 0.5);
					B = 0;
				}
				// 将分量联合形成RGB图像
				pTo->SetPixel(j, i, RGB(R, G, B));
			}
		}
	}
}

void CImgProcess::GetRGBLevel(CImgProcess * pTo, int iType)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取RGB分量
			int R = GetRValue(RGBPixel);
			int G = GetGValue(RGBPixel);
			int B = GetBValue(RGBPixel);
			int C, M, Y;

			if (iType == 1)
				pTo->SetPixel(j, i, RGB(R, 0, 0));
			
			else if(iType == 2)
				pTo->SetPixel(j, i, RGB(0, G, 0));

			else
				pTo->SetPixel(j, i, RGB(0, 0, B));
		}//for j
	}//for i

}

void CImgProcess::RGB2CMY(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取RGB分量
			int R = GetRValue(RGBPixel);
			int G = GetGValue(RGBPixel);
			int B = GetBValue(RGBPixel);
			int C, M, Y;

			C = 255 - R;
			M = 255 - G;
			Y = 255 - B;

			//将分量联合形成CMY图像
			pTo->SetPixel(j, i, RGB(C, M, Y));
		}//for j
	}//for i
}

void CImgProcess::CMY2RGB(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取CMY分量
			double C = GetRValue(RGBPixel) / 255.0;
			double M = GetGValue(RGBPixel) / 255.0;
			double Y = GetBValue(RGBPixel) / 255.0;
			double R, G, B;

			R = 1 - C;
			G = 1 - M;
			B = 1 - Y;

			R *= 255.0;
			G *= 255.0;
			B *= 255.0;

			//将分量联合形成CMY图像
			pTo->SetPixel(j, i, RGB(R, G, B));
		}
	}
}

void CImgProcess::RGB2HSV(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取RGB分量
			double R = GetRValue(RGBPixel) / 255.0;
			double G = GetGValue(RGBPixel) / 255.0;
			double B = GetBValue(RGBPixel) / 255.0;

			//计算HSV
			double H, S, V, MAX, MIN, TEMP;
			MAX = max(max(R, G), B);
			MIN = min(min(R, G), B);
			V = MAX;
			TEMP = MAX - MIN;

			if (MAX != 0)
				S = TEMP / MAX;
			else
			{
				S = 0;
				return;						//H = UNDEFINEDCOLOR;
			}
			if (R == MAX)
				H = (G - B) / TEMP;
			else if (G == MAX)
				H = 2 + (B - R) / TEMP;
			else
				H = 4 + (R - G) / TEMP;
			H *= 60;
			if (H < 0)
				H += 360;

			//将HSV分量化为能在计算机上范围为[0，255]可显示的图像
			H /= 360.0;
			H *= 255.0;
			S *= 255.0;
			V *= 255.0;

			//将分量联合形成HSV图像
			pTo->SetPixel(j, i, RGB(H, S, V));
		}
	}
}

void CImgProcess::HSV2RGB(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;

	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取HSV分量
			double H = (GetRValue(RGBPixel) / 255.0)*360.0;
			double S = GetGValue(RGBPixel) / 255.0;
			double V = GetBValue(RGBPixel) / 255.0;

			//计算RGB
			double R, G, B, f, p, q, t, TEMP;
			int n;

			if (S == 0)
				R = G = B = V;

			n = floor(H / 60);
			TEMP = H / 60;
			f = TEMP - n;
			p = V*(1 - S);
			q = V*(1 - f*S);
			t = V*(1 - (1 - f)*S);

			switch (n)
			{
			case 0:
				R = V;
				G = t;
				B = p;
				break;
			case 1:
				R = q;
				G = V;
				B = p;
				break;
			case 2:
				R = p;
				G = V;
				B = t;
				break;
			case 3:
				R = p;
				G = q;
				B = V;
				break;
			case 4:
				R = t;
				G = p;
				B = V;
				break;
			default:  //case 5:
				R = V;
				G = p;
				B = q;
				break;
			}

			R *= 255.0;
			G *= 255.0;
			B *= 255.0;

			//将分量联合形成RGB图像
			pTo->SetPixel(j, i, RGB(R, G, B));
		}// for j
	}//for i
}

void CImgProcess::RGB2YUV(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取RGB分量
			double R = GetRValue(RGBPixel);
			double G = GetGValue(RGBPixel);
			double B = GetBValue(RGBPixel);

			//计算YUV
			double Y, U, V;
			Y = 0.299*R + 0.587*G + 0.114*B;
			U = (B - Y)*0.567;
			V = (R - Y)*0.713;

			//防止溢出
			if (Y > 255)
				Y = 255;
			if (Y < 0)
				Y = 0;
			if (U > 255)
				U = 255;
			if (U < 0)
				U = 0;
			if (V > 255)
				V = 255;
			if (V < 0)
				V = 0;

			//将分量联合形成YUV图像
			pTo->SetPixel(j, i, RGB(Y, U, V));
		}//for j
	}//for i
}

void CImgProcess::YUV2RGB(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取YUV分量
			double Y = GetRValue(RGBPixel);
			double U = GetGValue(RGBPixel);
			double V = GetBValue(RGBPixel);

			//计算RGB
			double R, G, B;
			R = Y + 1.402*V;
			G = Y - 0.344*U - 0.714*V;
			B = Y + 1.772*U;

			//防止溢出
			if (R > 255)
				R = 255;
			if (R < 0)
				R = 0;
			if (G > 255)
				G = 255;
			if (G < 0)
				G = 0;
			if (B > 255)
				B = 255;
			if (B < 0)
				B = 0;

			//将分量联合形成RGB图像
			pTo->SetPixel(j, i, RGB(R, G, B));
		}
	}
}

void CImgProcess::RGB2YIQ(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取RGB分量
			double R = GetRValue(RGBPixel);
			double G = GetGValue(RGBPixel);
			double B = GetBValue(RGBPixel);

			//计算YUV
			double Y, I, Q;
			Y = 0.299*R + 0.587*G + 0.114*B;
			I = 0.596*R - 0.274*G - 0.322*B;
			Q = 0.211*R - 0.523*G + 0.312*B;

			//防止溢出
			if (Y > 255)
				Y = 255;
			if (Y < 0)
				Y = 0;
			if (I > 255)
				I = 255;
			if (I < 0)
				I = 0;
			if (Q > 255)
				Q = 255;
			if (Q < 0)
				Q = 0;

			//将分量联合形成YIQ图像
			pTo->SetPixel(j, i, RGB(Y, I, Q));
		}
	}
}

void CImgProcess::YIQ2RGB(CImgProcess *pTo)
{
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			COLORREF RGBPixel = GetPixel(j, i);
			//抽取YIQ分量
			double Y = GetRValue(RGBPixel);
			double I = GetGValue(RGBPixel);
			double Q = GetBValue(RGBPixel);

			//计算RGB
			double R, G, B;
			R = Y + 0.956*I + 0.114*Q;
			G = Y - 0.272*I - 0.647*Q;
			B = Y - 1.106*I + 1.703*Q;

			//防止溢出
			if (R > 255)
				R = 255;
			if (R < 0)
				R = 0;
			if (G > 255)
				G = 255;
			if (G < 0)
				G = 0;
			if (B > 255)
				B = 255;
			if (B < 0)
				B = 0;

			//将分量联合形成RGB图像
			pTo->SetPixel(j, i, RGB(R, G, B));
		}//for j
	}//for i
}

void CImgProcess::TemplateMatch(CImgProcess* pTo, CImgProcess* pTemplate)
{
	int i, j, m, n;								// 循环变量
	double dSumT;								// 模板元素的平方和
	double dSumS;								// 图像子区域元素的平方和
	double dSumST;								// 图像子区域和模板的点积	
	double R;									// 响应值
	double MaxR;								// 记录当前的最大响应
	int nMaxX;									// 最大响应出现位置X
	int nMaxY;									// 最大响应出现位置Y
	int nHeight = GetHeight();					// 图像的高
	int nWidth = GetWidthPixel();				// 图像的宽
	int nTplHeight = pTemplate->GetHeight();	// 模板的高
	int nTplWidth = pTemplate->GetWidthPixel();	// 模板的宽

	dSumT = 0;									//计算 dSumT
	for (m = 0; m < nTplHeight; m++)
	{
		for (n = 0; n < nTplWidth; n++)
		{
			// 模板图像第m行，第n个象素的灰度值
			int nGray = pTemplate->GetGray(n, m);
			dSumT += (double)nGray*nGray;
		}
	}

	MaxR = 0;									//找到图像中最大响应的出现位置
	for (i = 0; i < nHeight - nTplHeight + 1; i++)
	{
		for (j = 0; j < nWidth - nTplWidth + 1; j++)
		{
			dSumST = 0;
			dSumS = 0;

			for (m = 0; m < nTplHeight; m++)
			{
				for (n = 0; n < nTplWidth; n++)
				{
					// 原图像第i+m行，第j+n列象素的灰度值
					int nGraySrc = GetGray(j + n, i + m);

					// 模板图像第m行，第n个象素的灰度值
					int nGrayTpl = pTemplate->GetGray(n, m);

					dSumS += (double)nGraySrc*nGraySrc;
					dSumST += (double)nGraySrc*nGrayTpl;
				}
			}

			R = dSumST / (sqrt(dSumS)*sqrt(dSumT));//计算相关响应

			//与最大相似性比较
			if (R > MaxR)
			{
				MaxR = R;
				nMaxX = j;
				nMaxY = i;
			}
		}
	}

	pTo->InitPixels(255); //清空目标图像
	//将找到的最佳匹配区域复制到目标图像
	for (m = 0; m < nTplHeight; m++)
	{
		for (n = 0; n < nTplWidth; n++)
		{
			int nGray = pTemplate->GetGray(n, m);
			pTo->SetPixel(nMaxX + n, nMaxY + m, RGB(nGray, nGray, nGray));
		}
	}
}

BOOL CImgProcess::IsBiImg(CImgProcess * pTo)
{
	int i, j;
	int iTemp, iCount;
	int nHeight = pTo->GetHeight();
	int nWidth = pTo->GetWidthPixel();
	
	iTemp = 0;
	iCount = nHeight * nWidth;

	// 位深为1的图形一定是二值图
	if (pTo->m_pBMIH->biBitCount == 1)
		return TRUE;

	// 8位图和24位图必须只能有黑白两种颜色
	if (pTo->m_pBMIH->biBitCount == 8)
	{
		int iGray;
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				iGray = pTo->GetGray(j, i);
				iTemp++;
				if (iGray == 0 || iGray == 255)
					continue;
				else
					break;
			}
		}
	}

	if (pTo->m_pBMIH->biBitCount == 24)
	{
		int R, G, B;
		for (i = 0; i < nHeight; i++)
		{
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPix1 = pTo->GetPixel(j, i);
				R = GetRValue(RGBPix1);
				G = GetGValue(RGBPix1);
				B = GetBValue(RGBPix1);
				iTemp++;

				// RGB不为（0,0,0）或者（255,255,255）
				if ((R == 0 && B == 0 && G == 0)
					|| (R == 255 && B == 255 && G == 255))
					continue;
				else
					break;
			}
		}
	}
	if (iTemp == iCount)
		return TRUE;
	else
		return FALSE;
}

void CImgProcess::PicAdd(CImgProcess * pTo, CImgProcess * pStd)
{
	int nHeight, nWidth, nHeight1, nWidth1, nHeight2, nWidth2;
	int iGray, iGray1, iGray2;
	double R, G, B, R1, B1, G1, R2, B2, G2;
	int i, j;

	nHeight1 = pTo->GetHeight();
	nWidth1 = pTo->GetWidthPixel();
	nHeight2 = pStd->GetHeight();
	nWidth2 = pStd->GetWidthPixel();
	
	nHeight = nHeight1 < nHeight2 ? nHeight1 : nHeight2;
	nWidth = nWidth1 < nWidth2 ? nWidth1 : nWidth2;

	if (pTo->m_pBMIH->biBitCount == 8)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				iGray1 = pTo->GetGray(j, i);
				iGray2 = pStd->GetGray(j, i);
				iGray = iGray1 + iGray2;

				if (iGray > 255)
					iGray = 255;
				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));
			}
	}

	if (pTo->m_pBMIH->biBitCount == 24)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPix1 = pTo->GetPixel(j, i);
				COLORREF RGBPix2 = pStd->GetPixel(j, i);

				R1 = GetRValue(RGBPix1);
				G1 = GetGValue(RGBPix1);
				B1 = GetBValue(RGBPix1);

				R2 = GetRValue(RGBPix2);
				G2 = GetGValue(RGBPix2);
				B2 = GetBValue(RGBPix2);

				R = R1 + R2;
				G = G1 + G2;
				B = B1 + B2;

				if (R > 255) R = 255;
				if (G > 255) G = 255;
				if (B > 255) B = 255;

				pTo->SetPixel(j, i, RGB(R, G, B));
			}
	}
}

void CImgProcess::PicSub(CImgProcess * pTo, CImgProcess * pStd)
{
	int nHeight, nWidth, nHeight1, nWidth1, nHeight2, nWidth2;
	int iGray, iGray1, iGray2;
	double R, G, B, R1, B1, G1, R2, B2, G2;
	int i, j;

	nHeight1 = pTo->GetHeight();
	nWidth1 = pTo->GetWidthPixel();
	nHeight2 = pStd->GetHeight();
	nWidth2 = pStd->GetWidthPixel();

	nHeight = nHeight1 < nHeight2 ? nHeight1 : nHeight2;
	nWidth = nWidth1 < nWidth2 ? nWidth1 : nWidth2;

	if (pTo->m_pBMIH->biBitCount == 8)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				iGray1 = pTo->GetGray(j, i);
				iGray2 = pStd->GetGray(j, i);
				iGray = iGray1 - iGray2;

				if (iGray < 0)
					iGray = 0;
				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));
			}
	}

	if (pTo->m_pBMIH->biBitCount == 24)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPix1 = pTo->GetPixel(j, i);
				COLORREF RGBPix2 = pStd->GetPixel(j, i);

				R1 = GetRValue(RGBPix1);
				G1 = GetGValue(RGBPix1);
				B1 = GetBValue(RGBPix1);

				R2 = GetRValue(RGBPix2);
				G2 = GetGValue(RGBPix2);
				B2 = GetBValue(RGBPix2);

				R = R1 - R2;
				G = G1 - G2;
				B = B1 - B2;

				if (R < 0) R = 0;
				if (G < 0) G = 0;
				if (B < 0) B = 0;

				pTo->SetPixel(j, i, RGB(R, G, B));
			}
	}
}

void CImgProcess::PicMul(CImgProcess * pTo, CImgProcess * pStd)
{
	int nHeight, nWidth, nHeight1, nWidth1, nHeight2, nWidth2;
	int iGray, iGray1, iGray2;
	double R, G, B, R1, B1, G1, R2, B2, G2;
	int i, j;

	nHeight1 = pTo->GetHeight();
	nWidth1 = pTo->GetWidthPixel();
	nHeight2 = pStd->GetHeight();
	nWidth2 = pStd->GetWidthPixel();

	nHeight = nHeight1 < nHeight2 ? nHeight1 : nHeight2;
	nWidth = nWidth1 < nWidth2 ? nWidth1 : nWidth2;

	if (pTo->m_pBMIH->biBitCount == 8)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				iGray1 = pTo->GetGray(j, i);
				iGray2 = pStd->GetGray(j, i);
				iGray = iGray1 * iGray2;
				
				if (iGray > 255)
					iGray = 255;

				pTo->SetPixel(j, i, RGB(iGray, iGray, iGray));
			}
	}

	if (pTo->m_pBMIH->biBitCount == 24)
	{
		for (i = 0; i < nHeight; i++)
			for (j = 0; j < nWidth; j++)
			{
				COLORREF RGBPix1 = pTo->GetPixel(j, i);
				COLORREF RGBPix2 = pStd->GetPixel(j, i);

				R1 = GetRValue(RGBPix1);
				G1 = GetGValue(RGBPix1);
				B1 = GetBValue(RGBPix1);

				R2 = GetRValue(RGBPix2);
				G2 = GetGValue(RGBPix2);
				B2 = GetBValue(RGBPix2);

				R = R1 * R2;
				G = G1 * G2;
				B = B1 * B2;

				if (R > 255) R = 255;
				if (G < 255) G = 255;
				if (B < 255) B = 255;

				pTo->SetPixel(j, i, RGB(R, G, B));
			}
	}
}

vector< vector<int> > CImgProcess::GetGrayMatrix(POINT ptD1, POINT ptD2)
{
	vector< vector<int> > GrayMat; //灰度共现矩阵

	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();
	int i, j; //循环变量
	int nGray;

	//统计灰度级总数
	int nMaxGray = 0;
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			nGray = GetGray(j, i);
			if (nGray > nMaxGray)
				nMaxGray = nGray;
		}
	}

	//初始化灰度共现矩阵
	vector<int> vecRow(nMaxGray + 1, 0);
	for (i = 0; i < nMaxGray + 1; i++)
		GrayMat.push_back(vecRow);


	//统计符合空间位置关系并分别具有像素值gray1, gray2的像素对数目
	int i2, j2; //与(i, j)具有位置关系ptD1和ptD2的点
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			nGray = GetGray(j, i);

			i2 = i + ptD1.y;
			j2 = j + ptD1.x;
			if (((i2 >= 0) && (i2 < nHeight)) && ((j2 >= 0) && (j2 < nWidth)))
			{
				int nGrayD1 = GetGray(j2, i2);
				GrayMat[nGray][nGrayD1]++;//相应计数加一
			}

			i2 = i + ptD2.y;
			j2 = j + ptD2.x;
			if (((i2 >= 0) && (i2 < nHeight)) && ((j2 >= 0) && (j2 < nWidth)))
			{
				int nGrayD2 = GetGray(j2, i2);
				GrayMat[nGray][nGrayD2]++;//相应计数加一
			}
		}
	}

	//返回灰度共现矩阵
	return GrayMat;
}