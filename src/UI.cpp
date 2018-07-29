#include "UI.h"

using namespace ci;
using namespace ci::app;
using namespace std;

UI::UI(int windowWidth, int windowHeght) {
	score = 0;
	timer = 3600;

	uiCamera = CameraOrtho(0.f, windowWidth, windowHeght, 0.f, -1.f, 1.f);
	uiCamera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	uiCamera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));

	customFont = Font(loadAsset("AndrewsQueen.ttf"), 48.f);
}

UI::~UI() {

}

gl::Texture UI::TextSetUp(string txt, TextBox::Alignment centerPos, Vec2i size) {
	TextBox tBox = TextBox().alignment(centerPos).font(customFont).size(Vec2i(size)).text(txt);
	tBox.setColor(Color(1.f, 1.f, 1.f));
	tBox.setBackgroundColor(ColorA(0.f, 0.f, 0.f, 0.f));

	return gl::Texture(tBox.render());
}

void UI::UpDate() {
	if (timer > 0)
		timer -= 1;

	scoreText = "Score : " + std::to_string(score);
	scoreTexture = TextSetUp(scoreText, TextBox::LEFT, Vec2i(getWindowWidth(), /*size = */100));

	timerText = std::to_string(timer / 60);
	timerTexture = TextSetUp(timerText, TextBox::CENTER, Vec2i(getWindowWidth(), /*size = */100));
}

void UI::Draw() {
	gl::enableAlphaBlending();

	gl::color(Color(1.f, 1.f, 1.f));
	gl::setMatrices(uiCamera);

	if (scoreTexture)
		gl::draw(scoreTexture, Vec2i(0, 0));

	if (timerTexture)
		gl::draw(timerTexture, Vec2i(0, 0));

	gl::disableAlphaBlending();
}