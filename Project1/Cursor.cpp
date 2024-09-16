#include "Cursor.h"
#include <windows.h>
#include "Utils.h"

void Cursor::MoveLeftStick(int x, int y)
{
	int xDelta = static_cast<int>(x * sensitivity);
	int yDelta = static_cast<int>(y * sensitivity);
	if (xDelta != 0 || yDelta != 0)
	{
		MoveMouse(xDelta, yDelta);
	}
	MoveMouse(xDelta, yDelta);
}

void Cursor::MoveRightStick(int x, int y)
{
	SimulateMouseWheelScroll(y);
}

void Cursor::AButton()
{
	SimulateMouseClick();
}

void Cursor::BButton()
{
	SimulateRightClick();
}

void Cursor::XButton()
{
	sensitivity -= deltaSensitivity;
}

void Cursor::YButton()
{
	sensitivity += deltaSensitivity;
}

void Cursor::LButton()
{
	SimulateMouseClick();
}

void Cursor::RButton()
{
	SimulateMouseClick();
}

void Cursor::ZLButton()
{
	SimulateMouseClick();
}

void Cursor::ZRButton()
{
	SimulateMouseClick();
}
