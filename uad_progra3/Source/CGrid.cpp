#include "../Include/CGrid.h"
#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"
#include <iostream>
using namespace std;

CGrid::CGrid()
{
}

CGrid::CGrid(int window_width, int window_height):
	CApp(window_width, window_height)
{
	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_rotationSpeed = 0;

	m_objectPosition = CVector3::ZeroVector();

	cout << "Constructor: CGrid(int window_width, int window_height)" << endl;
}

CGrid::~CGrid()
{
}

void CGrid::initialize()
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
		&m_Cell.m_ShaderID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());

	if (m_Cell.m_ShaderID > 0)
	{
		// Show the figure
		//createPyramid();
		//createSphereTrail(6, 6);
		//loadFBXModel("Test_Cube_Ascii.fbx");
		createSavePosition();
		m_Cell.Cell();
		m_Cell.loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
			&m_Cell.m_ShaderID,
			&m_Cell.m_geoVAOID,
			m_Cell.vdata,			// Vertices
			7,				// Num Vertices
			m_Cell.nData,			// normales
			6,				// num normales
			m_Cell.vdata,			// UV coords
			7,				// num UV coords
			m_Cell.vIndices,		// Indices a vertices
			6,				// num tri
			m_Cell.nIndice,		// Indices a normales
			6,				// num indices a normales
			m_Cell.vIndices,		// Indices a UV Coords
			6);				// num indices a UV coords
	}
	if (!m_Cell.loaded)
		m_Cell.m_geoVAOID = 0;
	// ==================================
}

void CGrid::run()
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
			getOpenGLRenderer()->setCameraDistance(15.0f);
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

void CGrid::update(double deltaTime)
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
	//degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
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

void CGrid::render()
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

		unsigned int noTexture = 0;

		// convert total degrees rotated to radians;
		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation



		//CVector3 pos2 = m_objectPosition;
		//pos2.X += 1.7f;
		//MathHelper::Matrix4 modelMatrix2 = MathHelper::ModelMatrix(
		//	(float)totalDegreesRotatedRadians, pos2);


		// ============================== Trail object
		int Matrix[5][5] =
		{
			0,0,0,0,0,
			0,0,1,0,0,
			0,1,1,1,0,
			0,0,1,0,0,
			0,0,0,0,0
		};



		float incrementoX1 = 1.76;
		float incrementoY = 1.7 - .17;
		float incrementoX2 = 1.7 / 2;
		int filas = 10;
		int columnas = 10;
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

		for (float i = InicialY; i < totalTamanoY / 2 - 1; i += incrementoY) // Columnas
		{
			for (float j = InicialX; j < totalTamanoX / 2 - 1; j += incrementoX1) // Filas'
			{
				if ((count % 2) != 0)
				{
					m_objectPosition.Y = i;
					m_objectPosition.X = j + incrementoX2;
				}
				else
				{
					m_objectPosition.Y = i;
					m_objectPosition.X = j;

				}
				MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix(
					(float)totalDegreesRotatedRadians, m_objectPosition);


				if (m_Cell.m_geoVAOID > 0 && m_Cell.m_numFacesRender > 0)		// Cambiar por la variable pertinente
				{
					getOpenGLRenderer()->renderObject(
						&m_Cell.m_ShaderID,
						&m_Cell.m_geoVAOID,
						&noTexture,
						m_Cell.m_numFacesRender, // Sustituir por la variable correspondiente
						color,
						&modelMatrix,
						COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
						false
					);

				}
			}
			count++;
		}
	}
}


void CGrid::createSavePosition()
{
	m_cellPosition = new float*[filas*columnas];
	for (int i = 0; i < filas*columnas; i++)
	{
		m_cellPosition[i] = new float[3];
	}
}