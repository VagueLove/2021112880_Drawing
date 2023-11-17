
// 2021112880_DrawingView.h: CMy2021112880DrawingView 类的接口
//

#pragma once
#include "CSlist.h"
#include "DataDraw.h"
#include "DataDraw.h"
#include "Curve.h"
#include "PolyLine.h"
#include "CDrawVerLine.h"
#include "CGetIntersection.h"
#include "Padding.h"
#include "BSplineCurve.h"
#include "Bezier.h"

class CMy2021112880DrawingView : public CView
{
protected: // 仅从序列化创建
	CMy2021112880DrawingView() noexcept;
	DECLARE_DYNCREATE(CMy2021112880DrawingView)

// 特性
public:
	CMy2021112880DrawingDoc* GetDocument() const;

// 操作
public:
	//画一个小圆当作点
	void Draw_Point(CPoint point);
	//鼠标左键按下值的设置
	void LButtonDown_Set_RGB();
	void LButtonDown_Set_Type(CPoint point);
	void LButtonDown_Set_Function(CPoint point);
	//鼠标左键抬起值的设置
	void LButtonUp_Set_RGB_Type(CPoint point);
	void LButtonUp_Set_Function();
	//鼠标左键双击按下
	void LButtionDbCLK_For_Type(CPoint point);
	//鼠标移动绘制基本图形
	void MouseMove_Draw_Basic_Graphics(CPoint point);
	//鼠标移动，判断图形是否处于选中态
	void MouseMove_IsSelect(CPoint point);
	//鼠标移动，根据不同颜色绘制图形
	void MouseMove_Draw(CPoint point, int color);
protected:
	
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
// 实现
public:
	virtual ~CMy2021112880DrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	//图形类型
	int type;
	//图形颜色
	int what_RGB;
	//中点画线法
	int CenPointDraw;
	bool BresenhamDraw;
	//功能
	int function;
	//待填充的图形类型
	unsigned int Padding_type;
	//光标控制信号
	bool IsOpenSelect;
	bool IsSelected;
	bool start;
	bool go;

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnCircle();
	afx_msg void OnRectangle();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBlue();
	afx_msg void OnRed();
	afx_msg void OnGreen();
	afx_msg void OnSelect();
	afx_msg void OnCurve();
	afx_msg void OnPolyLine();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClear();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawVerLine();
	afx_msg void OnGetCenter();
	afx_msg void OnGetIntersection();
protected:
//	afx_msg LRESULT OnOnsetmousecursor(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBlack();
	afx_msg void OnCenterLine();
	afx_msg void OnBresenCircle();
	afx_msg void OnScanSeedFill();
	afx_msg void OnSimpleSeedFill();
	afx_msg void OnBSplineCurve();
	afx_msg void OnBezier();
};

#ifndef _DEBUG  // 2021112880_DrawingView.cpp 中的调试版本
inline CMy2021112880DrawingDoc* CMy2021112880DrawingView::GetDocument() const
   { return reinterpret_cast<CMy2021112880DrawingDoc*>(m_pDocument); }
#endif

