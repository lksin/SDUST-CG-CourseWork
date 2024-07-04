// DlgPic.cpp: 实现文件
//

#include "pch.h"
#include "OpenGL.h"
#include "afxdialogex.h"
#include "DlgPic.h"



// DlgPic 对话框

IMPLEMENT_DYNAMIC(DlgPic, CDialogEx)

DlgPic::DlgPic(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

DlgPic::~DlgPic()
{
}

void DlgPic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgPic, CDialogEx)
	ON_BN_CLICKED(IDC_J1, &DlgPic::OnBnClickedJ1)
	ON_BN_CLICKED(IDC_CanteenA, &DlgPic::OnBnClickedCanteena)
	ON_BN_CLICKED(IDOK, &DlgPic::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgPic::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_gaodi, &DlgPic::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_hos, &DlgPic::OnBnClickedCheck2)
END_MESSAGE_MAP()


// DlgPic 消息处理程序
void DlgPic::AddOrRemoveCheckbox(int id, int value)
{
	auto it = std::find(selectedCheckboxes.begin(), selectedCheckboxes.end(), value);
	if (it != selectedCheckboxes.end())
	{
		selectedCheckboxes.erase(it);
	}
	else
	{
		if (selectedCheckboxes.size() < 2)
		{
			selectedCheckboxes.push_back(value);
		}
		else
		{
			// 你可以在这里添加错误处理逻辑，比如提示用户只能选择两个复选框
			AfxMessageBox(_T("You can only select two checkboxes."));
		}
	}
}

void DlgPic::OnBnClickedJ1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOrRemoveCheckbox(IDC_J1, 21);
}


void DlgPic::OnBnClickedCanteena()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOrRemoveCheckbox(IDC_CanteenA, 30);
}

void DlgPic::GetNum(int& x, int& y) {
	m_x = x;
	m_y = y;
}

void DlgPic::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (selectedCheckboxes.size() == 2)
	{
		GetNum(selectedCheckboxes[0], selectedCheckboxes[1]);
	}
	else
	{
		// 提示用户需要选择两个复选框
		AfxMessageBox(_T("Please select exactly two checkboxes."));
	}
	CDialogEx::OnOK();
}


void DlgPic::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void DlgPic::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOrRemoveCheckbox(IDC_gaodi, 27);
}


void DlgPic::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOrRemoveCheckbox(IDC_hos, 28);
}
