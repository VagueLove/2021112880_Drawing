#include "pch.h"
#include "PolyLine.h"

PolyLine::PolyLine()
{
	num = 0;
	over = false;
	firstset = false;
	Is_Triangle = false;
}

PolyLine::~PolyLine()
{

}
void PolyLine::Get_point(CPoint p)
{
	int temp = this->num;
	now_point = pointbox[temp - 1];
	next_point = p;
}
void PolyLine::Set_point(CPoint p)
{
	pointbox[num] = p;
	if (firstset == false)
		firstset = true;
	++num;
}
void PolyLine::Draw(CDC* pDC)
{
	pDC->MoveTo(now_point);
	pDC->LineTo(next_point);
}
void PolyLine::ReDraw(CDC* pDC)
{
	int i, j = num - 2;
	for (i = 0; i <= j; i++)
	{
		now_point = pointbox[i];
		next_point = pointbox[i + 1];
		pDC->MoveTo(now_point);
		pDC->LineTo(next_point);
	}
}
int PolyLine::Get_num()
{
	return num;
}
void PolyLine::Set_num(int num)
{
	this->num = num;
}
void PolyLine::Is_DrawTriangle()
{
	int diff = 5;
	int diff_x = abs(pointbox[0].x - pointbox[3].x);
	int diff_y = abs(pointbox[0].y - pointbox[3].y);
	if (diff_x <= diff && diff_y <= diff)
	{
		pointbox[3].x = pointbox[0].x;
		pointbox[3].y = pointbox[0].y;
		Is_Triangle = true;
	}
}
int PolyLine::Selected(CPoint p)
{
	int d[1000];
	int i, j = num - 2;
	for (i = 0; i < j; i++)
	{
		now_point = pointbox[i];
		next_point = pointbox[i + 1];
		double a = next_point.y - now_point.y;
		double b = now_point.x - next_point.x;
		double c = next_point.x * now_point.y - now_point.x * next_point.y;
		// 使用点到直线距离公式计算距离
		d[i] = fabs((a * p.x + b * p.y + c) / sqrt(a * a + b * b));
	}
	for (i = 0; i < j; i++)
	{
		now_point = pointbox[i];
		next_point = pointbox[i + 1];
		int e = fabs(next_point.x - now_point.x);
		int f = fabs(next_point.y - now_point.y);
		int s1 = fabs(p.x - now_point.x);
		int s2 = fabs(p.y - now_point.y);
		int v1 = fabs(p.x - next_point.x);
		int v2 = fabs(p.y - next_point.y);
		if (d[i] < 5 && e >= s1 && f >= s2 && e >= v1 && f >= v2)
			return 1;
	}
	return 0;
}