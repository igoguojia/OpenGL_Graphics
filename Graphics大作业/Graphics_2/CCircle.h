#pragma once


// CCircle 对话框

class CCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CCircle)

public:
	CCircle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCircle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	short styles;
	short Llength;
	short Slength;
	short xiankuan;
};
