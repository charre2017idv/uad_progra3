// uad_progra3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Include/CGameWindow.h"
#include "Include/CApp.h"
#include "Include/CAppParcial2.h"
//#include "Include/CGeometricFigure.cpp.h"
#include  "Include/CFBXPARCIAL1.h"
//#include "Include/CAppHexGrid.h"
#include "Include/CAppEmpty.h"
#include "Include/CGridGame.h"

int main()
{
	CApp *app = NULL;                  // Pointer to BASE class CApp
	//app = new CFBXPARCIAL1(800, 600);     // Using pointer to base class, create a new object of DERIVED class
	app = new CGridGame(800, 600);     // Using pointer to base class, create a new object of DERIVED class
	app->run();                        // Run the app
	delete app;                        // Delete pointer
	app = NULL;                        // Set pointer to NULL

	return 0;
}

