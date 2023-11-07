#include"pch.h"
#include"CGetIntersection.h"
CGetIntersection::CGetIntersection()
{
	IsSet_Node_Pos_1 = false;
	IsSet_Node_Pos_2 = false;
	Intersection_1.x = -1;
	Intersection_2.x = -1;
}
void CGetIntersection::Set_GraphicsPos_List_1(int pos)
{
	GraphicsPos_List_1 = pos;
	IsSet_Node_Pos_1 = true;
}
void CGetIntersection::Set_GraphicsPos_List_2(int pos)
{
	GraphicsPos_List_2 = pos;
	IsSet_Node_Pos_2 = true;
}
void CGetIntersection::Circle_Circle(CCircle* c1, CCircle* c2)
{
	CPoint C1, C2;
	C1 = c1->GetCenter();
	C2 = c2->GetCenter();
	double x1 = C1.x, y1 = C1.y, x2 = C2.x, y2 = C2.y;
	double r1 = c1->GetRadius(), r2 = c2->GetRadius();

	// 计算两个圆心之间的距离
	double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	// 判断两个圆是否相离或内含，无交点
	if (d > r1 + r2 || d < fabs(r1 - r2)) {
		return;
	}
	// 计算交点的坐标
	double a = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
	double h = sqrt(pow(r1, 2) - pow(a, 2));
	double x3 = x1 + a * (x2 - x1) / d;
	double y3 = y1 + a * (y2 - y1) / d;
	// 如果只有一个交点，则返回该点坐标
	if (d == r1 + r2 || d == fabs(r1 - r2)) {
		Intersection_1.x = x3;
		Intersection_1.y = y3;
		return;
	}
	// 如果有两个交点，则返回两个点的坐标
	double x4 = x3 + h * (y2 - y1) / d;
	double y4 = y3 - h * (x2 - x1) / d;
	double x5 = x3 - h * (y2 - y1) / d;
	double y5 = y3 + h * (x2 - x1) / d;
	Intersection_1.x = x4;
	Intersection_1.y = y4;
	Intersection_2.x = x5;
	Intersection_2.y = y5;
}
void CGetIntersection::Circle_Line(CCircle* c, CLine* L)
{
	double x1 = (L->GetStart()).x;
	double y1 = (L->GetStart()).y;
	double x2 = (L->GetEnd()).x;
	double y2 = (L->GetEnd()).y;
	double cx = (c->GetCenter()).x;
	double cy = (c->GetCenter()).y;
	double r = c->GetRadius();

	// 计算直线的斜率和截距
	double slope = (y2 - y1) / (x2 - x1);
	double intercept = y1 - slope * x1;

	// 计算直线与圆的判别式的系数
	double A = 1 + pow(slope, 2);
	double B = 2 * (slope * intercept - slope * cy - cx);
	double C = pow(cx, 2) + pow(cy, 2) + pow(intercept, 2) - 2 * intercept * cy - pow(r, 2);

	// 计算判别式
	double discriminant = pow(B, 2) - 4 * A * C;

	// 判断是否有交点
	if (discriminant < 0) {
		return;
	}

	// 计算交点的x坐标
	double x3 = (-B + sqrt(discriminant)) / (2 * A);
	double x4 = (-B - sqrt(discriminant)) / (2 * A);

	// 计算交点的y坐标
	double y3 = slope * x3 + intercept;
	double y4 = slope * x4 + intercept;

	//判断交点是否在线段上
	if (x3 >= min(x1, x2) && x3 <= max(x1, x2))
	{
		Intersection_1.x = x3;
		Intersection_1.y = y3;
	}
	if (x4 >= min(x1, x2) && x4 <= max(x1, x2))
	{
		Intersection_2.x = x4;
		Intersection_2.y = y4;
	}
}
void CGetIntersection::Line_Line(CLine* L1, CLine* L2)
{
	double x1 = (L1->GetStart()).x, y1 = (L1->GetStart()).y;
	double x2 = (L1->GetEnd()).x, y2 = (L1->GetEnd()).y;
	double x3 = (L2->GetStart()).x, y3 = (L2->GetStart()).y;
	double x4 = (L2->GetEnd()).x, y4 = (L2->GetEnd()).y;

	// 计算第一条直线的斜率和截距
	double slope1 = (y2 - y1) / (x2 - x1);
	double intercept1 = y1 - slope1 * x1;

	// 计算第二条直线的斜率和截距
	double slope2 = (y4 - y3) / (x4 - x3);
	double intercept2 = y3 - slope2 * x3;

	// 处理平行线的情况
	if (fabs(slope1 - slope2) < 2.22045e-16) {
		return;
	}

	// 处理重合线的情况
	if (fabs(intercept1 - intercept2) < 2.22045e-16 && fabs(slope1 - slope2) < 2.22045e-16) {
		return;
	}

	// 处理垂直线的情况
	if (isinf(slope1) && slope2 == 0) {
		double x = x3;
		double y = slope1 * x + intercept1;
		Intersection_1.x = x;
		Intersection_1.y = y;
		return;
	}

	if (slope1 == 0 && isinf(slope2)) {
		double x = x1;
		double y = slope2 * x + intercept2;
		Intersection_1.x = x;
		Intersection_1.y = y;
		return;
	}

	// 计算交点的x坐标
	double x = (intercept2 - intercept1) / (slope1 - slope2);

	// 计算交点的y坐标
	double y = slope1 * x + intercept1;

	if (x >= min(x1, x2) && x <= max(x1, x2))
	{
		Intersection_1.x = x;
		Intersection_1.y = y;
	}
}
void CGetIntersection::CalcCC(CSlist& list)
{
	Node* c1 = list.GetElement(GraphicsPos_List_1);
	CCircle* C1 = (CCircle*)(c1->data);
	Node* c2 = list.GetElement(GraphicsPos_List_2);
	CCircle* C2 = (CCircle*)(c2->data);
	Circle_Circle(C1, C2);
}
void CGetIntersection::CalcCL(CSlist& list)
{
	Node* c = list.GetElement(GraphicsPos_List_1);
	CCircle* C = (CCircle*)(c->data);
	Node* l = list.GetElement(GraphicsPos_List_2);
	CLine* L = (CLine*)(l->data);
	Circle_Line(C, L);
}
void CGetIntersection::CalcLC(CSlist& list)
{
	Node* c = list.GetElement(GraphicsPos_List_2);
	CCircle* C = (CCircle*)(c->data);
	Node* l = list.GetElement(GraphicsPos_List_1);
	CLine* L = (CLine*)(l->data);
	Circle_Line(C, L);
}
void CGetIntersection::CalcLL(CSlist& list)
{
	Node* l1 = list.GetElement(GraphicsPos_List_1);
	CLine* L1 = (CLine*)(l1->data);
	Node* l2 = list.GetElement(GraphicsPos_List_2);
	CLine* L2 = (CLine*)(l2->data);
	Line_Line(L1, L2);
}