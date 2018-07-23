
// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "GameDlg.h"
#include "Createnew.h"
#include "Option.h"
#include "Gamecore.h"
#include "afxdialogex.h"
#include <Digitalv.h>  
#include <mmsystem.h>  
#pragma comment(lib,"Winmm.lib")  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDlg 对话框



CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEWGAME, m_bnewgame);
	DDX_Control(pDX, IDC_LOADGAME, m_bloadgame);
	DDX_Control(pDX, IDC_OPTION, m_boptions);
	DDX_Control(pDX, IDC_QUIT, m_bquit);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码\
	//定时器 
	SetTimer(0, 10, 0);
	//额外代码1：设置渐变效果
	CenterWindow();
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	typedef BOOL(WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC *)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 100, dwStyle);
	FreeLibrary(hInst);
	//额外代码2：显示图片
	void setbutton(UINT, CStatic&);
	setbutton(IDB_NWGU, m_bnewgame);
	setbutton(IDB_LDGU, m_bloadgame);
	setbutton(IDB_OPTU, m_boptions);
	setbutton(IDB_QUTU, m_bquit);
	MCI_OPEN_PARMS open = { 0 };
	open.lpstrElementName = _T("res/bgm.mp3");
	open.lpstrDeviceType = _T("mpegvideo");
	DWORD err = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT | MCI_WAIT | MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)&open);
	if (err == 0)
	{
		MCI_PLAY_PARMS play;
		play.dwFrom = 0;
		play.dwCallback = NULL;
		mciSendCommand(open.wDeviceID, MCI_PLAY, 0, (DWORD)&play);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//按下时更换按钮图片
void setbutton(UINT ID, CStatic& target)
{
	CBitmap bitmap;
	HBITMAP hBmp;
	bitmap.LoadBitmap(ID);
	hBmp = (HBITMAP)bitmap.GetSafeHandle();
	target.SetBitmap(hBmp);
}

BOOL CGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_NEWGAME)->m_hWnd)
			setbutton(IDB_NWGD, m_bnewgame);
		if (pMsg->hwnd == GetDlgItem(IDC_LOADGAME)->m_hWnd)
			setbutton(IDB_LDGD, m_bloadgame);
		if (pMsg->hwnd == GetDlgItem(IDC_OPTION)->m_hWnd)
			setbutton(IDB_OPTD, m_boptions);
		if (pMsg->hwnd == GetDlgItem(IDC_QUIT)->m_hWnd)
			setbutton(IDB_QUTD, m_bquit);
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		setbutton(IDB_NWGU, m_bnewgame);
		setbutton(IDB_LDGU, m_bloadgame);
		setbutton(IDB_OPTU, m_boptions);
		setbutton(IDB_QUTU, m_bquit);
		if (pMsg->hwnd == GetDlgItem(IDC_NEWGAME)->m_hWnd)
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			childwindow = 1;
		}
		if (pMsg->hwnd == GetDlgItem(IDC_LOADGAME)->m_hWnd)
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			childwindow = 2;
		}
		if (pMsg->hwnd == GetDlgItem(IDC_OPTION)->m_hWnd)
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			childwindow = 3;
		}
		if (pMsg->hwnd == GetDlgItem(IDC_QUIT)->m_hWnd)
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			CGameDlg::OnCancel();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CGameDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	KillTimer(0);
	CDialogEx::OnCancel();
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (childwindow == 1)
	{
		childwindow = 0;
		CCreatenew dlgcn;
		dlgcn.DoModal();
		UpdateWindow();
	}
	if (childwindow == 2)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("游戏存档(*.sav)|*.sav||");
		CFileDialog fileDlg(TRUE, _T(".cpp"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmsave/");
		fileDlg.m_ofn.lpstrTitle = _T("加载存档");
		if (IDOK == fileDlg.DoModal())
		{
			CGamecore dlg;
			CString filepath = fileDlg.GetPathName();
			dlg.tempsave.LoadGame(filepath);
			dlg.day = dlg.tempsave.Thesave.day;
			dlg.dayofweek = dlg.tempsave.Thesave.dayofweek;
			dlg.month = dlg.tempsave.Thesave.month;
			dlg.Themap = dlg.tempsave.Thesave.Themap;
			dlg.Theplayer = dlg.tempsave.Thesave.Theplayer;
			dlg.initplace = dlg.tempsave.Thesave.mapnow;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 5; j++)
					dlg.studentlist[i][j] = dlg.tempsave.Thesave.students[i][j];
			dlg.DoModal();
		}
	}
	if (childwindow == 3)
	{
		childwindow = 0;
		COption dlg;
		dlg.DoModal();
		UpdateWindow();
	}
	CDialogEx::OnTimer(nIDEvent);
}
