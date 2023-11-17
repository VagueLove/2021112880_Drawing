#pragma once
class Bezier
{
public:
	Bezier() = default;
	~Bezier() = default;
	//读入控制点
	void ReadPoint(CPoint p);
	//绘制曲线
	void Draw(CDC* pDC);
	//绘制控制多边形
	void DrawControlPolygon(CDC* pDC);
private:
	//decastljau
	void DeCasteLiau(double t);
public:
	CPoint Pt[10];//控制点数组
	CPoint pt[10][10];//递推二维数组
	int n = -1;//曲线次数
};

