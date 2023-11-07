#pragma once
#include "Graphics.h"
#include "Padding.h"
class CQuare : public Graphics
{
public:
	CQuare();
	void Set_first_point(CPoint p);
	void Get_other_point(CPoint p);
	void Set_end_point(CPoint p);
	
	void Draw(CDC* pDC);
	int Selected(CPoint p);
	//void RePadding(CDC* pDC);
	//获取起点
	CPoint GetStart();
	//获取终点
	CPoint GetEnd();
	//std::vector<CPoint> Pixel_Points;
private:
	POINT square_first_point;
	POINT square_east_point;
	POINT square_south_point;
	POINT square_end_point;
};
