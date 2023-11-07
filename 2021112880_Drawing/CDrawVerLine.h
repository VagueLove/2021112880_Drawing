#pragma once
#include"CLine.h"
#include"CSlist.h"
class CDrawVerLine
{
public:
	CDrawVerLine();
	//获取垂足
	void SetVerFoot();
	//设置过垂线的一点
	void SetPoint(CPoint p);
	//设置要做垂线的直线
	void SetLine(CLine* line);
	//画垂线
	void Draw(CDC* pDC, CSlist &list);
	//计算垂足
	void Calc_HangingFeet(double x1, double y1, double x2, double y2, double x3, double y3, double& foot_x, double& foot_y);
	//计算向量长度
	double Calc_VectorLength(double x, double y);
	//计算两向量差值
	void Calc_VectorDifference(double x1, double y1, double x2, double y2, double& diff_x, double& diff_y);
	//向量点乘
	double PointMultiply(double x1, double y1, double x2, double y2);

	bool IsPointSet;//判断是否已设置过垂线的一点
	bool IsLineSet;//判断是否已选中要做垂线的线
private:
	CPoint point;
	CPoint HangingFeet;
	CLine* line;
};