#pragma once
#include "Graphics.h"
#include "Padding.h"
#include "Transform.h"
#include <iostream>
class CQuare : public Graphics, public Transform
{
public:
	CQuare();
	~CQuare() = default;
	void Set_first_point(CPoint p);
	void Get_other_point();
	void Set_end_point(CPoint p);
	
	void Draw(CDC* pDC);
	void ReDraw(CDC* pDC);
	void TraDraw(CDC* pDC);//变换后重绘
	int Selected(CPoint p);
	void CalcMatrix(int&,int&);//计算四点旋转后的坐标
	//void RePadding(CDC* pDC);
	//获取起点
	CPoint GetStart();
	//获取终点
	CPoint GetEnd();
	//std::vector<CPoint> Pixel_Points;

	//平移实现
	void Translate(double tx, double ty);
	//比例变换
	void Scale(double sx, double sy);
	//旋转变换
	void Rotate(CPoint);
	//保存变换后的图形
	void SaveTransform();
	//初始化中点
	void InitCenterPoint();
	//获取中点
	const CPoint& GetCenterPoint();
	//计算旋转角度
	std::pair<double, double>CalcAngle(CPoint point);
	//初始化POld数组
	void InitPOld();
	//将POld数组的值赋值给Vertices数组
	void POldToVertices();
	bool IsDraw();//判断是否用Draw的方式绘图

private:
	//起点：0，终点：2
	CPoint Vertices[4];
	//中点
	CPoint centerPoint;
	CP2 POld[4];
public:
	bool IsTransform = false;
};
