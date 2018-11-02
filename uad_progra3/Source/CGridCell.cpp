#include "../Include/CGridCell.h"

CGridCell::CGridCell()
{
}

CGridCell::~CGridCell()
{
}

void CGridCell::Cell()
{
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

	for (int i = 0; i < 6 * 3; i++)
	{
		nData[i] = 0.0;
	}

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