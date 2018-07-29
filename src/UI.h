#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder\Camera.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"

class UI{
	ci::CameraOrtho uiCamera;
	
	ci::Font customFont;

	int score;
	std::string scoreText;
	ci::gl::Texture scoreTexture;
	
	int timer;
	std::string timerText;
	ci::gl::Texture timerTexture;

public:
	UI(int windowWidth, int windowHeght);
	~UI();

	void PlusScore(int point) {
		score += point;
	}

	ci::gl::Texture TextSetUp(std::string, ci::TextBox::Alignment, ci::Vec2i);
	void UpDate();
	void Draw();
};