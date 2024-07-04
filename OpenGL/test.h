#pragma once
#include "afxdialogex.h"


// test 对话框

class test : public CDialogEx
{
	DECLARE_DYNAMIC(test)

public:
	test(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~test();
	int a;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
