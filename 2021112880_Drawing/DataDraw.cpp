#include "pch.h"
#include "DataDraw.h"

DataDraw* DataDraw::Get_Draw(int type)
{
	switch (type)
	{
	case 1:return new LineDraw(); break;
	case 2:return new CquareDraw(); break;
	case 3:return new CircleDraw(); break;
	case 4:return new CurveDraw(); break;
	case 5:return new PolyLineDraw(); break;
	case 6:return new BSplineCurveDraw(); break;
	case 7:return new BezierDraw(); break;
	case 8:return new BSplineDraw(); break;
	default:break;
	}
}

void LineDraw::Draw(Node* p, CDC* pDC)
{
	COLORREF color;
	switch (p->now_RGB)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:break;
	}
	CPen pen(PS_SOLID, 1, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	((CLine*)p->data)->Draw(pDC);

}
void CquareDraw::Draw(Node* p, CDC* pDC)
{
	COLORREF color;
	switch (p->now_RGB)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:break;
	}
	CPen pen(PS_SOLID, 1, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	((CQuare*)p->data)->TraDraw(pDC);

}
void CircleDraw::Draw(Node* p, CDC* pDC)
{
	COLORREF color;
	switch (p->now_RGB)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:break;
	}
	CPen pen(PS_SOLID, 1, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	((CCircle*)p->data)->Draw(pDC);
}
void CurveDraw::Draw(Node* p, CDC* pDC)
{
	COLORREF color;
	switch (p->now_RGB)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:break;
	}
	CPen pen(PS_SOLID, 1, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	((Curve*)p->data)->ReDraw(pDC);
}
void PolyLineDraw::Draw(Node* p, CDC* pDC)
{
	COLORREF color;
	switch (p->now_RGB)
	{
	case 1:color = RGB(255, 0, 0); break;
	case 2:color = RGB(0, 255, 0); break;
	case 3:color = RGB(0, 0, 255); break;
	case 0:color = RGB(0, 0, 0); break;
	default:break;
	}
	CPen pen(PS_SOLID, 1, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	((PolyLine*)p->data)->ReDraw(pDC);
}
void BSplineCurveDraw::Draw(Node* p, CDC* pDC)
{
	((BSplineCurve*)p->data)->ReDraw(pDC, p->now_RGB);
}

void BezierDraw::Draw(Node* p, CDC* pDC)
{
	((Bezier*)p->data)->Draw(pDC);
	((Bezier*)p->data)->DrawControlPolygon(pDC);
}
void BSplineDraw::Draw(Node* p, CDC* pDC)
{
	((BSpline*)p->data)->DrawBSplineCurve(pDC);
	((BSpline*)p->data)->DrawControlPolygon(pDC);
}

