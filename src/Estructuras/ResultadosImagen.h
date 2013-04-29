/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ResultadosImagen.h
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

#ifndef _RESULTADOSIMAGEN_H_
	#define  _RESULTADOSIMAGEN_H_

	#include <vector>

	using namespace std;

	class ResultadosImagen
	{
		public:
			ResultadosImagen();
			~ResultadosImagen();
			ResultadosImagen(const ResultadosImagen &ri);
			void inicializarNumPunObj(int numEst);			
			double getNumPun(int indice);
			double getNumObj(int indice);
			double getnumPunAreaNoUse();
			vector<double> getDiametros();
			void setNumObj(double no, int indice);
			void setNumPun(double no, int indice);
			void setnumPunAreaNoUse(double np);
			void setDiametros(double d);
			const ResultadosImagen &operator=(const ResultadosImagen &ri);
		private:
			vector<double> numObj;
			vector<double> numPun;
			double numAreaNoUse;
			vector<double> diametros;
	};
#endif //_RESULTADOSIMAGEN_H_
