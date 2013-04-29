/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoEstadistico.h
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

#ifndef _CALCULOESTADISTICO_H_
	#define _CALCULOESTADISTICO_H_

	#include <math.h>
	#include <iostream>
	#include <vector>

	#include "Estructuras/ListadoCelulas.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Modulos/CalculoMorfologico.h"

	using namespace std;

	class CalculoEstadistico
	{
		public:
			static vector<Celula> celulasConNucleo(ListadoCelulas &listCell);
			static vector<Celula> celulasCoincidentesEstado(vector<EstadoCelula> &estados,
			                                     			vector<int> estSelec,
                                                 			ListadoCelulas &listCell);
			static vector<Celula> puntosDentroLimite(int maxX, int maxY, int minX,
			                                         int minY, int &numCelSelec, 
			                                         vector<Celula> &cellSelec);
			static int objetosDentroLimite(int maxX, int maxY, int minX,
			                               int minY, string est, 
			                               vector<Celula> &cellSelec);
			static bool calculoPuntosDentroRejilla(int aciertosIndiv[], vector<Celula> &cellAceptedGrid, 
                                                   vector<vector<int> > &puntosRejilla);
			static bool calculoRejillaSepar1(int aciertosIndiv[], vector<Celula> &cellAceptedGrid);
		private:
			static bool puntoDentroCelula(int cX, int cY, Celula &cell);
			
	};

#endif //_CALCULOESTADISTICO_H_
