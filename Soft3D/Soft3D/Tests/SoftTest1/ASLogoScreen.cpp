#include "ASLogoScreen.h"
#include "Importer.h"
#include "sceneGraph.h"
#include "nodeEntity.h"
#include "gameInput.h"
#include "pixelMap.h"
#include "AudioSystem.h"
#include "QuickDraw.h"
#include "Texture2D.h"
float ang3 = 0.0f;
float logoz = 30;
void ASLogoScreen::Init() {
	auto imp = new Importer;

	logoMesh = imp->importEntity("data/mesh/logo/hdlogo1.fbx");
	tex1 = new pixelMap("data/tex1.png");
	auto mh = logoMesh->getMeshes();
	for (int i = 0; i < mh.size(); i++) {
		auto m = mh[i];
		m->setColorMap(tex1);
	}

	g1 = new sceneGraph;
	g1->addNode(logoMesh);
	cam = g1->getCam();
	cam->setPos(0, -3, -8);
	cam->setRotation(0, 0, 0);
	l1 = new nodeLight;
	l1->setPos(4, -10, 8);
	g1->addLight(l1);
	logoMesh->setRotation(0, 180, 0);
	logoMesh->setPos(0, 0, 0);
	ang3 = 360;
}



float camx1 = 0;
float camy1 = 0;
void ASLogoScreen::Update()
{
	//ang3 += 0.7f;
	camy1 += gameInput::mouseDeltaX * 0.1;
	camx1 += gameInput::mouseDeltaY * 0.1;



	//cam->setRotation(camx1, camy1, 0);

	//cam->move(-gameInput::moveX * 0.1, 0, gameInput::moveY * 0.1);

	//ent1->setPos(50, 0,200);



	float lx, lz;
	//ang3 = 270;

	lx = cosf(deg2rad(270)) * 15;
	lz = sinf(deg2rad(270)) * 15;

	l1->setPos(lx, 7, lz);

	ang3 = ang3 - 0.8f;
	if (ang3 < 0) {
		ang3 = 0;
	}
	
	float dis = ang3 / 360;

	logoz = 20 * dis;

	logoMesh->setRotation(ang3, ang3*2, 0);
	logoMesh->setPos(0, 0, logoz);
}

void ASLogoScreen::Render()
{

	g1->render();

}