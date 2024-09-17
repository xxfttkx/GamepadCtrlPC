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

// 关闭当前窗口
void CloseCurrentWindow() {
	// 获取当前活动窗口的句柄
	HWND hwnd = GetForegroundWindow();

	// 确保窗口句柄有效
	if (hwnd != NULL) {
		// 发送关闭消息
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

// 最小化当前窗口的函数
void MinimizeCurrentWindow() {
	// 获取当前活动窗口的句柄
	HWND hwnd = GetForegroundWindow();

	// 确保窗口句柄有效
	if (hwnd != NULL) {
		// 最小化窗口
		ShowWindow(hwnd, SW_MINIMIZE);
	}
}

// 模拟按下和释放 Enter 键
void SimulateEnterKey() {
	// 设置 INPUT 结构体
	INPUT ip;
	ZeroMemory(&ip, sizeof(INPUT));
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_RETURN;

	// 按下 Enter 键
	SendInput(1, &ip, sizeof(INPUT));

	// 释放 Enter 键
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void SimulateSpacebarPress() {
	INPUT inputs[2] = {};

	// 设置输入事件类型为键盘事件
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_SPACE; // 空格键的虚拟键码

	// 设置释放空格键的输入事件
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_SPACE;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 按键释放事件

	// 发送输入事件
	SendInput(2, inputs, sizeof(INPUT));
}