#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/Vbo.h"

#include <list>
#include "Func.h"

class Boid {
	ci::Vec3f position;

	ci::Vec3f angle;
	ci::Vec3f direction;

	const float radius;

	const float viewAngleRange;
	const float viewDistanceRange;

	ci::gl::VboMeshRef vboMesh;
protected:
	bool OutOfViewRange(Boid&, float, float);

	ci::Vec3f Separate(std::list<Boid>&);
	ci::Vec3f Alignment(std::list<Boid>&);
	ci::Vec3f Cohesion(std::list<Boid>&);

public:
	Boid(ci::gl::VboMeshRef);
	Boid(ci::gl::VboMeshRef, ci::Vec3f);

	ci::Vec3f GetPosition() {
		return position;
	}

	float GetRadius() {
		return radius;
	}

	void Move(std::list<Boid>&);

	void Draw();
};
