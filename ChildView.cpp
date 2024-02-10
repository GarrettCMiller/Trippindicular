// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Trippindicular.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Vec2 pos;
	pos.X = point.x / 1600.0f;
	pos.Y = 1.0f - point.y / 900.0f;

	SAFE_CALL(theApp.m_Viz.PlotPoint(pos))

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		Vec2 pos;
		pos.X = point.x / 1600.0f;
		pos.Y = 1.0f - point.y / 900.0f;
		
		SAFE_CALL(theApp.m_Viz.PlotPoint(pos))
	}

	CWnd::OnMouseMove(nFlags, point);
}
