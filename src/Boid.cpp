#include "Boid.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Boid::Boid(ci::gl::VboMeshRef vbo) :radius(1.f), viewAngleRange(toRadians(45.f)), viewDistanceRange(10.f), vboMesh(vbo){
	position = Vec3f(randFloat(-50.f, 50.f), randFloat(-50.f, 50.f), randFloat(-50.f, 50.f));

	angle = MyFanc::ToRadians(Vec3f(randFloat(0.f, 360.f), randFloat(0.f, 360.f), randFloat(0.f, 360.f)));
	direction = Matrix44f::createRotation(angle) * Vec3f(1.f, 0.f, 0.f);
}

Boid::Boid(ci::gl::VboMeshRef vbo, Vec3f pos) :Boid(vbo) {
	position = pos;
}

bool Boid::OutOfViewRange(Boid& boid, float viewAngleRange, float viewDistanceRange) {
	Vec3f neighbors = (boid.position - position).normalized();

	if (direction.dot(neighbors) < viewAngleRange || position.distance(boid.position) > viewDistanceRange) {
		return true;
	}
	return false;
}

Vec3f Boid::Separate(list<Boid>&boids) {
	Vec3f relativePosition = Vec3f(0, 0, 0);
	Vec3f toAgent;

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (position.distance(itr->position) > viewDistanceRange) continue;

		toAgent = (position - itr->position).safeNormalized();
		relativePosition += toAgent;
	}

	return relativePosition;
}

Vec3f Boid::Alignment(list<Boid>&boids) {
	int neiborCount = 0;
	Vec3f ralativeAngle = Vec3f(0, 0, 0);

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (OutOfViewRange(*itr, viewAngleRange, viewDistanceRange))continue;

		ralativeAngle += itr->angle;

		++neiborCount;
	}

	if (neiborCount > 0) {
		ralativeAngle /= neiborCount;
	}

	angle = ralativeAngle;
	direction = Matrix44f::createRotation(angle) * Vec3f(1.f, 0.f, 0.f);

	return direction;
}


Vec3f Boid::Cohesion(list<Boid>&boids) {
	Vec3f centerPos = Vec3f(0, 0, 0);

	int neiborCount = 0;

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (OutOfViewRange(*itr, viewAngleRange, viewDistanceRange))continue;

		centerPos += itr->position;
		++neiborCount;
	}
	
	if (neiborCount > 0) {
		centerPos /= neiborCount;
	}

	return (centerPos - position).safeNormalized();
}

void Boid::Move(list<Boid>& boids) {
	Vec3f v;
	v = position;
	v += Separate(boids);
	v += Alignment(boids);
	v += Cohesion(boids);

	position += ((v - position) * 0.08f);

	MyFanc::MoveLimit(position,/*limitValue = */50, /*moveValue = */100);
}

void Boid::Draw() {
	gl::pushModelView();
	gl::translate(position);
	gl::rotate(Matrix44f::createRotation(angle));
	gl::draw(vboMesh);
	gl::popModelView();
}