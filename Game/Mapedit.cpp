// Mapedit.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "Mapedit.h"
#include "afxdialogex.h"
#include "Chooseload.h"
#include "Gamecore.h"
#include "mmsystem.h"  
#pragma comment(lib,"Winmm.lib")  


// CMapedit 对话框

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


// CMapedit 消息处理程序


BOOL CMapedit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
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
				  // 异常: OCX 属性页应返回 FALSE
}


void CMapedit::OnPaint()
{
	//绘图
	CPaintDC dc(this);	//创建一个绘图dc
	CRect clientRect;	//区域大小类
	GetClientRect(&clientRect);//获取客户区的大小
							   //双缓冲绘图
	CDC cMemDC;			// 内存DC
	CBitmap hBitMap;	//位图对象，位图就是bmp格式的图片
	hBitMap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());
	cMemDC.CreateCompatibleDC(&dc);
	CBitmap* hOldBitMap = (CBitmap*)cMemDC.SelectObject(&hBitMap);
	//现在在内存DC内画
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
	//还原对象，释放不用了的位图对象和内存dc
	cMemDC.SelectObject(hOldBitMap);
	hBitMap.DeleteObject();
	cMemDC.DeleteDC();
	CDialogEx::OnPaint();

}


void CMapedit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		TCHAR szFilter[] = _T("地图存档(*.map)|*.map||");
		CFileDialog fileDlg(TRUE, _T(".map"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("加载地图");
		if (IDOK == fileDlg.DoModal())
		{
			CString filepath = fileDlg.GetPathName();
			map.Loadgamemap(filepath);
		}
	}
	else if (childwindow == 2)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("位图文件(*.bmp)|*.bmp|所有文件(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T(".bmp"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("导入位图");
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
		TCHAR szFilter[] = _T("地图存档(*.map)|*.map||");
		CFileDialog fileDlg(FALSE, _T(".map"), NULL, OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmmap/");
		fileDlg.m_ofn.lpstrTitle = _T("地图另存为");
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
