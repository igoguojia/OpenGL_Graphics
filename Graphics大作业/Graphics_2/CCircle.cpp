// CCircle.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_2.h"
#include "CCircle.h"
#include "afxdialogex.h"


// CCircle 对话框

IMPLEMENT_DYNAMIC(CCircle, CDialogEx)

CCircle::CCircle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIRCLE, pParent)
	, styles(0x3F07)
	, Llength(10)
	, Slength(10)
	, xiankuan(1)
{

}

CCircle::~CCircle()
{
}

void CCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, styles);
	DDX_Text(pDX, IDC_EDIT1, Llength);
	DDX_Text(pDX, IDC_EDIT3, Slength);
	DDX_Text(pDX, IDC_EDIT2, xiankuan);
}


BEGIN_MESSAGE_MAP(CCircle, CDialogEx)
END_MESSAGE_MAP()


// CCircle 消息处理程序
