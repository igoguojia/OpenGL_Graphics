#pragma once

typedef  double   array2d[5][5];
typedef  double   array[24];

/***********************************************************
* ����˵����Aux1, Aux2, Aux3, Aux4, Aux5, Aux6, Aux7,  *
* Aux8��ȫ�ֱ��������ڴ�ȡ�����û�����ϵ�㵽�۲�����ϵ��� *
* ����ֵ��ʽ�е�������ֵ��X, Y, Z, C, XP, YP, ZP, CPΪһά *
* ���飬������嶥��������꣬XT, YT, ZT��Ϊһά���飬��� *
* ���嶥�㾭�任�������ֵ��A, Ah, Aw��ά���������������  *
* ͼ�ı任����������ͼ�ı任�������ֵ��                   *
***********************************************************/

class CBaseClass  // ����һ������
{
public:
	double	x0, z0, Aux1, Aux2, Aux3, Aux4, Aux5, Aux6, Aux7, Aux8;
	int     Theta, theta_y, phi_x, xx, yy, nn, n, ps, ed, eh, od, hl;
	array     X, Y, Z, C, XT, YT, ZT, XP, YP, ZP, CP;
	array2d   A, A1, Ah, Aw;
	double ax[9], ay[9], az[9];
	double bx[9], by[9], bz[9];
public:
	CBaseClass();
	virtual ~CBaseClass();
	void ReadWorkpiece();
	//void Read();
	void Calculate(array2d B);
	void MCalculate(array2d B);
	//	void XCalculate(array2d B);
	//	void TransformMatrice();
	void DrawText();
	void Display();
	void Drawve();
	//	void Drawvt();
	//	void Drawse();
	void DrawViewV(CDC* pdc, CRect rr);
	void DrawViewH();// CDC* pdc, CRect rr);
	void DrawViewW();// CDC* pdc, CRect rr);
	void moveto(double x, double y, CDC* pdc);
	void lineto(double x, double y, CDC* pdc);
	void setpixel(double x, double y, CDC* pdc);
	//	void Draw();
};

