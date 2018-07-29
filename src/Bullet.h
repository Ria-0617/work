#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class Bullet {
private:
	ci::Vec3f position;
	ci::Matrix44f direction;
	const float radius;
	const float speed;
	int surviveTime;

public:
	Bullet(ci::Vec3f playerPos, ci::Matrix44f m);
	~Bullet();

	ci::Vec3f GetPosition() {
		return position;
	}

	float GetRadius() {
		return radius;
	}

	void UpDate();
	void Draw();
	bool IsDead();
};
