#pragma once
#include "Graphics.h"
class CLine :public Graphics
{
public:
	CLine();
	//启用中点画线法
	void Set_CenPointDraw_True();
	void Set_CenPointDraw_False();
	//设置起点
	void Set_start_point(CPoint p);
	//设置终点
	void Set_end_point(CPoint p);
	//获取起点
	CPoint GetStart();
	//获取终点
	CPoint GetEnd();
	//绘制直线
	void Draw(CDC* pDC);
	void CenPointDraw(CDC* pDC);
	int Selected(CPoint p);

	void SetColor(int );
private:
	//起点
	CPoint Line_start_point;
	//终点
	CPoint Line_end_point;
	//是否采用中点画线法画线
	bool Is_CenPointDraw;
	int color_sequence = 0;
};

