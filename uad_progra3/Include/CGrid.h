#pragma once
#include "../Include/CGridCell.h"
#include "Globals.h"
#include "CApp.h"

class CGrid: public CApp
{
public:
	CGrid();
	CGrid(int window_width, int window_height);
	~CGrid();


	void paintGrid();
	CGridCell m_Cell;

	void initialize();
	void run();
	void update(double deltatime);
	void render();
	bool initializeMenu() { return false; }
public:
	// Center point
	int filas = 10;
	int columnas = 10;
	float **m_cellPosition;
	bool m_initialize;

	double m_currentDeltaTime;
	double m_objectRotation;
	CVector3 m_objectPosition;
	double m_rotationSpeed;
public:
	void createSavePosition();
private:

};
