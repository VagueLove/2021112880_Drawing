#include "pch.h"
#include "DataDraw.h"

DataDraw* DataDraw::Get_Draw(int type)
{
	switch (type)
	{
	case 1:
	{
		return new LineDraw();
	}
	break;
	case 2:
	{
		return new CquareDraw();
	}
	break;
	case 3:
	{
		return new CircleDraw();
	}
	break;	
	case 4:
	{
		return new CurveDraw();
	}
	break;	
	case 5:
	{
		return new PolyLineDraw();
	}
	break;
	case 6:
	{
		return new BSplineCurveDraw();
	}
	break;

	default:
		break;
	}
}

void LineDraw::Draw(Node* p, CDC* pDC)
{
	int color = p->now_RGB;
	if (color == 1)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CLine*)p->data)->Draw(pDC);
	}
	else if (color == 2)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CLine*)p->data)->Draw(pDC);
	}
	else if (color == 3)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CLine*)p->data)->Draw(pDC);
	}
	else if(color == 0)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CLine*)p->data)->Draw(pDC);
	}
}
void CquareDraw::Draw(Node* p, CDC* pDC)
{
	int color = p->now_RGB;
	if (color == 1)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CQuare*)p->data)->Draw(pDC);
	}
	else if (color == 2)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CQuare*)p->data)->Draw(pDC);
	}
	else if (color == 3)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CQuare*)p->data)->Draw(pDC);
	}
	else if (color == 0)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CQuare*)p->data)->Draw(pDC);
	}

}
void CircleDraw::Draw(Node* p, CDC* pDC)
{
	int color = p->now_RGB;
	if (color == 1)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CCircle*)p->data)->Draw(pDC);
	}
	else if (color == 2)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CCircle*)p->data)->Draw(pDC);
	}
	else if (color == 3)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CCircle*)p->data)->Draw(pDC);
	}
	else if (color == 0)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((CCircle*)p->data)->Draw(pDC);
	}
}
void CurveDraw::Draw(Node* p, CDC* pDC)
{
	int color = p->now_RGB;
	if (color == 1)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((Curve*)p->data)->ReDraw(pDC);
	}
	else if (color == 2)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((Curve*)p->data)->ReDraw(pDC);
	}
	else if (color == 3)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((Curve*)p->data)->ReDraw(pDC);
	}
	else if (color == 0)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((Curve*)p->data)->ReDraw(pDC);
	}
}
void PolyLineDraw::Draw(Node* p, CDC* pDC)
{
	int color = p->now_RGB;
	if (color == 1)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((PolyLine*)p->data)->ReDraw(pDC);
	}
	else if (color == 2)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((PolyLine*)p->data)->ReDraw(pDC);
	}
	else if (color == 3)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((PolyLine*)p->data)->ReDraw(pDC);
	}
	else if (color == 0)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		((PolyLine*)p->data)->ReDraw(pDC);
	}
}
void BSplineCurveDraw::Draw(Node* p, CDC* pDC)
{
	((BSplineCurve*)p->data)->ReDraw(pDC, p->now_RGB);
}