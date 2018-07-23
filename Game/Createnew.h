#pragma once
#include "afxcmn.h"
#include "Player.h"
#include "Mapedit.h"

// CCreatenew �Ի���

class CCreatenew : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatenew)

public:
	CCreatenew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreatenew();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATENEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CImage imageconfirm;
	CImage imagecancel;
	CImage imagebg;
	CImage imageregister;
	CImage imagemale;
	CImage imagefemale;
	CImage imagechn;
	CImage imagemath;
	CImage imageeng;
	CImage imagezuipao;
	CImage imageyundong;
	CImage imagelingxiu;

	BOOL sswitch[8] = { FALSE };
	BOOL confirm = FALSE;
	BOOL cancel = FALSE;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_introduction;
	CRichEditCtrl m_introctrl;
	CPlayer newplayer;
	CString m_newplayername;
	BOOL nextstep = FALSE;
	CRichEditCtrl m_newplayernamectrl;
};
