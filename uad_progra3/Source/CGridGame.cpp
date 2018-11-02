#include "../Include/CGridGame.h"
#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"
#include <iostream>
using namespace std;

CGridGame::CGridGame()
{
}

CGridGame::CGridGame(int window_width, int window_height)
{
	m_GRID = new CGrid(window_width, window_height);
}


CGridGame::~CGridGame()
{
	delete m_GRID;
}

void CGridGame::initialize()
{
	m_GRID->initialize();
}

void CGridGame::run()
{
	m_GRID->run();
}

void CGridGame::update(double deltaTime)
{
	m_GRID->update(deltaTime);
}

void CGridGame::render()
{
	m_GRID->render();
}