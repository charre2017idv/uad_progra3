#include <math.h>

class CGridCell
{
public:
	CGridCell();
	~CGridCell();

public:
	unsigned int m_ShaderID;
	unsigned int m_geoVAOID;

	bool loaded;
	int m_numFacesRender = 6;
	int size = 1;
	float width = sqrt(3) * size;
	float height = 2 * size;
	float centerWidth = width / 2;
	float centerHeight = height / 2;

	bool initializeMenu() { return false; }

	int numAristas = 6;
	int numVertices = 7;
	//int numFaces = (12 * 2) + 2;
	float anguloY = 360 / 6;
	float Z1 = 0.25;
	float Z2 = -0.25;
	float PI = 3.14159245358979323846;

	float Vertex_X = 0.0f;
	float Vertex_Y = 0.0f;
	float Vertex_Z = 0.0f;

	int numVertice = 0;
	int vertice = 0;
	int nV = 0;
	int fila, col;
	int num = 0;
	int num1 = 0;
	// ============================== SECTION
	float *vdata = new float[numVertices * 3];

	int **Vertex = new int *[3]; // Registro del indice de los vertices
	unsigned short vIndices[6 * 3];
	float nData[6 * 3];
	unsigned short nIndice[6 * 3];
public:
	void Cell();
};

