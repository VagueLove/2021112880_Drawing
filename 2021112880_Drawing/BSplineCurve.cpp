#include "pch.h"
#include "BSplineCurve.h"

BSplineCurve::BSplineCurve()
{
    knotVector.clear();
    controlPoint.clear();
}

void BSplineCurve::Draw(CDC* pDC, CPoint cur, int now_RGB)
{
    COLORREF color;
    switch (now_RGB)
    {
    case 1: color = RGB(255, 0, 0); break;
    case 2: color = RGB(0, 255, 0); break;
    case 3: color = RGB(0, 0, 255); break;
    case 0: color = RGB(0, 0, 0); break;
    default:
        break;
    }
    std::vector<double> knot;
    std::vector<CPoint> control;

    int control_len, control_i = 0;
    control_len = controlPoint.size();
    while (control_i < control_len)
    {
        control.push_back(controlPoint[control_i]);
        control_i++;
    }
    //将当前点作为预设的控制点
    control.push_back(cur);

    int n = control.size();
    int i, K = 4;

    if (n < K || n == 0)
    {
        return;
    }
    // 构造节点
    for (i = 0; i <= K - 1; i++) {
        knot.push_back(0.0);
    }
    for (i = K; i < n; i++) {
        knot.push_back((double)(i - K + 1.0) / (n - K + 2.0));
    }
    for (i = n; i <= n + K; i++) {
        knot.push_back(1.0);
    }
    // 绘制B样条曲线
    bSplinePoint.clear();//将之前算的点全部情空
    double delta_t, t;
    //delta_t为步长，决定了画点的多少，越多图约清晰，越平滑，但是运算成本会增加
    delta_t = (double)(1.0 / (n - 1)) * 0.005;
    for (t = 0; t <= 1; t += delta_t) {
        CPoint p = BSpline(n, K, t, control, knot);
        bSplinePoint.push_back(p);
        pDC->SetPixel(p, color);
    }
}

void BSplineCurve::Draw(CDC* pDC)
{
    for (const auto& i : bSplinePoint)
    {
        pDC->SetPixel(i, RGB(255,255,255));
    }
}

void BSplineCurve::ReDraw(CDC* pDC, int now_RGB)
{
    COLORREF color;
    switch (now_RGB)
    {
    case 1: color = RGB(255, 0, 0); break;
    case 2: color = RGB(0, 255, 0); break;
    case 3: color = RGB(0, 0, 255); break;
    case 0: color = RGB(0, 0, 0); break;
    default:
        break;
    }
    for (const auto& i : bSplinePoint)
    {
        pDC->SetPixel(i, color);
    }
}

void BSplineCurve::Set_ControlPoint(CPoint point)
{
    controlPoint.push_back(point);
}

double BSplineCurve::BaseFunction(int i, int k, double u, const std::vector<double>& knot)
{
    double left = 0.0;
    double right = 0.0;

    if (k == 1) {
        if (knot[i] <= u && u < knot[i + 1]) {
            return 1.0;
        }
        else {
            return 0.0;
        }
    }
    else {
        if (knot[i + k - 1] != knot[i]) {
            left = (u - knot[i]) / (knot[i + k - 1] - knot[i]) * BaseFunction(i, k - 1, u, knot);
        }
        if (knot[i + k] != knot[i + 1]) {
            right = (knot[i + k] - u) / (knot[i + k] - knot[i + 1]) * BaseFunction(i + 1, k - 1, u, knot);
        }
        return left + right;
    }
}


CPoint BSplineCurve::BSpline(int n, int k, double t, std::vector<CPoint> control, std::vector<double> knot)
{
    double x = 0.0, y = 0.0, b = 0.0;
    for (int i = 0; i < n; i++) {
        b = BaseFunction(i, k, t, knot);
        x += control[i].x * b;
        y += control[i].y * b;
    }
	return CPoint((int)x, (int)y);
}

unsigned int BSplineCurve::GetCount_ControlPoint()
{
    return controlPoint.size();
}
