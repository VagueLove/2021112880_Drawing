#include "pch.h"
#include "CCircle.h"
CCircle::CCircle()
{
	is_CenPoint = false;
	Is_Bresenham_Draw = false;
}
void CCircle::Set_CenPoint(CPoint p)
{
	is_CenPoint = true;
	m_CenPoint = p;
}

void CCircle::Set_Radius(int Radius)
{
	this->m_Radius = Radius;
}
void CCircle::Get_Radius(CPoint p)
{
	if (is_CenPoint)
	{
		double x = (p.x - m_CenPoint.x) * (p.x - m_CenPoint.x);
		double y = (p.y - m_CenPoint.y) * (p.y - m_CenPoint.y);
		m_Radius = (int)sqrt(x + y);
	}
}
void CCircle::Draw(CDC* pDC)
{
	if (Is_Bresenham_Draw)
	{
		BresenhamDraw(pDC);
	}
	else
	{
		pDC->Ellipse(m_CenPoint.x - m_Radius, m_CenPoint.y - m_Radius, 
					 m_CenPoint.x + m_Radius, m_CenPoint.y + m_Radius);
	}
}
void CCircle::BresenhamDraw(CDC* pDC)
{
	int xc = m_CenPoint.x, yc = m_CenPoint.y;
	int x = 0, y = m_Radius, d1, d2, direction;
	int d = 2 - 2 * m_Radius;
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
	while (y >= 0)
	{
		pDC->SetPixelV(xc + x, yc + y, color); pDC->SetPixelV(xc - x, yc + y, color);
		pDC->SetPixelV(xc - x, yc - y, color); pDC->SetPixelV(xc + x, yc - y, color);
		if (d < 0)
		{
			d1 = 2 * (d + y) - 1;
			if (d1 <= 0)direction = 1;
			else direction = 2;
		}
		else if (d > 0)
		{
			d2 = 2 * (d - x) - 1;
			if (d2 <= 0)direction = 2;
			else direction = 3;
		}
		else direction = 3;
		switch (direction)
		{
		case 1: {++x; d += 2 * x + 1; }break;
		case 2: {++x; --y; d += 2 * (x - y + 1); }break;
		case 3: {--y; d += -2 * y + 1; }break;
		default:break;
		}
	}
}
CPoint CCircle::GetCenter()
{
	return m_CenPoint;
}
int CCircle::GetRadius()
{
	return m_Radius;
}

int CCircle::Selected(CPoint p)
{
	double x = (p.x - m_CenPoint.x) * (p.x - m_CenPoint.x);
	double y = (p.y - m_CenPoint.y) * (p.y - m_CenPoint.y);
	double l = sqrt(x + y);
	if (fabs(l - m_Radius) < 5)
	{
		return 1;
	}
	else
		return 0;
}
void CCircle::SetColor(int color)
{
	color_sequence = color;
}
void CCircle::Set_Bresenham_True()
{
	Is_Bresenham_Draw = true;
}
void CCircle::Set_Bresenham_False()
{
	Is_Bresenham_Draw = false;
}