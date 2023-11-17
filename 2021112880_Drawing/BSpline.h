#pragma once
class BSpline
{
public:
	BSpline();
	~BSpline() = default;
private:
	CPoint P[6];//���Ƶ�
	double knot[10];//�ڵ�����
	int n = -1;//���Ƶ���-1
	int k;//����
public:
	void DrawBSplineCurve(CDC* pDC);//����B��������
	void DrawControlPolygon(CDC* pDC);//���ƿ��Ƶ�
	double BasisFunctionValue(double t, int i, int k);//����B����������
	void SetControlPoint(CPoint p);
	int GetN();
};

