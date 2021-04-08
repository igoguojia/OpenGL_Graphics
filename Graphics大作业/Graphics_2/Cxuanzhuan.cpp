// Cxuanzhuan.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_2.h"
#include "Cxuanzhuan.h"
#include "afxdialogex.h"


// Cxuanzhuan 对话框

IMPLEMENT_DYNAMIC(Cxuanzhuan, CDialogEx)

Cxuanzhuan::Cxuanzhuan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, Rangle(0)
	, Rx(0)
	, Ry(0)
	, Rz(1)
{

}

Cxuanzhuan::~Cxuanzhuan()
{
}

void Cxuanzhuan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Rangle);
	DDX_Text(pDX, IDC_EDIT1, Rx);
	DDX_Text(pDX, IDC_EDIT4, Ry);
	DDX_Text(pDX, IDC_EDIT3, Rz);
}


BEGIN_MESSAGE_MAP(Cxuanzhuan, CDialogEx)
END_MESSAGE_MAP()


// Cxuanzhuan 消息处理程序
