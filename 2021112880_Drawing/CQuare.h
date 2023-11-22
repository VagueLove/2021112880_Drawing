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
	void TraDraw(CDC* pDC);//�任���ػ�
	int Selected(CPoint p);
	void CalcMatrix(int&,int&);//�����ĵ���ת�������
	//void RePadding(CDC* pDC);
	//��ȡ���
	CPoint GetStart();
	//��ȡ�յ�
	CPoint GetEnd();
	//std::vector<CPoint> Pixel_Points;

	//ƽ��ʵ��
	void Translate(double tx, double ty);
	//�����任
	void Scale(double sx, double sy);
	//��ת�任
	void Rotate(CPoint);
	//����任���ͼ��
	void SaveTransform();
	//��ʼ���е�
	void InitCenterPoint();
	//��ȡ�е�
	const CPoint& GetCenterPoint();
	//������ת�Ƕ�
	std::pair<double, double>CalcAngle(CPoint point);
	//��ʼ��POld����
	void InitPOld();
	//��POld�����ֵ��ֵ��Vertices����
	void POldToVertices();
	bool IsDraw();//�ж��Ƿ���Draw�ķ�ʽ��ͼ

private:
	//��㣺0���յ㣺2
	CPoint Vertices[4];
	//�е�
	CPoint centerPoint;
	CP2 POld[4];
public:
	bool IsTransform = false;
};
