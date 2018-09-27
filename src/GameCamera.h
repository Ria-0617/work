#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder\Camera.h"
#include "JoyController.h"
#include "Player.h"
#include "Func.h"

class GameCamera :public JoyController {
private:
	ci::CameraPersp camera;
	float fov;

	ci::Vec3f target;
	ci::Vec3f offset;
	ci::Vec3f position;
	ci::Vec3f rotation;
	ci::Vec3f cameraCurrentPosition;
	float rotationSpeed;
	float limitAngle;

	ci::Matrix44f matrix;

	ci::Vec3f right, up;
	ci::Matrix44f viewMatrix;

public:
	GameCamera(ci::Vec3f, int, int);
	~GameCamera();

	void UpDate(ci::Vec3f targetPos);
	void Draw();

	ci::Vec3f GetPosition() {
		return position;
	}

	ci::Matrix44f GetMatrix() {
		return matrix;
	};

	ci::Vec3f GetRight() {
		return right;
	}
	ci::Vec3f GetUp() {
		return up;
	}
	ci::Matrix44f GetViewMatrix() {
		return viewMatrix;
	}
};