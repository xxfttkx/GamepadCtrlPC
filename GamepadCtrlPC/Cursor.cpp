#include "Cursor.h"
#include <windows.h>
#include "Utils.h"

void Cursor::MoveLeftStick(int x, int y)
{
	int xDelta = static_cast<int>(x * leftSensitivity);
	int yDelta = static_cast<int>(y * leftSensitivity);
	if (xDelta != 0 || yDelta != 0)
	{
		MoveMouse(xDelta, yDelta);
	}
}

void Cursor::MoveRightStick(int x, int y)
{
	SimulateMouseWheelScroll(y*rightSensitivity);
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
	SimulateMouseClick();
}

void Cursor::YButton()
{
	SimulateMouseClick();
}

void Cursor::UpButton()
{
	if (rightSensitivity < 10 * deltaRightSensitivity)
		rightSensitivity += deltaRightSensitivity;
}

void Cursor::DownButton()
{
	if (rightSensitivity - deltaRightSensitivity > 0)
		rightSensitivity -= deltaRightSensitivity;
}

void Cursor::LeftButton()
{
	if (leftSensitivity - deltaLeftSensitivity > 0)
		leftSensitivity -= deltaLeftSensitivity;
}

void Cursor::RightButton()
{
	if (leftSensitivity < 10 * deltaLeftSensitivity)
		leftSensitivity += deltaLeftSensitivity;
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
