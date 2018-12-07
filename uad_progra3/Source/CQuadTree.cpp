#include "../Include/CQuadTree.h"
#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"

CQuadTree::CQuadTree()
{
}

CQuadTree::CQuadTree(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_rotationSpeed = 0;

	m_objectPosition = CVector3::ZeroVector();

	cout << "Constructor: CGrid(int window_width, int window_height)" << endl;

}

CQuadTree::~CQuadTree()
{
}


void CQuadTree::initialize()
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
	//getOpenGLRenderer()->createShaderProgram(
	//	&m_Cell.m_ShaderID,
	//	resourceFilenameVS.c_str(),
	//	resourceFilenameFS.c_str());

}

void CQuadTree::run()
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

void CQuadTree::update(double deltaTime)
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

void CQuadTree::render() 
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

	}

}

/* Build Tree */

void CQuadTree::renderCam()
{
	// Obtener los rangos M
	if (Cam.m_leftUp.X < 0 && Cam.m_leftUp.Y > 0) // Seccion Izquierda Arriba
	{

	}

	if (Cam.m_leftUp.X > 0 && Cam.m_leftUp.Y > 0) // Seccion Derecha Arriba
	{

	}

	if (Cam.m_rightDown.X < 0 && Cam.m_rightDown.Y > 0)
	{

	}

	if (Cam.m_rightDown.X > 0 && Cam.m_rightDown.Y < 0)
	{

	}
}