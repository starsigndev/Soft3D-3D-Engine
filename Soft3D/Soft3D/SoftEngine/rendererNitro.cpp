#include "rendererNitro.h"
#include "SoftApp.h"
#include <iostream>
#include "pixelMap.h"
#include "nodeCamera.h"
#include "nodeLight.h"
#include <algorithm>
#include <list>
#include "pixelMap.h"
#include <chrono>
#include "depthBuffer.h"
#include <windows.h>
#include <math.h>

rendererNitro* rendererNitro::mThis = nullptr;
std::vector<rtri> rendererNitro::final_tris;

float renW, renH;


rendererNitro::rendererNitro() {

	m_Projection = matrix4();
	m_Projection.toProjection(70, (float)SoftApp::m_This->getHeight() / (float)SoftApp::m_This->getWidth(), 0.00001, 20);
	mThis = this;
	renW = SoftApp::m_This->getWidth();
	renH = SoftApp::m_This->getHeight();

}

void rendererNitro::beginRender() {

	render_tris.clear();

}


void rendererNitro::renderTriangle(vertex& v0, vertex& v1, vertex& v2, matrix4& model_mat, nodeCamera* cam, nodeLight* l, pixelMap* pix, color& col)
{
	rtri t;
	t.v0 = v0;
	t.v1 = v1;
	t.v2 = v2;
	t.map = pix;
	t.c0 = col;
	t.world = model_mat;
	t.view = cam->getWorldMat();
	render_tris.push_back(t);

}

/*
void rendererNitro::drawTriangle(vertex& v0, vertex& v1, vertex& v2, color& col, pixelMap* tex,matrix4& mat,nodeCamera* cam,nodeLight* l)
{

	matrix4 world = mat;
	matrix4 view = cam->getWorldMat();
	matrix4 proj = matrix4();
	proj.toProjection(70, (float)SoftApp::m_This->getHeight() / (float)SoftApp::m_This->getWidth(), 0.00001, 20);
	matrix4 worldView = world.multi(view);
	matrix4 transform = worldView.multi(proj);

	rtri t;
	t.v0 = v0;
	t.v1 = v1;
	t.v2 = v2;
	t.map = tex;
	final_tris.push_back(t);

}
*/



void rendererNitro::endRender() {

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
//	glLoadMatrixf()

	//glBegin(GL_TRIANGLES);
//	glFrontFace(GL_CCW);

	for (auto& tri : render_tris) {

		auto modelView = tri.view.multi(tri.world);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(&modelView.m[0][0]);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLoadMatrixf(&m_Projection.m[0][0]);

		glColor4f(0, 1, 1, 1);

		glBegin(GL_TRIANGLES);

		glVertex3f(tri.v0.pos.x,tri.v0.pos.y,tri.v0.pos.z);
		glVertex3f(tri.v1.pos.x,tri.v1.pos.y,tri.v1.pos.z);
		glVertex3f(tri.v2.pos.x, tri.v2.pos.y, tri.v2.pos.z);

		glEnd();


	}

	glEnd();

}
