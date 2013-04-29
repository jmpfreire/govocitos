/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InterfazGovoctios.h
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

#ifndef _INTERFAZGOVOCITOS_H_
	#define _INTERFAZGOVOCITOS_H_

	#include <gtkmm.h>	

	#include "Interfaz/MenuBarraPrincipal.h"
	#include "Interfaz/BarraEstado.h"
	#include "Utiles.h"
	#include "Interfaz/Preferencias.h"
	#include "Config/ConfigGovocitos.h"
	#include "Interfaz/DialogoAGLocal.h"
	#include "Interfaz/PanelDibujado.h"
	#include "Interfaz/PanelPropiedades.h"
	#include "Interfaz/PanelDiametros.h"
	#include "Interfaz/PanelDatosEstadisticos.h"
	#include "Interfaz/PanelFecundidad.h"
	#include "Dialogos.h"

	class CoreGovocitos;

	class InterfazGovocitos : public Gtk::Window
	{    
		public:
			InterfazGovocitos();
			~InterfazGovocitos();
			void setControlador(CoreGovocitos &cg);
			void destruyeDatos();
			virtual void menuAbrir();
			virtual void menuCargarCoord();
			virtual void menuAbrirIC();
			virtual void menuAbrirRemoto();
			virtual void menuAbrirXmlRemoto();
			virtual void menuAbrirICRemoto();
			virtual void menuAbrirIndividuo();
			virtual void menuGuardar();
			virtual void menuGuardarComo();
			virtual void menuGuardarXmlBD();
			virtual void menuGuardarImagen();
			virtual void menuGuardarMascara();
			virtual void menuSalir();
			virtual void menuCerrar();
			virtual void menuPreferencias();
			virtual void menuAcercaDe();
			virtual void desHacer();
			virtual void reHacer();
			virtual void barraNoSupervised();
			virtual void barraEditor();
			virtual void activaRegilla();
			virtual void aumentaZoom();
			virtual void disminuyeZoom();
			virtual void originalZoom();
			virtual void ventanaZoom();
			//virtual void recortaOvocito();
			virtual void deteccionAutomactica();
			void finalDetecNoSupervisada();
			void finalizarDeteccionaAutomactica();
			virtual void clasificacionAutomactica();
			virtual void activaPanelAuxiliarDatos(int panel);
			virtual void seleccionaTodasCelulas();
			void exportCsvDatosCell();
			void exportCsvStadisticalData();
			void exporFecundidadCSV();
			void exporFecundidadBD();
			void exporRejillaBD();
			void dialogoCambios();
			void mensajeSinClasesEstados();
			PanelDibujado *getPanelDibujado();
			BarraEstado *getBarraEstado();
			PanelPropiedades *getPanelPropiedades();
			MenuBarraPrincipal *getMenuBarraPrincipal();
			PanelDiametros *getPanelDiametros();
			PanelDatosEstadisticos *getPanelEstadisticos();
			PanelFecundidad *getPanelFecundidad();
			bool getCambios();
			void setCambios(bool c);
		private:
			void menuPrincipal();
			void panelCentral();
			bool multiSelecPressRelease(GdkEventKey *event);
			//Atributos
			Gtk::VBox m_Box;
			Gtk::Notebook noteBookPrin;
			Gtk::HPaned panelC;
			Gtk::VPaned panelDatos;
			Gtk::ScrolledWindow scrollPanIzq;
			CoreGovocitos *driverGovocitos;
			MenuBarraPrincipal *menBarPrincipal;
			Preferencias *panelPreferencias;
			BarraEstado *bEstado;
			DialogoAGLocal *dialogoLocal;
			PanelDibujado *panelDibujo;
			PanelPropiedades *panelProp;
			PanelDiametros *datosD;
			PanelDatosEstadisticos *datosE;
			PanelFecundidad *panelFec;
			bool cambios;
	};
#endif //_INTERFAZGOVOCITOS_H_
