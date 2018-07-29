#include "JoyController.h"

using namespace ci;
using namespace ci::app;

JoyController::JoyController(): maxValue(255.f) {

}

void JoyController::SetUp() {

	joy.dwSize = sizeof JOYINFOEX;
	joy.dwFlags = JOY_RETURNALL;

	// �Q�[���p�b�h���ڑ����Ă��邩�m�F
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //�T�|�[�g����Ă���W���C�X�e�B�b�N�̐���Ԃ�
		if (JOYERR_NOERROR == joyGetPosEx(i, &joy))
			console() << i << std::endl;
	}
}

// ���K��
float JoyController::StickValue(unsigned long value) {
	return 1 - 2 * (value & 0xff) / maxValue;
}

bool JoyController::IsMove(unsigned long valueX, unsigned long valueY, float minValue) {
	//0�Ԃ̃W���C�X�e�B�b�N�̏�������
	if (JOYERR_NOERROR != joyGetPosEx(JOYSTICKID1, &joy)) return false;

	if (StickValue(valueX) > minValue || StickValue(valueX) < -minValue ||
		StickValue(valueY) > minValue || StickValue(valueY) < -minValue) {
		return true;
	}
	else
		return false;
}

bool JoyController::IsPressedButton(unsigned long buttonNum) {
	if (JOYERR_NOERROR != joyGetPosEx(JOYSTICKID1, &joy)) return false;

	return joy.dwButtons == buttonNum ? true : false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �f�o�b�O�p
// �{�^���m�F
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy)) { //0�Ԃ̃W���C�X�e�B�b�N�̏�������
		console() << "L_posX = " << StickValue(joy.dwXpos) << std::endl;
		console() << "L_posY = " << StickValue(joy.dwYpos) << std::endl;
		console() << "R_posX = " << StickValue(joy.dwZpos) << std::endl;     // �E�X�e�B�b�N��
		console() << "R_posY = " << StickValue(joy.dwRpos) << std::endl;    // �E�X�e�B�b�N�c
		console() << "L2 = " << joy.dwVpos << std::endl;    // L2
		console() << "R2 = " << joy.dwUpos << std::endl;    // R2
		console() << "Buttons = " << joy.dwButtons << std::endl;
		console() << ' ' << std::endl;
	}
	else {
		console() << "�G���[" << std::endl;
	}
}