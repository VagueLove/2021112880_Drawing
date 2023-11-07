#pragma once
#include "Graphics.h"
#include <vector>
#define MAX_COUNT 1000
class PolyLine : public Graphics
{
public:
	PolyLine();
	~PolyLine();
	//�ж��Ƿ����
	bool over;
	bool firstset;
	void Get_point(CPoint p);
	void Set_point(CPoint p);
	void ReDraw(CDC* pDC);
	void Set_num(int );
	int Get_num();
	void Is_DrawTriangle();

	//�ж��Ƿ�������
	bool Is_Triangle;
	CPoint pointbox[MAX_COUNT] = { 0 };

	void Draw(CDC* pDC);
	int Selected(CPoint p);
	//std::vector<CPoint> Pixel_Points;
private:
	CPoint now_point;
	CPoint next_point;
	int num;
};