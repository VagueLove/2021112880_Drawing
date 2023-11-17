#pragma once
class Bezier
{
public:
	Bezier() = default;
	~Bezier() = default;
	//������Ƶ�
	void ReadPoint(CPoint p);
	//��������
	void Draw(CDC* pDC);
	//���ƿ��ƶ����
	void DrawControlPolygon(CDC* pDC);
private:
	//decastljau
	void DeCasteLiau(double t);
public:
	CPoint Pt[10];//���Ƶ�����
	CPoint pt[10][10];//���ƶ�ά����
	int n = -1;//���ߴ���
};

