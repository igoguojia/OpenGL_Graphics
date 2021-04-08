#pragma once


// Cxiankuan 对话框

class Cxiankuan : public CDialogEx
{
	DECLARE_DYNAMIC(Cxiankuan)

public:
	Cxiankuan(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cxiankuan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int edges;
	float Xk;
	short styles;
	virtual BOOL OnInitDialog();
	bool op_PolyUn = false;
};
