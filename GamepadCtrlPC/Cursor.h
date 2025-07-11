#pragma once
#include "BaseCtrl.h"
class Cursor : public BaseCtrl {
public:
	void MoveLeftStick(int x, int y) override;
	void MoveRightStick(int x, int y) override;
	void AButton() override;
	void BButton() override;
	void XButton() override;
	void YButton() override;
	void UpButton() override;
	void DownButton() override;
	void LeftButton() override;
	void RightButton() override;
	void LButton() override;
	void RButton() override;
	void ZLButton() override;
	void ZRButton() override;

private:
	float leftSensitivity = 0.1;
	float deltaLeftSensitivity = 0.03;
	float rightSensitivity = 1;
	float deltaRightSensitivity = 0.3;

	// 成员变量：存储当前速度（每帧增减）
	float speed = 0.0f;
	// 可调参数
	
	float acceleration = 0.1f;     // 加速度（每帧速度增加多少）
	float maxSpeed = 1.0f;        // 最大速度
	float decay = 0.2f;            // 松开摇杆后速度衰减率


};