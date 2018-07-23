
// GameDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Gamecore.h"

// CGameDlg 对话框
class CGameDlg : public CDialogEx
{
// 构造
public:
	CGameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_bnewgame;
	CStatic m_bloadgame;
	CStatic m_boptions;
	CStatic m_bquit;
	CImage top;
	CImage bg;

	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int childwindow = 0;
};
