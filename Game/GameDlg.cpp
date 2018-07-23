
// GameDlg.cpp : ʵ���ļ�
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


// CGameDlg �Ի���



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


// CGameDlg ��Ϣ�������

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������\
	//��ʱ�� 
	SetTimer(0, 10, 0);
	//�������1�����ý���Ч��
	CenterWindow();
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	typedef BOOL(WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC *)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 100, dwStyle);
	FreeLibrary(hInst);
	//�������2����ʾͼƬ
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//����ʱ������ťͼƬ
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
	// TODO: �ڴ����ר�ô����/����û���

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
	// TODO: �ڴ����ר�ô����/����û���
	KillTimer(0);
	CDialogEx::OnCancel();
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		TCHAR szFilter[] = _T("��Ϸ�浵(*.sav)|*.sav||");
		CFileDialog fileDlg(TRUE, _T(".cpp"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmsave/");
		fileDlg.m_ofn.lpstrTitle = _T("���ش浵");
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
