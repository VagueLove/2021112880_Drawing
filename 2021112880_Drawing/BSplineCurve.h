#pragma once
#include "Graphics.h"
#include <vector>
class BSplineCurve : public Graphics
{
public:
	BSplineCurve();
	~BSplineCurve() = default;
	//���ƺ���
	void Draw(CDC* pDC, CPoint cur, int now_RGB);
	void Draw(CDC* pDC);
	//�ػ溯��
	void ReDraw(CDC* pDC, int n);
	//���ÿ��Ƶ�
	void Set_controlPoints(CPoint point);

	double BaseFunction(int i, int k, double u, const std::vector<double>& knot);
	CPoint BSpline(int n, int k, double t, std::vector<CPoint> control, std::vector<double> knot);
	
	//��ȡ��ǰ���Ƶ�����
	unsigned int GetCount_controlPoints();
	//��ŵõ���B�������ߵĵ�
	std::vector<CPoint> bSplinePoints;
private:
	std::vector<double> knotVectors;//�ڵ�����
	std::vector<CPoint> controlPoints;//���Ƶ�
};

