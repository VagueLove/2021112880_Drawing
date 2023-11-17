#include "pch.h"
#include "Bezier.h"
#include <math.h>
#define ROUND(d) int(d+0.5)
void Bezier::ReadPoint(CPoint p)
{
	if(n < 9)
	{
		Pt[n+1] = p;
		++n;
	}
}

void Bezier::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(ROUND(Pt[0].x), ROUND(Pt[0].y));
	double tStep = 0.01;//²½³¤
	for (double t = 0.0; t <= 1.0; t += tStep)
	{
		DeCasteLiau(t);
		pDC->LineTo(ROUND(pt[0][n].x), ROUND(pt[0][n].y));
	}
	pDC->SelectObject(pOldPen);
}

void Bezier::DrawControlPolygon(CDC* pDC)
{
	CPen pen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush NewBrush, * pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0, 0, 255));
	pOldBrush = pDC->SelectObject(&NewBrush);
	for (int i = 0; i < n + 1; ++i)
	{
		if (0 == i)
		{
			pDC->MoveTo(ROUND(Pt[i].x), ROUND(Pt[i].y));
			pDC->Ellipse(ROUND(Pt[i].x - 5), ROUND(Pt[i].y - 5), ROUND(Pt[i].x + 5), ROUND(Pt[i].y + 5));
		}
		else
		{
			pDC->LineTo(ROUND(Pt[i].x), ROUND(Pt[i].y));
			pDC->Ellipse(ROUND(Pt[i].x) - 5, ROUND(Pt[i].y) - 5, ROUND(Pt[i].x) + 5, ROUND(Pt[i].y) + 5);
		}
	}
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldBrush);
}

void Bezier::DeCasteLiau(double t)
{
	for (int k = 0; k <= n; ++k)
	{
		pt[k][0] = Pt[k];
	}
	for (int r = 1; r <= n; ++r)
	{
		for (int i = 0; i <= n - r; ++i)
		{
			pt[i][r].x = (1 - t) * pt[i][r - 1].x + t * pt[i + 1][r - 1].x;
			pt[i][r].y = (1 - t) * pt[i][r - 1].y + t * pt[i + 1][r - 1].y;
		}
	}
}