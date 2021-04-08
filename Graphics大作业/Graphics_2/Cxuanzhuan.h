#pragma once


// Cxuanzhuan 对话框

class Cxuanzhuan : public CDialogEx
{
	DECLARE_DYNAMIC(Cxuanzhuan)

public:
	Cxuanzhuan(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cxuanzhuan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float Rangle;
	float Rx;
	float Ry;
	float Rz;
};
