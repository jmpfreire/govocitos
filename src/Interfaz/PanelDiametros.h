/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _PANELDIAMETROS_H_
	#define _PANELDIAMETROS_H_

	#include <iostream>
	#include <gtkmm.h>

	#include "Interfaz/PanelDibujado.h"
	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Interfaz/MenuSeleccion.h"
	#include "Modulos/CalculoMorfologico.h"
	#include "Dialogos.h"

	using namespace std;

	class PanelDiametros : public Gtk::VBox
	{
		public:
			PanelDiametros(PanelDibujado &pd, BarraEstado &be, vector<ClaseCelula> &cl, vector<EstadoCelula> &est);
			~PanelDiametros();
			void setCalibracion(bool c);
			void setCoordenadasPoligonos(ListadoCelulas &lc);
			void cerrarCalDiametros();
			void calculoDiametro();
			bool calculoDiametrosClass();
			void selectFilaTreeDiam();
			void writeDataDiameter(ofstream &ios) const;
			typedef sigc::signal<void> cierraPanelDiametros;
			cierraPanelDiametros signal_cierra_diametros();
		private:
			//Metodos
			void botonCerrarDiametros();
			void selecCelula();
			void reordenarPorColumnas();
			void datosFinalesDiametros();
			//Atributos
			PanelDibujado *panelDibuj;
			vector<ClaseCelula> *clases;
			vector<EstadoCelula> *estados;
			double micras;
			ListadoCelulas *coordCelulas;
			Gtk::ScrolledWindow scrollTreeView, scroollDatosFinales;
			Gtk::HBox *hboxPanelDatos;
			Gtk::Label *nombrePanel;			
			Gtk::Button *cerrarPanelDatos;
			Gtk::HBox boxFinal;
			Gtk::VSeparator separador;
			int numCelulas;
			BarraEstado *bEstado;
			bool calib;
			//Datos finales
			double diamMax, diamMin, redondezMax, redondezMin;
			//finales glade
			Gtk::VBox *vboxDiam;
			Gtk::Label *numCelulasG, *diamMaxG, *diamMinG, *redMaxG, *redMinG, *areaMinG, *areaMaxG;

			//modelo treeview
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumns(){add(numCol);add(colClase);add(colEstado);add(diamFormula);
					add(redondez);add(centroXY); add(areaCel); add(perimetro);
					/*add(diamCentroBorde);add(diamPuntos);add(diamPuntosSfl);*/}
				Gtk::TreeModelColumn<int> numCol;
				Gtk::TreeModelColumn<string> colClase;
				Gtk::TreeModelColumn<string> colEstado;
				/*Gtk::TreeModelColumn<float> diamCentroBorde;
				Gtk::TreeModelColumn<float> diamPuntos;
				Gtk::TreeModelColumn<float> diamPuntosSfl;*/
				Gtk::TreeModelColumn<float> diamFormula;
				Gtk::TreeModelColumn<int> areaCel;
				Gtk::TreeModelColumn<int> perimetro;
				Gtk::TreeModelColumn<float> redondez;
				Gtk::TreeModelColumn<string> centroXY;
			};
			Glib::RefPtr<Gtk::ListStore> refTreeModelCelula;
			Gtk::TreeView *treeviewDiametro;
			ModelColumns columCelula;
			cierraPanelDiametros panelDiamcierra;
	};
#endif // _PANELDIAMETROS_H_
