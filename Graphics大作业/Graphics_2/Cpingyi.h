#pragma once


// Cpingyi 对话框

class Cpingyi : public CDialogEx
{
	DECLARE_DYNAMIC(Cpingyi)

public:
	Cpingyi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cpingyi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float Tx=0;
	float Ty=0;
	float Tz=0;
};
