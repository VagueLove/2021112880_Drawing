#pragma once
//二维几何变换
struct CP2
{
	int x;
	int y;
	int size = 1;
};
class Transform
{
public:
	Transform();
	virtual ~Transform();
	virtual void Identity();
	virtual void Translate(double, double);//平移变换矩阵
	virtual void Scale(double, double);//比例变换矩阵
	virtual void Rotate(double);//旋转变换矩阵
	virtual void MultiMatrix();//矩阵相乘

	//void Scale(double, double, CPoint);//相对于任意点的比例变换矩阵
	//void Rotate(double, CPoint);//相对于任意点的旋转变换矩阵
public:
	double T[3][3];
	int num = 2;
	CP2 POld[2];
};

