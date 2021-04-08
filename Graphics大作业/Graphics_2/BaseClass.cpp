#include "pch.h"
#include "BaseClass.h"
//#include"Graphics_2View.h"

CBaseClass::CBaseClass()
{
	ed = 2000, eh = 100, od = 400, hl = 1, ps = 0;
}

CBaseClass::~CBaseClass()
{

}

// �˺��������ͼ�������϶�����������ֵ
void   CBaseClass::ReadWorkpiece()
{
	X[1] = 0;  Y[1] = 0;  Z[1] = 0;  C[1] = 1;
	X[2] = 45;  Y[2] = 0;  Z[2] = 0;  C[2] = 1;
	X[3] = 45; Y[3] = 37;  Z[3] = 0;  C[3] = 1;
	X[4] = 0;  Y[4] = 37;  Z[4] = 0;  C[4] = 1;
	X[5] = 0;  Y[5] = 37;  Z[5] = 45;  C[5] = 1;
	X[6] = 0;  Y[6] = 0;  Z[6] = 45;  C[6] = 1;
	X[7] = 12;  Y[7] = 0;  Z[7] = 45;  C[7] = 1;
	X[8] = 30;  Y[8] = 0;  Z[8] = 14;  C[8] = 1;
	X[9] = 45;  Y[9] = 0;  Z[9] = 14;  C[9] = 1;
	X[10] = 45;  Y[10] = 37;  Z[10] = 14;  C[10] = 1;
	X[11] = 30;  Y[11] = 37;  Z[11] = 14;  C[11] = 1;
	X[12] = 12;  Y[12] = 37;  Z[12] = 45;  C[12] = 1;
	X[13] = 12;  Y[13] = 21;  Z[13] = 45;  C[13] = 1;

}

/***************************************************
* �˺����ֱ�����������ͼ��ͶӰ�任��ͳһ�ñ任�� *
* �������������㹫ʽ��������ֵ����������ʽ���ɵ� *
* �����������Ա任��������ġ�ʵ����ÿ����ͼͶӰ *
* ֻ�ж�������������Ҫ������ã�����һ������������ *
* ����㡣���Ҳ���Ը���������ͬ��ͼ��ͶӰ���ֱ�� *
* ����ͶӰ��Ķ����������ʽ��������ֵ�������п��� *
* �������ѡ��ͬ��ͼͶӰ���ò�ͬ�������ʽ��ֵ�� *
***************************************************/
void   CBaseClass::Calculate(array2d B)
{
	ReadWorkpiece();
	for (int i = 1; i <= 12; ++i)
	{
		XT[i] = 3 * X[i] * B[1][1] + 3 * Y[i] * B[2][1] + 3 * Z[i] * B[3][1] + 3 * C[i] * B[4][1];
		YT[i] = 3 * X[i] * B[1][2] + 3 * Y[i] * B[2][2] + 3 * Z[i] * B[3][2] + 3 * C[i] * B[4][2];
		ZT[i] = 3 * X[i] * B[1][3] + 3 * Y[i] * B[2][3] + 3 * Z[i] * B[3][3] + 3 * C[i] * B[4][3];
	}
}

// �˺��������ͶӰ��������ֵ
void   CBaseClass::MCalculate(array2d B)
{
	ReadWorkpiece();
	for (int i = 1; i <= 12; ++i)
	{

		XT[i] = 3 * (X[i] * B[1][1] + Z[i] * B[2][1] + Y[i] * B[3][1] + C[i] * B[4][1]);
		YT[i] = 3 * (X[i] * B[1][2] + Z[i] * B[2][2] + Y[i] * B[3][2] + C[i] * B[4][2]);
		ZT[i] = 3 * (X[i] * B[1][3] + Z[i] * B[2][3] + Y[i] * B[3][3] + C[i] * B[4][3]);
	}
	// ����������㹫ʽ�ɵ���������������ͶӰ�任���������
}


void CBaseClass::Display()
{
	CFrameWnd* pWnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc = pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd, rr);
	DrawText();

	//DrawViewV(pdc, rr);
	//DrawViewH(pdc, rr);
	//DrawViewW(pdc, rr);
	pWnd->GetActiveView()->ReleaseDC(pdc);
}

//��������ͼ
void CBaseClass::DrawViewV(CDC* pdc, CRect rr)
{
	xx = rr.right / 2;
	yy = rr.bottom / 2;
	//�ڴ���Ӵ���




}

//�����Լ��Ķ��㺯����(x,y)Ϊ��Ҫ���ĵ�
void CBaseClass::moveto(double x, double y, CDC* pdc)
{
	pdc->MoveTo((int)x, (int)y);
}

//�����Լ��Ļ��ߺ������ɵ�ǰ�㻭��(x,y)��
void CBaseClass::lineto(double x, double y, CDC* pdc)
{
	pdc->LineTo((int)x, (int)y);
}
void CBaseClass::setpixel(double x, double y, CDC* pdc)
{
	pdc->SetPixel((int)x, (int)y, RGB(255, 0, 0));
}
//���Ƹ���ͼ
void CBaseClass::DrawViewH()//CDC* pdc, CRect rr)
{
	int I;
	CFrameWnd* pWnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc = pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd, rr);
	xx = rr.right / 3;
	yy = rr.bottom / 2;
	//�ڴ���Ӵ���

	Calculate(Ah);//�����ͶӰ�任
	//DrawText();

	moveto(xx + XT[1], yy - YT[1], pdc);
	for (I = 2; I <= 3; ++I)  // �������ͼ
		lineto(xx + XT[I], yy - YT[I], pdc);

	moveto(xx + XT[5], yy - YT[5], pdc);
	for (I = 6; I <= 12; ++I)
		lineto(xx + XT[I], yy - YT[I], pdc);
	moveto(xx + XT[1], yy - YT[1], pdc);
	lineto(xx + XT[6], yy - YT[6], pdc);
	moveto(xx + XT[7], yy - YT[7], pdc);
	lineto(xx + XT[12], yy - YT[12], pdc);
	moveto(xx + XT[3], yy - YT[3], pdc);
	lineto(xx + XT[10], yy - YT[10], pdc);
	moveto(xx + XT[2], yy - YT[2], pdc);
	lineto(xx + XT[9], yy - YT[9], pdc);
	moveto(xx + XT[12], yy - YT[12], pdc);
	lineto(xx + XT[5], yy - YT[5], pdc);
	moveto(xx + XT[8], yy - YT[8], pdc);
	lineto(xx + XT[11], yy - YT[11], pdc);
	pWnd->GetActiveView()->ReleaseDC(pdc);






}

//���Ʋ���ͼ
void CBaseClass::DrawViewW()//CDC* pdc, CRect rr)
{
	int I;
	CFrameWnd* pWnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc = pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd, rr);
	xx = rr.right / 3;
	yy = rr.bottom / 2;
	//�ڴ���Ӵ���


	Calculate(Aw);//��ͶӰ�任
	//DrawText();

	moveto(xx + XT[1], yy - YT[1], pdc);
	for (I = 2; I <= 3; ++I)  // ��ͼ
		lineto(xx + XT[I], yy - YT[I], pdc);

	moveto(xx + XT[5], yy - YT[5], pdc);
	for (I = 6; I <= 12; ++I)
		lineto(xx + XT[I], yy - YT[I], pdc);
	moveto(xx + XT[1], yy - YT[1], pdc);
	lineto(xx + XT[6], yy - YT[6], pdc);
	moveto(xx + XT[7], yy - YT[7], pdc);
	lineto(xx + XT[12], yy - YT[12], pdc);
	moveto(xx + XT[3], yy - YT[3], pdc);
	lineto(xx + XT[10], yy - YT[10], pdc);
	moveto(xx + XT[2], yy - YT[2], pdc);
	lineto(xx + XT[9], yy - YT[9], pdc);
	moveto(xx + XT[12], yy - YT[12], pdc);
	lineto(xx + XT[5], yy - YT[5], pdc);
	moveto(xx + XT[8], yy - YT[8], pdc);
	lineto(xx + XT[11], yy - YT[11], pdc);
	pWnd->GetActiveView()->ReleaseDC(pdc);


}

//�������ͼ
void CBaseClass::Drawve()
{
	int I;
	CFrameWnd* pWnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc = pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd, rr);
	xx = rr.right / 3;
	yy = rr.bottom * 2 / 4;
	MCalculate(A);//�����ͶӰ�任
	DrawText();

	moveto(xx + XT[1], yy - YT[1], pdc);
	for (I = 2; I <= 3; ++I)  // �������ͼ
		lineto(xx + XT[I], yy - YT[I], pdc);

	moveto(xx + XT[5], yy - YT[5], pdc);
	for (I = 6; I <= 12; ++I)
		lineto(xx + XT[I], yy - YT[I], pdc);
	moveto(xx + XT[1], yy - YT[1], pdc);
	lineto(xx + XT[6], yy - YT[6], pdc);
	moveto(xx + XT[7], yy - YT[7], pdc);
	lineto(xx + XT[12], yy - YT[12], pdc);
	moveto(xx + XT[3], yy - YT[3], pdc);
	lineto(xx + XT[10], yy - YT[10], pdc);
	moveto(xx + XT[2], yy - YT[2], pdc);
	lineto(xx + XT[9], yy - YT[9], pdc);
	moveto(xx + XT[12], yy - YT[12], pdc);
	lineto(xx + XT[5], yy - YT[5], pdc);
	moveto(xx + XT[8], yy - YT[8], pdc);
	lineto(xx + XT[11], yy - YT[11], pdc);
	pWnd->GetActiveView()->ReleaseDC(pdc);
}



//��(5,5)�������ǰ����ͼ�ε�����
void CBaseClass::DrawText()
{
	/*CFrameWnd* pWnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc = pWnd->GetActiveView()->GetDC();
	CGraphics2View* pView = (CGraphics2View*)pWnd->GetActiveView();
	pdc->TextOut(300, 200, pView->m_str);
	pWnd->GetActiveView()->ReleaseDC(pdc);*/
}



