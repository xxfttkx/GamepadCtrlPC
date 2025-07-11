#include "Cursor.h"
#include <windows.h>
#include <cmath> // 替换 <math.h> 为 <cmath>，以确保 std::sqrt 可用
#include "Utils.h"

void Cursor::MoveLeftStick(int x, int y)
{
	speed = maxSpeed;
	if (speed < maxSpeed)
	{
		speed += acceleration;
	}
	else
	{
		speed = maxSpeed;
	}
	int xDelta = static_cast<int>(x * leftSensitivity * speed);
	int yDelta = static_cast<int>(y * leftSensitivity * speed);
	if (xDelta != 0 || yDelta != 0)
	{
		MoveMouse(xDelta, yDelta);
	}
}

void Cursor::MoveRightStick(int x, int y)
{
	speed = 0;
	SimulateMouseWheelScroll(-y*rightSensitivity);
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
	SimulateKeyPress(VK_ESCAPE);
}

void Cursor::ZRButton()
{
	SimulateMouseClick();
}
