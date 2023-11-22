#pragma once
#include "Graphics.h"
#include <vector>
#include "Transform.h"
class CCircle : public Graphics, public Transform
{
public:
	CCircle();
	//获取圆心
	CPoint GetCenter();
	//获取半径
	int GetRadius();
	//设置半径
	void Set_Radius(int Radius);
	void Set_CenPoint(CPoint p);
	void Get_Radius(CPoint p);

	void Draw(CDC *pDC);
	int Selected(CPoint p);

	void SetColor(int);
	void BresenhamDraw(CDC* pDC);
	//启用Bresenham法
	void Set_Bresenham_True();
	void Set_Bresenham_False();

	//平移实现
	void Translate(double tx, double ty);
	//比例变换
	void Scale(double sx, double sy);
	//保存变换后的图形
	void SaveTransform();
	//std::vector<CPoint> Pixel_Points;
private:
	CPoint m_CenPoint;
	int m_Radius;
	bool is_CenPoint;
	bool Is_Bresenham_Draw;
	int color_sequence = 0;
public:
	bool IsTransform = false;
}; 
 