// DlgInputPoint.cpp: 实现文件
//

#include "pch.h"
#include "OpenGL.h"
#include "afxdialogex.h"
#include "DlgInputPoint.h"


// DlgInputPoint 对话框

IMPLEMENT_DYNAMIC(DlgInputPoint, CDialogEx)

DlgInputPoint::DlgInputPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

DlgInputPoint::~DlgInputPoint()
{
}

void DlgInputPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
}


BEGIN_MESSAGE_MAP(DlgInputPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgInputPoint::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgInputPoint::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &DlgInputPoint::OnEnChangeEdit2)
END_MESSAGE_MAP()


// DlgInputPoint 消息处理程序

void DlgInputPoint::GetPoints(int& x, int& y) {
	x = m_x;
	y = m_y;
}
void DlgInputPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void DlgInputPoint::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void DlgInputPoint::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
