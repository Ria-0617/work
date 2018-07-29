#include "JoyController.h"

using namespace ci;
using namespace ci::app;

JoyController::JoyController(): maxValue(255.f) {

}

void JoyController::SetUp() {

	joy.dwSize = sizeof JOYINFOEX;
	joy.dwFlags = JOY_RETURNALL;

	// ゲームパッドが接続しているか確認
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //サポートされているジョイスティックの数を返す
		if (JOYERR_NOERROR == joyGetPosEx(i, &joy))
			console() << i << std::endl;
	}
}

// 正規化
float JoyController::StickValue(unsigned long value) {
	return 1 - 2 * (value & 0xff) / maxValue;
}

bool JoyController::IsMove(unsigned long valueX, unsigned long valueY, float minValue) {
	//0番のジョイスティックの情報を見る
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

// デバッグ用
// ボタン確認
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy)) { //0番のジョイスティックの情報を見る
		console() << "L_posX = " << StickValue(joy.dwXpos) << std::endl;
		console() << "L_posY = " << StickValue(joy.dwYpos) << std::endl;
		console() << "R_posX = " << StickValue(joy.dwZpos) << std::endl;     // 右スティック横
		console() << "R_posY = " << StickValue(joy.dwRpos) << std::endl;    // 右スティック縦
		console() << "L2 = " << joy.dwVpos << std::endl;    // L2
		console() << "R2 = " << joy.dwUpos << std::endl;    // R2
		console() << "Buttons = " << joy.dwButtons << std::endl;
		console() << ' ' << std::endl;
	}
	else {
		console() << "エラー" << std::endl;
	}
}