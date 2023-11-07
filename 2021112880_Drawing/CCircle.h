#pragma once
#include "Graphics.h"
#include <vector>
class CCircle : public Graphics
{
public:
	CCircle();
	//��ȡԲ��
	CPoint GetCenter();
	//��ȡ�뾶
	int GetRadius();
	//���ð뾶
	void Set_Radius(int Radius);
	void Set_CenPoint(CPoint p);
	void Get_Radius(CPoint p);

	void Draw(CDC *pDC);
	int Selected(CPoint p);

	void SetColor(int);
	void BresenhamDraw(CDC* pDC);
	//����Bresenham��
	void Set_Bresenham_True();
	void Set_Bresenham_False();

	//std::vector<CPoint> Pixel_Points;
private:
	CPoint m_CenPoint;
	int m_Radius;
	bool is_CenPoint;
	bool Is_Bresenham_Draw;
	int color_sequence = 0;
}; 
 