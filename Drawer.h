#pragma once


#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define XMIN -2.
#define XMAX 2.
#define YMIN -2.
#define YMAX 2.
#define DELTA 0.2

#include"math3d.h"
using namespace math3d;
#include<math.h>


class Drawer
{
private:
	int height = 0;
	int width = 0;

	int trX = 0;
	int trY = 0;

	double scale = 0;

	double rx = 0;
	double ry = 0;
	double rz = 0;

	vec4 ViewPoint;
	vec4 actViewPoint;
	double R = 3;

	void Drawer::DCreatePolygonpoints(double x, double y, Point* out);

protected:
	inline void CreatePolygonpoints(double x, double y, Point* out);
	inline double CalcZ(double x, double y);
public:
	Drawer();
	~Drawer();

	Status Draw(HDC hdc);
	void Drawer::SetBmpSize(HDC hdc);
	void SetScale(double x);
	void SetRotate(double x, double y, double z);
	void SetViewPoint(double x, double y, double z);
	void SetRadius(double r);

	void OnMouseMove(int x, int y);
};