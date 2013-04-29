/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoMorfologico.h
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

#ifndef _CALCULOMORFOLOGICO_H_
	#define _CALCULOMORFOLOGICO_H_

	#include <math.h>
	#include <iostream>
	#include <gtkmm.h>

	#include "Estructuras/ListadoCelulas.h"
	#include "ScanFillLine.h"

	class CalculoMorfologico
	{
		public:
			static void setCalibracion(double calib);
			static int calcularPerimetro(Celula &cell);
			static int calcularPerimetro(vector<int> cX, vector<int> cY);
			static vector<double> calculoRedondez(Celula &cell, double area);
			static vector<int> calcularCentroide(Celula &cell);
			static double diametroAreaPuntos1(Celula &datosCelula);
			static double diametroAreaPuntos2(Celula &datosCelula);
			static vector<double> diametroAreaFormula(Celula &datosCelula);
			static vector<double> diametroCentroBorde(Celula &datosCelula);
		private:
			static int puntoEnCuadrante(int pos1, int pos2, vector<int> *x, vector<int> *y);
			static void centroide(vector<int> coordX, vector<int> coordY, double centro[]);
			static double maximo(double vector[], unsigned int fin );
			static double minimo(double vector[], unsigned int fin );
	};

#endif // _CALCULOMORFOLOGICO_H_
