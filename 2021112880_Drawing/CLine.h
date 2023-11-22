#pragma once
#include "Graphics.h"
#include "Transform.h"
class CLine :public Graphics, public Transform
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
	//平移实现
	void Translate(double, double);
	//比例变换
	void Scale(double, double);
	//旋转变换
	void Rotate(CPoint);

	//保存变换后的图形
	void SaveTransform();

	void SetColor(int );
private:
	//起点
	CPoint Line_start_point;
	//终点
	CPoint Line_end_point;
	//中点
	CPoint centerPoint;
	//是否采用中点画线法画线
	bool Is_CenPointDraw;
	int color_sequence = 0;
public:
	bool IsTransform = false;
};

