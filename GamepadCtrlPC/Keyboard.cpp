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
	// enter��
	SimulateEnterKey();
}

void Keyboard::BButton()
{
	MinimizeCurrentWindow();
}

void Keyboard::XButton()
{
	// �ո��
	SimulateSpacebarPress();
}

void Keyboard::YButton()
{
}

// �رյ�ǰ����
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
