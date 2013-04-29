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

#ifndef _PREFERENCIAS_H_
	#define _PREFERENCIAS_H_

	#include <libglademm.h>
	#include <iostream>
	#include <gtkmm.h>
	#include <vector>
	#include <glibmm.h>

	#include "Config/OpcionesPref.h"
	#include "Config/OpcionesRej.h"
	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Dialogos.h"

	using namespace std;
	
	class Preferencias : public Gtk::Dialog
	{
		public:
			Preferencias(OpcionesPref opc, vector<ClaseCelula> cc, vector<EstadoCelula> ce, vector<OpcionesRej> rej);
			~Preferencias();
			void mostrarDialogoP();
			void initDialogoPreferencias();
			OpcionesPref getOpcionesPref();
			vector<ClaseCelula> getClasesCelula();
			vector<EstadoCelula> getEstadosCelula();
			vector<OpcionesRej> getOpcionesRej();
			bool getModifi();
			void setModifi(bool cond);
			void setPaginaPreferencias(int pg);
		private:
			void cargaDatosGenerales();
			void pulsarBotonAceptar();
			void pulsarBotonCerrar();
			void pulsarBotonRevertir();
			void asignarRutaImag();
			void asignarRutaCel();
			void asignarRutaCSV();
			void cambiaColEstado();
			void cambiaLineaClass();
			void selecUsoDispClEst(int opc);
			void addClaseDispUso(bool opc);
			void addEstDispUso(bool opc);
			void seleccionaClase();
			void seleccionaEstado();
			void iniciadorClassEstado();
			void guardarRejilla();
			void reordenarPorColumnas();
			void iniciadorRejilla();
			void borraDatosForm(GtkNotebookPage* bloc,guint pag);
			bool datosCorrectorForm();
			void selecPref();//selecciona la opcion del menu disponible
			void iniciadorPreferencias();//crea el treeview del menu principal
			//Atributos
			Gtk::Dialog *dialogoPref;
			Gtk::TreeView *treeviewGeneral;
			Gtk::Label *labelTitulo;
			Gtk::Notebook *blocNotas;
			//Clases y Estados
			Gtk::TreeView *clDisp, *clUso, *estDisp, *estUso;
			Gtk::Button *addClase, *removeClase, *addEstado, *removeEstado;
			//Clases
			Gtk::Entry *clasesG, *nomClasesG;
			Gtk::TextView *descripClasesG;
			Gtk::TreeView *treeviewClasesG;
			Gtk::ComboBox *claseLinea;
			//Estados
			Gtk::Entry *estadosG, *nomEstadosG;
			Gtk::TextView *descripEstadosG;
			Gtk::TreeView *treeviewEstadosG;
			Gtk::ColorButton *colorEstadosG;
			//Editor
			Gtk::ColorButton *celSDetG, *seleCelG, *ediCelG;
			Gtk::SpinButton *grosLineaG, *grosPuntoG;
			//Directorios
			Gtk::Entry *archivImagG, *archivCelG, *archivCSVG;
			Gtk::FileChooserButton *selecImagG, *selecCelG, *selecCSVG;
			//Rejilla
			Gtk::ColorButton *limDIG, *limISG, *colRejG;
			Gtk::SpinButton *grosRejG, *separPuntosG, *grosBordeRejG;
			//Gtk::CheckButton *bordeRejComp;
			//Rejilla personalizada
			Gtk::SpinButton *separPuntosGPD, *numColumnsG, *numFilasG;
			Gtk::Button *guardarRejG;
			Gtk::TreeView *treeviewRejG;
			//Base de datos
			Gtk::Entry *loginBDG, *passBDG, *rutaBDG, *databaseBDG;
			//Secure FTP
			Gtk::Entry *rutaSFTP, *loginSFTP, *passSFTP, *pathSFTP;
			//Cache imagenes
			Gtk::Entry *cacheImagenesG;
			Gtk::SpinButton *tamCacheG;
			//Boton cerrar
			Gtk::Button *botonCerrar, *botonAceptar, *botonRevertir;
			//Colores
			Gdk::Color celSDet, seleCel, ediCel, limDI, limIS, colRej;
			//Objeto que guarda el archivo de configuracion
			OpcionesPref copiaPreferencias;
			//Clases y estados
			vector<ClaseCelula> copiaClaseCelula;
			vector<EstadoCelula> copiaEstadoCelula;
			//Opciones rejilla
			vector<OpcionesRej> copiaOpcRej;
			
			int indiceClassEstado;
			bool modificacion;

			//modelo treeview para la rejilla
			class ModelColRej : public Gtk::TreeModel::ColumnRecord
			{
				public:
					ModelColRej(){add(idCol); add(nCol); add(nFil); add(separP); add(numP);}
					Gtk::TreeModelColumn<int> idCol;
					Gtk::TreeModelColumn<int> nCol;
					Gtk::TreeModelColumn<int> nFil;
					Gtk::TreeModelColumn<int> separP;
					Gtk::TreeModelColumn<int> numP;
			};

			Glib::RefPtr<Gtk::ListStore> refTreeModelRej;
			ModelColRej columModelRej;
			
			//modelo treeview
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumns(){add(nomCol);}
				Gtk::TreeModelColumn<string> nomCol;
			};
			Glib::RefPtr<Gtk::ListStore> refTreeModelEtiq, refTreeModelClass, 
			refTreeModelClUso, refTreeModelClDisp, refTreeModelEstUso, refTreeModelEstDisp;
			Glib::RefPtr<Gtk::TreeStore> refTreeModelDialog;
			ModelColumns columModel;
			Gtk::TreeModel::iterator iterG, iter;
	};
#endif // _PREFERENCIAS_H_
