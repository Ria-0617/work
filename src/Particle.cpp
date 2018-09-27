#include "Particle.h"

using namespace ci;
using namespace ci::app;

Particle::Particle(gl::Texture texture, Vec3f pos) :speed(0.5f) {
	image = texture;

	for (int i = 0; i < MAX; ++i) {
		position[i] = pos;
		angle[i] = Vec3f(randFloat(-1.f, 1.f), randFloat(-1.f, 1.f), randFloat(-1.f, 1.f));
	}

	surviveTime = 60;

	data = new int[MAX];
}

Particle::~Particle() {
	delete data;
}

void Particle::DrawBillboardTexture(const Vec3f& pos, const Vec2f& scale, float rotationDegrees,
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

void Particle::Swap(int *a, int *b) {
	int n = *a; *a = *b; *b = n;
}

void Particle::QuickSort(int *s, int *e) {
	if (s == e)return;

	int pivot = *s;

	int *p1 = s, *p2 = e;

	while (true)
	{
		if (*p1 >= pivot && *p2 < pivot) {
			Swap(p1, p2);
		}

		if (*p1 < pivot) {
			++p1;
			if(p1 == p2)break;
		}

		if (*p2 >= pivot) {
			--p2;
			if (p1 == p2)break;
		}
	}

	if (p1 != s && *p1 >= pivot)--p1;
	else if (p2 != e)++p2;

	QuickSort(s, p1);
	QuickSort(p2, e);
}

void Particle::UpDate(const Vec3f& pos, const Vec3f& r, const Vec3f& u) {
	right = Matrix44f::identity().transformVec(r);
	up = Matrix44f::identity().transformVec(u);

	for (int i = 0; i < MAX; ++i) {
		position[i] += angle[i] * speed;
	}

	for (int i = 0; i < MAX; ++i) {
		data[i] = position[i].z - pos.z;
	}

	QuickSort(&data[0], &data[MAX - 1]);

	

	surviveTime -= 1;
}

void Particle::Draw() {
	gl::enableAlphaBlending();

	const int cut = 100;
	/*const int index = 10 - surviveTime / 6;
	int tx = (index % 7) * cut;
	int ty = (index / 7) * cut;
*/
	int tx = 4 * cut;
	int ty = 0;

	for (int i = 0; i < MAX; ++i) {
		DrawBillboardTexture(position[i], /*scale = */ Vec2f(5.f, 5.f), /*rotationDegree = */0,
			right, up, image, Area(tx, ty, tx + cut, ty + cut));
	}

	gl::disableAlphaBlending();
}

bool Particle::IsDead() {
	return surviveTime <= 0;
}