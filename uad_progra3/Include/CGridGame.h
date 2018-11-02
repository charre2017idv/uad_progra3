#pragma once
#include "Globals.h"
#include "CApp.h"
#include "CGrid.h"

class CGridGame:public CApp
{
public:
	CGridGame();
	CGridGame(int window_width, int window_height);
	~CGridGame();

public:
	void initialize();
	void run();
	void update(double deltatime);
	void render();
	bool initializeMenu() { return false; }

private:
	CGrid *m_GRID = NULL;

};

