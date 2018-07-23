// Option.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "Option.h"
#include "afxdialogex.h"


// COption 对话框

IMPLEMENT_DYNAMIC(COption, CDialogEx)

COption::COption(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPTION, pParent)
{

}

COption::~COption()
{
}

void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BGMVOLUME, m_volume);
}


BEGIN_MESSAGE_MAP(COption, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// COption 消息处理程序


BOOL COption::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CenterWindow();
	DWORD dwStyle = AW_BLEND;
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	typedef BOOL(WINAPI MYFUNC(HWND, DWORD, DWORD));
	MYFUNC* AnimateWindow;
	AnimateWindow = (MYFUNC *)::GetProcAddress(hInst, "AnimateWindow");
	AnimateWindow(this->m_hWnd, 100, dwStyle);
	FreeLibrary(hInst);

	unsigned long err;
	CString str;
	err = mixerOpen(&m_hmx, 0, 0, 0, 0);
	if (err)
		MessageBox(_T("ERROR: Can't open Mixer Device!"));
	ZeroMemory(&mxl, sizeof(mxl));
	mxl.cbStruct = sizeof(mxl);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	if (mixerGetLineInfo((HMIXEROBJ)m_hmx, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE))
		MessageBox(_T("Counldn't get the mixer line!"));
	ZeroMemory(&mxlc, sizeof(mxlc));
	mxlc.cbStruct = sizeof(mxlc);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(mxc);
	mxlc.pamxctrl = &mxc;
	ZeroMemory(&mxc, sizeof(mxc));
	mxc.cbStruct = sizeof(mxc);
	if (mixerGetLineControls((HMIXEROBJ)m_hmx, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE))
		MessageBox(_T("Get line controls failed!"));
	ZeroMemory(&mxcd, sizeof(mxcd));
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.cbDetails = sizeof(volstruct);
	mxcd.dwControlID = mxc.dwControlID;
	mxcd.paDetails = &volstruct;
	mxcd.cChannels = 1;
	if (mixerGetControlDetails((HMIXEROBJ)m_hmx, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE))
		MessageBox(_T("Couldn't get the volume!"));
	m_volume.SetRange(mxc.Bounds.dwMinimum, mxc.Bounds.dwMaximum);
	m_volume.SetPos(mxc.Bounds.dwMinimum + volstruct.lValue);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COption::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((CWnd*)pScrollBar == (CWnd*)&m_volume)
	{
		int pos = m_volume.GetPos();
		CString str;
		str.Format(_T("%d"),pos);
		volstruct.lValue = pos;
		mixerSetControlDetails((HMIXEROBJ)m_hmx, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
