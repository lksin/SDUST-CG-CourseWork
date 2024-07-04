// test.cpp: 实现文件
//

#include "pch.h"
#include "OpenGL.h"
#include "afxdialogex.h"
#include "test.h"


// test 对话框

IMPLEMENT_DYNAMIC(test, CDialogEx)

test::test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent),a(0)
{

}

test::~test()
{
}

void test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, a);
}


BEGIN_MESSAGE_MAP(test, CDialogEx)
	ON_BN_CLICKED(IDOK, &test::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &test::OnBnClickedCancel)
END_MESSAGE_MAP()


// test 消息处理程序


void test::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void test::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
