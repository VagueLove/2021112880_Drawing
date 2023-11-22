#include "pch.h"
#include "CLine.h"
#include <iostream>
#define PI 3.14159

CLine::CLine()
{
	Is_CenPointDraw = false;
}

void CLine::Set_start_point(CPoint p)
{
	Line_start_point = p;
}


void CLine::Set_end_point(CPoint p)
{
	Line_end_point = p;
}

void CLine::CenPointDraw(CDC* pDC)
{
	int x1 = Line_start_point.x;
	int y1 = Line_start_point.y;	//赋初始点
	int x2 = Line_end_point.x, y2 = Line_end_point.y;
	int dy = y1 - y2, dx = x2 - x1;
	int delta_x = (dx >= 0 ? 1 : (dx = -dx, -1));	//若dx>0则步长为1，否则为-1，同时dx变正
	int delta_y = (dy <= 0 ? 1 : (dy = -dy, -1));	//注意这里dy<0,才是画布中y的增长方向
	COLORREF color;
	switch (color_sequence)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:
		break;
	}
	pDC->SetPixelV({ x1,y1 }, color);		//画起始点
	int d, incrE, incrNE;
	if (-dy <= dx)		// 斜率绝对值 <= 1
		//这里-dy即画布中的dy
	{
		d = 2 * dy + dx;	//初始化判断式d
		incrE = 2 * dy;		//取像素E时判别式增量
		incrNE = 2 * (dy + dx);//NE
		while (x1 != x2)
		{
			if (d < 0)
				y1 += delta_y, d += incrNE;
			else
				d += incrE;
			x1 += delta_x;
			pDC->SetPixelV({ x1,y1 }, color);
		}
	}
	else				// 斜率绝对值 > 1
						// x和y情况互换
	{
		d = 2 * dx + dy;
		incrE = 2 * dx;
		incrNE = 2 * (dy + dx);
		while (y1 != y2)
		{
			if (d < 0)	//注意d变化情况
				d += incrE;
			else
				x1 += delta_x, d += incrNE;
			y1 += delta_y;
			pDC->SetPixelV({ x1,y1 }, color);
		}
	}
}
void CLine::Set_CenPointDraw_True()
{
	Is_CenPointDraw = true;
}
void CLine::Set_CenPointDraw_False()
{
	Is_CenPointDraw = false;
}
void CLine::Draw(CDC* pDC)
{
	
	if (Is_CenPointDraw)
	{
		//采用中点画线法绘制直线
		CenPointDraw(pDC);
	}
	else if (IsTransform)
	{
		pDC->MoveTo(POld[0].x,POld[0].y);
		pDC->LineTo(POld[1].x, POld[1].y);
	}
	else
	{
		pDC->MoveTo(Line_start_point);
		pDC->LineTo(Line_end_point);
	}

}

CPoint CLine::GetStart()
{
	return Line_start_point;
}
CPoint CLine::GetEnd()
{
	return Line_end_point;
}

int CLine::Selected(CPoint p)
{

	double a = Line_end_point.y - Line_start_point.y;
	double b = Line_start_point.x - Line_end_point.x;
	double c = Line_end_point.x * Line_start_point.y - Line_start_point.x * Line_end_point.y;

	// 使用点到直线距离公式计算距离
	int d = fabs((a * p.x + b * p.y + c) / sqrt(a * a + b * b));

	if (d < 5 && p.x >= min(Line_start_point.x, Line_end_point.x) && p.x <= max(Line_start_point.x, Line_end_point.x))
		return 1;
	else
		return 0;
}

void CLine::SetColor(int color)
{
	color_sequence = color;
}

void CLine::Translate(double tx, double ty)
{
	POld[0].x = Line_start_point.x;
	POld[0].y = Line_start_point.y;
	POld[1].x = Line_end_point.x;
	POld[1].y = Line_end_point.y;
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
	SaveTransform();
}

void CLine::Scale(double sx, double sy)
{
	centerPoint = Line_start_point + Line_end_point;
	if (POld[1].x * POld[1].x + POld[1].y * POld[1].y - centerPoint.x * centerPoint.x / 4
		- centerPoint.y * centerPoint.y / 4 < 0)
		return;
	POld[0].x = Line_start_point.x;
	POld[0].y = Line_start_point.y;
	POld[1].x = Line_end_point.x;
	POld[1].y = Line_end_point.y;
	Identity();
	T[0][0] = 1 + sx / 2000;
	T[1][1] = 1 + sy / 2000;
	POld[1].x *= T[0][0];
	POld[1].y *= T[1][1];
	IsTransform = true;
}

void CLine::Rotate(CPoint point)
{
	double d = (Line_end_point.x - Line_start_point.x) * (Line_end_point.x - Line_start_point.x) +
		(Line_end_point.y - Line_start_point.y) * (Line_end_point.y - Line_start_point.y);
	double d1 = d - 5, d2 = d + 5;
	if ((point.x - Line_start_point.x) * (point.x - Line_start_point.x) +
			(point.y - Line_start_point.y) * (point.y - Line_start_point.y) < d+5)
	{
		Set_end_point(point);
		IsTransform = true;
	}
}

void CLine::SaveTransform()
{
	IsTransform = false;
	Line_start_point = { POld[0].x, POld[0].y };
	Line_end_point = { POld[1].x, POld[1].y };
}
