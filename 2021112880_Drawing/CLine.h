#pragma once
#include "Graphics.h"
class CLine :public Graphics
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

	void SetColor(int );
private:
	//���
	CPoint Line_start_point;
	//�յ�
	CPoint Line_end_point;
	//�Ƿ�����е㻭�߷�����
	bool Is_CenPointDraw;
	int color_sequence = 0;
};

