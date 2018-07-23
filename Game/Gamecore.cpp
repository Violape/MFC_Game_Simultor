// Gamecore.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "Gamecore.h"
#include "Option.h"
#include "afxdialogex.h"


// CGamecore 对话框

IMPLEMENT_DYNAMIC(CGamecore, CDialogEx)

CGamecore::CGamecore(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAMECORE, pParent)
{

}


CGamecore::~CGamecore()
{

}


void CGamecore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOPTEXT, m_topedit);
	DDX_Control(pDX, IDC_NAS, m_nasctrl);
	DDX_Control(pDX, IDC_TASK, m_task);
	DDX_Control(pDX, IDC_STAFF, m_staffctrl);
}


BEGIN_MESSAGE_MAP(CGamecore, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_TASKOK, &CGamecore::OnBnClickedTaskok)
	ON_BN_CLICKED(IDC_STAFFOK, &CGamecore::OnBnClickedStaffok)
END_MESSAGE_MAP()


// CGamecore 消息处理程序
CString CGamecore::refreshtext(int m, int d, int dow, int money)
{
	CString textnow;
	CString weekday;
	switch (dow)
	{
	case 1: weekday = _T('日'); break;
	case 2: weekday = _T('一'); break;
	case 3: weekday = _T('二'); break;
	case 4: weekday = _T('三'); break;
	case 5: weekday = _T('四'); break;
	case 6: weekday = _T('五'); break;
	case 7: weekday = _T('六'); break;
	}
	textnow.Format(_T(" %d 月 %d 日　周%s    精力　　　　　　　压力　　　　　　　金钱  %d"),
		m, d, weekday, money);
	return textnow;
}


BOOL CGamecore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(0, 25, NULL);
	Theplayer.loca = 52;
	texture[0].Load(_T("res/tex/nothing.jpg"));
	texture[1].Load(_T("res/tex/roadc.jpg"));
	texture[2].Load(_T("res/tex/grassl.jpg"));
	texture[3].Load(_T("res/tex/grassd.jpg"));
	texture[4].Load(_T("res/tex/earth.jpg"));
	texture[5].Load(_T("res/tex/lake.jpg"));
	texture[6].Load(_T("res/tex/sand.jpg"));
	texture[7].Load(_T("res/tex/ice.jpg"));
	texture[8].Load(_T("res/tex/snow.jpg"));
	texture[9].Load(_T("res/tex/box.jpg"));
	texture[10].Load(_T("res/tex/monster.jpg"));
	texture[11].Load(_T("res/tex/event.jpg"));
	arrow[0].Load(_T("res/core/moveupup.png"));
	arrow[1].Load(_T("res/core/movedownup.png"));
	arrow[2].Load(_T("res/core/moveleftup.png"));
	arrow[3].Load(_T("res/core/moverightup.png"));
	leftbar.Load(_T("res/core/leftbar.png"));
	topbar.Load(_T("res/core/topbar.png"));
	button[0].Load(_T("res/core/menuup.png"));
	button[1].Load(_T("res/core/saveup.png"));
	button[2].Load(_T("res/core/loadup.png"));
	button[3].Load(_T("res/core/optionup.png"));
	button[4].Load(_T("res/core/exitup.png"));
	dest[0].Load(_T("res/core/togojoup.png"));
	dest[1].Load(_T("res/core/tootoup.png"));
	dest[2].Load(_T("res/core/tosaviaup.png"));
	dest[3].Load(_T("res/core/toionup.png"));
	dest[4].Load(_T("res/core/togouup.png"));
	dest[5].Load(_T("res/core/toduluup.png"));
	taskbg.Load(_T("res/core/taskbg.png"));
	activities[0].Load(_T("res/core/acstudy.png"));
	activities[1].Load(_T("res/core/acteach.png"));
	activities[2].Load(_T("res/core/acread.png"));
	activities[3].Load(_T("res/core/accycle.png"));
	activities[4].Load(_T("res/core/accall.png"));
	activities[5].Load(_T("res/core/acstock.png"));
	activities[6].Load(_T("res/core/acmorework.png"));
	activities[7].Load(_T("res/core/aclesswork.png"));

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = RGB(1, 1, 1);
	m_topedit.SetDefaultCharFormat(cf);
	m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));

	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = RGB(1, 1, 1);
	m_nasctrl.SetDefaultCharFormat(cf);

	CString nas;
	CString city;
	CString name(Theplayer.name);
	switch (initplace)
	{
	case 1: city = _T("高州市"); break;
	case 2: city = _T("洪涛市"); break;
	case 3: city = _T("桑樊市"); break;
	case 4: city = _T("弋阳市"); break;
	case 5: city = _T("高武市"); break;
	case 6: city = _T("渡泸市"); break;
	}
	nas.Format(_T("%s，%s立中学"), name, city);
	m_nasctrl.SetWindowTextW(nas);


	m_task.ShowWindow(SW_HIDE);


	CRect tasklist;
	m_task.GetWindowRect(&tasklist);
	m_task.InsertColumn(0, _T("任务编号"), LVCFMT_CENTER, 0);
	m_task.InsertColumn(1, _T("任务名"), LVCFMT_CENTER, tasklist.Width() / 4);
	m_task.InsertColumn(2, _T("任务简介"), LVCFMT_CENTER, tasklist.Width() / 2);
	m_task.InsertColumn(3, _T("状态"), LVCFMT_CENTER, tasklist.Width() / 4);

	initstudentlist(Theplayer.pres);
	CRect stafflist;
	m_staffctrl.GetWindowRect(&stafflist);
	m_staffctrl.InsertColumn(0, _T("学生序号"), LVCFMT_CENTER, stafflist.Width() / 3);
	m_staffctrl.InsertColumn(1, _T("语文"), LVCFMT_CENTER, stafflist.Width() / 6);
	m_staffctrl.InsertColumn(2, _T("数学"), LVCFMT_CENTER, stafflist.Width() / 6);
	m_staffctrl.InsertColumn(3, _T("英语"), LVCFMT_CENTER, stafflist.Width() / 6);
	m_staffctrl.InsertColumn(4, _T("综合"), LVCFMT_CENTER, stafflist.Width() / 6);
	for (int i = 0; i < 10; i++)
	{
		CString tag, score;
		tag.Format(_T("%d"), i + 1);
		m_staffctrl.InsertItem(i, tag);
		for (int j = 1; j < 5; j++)
		{
			score.Format(_T("%.0lf"), studentlist[i][j]);
			m_staffctrl.SetItemText(i, j, score);
		}
	}

	this->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGamecore::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (childwindow == 1)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("游戏存档(*.sav)|*.sav||");
		CFileDialog fileDlg(FALSE, _T(".sav"), NULL, OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmsave/");
		fileDlg.m_ofn.lpstrTitle = _T("保存游戏");
		if (IDOK == fileDlg.DoModal())
		{
			tempsave.Thesave.day = day;
			tempsave.Thesave.dayofweek = dayofweek;
			tempsave.Thesave.month = month;
			tempsave.Thesave.Themap = Themap;
			tempsave.Thesave.Theplayer = Theplayer;
			tempsave.Thesave.mapnow = initplace;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 5; j++)
					tempsave.Thesave.students[i][j] = studentlist[i][j];
			CString filepath = fileDlg.GetPathName();
			tempsave.SaveGame(filepath);
		}
	}
	else if (childwindow == 2)
	{
		childwindow = 0;
		TCHAR szFilter[] = _T("游戏存档(*.sav)|*.sav||");
		CFileDialog fileDlg(TRUE, _T(".sav"), NULL, 0, szFilter, this);
		fileDlg.m_ofn.lpstrInitialDir = _T("gmsave/");
		fileDlg.m_ofn.lpstrTitle = _T("加载游戏");
		if (IDOK == fileDlg.DoModal())
		{
			CString filepath = fileDlg.GetPathName();
			tempsave.LoadGame(filepath);
			day = tempsave.Thesave.day;
			dayofweek = tempsave.Thesave.dayofweek;
			month = tempsave.Thesave.month;
			Themap = tempsave.Thesave.Themap;
			Theplayer = tempsave.Thesave.Theplayer;
			initplace = tempsave.Thesave.mapnow;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 5; j++)
					studentlist[i][j] = tempsave.Thesave.students[i][j];
			m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
			CString nas;
			CString city;
			CString name(Theplayer.name);
			switch (initplace)
			{
			case 1: city = _T("高州市"); break;
			case 2: city = _T("洪涛市"); break;
			case 3: city = _T("桑樊市"); break;
			case 4: city = _T("弋阳市"); break;
			case 5: city = _T("高武市"); break;
			case 6: city = _T("渡泸市"); break;
			}
			nas.Format(_T("%s，%s立中学"), name, city);
			m_nasctrl.SetWindowTextW(nas);
			//数据读入主界面
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGamecore::OnPaint()
{
	//绘图
	CPaintDC dc(this); //创建一个绘图dc
	CRect clientRect;//区域大小类
	GetClientRect(&clientRect);//获取客户区的大小

							   //双缓冲绘图
	CDC cMemDC;	// 内存DC
	CBitmap hBitMap;	//位图对象，位图就是bmp格式的图片
	hBitMap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());
	cMemDC.CreateCompatibleDC(&dc);
	CBitmap* hOldBitMap = (CBitmap*)cMemDC.SelectObject(&hBitMap);
	//现在内存DC中画

	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 36; j++)
		{
			int pixelx = Theplayer.loca % 7 * 3 + i;
			int pixely = Theplayer.loca / 7 * 3 + j;
			int tex = Themap.Getpixel(initplace - 1, pixelx, pixely);
			if (tex < 9)
				texture[tex].TransparentBlt(cMemDC, 15 * i + 90, 15 * j + 36, 15, 15, 0, 0, 64, 64, RGB(0, 0, 0));
		}

	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 36; j++)
		{
			int pixelx = Theplayer.loca % 7 * 3 + i;
			int pixely = Theplayer.loca / 7 * 3 + j;
			int tex = Themap.Getpixel(initplace - 1, pixelx, pixely);
			if (tex > 8)
				texture[tex].TransparentBlt(cMemDC, 15 * i + 90, 15 * j + 36, 45, 45, 0, 0, 64, 64, RGB(0, 0, 0));
		}

	if (Theplayer.loca > 6)
		arrow[0].TransparentBlt(cMemDC, 460, 50, arrow[0].GetWidth(), arrow[0].GetHeight(),
			0, 0, arrow[0].GetWidth(), arrow[0].GetHeight(), RGB(0, 0, 0));
	if (Theplayer.loca < 98)
		arrow[1].TransparentBlt(cMemDC, 460, 530, arrow[1].GetWidth(), arrow[1].GetHeight(),
			0, 0, arrow[1].GetWidth(), arrow[1].GetHeight(), RGB(0, 0, 0));
	if (Theplayer.loca % 7)
		arrow[2].TransparentBlt(cMemDC, 120, 240, arrow[2].GetWidth(), arrow[2].GetHeight(),
			0, 0, arrow[2].GetWidth(), arrow[2].GetHeight(), RGB(0, 0, 0));
	if (Theplayer.loca % 7 - 6)
		arrow[3].TransparentBlt(cMemDC, 910, 240, arrow[3].GetWidth(), arrow[3].GetHeight(),
			0, 0, arrow[3].GetWidth(), arrow[3].GetHeight(), RGB(0, 0, 0));

	leftbar.TransparentBlt(cMemDC, 0, 10, leftbar.GetWidth(), leftbar.GetHeight(),
		0, 0, leftbar.GetWidth(), leftbar.GetHeight(), RGB(0, 0, 0));
	if (taskon || staffon)
		taskbg.TransparentBlt(cMemDC, 210, 120, taskbg.GetWidth(), taskbg.GetHeight(),
			0, 0, taskbg.GetWidth(), taskbg.GetHeight(), RGB(0, 0, 0));

	if (baron[2])
	{
		activities[0].TransparentBlt(cMemDC, 120, 300, 64, 64,
			0, 0, activities[0].GetWidth(), activities[0].GetHeight(), RGB(255, 0, 0));
		activities[1].TransparentBlt(cMemDC, 200, 300, 64, 64,
			0, 0, activities[1].GetWidth(), activities[1].GetHeight(), RGB(255, 0, 0));
		activities[2].TransparentBlt(cMemDC, 280, 300, 64, 64,
			0, 0, activities[2].GetWidth(), activities[2].GetHeight(), RGB(255, 0, 0));
		activities[3].TransparentBlt(cMemDC, 360, 300, 64, 64,
			0, 0, activities[3].GetWidth(), activities[3].GetHeight(), RGB(255, 0, 0));
		activities[4].TransparentBlt(cMemDC, 120, 380, 64, 64,
			0, 0, activities[4].GetWidth(), activities[4].GetHeight(), RGB(255, 0, 0));
		activities[5].TransparentBlt(cMemDC, 200, 380, 64, 64,
			0, 0, activities[5].GetWidth(), activities[5].GetHeight(), RGB(255, 0, 0));
		activities[6].TransparentBlt(cMemDC, 280, 380, 64, 64,
			0, 0, activities[6].GetWidth(), activities[6].GetHeight(), RGB(255, 0, 0));
		activities[7].TransparentBlt(cMemDC, 360, 380, 64, 64,
			0, 0, activities[7].GetWidth(), activities[7].GetHeight(), RGB(255, 0, 0));
	}

	if (baron[3])
	{
		dest[0].TransparentBlt(cMemDC, 115, 400, dest[0].GetWidth(), dest[0].GetHeight(),
			0, 0, dest[0].GetWidth(), dest[0].GetHeight(), RGB(0, 0, 0));
		dest[1].TransparentBlt(cMemDC, 115, 430, dest[1].GetWidth(), dest[1].GetHeight(),
			0, 0, dest[1].GetWidth(), dest[1].GetHeight(), RGB(0, 0, 0));
		dest[2].TransparentBlt(cMemDC, 115, 460, dest[2].GetWidth(), dest[2].GetHeight(),
			0, 0, dest[2].GetWidth(), dest[2].GetHeight(), RGB(0, 0, 0));
		dest[3].TransparentBlt(cMemDC, 200, 400, dest[3].GetWidth(), dest[3].GetHeight(),
			0, 0, dest[3].GetWidth(), dest[3].GetHeight(), RGB(0, 0, 0));
		dest[4].TransparentBlt(cMemDC, 200, 430, dest[4].GetWidth(), dest[4].GetHeight(),
			0, 0, dest[4].GetWidth(), dest[4].GetHeight(), RGB(0, 0, 0));
		dest[5].TransparentBlt(cMemDC, 200, 460, dest[5].GetWidth(), dest[5].GetHeight(),
			0, 0, dest[5].GetWidth(), dest[5].GetHeight(), RGB(0, 0, 0));
	}

	topbar.TransparentBlt(cMemDC, 0, 0, topbar.GetWidth(), topbar.GetHeight(),
		0, 0, topbar.GetWidth(), topbar.GetHeight(), RGB(0, 0, 0));

	button[0].TransparentBlt(cMemDC, 870, 0, button[0].GetWidth(), button[0].GetHeight(),
		0, 0, button[0].GetWidth(), button[0].GetHeight(), RGB(0, 0, 0));
	if (buttonon[0])
	{
		button[1].TransparentBlt(cMemDC, 630, 35, button[1].GetWidth(), button[1].GetHeight(),
			0, 0, button[1].GetWidth(), button[1].GetHeight(), RGB(0, 0, 0));
		button[2].TransparentBlt(cMemDC, 710, 35, button[2].GetWidth(), button[2].GetHeight(),
			0, 0, button[2].GetWidth(), button[2].GetHeight(), RGB(0, 0, 0));
		button[3].TransparentBlt(cMemDC, 790, 35, button[3].GetWidth(), button[3].GetHeight(),
			0, 0, button[3].GetWidth(), button[3].GetHeight(), RGB(0, 0, 0));
		button[4].TransparentBlt(cMemDC, 870, 35, button[4].GetWidth(), button[4].GetHeight(),
			0, 0, button[4].GetWidth(), button[4].GetHeight(), RGB(0, 0, 0));
	}

	//画条子
	CPen NewPen(PS_SOLID, 4, RGB(0, 0, 255));
	CPen *pOldPen = cMemDC.SelectObject(&NewPen);
	cMemDC.MoveTo(231, 16);
	cMemDC.LineTo((int)(231 + 0.95*Theplayer.energy), 16);
	cMemDC.MoveTo(399, 16);
	cMemDC.LineTo((int)(399 + 0.95*Theplayer.burden), 16);
	cMemDC.SelectObject(pOldPen);


	//绘制DC
	dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(),
		&cMemDC, 0, 0, SRCCOPY);
	cMemDC.SelectObject(hOldBitMap);
	hBitMap.DeleteObject();
	cMemDC.DeleteDC();
	CDialogEx::OnPaint();
}


BOOL CGamecore::isin(int xmin, int xmax, int ymin, int ymax, CPoint cursor)
{
	if (cursor.x > xmin&&cursor.x < xmax)
		if (cursor.y > ymin&&cursor.y < ymax)
			return TRUE;
	return FALSE;
}


void CGamecore::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isin(460, 560, 50, 85, point))
	{
		arrow[0].Destroy();
		arrow[0].Load(_T("res/core/moveupmove.png"));
		arrowon[0] = TRUE;
		CRect rect(460, 50, 560, 85);
		InvalidateRect(rect, FALSE);
	}

	else if (isin(460, 560, 530, 565, point))
	{
		arrow[1].Destroy();
		arrow[1].Load(_T("res/core/movedownmove.png"));
		arrowon[1] = TRUE;
		CRect rect(460, 530, 560, 565);
		InvalidateRect(rect, FALSE);
	}

	else if (isin(110, 155, 240, 335, point))
	{
		arrow[2].Destroy();
		arrow[2].Load(_T("res/core/moveleftmove.png"));
		arrowon[2] = TRUE;
		CRect rect(110, 240, 155, 335);
		InvalidateRect(rect, FALSE);
	}

	else if (isin(910, 950, 240, 335, point))
	{
		arrow[3].Destroy();
		arrow[3].Load(_T("res/core/moverightmove.png"));
		arrowon[3] = TRUE;
		CRect rect(910, 240, 950, 335);
		InvalidateRect(rect, FALSE);
	}

	else
	{
		if (arrowon[0])
		{
			arrow[0].Destroy();
			arrow[0].Load(_T("res/core/moveupup.png"));
			arrowon[0] = FALSE;
			Invalidate(FALSE);
		}
		if (arrowon[1])
		{
			arrow[1].Destroy();
			arrow[1].Load(_T("res/core/movedownup.png"));
			arrowon[1] = FALSE;
			Invalidate(FALSE);
		}
		if (arrowon[2])
		{
			arrow[2].Destroy();
			arrow[2].Load(_T("res/core/moveleftup.png"));
			arrowon[2] = FALSE;
			Invalidate(FALSE);
		}
		if (arrowon[3])
		{
			arrow[3].Destroy();
			arrow[3].Load(_T("res/core/moverightup.png"));
			arrowon[3] = FALSE;
			Invalidate(FALSE);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CGamecore::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (isin(460, 550, 50, 85, point))
	{
		arrow[0].Destroy();
		arrow[0].Load(_T("res/core/moveupdown.png"));
		arrowon[4] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(460, 550, 530, 565, point))
	{
		arrow[1].Destroy();
		arrow[1].Load(_T("res/core/movedowndown.png"));
		arrowon[5] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(120, 155, 240, 330, point))
	{
		arrow[2].Destroy();
		arrow[2].Load(_T("res/core/moveleftdown.png"));
		arrowon[6] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(910, 935, 240, 330, point))
	{
		arrow[3].Destroy();
		arrow[3].Load(_T("res/core/moverightdown.png"));
		arrowon[7] = TRUE;
		Invalidate(FALSE);
	}


	else if (isin(39, 77, 45, 98, point))
	{
		leftbar.Destroy();
		leftbar.Load(_T("res/core/leftbartask.png"));
		baron[0] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(33, 78, 144, 206, point))
	{
		leftbar.Destroy();
		leftbar.Load(_T("res/core/leftbarstaff.png"));
		baron[1] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(28, 76, 252, 330, point))
	{
		leftbar.Destroy();
		leftbar.Load(_T("res/core/leftbarknow.png"));
		if (baron[2])
			baron[2] = FALSE;
		else
			baron[2] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(21, 82, 383, 418, point))
	{
		leftbar.Destroy();
		leftbar.Load(_T("res/core/leftbardepart.png"));
		if (baron[3])
			baron[3] = FALSE;
		else
			baron[3] = TRUE;
		Invalidate(FALSE);
	}

	else if (isin(36, 73, 460, 495, point))
	{
		leftbar.Destroy();
		leftbar.Load(_T("res/core/leftbarsleep.png"));
		baron[4] = FALSE;
		Invalidate(FALSE);
	}


	else if (isin(870, 950, 5, 35, point))
	{
		if (buttonon[0] == FALSE)
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			button[0].Destroy();
			button[0].Load(_T("res/core/menudown.png"));
			buttonon[0] = TRUE;
			Invalidate(FALSE);
		}
		else
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			button[0].Destroy();
			button[0].Load(_T("res/core/menuup.png"));
			buttonon[0] = FALSE;
			Invalidate(FALSE);
		}
	}

	if (buttonon[0])
	{
		if (isin(630, 710, 35, 65, point))
		{
			button[1].Destroy();
			button[1].Load(_T("res/core/savedown.png"));
			buttonon[1] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(710, 790, 35, 65, point))
		{
			button[2].Destroy();
			button[2].Load(_T("res/core/loaddown.png"));
			buttonon[2] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(790, 870, 35, 65, point))
		{
			button[3].Destroy();
			button[3].Load(_T("res/core/optiondown.png"));
			buttonon[3] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(870, 950, 35, 65, point))
		{
			button[4].Destroy();
			button[4].Load(_T("res/core/exitdown.png"));
			buttonon[4] = TRUE;
			Invalidate(FALSE);
		}
	}
	
	if (baron[2])
	{
		if (isin(120, 184, 300, 364, point))
		{
			activity[0] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(200, 264, 300, 364, point))
		{
			activity[1] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(280, 344, 300, 364, point))
		{
			activity[2] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(360, 424, 300, 364, point))
		{
			activity[3] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(120, 184, 380, 444, point))
		{
			activity[4] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(200, 264, 380, 444, point))
		{
			activity[5] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(280, 344, 380, 444, point))
		{
			activity[6] = TRUE;
			Invalidate(FALSE);
		}
		if (isin(360, 424, 380, 444, point))
		{
			activity[7] = TRUE;
			Invalidate(FALSE);
		}
	}

	if (baron[3])
	{
		if (isin(115, 195, 400, 430, point))
		{
			dest[0].Destroy();
			dest[0].Load(_T("res/core/togojodown.png"));
			deston[0] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(115, 195, 430, 460, point))
		{
			dest[1].Destroy();
			dest[1].Load(_T("res/core/tootodown.png"));
			deston[1] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(115, 195, 460, 490, point))
		{
			dest[2].Destroy();
			dest[2].Load(_T("res/core/tosaviadown.png"));
			deston[2] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(200, 280, 400, 430, point))
		{
			dest[3].Destroy();
			dest[3].Load(_T("res/core/toiondown.png"));
			deston[3] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(200, 280, 430, 460, point))
		{
			dest[4].Destroy();
			dest[4].Load(_T("res/core/togoudown.png"));
			deston[4] = TRUE;
			Invalidate(FALSE);
		}

		if (isin(200, 280, 460, 490, point))
		{
			dest[5].Destroy();
			dest[5].Load(_T("res/core/toduludown.png"));
			deston[5] = TRUE;
			Invalidate(FALSE);
		}
	}
	
	if (isin(90, 960, 36, 576, point))
	{
		int countx = (point.x - 90) / 15 + Theplayer.loca % 7 * 3;
		int county = (point.y - 36) / 15 + Theplayer.loca / 7 * 3;
		if (countx > 2 && county > 2)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					switch (Themap.Getpixel(initplace - 1 , countx - i, county - j))
					{
					case 9:
						PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
						doevent(initplace - 1, countx - i, county - j);
						Invalidate(FALSE);
						break;
					case 10:
						PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
						dobattle();
						Invalidate(FALSE);
						break;
					case 11:
						PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
						dotask();
						Invalidate(FALSE);
						break;
					}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGamecore::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	arrow[0].Destroy();
	arrow[0].Load(_T("res/core/moveupup.png"));
	arrow[1].Destroy();
	arrow[1].Load(_T("res/core/movedownup.png"));
	arrow[2].Destroy();
	arrow[2].Load(_T("res/core/moveleftup.png"));
	arrow[3].Destroy();
	arrow[3].Load(_T("res/core/moverightup.png"));

	if (isin(460, 550, 50, 85, point) && arrowon[4] && Theplayer.loca > 6)
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		arrow[0].Destroy();
		arrow[0].Load(_T("res/core/moveupmove.png"));
		if(Theplayer.Onchange(12))
			Theplayer.loca = Theplayer.loca - 7;
		arrowon[4] = FALSE;
	}

	else if (isin(460, 550, 530, 565, point) && arrowon[5] && Theplayer.loca < 98)
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		arrow[1].Destroy();
		arrow[1].Load(_T("res/core/movedownmove.png"));
		if (Theplayer.Onchange(12))
			Theplayer.loca = Theplayer.loca + 7;
		arrowon[5] = FALSE;
	}

	else if (isin(120, 155, 240, 330, point) && arrowon[6] && Theplayer.loca % 7)
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		arrow[2].Destroy();
		arrow[2].Load(_T("res/core/moveleftmove.png"));
		if (Theplayer.Onchange(12))
			Theplayer.loca = Theplayer.loca - 1;
		arrowon[6] = FALSE;
	}

	else if (isin(910, 935, 240, 330, point) && arrowon[7] && Theplayer.loca % 7 - 6)
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		arrow[3].Destroy();
		arrow[3].Load(_T("res/core/moverightmove.png"));
		if (Theplayer.Onchange(12))
			Theplayer.loca = Theplayer.loca + 1;
		arrowon[7] = FALSE;
	}


	leftbar.Destroy();
	leftbar.Load(_T("res/core/leftbar.png"));

	if (isin(39, 77, 45, 98, point) && baron[0])
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		baron[0] = FALSE;
		taskon = TRUE;

		LVFINDINFO *pFindInfo = new LVFINDINFO;
		pFindInfo->flags = LVFI_PARTIAL | LVFI_STRING;
		int nindex;
		CString status;


		pFindInfo->psz = (LPCTSTR)(_T("0"));
		nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			status.Format(_T("%d/5"), taskstat[0] - 1);
			m_task.SetItemText(nindex, 3, status);
		}

		pFindInfo->psz = (LPCTSTR)(_T("1"));
		nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			status.Format(_T("%d/20000"), taskstat[1]);
			m_task.SetItemText(nindex, 3, status);
		}

		pFindInfo->psz = (LPCTSTR)(_T("2"));
		nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			status.Format(_T("%.1lf/%d"), studentlist[taskstat[2]][Theplayer.subj],taskstat[3]);
			m_task.SetItemText(nindex, 3, status);
		}

		delete pFindInfo;
		m_task.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TASKOK)->ShowWindow(SW_SHOW);
	}

	else if (isin(33, 78, 144, 206, point) && baron[1])
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		baron[1] = FALSE;
		staffon = TRUE;
		m_staffctrl.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STAFFOK)->ShowWindow(SW_SHOW);
	}

	else if (isin(28, 76, 252, 330, point) && baron[2])
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	else if (isin(21, 82, 383, 418, point) && baron[3])
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	else if (isin(36, 73, 460, 495, point))
	{
		PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		baron[4] = FALSE;
		dosleep();
		if (taskstat[1])
			taskstat[1] = Theplayer.money;
		m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
	}


	if (buttonon[0])
	{
		if (isin(630, 710, 35, 65, point) && buttonon[1])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			childwindow = 1;
		}

		if (isin(710, 790, 35, 65, point) && buttonon[2])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			childwindow = 2;
		}

		if (isin(790, 870, 35, 65, point) && buttonon[3])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			COption dlg;
			dlg.DoModal();
		}

		if (isin(870, 950, 35, 65, point) && buttonon[4])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			ExitProcess(0);
		}
		button[1].Destroy();
		button[1].Load(_T("res/core/saveup.png"));
		buttonon[1] = FALSE;
		button[2].Destroy();
		button[2].Load(_T("res/core/loadup.png"));
		buttonon[2] = FALSE;
		button[3].Destroy();
		button[3].Load(_T("res/core/optionup.png"));
		buttonon[3] = FALSE;
		button[4].Destroy();
		button[4].Load(_T("res/core/exitup.png"));
		buttonon[4] = FALSE;
	}


	if (baron[2])
	{
		if (isin(120, 184, 300, 364, point) && activity[0])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[0] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你选择读书来充实自己。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 10))
			{
				CString result;
				double buff1 = Gaussrand(0.02, 0.1, 1);
				double buff2 = Gaussrand(0.04, 0.2, 1);
				double buff3 = Gaussrand(0.1, 0.25, 1);
				double buff4 = Gaussrand(0.03, 0.15, 1);
				double buff5 = Gaussrand(0.03, 0.15, 1);
				double buff6 = Gaussrand(5, 10, 1);
				int dice = (int)Gaussrand(0, 4, 1);
				switch (dice)
				{
				case 0:
					Theplayer.bskl += buff1;
					Theplayer.pfkl += buff2;
					result.Format(_T("你选择了专业书籍阅读，基础知识提升了%.2lf点，专业知识提高了%.2lf点。"),
						buff1, buff2);
					break;
				case 1:
					Theplayer.comm += buff3;
					result.Format(_T("你选择了人文书籍阅读，沟通能力提升了%.2lf点。"), buff3);
					break;
				case 2:
					Theplayer.topp += buff4;
					Theplayer.back += buff5;
					result.Format(_T("你选择了教育学书籍阅读，提优能力提升了%.2lf点，补差能力提升了%.2lf点。"),
						buff4, buff5);
					break;
				case 3:
					Theplayer.burden -= buff6;
					Theplayer.energy += 5;
					result.Format(_T("你选择了休闲书籍阅读，压力减轻了。"));
					break;
				}
				AfxMessageBox(result, MB_ICONINFORMATION);
			}
		}

		if (isin(200, 264, 300, 364, point) && activity[1])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[1] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你选择开小灶帮助同学提升成绩。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 30))
			{
				double buff[10];
				double debuff1[10], debuff2[10], debuff3[10], debuff4[10];
				for (int i = 0; i < 10; i++)
				{
					buff[i] = Gaussrand(0, 1, 1);
					debuff1[i] = Gaussrand(-0.1, 0, 1);
					debuff2[i] = Gaussrand(-0.1, 0, 1);
					debuff3[i] = Gaussrand(-0.1, 0, 1);
					debuff4[i] = Gaussrand(-0.1, 0, 1);
					studentlist[i][Theplayer.subj] += buff[i];
					studentlist[i][1] += debuff1[i];
					studentlist[i][2] += debuff2[i];
					studentlist[i][3] += debuff3[i];
					studentlist[i][4] += debuff3[i];
				}
				double prob = Gaussrand(0, 1, 2);
				if (prob < 0.1)
				{
					Theplayer.money -= 5000;
					if (taskstat[1])
						taskstat[1] = Theplayer.money;
					m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
					Theplayer.burden += 40;
					AfxMessageBox(_T("有关部门接到家长举报，对你课外开设补习班的行为进行了处理，罚款人民币5000元。你受到了学校的严厉批评，压力陡增。"), MB_ICONWARNING);
				}
				else
				{
					Theplayer.money += 500;
					if (taskstat[1])
						taskstat[1] = Theplayer.money;
					m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
					Theplayer.burden += 8;
					AfxMessageBox(_T("通过开小灶，同学们的本科成绩得到了一定提升，你获得了一些学费，但你的压力也有所增加。"), MB_ICONINFORMATION);
				}
			}
		}

		if (isin(280, 344, 300, 364, point) && activity[2])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[2] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你认真研究了近年的高考命题趋势。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 20))
			{
				double buff = Gaussrand(0.1, 0.5, 1);
				Theplayer.yati += buff;
				Theplayer.burden += 2;
				CString result;
				result.Format(_T("你的押题能力提升了%.2lf点，但压力也增加了。"), buff);
				AfxMessageBox(result, MB_ICONINFORMATION);
			}
		}
		if (isin(360, 424, 300, 364, point) && activity[3])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[3] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你选择外出锻炼。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 20))
			{
				double buff = Gaussrand(0.5, 1.5, 2);
				Theplayer.stam += buff;
				Theplayer.burden -= 20;
				AfxMessageBox(_T("经过体育锻炼，你的压力减小了，晚上也睡得更踏实了。"), MB_ICONINFORMATION);
			}

		}
		if (isin(120, 184, 380, 444, point) && activity[4])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[4] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你选择对同学进行心理辅导。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 10))
			{
				Theplayer.pres += Theplayer.comm*0.2 + Gaussrand(0, 0.1, 1);
				int studentno = (int)Gaussrand(0, 10, 1);
				studentlist[studentno][Theplayer.subj] = Gaussrand(0, 0.1, 1);
				for (int i = 1; i < 4; i++)
					studentlist[studentno][i] += Gaussrand(0, 0.1, 1);
				AfxMessageBox(_T("通过与同学的亲切交谈，你在同学们中更受欢迎了，他们的压力也得到了释放。"), MB_ICONINFORMATION);
			}
		}
		if (isin(200, 264, 380, 444, point) && activity[5])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[5] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("紧张的教学之余，你选择风险投资发家致富。"), MB_ICONINFORMATION);
			Sleep(500);
			if (Theplayer.Onchange(31, 10))
			{
				int buff = (int)Gaussrand(-25000, 2000, 1);
				Theplayer.money += buff;
				if (taskstat[1])
					taskstat[1] = Theplayer.money;
				m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
				CString result;
				if (buff > 0)
					result.Format(_T("你通过风险投资小赚一笔，收入%d元。"), buff);
				else
					result.Format(_T("奈何股市有风险，入市需谨慎，你损失了%d元。"), -buff);
				AfxMessageBox(result, MB_ICONINFORMATION);
			}
		}
		if (isin(280, 344, 380, 444, point) && activity[6])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[6] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("为了提高同学们对知识掌握的能力，你选择布置更多的作业。"), MB_ICONINFORMATION);
			Sleep(500);
			double buff[10];
			double debuff1[10], debuff2[10], debuff3[10], debuff4[10];
			for (int i = 0; i < 10; i++)
			{
				buff[i] = Gaussrand(1, 2, 1);
				debuff1[i] = Gaussrand(-0.4, -0.1, 1);
				debuff2[i] = Gaussrand(-0.4, -0.1, 1);
				debuff3[i] = Gaussrand(-0.4, -0.1, 1);
				debuff4[i] = Gaussrand(-0.4, -0.1, 1);
				studentlist[i][Theplayer.subj] += buff[i];
				studentlist[i][1] += debuff1[i];
				studentlist[i][2] += debuff2[i];
				studentlist[i][3] += debuff3[i];
				studentlist[i][4] += debuff3[i];
			}
			Theplayer.pres -= 2;
			Theplayer.burden += 10;
			AfxMessageBox(_T("同学们确实得到了锻炼，但他们对你心生不满，你也压力陡增。"), MB_ICONINFORMATION);
		}
		if (isin(360, 424, 380, 444, point) && activity[7])
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			activity[7] = FALSE;
			baron[2] = FALSE;
			AfxMessageBox(_T("为了保证同学们有充分的休息，你选择减少作业量。"), MB_ICONINFORMATION);
			Sleep(500);
			double buff[10];
			double debuff1[10], debuff2[10], debuff3[10], debuff4[10];
			for (int i = 0; i < 10; i++)
			{
				buff[i] = Gaussrand(-2, -1, 1);
				debuff1[i] = Gaussrand(0.1, 0.4, 1);
				debuff2[i] = Gaussrand(0.1, 0.4, 1);
				debuff3[i] = Gaussrand(0.1, 0.4, 1);
				debuff4[i] = Gaussrand(0.1, 0.4, 1);
				studentlist[i][Theplayer.subj] += buff[i];
				studentlist[i][1] += debuff1[i];
				studentlist[i][2] += debuff2[i];
				studentlist[i][3] += debuff3[i];
				studentlist[i][4] += debuff3[i];
			}
			Theplayer.pres += 2;
			Theplayer.burden -= 10;
			AfxMessageBox(_T("同学们成绩受到影响，但他们依然乐意写更少的作业，你的负担也小了很多。"), MB_ICONINFORMATION);
		}
	}

	dest[0].Destroy();
	dest[0].Load(_T("res/core/togojoup.png"));
	dest[1].Destroy();
	dest[1].Load(_T("res/core/tootoup.png"));
	dest[2].Destroy();
	dest[2].Load(_T("res/core/tosaviaup.png"));
	dest[3].Destroy();
	dest[3].Load(_T("res/core/toionup.png"));
	dest[4].Destroy();
	dest[4].Load(_T("res/core/togouup.png"));
	dest[5].Destroy();
	dest[5].Load(_T("res/core/toduluup.png"));


	if (baron[3])
	{
		if (isin(115, 195, 400, 430, point) && deston[0])
		{
			deston[0] = FALSE;
			if (initplace != 1)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if(Theplayer.Onchange(11))
					initplace = 1;
			}
		}

		if (isin(115, 195, 430, 460, point) && deston[1])
		{
			deston[1] = FALSE;
			if (initplace != 2)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (Theplayer.Onchange(11))
					initplace = 2;
			}
		}

		if (isin(115, 195, 460, 490, point) && deston[2])
		{
			deston[2] = FALSE;
			if (initplace != 3)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (Theplayer.Onchange(11))
				initplace = 3;
			}
		}

		if (isin(200, 280, 400, 430, point) && deston[3])
		{
			deston[3] = FALSE;
			if (initplace != 4)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (Theplayer.Onchange(11))
					initplace = 4;
			}
		}

		if (isin(200, 280, 430, 460, point) && deston[4])
		{
			deston[4] = FALSE;
			if (initplace != 5)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (Theplayer.Onchange(11))
					initplace = 5;
			}
		}

		if (isin(200, 280, 460, 490, point) && deston[5])
		{
			deston[5] = FALSE;
			if (initplace != 6)
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (Theplayer.Onchange(11))
					initplace = 6;
			}
		}
	}
	Invalidate(FALSE);
	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CGamecore::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)         //若 按键消息
	{
		CRect region(96, 30, 960, 576);
		switch (pMsg->wParam)                 //获取按键虚键值
		{
		case VK_UP:
			if (Theplayer.loca > 6)
			{
				if (Theplayer.Onchange(12))
					Theplayer.loca = Theplayer.loca - 7;
				InvalidateRect(region, FALSE);
			}
			break;

		case VK_DOWN:
			if (Theplayer.loca < 98)
			{
				if (Theplayer.Onchange(12))
					Theplayer.loca = Theplayer.loca + 7;
				InvalidateRect(region, FALSE);
			}
			break;

		case VK_LEFT:
			if (Theplayer.loca % 7)
			{
				if (Theplayer.Onchange(12))
					Theplayer.loca = Theplayer.loca - 1;
				InvalidateRect(region, FALSE);
			}
			break;

		case VK_RIGHT:
			if (Theplayer.loca % 7 - 6)
			{
				if (Theplayer.Onchange(12))
					Theplayer.loca = Theplayer.loca + 1;
				InvalidateRect(region, FALSE);
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


double CGamecore::Gaussrand(double from, double to, int att)
{
	if (att > 90)
		return 0;
	int dice[100] = { 0 }, mean = 0;
	for (int i = 0; i < att + 10; i++)
	{
		static int first = true;
		if (first)
		{
			srand(time(NULL));
			first = false;
		}
		else
		{
			dice[i] = rand();
			if (i > 9)
				mean += dice[i];
		}
	}
	return (mean / 32768.0 / att)*(to - from) + from;
}


void CGamecore::initstudentlist(double pres)
{
	if (studentlist[0][0] != 0)
		return;
	for (int i = 0; i < 10; i++)
	{
		studentlist[i][0] = i + 1;
		double level = Gaussrand(50, 100, 3);
		for (int j = 1; j < 5; j++)
		{
			double score;
			if (level > 85)
				score = Gaussrand(level - 15, 100, 1);
			else if (level < 60)
				score = Gaussrand(50, level + 15, 1);
			else
				score = Gaussrand(level - 15, level + 15, 1);
			studentlist[i][j] = score;
		}
	}
	return;
}


void CGamecore::OnBnClickedTaskok()
{
	// TODO: 在此添加控件通知处理程序代码
	PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
	GetDlgItem(IDC_TASKOK)->ShowWindow(SW_HIDE);
	m_task.ShowWindow(SW_HIDE);
	taskon = FALSE;
	Invalidate(FALSE);
	this->SetFocus();
}


void CGamecore::OnBnClickedStaffok()
{
	// TODO: 在此添加控件通知处理程序代码
	PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
	GetDlgItem(IDC_STAFFOK)->ShowWindow(SW_HIDE);
	m_staffctrl.ShowWindow(SW_HIDE);
	staffon = FALSE;
	Invalidate(FALSE);
	this->SetFocus();
}


void CGamecore::dobattle()
{
	int id = (int)Gaussrand(0, 10, 1);
	CString sub;
	if (Theplayer.subj == 1)
		sub = _T("语文");
	else if (Theplayer.subj == 2)
		sub = _T("数学");
	else if (Theplayer.subj == 3)
		sub = _T("英语");
	CString message1;
	message1.Format(_T("学生有一个%s问题向你请教！"), sub);
	AfxMessageBox(message1, MB_ICONINFORMATION);

	Sleep(1000);
	if (Theplayer.Onchange(31, 10))
	{
		double difficolta = studentlist[id][Theplayer.subj] + Gaussrand(-10, 10, 2);
		double bkr = 0, cor = 0, pkr = 0;
		bkr = (difficolta - 46) / 3.0 + Gaussrand(-2, 2, 1);
		if (difficolta > 80)
			pkr = (difficolta - 50) / 3 + Gaussrand(-2, 2, 1);
		else
			pkr = Gaussrand(0, (int)bkr + 1, 1);
		cor = (bkr + pkr) / 2;
		if (difficolta > 100)
			cor += (10 - Theplayer.topp) / 2.0;
		else if (difficolta > 90)
			cor += (10 - Theplayer.topp) / 20.0 *(difficolta - 90);
		else if (difficolta < 50)
			cor += (10 - Theplayer.back) / 2.0;
		else if (difficolta < 60)
			cor += (10 - Theplayer.back) / 20.0 * (60 - difficolta);

		CString result;
		if (bkr > Theplayer.bskl)
		{
			result = _T("基础知识不牢靠的你，并没有答出这道问题。你的学生很失望地走开了。");
			Theplayer.bskl += Gaussrand(0, 0.1, 1);
			Theplayer.pres += Gaussrand(-0.2, -0.1, 1);
		}
		else if (cor > Theplayer.comm)
		{
			result = _T("你认真的讲解给学生听，学生似懂非懂的点了点头。");
			Theplayer.comm += Gaussrand(0, 0.1, 1);
			Theplayer.pres += Gaussrand(-0.1, 0, 1);
			studentlist[id][Theplayer.subj] += 0.1;
		}
		else if (pkr > Theplayer.pfkl)
			if (Theplayer.pres > 10)
			{
				result = _T("你虽然一时无法解决，但你仔细的学习了相关知识，并最终解答了问题。");
				Theplayer.pres += Gaussrand(0, 0.1, 1);
				Theplayer.pfkl += Gaussrand(0, 0.4, 1);
				studentlist[id][Theplayer.subj] += 0.3;
			}
			else
			{
				result = _T("你一时无法解决，让你的学生自行查找相关知识。你的学生失望地走了。");
				Theplayer.pres -= Gaussrand(-0.5, -0.2, 1);
				studentlist[id][Theplayer.subj] += 0.5;
			}
		else
		{
			result = _T("你完美的解决了学生的疑问，学生高高兴兴地走出了教师办公室。");
			Theplayer.pres += Gaussrand(0.2, 0.5, 1);
			studentlist[id][Theplayer.subj] += 0.5;
			if (taskstat[0])
				taskstat[0]++;
		}
		AfxMessageBox(result, MB_ICONINFORMATION);
	}
	return;
}


void CGamecore::doevent(int m, int x, int y)
{
	AfxMessageBox(_T("恭喜你捡到宝箱，获得了一笔巨款！"), MB_ICONINFORMATION);
	Theplayer.money += (int)Gaussrand(1000, 2000, 1);
	m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
	if (x)
		Themap.Setpixel(m, x, y, Themap.Getpixel(m, x - 1, y));
	else
		Themap.Setpixel(m, x, y, Themap.Getpixel(m, x + 1, y));
	
}


void CGamecore::dotask()
{
	LVFINDINFO *pFindInfo = new LVFINDINFO;
	pFindInfo->flags = LVFI_PARTIAL | LVFI_STRING;
	if (taskstat[0] > 5)
	{
		pFindInfo->psz = (LPCTSTR)(_T("0"));
		int nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			AfxMessageBox(_T("恭喜你完成“诲人不倦”任务！\n获得奖励：全员单科成绩+1，声望+0.5"), MB_ICONINFORMATION);
			for (int i = 0; i < 10; i++)
				studentlist[i][Theplayer.subj] += 1;
			Theplayer.pres += 0.5;
			taskstat[0] = 0;
			m_task.DeleteItem(nindex);
			return;
		}
	}
	if (taskstat[1] >= 20000)
	{
		pFindInfo->psz = (LPCTSTR)(_T("1"));
		int nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			AfxMessageBox(_T("恭喜你完成“富甲天下”任务！获得奖励：压力清空，精力全满"), MB_ICONINFORMATION);
			Theplayer.energy = 100;
			Theplayer.burden = 0;
			taskstat[1] = 0;
			m_task.DeleteItem(nindex);
			return;
		}
	}
	if (studentlist[taskstat[2]][Theplayer.subj] > taskstat[3])
	{
		pFindInfo->psz = (LPCTSTR)(_T("2"));
		int nindex = m_task.FindItem(pFindInfo);
		if (nindex != -1)
		{
			AfxMessageBox(_T("恭喜你完成“重点培养”任务！获得奖励：该生各科成绩+1，全员本科成绩+0.5"), MB_ICONINFORMATION);
			for (int i = 1; i < 5; i++)
				studentlist[taskstat[2]][i] += 1;
			for (int i = 0; i < 10; i++)
				if (i != taskstat[2])
					studentlist[taskstat[2]][Theplayer.subj] += 0.5;
			taskstat[2] = 0;
			taskstat[3] = 0;
			m_task.DeleteItem(nindex);
			return;
		}
	}
	int id = (int)Gaussrand(0, 3, 1);
	switch (id)
	{
	case 0:
		pFindInfo->psz = (LPCTSTR)(_T("0"));
		if (m_task.FindItem(pFindInfo) == -1)
		{
			if (AfxMessageBox(_T("任务“诲人不倦”\n任务要求：解决五个学生的问题。\n你要接受此项任务吗？"),
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				AfxMessageBox(_T("已接受任务“诲人不倦”！"), MB_ICONINFORMATION);
				taskstat[0] = 1;
				m_task.InsertItem(0, _T("0"));
				m_task.SetItemText(0, 1, _T("诲人不倦"));
				m_task.SetItemText(0, 2, _T("解决五个学生的问题"));
				m_task.SetItemText(0, 3, _T("0/5"));
			}
		}
		break;
	case 1:
		pFindInfo->psz = (LPCTSTR)(_T("1"));
		if (m_task.FindItem(pFindInfo) == -1 && Theplayer.money < 20000)
		{
			if (AfxMessageBox(_T("任务“富甲天下”\n任务要求：金钱达到20000。\n你要接受此项任务吗？"),
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				AfxMessageBox(_T("已接受任务“富甲天下”！"), MB_ICONINFORMATION);
				taskstat[1] = Theplayer.money;
				m_task.InsertItem(0, _T("1"));
				m_task.SetItemText(0, 1, _T("富甲天下"));
				m_task.SetItemText(0, 2, _T("金钱达到20000"));
				CString moneynow;
				moneynow.Format(_T("%d/20000"), taskstat[1]);
				m_task.SetItemText(0, 3, moneynow);
			}
		}
		break;
	case 2:
		pFindInfo->psz = (LPCTSTR)(_T("2"));
		if (m_task.FindItem(pFindInfo) == -1)
		{
			taskstat[2] = (int)Gaussrand(0, 10, 1);
			CString taskinfo, taskreq;
			taskinfo.Format(_T("任务“重点培养”\n任务要求：使%d号同学的本科目成绩提升5点以上。\n你要接受此项任务吗？"), taskstat[2] + 1);
			if (AfxMessageBox(taskinfo, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				AfxMessageBox(_T("已接受任务“重点培养”！"), MB_ICONINFORMATION);
				taskreq.Format(_T("提升%d号同学的成绩"), taskstat[2]);
				taskstat[3] = (int)(studentlist[taskstat[2]][Theplayer.subj] + 5.9);
				m_task.InsertItem(0, _T("2"));
				m_task.SetItemText(0, 1, _T("重点培养"));
				m_task.SetItemText(0, 2, taskreq);
				CString scorenow;
				scorenow.Format(_T("%lf/%d"), studentlist[taskstat[2]][Theplayer.subj], taskstat[3]);
				m_task.SetItemText(0, 3, scorenow);
			}
		}
		break;
	}
	delete pFindInfo;
}


void CGamecore::dosleep()
{
	Theplayer.Onchange(13);
	if (month == 4 && day == 30)
	{
		month = 5;
		day = 1;
		Theplayer.Onchange(21);
	}
	else if (month == 5 && day == 31)
	{
		month = 6;
		day = 1;
		Theplayer.Onchange(21);
	}
	else
		day++;
	if (dayofweek == 7)
		dayofweek = 1;
	else dayofweek++;

	if (month == 6 && day == 7)
	{
		AfxMessageBox(_T("终于到了高考的日子，之前的一切努力都将在这里兑现。"), MB_ICONINFORMATION);
		int scoresheet[10][6];
		for (int i = 0; i < 10; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				scoresheet[i][j] = (int)studentlist[i][j];
			}
			if (scoresheet[i][1] < 50)
				scoresheet[i][1] = (int)Gaussrand(leveltoscore[50][0], leveltoscore[50][1], 6);
			else
				scoresheet[i][1] = (int)Gaussrand(leveltoscore[100 - scoresheet[i][1]][0], leveltoscore[100 - scoresheet[i][1]][1], 6);
			
			if (scoresheet[i][2] < 50)
				scoresheet[i][2] = (int)Gaussrand(leveltoscore[50][2], leveltoscore[50][3], 4);
			else
				scoresheet[i][2] = (int)Gaussrand(leveltoscore[100 - scoresheet[i][2]][2], leveltoscore[100 - scoresheet[i][2]][3], 4);
			
			if (scoresheet[i][3] < 50)
				scoresheet[i][3] = (int)Gaussrand(leveltoscore[50][4], leveltoscore[50][5], 8);
			else
				scoresheet[i][3] = (int)Gaussrand(leveltoscore[100 - scoresheet[i][3]][4], leveltoscore[100 - scoresheet[i][3]][5], 8);
			
			if (scoresheet[i][4] < 50)
				scoresheet[i][4] = (int)Gaussrand(leveltoscore[50][6], leveltoscore[50][7], 8);
			else
				scoresheet[i][4] = (int)Gaussrand(leveltoscore[100 - scoresheet[i][4]][6], leveltoscore[100 - scoresheet[i][4]][7], 8);
		}
		
		if (Theplayer.yati > 10)
		{
			double buffprob = (Theplayer.yati - 10) * (Theplayer.yati - 10);
			double prob = Gaussrand(0, 1, 1);
			if (buffprob > prob)
			{
				for (int i = 0; i < 10; i++)
					scoresheet[i][Theplayer.subj] += (int)Gaussrand(Theplayer.yati - 5, Theplayer.yati + 5, 3);
				AfxMessageBox(_T("你精准的押题能力触发事件“百押百中”，全员本科成绩获大幅提升！"), MB_ICONINFORMATION);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 1; j < 4; j++)
				if (scoresheet[i][j] > 150)
					scoresheet[i][j] = 150;
			if (scoresheet[i][4] > 300)
				scoresheet[i][4] = 300;
			scoresheet[i][5] = scoresheet[i][1] + scoresheet[i][2] + scoresheet[i][3] + scoresheet[i][4];
		}
		day = 28;
		m_topedit.SetWindowTextW(refreshtext(month, day, dayofweek, Theplayer.money));
		AfxMessageBox(_T("到了高考成绩公布的日子！"), MB_ICONINFORMATION);
		AfxMessageBox(_T("你的孩子们的成绩是！"), MB_ICONINFORMATION);
		PlaySound(_T("res/reveal.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(3224);
		CString finale;
		for (int i = 0; i < 10; i++)
		{
			finale.Format(_T("%d号同学：\n语文%d分；\n数学%d分；\n英语%d分；\n综合%d分；\n总分%d分！"), 
				scoresheet[i][0], scoresheet[i][1], scoresheet[i][2], scoresheet[i][3], scoresheet[i][4], scoresheet[i][5]);
			AfxMessageBox(finale, MB_ICONINFORMATION);
		}
		AfxMessageBox(_T("感谢你这段时间来的辛勤付出！感谢试玩本款游戏，再见！"), MB_ICONINFORMATION);
		ExitProcess(0);
	}
	if (Theplayer.burden > 100)
	{
		AfxMessageBox(_T("你无法承受愈加沉重的压力，患上了抑郁症，被学校解雇。"), MB_ICONSTOP);
		ExitProcess(0);
	}

	if (Theplayer.money < 0)
	{
		AfxMessageBox(_T("你无法承受愈加沉重的经济压力，最终破产。"), MB_ICONSTOP);
		ExitProcess(0);
	}

	for (int i = 0; i < 10; i++)
		for (int j = 1; j < 5; j++)
		{
			studentlist[i][j] += Gaussrand(-1, 1, 2);
			CString score;
			score.Format(_T("%.0lf"), studentlist[i][j]);
			m_staffctrl.SetItemText(i, j, score);
		}
}