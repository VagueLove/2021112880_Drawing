#include"pch.h"
#include"CDrawVerLine.h"
CDrawVerLine::CDrawVerLine()
{
    IsPointSet = false;
    IsLineSet = false;
}
void CDrawVerLine::SetPoint(CPoint p)
{
	point = p;
    IsPointSet = true;
}
void CDrawVerLine::SetLine(CLine* line)
{
	this->line = line;
    IsLineSet = true;
}
void CDrawVerLine::SetVerFoot()
{
    double x1, y1, x2, y2, x3, y3;
    double foot_x, foot_y;
    x1 = (line->GetStart()).x;
    y1 = (line->GetStart()).y;
    x2 = (line->GetEnd()).x;
    y2 = (line->GetEnd()).y;
    x3 = point.x;
    y3 = point.y;
    Calc_HangingFeet(x1, y1, x2, y2, x3, y3, foot_x, foot_y);
    HangingFeet.x = foot_x;
    HangingFeet.y = foot_y;
}

double CDrawVerLine::PointMultiply(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

// 计算两个向量的差向量
void CDrawVerLine::Calc_VectorDifference
(double x1, double y1, double x2, double y2, double& diff_x, double& diff_y) 
{
    diff_x = x2 - x1;
    diff_y = y2 - y1;
}

// 计算两个向量的长度
double CDrawVerLine::Calc_VectorLength(double x, double y) {
    return sqrt(x * x + y * y);
}

// 计算垂足的坐标
void CDrawVerLine::Calc_HangingFeet
(double x1, double y1, double x2, double y2, double x3, double y3, double& foot_x, double& foot_y) 
{
    // 计算两个向量的差向量
    double AB_x, AB_y;
    Calc_VectorDifference(x1, y1, x2, y2, AB_x, AB_y);

    double AC_x, AC_y;
    Calc_VectorDifference(x1, y1, x3, y3, AC_x, AC_y);

    // 计算垂足到A点的向量
    double proj = PointMultiply(AC_x, AC_y, AB_x, AB_y) / PointMultiply(AB_x, AB_y, AB_x, AB_y);
    double foot_vector_x = proj * AB_x;
    double foot_vector_y = proj * AB_y;

    // 计算垂足的坐标
    foot_x = x1 + foot_vector_x;
    foot_y = y1 + foot_vector_y;
}

void CDrawVerLine::Draw(CDC* pDC,CSlist &list)
{
    Node* temp = new Node;
    CLine* VerLine = new CLine;
    VerLine->Set_start_point(point);
    pDC->Ellipse(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
    VerLine->Set_end_point(HangingFeet);
    temp->now_type = 1;
    temp->data = VerLine;
    list.InputFront(temp);
    VerLine->Draw(pDC);
}