#pragma once
#include "Player.h"
#include "Gamemap.h"

// CMapedit 对话框

class CMapedit : public CDialogEx
{
	DECLARE_DYNAMIC(CMapedit)

public:
	CMapedit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMapedit();
	CPlayer player;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPEDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CImage loadmap;
	CImage savemap;
	CImage loadbitmap;
	CImage startgame;
	CImage city[6];
	CImage bg;
	BOOL load = FALSE;
	BOOL save = FALSE;
	BOOL loadb = FALSE;
	BOOL start = FALSE;
	BOOL citta[6];
	CPoint citycoor[6];
	int childwindow = 0;
	DECLARE_MESSAGE_MAP()
public:
	CPlayer newplayer;
	CGamemap map;
	int initplace;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
