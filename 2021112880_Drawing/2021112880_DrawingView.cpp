
// 2021112880_DrawingView.cpp: CMy2021112880DrawingView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2021112880_Drawing.h"
#endif

#include "2021112880_DrawingDoc.h"
#include "2021112880_DrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#define N_MAX_POINT 10

CSlist m_link_list;
CLine* m_pline;
CQuare* m_psquare;
CCircle* m_pcircle;

Curve* m_pcurve = nullptr;
PolyLine* m_polyline = nullptr;
CDrawVerLine* m_ver_line = NULL;
CGetIntersection* m_intersection = NULL;
Padding* pad = nullptr;
BSplineCurve* m_bspline = nullptr;
Bezier* m_bezier = nullptr;
BSpline* m_bSpline = nullptr;

//鼠标光标
HCURSOR hCursor = LoadCursor(NULL, IDC_PERSON);

// CMy2021112880DrawingView

IMPLEMENT_DYNCREATE(CMy2021112880DrawingView, CView)

BEGIN_MESSAGE_MAP(CMy2021112880DrawingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Line, &CMy2021112880DrawingView::OnLine)
	ON_COMMAND(ID_Circle, &CMy2021112880DrawingView::OnCircle)
	ON_COMMAND(ID_Rectangle, &CMy2021112880DrawingView::OnRectangle)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Blue, &CMy2021112880DrawingView::OnBlue)
	ON_COMMAND(ID_Red, &CMy2021112880DrawingView::OnRed)
	ON_COMMAND(ID_Green, &CMy2021112880DrawingView::OnGreen)
	ON_COMMAND(ID_Select, &CMy2021112880DrawingView::OnSelect)
	ON_COMMAND(ID_Curve, &CMy2021112880DrawingView::OnCurve)
	ON_COMMAND(ID_Poly_Line, &CMy2021112880DrawingView::OnPolyLine)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_Clear, &CMy2021112880DrawingView::OnClear)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DrawVerLine, &CMy2021112880DrawingView::OnDrawVerLine)
	ON_COMMAND(ID_GetCenter, &CMy2021112880DrawingView::OnGetCenter)
	ON_COMMAND(ID_GetIntersection, &CMy2021112880DrawingView::OnGetIntersection)
//	ON_MESSAGE(OnSetMouseCursor, &CMy2021112880DrawingView::OnOnsetmousecursor)
ON_WM_SETCURSOR()
ON_COMMAND(ID_Black, &CMy2021112880DrawingView::OnBlack)
ON_COMMAND(ID_Center_Line, &CMy2021112880DrawingView::OnCenterLine)
ON_COMMAND(ID_Bresen_Circle, &CMy2021112880DrawingView::OnBresenCircle)
ON_COMMAND(ID_Scan_Seed_Fill, &CMy2021112880DrawingView::OnScanSeedFill)
ON_COMMAND(ID_Simple_Seed_Fill, &CMy2021112880DrawingView::OnSimpleSeedFill)
ON_COMMAND(ID_B_Spline_Curve, &CMy2021112880DrawingView::OnBSplineCurve)
ON_COMMAND(ID_Bezier, &CMy2021112880DrawingView::OnBezier)
ON_COMMAND(ID_BSpline_3, &CMy2021112880DrawingView::OnBspline3)
ON_COMMAND(ID_Rotate, &CMy2021112880DrawingView::OnRotate)
ON_COMMAND(ID_Translate, &CMy2021112880DrawingView::OnTranslate)
ON_COMMAND(ID_Scale, &CMy2021112880DrawingView::OnScale)
ON_COMMAND(ID_ClipLine, &CMy2021112880DrawingView::OnClipline)
ON_COMMAND(ID_SelectRect, &CMy2021112880DrawingView::OnSelectrect)
END_MESSAGE_MAP()

/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define XL 100
#define XR 300
#define YT 100
#define YB 250
const UINT N = 8;
CPoint ptset[N];
int Flag = 0;
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
// CMy2021112880DrawingView 构造/析构

CMy2021112880DrawingView::CMy2021112880DrawingView() noexcept
{
	// TODO: 在此处添加构造代码
	type = 0;
	CenPointDraw = 0;
	BresenhamDraw = false;
	start = false;
	what_RGB = 0;
	go = false;
	function = 0;
	IsSelected = false;
	IsOpenSelect = false;
	Padding_type = 0;
	initTransformPoint.x = 0;
	initTransformPoint.y = 0;
}

CMy2021112880DrawingView::~CMy2021112880DrawingView(){}

BOOL CMy2021112880DrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2021112880DrawingView 绘图
void CMy2021112880DrawingView::OnDraw(CDC* pDC)
{
	CMy2021112880DrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
	if(function == 9)
	{
		CPen newpen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* old = pDC->SelectObject(&newpen);
		pDC->Rectangle(CRect(XL, YT, XR, YB));
		ptset[0] = CPoint(120, 150);
		ptset[1] = CPoint(170, 110);
		ptset[2] = CPoint(0, 190);
		ptset[3] = CPoint(350, 150);
		ptset[4] = CPoint(0, 250);
		ptset[5] = CPoint(150, 230);
		ptset[6] = CPoint(200, 50);
		ptset[7] = CPoint(120, 150);
		pDC->TextOutW(0, 20, L"双击鼠标左键，出现要剪切的线段,右键按下完成裁剪");
		pDC->SelectObject(old);
	}
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
	int i, len;
	len = m_link_list.Length();
	if (len)
	{
		for (i = 1; i <= len; i++)
		{
			CDC* pDC = GetDC();
			//避免图形重叠
			pDC->SelectStockObject(NULL_BRUSH);
			Node* paint = m_link_list.GetElement(i);
			DataDraw* ddraw = DataDraw::Get_Draw(paint->now_type);
			if (ddraw)
			{
				ddraw->Draw(paint, pDC);
				delete ddraw;
			}
			ReleaseDC(pDC);
		}
	}
	if (!my_rect_cut.IsRectEmpty())
	{
		CDC* pDC = GetDC();
		// 创建一个笔，用于绘制矩形的边框
		CPen pen(PS_DASH, 1, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 创建一个空刷子，用于绘制矩形的内部
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		// 绘制矩形
		pDC->Rectangle(my_rect_cut);

		// 恢复原来的笔和刷子
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		ReleaseDC(pDC);

	}
}

// CMy2021112880DrawingView 打印
BOOL CMy2021112880DrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2021112880DrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2021112880DrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程 
}

// CMy2021112880DrawingView 诊断
#ifdef _DEBUG
void CMy2021112880DrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2021112880DrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2021112880DrawingDoc* CMy2021112880DrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2021112880DrawingDoc)));
	return (CMy2021112880DrawingDoc*)m_pDocument;
}
#endif //_DEBUG

// CMy2021112880DrawingView 消息处理程序
void CMy2021112880DrawingView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
	function = 0;
	if(m_pline)
		m_pline->Set_CenPointDraw_False();
}

void CMy2021112880DrawingView::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	type = 2;
	function = 0;

}

void CMy2021112880DrawingView::OnCircle()
{
	// TODO: 在此添加命令处理程序代码
	type = 3;
	function = 0;
	if (m_pcircle)
		m_pcircle->Set_Bresenham_False();

}

void CMy2021112880DrawingView::OnCurve()
{
	// TODO: 在此添加命令处理程序代码
	type = 4;
	function = 0;

}

void CMy2021112880DrawingView::OnPolyLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 5;
	function = 0;

}


void CMy2021112880DrawingView::OnSelect()
{
	// TODO: 在此添加命令处理程序代码
	IsOpenSelect = true;
}

void CMy2021112880DrawingView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/){}

void CMy2021112880DrawingView::LButtonDown_Set_RGB()
{
	switch (what_RGB)
	{
	case 1:what_RGB = 1;break;
	case 2:what_RGB = 2;break;
	case 3:what_RGB = 3;break;
	case 0:what_RGB = 0;break;
	}
}
void CMy2021112880DrawingView::LButtonDown_Set_Type(CPoint point)
{
	switch (type)
	{
	case 1:
	{
		//TODO:将直线的点存入待裁剪数组

		m_pline = new CLine;
		if(function != 6 && function != 7 && function != 8)
			m_pline->Set_start_point(point);
		if(CenPointDraw == 1)m_pline->Set_CenPointDraw_True();

	}break;

	case 2:
	{
		m_psquare = new CQuare;
		if (function != 6 && function != 7 && function != 8)
			m_psquare->Set_first_point(point);
	}break;

	case 3:
	{
		m_pcircle = new CCircle;
		if (function != 6 && function != 7 && function != 8)
			m_pcircle->Set_CenPoint(point);
		if (BresenhamDraw)
			m_pcircle->Set_Bresenham_True();
	}break;

	case 4:
	{
		if (m_pcurve == NULL)
			m_pcurve = new Curve;
	}break;

	case 5:
	{
		if (m_polyline == nullptr)
		{
			m_polyline = new PolyLine;
		}
		//设置第一个点
		if (!m_polyline->firstset)
			m_polyline->Set_point(point);
		
	}break;
	case 6:
	{
		//通过左键按下控制点
		if(m_bspline->GetCount_controlPoints() < 3)
		{
			Draw_Point(point);
			m_bspline->Set_controlPoints(point);
		}
	}break;
	case 7://Bezier曲线
	{
		Draw_Point(point);
		m_bezier->ReadPoint(point);
	}break;
	case 8://B样条曲线——3阶
	{
		if(m_bSpline->GetN() < 5)
		{
			Draw_Point(point);
			m_bSpline->SetControlPoint(point);
		}
		
	}break;
	case 9:
	{
		if (!my_rect_cut.PtInRect(point))
		{
			do_cut = true;
			my_cut_clear = false;
			base_point = point;
			my_rect_cut.SetRect(point.x, point.y, point.x, point.y);
		}
		else if (my_rect_cut.PtInRect(point))
		{
			if (part_large_down_count == 0)
			{
				my_large_redraw();
				part_large_down_count++;
			}
			else if (part_large_down_count > 0)
			{
				// 清空m_rectSelection
				my_rect_cut.SetRectEmpty();
				my_cut_clear = true;
				part_large_down_count = 0;
				/*HCURSOR hCur = LoadCursor(NULL, IDC_WAIT);
				::SetCursor(hCur);*/
				Invalidate();
				//my_own_redraw();
			}
		}
	}break;
	default:
		break;
	}
}
void CMy2021112880DrawingView::LButtonDown_Set_Function(CPoint point)
{
	switch (function)
	{
	case 1:
	{
		if (m_ver_line == NULL)
		{
			m_ver_line = new CDrawVerLine;
			//设置过垂线的点
			if (!m_ver_line->IsPointSet)
				m_ver_line->SetPoint(point);
		}
		else
		{
			//设置直线
			if (!m_ver_line->IsLineSet && m_ver_line->IsPointSet)
			{
				int i, len = m_link_list.Length();
				if (len)
				{
					for (i = 1; i <= len; i++)
					{
						Node* selectLine;
						selectLine = m_link_list.GetElement(i);
						if (selectLine->now_type == 1)
						{
							if (((CLine*)selectLine->data)->Selected(point))
							{
								m_ver_line->SetLine((CLine*)selectLine->data);
								break;
							}
						}
					}
				}
			}
		}
	}break;
	case 2:
	{
		if (m_intersection == NULL)
		{
			m_intersection = new CGetIntersection;
			int i, len = m_link_list.Length();
			if (len)
			{
				for (i = 1; i <= len; i++)
				{
					Node* selectObj = m_link_list.GetElement(i);
					if (selectObj->now_type == 1)
					{
						if (((CLine*)selectObj->data)->Selected(point))
						{
							m_intersection->Set_GraphicsPos_List_1(i);
							m_intersection->type_1 = 1;
							break;
						}
					}
					if (selectObj->now_type == 3)
					{
						if (((CCircle*)selectObj->data)->Selected(point))
						{
							m_intersection->Set_GraphicsPos_List_1(i);
							m_intersection->type_1 = 3;
							break;
						}
					}
				}
			}
		}
		else
		{
			int i, len = m_link_list.Length();
			if (len)
			{
				for (i = 1; i <= len; i++)
				{
					Node* selectObj = m_link_list.GetElement(i);
					if (selectObj->now_type == 1)
					{
						if (((CLine*)selectObj->data)->Selected(point))
						{
							m_intersection->Set_GraphicsPos_List_2(i);
							m_intersection->type_2 = 1;
							break;
						}
					}
					if (selectObj->now_type == 3)
					{
						if (((CCircle*)selectObj->data)->Selected(point))
						{
							m_intersection->Set_GraphicsPos_List_2(i);
							m_intersection->type_2 = 3;
							break;
						}
					}
				}
			}
		}
	}break;
	case 3:
	{
		int i, len = m_link_list.Length();
		if (len)
		{
			CDC* pDC = GetDC();
			for (i = 1; i <= len; i++)
			{
				Node* PoC = m_link_list.GetElement(i);
				if (PoC->now_type == 3)
				{
					CPoint Cen = ((CCircle*)PoC->data)->GetCenter();
					CPen pen;
					if (((CCircle*)PoC->data)->Selected(point))
					{
						pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					}
					else
					{
						pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
					}
					pDC->SelectObject(&pen);
					pDC->Ellipse(Cen.x - 2, Cen.y - 2, Cen.x + 2, Cen.y + 2);
				}
			}
			ReleaseDC(pDC);
		}
	}break;
	//图形变换--平移
	case 6:
	{
		//获取鼠标按下的坐标作为初始坐标
		initTransformPoint = point;
	}break;
	case 7:
	{
		//获取鼠标按下的坐标作为初始坐标
		initTransformPoint = point;
	}break;
	case 8:
	{
		//获取鼠标按下的坐标作为初始坐标
		initTransformPoint = point;
	}break;
	default:break;
	}
}

void CMy2021112880DrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	LButtonDown_Set_RGB();
	LButtonDown_Set_Type(point);
	LButtonDown_Set_Function(point);
	start = true;
	CView::OnLButtonDown(nFlags, point);
}

void CMy2021112880DrawingView::LButtonUp_Set_RGB_Type(CPoint point)
{
	Node* newPoint = new Node;
	switch (what_RGB)
	{
	case 1:newPoint->now_RGB = 1;break;
	case 2:newPoint->now_RGB = 2;break;
	case 3:newPoint->now_RGB = 3;break;
	case 0:newPoint->now_RGB = 0;break;
	}
	switch (type)
	{
	case 1:
	{
		newPoint->now_type = 1;
		newPoint->data = m_pline;
		m_link_list.InputFront(newPoint);
	}
	break;
	case 2:
	{
		newPoint->now_type = 2;
		newPoint->data = m_psquare;
		m_link_list.InputFront(newPoint);
	}
	break;
	case 3:
	{
		newPoint->now_type = 3;
		newPoint->data = m_pcircle;
		m_link_list.InputFront(newPoint);
	}
	break;
	case 4:
		break;
	case 5:
	{
		if (m_polyline)
		{
			m_polyline->Set_point(point);
			if (!m_polyline->Is_Triangle && m_polyline->Get_num() == 4)
			{
				m_polyline->Is_DrawTriangle();
				if (m_polyline->Is_Triangle)
				{
					m_polyline->over = true;
					Node* newPoint = new Node;
					newPoint->now_type = 5;
					newPoint->now_RGB = what_RGB;
					newPoint->data = m_polyline;
					m_link_list.InputFront(newPoint);
					m_polyline = NULL;
				}
			}
		}
	}
	break;
	case 9:
	{
		if (do_cut)
		{
			if (my_rect_cut.bottom - my_rect_cut.top == 0)
			{
				// 清空my_rect_select
				my_rect_cut.SetRectEmpty();
				my_cut_clear = true;
				my_own_redraw();
			}
			do_cut = false;
		}
	}break;
	default:break;
	}
}
void CMy2021112880DrawingView::LButtonUp_Set_Function()
{
	switch (function)
	{
	case 1:
	{
		CDC* pDC = GetDC();
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		pDC->SelectObject(&pen);
		if (m_ver_line->IsLineSet && m_ver_line->IsPointSet)
		{
			m_ver_line->SetVerFoot();
			m_ver_line->Draw(pDC, m_link_list);
			m_ver_line = NULL;
		}
		ReleaseDC(pDC);
	}break;
	case 2:
	{
		if (m_intersection->IsSet_Node_Pos_1 && m_intersection->IsSet_Node_Pos_2)
		{
			CString str;
			if (m_intersection->type_1 == 1 && m_intersection->type_2 == 1)
			{
				m_intersection->CalcLL(m_link_list);
				if ((m_intersection->Intersection_1).x >= 0)
				{
					str.Format(_T("两直线交点为(%d,%d))"), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y);
				}
				else
				{
					str.Format(_T("无交点"));
				}
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			}
			else if (m_intersection->type_1 == 3 && m_intersection->type_2 == 3)
			{
				m_intersection->CalcCC(m_link_list);
				if ((m_intersection->Intersection_1).x >= 0 && (m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("两圆的交点为(%d,%d) (%d,%d)"), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y, (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else if ((m_intersection->Intersection_1).x >= 0)
				{
					str.Format(_T("两圆的交点为(%d,%d) "), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y);
				}
				else if ((m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("两圆的交点为(%d,%d) "), (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else
				{
					str.Format(_T("无交点"));
				}
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			}
			else if (m_intersection->type_1 == 3 && m_intersection->type_2 == 1)
			{
				m_intersection->CalcCL(m_link_list);
				if ((m_intersection->Intersection_1).x >= 0 && (m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) (%d,%d)"), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y, (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else if ((m_intersection->Intersection_1).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) "), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y);
				}
				else if ((m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) "), (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else
				{
					str.Format(_T("无交点"));
				}
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			}
			else if (m_intersection->type_1 == 1 && m_intersection->type_2 == 3)
			{
				m_intersection->CalcLC(m_link_list);
				if ((m_intersection->Intersection_1).x >= 0 && (m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) (%d,%d)"), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y, (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else if ((m_intersection->Intersection_1).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) "), (m_intersection->Intersection_1).x, (m_intersection->Intersection_1).y);
				}
				else if ((m_intersection->Intersection_2).x >= 0)
				{
					str.Format(_T("直线与圆的交点为(%d,%d) "), (m_intersection->Intersection_2).x, (m_intersection->Intersection_2).y);
				}
				else
				{
					str.Format(_T("无交点"));
				}
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);

			}

			m_intersection = NULL;
		}
	}break;

	case 3:
	{}break;
	case 4:
	{

	}break;
	case 5:
	{

	}break;	
	case 6:
	{
		initTransformPoint.x = 0;
		initTransformPoint.y = 0;

	}break;
	case 7:
	{
		initTransformPoint.x = 0;
		initTransformPoint.y = 0;
		if (type == 1)m_pline->SaveTransform();
		else if (type == 2)m_psquare->SaveTransform();
		else if (type == 3)m_pcircle->SaveTransform();
	}break;	
	case 8:
	{
		initTransformPoint.x = 0;
		initTransformPoint.y = 0;
		if (type == 1)m_pline->SaveTransform();
		else if (type == 2)m_psquare->SaveTransform();
	}break;
	default:
		break;
	}
}
void CMy2021112880DrawingView::LButtionDbCLK_For_Type(CPoint point)
{
	switch (type)
	{
	case 4:
	{
		m_pcurve->flag = false;
		//双击设置起点和终点
		if (!m_pcurve->point1set)
		{
			Draw_Point(point);
			m_pcurve->Set_start_point(point);
		}
		else if (!m_pcurve->point2set)
		{
			Draw_Point(point);
			m_pcurve->Set_end_point(point);
		}
	}break;
	}
}

//辅助绘制点，方便显示
void CMy2021112880DrawingView::Draw_Point(CPoint point)
{
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	pDC->Ellipse(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
	ReleaseDC(pDC);
}

void CMy2021112880DrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (function != 6 && function != 7 && function != 8)
		LButtonUp_Set_RGB_Type(point);
	LButtonUp_Set_Function();

	go = false;
	start = false;
	CView::OnLButtonUp(nFlags, point);
}

void CMy2021112880DrawingView::MouseMove_Draw(CPoint point, int color)
{
	CDC* pDC = GetDC();
	pDC->SelectStockObject(NULL_BRUSH);
	CPen pen;
	switch (color)
	{
	case 1:pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));break;	
	case 2:pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));break;
	case 3:pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));break;
	case 0:pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));break;
	default:break;
	}
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	switch (type)
	{
	case 1:
	{
			m_pline->SetColor(color);
			if (go)
			{
				pDC->SetROP2(R2_NOTXORPEN);
				m_pline->Draw(pDC);
			}
			else
			{
				go = true;
			}
			if(!initTransformPoint.x && !initTransformPoint.y)
			{
				m_pline->Set_end_point(point);
				m_pline->Draw(pDC);
			}
			else
			{
				if (m_pline->GetStart().x == 0)
					break;
				switch (function)
				{
				case 6:
				{
					double sx = point.x - initTransformPoint.x;
					double sy = point.y - initTransformPoint.y;
					initTransformPoint = point;
					m_pline->Translate(sx, sy);
					m_pline->Draw(pDC);
				}break;				
				case 7:
				{
					double sx = sqrt((point.x - initTransformPoint.x) * (point.x - initTransformPoint.x)
								+ (point.y - initTransformPoint.y) * (point.y - initTransformPoint.y));
					if (initTransformPoint.x * initTransformPoint.x + initTransformPoint.y * initTransformPoint.y
						- point.x * point.x - point.y * point.y > 0)
					{
						sx = -sx;
					}
					m_pline->Scale(sx, sx);
					m_pline->Draw(pDC);
				}break;
				case 8:
				{
					if (go)
					{
						pDC->SetROP2(R2_NOTXORPEN);
						m_pline->Draw(pDC);
					}
					else
					{
						go = true;
					}
					m_pline->Rotate(point);
					m_pline->Draw(pDC);

				}break;
				default:
					break;
				}
			}
	}break;	
	case 2:
	{
		if (go)
		{
			pDC->SetROP2(R2_NOTXORPEN);
			if (!m_psquare->IsTransform && m_psquare->IsDraw())
			m_psquare->Draw(pDC);
			else
			m_psquare->TraDraw(pDC);
		}
		else
		{
			go = true;
		}
		if (!initTransformPoint.x && !initTransformPoint.y)
		{
			m_psquare->Set_end_point(point);
			m_psquare->Draw(pDC);
		}
		else
		{
			if (m_psquare->GetStart().x == 0)
				break;
			switch (function)
			{
			case 6:
			{
				double sx = point.x - initTransformPoint.x;
				double sy = point.y - initTransformPoint.y;
				initTransformPoint = point;
				m_psquare->Translate(sx, sy);
				m_psquare->TraDraw(pDC);
			}break;
			case 7:
			{
				double sx = sqrt((point.x - initTransformPoint.x) * (point.x - initTransformPoint.x)
					+ (point.y - initTransformPoint.y) * (point.y - initTransformPoint.y));
				if (initTransformPoint.x * initTransformPoint.x + initTransformPoint.y * initTransformPoint.y
					- point.x * point.x - point.y * point.y > 0)
				{
					sx = -sx;
				}
				m_psquare->Scale(sx, sx);
				m_psquare->TraDraw(pDC);
			}break;
			case 8:
			{
				m_psquare->Rotate(point);
				m_psquare->TraDraw(pDC);
			}break;
			default:
				break;
			}
		}
	}break;	
	case 3:
	{
		m_pcircle->SetColor(color);
		if (go)
		{
			pDC->SetROP2(R2_NOTXORPEN);
			m_pcircle->Draw(pDC);
		}
		else
		{
			go = true;
		}
		if (!initTransformPoint.x && !initTransformPoint.y)
		{
			m_pcircle->Get_Radius(point);
			m_pcircle->Draw(pDC);
		}
		else
		{
			if (m_pcircle->GetCenter().x == 0)
				break;
			switch (function)
			{
			case 6:
			{
				double sx = point.x - initTransformPoint.x;
				double sy = point.y - initTransformPoint.y;
				initTransformPoint = point;
				m_pcircle->Translate(sx, sy);
				m_pcircle->Draw(pDC);
			}break;
			case 7:
			{
				m_pcircle->Get_Radius(point);
				m_pcircle->Draw(pDC);
			}break;
			case 8:
			{
			}break;
			default:
				break;
			}
		}
	}break;	
	case 4:
	{
		if (m_pcurve->point2set)
		{
			if (go)
			{
				pDC->SetROP2(R2_NOTXORPEN);
				m_pcurve->Draw(pDC);
			}
			else
			{
				go = true;
			}
			m_pcurve->Set_direc_point(point);
			m_pcurve->Draw(pDC);
		}
	}break;	
	case 5:
	{
		if (!m_polyline->over)
		{
			if (go)
			{
				pDC->SetROP2(R2_NOTXORPEN);
				m_polyline->Draw(pDC);
			}
			else
			{
				go = true;
			}
			m_polyline->Get_point(point);
			m_polyline->Draw(pDC);
		}
	}break;
	case 6:
	{
		if (go)
		{
			m_bspline->Draw(pDC);
		}
		else
		{
			go = true;
		}
		m_bspline->Draw(pDC, point, what_RGB);
	}break;
	case 9:
	{
		if (do_cut)
		{
			my_cut_clear = false;
			// 使用鼠标的当前位置更新my_rect_cut的边
			if (point.x >= base_point.x) my_rect_cut.right = point.x;
			else my_rect_cut.left = point.x;
			if (point.y >= base_point.y) my_rect_cut.bottom = point.y;
			else my_rect_cut.top = point.y;
			//my_own_redraw();
			Invalidate();
		}
	}break;
	default:
		break;
	}
	if (type != 9 && !my_cut_clear)
	{
		// 清空my_rect_cut
		my_rect_cut.SetRectEmpty();
		my_cut_clear = true;
		my_own_redraw();
	}
	ReleaseDC(pDC);
}

void CMy2021112880DrawingView::my_large_redraw()
{
	CRect rect;
	GetClientRect(&rect);
	double s1 = rect.Width() / (double)my_rect_cut.Width();
	double s2 = rect.Height() / (double)my_rect_cut.Height();
	int  zoomWidth = s1 > s2 ? my_rect_cut.Width() * s2 : my_rect_cut.Width() * s1;
	int zoomHeight = s1 > s2 ? my_rect_cut.Height() * s2 : my_rect_cut.Height() * s1;

	int lx = s1 > s2 ? (rect.Width() - zoomWidth) / 2 : 0;
	int ty = s1 > s2 ? 0 : (rect.Height() - zoomHeight) / 2;
	// 创建一个用于放大显示的内存 DC
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	// 创建一个与放大显示区域大小相同的内存位图
	CBitmap zoomBitmap;
	zoomBitmap.CreateCompatibleBitmap(GetDC(), rect.Width(), rect.Height());
	memDC.SelectObject(&zoomBitmap);
	memDC.FillSolidRect(rect, 0xffffff); // 按原来背景填充客户区，不然会是黑色
	// 将需要放大显示的区域拷贝到内存 DC 中，并按比例拉伸
	memDC.StretchBlt(lx, ty, zoomWidth, zoomHeight, GetDC(), my_rect_cut.left, my_rect_cut.top,
		my_rect_cut.Width(), my_rect_cut.Height(), SRCCOPY);

	// 将放大后的图像绘制到整个窗口区域
	CDC* pDC = GetDC();
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	// 释放资源
	ReleaseDC(pDC);
	memDC.DeleteDC();
	zoomBitmap.DeleteObject();
	my_rect_cut = rect;
}

void CMy2021112880DrawingView::my_own_redraw()
{
	int i, len;
	len = m_link_list.Length();
	if (len)
	{
		for (i = 1; i <= len; i++)
		{
			CDC* pDC = GetDC();
			//避免图形重叠
			pDC->SelectStockObject(NULL_BRUSH);
			Node* paint = m_link_list.GetElement(i);
			DataDraw* ddraw = DataDraw::Get_Draw(paint->now_type);
			if (ddraw)
			{
				ddraw->Draw(paint, pDC);
				delete ddraw;
			}
			ReleaseDC(pDC);
		}
	}
	if (!my_rect_cut.IsRectEmpty())
	{
		CDC* pDC = GetDC();
		// 创建一个笔，用于绘制矩形的边框
		CPen pen(PS_DASH, 1, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 创建一个空刷子，用于绘制矩形的内部
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		// 绘制矩形
		pDC->Rectangle(my_rect_cut);

		// 恢复原来的笔和刷子
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		ReleaseDC(pDC);

	}
}

void CMy2021112880DrawingView::MouseMove_IsSelect(CPoint point)
{
	int i, len;
	len = m_link_list.Length();
	if (len)
	{
		for (i = 1; i <= len; i++)
		{
			Node* select;
			select = m_link_list.GetElement(i);
			if (select->now_type == 1)
			{
				if (((CLine*)select->data)->Selected(point))
				{
					type = 1;
					IsSelected = true;
					if (function)m_pline = ((CLine*)select->data);
					break;
				}
				else
					IsSelected = false;
			}
			else if (select->now_type == 2)
			{
				if (((CQuare*)select->data)->Selected(point) && IsOpenSelect)
				{
					type = 2;
					IsSelected = true;
					if(function)m_psquare = ((CQuare*)select->data);
					Padding_type = 2;
					break;
				}
				else
					IsSelected = false;
			}
			else if (select->now_type == 3)
			{
				if (((CCircle*)select->data)->Selected(point) && IsOpenSelect)
				{
					type = 3;
					IsSelected = true;
					if (function)m_pcircle = ((CCircle*)select->data);
					Padding_type = 3;
					break;
				}
				else
					IsSelected = false;
			}
			else if (select->now_type == 4)
			{
				if (((Curve*)select->data)->Selected(point) && IsOpenSelect)
				{
					IsSelected = true;
					break;
				}
				else
					IsSelected = false;
			}
			else if (select->now_type == 5)
			{
				if (((PolyLine*)select->data)->Selected(point) && IsOpenSelect)
				{
					IsSelected = true;
					Padding_type = 5;
					break;
				}
				else
					IsSelected = false;
			}
		}
	}

}

void CMy2021112880DrawingView::MouseMove_Draw_Basic_Graphics(CPoint point)
{
	if (start == true)
	{
		//根据不同颜色，绘制相应的图形
		switch (what_RGB)
		{
		case 1:MouseMove_Draw(point,what_RGB);break;
		case 2: MouseMove_Draw(point, what_RGB);break;
		case 3: MouseMove_Draw(point, what_RGB);break;
		case 0: MouseMove_Draw(point, what_RGB);break;
		default:break;
		}
	}
}

void CMy2021112880DrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	//实时在屏幕上打印鼠标坐标
	CString str;
	str.Format(_T("(%d,%d) "), point.x, point.y);
	CDC* pDC = GetDC();
	pDC->TextOutW(0, 0, str);
	MouseMove_Draw_Basic_Graphics(point);
	if(IsOpenSelect)
		MouseMove_IsSelect(point);

	CView::OnMouseMove(nFlags, point);
}


void CMy2021112880DrawingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LButtionDbCLK_For_Type(point);
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
	{
		CDC* pDC = GetDC();
		CPen newpen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* old = pDC->SelectObject(&newpen);
		Flag = 1;
		for (int i = 0; i < N; i++) 
		{
			pDC->MoveTo(ptset[i]);
			pDC->LineTo(ptset[i + 1]);
			i++;
		}
	}
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
	CView::OnLButtonDblClk(nFlags, point);
}

void CMy2021112880DrawingView::OnClear()
{
	// TODO: 在此添加命令处理程序代码
	m_link_list.MakeEmpty();
	CDC* pDC = GetDC();
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(255, 255, 255));
	ReleaseDC(pDC);
}

void CMy2021112880DrawingView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (type == 4)
	{
		if (m_pcurve && m_pcurve->point2set)
		{
			Node* newPoint = new Node;
			newPoint->now_type = 4;
			newPoint->now_RGB = what_RGB;
			newPoint->data = m_pcurve;
			m_link_list.InputFront(newPoint);
			m_pcurve = nullptr;
		}
	}
	else if (type == 5)
	{
		if(m_polyline)
		{
			m_polyline->over = true;
			Node* newPoint = new Node;
			newPoint->now_type = 5;
			newPoint->now_RGB = what_RGB;
			newPoint->data = m_polyline;
			m_link_list.InputFront(newPoint);
			m_polyline = NULL;
		}
	}
	else if (type == 6)
	{
		Node* rpaint = new Node;
		rpaint->now_RGB = what_RGB;
		rpaint->now_type = 6;
		rpaint->data = m_bspline;
		m_link_list.InputFront(rpaint);
		m_bspline = new BSplineCurve;
	}
	else if (type == 7)
	{
		//右键抬起绘制Bezier曲线
		CDC* pDC = GetDC();
		m_bezier->Draw(pDC);
		m_bezier->DrawControlPolygon(pDC);
		Node* rpaint = new Node;
		rpaint->now_type = 7;
		rpaint->data = m_bezier;
		m_link_list.InputFront(rpaint);
		m_bezier = new Bezier;
		ReleaseDC(pDC);
	}
	else if (type == 8)
	{
		if(m_bSpline->GetN() == 5)//确保已经初始化六个控制点后才绘制图形
		{
			//右键抬起绘制B_3曲线
			CDC* pDC = GetDC();
			m_bSpline->DrawBSplineCurve(pDC);
			m_bSpline->DrawControlPolygon(pDC);
			Node* rpaint = new Node;
			rpaint->now_type = 8;
			rpaint->data = m_bSpline;
			m_link_list.InputFront(rpaint);
			m_bSpline = new BSpline;
			ReleaseDC(pDC);
		}
	}
	//填充
	{
		CString str;
		if (Padding_type == 2 && pad)
		{
			pad->Set_Seed(point);
			CDC* pDC = GetDC();
			str.Format(_T("正在填充"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			if (function == 4)
				pad->Simple_Seed_Fill(pDC);
			else if (function == 5)
				pad->Scan_Seed_Fill(pDC);
			Padding_type = 0;
			str.Format(_T("填充成功"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			ReleaseDC(pDC);
		}
		else if (Padding_type == 3 && pad)
		{
			pad->Set_Seed(point);
			CDC* pDC = GetDC();
			str.Format(_T("正在填充"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			if (function == 4)
				pad->Simple_Seed_Fill(pDC);
			else if (function == 5)
				pad->Scan_Seed_Fill(pDC);
			Padding_type = 0;
			str.Format(_T("填充成功"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);

			ReleaseDC(pDC);
		}
		else if (Padding_type == 5 && pad)
		{
			pad->Set_Seed(point);
			CDC* pDC = GetDC();
			str.Format(_T("正在填充"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			if (function == 4)
				pad->Simple_Seed_Fill(pDC);
			else if (function == 5)
				pad->Scan_Seed_Fill(pDC);
			Padding_type = 0;
			str.Format(_T("填充成功"));
			GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowTextW(str);
			ReleaseDC(pDC);
		}
	}
	{
		if (function == 9)ClipLine();
	}
	IsOpenSelect = false;
	CView::OnRButtonUp(nFlags, point);
}

BOOL CMy2021112880DrawingView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (IsSelected && IsOpenSelect)
	{
		SetCursor(hCursor);
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
//颜色设置
void CMy2021112880DrawingView::OnBlue()
{
	// TODO: 在此添加命令处理程序代码
	what_RGB = 3;
}
void CMy2021112880DrawingView::OnRed()
{
	// TODO: 在此添加命令处理程序代码
	what_RGB = 1;
}
void CMy2021112880DrawingView::OnGreen()
{
	// TODO: 在此添加命令处理程序代码
	what_RGB = 2;
}
void CMy2021112880DrawingView::OnBlack()
{
	// TODO: 在此添加命令处理程序代码
	what_RGB = 0;
}
void CMy2021112880DrawingView::OnDrawVerLine()
{
	// TODO: 在此添加命令处理程序代码
	function = 1; //画垂线
	type = 0;
}
void CMy2021112880DrawingView::OnGetCenter()
{
	// TODO: 在此添加命令处理程序代码
	function = 3;//画圆心
	type = 0;
}
void CMy2021112880DrawingView::OnGetIntersection()
{
	// TODO: 在此添加命令处理程序代码
	function = 2;//求交点
	type = 0;
}

void CMy2021112880DrawingView::OnCenterLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
	CenPointDraw = 1;
}
void CMy2021112880DrawingView::OnBresenCircle()
{
	// TODO: 在此添加命令处理程序代码
	type = 3;
	BresenhamDraw = true;
}
void CMy2021112880DrawingView::OnScanSeedFill()
{
	// TODO: 在此添加命令处理程序代码
	function = 5;//扫描填充
	if (!pad)
		pad = new Padding;
}
void CMy2021112880DrawingView::OnSimpleSeedFill()
{
	// TODO: 在此添加命令处理程序代码
	function = 4;//简单填充
	if(!pad)
		pad = new Padding;
}
void CMy2021112880DrawingView::OnBSplineCurve()
{
	// TODO: 在此添加命令处理程序代码
	type = 6;
	if (!m_bspline)
		m_bspline = new BSplineCurve;
}
void CMy2021112880DrawingView::OnBezier()
{
	// TODO: 在此添加命令处理程序代码
	type = 7;
	if(!m_bezier)
		m_bezier = new Bezier;
}
void CMy2021112880DrawingView::OnBspline3()
{
	// TODO: 在此添加命令处理程序代码
	type = 8;
	if (!m_bSpline)
		m_bSpline = new BSpline;
}
void CMy2021112880DrawingView::OnTranslate()
{
	// TODO: 在此添加命令处理程序代码
	function = 6;
}
void CMy2021112880DrawingView::OnScale()
{
	// TODO: 在此添加命令处理程序代码
	function = 7;
}
void CMy2021112880DrawingView::OnRotate()
{
	// TODO: 在此添加命令处理程序代码
	function = 8;
}
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/
void CMy2021112880DrawingView::OnClipline()
{
	function = 9;
	CDC* pDC = GetDC();
	CPen newpen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* old = pDC->SelectObject(&newpen);
	pDC->Rectangle(CRect(XL, YT, XR, YB));
	ptset[0] = CPoint(120, 150);
	ptset[1] = CPoint(170, 110);
	ptset[2] = CPoint(0, 190);
	ptset[3] = CPoint(350, 150);
	ptset[4] = CPoint(0, 250);
	ptset[5] = CPoint(150, 230);
	ptset[6] = CPoint(200, 50);
	ptset[7] = CPoint(120, 150);
	pDC->TextOutW(0, 20, L"双击鼠标左键，出现要剪切的线段,右键按下完成裁剪");
	pDC->SelectObject(old);
}
void CMy2021112880DrawingView::ClipLine()
{
	CDC* pDC = GetDC();
	CPen newpen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* old = pDC->SelectObject(&newpen);
	if (Flag != 1) {
		MessageBox(L"请先双击鼠标左击", L"警告！");
	}
	else {
		Flag = 0;
		float x, y;
		int i;
		int code1, code2;
		RedrawWindow();
		for (int i = 0; i < N; i++, i++) {
			int c = 0;
			if (ptset[i].x < XL)
				c = c | LEFT;
			else if (ptset[i].x > XR)
				c = c | RIGHT;
			if (ptset[i].y > YB)
				c = c | BOTTOM;
			else if (ptset[i].y < YT)
				c = c | TOP;
			code1 = c;
			c = 0;
			if (ptset[i + 1].x < XL)
				c = c | LEFT;
			else if (ptset[i + 1].x > XR)
				c = c | RIGHT;
			if (ptset[i + 1].y > YB)
				c = c | BOTTOM;
			else if (ptset[i + 1].y < YT)
				c = c | TOP;
			code2 = c;
			if (code1 != 0 && code2 != 0 && (code1 & code2) == 0) {
				if ((LEFT & code1) != 0) {
					x = XL;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XL - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((RIGHT & code1) != 0) {
					x = XR;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XR - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((BOTTOM & code1) != 0) {
					y = YB;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YB - ptset[i].y) / (ptset[i + 1].y - ptset[i + 1].y);
				}
				else if ((TOP & code1) != 0) {
					y = YT;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YT - ptset[i].y) / (ptset[i + 1].y - ptset[i].y);
				}
				ptset[i].x = (long)x;
				ptset[i].y = (long)y;
				if ((LEFT & code2) != 0) {
					x = XL;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XL - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((RIGHT & code2) != 0) {
					x = XR;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XR - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((BOTTOM & code2) != 0) {
					y = YB;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YB - ptset[i].y) / (ptset[i + 1].y - ptset[i + 1].y);
				}
				else if ((TOP & code2) != 0) {
					y = YT;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YT - ptset[i].y) / (ptset[i + 1].y - ptset[i].y);
				}
				ptset[i + 1].x = (long)x;
				ptset[i + 1].y = (long)y;
				pDC->MoveTo(ptset[i].x, ptset[i].y);
				pDC->LineTo(ptset[i + 1].x, ptset[i + 1].y);
			}
			if (code1 == 0 && code2 == 0) {
				pDC->MoveTo(ptset[i].x, ptset[i].y);
				pDC->LineTo(ptset[i + 1].x, ptset[i + 1].y);
			}
			if (code1 == 0 && code2 != 0) {
				pDC->MoveTo(ptset[0].x, ptset[0].y);
				if ((LEFT & code2) != 0) {
					x = XL;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XL - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((RIGHT & code2) != 0) {
					x = XR;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XR - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((BOTTOM & code2) != 0) {
					y = YB;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YB - ptset[i].y) / (ptset[i + 1].y - ptset[i + 1].y);
				}
				else if ((TOP & code2) != 0) {
					y = YT;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YT - ptset[i].y) / (ptset[i + 1].y - ptset[i].y);
				}
				ptset[i + 1].x = (long)x;
				ptset[i + 1].y = (long)y;
				pDC->LineTo(ptset[i + 1].x, ptset[i + 1].y);
			}
			if (code1 != 0 && code2 == 0) {
				pDC->MoveTo(ptset[i + 1].x, ptset[i + 1].y);
				if ((LEFT & code1) != 0) {
					x = XL;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XL - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((RIGHT & code1) != 0) {
					x = XR;
					y = (float)ptset[i].y + (ptset[i + 1].y - ptset[i].y) * (XR - ptset[i].x) / (ptset[i + 1].x - ptset[i].x);
				}
				else if ((BOTTOM & code1) != 0) {
					y = YB;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YB - ptset[i].y) / (ptset[i + 1].y - ptset[i + 1].y);
				}
				else if ((TOP & code1) != 0) {
					y = YT;
					x = (float)ptset[i].x + (ptset[i + 1].x - ptset[i].x) * (YT - ptset[i].y) / (ptset[i + 1].y - ptset[i].y);
				}
				ptset[i].x = (long)x;
				ptset[i].y = (long)y;
				pDC->LineTo(ptset[i].x, ptset[i].y);
			}
		}
	}
}
/*******************************************************/
/*******************************************************/
/*裁剪测试代码*/

void CMy2021112880DrawingView::OnSelectrect()
{
 	// TODO: 在此添加命令处理程序代码
	type = 9;//选取框
}