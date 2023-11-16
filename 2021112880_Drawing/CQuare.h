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
	//��ȡ���
	CPoint GetStart();
	//��ȡ�յ�
	CPoint GetEnd();
	//std::vector<CPoint> Pixel_Points;
private:
	//��㣺0���յ㣺2
	CPoint Vertices[4];
};
