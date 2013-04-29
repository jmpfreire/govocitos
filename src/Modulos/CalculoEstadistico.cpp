/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoEstadistico.cpp
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jpfreire@correo.ei.uvigo.es>
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANPOILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "CalculoEstadistico.h"

/**
 Metodo estatico que identifica las celulas con nucleo y las devuelve en un vector
 de objetos de la clase Celula.
 @param listCell, referencia al objeto de la clase ListadoCelulas que contiene todas
 las celulas.
 @return vector de la clase Celula que contiene las celulas con nucleo.
 */
vector<Celula> CalculoEstadistico::celulasConNucleo(ListadoCelulas &listCell)
{
	int numCel;
	vector<Celula> cellConNucleo;
	Celula cell;

	numCel = listCell.getNumCelulas();

	for(int i = 0; i < numCel; i++)
	{
		cell = *listCell.getCelula(i);

		if(cell.getClaseCelula() == "cn")
		{
			cellConNucleo.push_back(cell);
		}
	}

	return cellConNucleo;
}

/**
 Metodo estatico que descarta las celulas que no coinciden con el estado seleccionado.
 @param estados, estados que se encuentran definidos en el sistema.
 @param estSelec, estados seleccionados para el filtrado de celulas.
 @param listCell, referencia al objeto de la clase ListadoCelulas que contiene todas
 las celulas.
 @return vector de la clase Celula que contiene las celulas con los estados coincidentes.
 */
vector<Celula> CalculoEstadistico::celulasCoincidentesEstado(vector<EstadoCelula> &estados,
                                                             vector<int> estSelec,
                                                             ListadoCelulas &listCell)
{
	int numCelulas, numEstados;
	string estado;
	Celula cell;
	vector<Celula> cellsSelec;

	numCelulas = listCell.getNumCelulas();
	numEstados = estSelec.size();
	
	for(int i = 0; i < numCelulas; i++)
	{
		cell = *listCell.getCelula(i);
		
		for(int j = 0; j < numEstados; j++)
		{
			estado = estados[estSelec[j]].getEtiquetaClasificacion();

			if(estado == cell.getEstadoCelula())
			{
				cellsSelec.push_back(cell);
			}
		}
	}

	return cellsSelec;
}

/**
 Metodo estatico que contabiliza si todos los puntos se encuentran dentro del limite
 de la rejilla.
 @param maxX, punto maximo de la rejilla en el eje X.
 @param maxY, punto maximo de la rejilla en el eje Y.
 @param minX, punto minimo de la rejilla en el eje X.
 @param minY, punto minimo de la rejilla en el eje Y.
 @param numCelSelec, int pasado pro referencia que contiene el número de celulas que
 se encuentran dentro de la rejilla.
 @param cellSelec, vector de la clase Celula que contiene las celulas a analizar.
 @return vector de la clase Celula que contiene las celulas que se encuentran dentro 
 de la rejilla.
 */
vector<Celula> CalculoEstadistico::puntosDentroLimite(int maxX, int maxY, int minX,
                                                   int minY, int &numCelSelec, 
                                                   vector<Celula> &cellSelec)
{	
	int numCelulas;
	Celula cell;
	vector<Celula> cellIn;

	//Asignamos el tamaño del vector de poligonos
	numCelulas = cellSelec.size();

	for(int i = 0; i < numCelulas; i++)
	{
		cell = cellSelec[i];

		//Posicion 0 Max X, Posicion 1 Min X, Posicion 2 Max Y, Posicion 3 Min Y
		if(((cell.getCoordMaxMin(1) <= maxX) && (cell.getCoordMaxMin(0) >= minX)) &&
		   ((cell.getCoordMaxMin(3) <= maxY) && (cell.getCoordMaxMin(2) >= minY)))
		{
			cellIn.push_back(cell);
		}
	}

	int numCellGrid = cellIn.size();
	numCelSelec = 0;
	
	for(int i = 0; i < numCellGrid; i++)
	{
		cell = cellIn[i];
		
		if((cell.getCoordMaxMin(0) <= maxX) && (cell.getCoordMaxMin(2) <= maxY))
		{
			numCelSelec++;
		}
	}

	return cellIn;
}

/**
 Metodo estatico que contabiliza si todos los puntos se encuentran dentro del limite
 y los objetos que no tocan el borde rojo.
 @param maxX, punto maximo de la rejilla en el eje X.
 @param maxY, punto maximo de la rejilla en el eje Y.
 @param minX, punto minimo de la rejilla en el eje X.
 @param minY, punto minimo de la rejilla en el eje Y.
 @param est, string que contiene el estado a analizar.
 @param cellSelec, vector de la clase Celula que contiene las celulas a analizar.
 @return int, con el numero total de celulas que se encuentran dentro de la rejilla.
 */
int CalculoEstadistico::objetosDentroLimite(int maxX, int maxY, int minX,
                                                   int minY, string est, 
                                                   vector<Celula> &cellSelec)
{	
	int numCelulas = 0;
	int numCellGrid = cellSelec.size();
	
	for(int i = 0; i < numCellGrid; i++)
	{	
		if((cellSelec[i].getCoordMaxMin(0) <= maxX) && (cellSelec[i].getCoordMaxMin(2) <= maxY) &&
		   (est == cellSelec[i].getEstadoCelula()))
		{
			numCelulas++;
		}
	}

	return numCelulas;
}

/**
 Metodo estatico que calcula el numero de puntos de la rejilla que cae en cada una
 de las células de la rejilla.
 @param aciertosIndiv, array de int donde se guardaran el número de puntos de la rejilla
 correspondientes a cada célula.
 @param cellAceptedGrid, vector de la clase Celula que contiene las celulas a analizar.
 @param puntosRejilla, vector<vector<int>> que contiene los puntos de la rejilla.
 @return bool, verdadero si se encuentra alguna célula contenida en la rejilla, 
 falso en caso contrario.
 */
bool CalculoEstadistico::calculoPuntosDentroRejilla(int aciertosIndiv[], vector<Celula> &cellAceptedGrid, 
                                                    vector<vector<int> > &puntosRejilla)
{

	int numColR, numFilR, numCelAceptadas;
	bool existenCelulas = false;

	numFilR = puntosRejilla.size();
	numColR = puntosRejilla[0].size();
	numCelAceptadas = cellAceptedGrid.size();

	for(int i = 0; i < numFilR; i++)
	{
		for(int j = 1 ; j < numColR; j++)
		{
			for(int z = 0; z < numCelAceptadas; z++)
			{
				if(puntoDentroCelula(puntosRejilla[i][j], puntosRejilla[i][0], cellAceptedGrid[z]))
				{
					aciertosIndiv[z]++;

					existenCelulas = true;
				}
			}
		}
	}

	return existenCelulas;
}

/**
 Metodo estatico que comprueba si la celula pasada por parametro se encuentra en
 las coordenadas cX y cY.
 @param cX, coordenada X de la busqueda.
 @param cY, coordenada Y de la busqueda.
 @param cell, referencia al objeto de la Celula a buscar.
 @return bool, verdadero si la célula se encuentra en las coordenadas indicadas, 
 falso en caso contrario.
 */
bool CalculoEstadistico::puntoDentroCelula(int cX, int cY, Celula &cell)
{
	int x1, y1, xMedia, yMedia, numCoordPol;
	vector<int> *coordX, *coordY;
	
	//Si el raton se encuentra entre la Max X e Y y la Min X e Y se comprueba 
	//el poligono
	if((cell.getCoordMaxMin(0)) > cX && (cell.getCoordMaxMin(1)) < cX 
	   && (cell.getCoordMaxMin(2)) > cY && (cell.getCoordMaxMin(3)) < cY)
	{
		//(XMax - XMin) / 2 -> resultado + XMin punto medio de coordenada x
		xMedia = (cell.getCoordMaxMin(0) - cell.getCoordMaxMin(1)) / 2;
		xMedia = cell.getCoordMaxMin(1) + xMedia;
		
		//(YMax - YMin) / 2 -> resultado + YMin punto medio de coordenada y
		yMedia = (cell.getCoordMaxMin(2) - cell.getCoordMaxMin(3)) / 2;
		yMedia = cell.getCoordMaxMin(3) + yMedia;

		//Asignamos el numero de coordenadas del poligono
		coordX = cell.getBordeCellX();
		coordY = cell.getBordeCellY();
		numCoordPol = coordX->size();
		
		//Recorremos el poligono
		for(int i = 0; i < numCoordPol; i++)
		{
			//Obtenemos las coordenas x e y del poligono
			x1 = (*coordX)[i];
			y1 = (*coordY)[i];
				
			//Comprobamos si la coordenada cX y cY se encuentra dentro del poligono
			//Cuadrante 1
			if((cX <= x1 && cY >= y1) && (cX >= xMedia && cY <= yMedia))
			{
				return true;
			}
			//Cuadrante 2
			else if((cX >= x1 && cY >= y1) && (cX <= xMedia && cY <= yMedia))
			{
				return true;
			}
			//Cuadrante 3
			else if((cX >= x1 && cY <= y1) && (cX <= xMedia && cY >= yMedia))
			{
				return true;
			}
			//Cuadrante 4
			else if((cX <= x1 && cY <= y1) && (cX >= xMedia && cY >= yMedia))
			{
				return true;
			}
		}
	}

	return false;
}

/**
 Metodo estatico que calcula el area de los ovocitos cuando la separación de esta entre 
 los puntos es de uno.
 @param aciertosIndiv, array con los puntos que estan dentro de un ovocito.
 @param cellAceptedGrid, referencia del vector que contiene las celulas validas.
 @return bool, verdadero si existe al menos una célula, false en caso contrario
 */
bool CalculoEstadistico::calculoRejillaSepar1(int aciertosIndiv[], vector<Celula> &cellAceptedGrid)
{
	int numCelulas;

	numCelulas = cellAceptedGrid.size();
	
	if(numCelulas)
	{
		for(int j = 0; j < numCelulas; j++)
		{
			vector<double> diametRes;

			diametRes = CalculoMorfologico::diametroAreaFormula(cellAceptedGrid[j]);

			cellAceptedGrid[j].setDiametroCell(diametRes[1]);
			cellAceptedGrid[j].setAreaCelula(diametRes[0]);

			aciertosIndiv[j] = diametRes[0];
		}	

		return true;
	}

	return false;
}
