/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ListadoIndividuo.h
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

#ifndef _LISTADOINDIVIDUO_H_
	#define _LISTADOINDIVIDUO_H_

	#include <iostream>
	#include <vector>
	#include "Estructuras/ImageCells.h"
	#include "Estructuras/ResultadosImagen.h"

	using namespace std;

	class ListadoIndividuo
	{
		public:
			ListadoIndividuo();
			~ListadoIndividuo();
			ListadoIndividuo(const ListadoIndividuo &li);
			string getCampanhaInd();
			string getMuestreoInd();
			string getIndividuoInd();
			string getEspecieInd();
			int getNumImagenes();
			int getNumXmlAnalizados();
			double getPesoOvarioFresco();
			double getValorBeta();
			double getValorScherle();
			double getFormolFresco();
			void setPesoOvarioFresco(double d);
			void setValorBeta(double d);
			void setValorScherle(double d);
			void setFormolFresco(double d);
			void setCampanhaInd(const string &campI);
			void setMuestreoInd(const string &muestI);
			void setEspecieInd(const string &espI);
			void setResultadoImagenes(ResultadosImagen ri);
			void setIndividuoInd(const string &indI);
			void setImagenVector(ImageCells iw);
			void setCelulasImagen(ListadoCelulas lc);
			void incrementaImagenes();
			void incrementaXmlAnalizado();
			void borraImagenVector(int indice);
			void borraCelulasImagen(int indice);
			void vaciaVectorResultados();
			ResultadosImagen getResultadosImg(int indice);
			ImageCells *getImagenVector(int indice);
			ListadoCelulas *getCelulasVector(int indice);
			int getNumResultadoImagenes();
			int getTamanhoVectorImag();
			int getTamanhoVectorCelulas();
			const ListadoIndividuo &operator=(const ListadoIndividuo &li);
		private:
			string codigoCampanha, codigoMuestreo, codigoIndividuo, codigoEspecie;
			int numImagenes, numXmlAnalizados;
			vector<ImageCells> datosIndiv;
			vector<ListadoCelulas> datosCelulas;
			vector<ResultadosImagen> listaResult;
			double pesoOvarioFresco, valorBeta, valorScherle, formolFresco;
	};
#endif //_LISTADOINDIVIDUO_H_
