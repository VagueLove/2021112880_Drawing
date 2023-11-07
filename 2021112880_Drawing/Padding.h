#pragma once
#include <vector>
#include <stack>

class Padding
{
public:
	Padding();
	~Padding() = default;
	//设置填充点
	void Set_Seed(CPoint p);
	//简单种子填充法
	void Simple_Seed_Fill(CDC* pDC);
	//扫描线种子填充法
	void Scan_Seed_Fill(CDC* pDC);
	//设置当前填充的颜色
	void Set_CurFilled_Color(unsigned int r, unsigned int g, unsigned int b);
	//设置前一次填充的颜色
	void Set_BefFilled_Color(unsigned int r, unsigned int g, unsigned int b);
	//简单种子填充法寻找下一个种子点
	void Find_NextSeed_Simple(CDC* pDC ,std::stack<CPoint>& st, int x, int y);
	//扫描线种子填充法寻找下一个种子点
	void Find_NextSeed_Scan(CDC* pDC, std::stack<CPoint>& st, int left, int right, int y);
	//获取填充像素数组
	const std::vector<CPoint>& Get_PPoints();
private:
	//种子点
	CPoint seed;
	//当前填充的颜色
	COLORREF CurFilled_Color;
	//上一次填充的颜色
	COLORREF BefFilled_Color;
	//填充的像素点数组
	std::vector<CPoint> Pixel_Points;
};

