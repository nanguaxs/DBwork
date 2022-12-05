// paperDlg.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "paperDlg.h"
#include"sql.h"

// paperDlg 对话框

IMPLEMENT_DYNAMIC(paperDlg, CDialogEx)

paperDlg::paperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

paperDlg::~paperDlg()
{
}

void paperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(paperDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &paperDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// paperDlg 消息处理程序


void paperDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

}
