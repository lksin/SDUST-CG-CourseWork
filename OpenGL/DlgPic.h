#pragma once
#include "afxdialogex.h"
#include <vector>

// DlgPic 对话框

class DlgPic : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPic)

public:
	DlgPic(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgPic();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedJ1();
	afx_msg void OnBnClickedCanteena();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	std::vector<int> selectedCheckboxes;
	void AddOrRemoveCheckbox(int id, int value);
public:
	int m_x = 5, m_y = 10;
	void GetNum(int& x, int& y);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedYanlake();
	afx_msg void OnBnClickedSchoolsouthgate();
	afx_msg void OnBnClickedPlaygroud();
	afx_msg void OnBnClickedTaishanpark();
	afx_msg void OnBnClickedOldlibrary();
	afx_msg void OnBnClickedJ14();
	afx_msg void OnBnClickedCanteenb();
	afx_msg void OnBnClickedS1();
	afx_msg void OnBnClickedJ13();
};
