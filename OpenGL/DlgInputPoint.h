#pragma once
#include "afxdialogex.h"


// DlgInputPoint 对话框

class DlgInputPoint : public CDialogEx
{
	DECLARE_DYNAMIC(DlgInputPoint)

public:
	DlgInputPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgInputPoint();
	void GetPoints(int& x, int& y);

private:
	int m_x;
	int m_y;

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
	afx_msg void OnEnChangeEdit2();
};
