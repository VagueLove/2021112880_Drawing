#include "pch.h"
#include "Transform.h"
#include <math.h>
#define PI 3.14159

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::Identity()//单位矩阵
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0;
}

void Transform::Translate(double tx, double ty)//平移变换矩阵
{
}

void Transform::Scale(double sx, double sy)//比例变换矩阵
{
}

//void Transform::Scale(double sx, double sy, CPoint p)//相对于任意点的整体比例变换矩阵
//{
//	Translate(-p.x, -p.y);
//	Scale(sx, sy);
//	Translate(p.x, p.y);
//}

void Transform::Rotate(double beta)//旋转变换矩阵
{
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
}

//void Transform::Rotate(double beta, CPoint p)//相对于任意点的旋转变换矩阵
//{
//	Translate(-p.x, -p.y);
//	Rotate(beta);
//	Translate(p.x, p.y);
//}

void Transform::MultiMatrix()//矩阵相乘
{
	CP2* PNew = new CP2[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld[j].x = PNew[j].x * T[0][0] + PNew[j].y * T[1][0] + PNew[j].size * T[2][0];
		POld[j].y = PNew[j].x * T[0][1] + PNew[j].y * T[1][1] + PNew[j].size * T[2][1];
		POld[j].size = PNew[j].x * T[0][2] + PNew[j].y * T[1][2] + PNew[j].size * T[2][2];
	}
	delete[]PNew;
}
