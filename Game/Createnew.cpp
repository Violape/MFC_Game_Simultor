// Createnew.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "Createnew.h"
#include "afxdialogex.h"
#include "mmsystem.h"  
#pragma comment(lib,"Winmm.lib")  


// CCreatenew 对话框

IMPLEMENT_DYNAMIC(CCreatenew, CDialogEx)

CCreatenew::CCreatenew(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATENEW, pParent)
	, m_introduction(_T(""))
	, m_newplayername(_T(""))
{

}

CCreatenew::~CCreatenew()
{
}

void CCreatenew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFOMATION, m_introduction);
	DDX_Control(pDX, IDC_INFOMATION, m_introctrl);
	DDX_Text(pDX, IDC_NEWNAME, m_newplayername);
	DDX_Control(pDX, IDC_NEWNAME, m_newplayernamectrl);
}


BEGIN_MESSAGE_MAP(CCreatenew, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCreatenew 消息处理程序


BOOL CCreatenew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//额外代码1：设置渐变效果
	SetTimer(1, 25, 0);
	//加载图片
	imageconfirm.Load(_T("res/reg/confirmup.png"));
	imagecancel.Load(_T("res/reg/cancelup.png"));
	imagebg.Load(_T("res/intro2.bmp"));
	imageregister.Load(_T("res/reg/reg.png"));
	imagemale.Load(_T("res/reg/male.png"));
	imagefemale.Load(_T("res/reg/female.png"));
	imagechn.Load(_T("res/reg/chn.png"));
	imagemath.Load(_T("res/reg/mat.png"));
	imageeng.Load(_T("res/reg/eng.png"));
	imagezuipao.Load(_T("res/reg/zp.png"));
	imageyundong.Load(_T("res/reg/yd.png"));
	imagelingxiu.Load(_T("res/reg/lx.png"));
	//设置文本
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.crTextColor = RGB(0, 0, 0);
	cf.yHeight = 15 * 18;
	m_introctrl.SetDefaultCharFormat(cf);
	cf.yHeight = 15 * 18;
	m_newplayernamectrl.SetDefaultCharFormat(cf);
	//限制富文本
	m_newplayernamectrl.LimitText(16);
	this->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCreatenew::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}


void CCreatenew::OnPaint()
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
	//划线
	//现在内存DC中画
	imagebg.BitBlt(cMemDC, 0, 0, imagebg.GetWidth(), imagebg.GetHeight(), 0, 0, SRCCOPY);
	imageregister.TransparentBlt(cMemDC, 50, 20, imageregister.GetWidth(), imageregister.GetHeight(),
		0, 0, imageregister.GetWidth(), imageregister.GetHeight(), RGB(0, 0, 0));
	imageconfirm.TransparentBlt(cMemDC, 330, 500, imageconfirm.GetWidth(), imageconfirm.GetHeight(),
		0, 0, imageconfirm.GetWidth(), imageconfirm.GetHeight(), RGB(0, 0, 0));
	imagecancel.TransparentBlt(cMemDC, 494, 500, imagecancel.GetWidth(), imagecancel.GetHeight(),
		0, 0, imagecancel.GetWidth(), imagecancel.GetHeight(), RGB(0, 0, 0));
	if (sswitch[0])
		imagemale.TransparentBlt(cMemDC,
			246, 152, imagemale.GetWidth(), imagemale.GetHeight(),
			0, 0, imagemale.GetWidth(), imagemale.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[1])
		imagefemale.TransparentBlt(cMemDC,
			341, 154, imagefemale.GetWidth(), imagefemale.GetHeight(),
			0, 0, imagefemale.GetWidth(), imagefemale.GetHeight(), 
			RGB(0, 0, 0));
	if (sswitch[2])
		imagechn.TransparentBlt(cMemDC,
			236, 235, imagechn.GetWidth(), imagechn.GetHeight(),
			0, 0, imagechn.GetWidth(), imagechn.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[3])
		imagemath.TransparentBlt(cMemDC,
			316, 235, imagemath.GetWidth(), imagemath.GetHeight(),
			0, 0, imagemath.GetWidth(), imagemath.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[4])
		imageeng.TransparentBlt(cMemDC,
			393, 235, imageeng.GetWidth(), imageeng.GetHeight(),
			0, 0, imageeng.GetWidth(), imageeng.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[5])
		imagezuipao.TransparentBlt(cMemDC,
			237, 291, imagezuipao.GetWidth(), imagezuipao.GetHeight(),
			0, 0, imagezuipao.GetWidth(), imagezuipao.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[6])
		imageyundong.TransparentBlt(cMemDC,
			317, 291, imageyundong.GetWidth(), imageyundong.GetHeight(),
			0, 0, imageyundong.GetWidth(), imageyundong.GetHeight(),
			RGB(0, 0, 0));
	if (sswitch[7])
		imagelingxiu.TransparentBlt(cMemDC,
			397, 290, imagelingxiu.GetWidth(), imagelingxiu.GetHeight(),
			0, 0, imagelingxiu.GetWidth(), imagelingxiu.GetHeight(),
			RGB(0, 0, 0));
	//画血条
	CPen NewPen(PS_SOLID, 8, RGB(0, 112, 192));
	CPen *pOldPen = cMemDC.SelectObject(&NewPen);
	if (sswitch[2] || sswitch[3] || sswitch[4])
	{
		cMemDC.MoveTo(623, 114);
		cMemDC.LineTo(623 + 10 * newplayer.bskl, 114);
		cMemDC.MoveTo(623, 144);
		cMemDC.LineTo(623 + 10 * newplayer.pfkl, 144);
		cMemDC.MoveTo(623, 174);
		cMemDC.LineTo(623 + 10 * newplayer.yati, 174);
		cMemDC.MoveTo(623, 204);
		cMemDC.LineTo(623 + 10 * newplayer.topp, 204);
		cMemDC.MoveTo(623, 234);
		cMemDC.LineTo(623 + 10 * newplayer.back, 234);
		cMemDC.MoveTo(623, 264);
		cMemDC.LineTo(623 + 10 * newplayer.comm, 264);
		cMemDC.MoveTo(623, 294);
		cMemDC.LineTo(623 + 10 * newplayer.pres, 294);
		cMemDC.MoveTo(623, 324);
		cMemDC.LineTo(623 + 10 * newplayer.stam, 324);
	}
	cMemDC.SelectObject(pOldPen);
	dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(), 
		&cMemDC, 0, 0, SRCCOPY);

	//还原对象，释放不用了的位图对象和内存dc
	cMemDC.SelectObject(hOldBitMap);
	hBitMap.DeleteObject();
	cMemDC.DeleteDC();
	CDialogEx::OnPaint();
}

void CCreatenew::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nextstep)
	{
		nextstep = FALSE;
		CMapedit dlg;
		dlg.newplayer = newplayer;
		dlg.DoModal();
		SendMessage(WM_CLOSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL cnisin(int xmin, int xmax, int ymin, int ymax, CPoint cursor)
{
	if (cursor.x > xmin && cursor.x < xmax)
		if (cursor.y > ymin && cursor.y < ymax)
			return TRUE;
	return FALSE;
}

BOOL CCreatenew::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CPoint cursor;
		GetCursorPos(&cursor);
		ScreenToClient(&cursor);
		if (cnisin(278, 278 + 35, 176, 176 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[0])
			{
				sswitch[0] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-8);
			}
			else
			{
				sswitch[0] = TRUE;
				m_introctrl.SetWindowTextW(_T("男生：你充满阳刚之气，体能充沛，阳光开朗。\n体能+2，声望+1"));
				newplayer.Onchange(0);
			}
			if (sswitch[1])
			{
				sswitch[1] = FALSE;
				newplayer.Onchange(-1);
			}
		}
		if (cnisin(373, 373 + 35, 176, 176 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[0])
			{
				sswitch[0] = FALSE;
				newplayer.Onchange(-8);
			}
			
			if (sswitch[1])
			{
				sswitch[1] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-1);
			}
			else
			{
				sswitch[1] = TRUE;
				m_introctrl.SetWindowTextW(_T("女生：你细腻而温柔，善于观察他人，循循善诱。\n交际能力+3"));
				newplayer.Onchange(1);
			}
		}
		if (cnisin(248, 248 + 35, 243, 243 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[2])
			{
				sswitch[2] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-2);
			}
			else
			{
				sswitch[2] = TRUE;
				m_introctrl.SetWindowTextW(_T("仙族：\n你是国文的使者，如仙人自在逍遥，给人们带来的是阅读和作文作业。\n"));
				newplayer.Onchange(2);
			}
			if (sswitch[3])
			{
				sswitch[3] = FALSE;
				newplayer.Onchange(-3);
			}
			if (sswitch[4])
			{
				sswitch[4] = FALSE;
				newplayer.Onchange(-4);
			}
		}
		if (cnisin(328, 328 + 35, 243, 243 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[2])
			{
				sswitch[2] = FALSE;
				newplayer.Onchange(-2);
			}
			
			if (sswitch[3])
			{
				sswitch[3] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-3);
			}
			else
			{
				sswitch[3] = TRUE;
				m_introctrl.SetWindowTextW(_T("巫族：\n从前有一棵大树叫做高树，很多人挂在上面。你是邪恶的化身，让人们学会活着。【手动微笑】\n"));
				newplayer.Onchange(3);
			}
			if (sswitch[4])
			{
				sswitch[4] = FALSE;
				newplayer.Onchange(-4);
			}
		}
		if (cnisin(408, 408 + 35, 243, 243 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[2])
			{
				sswitch[2] = FALSE;
				newplayer.Onchange(-2);
			}
			if (sswitch[3])
			{
				sswitch[3] = FALSE;
				newplayer.Onchange(-3);
			}
			if (sswitch[4])
			{
				sswitch[4] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-4);
			}
			else
			{
				sswitch[4] = TRUE;
				m_introctrl.SetWindowTextW(_T("蛮夷：\n你自英伦三岛而来，带来鸟语，没有花香。他们视你为蛮夷，你却将另一个世界带给他们。\n"));
				newplayer.Onchange(4);
			}
		}
		if (cnisin(248, 248 + 35, 300, 300 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[5])
			{
				sswitch[5] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-5);
			}
			else
			{
				sswitch[5] = TRUE;
				m_introctrl.SetWindowTextW(_T("最强嘴炮：\n你是传说中永远驳不倒的大神，伶牙俐齿能说得学生哑口无言。\n交流能力+4，威望-2，补差能力-1，提优能力-1"));
				newplayer.Onchange(5);
			}
				
		}
		if (cnisin(328, 328 + 35, 300, 300 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[6])
			{
				sswitch[6] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-6);
			}
			else
			{
				sswitch[6] = TRUE;
				m_introctrl.SetWindowTextW(_T("运动健将：\n健壮的体魄，让你从不疲倦，足以应付更多的学生。\n体能+4，基础知识-1，专业知识-1，押题能力-2"));
				newplayer.Onchange(6);
			}
		}
		if (cnisin(408, 408 + 35, 300, 300 + 35, cursor))
		{
			PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (sswitch[7])
			{
				sswitch[7] = FALSE;
				m_introctrl.SetWindowTextW(_T(""));
				newplayer.Onchange(-7);
			}
				
			else
			{
				sswitch[7] = TRUE;
				m_introctrl.SetWindowTextW(_T("学者：\n你热爱学习，知识渊博，是广大学生的偶像。\n威望+1，专业知识+3，提优能力+2，补差能力-2，交流能力-2，体能-2"));
				newplayer.Onchange(7);
			}
		}
		if (cnisin(330, 330 + imageconfirm.GetWidth(), 500, 500 + imageconfirm.GetHeight(), cursor))
		{
			imageconfirm.Destroy();
			imageconfirm.Load(_T("res/reg/confirmdown.png"));
			confirm = TRUE;
		}
		if (cnisin(494, 494 + imagecancel.GetWidth(), 500, 500 + imagecancel.GetHeight(), cursor))
		{
			imagecancel.Destroy();
			imagecancel.Load(_T("res/reg/canceldown.png"));
			cancel = TRUE;
		}
		Invalidate(FALSE);
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		CPoint cursor;
		GetCursorPos(&cursor);
		ScreenToClient(&cursor);
		imageconfirm.Destroy();
		imageconfirm.Load(_T("res/reg/confirmup.png"));
		imagecancel.Destroy();
		imagecancel.Load(_T("res/reg/cancelup.png"));
		if (confirm)
			if (cnisin(330, 330 + imageconfirm.GetWidth(), 500, 500 + imageconfirm.GetHeight(), cursor)) 
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				CString name;
				m_newplayernamectrl.GetWindowTextW(name);
				if (name == "")
					MessageBox(_T("请输入玩家姓名！"));
				else if (!sswitch[0] && !sswitch[1])
					MessageBox(_T("请选择性别！"));
				else if (!sswitch[2] && !sswitch[3] && !sswitch[4])
					MessageBox(_T("请选择派系！"));
				else
				{
					newplayer.Initenergy();
					int len = WideCharToMultiByte(CP_ACP, 0, name, name.GetLength(), NULL, 0, NULL, NULL);
					char* cname = new char[len + 1];
					len = WideCharToMultiByte(CP_ACP, 0, name, name.GetLength(), cname, len + 1, NULL, NULL);
					cname[len] = 0;
					strcpy(newplayer.name, cname);
					nextstep = TRUE;
					delete cname;
				}
			}
		if (cancel)
			if (cnisin(494, 494 + imagecancel.GetWidth(), 500, 500 + imagecancel.GetHeight(), cursor))
			{
				PlaySound(_T("res/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				SendMessage(WM_CLOSE);
			}
		Invalidate(FALSE);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
