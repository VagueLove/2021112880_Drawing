#include "pch.h"
#include "CLine.h"

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
		CenPointDraw(pDC);
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