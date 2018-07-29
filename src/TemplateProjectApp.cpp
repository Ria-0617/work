#include "TemplateProjectApp.h"

using namespace ci;
using namespace ci::app;

void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	ObjLoader loader = ObjLoader(loadAsset("model.obj"));
	loader.load(&enemyMesh, boost::logic::indeterminate, boost::logic::indeterminate, false);
	enemyVboMesh = gl::VboMesh::create(enemyMesh);

	billBoardTexture = loadImage(loadAsset("Battle_Effect-02.png"));

	player = new Player();
	camera1 = new GameCamera(player->GetPos(), getWindowWidth(), getWindowHeight());
	ui = new UI(getWindowWidth(), getWindowHeight());

	for (int i = 1; i < 100; ++i)
		boids.push_back(Boid(enemyVboMesh));

	gl::enable(GL_COLOR_MATERIAL);
}

void TemplateProjectApp::shutdown() {
	delete camera1;
	delete player;
	delete ui;
}

void TemplateProjectApp::update()
{
	camera1->UpDate(player->GetPos());
	player->UpDate(camera1->GetMatrix());
	ui->UpDate();

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		itr->Move(boids);
	}

	if (IsPressedButton(R1)) {
		shotTime += 1;
		if (shotTime % 5 == 0)
			bullets.push_back(Bullet(player->GetPos(), camera1->GetMatrix()));
	}
	else
		shotTime = 0;

	for (auto itr = bullets.begin(); itr != bullets.end(); ++itr) {
		itr->UpDate();
		if (itr->IsDead())
			itr = bullets.erase(itr);

		for (auto itr2 = boids.begin(); itr2 != boids.end(); ++itr2) {
			// 玉と敵の当たり判定
			if (MyFanc::OutCircleCollider(itr->GetPosition(), itr->GetRadius(), itr2->GetPosition(), itr2->GetRadius())) continue;
			particles.push_back(Particle(billBoardTexture, itr2->GetPosition()));

			itr = bullets.erase(itr);
			itr2 = boids.erase(itr2);
			ui->PlusScore(100);

			if (boids.size() > enemyMaxNum)continue;
			//boids.push_back(Boid(enemyVboMesh, itr2->GetPosition()));
		}
	}

	for (auto itr = particles.begin(); itr != particles.end(); ++itr) {
		itr->UpDate(camera1->GetMatrix(), camera1->getRight(), camera1->getUp());

		if (itr->IsDead())
			itr = particles.erase(itr);
	}
}

void TemplateProjectApp::draw()
{
#pragma region enable
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	//gl::enable(GL_LIGHTING);
#pragma endregion
	// clear out the window with black
	gl::clear(Color(0.0f, 0.0f, 0.0f));

	camera1->Draw();

	// templateField
#if 1
	for (int x = 0; x < 30; ++x) {
		for (int z = 0; z < 30; ++z) {
			color = x + z & 0x01 ? Color(0.f, 1.f, 1.f) : Color(0.f, 0.0f, 1.f);
			gl::color(color);
			gl::drawCube(Vec3f(0.f + x, -5.f, 0.f + z), Vec3f(1.f, 0.1f, 1.f));
		}
	}
#endif	

	player->Draw();

	// 玉
	for (auto itr = bullets.begin(); itr != bullets.end(); ++itr)
		itr->Draw();

	// 敵
	for (auto itr = boids.begin(); itr != boids.end(); ++itr)
		itr->Draw();

	// パーティクル
	for (auto itr = particles.begin(); itr != particles.end(); ++itr)
		itr->Draw();

#pragma region disable
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	//gl::disable(GL_LIGHTING);
#pragma endregion

	ui->Draw();
}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)