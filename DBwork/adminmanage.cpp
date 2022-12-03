// adminmanage.cpp: 实现文件
//

#include "pch.h"
#include "DBwork.h"
#include "afxdialogex.h"
#include "adminmanage.h"


// adminmanage 对话框

IMPLEMENT_DYNAMIC(adminmanage, CDialogEx)

adminmanage::adminmanage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

adminmanage::~adminmanage()
{
}

void adminmanage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(adminmanage, CDialogEx)
END_MESSAGE_MAP()


// adminmanage 消息处理程序
