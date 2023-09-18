#include"Drawer.h"




Drawer::Drawer()
{
	GdiplusStartup(&token, &si, NULL);

}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}