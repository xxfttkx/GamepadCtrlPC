#pragma once
#include <windows.h>

void EnableChinese();
void MoveMouse(int x, int y);
void SimulateMouseClick();
void SimulateRightClick();
void SimulateMouseWheelScroll(int scrollAmount);
void CloseCurrentWindow();
void MinimizeCurrentWindow();
void SimulateEnterKey();
void SimulateSpacebarPress();
void CaptureScreen();
void SimulateKeyPress(WORD key);
void CheckBatteryPower();
void PrintTime();