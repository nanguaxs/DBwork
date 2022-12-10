// paperDlg.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "paperDlg.h"


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
END_MESSAGE_MAP()


// paperDlg 消息处理程序
