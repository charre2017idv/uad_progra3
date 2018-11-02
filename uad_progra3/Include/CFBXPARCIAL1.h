#pragma once

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "Globals.h"
#include "CApp.h"
#include "CAppParcial2.h"
#include "LoadTGA.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include "windows.h"
using namespace std;
// --------------------------------------------------------------------------------------------------------------------------------------
// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
// --------------------------------------------------------------------------------------------------------------------------------------
class CFBXPARCIAL1 : public CApp
{
private:

	// ---------------------------------------------------
	// Private member variables specific to CAppEmpty only
	// ---------------------------------------------------
	//
	// ---------------------------------------------------

protected:

	// Method to initialize the menu 
	// (not needed in CAppEmpty, so return false)
	bool initializeMenu() { return false; }

public:
	// Constructors and destructor
	CFBXPARCIAL1();
	CFBXPARCIAL1(int window_width, int window_height);
	~CFBXPARCIAL1();

	// --------------------------------------------------------------------------------------------------------------------------
	// Inherited methods from CApp
	// Initialize(), update(), run(), and render() are PURE VIRTUAL methods, so they need to be implemented in this DERIVED class
	// --------------------------------------------------------------------------------------------------------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// -----------------------------------------------------------------------------------------------------------------------
	// Other inherited methods from CApp. These are optional to override.
	// Only provide an implementation in this DERIVD class if you need them to do something different than the base class CApp
	// -----------------------------------------------------------------------------------------------------------------------

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Called when mouse moves within the window
	void onMouseMove(float deltaX, float deltaY);

	// -----------------------------------------
	// Public methods specific to CAppEmpty only
	// -----------------------------------------
	//
	// -----------------------------------------

private:

	// ------------------------------------------
	// Private methods specific to CAppEmpty only
	// ------------------------------------------
	//
	// ------------------------------------------
public:
	// ------------------------------------------
	// New methods of figures
	// ------------------------------------------
	void createPyramid();
	void createSphere();
	void createCube();
	void createSphereTrail(int x, int y);



public:
	// Load FBX 
	void loadFBXModel(const char * const filename);
	// Parser
	void GetFBXData(string filename, string wordTofind, char token, string delimiter, char token2, char token3, string dataType, bool condition);
	void TGACaller(const char *filename, unsigned int *newTextureID);
	void reset();

	// Load FBX DLL
	void CallDLLFBX();

	// CreateGrid
	void Hexagon();
	int m_numFacesRender;
public:
	// ============================== Variables of GetFBXData
	string m_reader;

	// Value of size of the array
	size_t m_FinderPosition;
	size_t m_FinderPositionTwo;
	string m_SVertexAmount;								// This allocator will save the number of vertex on string type
	int m_index;
	int m_indexTwo;
	int m_ItypeAmount;						// Variable to transform to int
	// Data of the array
	string m_Sdata;
	vector <string> m_data;
	// Condition for getting the correct type of data
	vector <double> m_doubleData;
	vector <unsigned short> m_unsignedShortData;

	// ============================== Variables of load FBX
	int m_numFacesFBX;
	/* Vertex Information */
	int m_vertexAmount;
	vector<double> V_vertexAmount;

	int m_vertexIndexAmount;
	vector<unsigned short> V_vertexIndexData;

	/* Normals Information */
	int m_normalsAmount;
	vector<double> V_normalsData;

	int m_normalsIndexAmount;
	vector<double> V_normalsIndexData;

	/* Uv's Information */
	int m_uvsAmount;
	vector<unsigned short> V_uvsData;

	int m_uvsIndexAmount;
	vector<unsigned short> V_uvsIndexData;

	bool condition;



private:
	// ------------------------------------------
	// New variables
	// ------------------------------------------
	// Pyramid
	unsigned int m_ShaderID;
	unsigned int m_geoVAOID;
	bool m_initialize;
	int m_numFacesPiramid;
	// Sphere
	int m_numFacesSphere;
	int m_numFacesSphereTrail;
	// Cube
	int m_numFacesCube;

	/* Render */

	// Current delta time (time of the current frame - time of the last frame)
	double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	double m_objectRotation;

	// Current object position
	CVector3 m_objectPosition;

	//  Object rotation speed (degrees per second)
	double m_rotationSpeed;

};

#endif // !CAPPEMPTY_H