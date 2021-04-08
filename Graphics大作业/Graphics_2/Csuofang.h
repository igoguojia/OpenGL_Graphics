#pragma once


// Csuofang 对话框

class Csuofang : public CDialogEx
{
	DECLARE_DYNAMIC(Csuofang)

public:
	Csuofang(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Csuofang();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float Sx;
	float Sy;
	float Sz;
	/*CWnd *pWnd1 = GetDlgItem(IDC_EDIT1);
	CWnd *pWnd2 = GetDlgItem(IDC_EDIT2);
	CWnd *pWnd3 = GetDlgItem(IDC_EDIT3);*/
	int Soption = 0;//传递是否开启改变纵横比
	afx_msg void OnBnClickedCheck1();//
	float Sxyz;

	//控件变量，控制使用函数
	CEdit m_Sx;
	CEdit m_Sy;
	CEdit m_Sz;
	CEdit m_Sxyz;
	CButton CheckCBox;
};
