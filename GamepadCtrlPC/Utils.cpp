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
// ģ�������
void SimulateMouseClick() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // ����������
	SendInput(1, &input, sizeof(INPUT));    // ���Ͱ����¼�

	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;   // �ɿ�������
	SendInput(1, &input, sizeof(INPUT));    // �����ɿ��¼�
}

// �Ҽ����
void SimulateRightClick() {
	// ����һ�� INPUT �ṹ������ʾ�������
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;

	// ģ�ⰴ������Ҽ�
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	// ģ���ͷ�����Ҽ�
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

// ģ�������ֹ����ĺ���
void SimulateMouseWheelScroll(int scrollAmount) {
	// ���� INPUT �ṹ������ʾ�������
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	input.mi.mouseData = scrollAmount; // ����������ֵ��ʾ���¹�������ֵ��ʾ���Ϲ���

	// ���������¼�
	SendInput(1, &input, sizeof(INPUT));
}

void Print(std::string s)
{
	std::cout << s << std::endl;
}

// �رյ�ǰ����
void CloseCurrentWindow() {
	// ��ȡ��ǰ����ڵľ��
	HWND hwnd = GetForegroundWindow();

	// ȷ�����ھ����Ч
	if (hwnd != NULL) {
		// ���͹ر���Ϣ
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

// ��С����ǰ���ڵĺ���
void MinimizeCurrentWindow() {
	// ��ȡ��ǰ����ڵľ��
	HWND hwnd = GetForegroundWindow();

	// ȷ�����ھ����Ч
	if (hwnd != NULL) {
		// ��С������
		ShowWindow(hwnd, SW_MINIMIZE);
	}
}

// ģ�ⰴ�º��ͷ� Enter ��
void SimulateEnterKey() {
	// ���� INPUT �ṹ��
	INPUT ip;
	ZeroMemory(&ip, sizeof(INPUT));
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_RETURN;

	// ���� Enter ��
	SendInput(1, &ip, sizeof(INPUT));

	// �ͷ� Enter ��
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void SimulateSpacebarPress() {
	INPUT inputs[2] = {};

	// ���������¼�����Ϊ�����¼�
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_SPACE; // �ո�����������

	// �����ͷſո���������¼�
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_SPACE;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // �����ͷ��¼�

	// ���������¼�
	SendInput(2, inputs, sizeof(INPUT));
}
std::wstring GetCaptureFilename()
{
	std::wstring directory = L"F:\\Cap\\";
	std::wstring baseFilename = L"screenshot";
	std::wstring extension = L".bmp";

	// ��鲢�����ļ���
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
	bmpInfo.bmiHeader.biHeight = height; // ������ʾ���¶���
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// ��ȡλͼ����
	BYTE* pPixels = new BYTE[width * height * 3];
	GetDIBits(hMemoryDC, hBitmap, 0, height, pPixels, &bmpInfo, DIB_RGB_COLORS);

	// д���ļ�
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

	// ������Դ
	delete[] pPixels;
	DeleteObject(hBitmap);
	DeleteDC(hMemoryDC);
	ReleaseDC(NULL, hScreenDC);
}

void SimulateKeyPress(WORD key) {
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key; // �����������

	// ���¼�
	SendInput(1, &input, sizeof(INPUT));

	// �ͷż�
	input.ki.dwFlags = KEYEVENTF_KEYUP; // ����Ϊ�ͷ��¼�
	SendInput(1, &input, sizeof(INPUT));
}

void CheckBatteryPower() {
	// ��ȡ��Դ��Ϣ
	int seconds = 0, percent=0;
	SDL_PowerState powerState = SDL_GetPowerInfo(&seconds,&percent);

	// �����Դ��Ϣ
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