// Mapedit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Game.h"
#include "Mapedit.h"
#include "afxdialogex.h"
#include "Chooseload.h"
#include "Gamecore.h"
#include "mmsystem.h"  
#pragma comment(lib,"Winmm.lib")  


// CMapedit �Ի���

IMPLEMENT_DYNAMIC(CMapedit, CDialogEx)

CMapedit::CMapedit(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAPEDIT, pParent)
{

}

CMapedit::~CMapedit()
{
}

void CMapedit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapedit, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMapedit ��Ϣ�������


BOOL CMapedit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	loadmap.Load(_T("res/map/loadmapsup.png"));
	savemap.Load(_T("res/map/savemapsup.png"));
	loadbitmap.Load(_T("res/map/loadbitmapup.png"));
	startgame.Load(_T("res/map/startgameup.png"));
	bg.Load(_T("res/map/terrain.png"));
	for (int i = 0; i < 6; i++)
		city[i].Load(_T("res/map/citybuttonup.png"));
	citycoor[0].x = 803;
	citycoor[1].x = 548;
	citycoor[2].x = 447;
	citycoor[3].x = 230;
	citycoor[4].x = 48;
	citycoor[5].x = 175;
	citycoor[0].y = 126;
	citycoor[1].y = 103;
	citycoor[2].y = 458;
	citycoor[3].y = 132;
	citycoor[4].y = 160;
	citycoor[5].y = 398;

	SetTimer(0, 10, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMapedit::OnPaint()
{
	//��ͼ
	CPaintDC dc(this);	//����һ����ͼdc
	CRect clientRect;	//�����С��
	GetClientRect(&clientRect);//��ȡ�ͻ����Ĵ�С
							   //˫�����ͼ
	CDC cMemDC;			// �ڴ�DC
	CBitmap hBitMap;	//λͼ����λͼ����bmp��ʽ��ͼƬ
	hBitMap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());
	cMemDC.CreateCompatibleDC(&dc);
	CBitmap* hOldBitMap = (CBitmap*)cMemDC.SelectObject(&hBitMap);
	//�������ڴ�DC�ڻ�
	bg.TransparentBlt(cMemDC, 0, 0, 960, 576,
		0, 0, 960, 576, RGB(0, 0, 0));
	loadmap.TransparentBlt(cMemDC, 750, 350,
		loadmap.GetWidth(), loadmap.GetHeight(),
		0, 0, loadmap.GetWidth(), loadmap.GetHeight(), RGB(0, 0, 0));
	savemap.TransparentBlt(cMemDC, 750, 400,
		savemap.GetWidth(), savemap.GetHeight(),
		0, 0, savemap.GetWidth(), savemap.GetHeight(), RGB(0, 0, 0));
	loadbitmap.TransparentBlt(cMemDC, 750, 450,
		loadbitmap.GetWidth(), loadbitmap.GetHeight(),
		0, 0, loadbitmap.GetWidth(), loadbitmap.GetHeight(), RGB(0, 0, 0));
	startgame.TransparentBlt(cMemDC, 750, 500,
		startgame.GetWidth(), startgame.GetHeight(),
		0, 0, startgame.GetWidth(), startgame.GetHeight(), RGB(0, 0, 0));
	for (int i = 0; i < 6; i++)
	{
		city[i].TransparentBlt(cMemDC, citycoor[i].x, citycoor[i].y,
			city[i].GetWidth(), city[i].GetHeight(),
			0, 0, city[i].GetWidth(), city[i].GetHeight(), RGB(0, 0, 0));
	}
	dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(),
		&cMemDC, 0, 0, SRCCOPY);
	//��ԭ�����ͷŲ����˵�λͼ������ڴ�dc
	cMemDC.SelectObject(hOldBitMap);
	hBitMap.DeleteObject();
	cMemDC.DeleteDC();
	CDialogEx::OnPaint();

}


void CMapedit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x > 750 && point.x < 750 + loadmap.GetWidth())
	{
		if (point.y > 350 && point.y < 350 + loadmap.GetHeight())
		{
			loadmap.Destroy();
			loadmap.Load(_T("res/map/loadmapsdown.png"));
			load = TRUE;
		}
		else if (point.y > 400 && point.y < 400 + savemap.GetHeight())
		{
			savemap.Destroy();
			savemap.Load(_T("res/map/savemapsdown.png"));
			save = TRUE;
		}
		else if (point.y > 450 && point.y < 450 + loadbitmap.GetHeight())
		{
			loadbitmap.Destroy();
			loadbitmap.Load(_T("res/map/loadbitmapdown.png"));
			loadb = TRUE;
		}
		else if (point.y > 500 && point.y < 500 + startgame.GetHeight())
		{
			startgame.Destroy();
			startgame.Load(_T("res/map/startgamedown.png"));
			start = TRUE;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMapedit::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	loadmap.Destroy();
	loadmap.Load(_T("res/map/loadmapsup.png"));
	loadbitmap.Destroy();
	loadbitmap.Load(_T("res/map/loadbitmapup.png"));
	savemap.Destroy();
	savemap.Load(_T("res/map/savemapsup.png"));
	startgame.Destroy();
	startgame.Load(_T("res/map/startgameup.png"));
	if (point.x > 750 && point.x < 750 + loadmap.GetWidth())
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (load)
			if (point.y > 350 && point.y < 350 + loadbitmap.GetHeight())
			{
				childwindow = 1;
			}
		if (save)
			if (point.y > 400 && point.y < 400 + loadbitmap.GetHeight())
			{
				childwindow = 3;
			}
		if (loadb)
			if (point.y > 450 && point.y < 450 + loadbitmap.GetHeight())
			{
				childwindow = 2;
			}
		if (start)
			if (point.y > 500 && point.y < 500 + loadbitmap.GetHeight())
			{
				childwindow = 4;
			}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMapedit::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect inv1(750, 300, 950, 550);
	CRect inv2(0, 0, 740, 576);
	CRgn rgn1, rgn2;
	rgn1.CreateRectRgnIndirect(inv1);
	rgn2.CreateRectRgnIndirect(inv2);
	rgn1.CombineRgn(&rgn1, &rgn2, RGN_OR);
	InvalidateRgn(&rgn1, FALSE);
	if (childwindow == 1)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("��ͼ�浵(*.map)|*.map||");
		CFileDialog fileDlg(TRUE, _T(".map"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("���ص�ͼ");
		if (IDOK == fileDlg.DoModal())
		{
			CString filepath = fileDlg.GetPathName();
			map.Loadgamemap(filepath);
		}
	}
	else if (childwindow == 2)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T(".bmp"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("����λͼ");
		if (IDOK == fileDlg.DoModal())
		{
			CString filepath = fileDlg.GetPathName();
			CChooseload dlg;
			dlg.DoModal();
			if (dlg.m_return)
				map.Loadfrombitmap(dlg.m_return - 1, filepath);
		}
	}
	else if (childwindow == 3)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("��ͼ�浵(*.map)|*.map||");
		CFileDialog fileDlg(FALSE, _T(".map"), NULL, OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("��ͼ���Ϊ");
		if (IDOK == fileDlg.DoModal())
		{
			CString filepath = fileDlg.GetPathName();
			map.Savegamemap(filepath);
		}
	}
	else if (childwindow == 4)
	{
		childwindow = 0;
		CChooseload dlg1;
		if (dlg1.DoModal() == IDOK)
		{
			initplace = dlg1.m_return;
			CGamecore dlg;
			dlg.Theplayer = newplayer;
			dlg.Themap = map;
			dlg.initplace = initplace;
			dlg.DoModal();
		}
		SendMessage(WM_CLOSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}
