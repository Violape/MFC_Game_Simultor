#pragma once
#include <mmsystem.h>
#include "afxcmn.h"

// COption �Ի���

class COption : public CDialogEx
{
	DECLARE_DYNAMIC(COption)

public:
	COption(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COption();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	MIXERCONTROLDETAILS_SIGNED volstruct;
	MIXERCONTROLDETAILS mxcd;
	MIXERLINECONTROLS mxlc;
	MIXERLINE mxl;
	MIXERCONTROL mxc;
	HMIXER m_hmx;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_volume;
};
