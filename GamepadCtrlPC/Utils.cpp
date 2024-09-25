#include "Utils.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>

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
std::wstring GetCaptureFilename()
{
	std::wstring directory = L"F:\\Cap\\";
	std::wstring baseFilename = L"screenshot";
	std::wstring extension = L".bmp";

	// 检查并生成文件名
	int index = 0;
	std::wstring filename;
	do {
		std::wostringstream oss;
		oss << directory << baseFilename << (index == 0 ? extension : std::to_wstring(index) + extension);
		filename = oss.str();
		index++;
	} while (std::filesystem::exists(filename));

	return filename;
}

void CaptureScreen() {
	std::wstring filename = GetCaptureFilename();
	HDC hScreenDC = GetDC(NULL);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	SelectObject(hMemoryDC, hBitmap);
	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

	BITMAPINFO bmpInfo = { 0 };
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height; // 正数表示自下而上
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// 获取位图数据
	BYTE* pPixels = new BYTE[width * height * 3];
	GetDIBits(hMemoryDC, hBitmap, 0, height, pPixels, &bmpInfo, DIB_RGB_COLORS);

	// 写入文件
	std::ofstream file(filename, std::ios::binary);
	BITMAPFILEHEADER fileHeader = { 0 };
	fileHeader.bfType = 0x4D42; // "BM"
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fileHeader.bfSize = fileHeader.bfOffBits + width * height * 3;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;

	file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
	file.write(reinterpret_cast<const char*>(&bmpInfo.bmiHeader), sizeof(BITMAPINFOHEADER));
	file.write(reinterpret_cast<const char*>(pPixels), width * height * 3);

	// 清理资源
	delete[] pPixels;
	DeleteObject(hBitmap);
	DeleteDC(hMemoryDC);
	ReleaseDC(NULL, hScreenDC);
}

void SimulateKeyPress(WORD key) {
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key; // 设置虚拟键码

	// 按下键
	SendInput(1, &input, sizeof(INPUT));

	// 释放键
	input.ki.dwFlags = KEYEVENTF_KEYUP; // 设置为释放事件
	SendInput(1, &input, sizeof(INPUT));
}

void CheckBatteryPower() {
	// 获取电源信息
	int seconds = 0, percent=0;
	SDL_PowerState powerState = SDL_GetPowerInfo(&seconds,&percent);

	// 输出电源信息
	std::cout << "Power State: ";
	switch (powerState) {
	case SDL_POWERSTATE_UNKNOWN:
		std::cout << "Unknown" << std::endl;
		break;
	case SDL_POWERSTATE_ON_BATTERY:
		std::cout << "On Battery" << std::endl;
		break;
	case SDL_POWERSTATE_NO_BATTERY:
		std::cout << "No Battery" << std::endl;
		break;
	case SDL_POWERSTATE_CHARGING:
		std::cout << "Charging" << std::endl;
		break;
	case SDL_POWERSTATE_CHARGED:
		std::cout << "Charged" << std::endl;
		break;
	}

	if (powerState != SDL_POWERSTATE_NO_BATTERY) {
		std::cout << "Battery Seconds: " << seconds << "%, Battery Power: " << percent << "%" << std::endl;
	}
}