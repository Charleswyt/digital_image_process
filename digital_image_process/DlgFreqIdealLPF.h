#pragma once
// CDlgFreqIdealLPF �Ի���
class CDlgFreqIdealLPF : public CDialog 
{
	DECLARE_DYNAMIC(CDlgFreqIdealLPF)
public:
	CDlgFreqIdealLPF(CWnd* pParent = NULL);				// ��׼���캯��
	virtual ~CDlgFreqIdealLPF();
	enum { IDD = IDD_DLG_FREQ_IDEALLPF };				// �Ի�������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	int m_nFreq;		// ��ֹƵ��
};