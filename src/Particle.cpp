#include "Particle.h"

using namespace ci;
using namespace ci::app;

Particle::Particle(gl::Texture texture, Vec3f pos) :speed(0.5f) {
	image = texture;

	for (int i = 0; i < 30; ++i) {
		position[i] = pos;
		angle[i] = randVec3f() * 1.f;
	}

	surviveTime = 60;
}

Particle::~Particle() {

}

void Particle::drawBillboardTexture(const Vec3f& pos, const Vec2f& scale, float rotationDegrees,
	const Vec3f& bbRight, const Vec3f& bbUp, const gl::Texture& texture, const Area& area) {
	texture.enableAndBind();

	glEnableClientState(GL_VERTEX_ARRAY);
	Vec3f verts[4];
	glVertexPointer(3, GL_FLOAT, 0, &verts[0].x);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// UVŒvŽZ
	auto size = texture.getSize();
	GLfloat texCoords[8] = {
		area.x1 / float(size.x), area.y1 / float(size.y),
		area.x1 / float(size.x), area.y2 / float(size.y),
		area.x2 / float(size.x), area.y1 / float(size.y),
		area.x2 / float(size.x), area.y2 / float(size.y)
	};
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	float sinA = math<float>::sin(toRadians(rotationDegrees));
	float cosA = math<float>::cos(toRadians(rotationDegrees));

	verts[0] = pos + bbRight * (-0.5f * scale.x * cosA - 0.5f * sinA * scale.y) + bbUp * (-0.5f * scale.x * sinA + 0.5f * cosA * scale.y);
	verts[1] = pos + bbRight * (-0.5f * scale.x * cosA - -0.5f * sinA * scale.y) + bbUp * (-0.5f * scale.x * sinA + -0.5f * cosA * scale.y);
	verts[2] = pos + bbRight * (0.5f * scale.x * cosA - 0.5f * sinA * scale.y) + bbUp * (0.5f * scale.x * sinA + 0.5f * cosA * scale.y);
	verts[3] = pos + bbRight * (0.5f * scale.x * cosA - -0.5f * sinA * scale.y) + bbUp * (0.5f * scale.x * sinA + -0.5f * cosA * scale.y);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	texture.disable();
}

void Particle::UpDate(const Matrix44f& m, const Vec3f& r, const Vec3f& u) {
	mat = Matrix44f::identity();
	//mat.invert();
	right = mat.transformVec(r);
	up = mat.transformVec(u);

	for (int i = 0; i < 30; ++i) {
		position[i] += angle[i] * speed;
	}

	surviveTime -= 1;
}

void Particle::Draw() {
	gl::enableAlphaBlending();

	const int cut = 100;
	int index = 10 - surviveTime / 6;
	int tx = (index % 7) * cut;
	int ty = (index / 7) * cut;

	for (int i = 0; i < 30; ++i) {
		drawBillboardTexture(position[i], /*scale = */ Vec2f(5.f, 5.f), /*rotationDegree = */0,
			right, up, image, Area(tx, ty, tx + cut, ty + cut));
	}

	gl::disableAlphaBlending();
}

bool Particle::IsDead() {
	return surviveTime <= 0;
}