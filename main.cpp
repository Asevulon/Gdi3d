#include<afxwin.h>

#include"Drawer.h"


class App : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
App app;

class Win :public CFrameWnd
{
	Drawer drw;
	bool lbDown = false;
	CPoint lbD;
public:
	Win();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
Win::Win()
{
	Create(NULL, L"gdi3d");;
	drw.SetScale(200);
	drw.SetViewPoint(3, 0, 0);
	drw.SetRadius(4000);
}
BOOL App::InitInstance()
{
	// TODO: добавьте специализированный код или вызов базового класса
	ULONG_PTR token;
	GdiplusStartupInput si;

	GdiplusStartup(&token, &si, NULL);

	m_pMainWnd = new Win;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	
	return CWinApp::InitInstance();
}
BEGIN_MESSAGE_MAP(Win, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


#include"math3d.h"
using namespace math3d;
void Win::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CFrameWnd::OnPaint() для сообщений рисования


	drw.SetBmpSize(dc);
	drw.Draw(dc);
	/*for (int i = 0; i < 360; i+=3)
	{
		drw.SetRotate(i, 0, 0);
		drw.Draw(dc);
	}*/
	for (int i = 0; i < 360; i+=3)
	{
		drw.SetRotate(0, i, 0);
		drw.Draw(dc);
	}
	for (int i = 0; i < 360; i+=3)
	{
		drw.SetRotate(0, 0, i);
		drw.Draw(dc);
	}
}


void Win::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	lbDown = true;
	lbD = point;
	CFrameWnd::OnLButtonDown(nFlags, point);
}


void Win::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	lbDown = false;

	CFrameWnd::OnLButtonUp(nFlags, point);
}


void Win::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (lbDown)
	{
		drw.OnMouseMove(point.x - lbD.x, point.y - lbD.y);
		lbD = point;
		Invalidate(FALSE);
	}
	CFrameWnd::OnMouseMove(nFlags, point);
}
