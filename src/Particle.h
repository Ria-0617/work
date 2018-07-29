#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"

class Particle {
private:
	ci::Vec3f position[30];
	ci::Vec3f angle[30];
	const float speed;

	ci::Vec3f right, up;
	ci::Matrix44f mat;

	int surviveTime;

	ci::gl::Texture image;

public:
	Particle(ci::gl::Texture texture, ci::Vec3f pos);
	~Particle();

	void drawBillboardTexture(const ci::Vec3f& pos, const ci::Vec2f& scale, float rotationDegrees,
		const ci::Vec3f& bbRight, const ci::Vec3f& bbUp, const ci::gl::Texture& texture, const ci::Area& area);

	void UpDate(const ci::Matrix44f& m, const ci::Vec3f& r, const ci::Vec3f& u);
	void Draw();
	bool IsDead();
};