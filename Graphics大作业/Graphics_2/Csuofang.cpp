// Csuofang.cpp: 实现文件
//

#include "pch.h"
#include "Graphics_2.h"
#include "Csuofang.h"
#include "afxdialogex.h"


// Csuofang 对话框

IMPLEMENT_DYNAMIC(Csuofang, CDialogEx)

Csuofang::Csuofang(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, Sx(2.0)
	, Sy(2.0)
	, Sz(1.0)
	, Sxyz(2.0)
{
	//pWnd1->EnableWindow(FALSE);
	//pWnd2->EnableWindow(FALSE);
	//pWnd3->EnableWindow(FALSE);
	//m_Sx.EnableWindow(FALSE);
}

Csuofang::~Csuofang()
{
}

void Csuofang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Sx);
	DDX_Text(pDX, IDC_EDIT3, Sy);
	DDX_Text(pDX, IDC_EDIT2, Sz);
	DDX_Text(pDX, IDC_EDIT4, Sxyz);
	DDX_Control(pDX, IDC_EDIT1, m_Sx);
	DDX_Control(pDX, IDC_EDIT3, m_Sy);
	DDX_Control(pDX, IDC_EDIT2, m_Sz);
	DDX_Control(pDX, IDC_EDIT4, m_Sxyz);
	DDX_Control(pDX, IDC_CHECK1, CheckCBox);
}


BEGIN_MESSAGE_MAP(Csuofang, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &Csuofang::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Csuofang 消息处理程序


//改变纵横比
void Csuofang::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (CheckCBox.GetCheck())//检查checkbox是否选中
	{
		Soption = 1;
		m_Sx.EnableWindow(true);
		m_Sy.EnableWindow(true);
		m_Sz.EnableWindow(true);
		m_Sxyz.EnableWindow(false);
	}
	else
	{
		Soption = 0;
		m_Sx.EnableWindow(false);
		m_Sy.EnableWindow(false);
		m_Sz.EnableWindow(false);
		m_Sxyz.EnableWindow(true);
	}
}
