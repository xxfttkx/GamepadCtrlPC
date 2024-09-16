#include <SDL2/SDL.h>
#include <windows.h>
#include <iostream>
#include <chrono>

float sensitivity = 0.3;  // ����������
float deltaSensitivity = 0.05;

// ����ƶ�����
void MoveMouse(int xDelta, int yDelta) {
	POINT p;
	GetCursorPos(&p);
	SetCursorPos(p.x + xDelta, p.y + yDelta);
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

void AButton()
{
	// std::cout << "A Button pressed!" << std::endl;
	SimulateMouseClick();  // ģ����
}
void BButton()
{
	SimulateRightClick();
}
void XButton()
{
	sensitivity -= deltaSensitivity;
}
void YButton()
{
	sensitivity += deltaSensitivity;
}
void RButton()
{
	// std::cout << "R Button pressed!" << std::endl;
	SimulateMouseClick();  // ģ����
}
void ZRButton()
{
	// std::cout << "ZR Button pressed!" << std::endl;
	SimulateMouseClick();
}
void Print(std::string s)
{
	std::cout << s << std::endl;
}


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
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					AButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
					BButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
					XButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
					YButton();
				}
				else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
					RButton();
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

					// ��������ƶ���
					int xDelta = static_cast<int>(xAxis * sensitivity * deltaTime.count());
					int yDelta = static_cast<int>(yAxis * sensitivity * deltaTime.count());
					if (xDelta != 0 || yDelta != 0)
					{
						std::cout << "xDelta: " << xDelta << ", yDelta: " << yDelta << std::endl;
						MoveMouse(xDelta, yDelta);
					}
					else
					{
						// �����Լ��� CPU ʹ����
						// SDL_Delay(100);
					}
				}
				else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					// ��ȡ��ҡ�˵�ֵ
					int axisValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					if (std::abs(axisValue) < 10000)
						continue;
					// ������ҡ�˵�ֵ������ֵĹ�����
					int scrollAmount = axisValue / 32767.0 * 120; // ��������120�ǳ��õ�ÿ�ι����ĵ�λ

					// ʹ�ø�ֵ���¹�������ֵ���Ϲ���
					SimulateMouseWheelScroll(-scrollAmount);
				}
			}
		}
		int zrValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		// ZR ����ֵͨ���� 0 �� 32767 ֮��
		if (zrValue > 16000) {  // ���Ը�����Ҫ������ֵ
			ZRButton();
			SDL_Delay(100);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_Quit();

	return 0;
}
