#include "pch.h"
#include "CQuare.h"
CQuare::CQuare()
{

}
void CQuare::Set_first_point(CPoint p)
{
	Vertices[0] = p;
}
void CQuare::Set_end_point(CPoint p)
{
	Vertices[2] = p;
}
void CQuare::Get_other_point()
{
	Vertices[1].x = Vertices[2].x;
	Vertices[1].y = Vertices[0].y;

	Vertices[3].x = Vertices[0].x;
	Vertices[3].y = Vertices[2].y;
}
void CQuare::Draw(CDC* pDC)
{
	Get_other_point();
	//按逆时针顺序绘制顶点数组（直线段），得到矩形
	int i = 0;
	pDC->MoveTo(Vertices[i]);
	for (; i < 3; ++i)
	{
		pDC->LineTo(Vertices[i + 1]);
	}
	pDC->LineTo(Vertices[0]);
}
void CQuare::ReDraw(CDC* pDC)
{
	//按逆时针顺序绘制顶点数组（直线段），得到矩形
	int i = 0;
	pDC->MoveTo(Vertices[i]);
	for (; i < 3; ++i)
	{
		pDC->LineTo(Vertices[i + 1]);
	}
	pDC->LineTo(Vertices[0]);
}
void CQuare::TraDraw(CDC* pDC)
{
	CPoint Vertices[4];
	Vertices[0] = { POld[0].x,POld[0].y };
	Vertices[2] = { POld[2].x,POld[2].y };
	Vertices[1] = { POld[1].x,POld[1].y };
	Vertices[3] = { POld[3].x,POld[3].y };

	//按逆时针顺序绘制顶点数组（直线段），得到矩形
	int i = 0;
	pDC->MoveTo(Vertices[i]);
	for (; i < 3; ++i)
	{
		pDC->LineTo(Vertices[i + 1]);
	}
	pDC->LineTo(Vertices[0]);
}

CPoint CQuare::GetStart()
{
	return Vertices[0];
}
CPoint CQuare::GetEnd()
{
	return Vertices[2];
}
void CQuare::Translate(double tx, double ty)
{
	InitPOld();
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	POld[0].x += T[2][0];
	POld[0].y += T[2][1];	
	POld[1].x += T[2][0];
	POld[1].y += T[2][1];	
	POld[3].x += T[2][0];
	POld[3].y += T[2][1];
	POld[2].x += T[2][0];
	POld[2].y += T[2][1];
	SaveTransform();
}
void CQuare::Scale(double sx, double sy)
{
	InitPOld();
	centerPoint = Vertices[0] + Vertices[2];
	if (POld[2].x * POld[2].x + POld[2].y * POld[2].y - centerPoint.x * centerPoint.x / 4
		- centerPoint.y * centerPoint.y / 4 < 0)
		return;
	Identity();
	T[0][0] = 1 + sx / 2000;
	T[1][1] = 1 + sy / 2000;
	POld[2].x *= T[0][0];
	POld[2].y *= T[1][1];
	POld[1].x = POld[2].x;
	//POld[1].x += POld[2].x - Vertices[2].x;
	POld[1].y = POld[0].y;	
	POld[3].x = POld[0].x;
	POld[3].y = POld[2].y;
	//POld[3].y += POld[2].y - Vertices[2].y;
	IsTransform = true;
}

void CQuare::Rotate(CPoint point)
{
	InitCenterPoint();
	InitPOld();
	Identity();
	auto deta = CalcAngle(point);
	T[0][0] = deta.second; T[0][1] = deta.first;
	T[1][0] = -deta.first; T[1][1] = deta.second;
	for (auto& i : POld)
	{
		CalcMatrix(i.x,i.y);
	}
	CPoint temp = { (POld[0].x + POld[2].x)/2, (POld[0].y + POld[2].y) / 2 };
	int dx = centerPoint.x - temp.x;
	int dy = centerPoint.y - temp.y;
	POld[0].x += dx;
	POld[0].y += dy;	
	POld[1].x += dx;
	POld[1].y += dy;	
	POld[2].x += dx;
	POld[2].y += dy;	
	POld[3].x += dx;
	POld[3].y += dy;

	IsTransform = true;
}
void CQuare::SaveTransform()
{
	IsTransform = false;
	POldToVertices();
}
void CQuare::InitCenterPoint()
{
	centerPoint = (Vertices[0] + Vertices[2]);
	centerPoint.x /= 2;
	centerPoint.y /= 2;
}
const CPoint& CQuare::GetCenterPoint()
{
	return centerPoint;
}
std::pair<double, double> CQuare::CalcAngle(CPoint point)
{
	// 计算向量
	double deltaX = point.x - centerPoint.x;
	double deltaY = centerPoint.y - point.y;
	// 计算向量长度
	double vectorLength = std::sqrt(deltaX * deltaX + deltaY * deltaY);
	// 计算 sin 和 cos
	return { deltaY / vectorLength, deltaX / vectorLength };
}
void CQuare::InitPOld()
{
	POld[0].x = Vertices[0].x;
	POld[0].y = Vertices[0].y;
	POld[1].x = Vertices[1].x;
	POld[1].y = Vertices[1].y;
	POld[2].x = Vertices[2].x;
	POld[2].y = Vertices[2].y;
	POld[3].x = Vertices[3].x;
	POld[3].y = Vertices[3].y;
}
void CQuare::POldToVertices()
{
	Vertices[0] = { POld[0].x, POld[0].y };
	Vertices[1] = { POld[1].x, POld[1].y };
	Vertices[2] = { POld[2].x, POld[2].y };
	Vertices[3] = { POld[3].x, POld[3].y };
}
bool CQuare::IsDraw()
{
	if (Vertices[0].x == Vertices[3].x)return true;
	else return false;
}
int CQuare::Selected(CPoint p)
{
	unsigned int min_x = INT32_MAX,min_y = INT32_MAX, max_x = 0, max_y = 0;
	for (const auto& i : Vertices)
	{
		min_x = i.x > min_x ? min_x : i.x;
		min_y = i.y > min_y ? min_y : i.y;
		max_x = i.x < max_x ? max_x : i.x;
		max_y = i.y < max_y ? max_y : i.y;
	}
	if (abs(p.x - Vertices[0].x) < 5 && p.y >= min_y &&
		p.y <= max_y)
		return 1;
	if (abs(p.x - Vertices[2].x) < 5 && p.y >= min_y &&
		p.y <= max_y)
		return 1;
	if (abs(p.y - Vertices[0].y) < 5 && p.x >= min_x &&
		p.x <= max_x)
		return 1;
	if (abs(p.y - Vertices[2].y) < 5 && p.x >= min_x &&
		p.x <= max_x)
	if (abs(p.x - Vertices[1].x) < 5 && p.y >= min_y &&
		p.y <= max_y)
		return 1;
	if (abs(p.x - Vertices[3].x) < 5 && p.y >= min_y &&
		p.y <= max_y)
		return 1;
	if (abs(p.y - Vertices[1].y) < 5 && p.x >= min_x &&
		p.x <= max_x)
		return 1;
	if (abs(p.y - Vertices[3].y) < 5 && p.x >= min_x &&
		p.x <= max_x)
		return 1;
	return 0;
}
void CQuare::CalcMatrix(int& x , int& y)
{
	int x1 = x, y1 = y;
	x = T[0][0] * x1 + T[0][1] * y1;
	y = T[1][0] * x1 + T[1][1] * y1;
}
