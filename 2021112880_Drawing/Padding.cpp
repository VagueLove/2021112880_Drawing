#include "pch.h"
#include "Padding.h"
Padding::Padding()
{
	CurFilled_Color = RGB(255, 0, 255);
	BefFilled_Color = RGB(255, 255, 255);
	Pixel_Points.clear();
}
void Padding::Set_Seed(CPoint point)
{
	seed = point;
}

void Padding::Simple_Seed_Fill(CDC* pDC)
{
	std::stack<CPoint> st;
	st.push(seed);
	CPoint cur;
	while (!st.empty())
	{
		cur = st.top();
		st.pop();
		if (pDC->GetPixel(cur) == BefFilled_Color)
		{
			//Pixel_Points.push_back(cur);
			pDC->SetPixelV(cur, CurFilled_Color);
			//向左上右下，寻找下一个种子点
			Find_NextSeed_Simple(pDC, st, cur.x - 1, cur.y);
			Find_NextSeed_Simple(pDC, st, cur.x , cur.y - 1);
			Find_NextSeed_Simple(pDC, st, cur.x + 1, cur.y);
			Find_NextSeed_Simple(pDC, st, cur.x, cur.y + 1);
		}
	}
}

void Padding::Scan_Seed_Fill(CDC* pDC)
{
	std::stack<CPoint> st;
	st.push(seed);
	CPoint cur;
	while (!st.empty())
	{
		cur = st.top();
		st.pop();
		if (pDC->GetPixel(cur.x, cur.y) == BefFilled_Color)
		{
			int i, j;
			i = cur.x;
			j = cur.x + 1;
			//向左填充
			while (pDC->GetPixel(i, cur.y) == BefFilled_Color)
			{
				//Pixel_Points.push_back({ i, cur.y });
				pDC->SetPixel({ i, cur.y }, CurFilled_Color);
				--i;
			}
			//向右填充
			while (pDC->GetPixel(j, cur.y) == BefFilled_Color)
			{
				//Pixel_Points.push_back({ i, cur.y });
				pDC->SetPixel({ j, cur.y }, CurFilled_Color);
				++j;
			}
			//向上下方向,寻找新的种子点
			Find_NextSeed_Scan(pDC, st, i + 1, j - 1, cur.y + 1);
			Find_NextSeed_Scan(pDC, st, i + 1, j - 1, cur.y - 1);
		}
	}
}

void Padding::Set_CurFilled_Color(unsigned int r, unsigned int g, unsigned int b)
{
	CurFilled_Color = RGB(r, g, b);
}

void Padding::Set_BefFilled_Color(unsigned int r, unsigned int g, unsigned int b)
{
	BefFilled_Color = RGB(r, g, b);
}

void Padding::Find_NextSeed_Simple(CDC* pDC, std::stack<CPoint>& st, int x, int y)
{
	if (pDC->GetPixel({ x,y }) == BefFilled_Color)
	{
		st.push({ x,y });
	}
}

void Padding::Find_NextSeed_Scan(CDC* pDC, std::stack<CPoint>& st, int left, int right, int y)
{
	for (int i = left; i <= right; ++i)
	{
		if (pDC->GetPixel(i, y) == BefFilled_Color)
		{
			int j = i + 1;
			while (pDC->GetPixel(j, y) == BefFilled_Color)
			{
				j++;
			}
			i = j--;
			st.push({ j, y });
		}
	}
}

const std::vector<CPoint>& Padding::Get_PPoints()
{
	return Pixel_Points;
}
