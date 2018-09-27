#include "GameCamera.h"

using namespace ci;
using namespace ci::app;

GameCamera::GameCamera(Vec3f targetPos, int windowWidth, int windowHeight) {
	fov = 35.f;

	target = targetPos;
	offset = Vec3f(0.f, 0.f, -8.f);
	position = targetPos + offset;
	rotation = Vec3f(0.f, 0.f, 0.f);
	cameraCurrentPosition = position;
	rotationSpeed = 3.f;
	limitAngle = 45.f;
	matrix = Matrix44f::identity();

	right = Vec3f(0, 0, 0);
	up = Vec3f(0, 0, 0);

	viewMatrix = Matrix44f::identity();

	camera = CameraPersp(windowWidth, windowHeight, fov, 0.1f, 100.f);
	camera.setEyePoint(position);
	camera.setCenterOfInterestPoint(target);
};

GameCamera::~GameCamera() {

}

void GameCamera::UpDate(Vec3f targetPos) {

	if (IsMove(joy.dwRpos, joy.dwZpos,/*minValue = */0.25f)) {
		rotation += Vec3f(-StickValue(joy.dwRpos), StickValue(joy.dwZpos), 0.f)*rotationSpeed;

		MyFanc::Clamp(rotation.x, -limitAngle, limitAngle);

		matrix = Matrix44f::createRotation(MyFanc::ToRadians(rotation));
	}

	cameraCurrentPosition = targetPos + matrix * offset;
	Vec3f t = targetPos + matrix * Vec3f(0.f, 0.f, 1.f);

	camera.setEyePoint(cameraCurrentPosition + Vec3f(0.f, 2.f, 0.f));
	camera.setCenterOfInterestPoint(t + Vec3f(0.f, 2.f, 0.f));

	camera.getBillboardVectors(&right, &up);
	viewMatrix = camera.getModelViewMatrix();
}

void GameCamera::Draw() {
	gl::setMatrices(camera);
}