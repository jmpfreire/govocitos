/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelFecundidad.h
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


#ifndef _PANELFECUNDIDAD_H_
	#define _PANELFECUNDIDAD_H_

	#include <iostream>
	#include <gtkmm.h>

	#include "Utiles.h"
	#include "Modulos/Rejilla.h"
	#include "Interfaz/RejillaPersonalizada.h"
	#include "Modulos/CalculoFecundidad.h"
	#include "Config/ConfigGovocitos.h"
	#include "Modulos/ResultFecundidad.h"
	#include "Interfaz/PlotHistogram.h"

	using namespace std;

	class PanelFecundidad : public Gtk::ScrolledWindow
	{
		public:
			PanelFecundidad();
			~PanelFecundidad();
			bool getHistologicoK();
			bool getLupaK();
			bool getActivoPanelFec();
			void setActivoPanelFec(bool c);
			void setCalculoFecundidad(CalculoFecundidad &cF);
			void setRejilla(Rejilla &rej);
			void setConfiguracion(ConfigGovocitos &cfg);
			void setListaIndividuos(ListadoIndividuo &lv);
			void setListaResultadosImg(ResultFecundidad &lri);
			void setFrecuenciaDiametros(vector<double> fd);
			void configuraMetodoCalculoK();
			void preCalculaRejilla();
			void iniciarTreeViewDatosEstadisticos();
			void cargarImagenesMiniatura();
			void estableceDatosFecundidad();
			void recalcularFecundidad();
			void presentaHistograma();
			void writeDataDiameter(ofstream &ios) const;
			typedef sigc::signal<void> guardaDatos;
			guardaDatos signal_imprime_datos();
			typedef sigc::signal<void> guardaDatosBD;
			guardaDatosBD signal_datos_bd();
			typedef sigc::signal<void> guardaRejilla;
			guardaRejilla signal_datos_rejilla();
			void activaImprimeDatos();
			void activaGuardaDatosBD();
			void activaGuardarRejilla();
		private:
			void iniciaPanelFecundidad();
			void seleccionTipoRejilla();
			void setTipoCalculoK();
			void setOpcionesRej();
			void configurarRejilla();
			vector<double> datosObjetosTotales();
			vector<double> datosPuntosTotales(double &nUse);
			void selecImagen();
			void calculoFecundidadParcial(ResultadosImagen res, const string &nombre);
			//Atributos
			/*Interfaz*/
			Gtk::VBox *panelFecG;
			//Treeview y totales
			Gtk::Label *individuoG;
			Gtk::TreeView *treeviewPuntosG;
			//Rejilla y k
			Gtk::RadioButton *rejCompletaG, *rejPersonalG, *histologicoG, *diamLupaG;
			Gtk::Label *filRejG, *colRejG, *separRejG, *puntosRejG, *kFinalG;
			Gtk::Button *selecRejG, *LupaButton;
			//Resultados
			Gtk::Label *areaRejG, *numImagG, *numObjG, *pesoOvarioG;
			Gtk::Table *fecTotal, *fecParcial;
			Gtk::HBox *hboxFecContain, *hboxFecParcialContain;
			//Individual
			Gtk::VBox *vboxImg, *vboxPlot;
			Gtk::Label *labFecunParcG;
			//Botonoes
			Gtk::Button *exportCSVF, *saveBDFec;
			/**********/
			CalculoFecundidad *calcFecun;
			Rejilla *rejilla;
			ConfigGovocitos *configuracion;
			ListadoIndividuo *listIndiv;
			vector<OpcionesRej> *opcRej;
			vector<EstadoCelula> *estados;
			vector<int> estadosEnUso;
			ResultFecundidad *listResultados;
			vector<double> frecuenDiamet;
			vector<double> diametrosLupa;
			PlotHistogram *plot;
			guardaDatos operacionCSVDatos;
			guardaDatosBD operacionBDDatos;
			guardaRejilla operacionBDRejilla;
			bool fecundidadActivada;
			
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
				public:
					ModelColumns();
					ModelColumns(int numEstados, int nUs)
					{
						add(idCol);
						
						if(nUs != 0)
						{
							add(noUse);
						}

						for(int i = 0; i < (numEstados * 2); i++)
						{
							items = new Gtk::TreeModelColumn<int>();
							add(*items);

							itemList.push_back(items);
						}
					}
					Gtk::TreeModelColumn<int> getItem(int indice)
					{
						return *itemList[indice];
					}
					//Atributos
					Gtk::TreeModelColumn<string> idCol;
					Gtk::TreeModelColumn<int> noUse;
					vector<Gtk::TreeModelColumn<int> *> itemList;
					Gtk::TreeModelColumn<int> *items;
			};
			
			Glib::RefPtr<Gtk::ListStore> refTreeModelDatos;
			ModelColumns *columDatos;
	};
#endif //_PANELFECUNDIDAD_H_
