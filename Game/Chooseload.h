#pragma once


// CChooseload �Ի���

class CChooseload : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseload)

public:
	CChooseload(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChooseload();
	int m_return = 0;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSELOAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
//	virtual BOOL OnInitDialog();
//	virtual BOOL OnInitDialog();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
