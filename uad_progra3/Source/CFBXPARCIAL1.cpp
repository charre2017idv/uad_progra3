#include "../stdafx.h"
#include "../Include/CFBXPARCIAL1.h"
#include "../Include/CWideStringHelper.h"

#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

//#include "../Include/CFBXPARCIAL1.h"

/* */
CFBXPARCIAL1::CFBXPARCIAL1() :

	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
	cout << "Constructor: CFBXPARCIAL1()" << endl;
	// Initialize class member variables here
	// ======================================
	m_ShaderID = 0;
	m_geoVAOID = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	//
	// ======================================
}

/* */
CFBXPARCIAL1::CFBXPARCIAL1(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CFBXPARCIAL1(int window_width, int window_height)" << endl;
	// Initialize class member variables here
	// ======================================
	m_ShaderID = 0;
	m_geoVAOID = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;
	//
	// ======================================
}

/* */
CFBXPARCIAL1::~CFBXPARCIAL1()
{
	cout << "Destructor: ~CFBXPARCIAL1()" << endl;

	// Free memory allocated in this class instance here
	// =================================================
	//
	if (m_geoVAOID)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_ShaderID, &m_geoVAOID);
	}
	// =================================================
}

/* */
void CFBXPARCIAL1::initialize()
{
	// Initialize app-specific stuff here
	// ==================================
	//
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	char *vertexShaderToLoad = VERTEX_SHADER_3D_OBJECT;
	char *fragmentShaderToLoad = FRAGMENT_SHADER_3D_OBJECT;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(vertexShaderToLoad, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(fragmentShaderToLoad, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << vertexShaderToLoad << endl;
		cout << "  " << fragmentShaderToLoad << endl;

		m_initialize = false;
	}

	// Create the renderer
	getOpenGLRenderer()->createShaderProgram(
		&m_ShaderID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());

	if (m_ShaderID > 0)
	{
		// Show the figure
		//createPyramid();
		//createSphereTrail(6, 6);
		loadFBXModel("Test_Cube_Ascii.fbx");
	}

	// ==================================
}

/* */
void CFBXPARCIAL1::run()
{

	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_EMPTYAPP_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);
			// Set Distance of the camera
			getOpenGLRenderer()->setCameraDistance(100.0f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());


			// Initialize before the main loop, becouse it needs to charge the object after the library of OpenGl initialize 
			initialize();

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

/* */
void CFBXPARCIAL1::update(double deltaTime)
{
	double degreesToRotate = 0.0;

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	// ----------------------------------------------------------------------------------------------------------------------------------------
	// degrees = rotation speed * delta time 
	// deltaTime is expressed in milliseconds, but our rotation speed is expressed in seconds (convert delta time from milliseconds to seconds)
	degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
	// accumulate rotation degrees
	m_objectRotation += degreesToRotate;

	// Reset rotation if needed
	while (m_objectRotation > 360.0)
	{
		m_objectRotation -= 360.0;
	}
	if (m_objectRotation < 0.0)
	{
		m_objectRotation = 0.0;
	}
}

/* */
void CFBXPARCIAL1::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL
		&& menu->isInitialized()
		&& menu->isActive())
	{
		//...
	}
	else // Otherwise, render app-specific stuff here...
	{
		// =================================
		float color[3] = { 194.0f, 54.0, 22.0f };

		unsigned int noTexture = 0;

		// convert total degrees rotated to radians;
		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix(
			(float)totalDegreesRotatedRadians, m_objectPosition);

		if (m_geoVAOID > 0 && m_numFacesFBX > 0)		// Cambiar por la variable pertinente
		{
			getOpenGLRenderer()->renderObject(
				&m_ShaderID,
				&m_geoVAOID,
				&noTexture,
				m_numFacesFBX, // Sustituir por la variable correspondiente
				color,
				&modelMatrix,
				COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
				false
			);
		}
		// =================================
	}
}

/* */
void CFBXPARCIAL1::onMouseMove(float deltaX, float deltaY)
{
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
void CFBXPARCIAL1::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}

void CFBXPARCIAL1::createPyramid()
{
	m_numFacesPiramid = 6;
	bool loaded = false;
	float h = 2.5f;
	float halfz = 1.5f;
	float halfx = 2.0f;
	//float v1V3[3], v1V2[3], normal[3];

	// vertices
	float vData[15] = {
		0.0, h, 0.0,
		-halfx, 0.0, halfz,
		halfx, 0.0, halfz,
		-halfx, 0.0, -halfz,
		halfx, 0.0, -halfz
	};

	// Se definen los vertices
	unsigned short vIndices[18] = {
		0,1,2,
		0,2,4,
		0,4,3,
		0,3,1,
		1,4,2,
		4,3,1
	};

	// Se definen las normales
	float nData[18] = {
		0.0,0.0,0.0,	// Normal de la primera cara
		0.0,0.0,0.0,	// Normal de la segunda cara
		0.0,0.0,0.0,	// Normal de la tercera cara
		0.0,0.0,0.0,	// Normal de la cuarta cara
		0.0,0.0,0.0,	// Normal de la	quinta cara
		0.0,0.0,0.0,	// Normal de la sexta cara
	};
	// Se difinen los indices (identificadores)
	unsigned short nIndices[18] = {
		0.0,0.0,0.0,	// Primer indice
		1.0,1.0,1.0,	// Segundo indice
		2.0,2.0,2.0,
		3.0,3.0,3.0,
		4.0,4.0,4.0,
		5.0,5.0,5.0
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_ShaderID,
		&m_geoVAOID,
		vData,			// Vertices
		5,				// Num Vertices
		nData,			// normales
		6,				// num normales
		vData,			// UV coords
		5,				// num UV coords
		vIndices,		// Indices a vertices
		6,				// num tri
		nIndices,		// Indices a normales
		6,				// num indices a normales
		vIndices,		// Indices a UV Coords
		6);				// num indices a UV coords
	if (!loaded)
		m_geoVAOID = 0;
	


}

void CFBXPARCIAL1::createCube()
{
	m_numFacesCube = 12;
	bool loaded = false;
	float h = 1.0f;
	float halfx = .5f;
	float halfz = .5f;
	float v1V3[3], v1V2[3], normal[3];

	// Vertices
	float vData[24] = {
		// Abajo
		halfx, 0.0, halfz, // Vertice 0, porque esta en el suelo y la altura es 0
		halfx, 0.0, -halfz, // Vertice 1
		-halfx, 0.0, halfz, // Vertice 2
		-halfx, 0.0, -halfz, // Vertice 3
							 // Arriba
							 halfx, h, halfz,		// Vertice 4
							 halfx, h, -halfz,		// Vertice 5
							 -halfx, h, halfz,		// Vertice 6
							 -halfx, h, -halfz		// Vertice 7
	};

	// Se definen los vertices 12 (Numtringulos) x 3 (num Vertices de un tringulo) = 36 indices
	unsigned short vIndices[36] = {
		// Cara base inferior
		1,2,3,
		1,0,2,

		// Cara 1
		0,6,2,
		0,4,6,

		// Cara 2
		1,4,0,
		1,5,4,

		// Cara 3
		3,5,1,
		3,7,5,

		// Cara 4
		2,7,3,
		2,6,7,

		// Cara Base Superior
		4,7,6,
		4,5,7
	};

	// Se definen las normales
	float nData[36] = {
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0
	};
	// Se difinen los indices (identificadores)
	unsigned short nIndices[36] = {
		0,0,0,	// Primer indice
		1,1,1,	// Segundo indice
		2,2,2,
		3,3,3,
		4,4,4,
		5,5,5,
		6,6,6,
		7,7,7,
		8,8,8,
		9,9,9,
		10,10,10,
		11,11,11
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_ShaderID,
		&m_geoVAOID,
		vData,			// Vertices
		8,				// Num Vertices
		nData,			// normales
		12,				// num normales
		vData,			// UV coords
		8,				// num UV coords
		vIndices,		// Indices a vertices
		12,				// num tri
		nIndices,		// Indices a normales
		12,				// num indices a normales
		vIndices,		// Indices a UV Coords
		12);				// num indices a UV coords
	if (!loaded)
		m_geoVAOID = 0;
}

void CFBXPARCIAL1::createSphere()
{
	m_numFacesSphere = 40;
	bool loaded = false;
	float h = 2.0f;
	float halfz = .5f;
	float halfx = .5f;
	const float pi = 3.14159265358979323846;
	float radio = 5;
	float volumen = pow(radio, 3) * 4;
	float defVolumen = volumen * (pi) / 3;
	cout << "Volumen: " << defVolumen << endl;

	// vertices
	float vData[30] = {
		0.0, h, 0.0,			// vector 0
		-halfx, 1.0, halfz,		// vector 1
		halfx, 1.0, halfz,		// vector 2
		-halfx, 1.0, -halfz,	// vector 3
		halfx, 1.0, -halfz,		// vector 4

		0.0, 0.0, 0.0,			// vector 5


	};

	// Se definen los vertices
	unsigned short vIndices[36] = {
		0,1,2,
		0,2,4,
		0,4,3,
		0,3,1,

		1,4,2,
		4,3,1,

		5,1,2,
		5,2,4,
		5,4,3,
		5,3,1

	};

	// Se definen las normales
	float nData[36] = {
		0.0,0.0,0.0,	// Normal de la primera cara
		0.0,0.0,0.0,	// Normal de la segunda cara
		0.0,0.0,0.0,	// Normal de la tercera cara
		0.0,0.0,0.0,	// Normal de la cuarta cara
		0.0,0.0,0.0,	// Normal de la	quinta cara
		0.0,0.0,0.0,	// Normal de la sexta cara
		0.0,0.0,0.0,	// Normal de la primera cara
		0.0,0.0,0.0,	// Normal de la segunda cara
		0.0,0.0,0.0,	// Normal de la tercera cara
		0.0,0.0,0.0,	// Normal de la cuarta cara
		0.0,0.0,0.0,	// Normal de la	quinta cara
		0.0,0.0,0.0,	// Normal de la sexta cara
	};
	// Se difinen los indices (identificadores)
	unsigned short nIndices[36] = {
		0.0,0.0,0.0,	// Primer indice
		1.0,1.0,1.0,	// Segundo indice
		2.0,2.0,2.0,
		3.0,3.0,3.0,
		4.0,4.0,4.0,
		5.0,5.0,5.0,
		6.0,6.0,6.0,
		7.0,7.0,7.0,
		8.0,8.0,8.0,
		9.0,9.0,9.0,
		10.0,10.0,10.0
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_ShaderID,
		&m_geoVAOID,
		vData,			// Vertices
		6,				// Num Vertices
		nData,			// normales
		12,				// num normales
		vData,			// UV coords
		6,				// num UV coords
		vIndices,		// Indices a vertices
		12,				// num tri
		nIndices,		// Indices a normales
		12,				// num indices a normales
		vIndices,		// Indices a UV Coords
		12);				// num indices a UV coords
	if (!loaded)
		m_geoVAOID = 0;



}

void CFBXPARCIAL1::createSphereTrail(int x, int y)
{
	// Variables
#define DtoR 0.0174533
	bool loaded = false;
	float radio = 1.0f;
	float SubdivisionAxis = x - 1;  //Subdivisiones horizontales
	float SubdivisionHeight = y;        //Subdivisiones verticales

	float Xdegrees = 180.0f / x;
	float Ydegrees = 360.0f / y;

	float newHeight = 3.5;
	//Numero de caras y vertices en el mesh
	int numVertices = (SubdivisionHeight * (SubdivisionAxis)) + 2;
	m_numFacesSphereTrail = (numVertices - 2) * 2;



	//Numero de vertices
	float* vData = new float[numVertices * 3];

	int indexLoop = 1;
	int verticeActual = 0;
	float CurrentRadius = radio * sin(((180.0f - (Xdegrees *newHeight* indexLoop)) * DtoR));
	//Calculo las posiciones de los vertices
	for (int i = 0; i < numVertices * 3; i += 3)
	{
		if (SubdivisionHeight == verticeActual)
		{
			indexLoop++;
			CurrentRadius = radio * sin(((180.0f - (Xdegrees * newHeight* indexLoop)) * DtoR));
			verticeActual = 0;
		}

		if (indexLoop < SubdivisionHeight)
		{
			vData[i] = (CurrentRadius * cos((Ydegrees * verticeActual) * DtoR));				// X
			vData[i + 1] = CurrentRadius * sin(((180.0f - (Xdegrees * indexLoop)) * DtoR));		// Y
			vData[i + 2] = CurrentRadius * sin((Ydegrees * verticeActual) * DtoR);				// Z
		}

		else
		{
			vData[i] = 0;			// X
			vData[i++] = -radio;	// Y
			vData[i++] = 0;			// Z
			vData[i++] = 0;
			vData[i++] = radio;
			vData[i++] = 0;
		}

		verticeActual++;
	}

	//Indices de los vertices
	unsigned short* vIndices = new unsigned short[m_numFacesSphereTrail * 3];

	indexLoop = 1;
	verticeActual = 0;

	//Calculo los indices a los vertices
	for (int i = 0; i < m_numFacesSphereTrail * 3; i += 6)
	{
		if (SubdivisionHeight == verticeActual)
		{
			indexLoop++;
			verticeActual = 0;
		}

		if (indexLoop < SubdivisionAxis)
		{
			vIndices[i] = ((indexLoop - 1) * SubdivisionHeight) + verticeActual;

			if (verticeActual == SubdivisionAxis)
			{
				vIndices[i + 1] = ((indexLoop - 1) * SubdivisionHeight);
				vIndices[i + 3] = (indexLoop - 1) * SubdivisionHeight;
				vIndices[i + 4] = (((indexLoop - 1) * SubdivisionHeight) + SubdivisionHeight);
			}

			else
			{
				vIndices[i + 1] = (((indexLoop - 1) * SubdivisionHeight) + 1) + verticeActual;
				vIndices[i + 3] = (((indexLoop - 1) * SubdivisionHeight) + 1) + verticeActual;
				vIndices[i + 4] = (((indexLoop - 1) * SubdivisionHeight) + 1 + SubdivisionHeight) + verticeActual;
			}

			vIndices[i + 2] = (((indexLoop - 1) * SubdivisionHeight) + SubdivisionHeight) + verticeActual;
			vIndices[i + 5] = (((indexLoop - 1) * SubdivisionHeight) + SubdivisionHeight) + verticeActual;
		}

		else
		{
			unsigned short downVertex = vIndices[i - 1] + 1;
			unsigned short upVertex = downVertex + 1;

			unsigned short topLoop = (SubdivisionAxis * SubdivisionHeight) - SubdivisionHeight;

			for (int j = 0; j < SubdivisionHeight; j += 2)
			{
				vIndices[i++] = topLoop + j;
				vIndices[i++] = topLoop + j + 1;
				vIndices[i++] = upVertex;

				vIndices[i++] = topLoop + j + 1;

				vIndices[i++] = topLoop + j + 2;

				if (vIndices[i - 1] >= (topLoop + SubdivisionHeight))
				{
					vIndices[i - 1] = topLoop;
				}

				vIndices[i++] = upVertex;
			}

			for (int j = 0; j < SubdivisionHeight; j += 2)
			{
				vIndices[i++] = downVertex;
				vIndices[i++] = j + 1;
				vIndices[i++] = j;

				vIndices[i++] = downVertex;

				vIndices[i++] = j + 2;

				if (vIndices[i - 1] >= SubdivisionHeight)
				{
					vIndices[i - 1] = 0;
				}

				vIndices[i++] = j + 1;
			}
		}

		verticeActual++;
	}

	//Normales
	float* nData = new float[m_numFacesSphereTrail * 3];

	//Le asigno el valor 0 a todos los indices
	for (int i = 0; i < m_numFacesSphereTrail; i += 3)
	{
		nData[i] = 0.0f;
		nData[i + 1] = 0.0f;
		nData[i + 2] = 0.0f;
	}

	//Indices de las normales
	unsigned short* nIndices = new unsigned short[m_numFacesSphereTrail * 3];

	//nIndices
	int nIndex = 0;

	for (int i = 0; i < m_numFacesSphereTrail * 3; i += 3)
	{
		nIndices[i] = nIndex;
		nIndices[i + 1] = nIndex;
		nIndices[i + 2] = nIndex;

		nIndex++;
	}

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_ShaderID,
		&m_geoVAOID,
		vData,          // vertices
		numVertices,    // Numero de vertices
		nData,          // Normales
		m_numFacesSphereTrail,     // Numero de normales
		vData,          // UV coords
		numVertices,    // Numero de UV coords
		vIndices,       // Indices de vertices
		m_numFacesSphereTrail,     // Numero de vertices
		nIndices,       // Indices a normales
		m_numFacesSphereTrail,     // Numero de indices a normales
		vIndices,       // Indices a las UV coords
		m_numFacesSphereTrail      // Numero de indices a UV coords
	);

	if (!loaded)
	{
		m_geoVAOID = 0;
	}
}

void CFBXPARCIAL1::loadFBXModel(const char * const filename)
{
	// Getting the vertex Data
	GetFBXData(filename, "Vertices:", ' ', "a:", ',', '\0', "float", false);
	m_vertexAmount = m_data.size();
	V_vertexAmount = m_doubleData;

	float *arrayVertex = new float[V_vertexAmount.size()];
	for (int i = 0; i < V_vertexAmount.size(); i++)
		arrayVertex[i] = V_vertexAmount[i];

	
	reset();

	// Getting the Normals Data
	GetFBXData(filename, "Normals:", ' ', "a:", ',', '\0', "float", false);
	m_normalsAmount = m_data.size();
	V_normalsData = m_doubleData;
	float *arrayNormals = new float[V_normalsData.size()];
	for (int i = 0; i < V_normalsData.size(); i++)
		arrayNormals[i] = V_normalsData[i];
	reset();

	// Getting the UV's Data
	GetFBXData(filename, "UV:", ' ', "a:", ',', '\0', "unsignedshort", false);
	m_uvsAmount = m_data.size();
	V_uvsData = m_unsignedShortData;
	float *arrayUV = new float[V_uvsData.size()];
	for (int i = 0; i < V_uvsData.size(); i++)
		arrayUV[i] = V_uvsData[i];
	reset();

	// Geeting the index vertex data
	GetFBXData(filename, "PolygonVertexIndex:", ' ', "a:", ',', '\0', "unsignedshort", true);
	m_vertexIndexAmount = m_data.size();
	V_vertexIndexData = m_unsignedShortData;
	unsigned short *arrayVertexIndex = new unsigned short[V_vertexIndexData.size()];
	for (int i = 0; i < V_vertexIndexData.size(); i++)
		arrayVertexIndex[i] = V_vertexIndexData[i];

	// Getting the normals index Data
	for (int i = 0; i < m_vertexIndexAmount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			V_normalsIndexData.push_back(i);
		}
	}
	unsigned short *arrayNormalsIndex = new unsigned short[V_normalsIndexData.size()];
	for (int i = 0; i < V_normalsIndexData.size(); i++)
		arrayNormalsIndex[i] = V_normalsIndexData[i];

	m_normalsIndexAmount = V_normalsIndexData.size();


	reset();

	// Getting the UV's Index Data
	GetFBXData(filename, "UVIndex:", ' ', "a:", ',', '\0', "unsignedshort", true);
	m_uvsIndexAmount = m_data.size();
	V_uvsIndexData = m_unsignedShortData;
	unsigned short *arrayUvIndex = new unsigned short[V_uvsIndexData.size()];
	for (int i = 0; i < V_uvsIndexData.size(); i++)
		arrayUvIndex[i] = V_uvsIndexData[i];
	reset();

	bool loaded = false;
	m_numFacesFBX = m_vertexIndexAmount / 3;
	// Charge the data to the render
	





	// Todos los indices tienen que ser positivos, multiplicar por -1
	//loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(&m_ShaderID, &m_geoVAOID);
	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_ShaderID,
		&m_geoVAOID,
		// vertices
		arrayVertex,
		m_vertexAmount / 3,
		// Indices de vertices
		arrayNormals,
		m_normalsAmount / 3,
		// numero de indices de uvs
		arrayUV,
		m_uvsAmount / 2,
		// numero de indices de vertices
		arrayVertexIndex,
		m_vertexIndexAmount / 3,
		// numero de incies Indices de normales es la cantidad de vertices pero x3 veces cada dato
		arrayNormalsIndex,
		m_normalsIndexAmount / 3,
		// idices de uvs
		arrayUvIndex,
		m_uvsIndexAmount / 3
	);
	if (!loaded)
		m_geoVAOID = 0;
}

// Inicializa en cero las variables
void CFBXPARCIAL1::reset()
{
	// ============================== Variables a inicializar
	m_index = 0;
	m_indexTwo = 0;
	m_ItypeAmount = 0;					
	m_data.clear();
	m_doubleData.clear();
	m_unsignedShortData.clear();
}


void CFBXPARCIAL1::GetFBXData(string filename, string wordTofind, char token, string delimiter, char token2, char token3, string dataType, bool condition)
{
	ifstream LoadFBXFile;
	LoadFBXFile.open(filename);
	if (LoadFBXFile.fail())
		cout << "loadFBXModel() - Error en la carga de archivos FBX." << endl;
	else
		//cout << "loadFBXModel() - Exito en la carga de archivos FBX." << endl;

	
	m_index = wordTofind.length() + 2;
	m_indexTwo = delimiter.length() + 1;
	m_FinderPosition = m_reader.find(wordTofind);			// This is the word to find in the .fbx
	


	if (LoadFBXFile.is_open())
	{
		while (getline(LoadFBXFile, m_reader))
		{
			// ============================== VERTICES

			m_FinderPosition = m_reader.find(wordTofind);				// Finder of the word

			if (m_FinderPosition != string::npos)						// string::npos is returned if string is not found
			{
				// Find the amount of vertex 

				while (true)
				{	// Find the amount of the array on string
					if (m_reader[m_FinderPosition + m_index] != token)
						m_SVertexAmount += m_reader[m_FinderPosition + m_index];		// Number of vector or array
					else
						break;
					m_index++;
				}

				
				stringstream stringToint(m_SVertexAmount);
				stringToint >> m_ItypeAmount;										// Get the data of the string to int

				// Find the information of the type of data
				getline(LoadFBXFile, m_reader);
				m_FinderPositionTwo = m_reader.find(delimiter);
				
				
				m_Sdata.clear();
				if (m_FinderPositionTwo != string::npos)
				{
					while (true) 
					{	// Find the data of the array on string
						if (m_reader[m_FinderPositionTwo + m_indexTwo + 1] == token3)
						{
							m_Sdata += m_reader[m_FinderPositionTwo + m_indexTwo];
						}
						if (m_reader[m_FinderPositionTwo + m_indexTwo] == token2 || m_reader[m_FinderPositionTwo + m_indexTwo + 1] == token3)
						{
							m_data.push_back(m_Sdata);
							if (m_reader[m_FinderPositionTwo + m_indexTwo + 1] == token3)
							{
								break;
							}
							m_Sdata.clear();
						}
						else
						{
							m_Sdata += m_reader[m_FinderPositionTwo + m_indexTwo];
						
						}
						m_indexTwo++;
					}

					// Condition for getting the correct type of data

					// Convert the string vector to int vector
					cout << endl;
					cout << wordTofind << "[" << m_data.size() << "]" << ": ";
					for (int i = 0; i < m_data.size(); i++)
					{
						if (dataType == "float")
						{
							double num = atof(m_data.at(i).c_str());
							if (num < 0 && condition == true)
							{
								double newIndex = (num * -1)-1;
								m_doubleData.push_back(newIndex);
							}
							else
								m_doubleData.push_back(num);

							cout << m_doubleData[i] << ", ";				// Print the vertex data
						}
						if (dataType == "unsignedshort")
						{
							int num = atof(m_data.at(i).c_str());
							if (num < 0 && condition == true)
							{
								unsigned short newIndex = (num * -1)-1;
								m_unsignedShortData.push_back(newIndex);
							}
							else
								m_unsignedShortData.push_back(num);

							cout << m_unsignedShortData[i] << ", ";
						}

					}
						cout << endl;
				}
			}
		}
	}
	LoadFBXFile.close();

}

void CFBXPARCIAL1::TGACaller(const char *filename, unsigned int *newTextureID)
{
	
}