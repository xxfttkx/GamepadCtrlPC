#include <SDL2/SDL.h>
#include <windows.h>
#include <iostream>
#include <chrono>
#include "BaseCtrl.h"
#include "Cursor.h"
#include "KeyBoard.h"




int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GameController* controller = nullptr;

	// 查找并打开第一个手柄
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				std::cout << "Controller connected!" << std::endl;
				break;
			}
		}
	}

	if (!controller) {
		std::cerr << "No controller found!" << std::endl;
		SDL_Quit();
		return -1;
	}

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
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
					// baseCtrl->RButton(); 
					// todo
					if (baseCtrl == &cursor)
						baseCtrl = &keyboard;
					else
						baseCtrl == &cursor;
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
					if (std::abs(xAxis) < 10000 && std::abs(yAxis) < 10000)
						continue;
					baseCtrl->MoveLeftStick(xAxis * deltaTime.count(), yAxis * deltaTime.count());
				}
				else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					// 获取右摇杆的值
					int axisValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					if (std::abs(axisValue) < 10000)
						continue;
					// 根据右摇杆的值计算滚轮的滚动量
					int scrollAmount = axisValue / 32767.0 * 120; // 滚动量，120是常用的每次滚动的单位
					baseCtrl->MoveRightStick(0,-scrollAmount);
				}
			}
		}
		int zrValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		// ZR 按键值通常在 0 到 32767 之间
		if (zrValue > 16000) {  // 可以根据需要调整阈值
			baseCtrl->ZRButton();
			SDL_Delay(100);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_Quit();

	return 0;
}
