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

#ifndef _PANELPROPIEDADES_H_
	#define _PANELPROPIEDADES_H_

	#include <iostream>
	#include <gtkmm.h>
	#include "PanelDibujado.h"
	#include "Config/OpcionesRej.h"
	#include "Config/ConfigGovocitos.h"
	#include "RejillaPersonalizada.h"
	#include "Modulos/Rejilla.h"

	using namespace std;

	class PanelDibujado;
	class InterfazGovocitos;

	class PanelPropiedades : public Gtk::ScrolledWindow
	{
		public:
			PanelPropiedades(InterfazGovocitos &ig, PanelDibujado &pd);
			~PanelPropiedades();
			void setRejilla(Rejilla &rej);
			void iniciadorPanelDer();
			void cargaClasEstadPanel();
			void setConfiguracion(ConfigGovocitos &cfg);
			bool getAnhadirCel();
			bool getAnhadirCelManoAL();
			bool getAnhadirCelPT();
			bool getAnhadirCelManoALNSup();
			bool getAnhadirCelPTNSup();
			bool getModifCel();
			bool getModifCelNSup();
			bool getSelecCel();
			bool getSelecCelNSup();
			bool getNotUseAreaImage();
			int getPagBlocnotas();
			bool getRejillaDefec();
			void setPagBlocNotas(int pag);
			void setLabelPanel(const string &lab);
			void setSensitiveSelecCel(bool s);
			void setSensitiveAnhadirCelManoAL(bool s);
			void setSensitiveAnhadirCelPT(bool s);
			void setSensitiveEliminaCelula(bool s);
			void setSensitiveSelecClase(bool cl);
			void setSensitiveSelecEstado(bool est);
			void setSensitiveUnePuntos(bool s);
			void setSensitiveCalcDiam(bool); 
			void setSentiviePrintData(bool c);
			void setSensitivePrinData1(bool c);
			void setActivaRejilla(bool c);
			void setActivaBordeRej(bool c);
			void setSeleccionaClase(const string &t);
			void setSeleccionaEstado(const string &t);			
			void setActiveSelec(bool s);
			void setActiveRejillaDefec(bool s);
			void setOpcionesRej();
			void setValorMicras(double m);
			void cierraPaneLateral();
			void activaRejilla();
			void activaBordeRejilla();
			void setSensiblePanel();
			void activaCapaCelulas();
			void preCalculaRejilla();
			typedef sigc::signal<void> modificaClasEstadoC;
			modificaClasEstadoC signal_modifica_classEstado();
			typedef sigc::signal<void, int> abrePanelDatos;
			abrePanelDatos signal_abre_datos();
			void activaVistaDatos(int numSen);
		private:
			//Metodos
			void estableceClase();
			void estableceEstado();			
			void configurarRejilla();
			//Atributos
			PanelDibujado *panelDibuj;
			Gtk::VBox *panDer;
			Gtk::Notebook *blocNotas;
			Gtk::Button *cierraPanel, *UnePuntos, *EliminaCelula, *selectAllG, 
			*calcDiamet, *calcEstadist, *confRej, *calcTodosDiam, *printDataG, *printDataG1;
			Gtk::CheckButton *activCapaCelE, *activCapaCelR, *activaCapaRejR, *activaBordeRejR;
			Gtk::Label *panelP;
			Gtk::Label *nFilasR, *nColR, *nPunR, *separR;
			Gtk::RadioButton *AnhadirCel, *ModifCel, *AnhadirCelManoAL, *AnhadirCelPT,
			*SelecCel, *rejillaDefec, *rejillaPersonal;
			Gtk::HBox *hboxClases, *hboxEstados;
			Gtk::ComboBoxText selecionaClase, selecionaEstado;
			vector<ClaseCelula> *clases;
			vector<EstadoCelula> *estados;
			vector<OpcionesRej> *opcRej;
			//ModoEdicionNoSupervisado
			Gtk::Button *printDataGNSup, *EliminaCelulaNSup, *UnePuntosNSup;
			Gtk::RadioButton *ModifCelNSup, *AnhadirCelManoALNSup, *AnhadirCelPTNSup, *SelecCelNSup, *NotUseAreaG;
			double micras;
			InterfazGovocitos *interfazPrincipal;
			modificaClasEstadoC modifClaseEstado;
			abrePanelDatos panelDatosAbierto;
			ConfigGovocitos *configuracion;
			Rejilla *rejilla;
	};
#endif // _PANELPROPIEDADES_H_
