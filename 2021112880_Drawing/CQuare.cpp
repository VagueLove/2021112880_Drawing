#include "pch.h"
#include "CQuare.h"
CQuare::CQuare()
{

}
void CQuare::Set_first_point(CPoint p)
{
	Vertices[0] = p;
}
void CQuare::Set_end_point(CPoint p)
{
	Vertices[2] = p;
}
void CQuare::Get_other_point()
{
	Vertices[1].x = Vertices[2].x;
	Vertices[1].y = Vertices[0].y;

	Vertices[3].x = Vertices[0].x;
	Vertices[3].y = Vertices[2].y;
}
void CQuare::Draw(CDC* pDC)
{
	Get_other_point();
	//按逆时针顺序绘制顶点数组（直线段），得到矩形
	int i = 0;
	for (; i < 3; ++i)
	{
		pDC->MoveTo(Vertices[i]);
		pDC->LineTo(Vertices[i + 1]);
	}
	pDC->MoveTo(Vertices[0]);
	pDC->LineTo(Vertices[i]);
}

CPoint CQuare::GetStart()
{
	return Vertices[0];
}
CPoint CQuare::GetEnd()
{
	return Vertices[2];
}
int CQuare::Selected(CPoint p)
{
	if (abs(p.x - Vertices[0].x) < 5 && p.y >= min(Vertices[0].y, Vertices[2].y) &&
		p.y <= max(Vertices[2].y, Vertices[0].y))
		return 1;
	if (abs(p.x - Vertices[2].x) < 5 && p.y >= min(Vertices[0].y, Vertices[2].y) &&
		p.y <= max(Vertices[2].y, Vertices[0].y))
		return 1;
	if (abs(p.y - Vertices[0].y) < 5 && p.x >= min(Vertices[0].x, Vertices[2].x) &&
		p.x <= max(Vertices[2].x, Vertices[0].x))
		return 1;
	if (abs(p.y - Vertices[2].y) < 5 && p.x >= min(Vertices[0].x, Vertices[2].x) &&
		p.x <= max(Vertices[2].x, Vertices[0].x))
		return 1;
	return 0;
}