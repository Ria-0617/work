#include "Bullet.h"

using namespace ci;
using namespace ci::app;

Bullet::Bullet(Vec3f playerPos,Matrix44f m) :radius(0.2f), speed(3.f) {
	direction = m;
	position = playerPos;
	surviveTime = 30;
}

Bullet::~Bullet() {

}

void Bullet::UpDate() {
	position += direction * Vec3f(0.f, 0.f, 1.f) * speed + Vec3f(0.f, 0.f, 0.f);

	surviveTime -= 1;
}

void Bullet::Draw() {
	gl::drawSphere(position, radius);
}

bool Bullet::IsDead() {
	return surviveTime <= 0;
}