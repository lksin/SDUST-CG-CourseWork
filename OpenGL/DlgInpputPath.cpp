// DlgInpputPath.cpp: 实现文件
//

#include "pch.h"
#include "OpenGL.h"
#include "afxdialogex.h"
#include "DlgInpputPath.h"


// DlgInpputPath 对话框

IMPLEMENT_DYNAMIC(DlgInpputPath, CDialogEx)

DlgInpputPath::DlgInpputPath(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent),
	m_start(1), m_end(1){}

DlgInpputPath::~DlgInpputPath()
{
}

void DlgInpputPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_start);
	DDX_Text(pDX, IDC_EDIT4, m_end);

}


BEGIN_MESSAGE_MAP(DlgInpputPath, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgInpputPath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgInpputPath::OnBnClickedCancel)

END_MESSAGE_MAP()



// DlgInpputPath 消息处理程序


void DlgInpputPath::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void DlgInpputPath::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

