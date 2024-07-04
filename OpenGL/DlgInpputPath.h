#pragma once
#include "afxdialogex.h"


// DlgInpputPath 对话框

class DlgInpputPath : public CDialogEx
{
	DECLARE_DYNAMIC(DlgInpputPath)

public:
	DlgInpputPath(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgInpputPath();

	/*void SetStartEnd(int& start, int& end);*/

public:
	int m_start;
	int m_end;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

};
