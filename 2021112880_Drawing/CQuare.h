#pragma once
#include "Graphics.h"
#include "Padding.h"
class CQuare : public Graphics
{
public:
	CQuare();
	~CQuare() = default;
	void Set_first_point(CPoint p);
	void Get_other_point();
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
	//起点：0，终点：2
	CPoint Vertices[4];
};
