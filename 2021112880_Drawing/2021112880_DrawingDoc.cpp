
// 2021112880_DrawingDoc.cpp: CMy2021112880DrawingDoc 类的实现
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


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2021112880DrawingDoc

IMPLEMENT_DYNCREATE(CMy2021112880DrawingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy2021112880DrawingDoc, CDocument)
END_MESSAGE_MAP()


// CMy2021112880DrawingDoc 构造/析构

CMy2021112880DrawingDoc::CMy2021112880DrawingDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CMy2021112880DrawingDoc::~CMy2021112880DrawingDoc()
{
}

BOOL CMy2021112880DrawingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}



// CMy2021112880DrawingDoc 序列化
extern CSlist m_link_list;
void CMy2021112880DrawingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int i = 1;
		int len = m_link_list.Length();
		ar << len;
		while (i <= len)
		{
			Node* temp = m_link_list.GetElement(i);
			ar << temp->now_type << temp->now_RGB;
			switch (temp->now_type)
			{
			case 1:
			{
				ar << ((CLine*)temp->data)->GetStart().x << ((CLine*)temp->data)->GetStart().y <<
					((CLine*)temp->data)->GetEnd().x << ((CLine*)temp->data)->GetEnd().y;
			}break;
			case 2:
			{

				ar << ((CQuare*)temp->data)->GetStart().x << ((CQuare*)temp->data)->GetStart().y <<
					((CQuare*)temp->data)->GetEnd().x << ((CQuare*)temp->data)->GetEnd().y;
			}break;
			case 3:
			{
				ar << ((CCircle*)temp->data)->GetCenter().x << ((CCircle*)temp->data)->GetCenter().y <<
					((CCircle*)temp->data)->GetRadius();
			}break;
			case 4:
			{
				ar << ((Curve*)temp->data)->Get_start_point().x << 
					((Curve*)temp->data)->Get_start_point().y << 
					((Curve*)temp->data)->Get_Cent_point().x << 
					((Curve*)temp->data)->Get_Cent_point().y <<
					((Curve*)temp->data)->Get_end_point().x << 
					((Curve*)temp->data)->Get_end_point().y;
			}break;
			case 5:
			{
				int num = ((PolyLine*)temp->data)->Get_num();
				ar << num;
				int i = 0;
				for (; i < num; ++i)
				{
					ar << ((PolyLine*)temp->data)->pointbox[i].x;
					ar << ((PolyLine*)temp->data)->pointbox[i].y;
				}
			}
			break;
			case 6:
			{
				ar << ((BSplineCurve*)temp->data)->bSplinePoints.size();
				for (const auto& i : ((BSplineCurve*)temp->data)->bSplinePoints)
				{
					ar << i.x << i.y;
				}
			}break;
			default:
				break;
			}
			++i;
			
		}
	}
	else
	{
		m_link_list.MakeEmpty();
		int len = 0, i = 1;
		int now_RGB = 0;//画笔颜色
		int now_type = 0;//存储形状
		ar >> len;
		while (i <= len)
		{
			Node* repaint = new Node;
			ar >> now_type >> now_RGB;
			switch (now_type)
			{
			case 1:
			{
				CPoint P1, P2;
				ar >> P1.x >> P1.y;
				ar >> P2.x >> P2.y;
				CLine* m_pline = new CLine;
				m_pline->Set_start_point(P1);
				m_pline->Set_end_point(P2);
				repaint->now_type = 1;
				repaint->now_RGB = now_RGB;
				repaint->data = m_pline;
				m_link_list.InputTail(repaint);
			}break;
			case 2:
			{
				CPoint P1, P2;
				ar >> P1.x >> P1.y;
				ar >> P2.x >> P2.y;
				CQuare* m_psquare = new CQuare;
				m_psquare->Set_first_point(P1);
				m_psquare->Set_end_point(P2);
				repaint->now_type = 2;
				repaint->now_RGB = now_RGB;
				repaint->data = m_psquare;
				m_link_list.InputTail(repaint);
			}break;
			case 3:
			{
				CPoint P1;
				int radius;
				ar >> P1.x >> P1.y;
				ar >> radius;
				CCircle* m_pcircle = new CCircle;
				m_pcircle->Set_CenPoint(P1);
				m_pcircle->Set_Radius(radius);
				repaint->now_type = 3;
				repaint->now_RGB = now_RGB;
				repaint->data = m_pcircle;
				m_link_list.InputTail(repaint);
			}break;
			case 4:
			{
				Curve* m_pcurve = new Curve;
				CPoint start, center, end;
				ar >> start.x >> start.y >> center.x >> center.y >> end.x >> end.y;
				m_pcurve->Set_start_point(start);
				m_pcurve->SetCenterPoint(center);
				m_pcurve->Set_end_point(end);
				repaint->now_RGB = now_RGB;
				repaint->now_type = 4;
				repaint->data = m_pcurve;
				m_link_list.InputTail(repaint);
			}break;
			case 5:
			{
				int num = 0;
				PolyLine* m_polyline = new PolyLine;
				ar >> num;
				m_polyline->Set_num(num);
				CPoint p;
				for (int i = 0; i < num; ++i)
				{
					ar >> p.x >> p.y;
					m_polyline->pointbox[i].x = p.x;
					m_polyline->pointbox[i].y = p.y;
				}
				repaint->now_RGB = now_RGB;
				repaint->now_type = 5;
				repaint->data = m_polyline;
				m_link_list.InputTail(repaint);

			}break;
			case 6:
			{
				BSplineCurve* m_bSpline = new BSplineCurve;
				int len2 = 0;
				ar >> len2;
				CPoint temp;
				for (int i = 0; i < len2; ++i)
				{
					ar >> temp.y >> temp.x;
					m_bSpline->bSplinePoints.push_back(temp);
				}
				repaint->now_RGB = now_RGB;
				repaint->now_type = now_type;
				repaint->data = m_bSpline;
				m_link_list.InputTail(repaint);

			}break;
			default:
				break;
			}
			++i;
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy2021112880DrawingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockOblenect(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectOblenect(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectOblenect(pOldFont);
}

// 搜索处理程序的支持
void CMy2021112880DrawingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole oblenect;")；
	SetSearchContent(strSearchContent);
}

void CMy2021112880DrawingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2021112880DrawingDoc 诊断

#ifdef _DEBUG
void CMy2021112880DrawingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2021112880DrawingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2021112880DrawingDoc 命令
