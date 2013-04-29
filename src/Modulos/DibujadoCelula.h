/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DibujadoCelula.h
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


#ifndef _DIBUJADOCELULA_H_
	#define _DIBUJADOCELULA_H_

	#include <gtkmm.h>
	#include <iostream>
	#include <gdkmm.h>
	#include <cairomm/context.h>
	#include <algorithm>

	#include "Estructuras/ListadoCelulas.h"
	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Fichero.h"
	#include "Utiles.h"
	#include "Modulos/CalculoMorfologico.h"
	
	using namespace std; 
	
	class DibujadoCelula
	{
		public:
			DibujadoCelula();
			~DibujadoCelula();
			void setZoomCelulas(double zoom);
			void borrarCelulaNueva();
			Celula getNuevaCelula();
			int getTamanhoNuevaCelula();
			vector<int> getNuevaCelulaX();
			vector<int> getNuevaCelulaY();
			bool getPuntosModif();
			bool getManoAlzada();
			bool getSeccionBorrada();
			bool getModificacion();
			bool getSelecMultiple();
			int getCelulaSeleccionada(int indice);
			void vaciaVectorCelulaSeleccionada();
			int getNumsCelulaSeleccionada();
			string getClaseCelulaSeleccionada(int s);
			string getEstadoCelulaSeleccionada(int s);
			string setClaseCelulaSeleccionada(const string &cl, int s);
			string setEstadoCelulaSeleccionada(const string &est, int s);
			void setSelecMultiple(bool s);
			void setSeccionBorrada(bool s);
			void setOperPoligono(ListadoCelulas lc);
			void setCelulaSeleccionada(int i);
			void setManoAlzada(bool valor);
			void setEdiCel(Gdk::Color ec);
			void setSeleCel(Gdk::Color sc);
			void setSinIdCel(Gdk::Color sic);
			void setGrosPunto(double gp);
			void setGrosLinea(double gl);
			void setContexCelulasPrin(Cairo::RefPtr<Cairo::ImageSurface> surfaceCelulas);
			void setContexCelulasSecun(Cairo::RefPtr<Cairo::ImageSurface> surfaceOperaciones);
			void setClaseEstado(vector<ClaseCelula> &cl, vector<EstadoCelula> &est);
			void setCoordenadasPoligonos(ListadoCelulas &lc);
			void setVisibleCapaCelulas(bool c);
			/**
			 Funcion inline que realiza el pintado del borde de las células.
			 */
			inline void pintaBorde()
			{	
				register int numPoligonos, numCoordPol, numClases;
				vector<double> color, dashes;
				Celula *cell;
				vector<int> *cx, *cy;
				string clasePunteada, claseSinPuntear, claseActual;
	
				if(visibleCapaCelulas)
				{
					numClases = clases->size();

					for(int j = 0; j < numClases; j++)
					{
						if((*clases)[j].getLinea() == 2)
						{
							clasePunteada = (*clases)[j].getEtiquetaClasificacion();
						}
						else if((*clases)[j].getLinea() == 1)
						{
							claseSinPuntear = (*clases)[j].getEtiquetaClasificacion();
						}
					}
		
					dashes.push_back((50.0 * zoomCelulas));
					dashes.push_back((30.0 * zoomCelulas));
					
					//Ancho de la linea de dibujo
					cr1->set_line_width(grosLinea * zoomCelulas);
					//Asignamos el numero de poligonos
					numPoligonos = coordCelulas->getNumCelulas();
					cr1->save();

					for(register int i = 0; i < numPoligonos; i++)
					{
						//Asignamos el poligno actual
						cell = coordCelulas->getCelula(i);
						cx = cell->getBordeCellX();
						cy = cell->getBordeCellY();
						claseActual = cell->getClaseCelula();
			
						if(claseActual == clasePunteada)
						{
							dashes[0] = (70 * zoomCelulas);
							cr1->set_dash(dashes, 0.0);
						}
						else if(claseActual == claseSinPuntear)
						{
							cr1->restore();
							cr1->save();
						}
						else
						{
							dashes[0] = (10 * zoomCelulas);
							cr1->set_dash(dashes, 0.0);
						}
			
						//Establecemos el color
						color = estableceColores(i);
						cr1->set_source_rgba(color[0], color[1], color[2],1);
		
						//Pinta el primer punto del poligono
						cr1->move_to(((*cx)[0] * zoomCelulas), ((*cy)[0] * zoomCelulas));
						//cr1->arc((double)((*cx)[0]), (double)((*cy)[0]), (1 * zoomCelulas), 0, 2 * M_PI);
						//Asigna el numero de coordenadas del poligono
						numCoordPol = cx->size();
	
						for(register int j = 1; j < numCoordPol; j++)
						{
							//Traza una linea entre distintos puntos (coordenadas)
							cr1->line_to(((*cx)[j] * zoomCelulas), ((*cy)[j] * zoomCelulas));
							//cr1->arc((double)((*cx)[j]), (double)((*cy)[j]), (1 * zoomCelulas), 0, 2 * M_PI);
						}
						//Cierra el poligono que bordea las celulas
						if(celulaModificandose != i)
						{
							cr1->close_path();
						}
						//Dibujamos la ruta
						cr1->stroke();
					}	
					cr1->restore();
				}
			};
			void busquedaCelula(const int &cX, const int &cY);
			void selecAllCells();
			bool puntoDentroCelula(int cX, int cY);
			void eliminaCelulaSeleccionada();
			void dibujarPuntosCelula(double cX, double cY);
			void repintadoPuntosCelulas();
			void manoAlzadaPuntoInicial(const int &cX, const int &cY); 
			/**
			 Funcion inline que realiza el pintado a mano alzada.
			 @param cx, int coordenada x.
			 @param cy, int coordenada y.
			 */
			inline void pintaManoAlzada(int cx, int cy)
			{
				//Añadimos las coordenadas en el poligono
				int tamV;

				tamV = nuevaCelulaX.size() - 1;

				if(nuevaCelulaX[tamV] != cx || nuevaCelulaY[tamV] != cy)
				{
					nuevaCelulaX.push_back((cx / zoomCelulas));
					nuevaCelulaY.push_back((cy / zoomCelulas));

				}
				
				//Dibujamos la linea entre puntos
				crLinea->line_to(cx, cy);
	
				crLinea->stroke_preserve();
			};
			bool agregaCelula();
			void addCellToListCells(bool cond = false);
			void modifcaCelula(const int &cX, const int &cY);
			void eliminaParteModif(const int &cX, const int &cY);
			void destruyeDatos();
		private:
			//Metodos
			bool compruebaCelulaSeleccionada(const int &numCel);
			void seleccionCelula(const int &indice);
			void buscaCoordCelula(int pos1[2], int pos2[2]);
			vector<double> estableceColores(const int &indice);
			void uneCelulaModificada();
			//Atributos
			double zoomCelulas, grosPunto, grosLinea;
			int numTotalPolig;
			bool manoAlzada, puntosModif, seccionBorrada, visibleCapaCelulas,
			modificacion, seleccionMultiple;
			ListadoCelulas *coordCelulas;
			Cairo::RefPtr<Cairo::Context> cr1;
			Cairo::RefPtr<Cairo::Context> crPuntos;
			Cairo::RefPtr<Cairo::Context> crLinea;
			Cairo::RefPtr<Cairo::Context> crModifi;
			double ediCelR, ediCelG, ediCelB, seleCelR, seleCelG, seleCelB;
			double sinIdCelR, sinIdCelG, sinIdCelB, divisor;
			vector<int> nuevaCelulaX, nuevaCelulaY;
			Celula *nuevaCelula;
			vector<ClaseCelula> *clases;
			vector<EstadoCelula> *estados;
			int modifPos1[2], modifPos2[2];
			int posi1, posi2;
			vector<int> celulaSeleccionada;
			int celulaModificandose;
	};

#endif // _DIBUJADOCELULA_H_
