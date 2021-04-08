
// Graphics_2View.h: CGraphics2View 类的接口
//

#pragma once
#include<GL/gl.h>
#include<GL/glu.h>

class CGraphics2View : public CView
{
protected: // 仅从序列化创建
	CGraphics2View() noexcept;
	DECLARE_DYNCREATE(CGraphics2View)

// 特性
public:
	CGraphics2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphics2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//必须加
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// 用于onCREATE，onDESTORY，onSIZE
	HGLRC hRC;
	CClientDC* pDC;
	bool bSetDCPixelFormat();//选择像素格式，放在onCREATE中

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnColorDialog();
	COLORREF color = RGB(255, 0, 0);//调色板
	int ColorR=255, ColorG=0, ColorB=0;

	afx_msg void OnColorClear();//清屏
	int Start = 0;
	CPoint pointxy[10];
	
public:
	//多边形
	afx_msg void OnPoly_un();//折线
	void DrawPoly_un();
	afx_msg void OnCircle();
	void DrawCircle();
	short circle_xk;
	short circle_sty, circle_slength, circle_llength;
	CPoint circle;

	float Xiank = 1.0;
	short styles;	
	afx_msg void OnDrawPolygon();
	void DrawPolygon();
	int m_PtNum=0; //边的个数
	int num = 0;//计数器
	int num_P=0;//多边形计数器
	
	CPoint m_Pts[100];
	struct Edge
	{
		double Ymax;
		double X;
		double Dx;
	};
	struct EDGE
	{//边结构(有效边结构）
		CPoint Up;
		CPoint Down;
		Edge EG;
	};
	void BuildEDGEs();//存储多边形
	void CreateET();//初始化全局边表
	void InitAET();//初始化活跃边表
	void FillPolygon(CDC *pDC);
	void GetMinMaxY(int &MinY, int &MaxY);//多边形统计，获得最大最小扫描线Y标号
	void GetMinMaxX(int &MinY, int &MaxY);//多边形统计，获得最大最小扫描线X标号

	void MoveNewEdgeFromET();// 加入新边

	void RemoveEdges();// 删除旧边

	void SortAET();// 排序

	void FillScanLine(CDC *pDC, int ColorR, int ColorG,int ColorB);// 配对填充当前行

	void UpdateDelteX();// 更新交点横坐标。
	EDGE *m_pEDGEs;
	CArray <Edge, Edge> *m_pET;//边表
	CArray <Edge, Edge> *m_pAET;//有效边表
	int MinY = 1,
		MaxY = 20,
		MinX = 1,
		MaxX = 20,
		m_CurrentScanLine;

public://平移
	float Trax, Tray, Traz;
	afx_msg void OnTranslate();
	void Translate();
	afx_msg void OnUpdateTranslate(CCmdUI *pCmdUI);//设置该菜单可用不可用函数
	bool TraEnable = false;

public://缩放
	afx_msg void OnScale();
	float Scax, Scay, Scaz, Scaxyz;//传递缩放因子
	int Scaoption;//传递是否开启改变纵横比
	void Scale();
	afx_msg void OnUpdateScale(CCmdUI *pCmdUI);
	bool ScaEnable = false;

public://旋转
	afx_msg void OnRotate();
	float Rotx, Roty, Rotz, Rotangle;
	void Rotate();
	afx_msg void OnUpdateRotate(CCmdUI *pCmdUI);
	bool RotEnable = false;
	void find_center_point();//找距离原点最近点函数
	CPoint c_point;

public://印章
	float PI = 3.1415926535;
	double POld[1][3];
	double TR[3][3];
	double SecondE[60][2];
	void nameShow();
	afx_msg void OnnameShow();
	afx_msg void OnnameShowRotate();

public://裁剪
	//初始化矩形大小
	afx_msg void OnCohen_Sutherland();
	void On_Draw();
	CPoint m_Draw[2];
	int draw_num = 0;//计数器
	double xl=100, xr=600, yt=600, yb=100;
	unsigned int RC, RC0, RC1;//变量
	void   encode(double x, double y, int &code);//函数
	void cohen(double x1, double y1, double x2, double y2);//裁剪函数
	afx_msg void OnCS_draw();

public://3D
	// 将立方体的八个顶点保存到一个数组里面	
	afx_msg void On3DCurve();
	void Draw3DCurve();
	afx_msg void On3DV();
	afx_msg void On3DW();
	afx_msg void On3DH();

	afx_msg void OnGlobe();
	void DrawGlobe();

	afx_msg void OnCuboid();
	afx_msg void OnCuboidV();
	afx_msg void OnCuboidW();
	afx_msg void OnCuboidH();
	void DrawCuboid();

	afx_msg void OnPixel();
	void onDrawPixel();//画三维图像
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int ccx, ccy;//获得窗口大小
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CPoint rpoint;//右键按下时的坐标
	float RpointX_zoom, RpointY_zoom;//右键平移距离，转为旋转角度用
	CPoint lpoint;
	float LpointX_zoom, LpointY_zoom;//左键平移距离
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	float m_fMultiple = 0.1;//放大缩小倍数

public://LOGO
	afx_msg void OnLogoRedandWhite();
	void Draw_One_Logo();
	afx_msg void OnLogoColorful();
	void Draw_One_Colorful_Logo(int R,int G,int B);

public:

public:
	int m_Bezier_num = 3, m_Bezier_xiankuan = 1,m_Bezier_styles;
	void Bezier();	
	afx_msg void OnBezier();
	GLfloat ctrlpoints[10][3] = { 0 };
	int order = 0;

	//B样条
public:
	void Bspline();
	void DrawBspline();
	GLfloat x_coord[10] = { 0 }, y_coord[10] = { 0 };
	int nest = -1;
	float x, y, length = 9999.0, L;
	afx_msg void OnBspline();
	//动态B样条
public:
	afx_msg void OnBsplineMOVE();
	afx_msg void OnBezierMOVE();

	afx_msg void OnFillColor();






	afx_msg void OnCut();
	void OnDrawCut();
	int cutx, cuty;
	afx_msg void OnSave();
	afx_msg void OnSaveJpg();

};

#ifndef _DEBUG  // Graphics_2View.cpp 中的调试版本
inline CGraphics2Doc* CGraphics2View::GetDocument() const
   { return reinterpret_cast<CGraphics2Doc*>(m_pDocument); }
#endif

