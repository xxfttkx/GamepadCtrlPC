#include "Keyboard.h"
#include <windows.h>
#include "Utils.h"

void Keyboard::MoveLeftStick(int x, int y)
{
	if (x > 10)SimulateKeyPress(0x41+('d'-'a'));
	else if (x < -10)SimulateKeyPress(0x41);
	if (y > 10)SimulateKeyPress(0x41 + ('s' - 'a'));
	else if (y < -10)SimulateKeyPress(0x41 + ('w' - 'a'));
}

void Keyboard::MoveRightStick(int x, int y)
{
	if (x > 100)SimulateKeyPress(VK_RIGHT);
	else if (x < -100)SimulateKeyPress(VK_LEFT);
	if (y > 100)SimulateKeyPress(VK_UP);
	else if (y < -100)SimulateKeyPress(VK_DOWN);
}

void Keyboard::AButton()
{
	// Enter键
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

void Keyboard::UpButton()
{
}

void Keyboard::DownButton()
{
}

void Keyboard::LeftButton()
{
}

void Keyboard::RightButton()
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
