#pragma once
#include <math.h>
class CGridCell
{
public:
	CGridCell();
	~CGridCell();

public: 
	bool loaded;
	int m_numFacesRender = 6;
	int size = 1;
	float width = sqrt(3) * size;
	float height = 2 * size;
	float centerWidth = width / 2;
	float centerHeight = height / 2;



	int numAristas = 6;
	int numVertices = 7;
	//int numFaces = (12 * 2) + 2;
	float anguloY = 360 / 6;
	float Z1 = 0.25;
	float Z2 = -0.25;
	float PI = 3.14159245358979323846;
	// ============================== SECTION

public:
	void createCell();
};

