#pragma once
#include "../Include/CGridCell.h"
#include "Globals.h"
#include "CApp.h"
#include <vector>
#include <fstream>
using namespace std;

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
	int filas = 2;
	int columnas = 2;
	float **m_cellPosition;
	bool m_initialize;
	vector <CVector3> centerPoints;
	vector <CVector3> centerPoints2;


	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;
	CVector3 m_objectPosition;

	CVector3 pos = { 0,0,0 };
	CVector3 pos2 = { 0,0,0 };
	vector <CVector3> savePos;
	vector <CGridCell> newsavePos;


	float incrementoX1 = 1.76;
	float incrementoY = 1.7 - .17;
	float incrementoX2 = 1.7 / 2;
	//int filas = 10;
	//int columnas = 10;
	float totalTamanoX = incrementoX1 * columnas;
	float totalTamanoY = incrementoY * filas;
	float InicialX = (totalTamanoX / 2) - totalTamanoX;
	float InicialY = (totalTamanoY / 2) - totalTamanoY;
	int count = 0;

	float R = 194.0;
	float G = 54.0;
	float B = 22.0;

	//float R = ((float) rand());
	//float G = 54.0;
	//float B = 22.0;


	float color[3] = { R,G,B };
	float color2[3] = { 255.0f, 177.0, 44.0f };

public:
	void createSavePosition();
	void savePostionForNode(vector <CVector3> &Positons);
	void saveCenterPoints(CVector3 Positions);


	void moveCamera();
	void renderGrid();
private:

};
