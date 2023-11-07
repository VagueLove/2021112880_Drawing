#pragma once
#include "Graphics.h"
class Curve : public Graphics
{
public:
	Curve();
	void Set_start_point(CPoint p);
	void Set_end_point(CPoint p);
	void Set_direc_point(CPoint p);
	void ReDraw(CDC* pDC);
	void SetCenterPoint(CPoint);

	void Draw(CDC* pDC);
	int Selected(CPoint p);

	//点一是否以获取
	bool point1set;
	//点二是否以获取
	bool point2set;
	bool flag;
	CPoint Get_start_point();
	CPoint Get_end_point();
	CPoint Get_direc_point();
	CPoint Get_Cent_point();
private:
	void Circent(CPoint a, CPoint b, CPoint c);
	double Radius(CPoint a, CPoint c);
	CPoint Start_point;
	CPoint End_point;
	CPoint Direc_point;
	CPoint Cent_point;
};