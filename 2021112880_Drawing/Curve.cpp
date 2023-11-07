#include "pch.h"
#include "Curve.h"

Curve::Curve()
{
	flag = false;
	point1set = false;
	point2set = false;
}
int Curve::Selected(CPoint p)
{
	double r = Radius(Start_point, Cent_point);
	double l = Radius(p, Cent_point);
	double angle = atan2(p.y - Cent_point.y, p.x - Cent_point.x);

	double startAngle = atan2(Start_point.y - Cent_point.y, Start_point.x - Cent_point.x);

	double endAngle = atan2(End_point.y - Cent_point.y, End_point.x - Cent_point.x);

	// 判断点是否在圆弧上
	if (fabs(r - l) < 5 && angle <= startAngle && angle >= endAngle) {
		return 1;
	}
	else {
		return 0;
	}
}

void Curve::Set_start_point(CPoint p)
{
	point1set = true;
	Start_point = p;
}
void Curve::Set_end_point(CPoint p)
{
	point2set = true;
	End_point = p;
}
void Curve::Set_direc_point(CPoint p)
{
	Direc_point = p;
}
void Curve::Draw(CDC* pDC)
{
	Circent(Start_point, End_point, Direc_point);
	double r = Radius(Start_point, Cent_point);
	pDC->Arc(Cent_point.x - r, Cent_point.y - r, Cent_point.x + r, Cent_point.y + r, Start_point.x, Start_point.y, End_point.x, End_point.y);
}
void Curve::ReDraw(CDC* pDC)
{
	double r = Radius(Start_point, Cent_point);
	pDC->Arc(Cent_point.x - r, Cent_point.y - r, Cent_point.x + r, Cent_point.y + r, Start_point.x, Start_point.y, End_point.x, End_point.y);
}
void Curve::Circent(CPoint a, CPoint b, CPoint c)
{
	double x1 = a.x, y1 = a.y;
	double x2 = b.x, y2 = b.y;
	double x3 = c.x, y3 = c.y;

	// 计算中垂线的斜率
	double m1 = -(x2 - x1) / (y2 - y1);
	double m2 = -(x3 - x2) / (y3 - y2);

	// 计算中点坐标
	double mid_x1 = (x1 + x2) / 2;
	double mid_y1 = (y1 + y2) / 2;
	double mid_x2 = (x2 + x3) / 2;
	double mid_y2 = (y2 + y3) / 2;

	// 求解中垂线方程的截距
	double b1 = mid_y1 - m1 * mid_x1;
	double b2 = mid_y2 - m2 * mid_x2;

	// 求解交点
	double center_x = (b2 - b1) / (m1 - m2);
	double center_y = m1 * center_x + b1;

	Cent_point.x = center_x;
	Cent_point.y = center_y;
}
double Curve::Radius(CPoint a, CPoint c)
{
	double r;
	double x = (a.x - c.x) * (a.x - c.x);
	double y = (a.y - c.y) * (a.y - c.y);
	r = sqrt(x + y);
	return r;
}
void Curve::SetCenterPoint(CPoint p) 
{
	Cent_point = p;
}

CPoint Curve::Get_start_point()
{
	return Start_point;
}
CPoint Curve::Get_end_point()
{
	return End_point;
}
CPoint Curve::Get_direc_point()
{
	return Direc_point;
}
CPoint Curve::Get_Cent_point()
{
	return Cent_point;
}