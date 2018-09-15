#include "../stdafx.h"
#include "../Include/CGeometricFigure.cpp.h"
#include "../Include/CWideStringHelper.h"
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

#include "../Include/Globals.h"
//#include "../Include/CGeometricFigure.h"

/* */
CGeometricFigure::CGeometricFigure() :

	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
	cout << "Constructor: CGeometricFigure()" << endl;
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
CGeometricFigure::CGeometricFigure(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CGeometricFigure(int window_width, int window_height)" << endl;
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
CGeometricFigure::~CGeometricFigure()
{
	cout << "Destructor: ~CGeometricFigure()" << endl;

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
void CGeometricFigure::initialize()
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
		createSphereTrail(6,6);
	}

	// ==================================
}

/* */
void CGeometricFigure::run()
{

	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_EMPTYAPP_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

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
void CGeometricFigure::update(double deltaTime)
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
void CGeometricFigure::render()
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
		float color[3] = { 87.0f, 145.0f, 237.0f };

		unsigned int noTexture = 0;

		// convert total degrees rotated to radians;
		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix(
			(float)totalDegreesRotatedRadians, m_objectPosition);

		if (m_geoVAOID > 0 && m_numFacesSphereTrail > 0)		// Cambiar por la variable pertinente
		{
			getOpenGLRenderer()->renderObject(
				&m_ShaderID,
				&m_geoVAOID,
				&noTexture,
				m_numFacesSphereTrail, // Sustituir por la variable correspondiente
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
void CGeometricFigure::onMouseMove(float deltaX, float deltaY)
{
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
void CGeometricFigure::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}

void CGeometricFigure::createPyramid()
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

void CGeometricFigure::createCube()
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

void CGeometricFigure::createSphere()
{
	m_numFacesSphere = 40;
	bool loaded = false;
	float h = 2.0f;
	float halfz = .5f;
	float halfx = .5f;
	const float pi = 3.14159265358979323846;
	float radio = 5;
	float volumen =pow(radio, 3) * 4;
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

void CGeometricFigure::createSphereTrail(int x, int y)
{
	// Variables
#define DtoR 0.0174533
	bool loaded = false;
	float radio = 1.0f;
	float SubdivisionAxis = x - 1;  //Subdivisiones horizontales
	float SubdivisionHeight = y;        //Subdivisiones verticales

	float Xdegrees = 180.0f / x;
	float Ydegrees = 360.0f / y;

	//Numero de caras y vertices en el mesh
	int numVertices = (SubdivisionHeight * (SubdivisionAxis)) + 2;
	m_numFacesSphereTrail = (numVertices - 2) * 2;



	//Numero de vertices
	float* vData = new float[numVertices * 3];

	int indexLoop = 1;
	int verticeActual = 0;
	float CurrentRadius = radio * sin(((180.0f - (Xdegrees * indexLoop)) * DtoR));
	//Calculo las posiciones de los vertices
	for (int i = 0; i < numVertices * 3; i += 3)
	{
		if (SubdivisionHeight == verticeActual)
		{
			indexLoop++;
			CurrentRadius = radio * sin(((180.0f - (Xdegrees * indexLoop)) * DtoR));
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