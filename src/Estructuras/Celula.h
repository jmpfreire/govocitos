/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Celula.h
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

#ifndef _CELULA_H_
	#define _CELULA_H_

	#include <vector>
	#include <string>
	#include "NucleoCelula.h"

	using namespace std;

	class Celula
	{
		public:
			Celula();
			~Celula();
			Celula(const Celula &cl);
			int getIdCelula();
			string getClaseCelula();
			string getEstadoCelula();
			int getCoordMaxMin(int indice);
			double getDiametroCell();
			int getCelulaCandidata();
			double getAreaCelula();
			void setAreaCelula(double a);
			void setCelulaCandidata(int c);
			void setIdCelula(int idc);
			void setClaseCelula(const string &cc);
			void setEstadoCelula(const string &ec);
			void borraDatosVectorX();
			void borraDatosVectorY();
			void setCoordCellX(vector<int> cx);
			void setCoordCellY(vector<int> cy);
			void setCoordMaxMin(int indice, int coord);
			void setDiametroCell(double dc);
			vector<int> *getBordeCellX();
			vector<int> *getBordeCellY();
			const Celula &operator=(const Celula &cl);
		private:
			int idCelula;
			string claseCelula, estadoCelula;
			vector<int> bordeCoordX;
			vector<int> bordeCoordY;
			//Se almacena las coordenadas Max X e Y y Min X e Y de la celula
			//Posicion 0 Max X, Posicion 1 Min X, Posicion 2 Max Y, Posicion 3 Min Y
			int maxMinPuntosCell[4];
			double diametroCell;
			double areaCelula;
			NucleoCelula nucleoCell;
			int celulaCandidata;
	};

#endif //_CELULA_H_ 
