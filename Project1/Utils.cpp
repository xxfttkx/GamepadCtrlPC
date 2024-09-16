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