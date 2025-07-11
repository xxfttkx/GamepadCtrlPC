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

	// ��Ա�������洢��ǰ�ٶȣ�ÿ֡������
	float speed = 0.0f;
	// �ɵ�����
	
	float acceleration = 0.1f;     // ���ٶȣ�ÿ֡�ٶ����Ӷ��٣�
	float maxSpeed = 1.0f;        // ����ٶ�
	float decay = 0.2f;            // �ɿ�ҡ�˺��ٶ�˥����


};