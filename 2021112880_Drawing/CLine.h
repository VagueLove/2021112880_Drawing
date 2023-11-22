#pragma once
#include "Graphics.h"
#include "Transform.h"
class CLine :public Graphics, public Transform
{
public:
	CLine();
	//�����е㻭�߷�
	void Set_CenPointDraw_True();
	void Set_CenPointDraw_False();
	//�������
	void Set_start_point(CPoint p);
	//�����յ�
	void Set_end_point(CPoint p);
	//��ȡ���
	CPoint GetStart();
	//��ȡ�յ�
	CPoint GetEnd();
	//����ֱ��
	void Draw(CDC* pDC);
	void CenPointDraw(CDC* pDC);
	int Selected(CPoint p);
	//ƽ��ʵ��
	void Translate(double, double);
	//�����任
	void Scale(double, double);
	//��ת�任
	void Rotate(CPoint);

	//����任���ͼ��
	void SaveTransform();

	void SetColor(int );
private:
	//���
	CPoint Line_start_point;
	//�յ�
	CPoint Line_end_point;
	//�е�
	CPoint centerPoint;
	//�Ƿ�����е㻭�߷�����
	bool Is_CenPointDraw;
	int color_sequence = 0;
public:
	bool IsTransform = false;
};

