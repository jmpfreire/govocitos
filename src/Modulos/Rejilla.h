/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2008 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _REJILLA_H_
	#define _REJILLA_H_

	#include <gtkmm.h>
	#include <iostream>
	#include <gdkmm.h>
	#include <cairomm/context.h>

	#include "Estructuras/EstadoCelula.h"
	#include "Modulos/DibujadoCelula.h"
	
	using namespace std;

	class Rejilla
	{
		public:
			Rejilla();
			~Rejilla();
			int getBordeMaxX();
			int getBordeMaxY();
			int getBordeMinX();
			int getBordeMinY();
			bool getBordeActivo();
			bool getVisibleCapaRejilla();
			int getSeparPuntos();
			int getNumFilas();
			int getNumColumnas();
			int getNumPuntos();
			int getAncho();
			int getAlto();
			int getAltoRej();
			int getAnchoRej();
			vector<vector<int> > *getVectorRejilla();
			int getID();
			void setZoomRejilla(double zoom);
			void setVisibleCapaRejilla(bool vc);
			void setBordeComp(bool cond);
			void setLimIS(Gdk::Color is);
			void setLimDI(Gdk::Color di);
			void setColRej(Gdk::Color rej);
			void setGrosRej(double gr);
			void setSeparPun(double sp);
			void setNumFilas(int nf);
			void setNumColumnas(int nc);
			void setAlto(int al);
			void setAncho(int ac);
			void setAnchoRej(int acR);
			void setAltoRej(int alR);
			void setGrosBordeRej(double gbr);
			void setContexRejilla(Cairo::RefPtr<Cairo::ImageSurface> surfaceRejilla);
			void setEstado(vector<EstadoCelula> &est);
			void setID(int id);
			Cairo::RefPtr<Cairo::Context> getCairoContext();
			void calculaRejilla();
			void pintaRejilla();
			void pintaBordeRejilla();		
		private:
			Cairo::RefPtr<Cairo::Context> crRej;
			Cairo::RefPtr<Cairo::Context> crLat;
			double limISR, limISG, limISB, limDIR, limDIG, limDIB, colRejR, colRejG, colRejB;
			double grosRej, divisor, grosBordeRej;
			//En cada i se guarda todas las x de la rejilla y la y en la primera posicion
			vector<vector<int> > puntosRejilla;
			vector<EstadoCelula> *estados;
			bool bordeAct, visibleCapaRejilla;
			int bordeMaxY, bordeMaxX, bordeMinY, bordeMinX;
			ListadoCelulas *coordCelulas;
			//Rejilla
			double separPun;
			int numFilas, numColumnas, numPuntos;
			int ancho, alto;
			int anchoR, altoR;
			double zoomRej;
			int idRej;
	};
#endif // _REJILLA_H_
