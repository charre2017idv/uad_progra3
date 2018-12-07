#include "../Include/CQuadTreeNode.h"

CQuadTreeNode::CQuadTreeNode()
{
	m_Grid.savePostionForNode(centerPositions);
}

CQuadTreeNode::~CQuadTreeNode()
{

}

void CQuadTreeNode::initialize()
{
	Cam();
	BoundsSize();

}

/* Get logic */
void CQuadTreeNode::BoundsSize()
{
	// -X,-Y
	m_bounds[0].X = -(m_Grid.incrementoX1 * m_Grid.columnas) / 2;
	m_bounds[0].Y = -(m_Grid.incrementoY * m_Grid.filas) / 2;
	// X, -Y
	m_bounds[1].X = (m_Grid.incrementoX1 * m_Grid.columnas) / 2;
	m_bounds[1].Y = -(m_Grid.incrementoY * m_Grid.filas) / 2;
	// -X, Y
	m_bounds[2].X = -(m_Grid.incrementoX1 * m_Grid.columnas) / 2;
	m_bounds[2].Y = (m_Grid.incrementoY * m_Grid.filas) / 2;
	// X, Y
	m_bounds[3].X = (m_Grid.incrementoX1 * m_Grid.columnas) / 2;
	m_bounds[3].Y = (m_Grid.incrementoY * m_Grid.filas) / 2;


	// Calcular cuadro de render? - sub divisiones (4)
	for (int i = 0; i < centerPositions.size(); i++)
	{
		if (centerPositions[i].X < 0 && centerPositions[i].Y > 0) // Nodo arriba izquierda
		{
			Nodo1.push_back(centerPositions[i]);
		}

		else if (centerPositions[i].X > 0 && centerPositions[i].Y > 0) // Nodo arriba derecha 
		{
			Nodo2.push_back(centerPositions[i]);
		}
		
		else if (centerPositions[i].X < 0 && centerPositions[i].Y < 0) // Nodo abajo izquierda
		{
			Nodo3.push_back(centerPositions[i]);
		}

		else if (centerPositions[i].X > 0 && centerPositions[i].Y > 0) // Nodo abajo derecha
		{
			Nodo4.push_back(centerPositions[i]);
		}

	}
}

void CQuadTreeNode::Cam()
{

}