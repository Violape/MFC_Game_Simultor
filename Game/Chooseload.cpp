// Chooseload.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Game.h"
#include "Chooseload.h"
#include "afxdialogex.h"


// CChooseload �Ի���

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


// CChooseload ��Ϣ�������


void CChooseload::OnBnClickedRadio1()
{
	m_return = 1;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChooseload::OnBnClickedRadio2()
{
	m_return = 2;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChooseload::OnBnClickedRadio3()
{
	m_return = 3;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChooseload::OnBnClickedRadio4()
{
	m_return = 4;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChooseload::OnBnClickedRadio5()
{
	m_return = 5;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChooseload::OnBnClickedRadio6()
{
	m_return = 6;// TODO: �ڴ���ӿؼ�֪ͨ����������
}

BOOL CChooseload::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
