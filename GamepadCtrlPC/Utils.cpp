#include "Utils.h"
#include <iostream>
#include <windows.h>

void MoveMouse(int x,int y)
{
	POINT p;
	GetCursorPos(&p);
	SetCursorPos(p.x + x, p.y + y);
}
// 模拟鼠标点击
void SimulateMouseClick() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 按下鼠标左键
	SendInput(1, &input, sizeof(INPUT));    // 发送按下事件

	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;   // 松开鼠标左键
	SendInput(1, &input, sizeof(INPUT));    // 发送松开事件
}

// 右键点击
void SimulateRightClick() {
	// 创建一个 INPUT 结构体来表示鼠标输入
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;

	// 模拟按下鼠标右键
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// 模拟释放鼠标右键
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

// 模拟鼠标滚轮滚动的函数
void SimulateMouseWheelScroll(int scrollAmount) {
	// 创建 INPUT 结构体来表示鼠标输入
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	input.mi.mouseData = scrollAmount; // 滚动量，负值表示向下滚动，正值表示向上滚动

	// 发送输入事件
	SendInput(1, &input, sizeof(INPUT));
}

void Print(std::string s)
{
	std::cout << s << std::endl;
}