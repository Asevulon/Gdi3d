#include<afxwin.h>


class App : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
App app;

class Win :public CFrameWnd
{
public:
	Win() { Create(NULL, L"gdi3d"); }
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

BOOL App::InitInstance()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_pMainWnd = new Win;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return CWinApp::InitInstance();
}
BEGIN_MESSAGE_MAP(Win, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void Win::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CFrameWnd::OnPaint() для сообщений рисования
}
