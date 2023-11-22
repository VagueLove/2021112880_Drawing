#pragma once
#include <vector>
class BSpline
{
public:
	BSpline();
	~BSpline() = default;
private:
	CPoint P[6];//控制点
	double knot[10];//节点数组
	int n = -1;//控制点数-1
	int k;//次数
	std::vector<CPoint> points;//曲线上的点
public:
	void DrawBSplineCurve(CDC* pDC);//绘制B样条曲线
	void DrawControlPolygon(CDC* pDC);//绘制控制点
	double BasisFunctionValue(double t, int i, int k);//计算B样条基函数
	void SetControlPoint(CPoint p);
	int GetN();
};

