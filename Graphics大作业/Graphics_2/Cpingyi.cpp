// Cpingyi.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_2.h"
#include "Cpingyi.h"
#include "afxdialogex.h"


// Cpingyi 对话框

IMPLEMENT_DYNAMIC(Cpingyi, CDialogEx)

Cpingyi::Cpingyi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, Tx(0)
	, Ty(0)
	, Tz(0)
{

}

Cpingyi::~Cpingyi()
{
}

void Cpingyi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Tx);
	DDX_Text(pDX, IDC_EDIT3, Ty);
	DDX_Text(pDX, IDC_EDIT2, Tz);
}


BEGIN_MESSAGE_MAP(Cpingyi, CDialogEx)
END_MESSAGE_MAP()


// Cpingyi 消息处理程序
