#include "pch.h"
#include "CQuare.h"
CQuare::CQuare()
{

}
void CQuare::Set_first_point(CPoint p)
{
	square_first_point = p;
}
void CQuare::Set_end_point(CPoint p)
{
	square_end_point = p;
}
void CQuare::Get_other_point(CPoint p)
{
	square_east_point.x = square_end_point.x;
	square_east_point.y = square_first_point.y;

	square_south_point.x = square_first_point.x;
	square_south_point.y = square_end_point.y;
}
void CQuare::Draw(CDC* pDC)
{
	pDC->Rectangle(square_first_point.x, square_first_point.y, square_end_point.x, square_end_point.y);
}

CPoint CQuare::GetStart()
{
	return square_first_point;
}
CPoint CQuare::GetEnd()
{
	return square_end_point;
}
int CQuare::Selected(CPoint p)
{
	if (abs(p.x - square_first_point.x) < 5 && p.y >= min(square_first_point.y, square_end_point.y) &&
		p.y <= max(square_end_point.y, square_first_point.y))
		return 1;
	if (abs(p.x - square_end_point.x) < 5 && p.y >= min(square_first_point.y, square_end_point.y) &&
		p.y <= max(square_end_point.y, square_first_point.y))
		return 1;
	if (abs(p.y - square_first_point.y) < 5 && p.x >= min(square_first_point.x, square_end_point.x) &&
		p.x <= max(square_end_point.x, square_first_point.x))
		return 1;
	if (abs(p.y - square_end_point.y) < 5 && p.x >= min(square_first_point.x, square_end_point.x) &&
		p.x <= max(square_end_point.x, square_first_point.x))
		return 1;
	return 0;
}

//void CQuare::RePadding(CDC* pDC)
//{
//	for(const auto& i : Pixel_Points)
//	{
//		pDC->SetPixel(i, RGB(255, 0, 255));
//	}
//}
