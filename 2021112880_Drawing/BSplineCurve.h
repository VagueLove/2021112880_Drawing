#pragma once
#include "Graphics.h"
#include <vector>
class BSplineCurve : public Graphics
{
public:
	BSplineCurve();
	~BSplineCurve() = default;
	//绘制函数
	void Draw(CDC* pDC, CPoint cur, int now_RGB);
	void Draw(CDC* pDC);
	//重绘函数
	void ReDraw(CDC* pDC, int n);
	//设置控制点
	void Set_ControlPoint(CPoint point);

	double Base_Fun(int i, int k, double u, std::vector<double> knot);
	CPoint BSpline(int n, int k, double t, std::vector<CPoint> control, std::vector<double> knot);
	
	//获取当前控制点数量
	unsigned int GetCount_ControlPoint();
	//存放得到的B样条曲线的点
	std::vector<CPoint> bSplinePoint;
private:
	std::vector<double> knotVector;
	std::vector<CPoint> controlPoint;

};

