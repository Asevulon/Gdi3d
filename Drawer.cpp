#include"Drawer.h"



Drawer::Drawer()
{
	
}

Drawer::~Drawer()
{
}
void Drawer::SetScale(double x)
{
	scale = x;
}


void Drawer::SetRadius(double r)
{
	double temp = r / R;
	ViewPoint.x() *= temp;
	ViewPoint.y() *= temp;
	ViewPoint.z() *= temp;

}

void Drawer::SetViewPoint(double x, double y, double z)
{
	ViewPoint.x() = x;
	ViewPoint.y() = y;
	ViewPoint.z() = z;
}
void Drawer::SetBmpSize(HDC hdc)
{
	HBITMAP hbm = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);
	BITMAP bm;
	GetObject(hbm, sizeof(bm), (LPVOID)&bm);
	width = bm.bmWidth; //ширина картинки в
	height = bm.bmHeight;//высота картинки
	trX = width / 2.;
	trY = height / 2.;
}
void Drawer::SetRotate(double x, double y, double z)
{
	rx = x;
	ry = y;
	rz = z;
}

Status Drawer::Draw(HDC hdc)
{
	Graphics FinalDrawer(hdc);
	Bitmap bmp(width, height);
	Graphics gr(&bmp);
	gr.SetSmoothingMode(SmoothingModeAntiAlias);
	gr.Clear(Color::White);

	SolidBrush brush(Color::BlueViolet);
	Pen pen(Color::CornflowerBlue);

	double actualXmax = XMAX - DELTA;
	double actualYmax = YMAX - DELTA;

	for (double x = XMIN; x <= actualXmax; x += DELTA)
	{
		for (double y = YMIN; y <= actualYmax; y += DELTA)
		{
			Point point[8];
			CreatePolygonpoints(x, y, point);
			gr.FillPolygon(&brush, point, 4);
			gr.DrawPolygon(&pen, point, 4);
		}
	}

	FinalDrawer.DrawImage(&bmp, 0, 0);
	return Status::Ok;
}


void Drawer::CreatePolygonpoints(double x, double y, Point* out)
{
	mat4 m, mp;
	m.rotateX(rx).rotateY(ry).rotateZ(rz);
	actViewPoint = ViewPoint * m;
	//mp.perspective(actViewPoint.x(), actViewPoint.y(), actViewPoint.z());
	mp.perspective(actViewPoint.x(), actViewPoint.y(), actViewPoint.y());
	m.scale(scale, scale, -scale).translate(0, trX, trY);
	actViewPoint = ViewPoint * m;

	vec4 p;
	p.x() = x;
	p.y() = y;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[0] = Point(p.y(), p.z());

	p.x() = x + DELTA;
	p.y() = y;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[1] = Point(p.y(), p.z());

	p.x() = x;
	p.y() = y + DELTA;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[3] = Point(p.y(), p.z());

	p.x() = x + DELTA;
	p.y() = y + DELTA;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[2] = Point(p.y(), p.z());
}

//for debug
void Drawer::DCreatePolygonpoints(double x, double y, Point* out)
{
	double center = 3;
	mat4 m, mp;
	mp.perspective(3,0,0);

	m.scale(scale, scale, -scale).translate(0, trX, trY);
	vec4 p;
	p.x() = x;
	p.y() = y;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[0] = Point(p.y(), p.z());

	p.x() = x + DELTA;
	p.y() = y;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[1] = Point(p.y(), p.z());

	p.x() = x;
	p.y() = y + DELTA;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[3] = Point(p.y(), p.z());

	p.x() = x + DELTA;
	p.y() = y + DELTA;
	p.z() = CalcZ(p.x(), p.y());
	p = p * mp;
	p.normalize();
	p = p * m;
	out[2] = Point(p.y(), p.z());
}


double Drawer::CalcZ(double x, double y)
{
	double temp = x * x + y * y;
	return cos(temp) / (temp + 1);
}


void Drawer::OnMouseMove(int x, int y)
{
	mat4 m;
	m.translate(0, -trX, -trY).scale(1/scale, 1/scale, 1/-scale).rotateZ(-rz).rotateY(-ry).rotateX(-rx);
	actViewPoint.y() += x;
	actViewPoint.z() += y;
	actViewPoint = actViewPoint * m;
	double absol = sqrt(actViewPoint.x() * actViewPoint.x() + actViewPoint.y() * actViewPoint.y() + actViewPoint.z() * actViewPoint.z()) / R;
	actViewPoint.x() /= absol;
	actViewPoint.y() /= absol;
	actViewPoint.z() /= absol;
	
	
}
