/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ResultFecundidad.h
 * Copyright (C) José Manuel Pintor Freire 2011 <jpfreire@correo.ei.uvigo.es>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _RESULTFECUNDIDAD_H_
	#define _RESULTFECUNDIDAD_H_

	#include <vector>
	#include "Estructuras/ResultadosImagen.h"
	#include <string>
	#include <iostream>

	using namespace std;

	class ResultFecundidad
	{
		public:
			ResultFecundidad();
			~ResultFecundidad();
			ResultFecundidad(const ResultFecundidad &lr);
			void inicializaResulFec(int numEstados);
			double getFecundidadEst(int indice);
			double getValorK();
			int getNumOvocitos();
			double getAreaRejilla();
			int getNumImagenes();
			int getIdRejilla();
			string getMetodoCalculo();
			void setFecundidadEst(double f, int indice);
			void setAreaRejilla(double a);
			void setNumOvocitos(int num);
			void setValorK(double k);
			void setNumImagenes(int nI);
			void setIdRejilla(int id);
			void setMetodoCalculo(const string &m);
			const ResultFecundidad &operator=(const ResultFecundidad &lr);
		private:
			double valorK;
			int numOvocitos, numImagenes, idRejilla;
			double areaRejilla; //en centimetros cuadrados
			vector<double> fecundidadEst;
			string metodoCalc;
	};
#endif //_RESULTFECUNDIDAD_H_
