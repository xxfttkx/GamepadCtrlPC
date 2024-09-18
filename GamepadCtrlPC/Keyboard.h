#pragma once
#include "BaseCtrl.h"
class Keyboard : public BaseCtrl {
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
	float sensitivity = 0.1;
	float deltaSensitivity = 0.03;
};