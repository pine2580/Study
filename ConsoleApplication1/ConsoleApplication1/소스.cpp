#include <turboc.h>

class Coord
{
protected:
	int a, b;
public:
	Coord(int ax, int bx)
	{
		a = ax;
		b = bx;
	}
};
class Plus: public Coord
{
protected:
	int c;
public:
	Plus(int ax, int bx, int cx):Coord(ax, bx)
	{
		c = a + b;
	}
	void Show()
	{
		printf("%d", c);
	}
};
class Sub: public Plus
{
protected:
	int d;
public:
	Sub(int ax, int bx, int cx, int dx):Plus(ax, bx, cx)
	{
		d = c - a - b;
	}
	void Show()
	{
		printf("%d + %d = %d \n", a, b, c);
		printf("%d - %d - %d = %d\n", c, a, b, d);
	}
};