#include "Utils.h"
#include <iostream>
#include <windows.h>

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