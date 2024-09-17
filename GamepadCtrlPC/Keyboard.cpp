#include "Keyboard.h"
#include <windows.h>
#include "Utils.h"

void Keyboard::MoveLeftStick(int x, int y)
{
	MoveMouse(x, y);
}

void Keyboard::MoveRightStick(int x, int y)
{
	SimulateMouseWheelScroll(y);
}

void Keyboard::AButton()
{
	// enter键
	SimulateEnterKey();
}

void Keyboard::BButton()
{
	MinimizeCurrentWindow();
}

void Keyboard::XButton()
{
	// 空格键
	SimulateSpacebarPress();
}

void Keyboard::YButton()
{
}

// 关闭当前窗口
void Keyboard::LButton()
{
	CloseCurrentWindow();
}

void Keyboard::RButton()
{
}

void Keyboard::ZLButton()
{
}

void Keyboard::ZRButton()
{
	SimulateSpacebarPress();
}
