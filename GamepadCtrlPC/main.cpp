#include <SDL2/SDL.h>
#include <windows.h>
#include <iostream>
#include <chrono>
#include "BaseCtrl.h"
#include "Cursor.h"
#include "KeyBoard.h"
#include "Utils.h"




int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GameController* controller = nullptr;
	bool found = false;
	while (!found)
	{
		// 查找并打开第一个手柄
		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				controller = SDL_GameControllerOpen(i);
				if (controller) {
					std::cout << "Controller connected!" << std::endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			PrintTime();
			std::cout << "Controller not found!" << std::endl;
			SDL_Delay(10000);
		}
	}
	

	if (!controller) {
		std::cerr << "No controller found!" << std::endl;
		SDL_Quit();
		return -1;
	}
	EnableChinese();
	SDL_Event event;
	bool running = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	Cursor cursor;
	Keyboard keyboard;
	BaseCtrl* baseCtrl = &cursor;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					baseCtrl->AButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
					baseCtrl->BButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
					baseCtrl->XButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
					baseCtrl->YButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
					baseCtrl->LButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
					baseCtrl->RButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) {
					CheckBatteryPower();
					if (baseCtrl == &cursor){
						std::cout << "模式改变，现在：keyboard" << std::endl;
						baseCtrl = &keyboard;
					}	
					else {
						std::cout << "模式改变，现在：cursor" << std::endl;
						baseCtrl = &cursor;
					}
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_MISC1) {
					// capture
					CaptureScreen();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
					baseCtrl->UpButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
					baseCtrl->DownButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
					baseCtrl->LeftButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
					baseCtrl->RightButton();
				}
			}
			else if (event.type == SDL_CONTROLLERAXISMOTION) {
				// 获取摇杆输入
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX || event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
					// 获取当前时间
					auto currentTime = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> deltaTime = currentTime - lastTime;
					lastTime = currentTime;
					// 计算移动
					int xAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					int yAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
					if (std::abs(xAxis) < 10000)xAxis = 0;
					if (std::abs(yAxis) < 10000)yAxis = 0;
					if (xAxis == 0 && yAxis == 0)continue;
					baseCtrl->MoveLeftStick(xAxis * deltaTime.count(), yAxis * deltaTime.count());
				}
				else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					// 获取当前时间
					auto currentTime = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> deltaTime = currentTime - lastTime;
					lastTime = currentTime;
					// 计算移动
					int xAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
					int yAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					if (std::abs(xAxis) < 10000)xAxis = 0;
					if (std::abs(yAxis) < 10000)yAxis = 0;
					if (xAxis == 0 && yAxis == 0)continue;
					baseCtrl->MoveLeftStick(xAxis * deltaTime.count(), yAxis * deltaTime.count());
				}
			}
		}
		int zrValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		// ZR 按键值通常在 0 到 32767 之间
		if (zrValue > 16000) {  // 可以根据需要调整阈值
			baseCtrl->ZRButton();
			SDL_Delay(100);
		}
		int zlValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		if (zlValue > 16000) {  // 可以根据需要调整阈值
			baseCtrl->ZLButton();
			SDL_Delay(100);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_Quit();

	return 0;
}
