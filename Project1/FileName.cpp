#include <SDL2/SDL.h>
#include <windows.h>
#include <iostream>
#include <chrono>

float sensitivity = 0.3;  // 调整灵敏度
float deltaSensitivity = 0.05;

// 鼠标移动函数
void MoveMouse(int xDelta, int yDelta) {
	POINT p;
	GetCursorPos(&p);
	SetCursorPos(p.x + xDelta, p.y + yDelta);
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

void AButton()
{
	// std::cout << "A Button pressed!" << std::endl;
	SimulateMouseClick();  // 模拟点击
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
	SimulateMouseClick();  // 模拟点击
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

					// 计算鼠标移动量
					int xDelta = static_cast<int>(xAxis * sensitivity * deltaTime.count());
					int yDelta = static_cast<int>(yAxis * sensitivity * deltaTime.count());
					if (xDelta != 0 || yDelta != 0)
					{
						std::cout << "xDelta: " << xDelta << ", yDelta: " << yDelta << std::endl;
						MoveMouse(xDelta, yDelta);
					}
					else
					{
						// 休眠以减少 CPU 使用率
						// SDL_Delay(100);
					}
				}
				else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
					// 获取右摇杆的值
					int axisValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					if (std::abs(axisValue) < 10000)
						continue;
					// 根据右摇杆的值计算滚轮的滚动量
					int scrollAmount = axisValue / 32767.0 * 120; // 滚动量，120是常用的每次滚动的单位

					// 使用负值向下滚动，正值向上滚动
					SimulateMouseWheelScroll(-scrollAmount);
				}
			}
		}
		int zrValue = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		// ZR 按键值通常在 0 到 32767 之间
		if (zrValue > 16000) {  // 可以根据需要调整阈值
			ZRButton();
			SDL_Delay(100);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_Quit();

	return 0;
}
