#pragma once
#include "../Include/CVector3.h"
#include "../Include/CQuadTree.h"
#include "CCamera.h"
#include "CGrid.h"
#include "CGridCell.h"
#include <vector>
#include <iostream>
using namespace std;
class CQuadTreeNode
{
public:
	CQuadTreeNode();
	~CQuadTreeNode();
public:
	//AABB_2D m_volume;
	//CQuadTree* m_children[4];
	vector<CGridCell> m_cells;
	CVector3 m_bounds[4]; // Dimension of the division of the bounds (!) change to AABB_2D
	vector <CVector3> centerPositions;
	CGrid m_Grid;


	vector <CVector3> Nodo1;
	vector <CVector3> Nodo2;
	vector <CVector3> Nodo3;
	vector <CVector3> Nodo4;

//	CCamera camara;
public:
	void BoundsSize();
	void hexCell();
	
	void Cam();
	

	void initialize();
	
public:


public:

	
};

