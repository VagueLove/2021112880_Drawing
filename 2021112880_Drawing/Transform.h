#pragma once
//��ά���α任
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
	virtual void Translate(double, double);//ƽ�Ʊ任����
	virtual void Scale(double, double);//�����任����
	virtual void Rotate(double);//��ת�任����
	virtual void MultiMatrix();//�������

	//void Scale(double, double, CPoint);//����������ı����任����
	//void Rotate(double, CPoint);//�������������ת�任����
public:
	double T[3][3];
	int num = 2;
	CP2 POld[2];
};

