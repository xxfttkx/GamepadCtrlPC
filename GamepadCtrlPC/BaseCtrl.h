#pragma once
class BaseCtrl
{
public:
	virtual ~BaseCtrl() = default;
	virtual void MoveLeftStick(int x,int y) = 0;
	virtual void MoveRightStick(int x, int y) = 0;
	virtual void AButton() = 0;
	virtual void BButton() = 0;
	virtual void XButton() = 0;
	virtual void YButton() = 0;
	virtual void UpButton() = 0;
	virtual void DownButton() = 0;
	virtual void LeftButton() = 0;
	virtual void RightButton() = 0;
	virtual void LButton() = 0;
	virtual void RButton() = 0;
	virtual void ZLButton() = 0;
	virtual void ZRButton() = 0;
private:

};