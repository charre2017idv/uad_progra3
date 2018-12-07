#pragma once
#include "CQuadTreeNode.h"
#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "CCamera.h"
#include <vector>
#include <iostream>
// En la camara si esta dentro de los rango que haga el proceso
class CQuadTree: public CApp
{
public:
	CQuadTree();
	CQuadTree(int window_width, int window_height);
	~CQuadTree();
public:
	CCamera Cam;
//	CQuadTreeNode Nodo;
	CVector3 m_objectPosition;
	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;
	bool m_initialize;

public:
	void initialize();
	void run();
	void update(double deltatime);
	void render();
	bool initializeMenu() { return false; }

	void renderCam();
};

