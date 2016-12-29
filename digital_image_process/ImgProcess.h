#if !defined(AFX_IMAGE_H__D566CE6A_BA81_4157_8E6A_748DA096668F__INCLUDED_)
#define AFX_IMAGE_H__D566CE6A_BA81_4157_8E6A_748DA096668F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Img.h"
#include "math.h"
#include <complex>

using namespace std;

extern double Template_Log[];
extern double Template_VSobel[];
extern double Template_HSobel[];
extern double Template_Smooth_Gauss[];
extern double Template_Smooth_Avg[];
extern double Template_Laplacian1[];
extern double Template_Laplacian2[];

#define PI 3.141592654
#define e  2.7182818284

struct SLineInfo
{
	int nPixels;
	int nAngle;  // -180   +180
	int nDist;   // 0      +Max
	int GetLineAngle(SLineInfo *pLine)
	{

		int nRet = abs(pLine->GetAngle360() - GetAngle360());
		if (nRet > 180)
			nRet = 360 - nRet;

		if (nRet > 90)
			nRet = 180 - nRet;


		return abs(nRet);
	}

	int GetLineDist(SLineInfo *pLine)
	{
		if (nAngle * pLine->nAngle < 0)
			return abs(nDist + pLine->nDist);

		return abs(nDist - pLine->nDist);
	}

	void AddDistWithAngle(int nAdd, int n)
	{
		if (n < 0)
			nAdd *= -1;

		nDist += nAdd;
	}

	int GetDistWithAngle(int n)
	{
		int nRet = nDist;
		if (n < 0)
			nRet *= -1;

		return nRet;
	}

	int GetAngle360()
	{
		int nRet = nAngle;
		if (nAngle < 0)
			nRet = abs(nAngle + 180) + 180;
		return nRet;
	}

	int GetY(int x)
	{
		int nRet = 0;
		double fRadian = nAngle*PI / 180.0;


		if (sin(fRadian) != 0)
			nRet = (nDist - x*cos(fRadian)) / sin(fRadian);

		return nRet;

	}

	int GetX(int y)
	{
		int nRet = 0;
		double fRadian = nAngle*PI / 180.0;
		if (cos(fRadian) != 0)
			nRet = (nDist - y*sin(fRadian)) / cos(fRadian);

		return nRet;
	}

};

struct MYPOINT
{
	double x;
	double y;
};

// CImgProcess封装了各种图像处理的标准算法
class CImgProcess : public CImg
{
public:
	CImgProcess();
	virtual ~CImgProcess();
	CImgProcess& operator = (CImg& img);							// 从基类的转换

	/*************** 图像的点运算*****************/
	BOOL GenHist(double * hist, int n = 256);						// 生成灰度直方图
	BOOL GenRGBHist(double * hist, int iType, int n = 256);			// 生成RGB的颜色直方图
	BOOL ParLinTran(CImgProcess * pTo, BYTE x1, BYTE x2,
		BYTE y1, BYTE y2);											// 分段线性变换
	BOOL LinTran(CImgProcess * pTo, double dFa, double dFb);		// 线性变换
	BOOL LogTran(CImgProcess * pTo, double C);						// 对数变换
	BOOL GammaTran(CImgProcess * pTo, double gamma,
		double comp = 0);											// 指数变换
	BOOL WindowTran(CImgProcess * pTo, BYTE lowThre, BYTE highThre);// 窗口变换
	BOOL Histeq(CImgProcess * pTo);									// 灰度均衡化
	BOOL Histst(CImgProcess * pTo, double* pdStdHist);				// 直方图规定化，直接匹配直方图
	BOOL Histst(CImgProcess * pTo, CImgProcess* pStd);				// 直方图规定化，匹配标准图像的直方图
	BOOL GetBitLayer(CImgProcess* pTo, int iLayerLevel);			// 获取灰度图的各级位面图
	double* CImgProcess::StatisticRGBMoment(CImgProcess * pTo);		// 统计图像的RGB颜色矩
	int* CImgProcess::StatisticRGBHist(CImgProcess * pTo, CImgProcess* pStd);	// 计算两图像的RGB直方图直接的差异

	/*************** 图像的几何变换 *****************/
	void ImMove(CImgProcess* pTo, int x, int y);					// 图像平移
	void HorMirror(CImgProcess* pTo);								// 图像水平镜象
	void VerMirror(CImgProcess* pTo);								// 图像垂直镜象
	void Transpose(CImgProcess* pTo);								// 图像转置
	void Scale1(CImgProcess* pTo, double times);					// 图像等比例缩放
	void Scale2(CImgProcess* pTo, double xTimes, double yTimes);	// 图像畸变缩放
	void Rotate(CImgProcess* pTo, double ang);						// 图像旋转

	/************** 噪声 **************/
	void AddGaussian(CImgProcess *pTo, double dRate, double dSigma);// 高斯噪声
	void AddSalt_Pepper(CImgProcess *pTo, double dRate);			// 椒盐噪声
	void AddRayleigh(CImgProcess *pTo,double dRata, double dSigma); // 瑞利噪声
	void AddGamma(CImgProcess *pTo, double dA, double dB);			// 伽马噪声
	void AddExp(CImgProcess *pTo, double dRate);					// 指数噪声
	void AddUniform(CImgProcess *pTo, double dLow, double dHigh);	// 均匀噪声

	/************** 投影变换复原 ***************/
	int m_nBasePt;													// 基准点对儿的数目
	BOOL ImProjRestore(CImgProcess* pTo, CPoint *pPointBase,
		CPoint *pPointSampl, bool bInterp);							// 投影变形校正
	void GetProjPara(CPoint *pPointBase, CPoint *pPointSampl,
		double *pDbProjPara);										// 根据基准点确定变换参数
	BOOL InvMat(double** ppDbMat, int nLen);						// 矩阵求逆
	void ProdMat(double** ppDbMat, double* pDbSrc2,
		double* pDbDest, int y, int x, int z);
	struct MYPOINT ProjTrans(CPoint pt, double* pDbProjPara);		// 根据变换参数对点pt实施投影变换
	int InterpBilinear(double x, double y);							// 返回(x,y)点双线性插值后的灰度

	/*************** 空域滤波 *****************/
	void Template(CImgProcess *pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, double *pfArray, double fCoef);	// 通用模板操作
	int GetGraySum(int * pAryGray, int nFilterLen);					// 取得模板窗口内灰度值的和值
	int GetMedianValue(int * pAryGray, int nFilterLen);				// 取得模板窗口中值
	int GetMidValue(int * pAryGray, int nFilterLen);				// 取得模板窗口中点值
	int GetMeanValue(int * pAryGray, int nFilterLen);				// 取得模板窗口均值
	int GetGeoMeanValue(int * pAryGray, int nFilterLen);			// 取得模板窗口几何均值
	int GetHarmonicMeanValue(int * pAryGray, int nFilterLen);		// 取得模板窗口谐波均值
	int GetInvHarmonicMeanValue(int * pAryGray, int nFilterLen, 
		int Q);														// 取得模板窗口逆谐波均值，Q为均值
	int GetAlphaMeanValue(int * pAryGray, int nFilterLen, int d);	// 取得模板窗口阿尔法均值，d为将要删去的像素点的个数
	int GetMaxValue(int * pAryGray, int nFilterLen);				// 取得模板窗口最大值
	int GetMinValue(int * pAryGray, int nFilterLen);				// 取得模板窗口最小值
	double GetGradientSum(double* pAryGradient, int nFilterLen);	// 取得模板窗口内的梯度之和
	void LowFilter1(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 邻域均值滤波
	void LowFilter2(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 简单加权均值滤波
	void LowFilter3(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 梯度加权均值滤波
	void LowFilter4(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX, int iThreshold);				// 超限邻域均值滤波
	void LowFilter5(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX, int iThreshold, int iCnt);	// 噪声门限滤波
	void LowFilter6(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 几何均值滤波器
	void LowFilter7(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 谐波均值滤波器
	void LowFilter8(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX, int Q);						// 逆谐波均值滤波器
	void LowFilter9(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX, int d);						// 修正阿尔法均值滤波器
	void MidFilter(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 中点滤波器
	void HighFilter1(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 基本高通滤波
	void HighFilter2(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX, double dGain);				// 高增益滤波
	void MedianFilter(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 中值滤波
	void MaxFilter(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 最大值滤波
	void MinFilter(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 最小值滤波
	void AdaptiveMedianFilter(CImgProcess *pTo, int nFilterH,
		int nFilterW, int nFilterMY, int nFilterMX);				// 自适应中值滤波
	void FilterSobel(CImgProcess *pTo);								// Sobel梯度锐化
	void EnhanceFilter(CImgProcess *pTo, double dProportion, int nTempH, int nTempW,
		int nTempMY, int nTempMX, double *pfArray, double fCoef);	// 高提升滤波
	void EnhaGaussianF(CImgProcess *pTo, int nFilterH, int nFilterW,
		int nFilterMY, int nFilterMX);								// 高斯平滑滤波
	void EnhaAdaptiveSmooth(CImgProcess *pTo, int nFilterH,
		int nFilterW, int nFilterMY, int nFilterMX);				// 自适应均值滤波

	/*************** 频率域空域滤波 *****************/
private:

	void FFT(complex<double> * TD, complex<double> * FD, int r);	// FFT
	void IFFT(complex<double> * FD, complex<double> * TD, int r);	// IFFT
	void dct8x8(double *in, double *out);							// 8*8DCT
	void idct8x8(double *in, double *out);							// IDCT
	void quant(double *in, int *out);								// 量化
	void iquant(int *in, double *out);								// 反量化
	int Quant_table[8][8]											// DCT量化数组 
	=	{ 16,11,10,16,24,40,51,61,
		12,12,14,19,26,58,60,55,
		14,13,16,24,40,57,69,56,
		14,17,22,29,51,87,80,62,
		18,22,37,56,68,109,103,77,
		24,35,55,64,81,104,113,92,
		49,64,78,87,103,121,120,101,
		72,92,95,98,112,100,103,99 };

public:

	BOOL FFT2(CImgProcess * pTo, BOOL bExpand = FALSE,
		complex<double> * pOutput = NULL, BYTE bFillColor = 255);	// FFT2
	BOOL IFFT2(CImgProcess * pTo, complex<double> * pInput, long lWidth,
		long lHeight, long lOutW = 0, long lOutH = 0);				// IFFT2
	BOOL fft2(CImgProcess * pTo);									// FFT2
	BOOL ifft2(CImgProcess * pTo);									// IFFT2
	BOOL DCT(CImgProcess *pTo);										// DCT
	BOOL IDCT(CImgProcess *pTo);									// IDCT

	BOOL FreqFilt(CImgProcess * pTo, double * pdFilter,
		BYTE bFillColor = 255);										// 频域滤波
	BOOL FreqIdealLPF(double * pdFilter, int nFreq);				// 频域理想低通滤波器
	BOOL FreqIdealHPF(double * pdFilter, int nFreq);				// 频域理想高通滤波器
	BOOL FreqGaussLPF(double * pdFilter, double dSigma);			// 频域高斯低通滤波器
	BOOL FreqGaussHPF(double * pdFilter, double dSigma);			// 频域高斯高通滤波器
	BOOL FreqButterworthLPF(double * pdFilter, int nFreq, int n);	// 频域巴特沃斯低通滤波器
	BOOL FreqButterworthHPF(double * pdFilter, int nFreq, int n);	// 频域巴特沃斯高通滤波器
	BOOL FreqExpLPF(double * pdFilter, int nFreq, int n);			// 频域指数低通滤波器
	BOOL FreqExpHPF(double * pdFilter, int nFreq, int n);			// 频域指数高通滤波器
	BOOL FreqLadderLPF(double * pdFilter, int nFreq, int nF);		// 频域梯形低通滤波器
	BOOL FreqLadderHPF(double * pdFilter, int nFreq, int nF);		// 频域梯形高通滤波器
	BOOL FreqLaplace(double * pdFilter);							// 频域拉普拉斯滤波器
	BOOL FreqGaussBRF(double * pdFilter, int nFreq, int nWidth);	// 频域高斯带阻滤波器

	inline LONG GetFreqWidth(BOOL isExtending = true)
	{
		LONG w = 1;

		while (w * 2 <= GetWidthPixel())
			w *= 2;

		// 如果需要扩展图像宽度，且图像宽度不恰好是2整数幂，则：
		if ((w != GetWidthPixel()) && (isExtending))
			w *= 2;

		return w;
	}

	inline LONG GetFreqHeight(BOOL isExtending = true)
	{
		LONG h = 1;

		while (h * 2 <= GetHeight())
			h *= 2;

		// 如果需要扩展图像高度，且图像高度不恰好是2整数幂，则：
		if ((h != GetHeight()) && (isExtending))
			h *= 2;

		return h;
	}

	/*************** 颜色空间变换 *****************/
	void CMY2RGB(CImgProcess *pTo);									// CMY转RGB
	void RGB2CMY(CImgProcess *pTo);									// RGB转CMY
	void RGB2HSI(CImgProcess* pTo);									// RGB转HSI
	void HSI2RGB(CImgProcess *pTo);									// HSI转RGB
	void RGB2Gray(CImgProcess *pTo, int iType);						// RGB转灰度
	void Gray2RGB(CImgProcess *pTo, int iType);						// 灰度转RGB
	void GetRGBLevel(CImgProcess *pTo, int iType);					// 获取RGB平面，R-1 G-2 B-3
	void YIQ2RGB(CImgProcess *pTo);									// YIQ转RGB
	void RGB2YIQ(CImgProcess *pTo);									// RGB转YIQ
	void YUV2RGB(CImgProcess *pTo);									// YUV转RGB
	void RGB2YUV(CImgProcess *pTo);									// RGB转YUV
	void HSV2RGB(CImgProcess *pTo);									// HSV转RGB
	void RGB2HSV(CImgProcess *pTo);									// RGB转HSV

	/************** 形态学运算 ********************/
	void FillRgn(CImgProcess *pTo, POINT ptStart);					// 区域填充算法
	void TraceBoundary(CImgProcess *pTo);							// 边界跟踪算法
	void Thining();													// 细化算法
	void Erode(CImgProcess* pTo, int se[3][3]);						// 腐蚀算法
	void Dilate(CImgProcess* pTo, int se[3][3]);					// 膨胀算法
	void Convex(CImgProcess* pTo, BOOL bConstrain);					// 计算凸壳
	void Open(CImgProcess* pTo, int se[3][3]);						// 开运算
	void Close(CImgProcess* pTo, int se[3][3]);						// 闭运算
	void PixelImage(CImgProcess* pTo, int lowerThres, int upperThres);
	int TestConnRgn(CImgProcess* pImage, LPBYTE lpVisited, int nWidth,
		int nHeight, int x, int y, CPoint ptVisited[], int lowerThres, int upperThres, int &curLianXuShu);
	void LabelConnRgn(CImgProcess* pTo, int nConn = 8);				// 标注连通分量

	//灰度形态学
	void GrayDilate(CImgProcess* pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, int** se);						// 灰度膨胀
	void GrayErode(CImgProcess* pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, int** se);						// 灰度腐蚀
	void GrayOpen(CImgProcess* pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, int** se);						// 灰度开运算
	void GrayClose(CImgProcess* pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, int** se);						//灰度闭运算
	void Tophat(CImgProcess* pTo, int nTempH, int nTempW,
		int nTempMY, int nTempMX, int** se);						// 顶帽变换

	/********************* 图像分割 ********************/

	BOOL EdgeRoberts(CImgProcess * pTo, BYTE bThre = 0, BYTE bEdgeType = 0,
		BOOL bThinning = true, BOOL bGOnly = false);				// Roberts边缘寻找
	BOOL EdgeSobel(CImgProcess * pTo, BYTE bThre = 0, BYTE bEdgeType = 0,
		BOOL bThinning = true, BOOL bGOnly = false);				// Sobel边缘寻找
	BOOL EdgePrewitt(CImgProcess * pTo, BYTE bThre = 0, BYTE bEdgeType = 0,
		BOOL bThinning = true, BOOL bGOnly = false);				// Prewitt边缘寻找
	void EdgeLoG(CImgProcess * pTo);								// 高斯拉普拉斯边缘寻找
	BOOL EdgeCanny(CImgProcess * pTo, BYTE bThreL = 0, BYTE bThreH = 0,
		BOOL bThinning = true);										// Canny算法
	BOOL Hough(SLineInfo *pInfoRet, int nLineRet);					// Hough变换 查找直线
	void Threshold(CImgProcess *pTo, BYTE bThre);					// 阈值分割
	int DetectThreshold(int nMaxIter, int &nDiffRet);				// 迭代获取最优伐值
	void SimpThreshold(CImgProcess *pTo, int iThreshold);			// 简单阈值分割					 
	void AutoThreshold(CImgProcess *pTo);							// 自动阈值分割							 
	BOOL RegionGrow(CImgProcess * pTo, int nSeedX, int nSeedY,
		BYTE bThre);												// 区域生长算法

	/*************** 特征提取 *****************/
	vector< vector<int> > GetGrayMatrix(POINT ptD1, POINT ptD2);	// 计算灰度共现矩阵

	/*************** 特征匹配 *****************/
	void TemplateMatch(CImgProcess* pTo, CImgProcess* pTemplate);	// 模板匹配

	/*************** 图像四则运算 *****************/
	BOOL IsBiImg(CImgProcess * pTo);								// 判断当前是否为广义二值图像（位深为1或者只有两种颜色）
	void PicAdd(CImgProcess * pTo, CImgProcess* pStd);				// 图像相加
	void PicSub(CImgProcess * pTo, CImgProcess* pStd);				// 图像相减
	void PicMul(CImgProcess * pTo, CImgProcess* pStd);				// 图像相乘

};//class CImgProcess
#endif // !defined(AFX_IMAGE_H__D566CE6A_BA81_4157_8E6A_748DA096668F__INCLUDED_)