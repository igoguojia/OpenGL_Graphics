// Cxiankuan.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_2.h"
#include "Cxiankuan.h"
#include "afxdialogex.h"


// Cxiankuan 对话框

IMPLEMENT_DYNAMIC(Cxiankuan, CDialogEx)

Cxiankuan::Cxiankuan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, edges(3)
	, Xk(1.0)
	, styles(0x3F07)
{

}

Cxiankuan::~Cxiankuan()
{
}

void Cxiankuan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, edges);
	DDX_Text(pDX, IDC_EDIT2, Xk);
	DDV_MinMaxFloat(pDX, Xk, 1.0, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT4, styles);
}


BEGIN_MESSAGE_MAP(Cxiankuan, CDialogEx)
END_MESSAGE_MAP()


// Cxiankuan 消息处理程序


BOOL Cxiankuan::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (op_PolyUn)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
