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

	// ���Ҳ��򿪵�һ���ֱ�
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
				// ��ȡҡ������
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX || event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
					// ��ȡ��ǰʱ��
					auto currentTime = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> deltaTime = currentTime - lastTime;
					lastTime = currentTime;
					// �����ƶ�
					int xAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					int yAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
					if (std::abs(xAxis) < 10000 && std::abs(yAxis) < 10000)
						continue;
					baseCtrl->MoveLeftStick(xAxis * deltaTime.count(), yAxis * deltaTime.count());
				}
				else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					// ��ȡ��ҡ�˵�ֵ
					int axisValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					if (std::abs(axisValue) < 10000)
						continue;
					// ������ҡ�˵�ֵ������ֵĹ�����
					int scrollAmount = axisValue / 32767.0 * 120; // ��������120�ǳ��õ�ÿ�ι����ĵ�λ
					baseCtrl->MoveRightStick(0,-scrollAmount);
				}
			}
		}
		int zrValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		// ZR ����ֵͨ���� 0 �� 32767 ֮��
		if (zrValue > 16000) {  // ���Ը�����Ҫ������ֵ
			baseCtrl->ZRButton();
			SDL_Delay(100);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_Quit();

	return 0;
}
