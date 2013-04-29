/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelDatosEstadisticos.h
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _PANELDATOSESTADISTICOS_H_
	#define _PANELDATOSESTADISTICOS_H_

	#include <gtkmm.h>

	#include "Modulos/SistemaDibujado.h"
	#include "Interfaz/MenuSeleccion.h"
	#include "Interfaz/PanelDibujado.h"
	#include "Dialogos.h"
	#include "Modulos/CalculoEstadistico.h"

	class PanelDatosEstadisticos : public Gtk::VBox
	{
		public:
			PanelDatosEstadisticos(SistemaDibujado &sd, PanelDibujado &pd, Rejilla &rej,
			                       BarraEstado &be, vector<EstadoCelula> &est);
			~PanelDatosEstadisticos();
			void setListaCelulas(ListadoCelulas &lc);
			void cerrarCalEstadisticos();
			bool calculoEstadistico();	
			void selectFilaTreeEst();
			void writeDataStadistical(ofstream &ios) const;
			typedef sigc::signal<void> cierraPanelEstadistico;
			cierraPanelEstadistico signal_cierra_estadisticos();
		private:
			//Metodos
			void botonCerrarCalEstadisticos();
			void iniciarPanelDatosEstadisticos();
			void selecCelula();
			void reordenarPorColumnas();
			void datosFinalesEstadisticos(int numCel, int numPUsados, double areaTotal);
			double areaRejNoUsada();
			//Atributos
			Gtk::HBox hboxEstadisticos, *hboxPanelDatos;
			Gtk::ScrolledWindow scrollTotal, scrollEstadist, scrollFinales;
			Gtk::Label *nombrePanel;			
			Gtk::Button *cerrarPanelDatos;
			Gtk::VSeparator separador, separador1;
			SistemaDibujado *sistemDibujo;
			PanelDibujado *panelDibujo;
			cierraPanelEstadistico panelEstacierra;
			vector<EstadoCelula> *estados;
			ListadoCelulas *coordCelulas;
			vector<int> idCelulas;
			BarraEstado *bEstado;
			Rejilla *rejilla;
			//Datos finales
			Gtk::Label *numCelG, *punTotalG, *percentRejG, *percentNoCellG, *percentNoUseG;
			Gtk::VBox *vboxEst;
			
			//clases auxiliares
			//modelo treeview para todos los datos
			class ModelColumnsT : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumnsT(){add(colEstado);add(numPuntos);add(numCelulas);}
				Gtk::TreeModelColumn<string> colEstado;
				Gtk::TreeModelColumn<int> numPuntos;
				Gtk::TreeModelColumn<int> numCelulas;
			};
			//modelo treeview para los individuales de las celulas
			class ModelColumnsP : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumnsP(){add(numCol);add(colClase);add(colEstado);add(numPuntos); add(areaRejilla);}
				Gtk::TreeModelColumn<int> numCol;
				Gtk::TreeModelColumn<string> colClase;
				Gtk::TreeModelColumn<string> colEstado;
				Gtk::TreeModelColumn<int> numPuntos;
				Gtk::TreeModelColumn<double> areaRejilla;
			};
			
			Glib::RefPtr<Gtk::ListStore> refTreeModelCelula, refTreeModelTotales;
			Gtk::TreeView *treeviewEstadist, *treeviewTotales;
			ModelColumnsP columCelula;
			ModelColumnsT columTotales;
			
	};
#endif //_PANELDATOSESTADISTICOS_H_
