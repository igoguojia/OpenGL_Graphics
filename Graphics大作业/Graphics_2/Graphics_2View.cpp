
// Graphics_2View.cpp: CGraphics2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphics_2.h"
#endif
#include<gl/glew.h>
#include<GL/glut.h>
#include<GLTools.h>
//#include <GLFW/glfw3.h>
//#include<GL/glu.h>
//#include<gl/gl.h>
//#include<gl/>
#include "Graphics_2Doc.h"
#include "Graphics_2View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include"Cxiankuan.h"
#include"Cpingyi.h"
#include"Csuofang.h"
#include"Cxuanzhuan.h"
#include<graphics.h>
#include"CCircle.h"
#include"BaseClass.h"
#pragma warning(disable:4996)
// CGraphics2View

IMPLEMENT_DYNCREATE(CGraphics2View, CView)

BEGIN_MESSAGE_MAP(CGraphics2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphics2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_32771, &CGraphics2View::OnDrawPolygon)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32772, &CGraphics2View::OnTranslate)
	ON_COMMAND(ID_32773, &CGraphics2View::OnColorDialog)
	ON_COMMAND(ID_32774, &CGraphics2View::OnColorClear)
	ON_UPDATE_COMMAND_UI(ID_32772, &CGraphics2View::OnUpdateTranslate)
	ON_COMMAND(ID_32776, &CGraphics2View::OnScale)
	ON_UPDATE_COMMAND_UI(ID_32776, &CGraphics2View::OnUpdateScale)
	ON_COMMAND(ID_32777, &CGraphics2View::OnRotate)
	ON_UPDATE_COMMAND_UI(ID_32777, &CGraphics2View::OnUpdateRotate)
	ON_COMMAND(ID_32778, &CGraphics2View::OnnameShow)
	ON_COMMAND(ID_32779, &CGraphics2View::OnnameShowRotate)
	ON_COMMAND(ID_32780, &CGraphics2View::OnCohen_Sutherland)
	ON_COMMAND(ID_32781, &CGraphics2View::OnCS_draw)
	ON_COMMAND(ID_32784, &CGraphics2View::OnPixel)
	ON_COMMAND(ID_LOGO_32785, &CGraphics2View::OnLogoRedandWhite)
	ON_COMMAND(ID_LOGO_32786, &CGraphics2View::OnLogoColorful)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()

	ON_COMMAND(ID_32795, &CGraphics2View::OnPoly_un)
	ON_COMMAND(ID_32796, &CGraphics2View::OnCircle)
	ON_COMMAND(ID_32797, &CGraphics2View::OnBezier)
	ON_COMMAND(ID_32798, &CGraphics2View::OnBspline)
	ON_COMMAND(ID_32799, &CGraphics2View::OnBsplineMOVE)
	ON_COMMAND(ID_32800, &CGraphics2View::OnBezierMOVE)
	ON_COMMAND(ID_32801, &CGraphics2View::OnFillColor)
	ON_COMMAND(ID_32802, &CGraphics2View::OnCuboid)
	ON_COMMAND(ID_32803, &CGraphics2View::OnGlobe)
	ON_COMMAND(ID_32804, &CGraphics2View::On3DCurve)
	ON_COMMAND(ID_32805, &CGraphics2View::On3DV)
	ON_COMMAND(ID_32806, &CGraphics2View::On3DW)
	ON_COMMAND(ID_32807, &CGraphics2View::On3DH)
	ON_COMMAND(ID_32808, &CGraphics2View::OnCut)
	ON_COMMAND(ID_32809, &CGraphics2View::OnSave)
	ON_COMMAND(ID_32811, &CGraphics2View::OnSaveJpg)
	ON_COMMAND(ID_32814, &CGraphics2View::OnCuboidV)
	ON_COMMAND(ID_32815, &CGraphics2View::OnCuboidW)
	ON_COMMAND(ID_32816, &CGraphics2View::OnCuboidH)
END_MESSAGE_MAP()

// CGraphics2View 构造/析构

CGraphics2View::CGraphics2View() noexcept
{
	// TODO: 在此处添加构造代码
	m_pEDGEs = NULL;
	m_pET = NULL;
	m_pAET = NULL;

}

CGraphics2View::~CGraphics2View()
{
	if (m_pEDGEs)  delete[] m_pEDGEs;
	if (m_pET)     delete[] m_pET;
	if (m_pAET)    delete[] m_pAET;
}

BOOL CGraphics2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphics2View 绘图

void CGraphics2View::OnDraw(CDC* /*pDC*/)
{
	CGraphics2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	//设置当前绘图设备为OPENGL的设备情景对象
	if (hRC) wglMakeCurrent(pDC->GetSafeHdc(), hRC);
	else return;
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(0.7, 0.7, 0.7, 0.7);
	//将颜色缓存设为glclearcolor命令所设置的颜色，即背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glLineWidth(50.0);

	glBegin(GL_LINES);
	// glLineWidth(50.0);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(2.50, 2.5);
	glVertex2f(17.5, 12.5);
	glEnd();*/
	SwapBuffers(wglGetCurrentDC());//交换前后缓存

	/*glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	glVertex2i(200, 100);
	glVertex2i(200, 200);
	glVertex2i(100, 200);
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存*/

}


// CGraphics2View 打印


void CGraphics2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphics2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphics2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphics2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGraphics2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (Start != 3 && Start != 4 && Start != 8 && Start != 9 && Start != 10 && Start != 11 && Start != 12)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
	if (Start == 8)
	{
		nest = -1;
		length = 9999;
	}
	if (Start == 9)
	{
		nest = -1;
		length = 9999;
	}
	if (Start == 4)
	{
		nest = -1;
		length = 9999;
	}

}

void CGraphics2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphics2View 诊断

#ifdef _DEBUG
void CGraphics2View::AssertValid() const
{
	CView::AssertValid();
}

void CGraphics2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphics2Doc* CGraphics2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphics2Doc)));
	return (CGraphics2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGraphics2View 消息处理程序


int CGraphics2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	pDC = new CClientDC(this);
	ASSERT(pDC != NULL);//断言，相当于if，如果pdc不空，则执行；
	// 设置像素格式
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  //结构大小
		1,
		PFD_DRAW_TO_WINDOW |             //窗口中绘图
		PFD_SUPPORT_OPENGL |             //支持OPENGL
		PFD_DOUBLEBUFFER,               //双缓冲模式
		PFD_TYPE_RGBA,                 //RGBA颜色模式
		24,                           // 24位色彩深度
		0, 0, 0, 0, 0, 0,                   //无颜色位
		0,                           // 无alpha 缓存
		0,                           //无移位
		0,                           //无加速缓存
		0, 0, 0, 0,                     //无累积位
		32,                          //32位深度缓存
		0,                           //无模板缓存
		0,                           //无辅助缓存
		PFD_MAIN_PLANE,              //PFD主平面
		0,                           //保留
		0, 0, 0                        //忽略主层掩模
	};
	//选择像素格式
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox(L"选择像素格式失败！"); return -1;
	}
	//设置像素格式
	if (SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox(L"(设置像素格式失败！)"); return -1;
	}
	int n;
	n = ::GetPixelFormat(pDC->GetSafeHdc());
	::DescribePixelFormat(pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	hRC = wglCreateContext(pDC->GetSafeHdc());
	wglMakeCurrent(pDC->GetSafeHdc(), hRC);
	return 0;
}


void CGraphics2View::OnDestroy()
{
	wglMakeCurrent(NULL, NULL); //将当前绘图情景对象赋空
//删除当前绘图情景对象并释放所占内存
	if (hRC) ::wglDeleteContext(hRC);
	if (pDC) delete pDC;
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CGraphics2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	ccx = cx; ccy = cy;
	// TODO: 在此处添加消息处理程序代码
	//设置视口
	glViewport(0, 0, cx, cy);//它负责把视景体截取的图像按照怎样的高和宽显 示到屏幕上。

	//设置投影矩阵（透视投影）
	glMatrixMode(GL_PROJECTION);//增加透视感
	glLoadIdentity();//初始化投影变换矩阵
	//根据窗口大小设置调整正射投影矩阵
	//if (cx <= cy)//glOrtho是正射投影矩阵,先设置GL_PROJECTION，再设置glOrtho
	//glOrtho(-20.0, 20.0, -20.0*(GLfloat)cy / (GLfloat)cx, 20.0*(GLfloat)cy / (GLfloat)cx, -50.0, 50.0);
	//else
	//glOrtho(-1, 1, -1,1, -2, 2);
	glOrtho(0, (GLfloat)cx, (GLfloat)cy, 0, 1000, -1000);
	//MFC 屏幕坐标系（设备坐标系一种）左手坐标系，y下，x右，z外，
	//glOrtho是在设备坐标系上设置，因此把远点，设成负值，在逻辑坐标系里是正的
	glMatrixMode(GL_MODELVIEW);//设置变换模式为模型变换
	glLoadIdentity();//初始化投影变换矩阵

	//glViewport设置视口，之后视口中的坐标怎么设置就是glOrtho的功能
}


bool CGraphics2View::bSetDCPixelFormat()
{
	// TODO: 在此处添加实现代码.
	// 设置像素格式
/*	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  //结构大小
		1,
		PFD_DRAW_TO_WINDOW |             //窗口中绘图
		PFD_SUPPORT_OPENGL |             //支持OPENGL
		PFD_DOUBLEBUFFER,               //双缓冲模式
		PFD_TYPE_RGBA,                 //RGBA颜色模式
		24,                           // 24位色彩深度
		0, 0, 0, 0, 0, 0,                   //无颜色位
		0,                           // 无alpha 缓存
		0,                           //无移位
		0,                           //无加速缓存
		0, 0, 0, 0,                     //无累积位
		32,                          //32位深度缓存
		0,                           //无模板缓存
		0,                           //无辅助缓存
		PFD_MAIN_PLANE,              //PFD主平面
		0,                           //保留
		0, 0, 0                        //忽略主层掩模
	};
	*/
	return false;
}


void CGraphics2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	if (Start == 1)
	{
		m_Pts[num] = point;
		num++;
		if (num == m_PtNum)
		{
			num = 0;
			DrawPolygon();

		}
	}
	if (Start == 2)
	{
		m_Draw[draw_num] = point;
		draw_num++;
		if (draw_num == 2)
		{
			draw_num = 0;
			On_Draw();
		}
	}
	if (Start == 3 || Start == 10 || Start == 11 || Start == 12)
	{
		lpoint.x = point.x;
		lpoint.y = point.y;
	}
	if (Start == 4)
	{
		m_Pts[num_P] = point;
		num_P++;
		if (num_P >= 2 && num_P < 90)
		{
			//num = 0;
			DrawPoly_un();
		}
	}
	if (Start == 5)
	{
		circle = point;
		DrawCircle();
	}
	if (Start == 6)
	{
		ctrlpoints[order][0] = point.x;
		ctrlpoints[order][1] = point.y;
		order++;
		if (order == m_Bezier_num)
		{
			Bezier();
			order = 0;

		}
	}
	if (Start == 7)
	{
		x_coord[order] = point.x;
		y_coord[order] = point.y;
		order++;
		if (order == m_Bezier_num)
		{
			DrawBspline();
			order = 0;
		}
	}
	if (Start == 13)
	{
		cutx = point.x;
		cuty = point.y;
		num++;
		if (num == 1)
		{
			num = 0;
			OnDrawCut();

		}
	}
}
//调色板
void CGraphics2View::OnColorDialog()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg(color, CC_FULLOPEN | CC_RGBINIT);//设置默认颜色
	if (IDOK == dlg.DoModal())
		color = dlg.GetColor();
	ColorR = GetRValue(color);
	ColorG = GetGValue(color);
	ColorB = GetBValue(color);

}


void CGraphics2View::BuildEDGEs()
{
	if (m_pEDGEs)
	{
		delete[] m_pEDGEs;
		m_pEDGEs = NULL;
	}
	m_pEDGEs = new EDGE[m_PtNum];

	for (int i = 0; i < m_PtNum - 1; i++)
	{
		if (m_Pts[i].y > m_Pts[i + 1].y)
		{
			m_pEDGEs[i].Up = m_Pts[i];
			m_pEDGEs[i].Down = m_Pts[i + 1];
		}
		else
		{
			m_pEDGEs[i].Up = m_Pts[i + 1];
			m_pEDGEs[i].Down = m_Pts[i];
		}
		m_pEDGEs[i].EG.Ymax = m_pEDGEs[i].Up.y;
		m_pEDGEs[i].EG.X = m_pEDGEs[i].Down.x;
		m_pEDGEs[i].EG.Dx = double((m_pEDGEs[i].Up.x - m_pEDGEs[i].Down.x)) / (m_pEDGEs[i].Up.y - m_pEDGEs[i].Down.y);
	}

	if (m_Pts[0].y > m_Pts[m_PtNum - 1].y)
	{
		m_pEDGEs[m_PtNum - 1].Up = m_Pts[0];
		m_pEDGEs[m_PtNum - 1].Down = m_Pts[m_PtNum - 1];
	}
	else
	{
		m_pEDGEs[m_PtNum - 1].Up = m_Pts[m_PtNum - 1];
		m_pEDGEs[m_PtNum - 1].Down = m_Pts[0];
	}
	m_pEDGEs[m_PtNum - 1].EG.Ymax = m_pEDGEs[m_PtNum - 1].Up.y;
	m_pEDGEs[m_PtNum - 1].EG.X = m_pEDGEs[m_PtNum - 1].Down.x;
	m_pEDGEs[m_PtNum - 1].EG.Dx = double((m_pEDGEs[m_PtNum - 1].Up.x - m_pEDGEs[m_PtNum - 1].Down.x)) / (m_pEDGEs[m_PtNum - 1].Up.y - m_pEDGEs[m_PtNum - 1].Down.y);

}

void CGraphics2View::CreateET()
{

	GetMinMaxY(MinY, MaxY);
	if (m_pET)
	{
		delete[] m_pET;
		m_pET = NULL;
	}
	m_pET = new CArray <Edge, Edge>[MaxY - MinY + 1];
	// Add EDGE to ET ,把边结构加入边表中
	for (int i = 0; i < m_PtNum; i++)
	{
		int scanline = m_pEDGEs[i].Down.y - MinY;
		m_pET[scanline].Add(m_pEDGEs[i].EG);
	}
	// 多边形的边排序： Sort according to Xmin
	for (int n = MinY; n < MaxY; n++)
	{//每条扫描线与有效边不止一个交点
		int index = n - MinY;
		int sz = m_pET[index].GetSize();
		for (int i = 0; i < sz - 1; i++)
		{
			for (int k = i + 1; k < sz; k++)
			{//将一条有效边与扫描线的交点按照x值递增排序
				if (m_pET[index][i].X > m_pET[index][k].X)
				{
					Edge t = m_pET[index][i];
					m_pET[index][i] = m_pET[index][k];
					m_pET[index][k] = t;
				}
			}
		}
	}

}

void CGraphics2View::InitAET()
{
	if (m_pAET)
	{
		delete[] m_pAET;
		m_pAET = NULL;
	}
	m_pAET = new CArray<Edge, Edge>[MaxY - MinY + 1];
}

void CGraphics2View::FillPolygon(CDC *pDC)
{
	//int nRand = rand();
	//float fMap = (float)255 / RAND_MAX;//RAND_MAX是 <stdlib.h> 中伪随机数生成函数 rand 所能返回的最大数值。
	//int ColorR = (UINT)(float)nRand*fMap + 0.5f;
	//nRand = rand();
	//fMap = (float)255 / RAND_MAX;
	//int ColorG = (UINT)(float)nRand*fMap + 0.5f;
	for (m_CurrentScanLine = MinY; m_CurrentScanLine < MaxY;
		m_CurrentScanLine++)
	{
		MoveNewEdgeFromET();   // 加入新边
		RemoveEdges();         // 删除旧边
		SortAET();             // 按照边的交点的 X值排列
		FillScanLine(pDC, ColorR, ColorG, ColorB);     // 按照配对填充当前扫描行
		UpdateDelteX();        // 更新下条扫描线的交点 X坐标
	}
}

void CGraphics2View::GetMinMaxY(int &MinY, int &MaxY)
{
	for (int i = 0; i < m_PtNum; i++)
	{
		if (MaxY < m_Pts[i].y)
		{
			MaxY = m_Pts[i].y;
		}
		if (MinY > m_Pts[i].y)
		{
			MinY = m_Pts[i].y;
		}
	}
}
void CGraphics2View::GetMinMaxX(int &MinX, int &MaxX)
{
	for (int i = 0; i < m_PtNum; i++)
	{
		if (MaxX < m_Pts[i].x)
		{
			MaxX = m_Pts[i].x;
		}
		if (MinX > m_Pts[i].x)
		{
			MinX = m_Pts[i].x;
		}
	}
}
void CGraphics2View::MoveNewEdgeFromET()
{
	int index = m_CurrentScanLine - MinY;
	for (int i = 0; i < m_pET[index].GetSize(); i++)
	{
		m_pAET[index].Add(m_pET[index][i]);
	}
}
void CGraphics2View::RemoveEdges()
{
	int index = m_CurrentScanLine - MinY;
	for (int i = 0; i < m_pAET[index].GetSize(); i++)
	{
		if (m_CurrentScanLine == m_pAET[index][i].Ymax)
		{
			m_pAET[index].RemoveAt(i);
			i--;
		}
	}
}

void CGraphics2View::SortAET()
{
	// Sort according to Xmin 
	int index = m_CurrentScanLine - MinY;
	int sz = m_pAET[index].GetSize();
	for (int i = 0; i < sz - 1; i++)
	{
		for (int k = i + 1; k < sz; k++)
		{
			if (m_pAET[index][i].X > m_pAET[index][k].X)
			{
				Edge t = m_pAET[index][i];
				m_pAET[index][i] = m_pAET[index][k];
				m_pAET[index][k] = t;
			}
		}
	}
}
// 配对填充当前行
void CGraphics2View::FillScanLine(CDC *pDC, int ColorR, int ColorG, int ColorB)
{
	int mY;
	mY = MaxY - MinY;
	int index = m_CurrentScanLine - MinY;
	for (int i = 0; i < m_pAET[index].GetSize() - 1; i += 2)
	{
		// int i =0; 
		for (int x0 = m_pAET[index][i].X + 0.99; x0 <
			int(m_pAET[index][i + 1].X); x0++)
		{
			pDC->SetPixel(x0, m_CurrentScanLine, RGB(ColorR, ColorG, ColorB));
		}
	}
}

// 更新交点横坐标。
void CGraphics2View::UpdateDelteX()
{
	// Sort according to Xmin 
	int index = m_CurrentScanLine - MinY;
	int sz = m_pAET[index].GetSize();
	for (int i = 0; i < sz; i++)
	{
		m_pAET[index][i].X += m_pAET[index][i].Dx;
		m_pAET[index + 1].Add(m_pAET[index][i]);
	}
}
void CGraphics2View::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	Cxiankuan dlg1;
	if (IDOK == dlg1.DoModal())
	{
		m_PtNum = dlg1.edges;
		Xiank = dlg1.Xk;
		styles = dlg1.styles;

		//Invalidate(TRUE);//刷新画图界面
		Start = 1;
		//开启按钮
		TraEnable = true;
		ScaEnable = true;
		RotEnable = true;
	}
}
void CGraphics2View::DrawPolygon()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineStipple(1, styles);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存	
	glDisable(GL_LINE_STIPPLE);

}


void CGraphics2View::OnPoly_un()
{
	// TODO: 在此添加命令处理程序代码
	Cxiankuan dlg1;
	dlg1.op_PolyUn = true;
	if (IDOK == dlg1.DoModal())
	{
		//m_PtNum = dlg1.edges;
		Xiank = dlg1.Xk;
		styles = dlg1.styles;
		num_P = 0;
		//Invalidate(TRUE);//刷新画图界面
		Start = 4;
		MessageBox(_T("右键顶点删除！"), _T("提示"), MB_OK);

		//开启按钮
	}

}

void CGraphics2View::DrawPoly_un()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineStipple(1, styles);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < num_P; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	for (int i = 0; i < num_P; i++)
	{
		glBegin(GL_POLYGON);

		for (float j = 0; j < 2 * 3.14; j += 0.01)
		{
			x = 5 * cos(j) + m_Pts[i].x;
			y = 5 * sin(j) + m_Pts[i].y;
			glVertex3f(x, y, 0.0);
		}
		glEnd();
	}
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDisable(GL_LINE_STIPPLE);

}

void CGraphics2View::OnCircle()
{
	// TODO: 在此添加命令处理程序代码
	CCircle dlg1;
	//dlg1.GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	if (IDOK == dlg1.DoModal())
	{
		circle_xk = dlg1.xiankuan;
		circle_sty = dlg1.styles;
		circle_llength = dlg1.Llength;
		circle_slength = dlg1.Slength;
		//Invalidate(TRUE);//刷新画图界面
		Start = 5;

	}
}

void CGraphics2View::DrawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineStipple(1, circle_sty);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(circle_xk);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_STRIP);
	float x, y;
	for (float i = 0; i < 2 * 3.1415926; i += 0.01)
	{
		x = circle_llength * cos(i) + circle.x;
		y = circle_slength * sin(i) + circle.y;
		glVertex2i(x, y);

	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDisable(GL_LINE_STIPPLE);

}
//清屏
void CGraphics2View::OnColorClear()
{
	// TODO: 在此添加命令处理程序代码
	//glClearColor(0.7, 0.7, 0.7, 0);
	//将颜色缓存设为glclearcolor命令所设置的颜色，即背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	//禁用按钮
	TraEnable = false;
	ScaEnable = false;
	RotEnable = false;
}

//平移
void CGraphics2View::OnTranslate()
{
	// TODO: 在此添加命令处理程序代码
	Cpingyi dlg2;
	if (IDOK == dlg2.DoModal())
	{
		Trax = dlg2.Tx;
		Tray = dlg2.Ty;
		Traz = dlg2.Tz;
		Translate();
		Start = 0;
	}
}
void CGraphics2View::Translate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();


	glTranslatef(Trax, Tray, Traz);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存

	BuildEDGEs();
	CreateET();
	InitAET();
	FillPolygon(pDC);

	glLoadIdentity();//初始化投影变换矩阵

}
//禁用/开启平移按钮
void CGraphics2View::OnUpdateTranslate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(TraEnable);
}





//缩放
void CGraphics2View::OnScale()
{
	// TODO: 在此添加命令处理程序代码
	Csuofang dlg3;
	if (IDOK == dlg3.DoModal())
	{
		Scaoption = dlg3.Soption;
		if (Scaoption == 0)
			Scaxyz = dlg3.Sxyz;
		else
		{
			Scax = dlg3.Sx;
			Scay = dlg3.Sy;
			Scaz = dlg3.Sz;
		}
		Start = 0;
		Scale();
	}
}
void CGraphics2View::Scale()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();


	if (Scaoption == 0)
		glScalef(Scaxyz, Scaxyz, Scaxyz);
	else
		glScalef(Scax, Scay, Scaz);


	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存

	BuildEDGEs();
	CreateET();
	InitAET();
	FillPolygon(pDC);
	glLoadIdentity();//初始化投影变换矩阵
}
void CGraphics2View::OnUpdateScale(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(ScaEnable);

}


/**********************************************************/
/*旋转*****************************************************/
void CGraphics2View::OnRotate()
{
	// TODO: 在此添加命令处理程序代码
	Cxuanzhuan dlg4;
	if (IDOK == dlg4.DoModal())
	{
		Rotangle = dlg4.Rangle;
		Rotx = dlg4.Rx;
		Roty = dlg4.Ry;
		Rotz = dlg4.Rz;
		Start = 0;
		find_center_point();
		Rotate();

	}
}
void CGraphics2View::Rotate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();

	glTranslatef(c_point.x, c_point.y, 0); // 正方体的中心从中心移动到（0,0,0)
	glRotatef(Rotangle, Rotx, Roty, Rotz);
	glTranslatef(-c_point.x, -c_point.y, 0); // 移回去

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存

	BuildEDGEs();
	CreateET();
	InitAET();
	FillPolygon(pDC);
	glLoadIdentity();//初始化投影变换矩阵
}
void CGraphics2View::OnUpdateRotate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(RotEnable);
}
//找中心函数
void CGraphics2View::find_center_point()
{
	for (int i = 0; i < m_PtNum; i++)
	{
		c_point.x += m_Pts[i].x;
		c_point.y += m_Pts[i].y;
	}
	c_point.x = c_point.x / m_PtNum;
	c_point.y = c_point.y / m_PtNum;

}
/*****************************************************/
/**********************************************************/


/**********************************************************/
/**********************************************************/
//印章
void CGraphics2View::OnnameShow()
{
	nameShow();
}
void CGraphics2View::nameShow()
{
	// TODO: 在此添加命令处理程序代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double  x, y;

	glLineWidth(9);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	//螺旋线
	glBegin(GL_LINE_STRIP);
	glVertex2d(60, 60);
	for (double a = 0; a < 2.83*PI; a += 0.1)
	{
		x = -2.4*a*cos(a);
		y = 2.4*a*sin(a);
		glVertex2d(60 + x, 60 + y);
	}
	glEnd();

	double x1, y1;
	double X = 60 + x,
		Y = 60 + y;
	//右上泪滴
	glLineWidth(8);
	glBegin(GL_LINE_STRIP);
	glVertex2d(X + 5, Y - 10);
	for (double i = 0; i < PI / 6.28; i += 0.01)
	{
		x1 = int(40 * sin(2 * PI * i) * cos(1 * PI * i)) + X + 2;//+ 2.8;
		y1 = -int(40 * sin(2 * PI * i) * sin(1 * PI * i)) + Y; //- 10;
		glVertex2d(x1, y1);
	}
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	glVertex2d(X + 10, Y - 25);
	glVertex2d(X - 22, Y + 41);//主干
	glEnd();

	//画左下泪滴
	glLineWidth(9);
	glBegin(GL_LINE_STRIP);

	for (double i = 0; i < PI / 6.28; i += 0.01)
	{
		x1 = -int(40 * sin(2 * PI * i) * cos(1 * PI * i)) + X - 15;//+ 2.8;
		y1 = int(37 * sin(2 * PI * i) * sin(1 * PI * i)) + Y + 21; //- 10;
		glVertex2d(x1, y1);
	}
	glEnd();

	int ab = 0;
	int pen[5] = { 6,7,8,9,10 };
	glLineWidth(9);
	glBegin(GL_LINE_STRIP);
	glVertex2d(X - 15, Y + 21);
	//画捺
	for (int i = 7; i <= 35; i += 7, ab++)
	{
		//pDC->SelectObject(pen[ab]);
		glVertex2d(X - 15 + i, Y + 21 + i * 0.7);
	}
	glEnd();
	glLineWidth(8);
	glBegin(GL_LINE_STRIP);
	glVertex2d(X - 15 + 35 + 10, Y + 21 + 24 - 8);
	//画勾
	for (double a = 0; a < 1.7*PI; a += 0.1)
	{
		x1 = -2.4*a*cos(a) + X - 15 + 35 + 10;
		y1 = -2.4*a*sin(a) + Y + 21 + 24 - 8;
		glVertex2d(x1, y1);
	}
	glEnd();
	//画e

	glLineWidth(8);
	glTranslated(55, 0, 0);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(X + 5, Y - 10, 0);
		glRotated(-45 * i, 0, 0, 1);
		glTranslated(-(X + 5), -(Y - 10), 0);
		glBegin(GL_LINE_STRIP);
		glVertex2d(X + 5, Y - 10);
		for (double i = 0; i < PI / 5.8; i += 0.01)
		{
			x1 = (40 * sin(2 * PI * i) * cos(1 * PI * i)) + X + 2;//+ 2.8;
			y1 = (40 * sin(2 * PI * i) * sin(1 * PI * i)) + Y; //- 10;
			glVertex2d(x1, y1);
		}
		glEnd();
	}
	glTranslated(X + 5, Y - 10, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-(X + 5), -(Y - 10), 0);

	glLineWidth(8);
	glTranslated(65, 0, 0);
	for (int i = 0; i < 2; i++)
	{
		glTranslated(X + 5, Y - 10, 0);
		glRotated(-45 * i, 0, 0, 1);
		glTranslated(-(X + 5), -(Y - 10), 0);
		glBegin(GL_LINE_STRIP);
		glVertex2d(X + 5, Y - 10);
		for (double i = 0; i < PI / 5.8; i += 0.01)
		{
			x1 = (40 * sin(2 * PI * i) * cos(1 * PI * i)) + X + 2;//+ 2.8;
			y1 = (40 * sin(2 * PI * i) * sin(1 * PI * i)) + Y; //- 10;
			glVertex2d(x1, y1);
		}
		glEnd();
	}

	glLoadIdentity();

	SwapBuffers(wglGetCurrentDC());//交换前后缓存

}
void CGraphics2View::OnnameShowRotate()
{
	// TODO: 在此添加命令处理程序代码
	glTranslated(500, 0, 0);
	glRotated(180, 0, 50, 0);
	nameShow();
	glLoadIdentity();
	/******/
	//nameShow函数中间不能用	glLoadIdentity();，在函数执行最后可以用，因为此时图元已经全部画出。

}
/**************************************************/
/**************************************************/



/*******************************************/
/*裁剪*/
#define left 1
#define right 2
#define bottom 4
#define top 8
void CGraphics2View::OnCS_draw()
{
	// TODO: 在此添加命令处理程序代码
	Start = 2;
}
void CGraphics2View::OnCohen_Sutherland()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xl, yb);
	glVertex2i(xl, yt);
	glVertex2i(xr, yt);
	glVertex2i(xr, yb);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(m_Draw[0].x, m_Draw[0].y);
	glVertex2i(m_Draw[1].x, m_Draw[1].y);
	glEnd();

	cohen(m_Draw[0].x, m_Draw[0].y, m_Draw[1].x, m_Draw[1].y);
}
void CGraphics2View::On_Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	glLineWidth(Xiank);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xl, yb);
	glVertex2i(xl, yt);
	glVertex2i(xr, yt);
	glVertex2i(xr, yb);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(m_Draw[0].x, m_Draw[0].y);
	glVertex2i(m_Draw[1].x, m_Draw[1].y);
	glEnd();
	SwapBuffers(wglGetCurrentDC());
	Start = 0;

}
void  CGraphics2View::encode(double x, double y, int &code)
{

	int c = 0;
	if (x < xl) { c = c + left; }
	else if (x > xr) { c = c + right; }
	if (y < yb) { c = c + bottom; }
	else if (y > yt) { c = c + top; }
	code = c;
}
void CGraphics2View::cohen(double x1, double y1, double x2, double y2)
{

	int code1, code2, code;
	int x, y;
	encode(x1, y1, code1);
	encode(x2, y2, code2);
	while (code1 != 0 || code2 != 0)//都在里面时，直接画线，否则进行判断
	{
		if ((code1&code2) != 0)  return;//都在外面舍弃
		code = code1;
		if (code1 == 0)  code = code2;
		if ((left&code) != 0)
		{
			x = xl; y = y1 + (y2 - y1)*(xl - x1) / (x2 - x1);
		}
		else if ((right&code) != 0)
		{
			x = xr; y = y1 + (y2 - y1)*(xr - x1) / (x2 - x1);
		}
		else if ((bottom&code) != 0)
		{
			y = yb; x = x1 + (x2 - x1)*(yb - y1) / (y2 - y1);
		}
		else if ((top&code) != 0)
		{
			y = yt; x = x1 + (x2 - x1)*(yt - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x; y1 = y; encode(x, y, code1);
		}
		else
		{
			x2 = x; y2 = y; encode(x, y, code2);
		}
	}
	glLineWidth(1);
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
	SwapBuffers(wglGetCurrentDC());
}
/******************************************************************/
/******************************************************************/

/*************************************/
/*三维*******************************/
void CGraphics2View::OnPixel()
{
	// 将立方体的八个顶点保存到一个数组里面
	MessageBox(_T("右键旋转，左键平移，滚轮缩放！"), _T("提示"), MB_OK);
	onDrawPixel();
	SwapBuffers(wglGetCurrentDC());
	Start = 3;

}
static const GLfloat vertex_list[][3] = {
	10, 500, 500,
	 500, 500, 500,
	10,  10, 500,
	 500,  10, 500,
	10, 500,  10,
	500,500,10,
	 10, 10,  10,
	 500,  10,  10,
};
void CGraphics2View::onDrawPixel()
{

	static const GLint index_list[][4] = {
		0, 2, 3, 1,
		0, 4, 6, 2,
		0, 1, 5, 4,
		4, 5, 7, 6,
		1, 3, 7, 5,
		2, 6, 7, 3,
	};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(0, 0, 0);							//如果没有调用glLookAt设置视图矩阵，默认情况下，
													//相机会被设置为位置在世界坐标系原点，指向z轴负方向，朝上向量为（0，1，0）。								
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)         // 有六个面，循环六次
		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
			glVertex3fv(vertex_list[index_list[i][j]]);
	glEnd();

	glColor3ub(0, 0, 255);
	glLineWidth(3);
	for (int i = 0; i < 6; ++i)  	  // 有六个面，循环六次
	{
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
			glVertex3fv(vertex_list[index_list[i][j]]);
		glEnd();
	}
	//glLoadIdentity();


}
void CGraphics2View::OnCuboid()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("右键旋转，左键平移，滚轮缩放！"), _T("提示"), MB_OK);
	DrawCuboid();
	SwapBuffers(wglGetCurrentDC());

	Start = 10;
}
static const GLfloat vertex_list_Cu[][3] = {
10, 500, 1000,
 500, 500, 1000,
10,  10, 1000,
 500,  10, 1000,
10, 500,  10,
500,500,10,
 10, 10,  10,
 500,  10,  10,
};
void CGraphics2View::DrawCuboid()
{

	static const GLint index_list[][4] = {
		0, 2, 3, 1,
		0, 4, 6, 2,
		0, 1, 5, 4,
		4, 5, 7, 6,
		1, 3, 7, 5,
		2, 6, 7, 3,
	};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(0, 0, 0);							//如果没有调用glLookAt设置视图矩阵，默认情况下，
													//相机会被设置为位置在世界坐标系原点，指向z轴负方向，朝上向量为（0，1，0）。								
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)         // 有六个面，循环六次
		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
			glVertex3fv(vertex_list_Cu[index_list[i][j]]);
	glEnd();

	glColor3ub(0, 0, 255);
	glLineWidth(3);
	for (int i = 0; i < 6; ++i)  	  // 有六个面，循环六次
	{
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
			glVertex3fv(vertex_list_Cu[index_list[i][j]]);
		glEnd();
	}
	//glLoadIdentity();

}

void CGraphics2View::OnGlobe()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("右键旋转，左键平移，滚轮缩放！"), _T("提示"), MB_OK);
	DrawGlobe();
	SwapBuffers(wglGetCurrentDC());
	Start = 11;
}

void CGraphics2View::DrawGlobe()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (float i = 0; i < 2 * 3.1415926; i += 0.01)
	{
		glColor3ub(0, 0, 0);
		glTranslated(300, 300, 300);
		glRotated(i, 0, 1, 0);
		glTranslated(-300, -300, -300);
		glBegin(GL_POLYGON);
		for (float i = 0; i < 2 * 3.1415926; i += 0.1)
			glVertex3f(300 + 100 * cos(i), 300 + 100 * sin(i), 300);
		glEnd();

	}
	glColor3ub(255, 255, 255);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2 * 3.1415926; i += 0.1)
		glVertex3f(300 + 100 * cos(i), 300 + 100 * sin(i), 300);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2 * 3.1415926; i += 0.1)
		glVertex3f(300 + 100 * cos(i), 300, 300 + 100 * sin(i));
	glEnd();


}
void CGraphics2View::On3DCurve()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("右键旋转，左键平移"), _T("提示"), MB_OK);
	Draw3DCurve();
	SwapBuffers(wglGetCurrentDC());
	Start = 12;
}

GLfloat ctrlpointsCurve[4][4][3] = {

	{{100,100,300},{200,130,0},{300,70,0},{400,100,300}},
	{{100,200,0},{200,230,0},{300,170,0},{400,200,0}},
	{{100,300,0},{200,330,0},{300,270,0},{400,300,0}},
	{{100,400,300},{200,430,0},{300,370,0},{400,400,300}}

};
void CGraphics2View::Draw3DCurve()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex3f(100, 100, 300);
	glVertex3f(400, 100, 300);
	glVertex3f(400, 400, 300);
	glVertex3f(100, 400, 300);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	int i, j;
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpointsCurve[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);   //激活该曲面函数
	for (j = 0; j <= 20; j++)
	{
		int nRand = rand();
		float fMap = (float)255 / RAND_MAX;//RAND_MAX是 <stdlib.h> 中伪随机数生成函数 rand 所能返回的最大数值。
		int ColorR = (UINT)(float)nRand*fMap + 0.5f;
		nRand = rand();
		fMap = (float)255 / RAND_MAX;
		int ColorG = (UINT)(float)nRand*fMap + 0.5f;
		glColor3ub(ColorR, ColorG, 125);
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 20; i++)
			glEvalCoord2f((GLfloat)i / 20.0, (GLfloat)j / 20.0); //调用求值器
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 20; i++)
			glEvalCoord2f((GLfloat)j / 20.0, (GLfloat)i / 20.0); //调用求值器
		glEnd();
	}


}

void CGraphics2View::OnCuboidV()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	DrawCuboid();
	SwapBuffers(wglGetCurrentDC());

}
void CGraphics2View::OnCuboidW()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	glTranslated(255, 255, 505);
	glRotated(90, 1, 0, 0);
	glTranslated(-255,-255, -505);
	DrawCuboid();
	SwapBuffers(wglGetCurrentDC());
	glLoadIdentity();
}


void CGraphics2View::OnCuboidH()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	glTranslated(255, 255, 505);
	glRotated(-90, 0, 1, 0);
	glTranslated(-250, -250, -505);
	DrawCuboid();
	SwapBuffers(wglGetCurrentDC());
	glLoadIdentity();
}

void CGraphics2View::On3DV()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	Draw3DCurve();
	SwapBuffers(wglGetCurrentDC());

}
void CGraphics2View::On3DW()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	glTranslated(250, 250, 250);
	glRotated(90, 1, 0, 0);
	glTranslated(-250, -250, -250);
	Draw3DCurve();
	SwapBuffers(wglGetCurrentDC());
	glLoadIdentity();
}


void CGraphics2View::On3DH()
{
	// TODO: 在此添加命令处理程序代码
	Start = 0;
	glTranslated(250, 250, 250);
	glRotated(-90, 0, 1, 0);
	glTranslated(-250, -250, -250);
	Draw3DCurve();
	SwapBuffers(wglGetCurrentDC());
	glLoadIdentity();
}

void CGraphics2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (point.x < ccx&&point.y < ccy&&Start == 3)

	{

		int diffX = (int)(point.x - rpoint.x);

		int diffY = (int)(point.y - rpoint.y);

		//rpoint.x = (float)point.x;

		//rpoint.y = (float)point.y;
		if (nFlags&MK_RBUTTON)
		{
			RpointX_zoom = (float)diffX / 3;
			RpointY_zoom = (float)diffY / 3;
			if (RpointY_zoom > 90) RpointY_zoom = 90;
			if (RpointY_zoom < -90) RpointY_zoom = -90;
			if (RpointX_zoom > 90)RpointX_zoom = 90;
			if (RpointX_zoom < -90)RpointX_zoom = -90;

			glTranslated(150, 150, 500);
			glTranslated(255, 255, 255);
			glRotated(RpointX_zoom, 0, 1, 0);
			glTranslated(-255, -255, -255);

			glTranslated(255, 255, 255);
			glRotated(RpointY_zoom, 1, 0, 0);
			glTranslated(-255, -255, -255);

			onDrawPixel();
			if (RpointX_zoom > 0 && RpointY_zoom > 0 && RpointX_zoom < 90 && RpointY_zoom < 90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list[0]);
				glVertex3fv(vertex_list[2]);
				glVertex3fv(vertex_list[0]);
				glVertex3fv(vertex_list[1]);
				glVertex3fv(vertex_list[0]);
				glVertex3fv(vertex_list[4]);
				glEnd();
			}
			else if (RpointX_zoom < 0 && RpointY_zoom > 0 && RpointX_zoom > -90 && RpointY_zoom < 90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list[1]);
				glVertex3fv(vertex_list[0]);
				glVertex3fv(vertex_list[1]);
				glVertex3fv(vertex_list[5]);
				glVertex3fv(vertex_list[1]);
				glVertex3fv(vertex_list[3]);
				glEnd();
			}
			else if (RpointX_zoom < 0 && RpointY_zoom < 0 && RpointX_zoom>-90 && RpointY_zoom>-90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list[3]);
				glVertex3fv(vertex_list[1]);
				glVertex3fv(vertex_list[3]);
				glVertex3fv(vertex_list[2]);
				glVertex3fv(vertex_list[3]);
				glVertex3fv(vertex_list[7]);
				glEnd();
			}
			else if (RpointX_zoom > 0 && RpointY_zoom < 0 && RpointX_zoom<90 && RpointY_zoom>-90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list[2]);
				glVertex3fv(vertex_list[6]);
				glVertex3fv(vertex_list[2]);
				glVertex3fv(vertex_list[3]);
				glVertex3fv(vertex_list[2]);
				glVertex3fv(vertex_list[0]);
				glEnd();
			}
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
		if (nFlags&MK_LBUTTON)
		{
			LpointX_zoom = point.x - lpoint.x;
			LpointY_zoom = point.y - lpoint.y;
			//glTranslated(100, 100, 500);
			glTranslated(LpointX_zoom, 0, 0);
			glTranslated(0, LpointY_zoom, 0);
			onDrawPixel();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
	}
	if (point.x < ccx&&point.y < ccy&&Start == 10)

	{

		int diffX = (int)(point.x - rpoint.x);

		int diffY = (int)(point.y - rpoint.y);

		//rpoint.x = (float)point.x;

		//rpoint.y = (float)point.y;
		if (nFlags&MK_RBUTTON)
		{
			RpointX_zoom = (float)diffX / 3;
			RpointY_zoom = (float)diffY / 3;
			if (RpointY_zoom > 90) RpointY_zoom = 90;
			if (RpointY_zoom < -90) RpointY_zoom = -90;
			if (RpointX_zoom > 90)RpointX_zoom = 90;
			if (RpointX_zoom < -90)RpointX_zoom = -90;

			glTranslated(150, 150, 500);
			glTranslated(255, 255, 505);
			glRotated(RpointX_zoom, 0, 1, 0);
			glTranslated(-255, -255, -505);

			glTranslated(255, 255, 505);
			glRotated(RpointY_zoom, 1, 0, 0);
			glTranslated(-255, -255, -505);

			DrawCuboid();
			if (RpointX_zoom > 0 && RpointY_zoom > 0 && RpointX_zoom < 90 && RpointY_zoom < 90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list_Cu[0]);
				glVertex3fv(vertex_list_Cu[2]);
				glVertex3fv(vertex_list_Cu[0]);
				glVertex3fv(vertex_list_Cu[1]);
				glVertex3fv(vertex_list_Cu[0]);
				glVertex3fv(vertex_list_Cu[4]);
				glEnd();
			}
			else if (RpointX_zoom < 0 && RpointY_zoom > 0 && RpointX_zoom > -90 && RpointY_zoom < 90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list_Cu[1]);
				glVertex3fv(vertex_list_Cu[0]);
				glVertex3fv(vertex_list_Cu[1]);
				glVertex3fv(vertex_list_Cu[5]);
				glVertex3fv(vertex_list_Cu[1]);
				glVertex3fv(vertex_list_Cu[3]);
				glEnd();
			}
			else if (RpointX_zoom < 0 && RpointY_zoom < 0 && RpointX_zoom>-90 && RpointY_zoom>-90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list_Cu[3]);
				glVertex3fv(vertex_list_Cu[1]);
				glVertex3fv(vertex_list_Cu[3]);
				glVertex3fv(vertex_list_Cu[2]);
				glVertex3fv(vertex_list_Cu[3]);
				glVertex3fv(vertex_list_Cu[7]);
				glEnd();
			}
			else if (RpointX_zoom > 0 && RpointY_zoom < 0 && RpointX_zoom<90 && RpointY_zoom>-90)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINES);
				glVertex3fv(vertex_list_Cu[2]);
				glVertex3fv(vertex_list_Cu[6]);
				glVertex3fv(vertex_list_Cu[2]);
				glVertex3fv(vertex_list_Cu[3]);
				glVertex3fv(vertex_list_Cu[2]);
				glVertex3fv(vertex_list_Cu[0]);
				glEnd();
			}
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
		if (nFlags&MK_LBUTTON)
		{
			LpointX_zoom = point.x - lpoint.x;
			LpointY_zoom = point.y - lpoint.y;
			//glTranslated(100, 100, 500);
			glTranslated(LpointX_zoom, 0, 0);
			glTranslated(0, LpointY_zoom, 0);
			DrawCuboid();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
	}
	if (point.x < ccx&&point.y < ccy&&Start == 11)

	{

		int diffX = (int)(point.x - rpoint.x);

		int diffY = (int)(point.y - rpoint.y);

		//rpoint.x = (float)point.x;

		//rpoint.y = (float)point.y;
		if (nFlags&MK_RBUTTON)
		{
			RpointX_zoom = (float)diffX / 3;
			RpointY_zoom = (float)diffY / 3;


			glTranslated(300, 300, 300);
			glRotated(RpointX_zoom, 0, 1, 0);
			glTranslated(-300, -300, -300);

			glTranslated(300, 300, 300);
			glRotated(RpointY_zoom, 1, 0, 0);
			glTranslated(-300, -300, -300);

			DrawGlobe();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
		if (nFlags&MK_LBUTTON)
		{
			LpointX_zoom = point.x - lpoint.x;
			LpointY_zoom = point.y - lpoint.y;
			//glTranslated(100, 100, 500);
			glTranslated(LpointX_zoom, 0, 0);
			glTranslated(0, LpointY_zoom, 0);
			DrawGlobe();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
	}
	if (point.x < ccx&&point.y < ccy&&Start == 12)

	{

		int diffX = (int)(point.x - rpoint.x);

		int diffY = (int)(point.y - rpoint.y);

		//rpoint.x = (float)point.x;

		//rpoint.y = (float)point.y;
		if (nFlags&MK_RBUTTON)
		{
			RpointX_zoom = (float)diffX / 3;
			RpointY_zoom = (float)diffY / 3;


			glTranslated(250, 250, 250);
			glRotated(RpointX_zoom, 0, 1, 0);
			glTranslated(-250, -250, -250);

			glTranslated(250, 250, 250);
			glRotated(RpointY_zoom, 1, 0, 0);
			glTranslated(-250, -250, -250);

			Draw3DCurve();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
		if (nFlags&MK_LBUTTON)
		{
			LpointX_zoom = point.x - lpoint.x;
			LpointY_zoom = point.y - lpoint.y;
			//glTranslated(100, 100, 500);
			glTranslated(LpointX_zoom, 0, 0);
			glTranslated(0, LpointY_zoom, 0);
			Draw3DCurve();
			SwapBuffers(wglGetCurrentDC());

			glLoadIdentity();

		}
	}

	if (Start == 8 && nest != -1)
	{
		if (nFlags&MK_RBUTTON)
		{
			x_coord[nest] = point.x;
			y_coord[nest] = point.y;
			DrawBspline();
		}
	}
	if (Start == 9 && nest != -1)
	{
		if (nFlags&MK_RBUTTON)
		{
			ctrlpoints[nest][0] = point.x;
			ctrlpoints[nest][1] = point.y;
			Bezier();
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CGraphics2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonDown(nFlags, point);
	if (Start == 3 || Start == 10 || Start == 11 || Start == 12)
	{
		rpoint.x = point.x;
		rpoint.y = point.y;
	}
	else if (Start == 8)
	{
		for (int i = 0; i < m_Bezier_num + 1; i++)
		{
			L = (point.x - x_coord[i])*(point.x - x_coord[i]) + (point.y - y_coord[i])*(point.y - y_coord[i]);
			if (L < length)
			{
				length = L;
				nest = i;
			}
		}
	}
	else if (Start == 9)
	{
		for (int i = 0; i < m_Bezier_num + 1; i++)
		{
			L = (point.x - ctrlpoints[i][0])*(point.x - ctrlpoints[i][0]) + (point.y - ctrlpoints[i][1])*(point.y - ctrlpoints[i][1]);
			if (L < length)
			{
				length = L;
				nest = i;
			}
		}
	}
	else if (Start == 4)
	{

		for (int i = 0; i < num_P; i++)
		{
			L = (point.x - m_Pts[i].x)*(point.x - m_Pts[i].x) + (point.y - m_Pts[i].y)*(point.y - m_Pts[i].y);
			if (L < length)
			{
				length = L;
				nest = i;
			}
		}
		if (nest != -1)
		{
			for (int i = nest; i < num_P - 1; i++)
			{
				m_Pts[i] = m_Pts[i + 1];
			}
			num_P--;
			DrawPoly_un();
		}
	}
}

BOOL CGraphics2View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Start == 3)
	{
		if (zDelta > 0)
		{
			//glTranslated(100, 100, 500);
			//glTranslated(300, 300, 0);
			glScaled(1 + m_fMultiple, 1 + m_fMultiple, 1 + m_fMultiple);
			//glTranslated(-pt.x, -pt.y, 0);
			onDrawPixel();			SwapBuffers(wglGetCurrentDC());

		}
		else
		{
			glScaled(1 - m_fMultiple, 1 - m_fMultiple, 1 - m_fMultiple);
			onDrawPixel();
			SwapBuffers(wglGetCurrentDC());

		}
	}
	if (Start == 10)
	{
		if (zDelta > 0)
		{
			//glTranslated(100, 100, 500);
			//glTranslated(300, 300, 0);
			glScaled(1 + m_fMultiple, 1 + m_fMultiple, 1 + m_fMultiple);
			//glTranslated(-pt.x, -pt.y, 0);
			DrawCuboid();
			SwapBuffers(wglGetCurrentDC());
		}
		else
		{
			glScaled(1 - m_fMultiple, 1 - m_fMultiple, 1 - m_fMultiple);
			DrawCuboid();
			SwapBuffers(wglGetCurrentDC());

		}
	}
	if (Start == 11)
	{
		if (zDelta > 0)
		{
			//glTranslated(100, 100, 500);
			//glTranslated(300, 300, 0);
			glScaled(1 + m_fMultiple, 1 + m_fMultiple, 1 + m_fMultiple);
			//glTranslated(-pt.x, -pt.y, 0);
			DrawGlobe();
			SwapBuffers(wglGetCurrentDC());
		}
		else
		{
			glScaled(1 - m_fMultiple, 1 - m_fMultiple, 1 - m_fMultiple);
			DrawGlobe();
			SwapBuffers(wglGetCurrentDC());

		}
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

/****************************************/
/*LOGO***********************************/
void CGraphics2View::Draw_One_Logo()
{
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2d(203, 54);
	glVertex2d(153, 104);
	glVertex2d(203, 155);
	glVertex2d(253, 104);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(203, 80);
	glVertex2d(179, 104);
	glVertex2d(203, 128);
	glVertex2d(227, 104);
	glEnd();
}

void CGraphics2View::OnLogoRedandWhite()
{
	Start = 0;
	glLoadIdentity();

	// TODO: 在此添加命令处理程序代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLineWidth(1);
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(2, 3);
	glVertex2d(2, 403);
	glVertex2d(403, 403);
	glVertex2d(403, 3);
	glEnd();

	Draw_One_Logo();

	glTranslated(-75, 75, 0);
	Draw_One_Logo();
	glTranslated(75, 0, 0);
	Draw_One_Logo();
	glTranslated(75, 0, 0);
	Draw_One_Logo();

	glTranslated(0, 75, 0);
	Draw_One_Logo();
	glTranslated(-75, 0, 0);
	Draw_One_Logo();
	glTranslated(-75, 0, 0);
	Draw_One_Logo();

	glLoadIdentity();
	glColor3ub(255, 255, 255);
	glBegin(GL_TRIANGLES);
	glVertex2d(203, 278);
	glVertex2d(133, 349);
	glVertex2d(273, 349);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2d(203, 305);
	glVertex2d(185, 323);
	glVertex2d(221, 323);
	glEnd();

	SwapBuffers(wglGetCurrentDC());

}

void CGraphics2View::Draw_One_Colorful_Logo(int R, int G, int B)
{
	glColor3ub(R, G, B);
	glBegin(GL_POLYGON);
	glVertex2d(240, 47);
	glVertex2d(156, 214);
	glVertex2d(240, 297);
	glVertex2d(324, 214);
	glEnd();

	/*glLineWidth(2);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(240, 49);
	glVertex2d(240, 297);
	glEnd();*/

}

void CGraphics2View::OnLogoColorful()
{
	Start = 0;

	glLoadIdentity();

	int Co[5][3] = { { 212,173,148 }, {236,200,180},{241,218,192},{188,142,115},{215,193,166} };
	// TODO: 在此添加命令处理程序代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2d(2, 2);
	glVertex2d(2, 540);
	glVertex2d(540, 540);
	glVertex2d(540, 2);
	glEnd();

	for (int i = 0; i < 5; i++)
	{
		glTranslated(240, 297, 0);
		glRotated(72, 0, 0, 1);
		glTranslated(-240, -297, 0);
		Draw_One_Colorful_Logo(Co[i][0], Co[i][1], Co[i][2]);
	}
	glLoadIdentity();
	SwapBuffers(wglGetCurrentDC());

}

/****************************************/
/****************************************/

/*************************************/




void CGraphics2View::Bezier()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_FLAT);
	//下行用于定义曲线函数
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, m_Bezier_num, &ctrlpoints[0][0]);
	/*
	   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	   void glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
	   //target参数指定了控制点表示什么。如表所示，并因此确定了points应该提供多少值

	   //u1和u2参数表示变量u的变化范围，变量stride是每个存储块之间单精度或双精度浮点数的数量

	   //order参数的值就是stride+1,它应该与控制点的数量一致

	   //points参数指向第一个控制点的第一个坐标
	*/
	glEnable(GL_MAP1_VERTEX_3); //将当前曲线函数激活
	int i;
	//下面用求值器按20等分计算Bezier曲线上的点
	glColor3ub(ColorR, ColorG, ColorB);
	glLineStipple(1, m_Bezier_styles);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(m_Bezier_xiankuan);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 20; i++)
		glEvalCoord1f((GLfloat)i / 20.0); //相当于调用了glVertex*()
	glEnd();
	//下面绘制控制多边形
	glColor3ub(255, 255, 255);
	for (int i = 0; i < order; i++)
	{
		glBegin(GL_POLYGON);

		for (float j = 0; j < 2 * 3.14; j += 0.01)
		{
			x = 5 * cos(j) + ctrlpoints[i][0];
			y = 5 * sin(j) + ctrlpoints[i][1];
			glVertex3f(x, y, 0.0);
		}
		glEnd();
	}
	glLineWidth(1);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < m_Bezier_num; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
	//glFlush();
	SwapBuffers(wglGetCurrentDC());
	glDisable(GL_LINE_STIPPLE);

}
void CGraphics2View::OnBezier()
{
	// TODO: 在此添加命令处理程序代码
	Cxiankuan dlg1;
	//dlg1.GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	if (IDOK == dlg1.DoModal())
	{
		m_Bezier_xiankuan = dlg1.Xk;
		m_Bezier_styles = dlg1.styles;
		m_Bezier_num = dlg1.edges + 1;
		//Invalidate(TRUE);//刷新画图界面
		Start = 6;

	}
	order = 0;

}
//B样条
void CGraphics2View::Bspline()
{
	float t, dt, f1, f2, f3, f4;
	dt = 1.0 / 20;      // u[0,1].      
	glBegin(GL_LINE_STRIP);
	for (int j = 0; j < (order - 2); j++)
		for (t = 0.0; t <= 1.0 + dt; t += dt)
		{
			f1 = (1.0 / 6)*((-1)*t*t*t + 3 * t*t - 3 * t + 1);
			f2 = (1.0 / 6)*(3 * t*t*t - 6 * t*t + 4);
			f3 = (1.0 / 6)*((-3)*t*t*t + 3 * t*t + 3 * t + 1);
			f4 = (1.0 / 6)*(t*t*t);
			glVertex2f(f1*x_coord[j] + f2 * x_coord[j + 1] + f3 * x_coord[j + 2] + f4 * x_coord[j + 3],
				f1*y_coord[j] + f2 * y_coord[j + 1] + f3 * y_coord[j + 2] + f4 * y_coord[j + 3]);
		}
	glEnd();

}
void CGraphics2View::DrawBspline()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < order; i++)
		glVertex3f(x_coord[i], y_coord[i], 0.0);
	glEnd();
	for (int i = 0; i < order; i++)
	{
		glBegin(GL_POLYGON);

		for (float j = 0; j < 2 * 3.14; j += 0.01)
		{
			x = 5 * cos(j) + x_coord[i];
			y = 5 * sin(j) + y_coord[i];
			glVertex3f(x, y, 0.0);
		}
		glEnd();
	}
	glColor3ub(ColorR, ColorG, ColorB);
	glLineWidth(m_Bezier_xiankuan);
	Bspline();
	//glFlush();
	SwapBuffers(wglGetCurrentDC());
}
void CGraphics2View::OnBspline()
{
	// TODO: 在此添加命令处理程序代码
	Cxiankuan dlg1;
	//dlg1.GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	if (IDOK == dlg1.DoModal())
	{
		m_Bezier_xiankuan = dlg1.Xk;
		m_Bezier_styles = dlg1.styles;
		m_Bezier_num = dlg1.edges + 1;
		//Invalidate(TRUE);//刷新画图界面
		Start = 7;

	}
	order = 0;
}

void CGraphics2View::OnBsplineMOVE()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	//glTranslatef(100, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MessageBox(_T("鼠标右键点击移动，松开取消！"), _T("提示"), MB_OK);
	Start = 8;
	order = m_Bezier_num;
	DrawBspline();
}


void CGraphics2View::OnBezierMOVE()
{
	// TODO: 在此添加命令处理程序代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MessageBox(_T("鼠标右键点击移动，松开取消！"), _T("提示"), MB_OK);
	Start = 9;
	order = m_Bezier_num;
	Bezier();
}


void CGraphics2View::OnFillColor()
{
	// TODO: 在此添加命令处理程序代码
	if (Start == 1)
	{
		BuildEDGEs();
		CreateET();
		InitAET();
		FillPolygon(pDC);
	}
}

void CGraphics2View::OnCut()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("点击选择截取位置！"), _T("提示"), MB_OK);
	Start = 13;

}

void CGraphics2View::OnDrawCut()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLdouble eqn[4] = { -1,0,0.0,cutx };
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	GLdouble eqn1[4] = { 0,-1,0.0,cuty };
	glClipPlane(GL_CLIP_PLANE1, eqn1);
	glEnable(GL_CLIP_PLANE1);

	glLineStipple(1, styles);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(Xiank);
	glColor3ub(ColorR, ColorG, ColorB);//用rgb（255最大)设置颜色
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_PtNum; i++)
	{
		glVertex2i(m_Pts[i].x, m_Pts[i].y);
	}
	glEnd();
	SwapBuffers(wglGetCurrentDC());//交换前后缓存	
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_LINE_STIPPLE);


}

#define BMP_Header_Length 54 
void CGraphics2View::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	SwapBuffers(wglGetCurrentDC());
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	// 计算像素数据的实际长度 
	i = ccx * 3; // 得到每一行的像素数据长度 
	while (i % 4 != 0) // 补充数据，直到i是的倍数 
		++i; // 本来还有更快的算法， 
		// 但这里仅追求直观，对速度没有太高要求 
	PixelDataLength = i * ccy;

	// 分配内存和打开文件 
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		return;

	pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
		return;

	pWritingFile = fopen("grab.bmp", "wb");
	if (pWritingFile == 0)
		return;

	// 读取像素 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, ccx, ccy,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头 
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = ccx;
	j = ccy;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据 
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件 
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}


void CGraphics2View::OnSaveJpg()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	SwapBuffers(wglGetCurrentDC());
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	// 计算像素数据的实际长度 
	i = ccx * 3; // 得到每一行的像素数据长度 
	while (i % 4 != 0) // 补充数据，直到i是的倍数 
		++i; // 本来还有更快的算法， 
		// 但这里仅追求直观，对速度没有太高要求 
	PixelDataLength = i * ccy;

	// 分配内存和打开文件 
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		return;

	pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
		return;

	pWritingFile = fopen("grab2.jpg", "wb");
	if (pWritingFile == 0)
		return;

	// 读取像素 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, ccx, ccy,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头 
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = ccx;
	j = ccy;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据 
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件 
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}




