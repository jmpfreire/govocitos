/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DeteccionAut.h
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

#ifndef _DETECCIONAUT_H_
	#define  _DETECCIONAUT_H_

	#include <iostream>
	#include "Estructuras/ListadoCelulas.h"
	#include "Interfaz/DialogoBarraProgres.h"
	#include "Estructuras/Celula.h"
	#include "Utiles.h"
	#include "Bordes/image.h"
	#include <time.h>
	#include "Dialogos.h"
	#include "image.h"

	using namespace std;

	class DeteccionAut
	{
		public:
			DeteccionAut();
			~DeteccionAut();
			DeteccionAut(const DeteccionAut &d);
			void setCalibracion(double calib);
			void setRutaImagen(const string &r);
			void setListadoCelulas(ListadoCelulas &lc);
			void setDiametrosMaxMin(double max, double min);
			bool deteccionBordesNoSupervisado();
			void deteccionBordesSupervisado(vector <int> x, vector <int> y);
			void pasoCoordSistemaGovocitos(PointList *p);
			void pasoCoordGovocitosPointList(PointList  **nsd);
			const DeteccionAut &operator=(const DeteccionAut &d);
		private:
			//Atributos
			ListadoCelulas *vectorPol;
			string ruta;
			PointList **contour;
			int num_edges;
			Image * img, *img_grey;
			int  num_rows, num_cols;
			double diamMax, diamMin;
			double calibracion;
			int MIN_DIAMETER;
			int MAX_DIAMETER;
	};
#endif // _DETECCIONAUT_H_
