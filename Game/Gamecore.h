#pragma once
#include "Player.h"
#include "gamemap.h"
#include "afxcmn.h"
#include "Savegame.h"
#include "Chooseload.h"

// CGamecore 对话框

class CGamecore : public CDialogEx
{
	DECLARE_DYNAMIC(CGamecore)

public:
	CGamecore(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGamecore();
	BOOL isin(int xmin, int xmax, int ymin, int ymax, CPoint cursor);
	int month = 4;
	int day = 21;
	int dayofweek = 6;
	CPlayer Theplayer;
	CGamemap Themap;
	CImage texture[12];
	CImage arrow[4];
	CImage leftbar;
	CImage topbar;
	CImage button[5];
	CImage dest[6];
	CImage taskbg;
	CImage activities[8];
	CImage gettask;
	int taskstat[4];
	BOOL arrowon[8] = { FALSE };
	BOOL baron[5] = { FALSE };
	BOOL buttonon[5] = { FALSE };
	BOOL deston[6] = { FALSE };
	BOOL activity[8] = { FALSE };
	BOOL taskon = FALSE;
	BOOL staffon = FALSE;
	double studentlist[10][5] = { 0 };
	int initplace;
	int childwindow = 0;
	CSavegame tempsave;
	CRichEditCtrl m_topedit;
	CRichEditCtrl m_nasctrl;
	CListCtrl m_task;
	CListCtrl m_staffctrl;
	CString refreshtext(int m, int d, int dow, int money);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMECORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedTaskok();
	afx_msg void OnBnClickedStaffok();
	void dobattle();
	void doevent(int m, int x, int y);
	void dotask();
	void dosleep();
	void initstudentlist(double pres);
	double CGamecore::Gaussrand(double from, double to, int att);
	double leveltoscore[51][8]= {
		{ 130,155,135,160,140,150,260,300 },
		{ 125,155,132,160,138,150,250,300 },
		{ 123,155,130,160,137,150,240,300 },
		{ 121,155,128,160,136,150,236,296 },
		{ 119,155,126,160,135,150,232,292 },
		{ 117,155,124,160,134,150,228,288 },
		{ 115,155,122,160,133,150,224,284 },
		{ 113,153,120,160,132,150,220,280 },
		{ 111,151,119,159,131,150,217,277 },
		{ 110,150,118,158,130,150,214,274 },
		{ 108,148,117,157,129,149,211,271 },
		{ 106,146,116,156,128,148,208,268 },
		{ 104,144,115,155,126,147,205,265 },
		{ 102,142,114,154,124,146,202,262 },
		{ 100,140,113,153,122,145,199,259 },
		{ 98,138,112,152,120,144,196,256 },
		{ 96,137,111,151,117,142,192,252 },
		{ 95,135,110,150,114,140,188,248 },
		{ 93,134,109,149,111,138,184,244 },
		{ 92,132,106,146,108,136,180,240 },
		{ 91,131,104,144,105,135,176,236 },
		{ 90,130,102,142,102,134,172,232 },
		{ 89,128,100,140,99,133,168,228 },
		{ 88,127,98,138,96,132,164,224 },
		{ 87,126,96,136,93,131,160,220 },
		{ 86,124,94,134,90,130,156,216 },
		{ 85,122,92,132,87,127,152,212 },
		{ 83,121,89,129,84,124,148,208 },
		{ 82,120,86,126,81,121,144,204 },
		{ 80,119,84,124,78,118,140,200 },
		{ 78,118,82,122,75,115,135,195 },
		{ 77,117,80,120,72,112,130,190 },
		{ 76,116,78,118,70,110,125,185 },
		{ 75,115,76,116,67,107,120,180 },
		{ 73,113,74,114,64,104,115,175 },
		{ 72,112,73,113,62,102,110,170 },
		{ 70,110,72,112,60,100,105,165 },
		{ 68,108,71,110,58,98,100,160 },
		{ 66,106,70,108,56,96,95,155 },
		{ 64,104,69,106,54,94,90,150 },
		{ 62,102,68,104,52,92,85,140 },
		{ 61,100,67,102,50,90,80,130 },
		{ 60,98,65,100,40,85,75,120 },
		{ 60,96,60,98,30,80,70,110 },
		{ 60,94,50,96,20,70,60,100 },
		{ 60,92,40,93,10,60,50,90 },
		{ 60,90,30,90,0,55,40,80 },
		{ 58,88,24,90,0,50,30,70 },
		{ 56,86,16,80,0,40,20,60 },
		{ 50,84,10,70,0,30,10,60 },
		{ 40,80,0,60,0,20,0,60 } };
};
