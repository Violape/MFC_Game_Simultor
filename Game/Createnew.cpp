// Createnew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Game.h"
#include "Createnew.h"
#include "afxdialogex.h"
#include "mmsystem.h"  
#pragma comment(lib,"Winmm.lib")  


// CCreatenew �Ի���

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


// CCreatenew ��Ϣ�������


BOOL CCreatenew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//�������1�����ý���Ч��
	SetTimer(1, 25, 0);
	//����ͼƬ
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
	//�����ı�
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_SIZE;
	cf.crTextColor = RGB(0, 0, 0);
	cf.yHeight = 15 * 18;
	m_introctrl.SetDefaultCharFormat(cf);
	cf.yHeight = 15 * 18;
	m_newplayernamectrl.SetDefaultCharFormat(cf);
	//���Ƹ��ı�
	m_newplayernamectrl.LimitText(16);
	this->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CCreatenew::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnClose();
}


void CCreatenew::OnPaint()
{
	//��ͼ
	CPaintDC dc(this); //����һ����ͼdc
	CRect clientRect;//�����С��
	GetClientRect(&clientRect);//��ȡ�ͻ����Ĵ�С

	//˫�����ͼ
	CDC cMemDC;	// �ڴ�DC
	CBitmap hBitMap;	//λͼ����λͼ����bmp��ʽ��ͼƬ
	hBitMap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());
	cMemDC.CreateCompatibleDC(&dc);
	CBitmap* hOldBitMap = (CBitmap*)cMemDC.SelectObject(&hBitMap);
	//����
	//�����ڴ�DC�л�
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
	//��Ѫ��
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

	//��ԭ�����ͷŲ����˵�λͼ������ڴ�dc
	cMemDC.SelectObject(hOldBitMap);
	hBitMap.DeleteObject();
	cMemDC.DeleteDC();
	CDialogEx::OnPaint();
}

void CCreatenew::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ����ר�ô����/����û���
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
				m_introctrl.SetWindowTextW(_T("���������������֮�������ܳ��棬���⿪�ʡ�\n����+2������+1"));
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
				m_introctrl.SetWindowTextW(_T("Ů������ϸ������ᣬ���ڹ۲����ˣ�ѭѭ���ա�\n��������+3"));
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
				m_introctrl.SetWindowTextW(_T("���壺\n���ǹ��ĵ�ʹ�ߣ�������������ң�������Ǵ��������Ķ���������ҵ��\n"));
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
				m_introctrl.SetWindowTextW(_T("���壺\n��ǰ��һ�ô��������������ܶ��˹������档����а��Ļ���������ѧ����š����ֶ�΢Ц��\n"));
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
				m_introctrl.SetWindowTextW(_T("���ģ�\n����Ӣ�������������������û�л��㡣��������Ϊ���ģ���ȴ����һ������������ǡ�\n"));
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
				m_introctrl.SetWindowTextW(_T("��ǿ���ڣ�\n���Ǵ�˵����Զ�������Ĵ�������������˵��ѧ���ƿ����ԡ�\n��������+4������-2����������-1����������-1"));
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
				m_introctrl.SetWindowTextW(_T("�˶�������\n��׳�����ǣ�����Ӳ�ƣ�룬����Ӧ�������ѧ����\n����+4������֪ʶ-1��רҵ֪ʶ-1��Ѻ������-2"));
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
				m_introctrl.SetWindowTextW(_T("ѧ�ߣ�\n���Ȱ�ѧϰ��֪ʶԨ�����ǹ��ѧ����ż��\n����+1��רҵ֪ʶ+3����������+2����������-2����������-2������-2"));
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
					MessageBox(_T("���������������"));
				else if (!sswitch[0] && !sswitch[1])
					MessageBox(_T("��ѡ���Ա�"));
				else if (!sswitch[2] && !sswitch[3] && !sswitch[4])
					MessageBox(_T("��ѡ����ϵ��"));
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
