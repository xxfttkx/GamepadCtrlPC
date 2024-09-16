#include "Keyboard.h"
#include <windows.h>
#include "Utils.h"

void Keyboard::MoveLeftStick(int x, int y)
{
}

void Keyboard::MoveRightStick(int x, int y)
{
}

void Keyboard::AButton()
{
	SimulateMouseClick();
}

void Keyboard::BButton()
{
	HWND hwnd = GetForegroundWindow();  // 获取当前活动窗口的句柄
	if (hwnd) {
		ShowWindow(hwnd, SW_MINIMIZE);  // 最小化窗口
	}
	else {
		MessageBox(nullptr, L"No window is currently in the foreground.", L"Error", MB_OK | MB_ICONERROR);
	}
}

void Keyboard::XButton()
{
}

void Keyboard::YButton()
{
}

void Keyboard::LButton()
{
}

void Keyboard::RButton()
{
}

void Keyboard::ZLButton()
{
}

void Keyboard::ZRButton()
{
}
