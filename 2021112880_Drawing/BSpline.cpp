#include "pch.h"
#include "BSpline.h"
#define ROUND(d) int(d+0.5)//四舍五入宏定义
BSpline::BSpline()
{
	//准均匀三次均匀B样条
	knot[0] = 0, knot[1] = 0, knot[2] = 0, knot[3] = 0, 
	knot[4] = 1 / 3.0, knot[5] = 2 / 3.0,
	knot[6] = 1, knot[7] = 1, knot[8] = 1, knot[9] = 1;
	k = 3;
}

void BSpline::DrawBSplineCurve(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);
	double tStep = 0.01;
	for (double t = 0.0; t <= 1.0; t += tStep)
	{
		CPoint p(0.0, 0.0);
		for (int i = 0; i <= n; i++)
		{
			double BValue = BasisFunctionValue(t, i, k);
			p.x += P[i].x * BValue;//B样条曲线定义
			p.y += P[i].y * BValue;
		}
		points.push_back(p);
		if (0.0 == t)
			pDC->MoveTo(ROUND(p.x), ROUND(p.y));
		else
			pDC->LineTo(ROUND(p.x), ROUND(p.y));
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void BSpline::DrawControlPolygon(CDC* pDC)
{
	CPen NewPen(PS_SOLID, 3, RGB(0, 0, 255)), * pOldPen;
	pOldPen = pDC->SelectObject(&NewPen);
	CBrush NewBrush, * pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0, 0, 255));
	pOldBrush = pDC->SelectObject(&NewBrush);
	for (int i = 0; i <= n; i++)
	{
		if (0 == i)
		{
			pDC->MoveTo(ROUND(P[i].x), ROUND(P[i].y));
			pDC->Ellipse(ROUND(P[i].x) - 5, ROUND(P[i].y) - 5, ROUND(P[i].x) + 5, ROUND(P[i].y) + 5);
		}
		else
		{
			pDC->LineTo(ROUND(P[i].x), ROUND(P[i].y));
			pDC->Ellipse(ROUND(P[i].x) - 5, ROUND(P[i].y) - 5, ROUND(P[i].x) + 5, ROUND(P[i].y) + 5);
		}
	}
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

double BSpline::BasisFunctionValue(double t, int i, int k)
{
	double value1, value2, value;
	if (k == 0)
	{
		if (t >= knot[i] && t < knot[i + 1])
			return 1.0;
		else
			return 0.0;
	}
	if (k > 0)
	{
		if (t<knot[i] || t>knot[i + k + 1])
			return 0.0;
		else
		{
			double coffcient1, coffcient2;//凸组合系数1，凸组合系数2
			double denominator = 0.0;//分母
			denominator = knot[i + k] - knot[i];//递推公式第一项分母
			if (denominator == 0.0)//约定0/0
				coffcient1 = 0.0;
			else
				coffcient1 = (t - knot[i]) / denominator;
			denominator = knot[i + k + 1] - knot[i + 1];//递推公式第二项分母
			if (0.0 == denominator)//约定0/0
				coffcient2 = 0.0;
			else
				coffcient2 = (knot[i + k + 1] - t) / denominator;
			value1 = coffcient1 * BasisFunctionValue(t, i, k - 1);//递推公式第一项的值
			value2 = coffcient2 * BasisFunctionValue(t, i + 1, k - 1);//递推公式第二项的值
			value = value1 + value2;//基函数的值
		}
	}
	return value;
}

void BSpline::SetControlPoint(CPoint p)
{
	if (n < 5)
	{
		P[n + 1] = p;
		++n;
	}
}

int BSpline::GetN()
{
	return n;
}
