#pragma once
#include <vector>
#include <stack>

class Padding
{
public:
	Padding();
	~Padding() = default;
	//��������
	void Set_Seed(CPoint p);
	//��������䷨
	void Simple_Seed_Fill(CDC* pDC);
	//ɨ����������䷨
	void Scan_Seed_Fill(CDC* pDC);
	//���õ�ǰ������ɫ
	void Set_CurFilled_Color(unsigned int r, unsigned int g, unsigned int b);
	//����ǰһ��������ɫ
	void Set_BefFilled_Color(unsigned int r, unsigned int g, unsigned int b);
	//��������䷨Ѱ����һ�����ӵ�
	void Find_NextSeed_Simple(CDC* pDC ,std::stack<CPoint>& st, int x, int y);
	//ɨ����������䷨Ѱ����һ�����ӵ�
	void Find_NextSeed_Scan(CDC* pDC, std::stack<CPoint>& st, int left, int right, int y);
	//��ȡ�����������
	const std::vector<CPoint>& Get_PPoints();
private:
	//���ӵ�
	CPoint seed;
	//��ǰ������ɫ
	COLORREF CurFilled_Color;
	//��һ��������ɫ
	COLORREF BefFilled_Color;
	//�������ص�����
	std::vector<CPoint> Pixel_Points;
};

