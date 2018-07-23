// Chooseload.cpp : 实现文件
//

#include "stdafx.h"
#include "Game.h"
#include "Chooseload.h"
#include "afxdialogex.h"


// CChooseload 对话框

IMPLEMENT_DYNAMIC(CChooseload, CDialogEx)

CChooseload::CChooseload(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHOOSELOAD, pParent)
{

}

CChooseload::~CChooseload()
{
}

void CChooseload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChooseload, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CChooseload::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CChooseload::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CChooseload::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CChooseload::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CChooseload::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CChooseload::OnBnClickedRadio6)
//	ON_WM_TIMER()
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CChooseload 消息处理程序


void CChooseload::OnBnClickedRadio1()
{
	m_return = 1;// TODO: 在此添加控件通知处理程序代码
}


void CChooseload::OnBnClickedRadio2()
{
	m_return = 2;// TODO: 在此添加控件通知处理程序代码
}


void CChooseload::OnBnClickedRadio3()
{
	m_return = 3;// TODO: 在此添加控件通知处理程序代码
}


void CChooseload::OnBnClickedRadio4()
{
	m_return = 4;// TODO: 在此添加控件通知处理程序代码
}


void CChooseload::OnBnClickedRadio5()
{
	m_return = 5;// TODO: 在此添加控件通知处理程序代码
}


void CChooseload::OnBnClickedRadio6()
{
	m_return = 6;// TODO: 在此添加控件通知处理程序代码
}

BOOL CChooseload::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
