#include "CGridCell.h"


CGridCell::CGridCell()
{
}

CGridCell::~CGridCell()
{
}

void CGridCell::createCell()
{
	
	float *vdata = new float[numVertices * 3];

	int **Vertex = new int *[3]; // Registro del indice de los vertices

	for (int i = 0; i < 6 + 2; i++)
	{
		Vertex[i] = new int[6 + 2];
	}
	// Referencia del limite de los vertices
	for (int i = 0; i < 2 + 1; i++)
	{
		for (int j = 0; j < 6 + 2; j++)
		{
			Vertex[i][j] = -1;
		}
	}
	// ============================== SECTION
	float Vertex_X = 0.0f;
	float Vertex_Y = 0.0f;
	float Vertex_Z = 0.0f;

	int numVertice = 0;
	int vertice = 0;
	int nV = 0;
	// ============================== Asignando los vertices
	for (int j = 0; j < 1; j++)
	{
		Vertex_X = 0;
		vdata[nV] = Vertex_X;
		nV++;
		Vertex_Y = 0;
		vdata[nV] = Vertex_Y;
		nV++;
		if (j < 1)
		{
			Vertex_Z = Z1;
		}


		vdata[nV] = Vertex_Z;
		nV++;

		Vertex[j][vertice] = numVertice;
		numVertice++;
		vertice++;
		// ============================== Se definen los vertices en su posicion
		for (int i = 0; i < 360; i += anguloY)
		{
			Vertex_X = size * sin(i / (180 / PI));
			vdata[nV] = Vertex_X;
			nV++;

			Vertex_Y = size * cos(i / (180 / PI));
			vdata[nV] = Vertex_Y;
			nV++;

			if (j < 1)
			{
				Vertex_Z = Z1;
			}


			vdata[nV] = Vertex_Z;
			nV++;

			Vertex[j][vertice] = numVertice;
			numVertice++;
			vertice++;

		}
		vertice = 0;
	}

	// Vertices = 6;
	int fila, col;
	int num = 0;
	unsigned short vIndices[6 * 3];

	// Se asignana los vertices a su posicion
	for (int i = 0; i < 6 * 3; i++)
	{
		vIndices[i] = 0;
	}

	for (int i = 0; i < 1; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			if (i == 0)
			{
				if (Vertex[i][j + 1] == -1)
				{
					vIndices[num] = unsigned short(Vertex[i][0]);
					num++;
					vIndices[num] = unsigned short(Vertex[i][1]);
					num++;
					vIndices[num] = unsigned short(Vertex[i][j]);
					num++;
				}
				else
				{
					vIndices[num] = unsigned short(Vertex[i][0]);
					num++;
					vIndices[num] = unsigned short(Vertex[i][j + 1]);
					num++;
					vIndices[num] = unsigned short(Vertex[i][j]);
					num++;
				}

			}
			// Se muestra el lado contrario	
			else if (i == 1)
			{
				/*
					if (Vertex[i][j + 1] == -1)
					{
						vIndices[num] = unsigned short(Vertex[i][0]);
						num++;
						vIndices[num] = unsigned short(Vertex[i][j]);
						num++;
						vIndices[num] = unsigned short(Vertex[i][1]);
						num++;
					}
					else
					{
						vIndices[num] = unsigned short(Vertex[i][0]);
						num++;
						vIndices[num] = unsigned short(Vertex[i][j]);
						num++;
						vIndices[num] = unsigned short(Vertex[i][j + 1]);
						num++;
					}
				*/
			}
		}
	}

	// Se definen las normales
	float nData[6 * 3];
	for (int i = 0; i < 6 * 3; i++)
	{
		nData[i] = 0.0;
	}

	int num1 = 0;
	unsigned short nIndice[6 * 3];
	// Se definen los indices de las normales
	for (int i = 0; i < 6 * 3; i++)
	{
		nIndice[i] = num1;
		i++;
		nIndice[i] = num1;
		i++;
		nIndice[i] = num1;
		num1++;
	}
}