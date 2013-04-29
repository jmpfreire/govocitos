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

#include "MenuBarraPrincipal.h"
#include "InterfazGovocitos.h"

/**
 Constructor
 */
MenuBarraPrincipal::MenuBarraPrincipal(InterfazGovocitos &inter)
{
	interfazPrincipal = &inter;
	
	InicializaMenuBarraPrincipal();
	
	CreaUIManagerMenu();
		
	//Establecemos la sensibilidad de las opciones principales
	estableceMenuPosiconInicial();
}

/**
 Destructor
 */
MenuBarraPrincipal::~MenuBarraPrincipal()
{
	
}

/**
 Devuelve el ui manager
 */
Glib::RefPtr<Gtk::UIManager> MenuBarraPrincipal::getUIManager()
{
	return xmlMPrincipal;
}

/**
 Devuelve el widget asocioado al menu principal
 */
Gtk::Widget *MenuBarraPrincipal::getWidgetMenuBarraPrincipal(const string &tipo)
{
	return xmlMPrincipal->get_widget(tipo);
}

/**
 Establece la sensibilidad del menu pasado en la variable string menu. Si condicion
 es verdadero el menu es sensible en caso contrario no es sensible
 @param menu string del menu que queremos hacer sensible o no
 @param condicion si es verdadero el menu es sensible en caso contrario no es sensible
 por defecto es falso si no se le pasa condicion
 */
void MenuBarraPrincipal::setSensitiveOpcMenu(const string &menu, bool condicion)
{
	mPrincipal->get_action(menu)->set_sensitive(condicion);
}

/**
 Hace sensibles las opciones basicas y desabilida deshacer y rehacer
 */
void MenuBarraPrincipal::setSensibleOpcionesBasicas()
{
	mPrincipal->get_action("SubMenuZoomOut")->set_sensitive(true);
	mPrincipal->get_action("SubMenuZoomVentana")->set_sensitive(true);
	mPrincipal->get_action("SubMenuCargarCoord")->set_sensitive(true);
	mPrincipal->get_action("SubMenuCerrar")->set_sensitive(true);
	mPrincipal->get_action("SubMenuGuardar")->set_sensitive(true);
	mPrincipal->get_action("SubMenuGuardarComo")->set_sensitive(true);
	mPrincipal->get_action("SubMenuGuardarImagen")->set_sensitive(true);
	mPrincipal->get_action("SubMenuEditor")->set_sensitive(true);
	mPrincipal->get_action("SubMenuRejilla")->set_sensitive(true);
	mPrincipal->get_action("SubMenuRehacer")->set_sensitive(false);
	mPrincipal->get_action("SubMenuDeshacer")->set_sensitive(false);
}

/**
 Establece las opciones del menu al modo de inicio
 */
void MenuBarraPrincipal::estableceMenuPosiconInicial()
{
	mPrincipal->get_action("SubMenuCargarCoord")->set_sensitive(false);
	mPrincipal->get_action("SubMenuGuardar")->set_sensitive(false);
	mPrincipal->get_action("SubMenuGuardarComo")->set_sensitive(false);
	mPrincipal->get_action("SubMenuZoom100")->set_sensitive(false);
	mPrincipal->get_action("SubMenuZoomVentana")->set_sensitive(false);
	mPrincipal->get_action("SubMenuZoomIn")->set_sensitive(false);
	mPrincipal->get_action("SubMenuZoomOut")->set_sensitive(false);
	mPrincipal->get_action("SubMenuEditor")->set_sensitive(false);
	mPrincipal->get_action("SubMenuRejilla")->set_sensitive(false);
	mPrincipal->get_action("SubMenuRehacer")->set_sensitive(false);
	mPrincipal->get_action("SubMenuDeshacer")->set_sensitive(false);
	mPrincipal->get_action("SubCalcularEstadist")->set_sensitive(false);
	mPrincipal->get_action("SubCalcularDiam")->set_sensitive(false);
	mPrincipal->get_action("SubCalcularUnDiam")->set_sensitive(false);
	mPrincipal->get_action("SubMenuCerrar")->set_sensitive(false);
	mPrincipal->get_action("SubMenuAbrirXmlRemoto")->set_sensitive(false);
	mPrincipal->get_action("SubMenuGuardarImagen")->set_sensitive(false);
	mPrincipal->get_action("SubMenuDeteccionSupervisada1")->set_sensitive(false);
	mPrincipal->get_action("SubMenuClasificacion")->set_sensitive(false);
	mPrincipal->get_action("MenuServidor")->set_sensitive(false);
//	mPrincipal->get_action("SubMenuAvanzado")->set_sensitive(false);
	mPrincipal->get_action("SubMenuGuardarMascara")->set_sensitive(false);
	mPrincipal->get_action("SubMenuSeleccionar")->set_sensitive(false);
	mPrincipal->get_action("SubMenuGuardarBD")->set_sensitive(false);
}

/**
 Inicializa el menu principal y barra de herramientas
 */
void MenuBarraPrincipal::InicializaMenuBarraPrincipal()
{
	mPrincipal = Gtk::ActionGroup::create();
	
	//Menu Archivo
	//mPrincipal->add(Gtk::Action::create("MenuArchivo", "_Archivo"));
	mPrincipal->add(Gtk::Action::create("MenuArchivo", "_File"));

	//mPrincipal->add(Gtk::Action::create("SubMenuIndividuo",Gtk::Stock::OPEN,"Abrir Individuo"),
					//Gtk::AccelKey("<control>H"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirIndividuo));
	mPrincipal->add(Gtk::Action::create("SubMenuIndividuo",Gtk::Stock::OPEN,"Calculate Fecunditiy"),
					Gtk::AccelKey("<control>F"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirIndividuo));


	//mPrincipal->add(Gtk::Action::create("SubMenuCerrar",Gtk::Stock::CANCEL,"Cerrar Imagen"),
					//Gtk::AccelKey("<control>H"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuCerrar));
	mPrincipal->add(Gtk::Action::create("SubMenuCerrar",Gtk::Stock::CANCEL,"Close Image"),
					Gtk::AccelKey("<control>C"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuCerrar));


	//mPrincipal->add(Gtk::Action::create("SubMenuSalir",Gtk::Stock::QUIT,"Salir"),
					//Gtk::AccelKey("<control>S"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuSalir));
	mPrincipal->add(Gtk::Action::create("SubMenuSalir",Gtk::Stock::QUIT,"Exit"),
					Gtk::AccelKey("<control>S"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuSalir));
	//Menu Local
	mPrincipal->add(Gtk::Action::create("MenuLocal", "_Local"));
	//Submenu Archivo
	//mPrincipal->add(Gtk::Action::create("SubMenuAbrir",Gtk::Stock::OPEN,
								//		"Abrir Imagen"),
					//Gtk::AccelKey("<control>a"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrir));
	mPrincipal->add(Gtk::Action::create("SubMenuAbrir",Gtk::Stock::OPEN,
										"Open Image"),
					Gtk::AccelKey("<control>O"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrir));
	//mPrincipal->add(Gtk::Action::create("SubMenuCargarCoord",Gtk::Stock::ADD,
					//					"Abrir Celulas"),
					//Gtk::AccelKey("<control>F"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuCargarCoord));
	mPrincipal->add(Gtk::Action::create("SubMenuCargarCoord",Gtk::Stock::ADD,
										"Open Cells"),
					Gtk::AccelKey("<control>Q"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuCargarCoord));

	//mPrincipal->add(Gtk::Action::create("SubMenuAbrirIC",Gtk::Stock::OPEN,
					//					"Abrir Imagen-Células"),
					//Gtk::AccelKey("<control>J"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirIC));
	mPrincipal->add(Gtk::Action::create("SubMenuAbrirIC",Gtk::Stock::OPEN,
										"Open Image and Cells"),
					Gtk::AccelKey("<control>J"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirIC));

	//Menu Servidor
	//mPrincipal->add(Gtk::Action::create("MenuServidor", "_Servidor"));
	mPrincipal->add(Gtk::Action::create("MenuServidor", "_Server"));

	//Submenu Archivo
	//mPrincipal->add(Gtk::Action::create("SubMenuAbrirRemoto",Gtk::Stock::OPEN,
		//								"Abrir Imagen"),
				//	Gtk::AccelKey("<control>ar"),
				//	sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirRemoto));
	mPrincipal->add(Gtk::Action::create("SubMenuAbrirRemoto",Gtk::Stock::OPEN,
										"Open Image"),
					Gtk::AccelKey("<control>R"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirRemoto));
	//mPrincipal->add(Gtk::Action::create("SubMenuAbrirXmlRemoto",Gtk::Stock::OPEN,
			//							"Abrir Celulas"),
			//		Gtk::AccelKey("<control>ax"),
			//		sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirXmlRemoto));
	mPrincipal->add(Gtk::Action::create("SubMenuAbrirXmlRemoto",Gtk::Stock::OPEN,
										"Open Cells"),
					Gtk::AccelKey("<control>B"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirXmlRemoto));
	mPrincipal->add(Gtk::Action::create("SubMenuAbrirICRemoto",Gtk::Stock::OPEN,
										"Open Image and Cells"),
					Gtk::AccelKey("<control>I"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrirICRemoto));

	
	//Menu Guardar
	//mPrincipal->add(Gtk::Action::create("MenuGuardar", "_Guardar"));
	mPrincipal->add(Gtk::Action::create("MenuGuardar", "_Save"));
	//SubMenu Guardar
	//mPrincipal->add(Gtk::Action::create("SubMenuGuardar",Gtk::Stock::SAVE,"Guardar"),
					//Gtk::AccelKey("<control>G"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardar));
	mPrincipal->add(Gtk::Action::create("SubMenuGuardarBD",Gtk::Stock::SAVE,"Save Cells DB"),
					Gtk::AccelKey("<control>G"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarXmlBD));
	mPrincipal->add(Gtk::Action::create("SubMenuGuardar",Gtk::Stock::SAVE,"Save Cells"),
					Gtk::AccelKey("<control>M"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardar));

	//mPrincipal->add(Gtk::Action::create("SubMenuGuardarComo",Gtk::Stock::SAVE_AS,
			//							"Guardar Como"),
			//		Gtk::AccelKey("<control><shift>G"),
			//		sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarComo));
	mPrincipal->add(Gtk::Action::create("SubMenuGuardarComo",Gtk::Stock::SAVE_AS,
										"Save Cells As"),
					Gtk::AccelKey("<control><shift>G"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarComo));
	//mPrincipal->add(Gtk::Action::create("SubMenuGuardarImagen",Gtk::Stock::SAVE_AS,
					//					"Guardar Imagen"),
					//Gtk::AccelKey("<control><shift>I"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarImagen));
	mPrincipal->add(Gtk::Action::create("SubMenuGuardarImagen",Gtk::Stock::SAVE_AS,
										"Save Image"),
					Gtk::AccelKey("<control><shift>I"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarImagen));
	//mPrincipal->add(Gtk::Action::create("SubMenuGuardarMascara",Gtk::Stock::SAVE_AS,
				//						"Guardar Mascara"),
				//	Gtk::AccelKey("<control><shift>I"),
				//	sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarMascara));
	mPrincipal->add(Gtk::Action::create("SubMenuGuardarMascara",Gtk::Stock::SAVE_AS,
										"Save Mask"),
					Gtk::AccelKey("<control><shift>M"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuGuardarMascara));
	
	//Menu Editar 
	//mPrincipal->add(Gtk::Action::create("MenuEditar", "_Editar"));
	mPrincipal->add(Gtk::Action::create("MenuEditar", "_Edit"));
	//Submenu Editar
	mPrincipal->add(Gtk::Action::create("SubMenuSeleccionar",Gtk::Stock::PREFERENCES, "Select all cells"),
					Gtk::AccelKey("<control>E"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::seleccionaTodasCelulas));
	
	//mPrincipal->add(Gtk::Action::create("SubMenuPreferencias",Gtk::Stock::PREFERENCES, "Preferencias"),
					//Gtk::AccelKey("<control>P"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuPreferencias));
	mPrincipal->add(Gtk::Action::create("SubMenuPreferencias",Gtk::Stock::PREFERENCES, "Preferences"),
					Gtk::AccelKey("<control>P"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuPreferencias));

	//mPrincipal->add(Gtk::Action::create("SubMenuDeshacer",Gtk::Stock::UNDO, "Deshacer"),
				//	Gtk::AccelKey("<control>D"),
				//	sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::desHacer));
	mPrincipal->add(Gtk::Action::create("SubMenuDeshacer",Gtk::Stock::UNDO, "Undo"),
					Gtk::AccelKey("<control>D"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::desHacer));
	//mPrincipal->add(Gtk::Action::create("SubMenuRehacer",Gtk::Stock::REDO, "Rehacer"),
		//			Gtk::AccelKey("<control>R"),
		//			sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::reHacer));
	mPrincipal->add(Gtk::Action::create("SubMenuRehacer",Gtk::Stock::REDO, "Redo"),
					Gtk::AccelKey("<control>U"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::reHacer));
	
	
	//Menu Ver
	//mPrincipal->add(Gtk::Action::create("MenuVer", "_Ver"));
	mPrincipal->add(Gtk::Action::create("MenuVer", "_View"));
	//Submenu Ver
	//mPrincipal->add(Gtk::Action::create("SubMenuZoomIn",Gtk::Stock::ZOOM_IN, "Ampliar"),
					//Gtk::AccelKey("<control>I"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::aumentaZoom));
	mPrincipal->add(Gtk::Action::create("SubMenuZoomIn",Gtk::Stock::ZOOM_IN, "Zoom In"),
					Gtk::AccelKey("<control>+"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::aumentaZoom));
	//mPrincipal->add(Gtk::Action::create("SubMenuZoomOut",Gtk::Stock::ZOOM_OUT, "Reducir"),
					//Gtk::AccelKey("<control>O"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::disminuyeZoom));
	mPrincipal->add(Gtk::Action::create("SubMenuZoomOut",Gtk::Stock::ZOOM_OUT, "Zoom Out"),
					Gtk::AccelKey("<control>-"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::disminuyeZoom));
	//mPrincipal->add(Gtk::Action::create("SubMenuZoom100",Gtk::Stock::ZOOM_100, "Tamaño normal"),
					//Gtk::AccelKey("<control>T"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::originalZoom));
	mPrincipal->add(Gtk::Action::create("SubMenuZoom100",Gtk::Stock::ZOOM_100, "Original Zoom"),
					Gtk::AccelKey("<control>V"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::originalZoom));
	//mPrincipal->add(Gtk::Action::create("SubMenuZoomVentana",Gtk::Stock::ZOOM_FIT, "Ajuste óptimo"),
	//				Gtk::AccelKey("<control>V"),
	//				sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::ventanaZoom));
	mPrincipal->add(Gtk::Action::create("SubMenuZoomVentana",Gtk::Stock::ZOOM_FIT, "Zoom Fit"),
					Gtk::AccelKey("<control>W"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::ventanaZoom));
	
	//Menu Herramientas
	//mPrincipal->add(Gtk::Action::create("MenuHerramientas", "_Herramientas"));
	mPrincipal->add(Gtk::Action::create("MenuHerramientas", "_Tools"));
	//Submenu Herramientas
	//mPrincipal->add(Gtk::Action::create("SubMenuEditor",Gtk::Stock::SELECT_COLOR,
					//					"Panel Editor"),
					//Gtk::AccelKey("<control>E"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::barraEditor));
	mPrincipal->add(Gtk::Action::create("SubMenuEditor",Gtk::Stock::SELECT_COLOR,
										"Edition Panel"),
					Gtk::AccelKey("<control>T"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::barraEditor));
	//mPrincipal->add(Gtk::Action::create("SubMenuRejilla",Gtk::Stock::APPLY,
					//					"Panel Rejilla"),
					//Gtk::AccelKey("<control>R"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaRegilla));
	mPrincipal->add(Gtk::Action::create("SubMenuRejilla",Gtk::Stock::APPLY,
										"Grid Panel"),
					Gtk::AccelKey("<control>N"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaRegilla));

	//Menu Calculos
	//mPrincipal->add(Gtk::Action::create("MenuCalcular", "_Calcular"));
	mPrincipal->add(Gtk::Action::create("MenuCalcular", "_Calculations"));
	//Submenu diametros
	//mPrincipal->add(Gtk::Action::create("MenuDiametro", "_Diametros"));
	mPrincipal->add(Gtk::Action::create("MenuDiametro", "_Diameters"));
	//Submenu Calculos
	//mPrincipal->add(Gtk::Action::create("SubCalcularDiam",Gtk::Stock::INFO, "Todas las células"),
					//Gtk::AccelKey("<control>N"),
					//sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 2));
	mPrincipal->add(Gtk::Action::create("SubCalcularDiam",Gtk::Stock::INFO, "All the cells"),
					Gtk::AccelKey("<control><shift>N"),
					sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 2));
	
	//mPrincipal->add(Gtk::Action::create("SubCalcularUnDiam",Gtk::Stock::INFO, "Una Célula"),
					//Gtk::AccelKey("<control>U"),
					//sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 1));
	mPrincipal->add(Gtk::Action::create("SubCalcularUnDiam",Gtk::Stock::INFO, "One cell"),
					Gtk::AccelKey("<control><shift>U"),
					sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 1));
	
	//mPrincipal->add(Gtk::Action::create("SubCalcularEstadist",Gtk::Stock::INFO,"Número de puntos"),
					//Gtk::AccelKey("<control>P"),
					//sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 3));
	mPrincipal->add(Gtk::Action::create("SubCalcularEstadist",Gtk::Stock::INFO,"Data"),
					Gtk::AccelKey("<control><shift>P"),
					sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::activaPanelAuxiliarDatos), 3));
	
	//Menu Avanzado
	//mPrincipal->add(Gtk::Action::create("MenuAvanzado", "_Extraccion"));
	//mPrincipal->add(Gtk::Action::create("MenuAvanzado", "_Extraction"));
	//Submenu Avanzado
	//mPrincipal->add(Gtk::Action::create("SubMenuAvanzado",Gtk::Stock::DND,
					//					"Recortar ovocito"),
					//Gtk::AccelKey("<control>X"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::recortaOvocito));
	/*mPrincipal->add(Gtk::Action::create("SubMenuAvanzado",Gtk::Stock::DND,
										"Segment oocyte"),
					Gtk::AccelKey("<control>X"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::recortaOvocito));*/
	
	//Menu Deteccion automatica
	//mPrincipal->add(Gtk::Action::create("MenuDeteccion", "_Deteccion"));
	mPrincipal->add(Gtk::Action::create("MenuDeteccion", "_Detection"));
	//Submenu Deteccion
	//mPrincipal->add(Gtk::Action::create("SubMenuDeteccionNoSupervisada1",Gtk::Stock::DND,
					//					"Bordes (No supervisado, v1)"),
					//Gtk::AccelKey("<control>P"),
					//sigc::bind(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::deteccionAutomactica), 1));
	mPrincipal->add(Gtk::Action::create("SubMenuDeteccionSupervisada1",Gtk::Stock::DND,
										"Launch border detection"),
					Gtk::AccelKey("<control><shift>F"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::deteccionAutomactica));

	//Menu Clasificacion automatica
	mPrincipal->add(Gtk::Action::create("MenuClasificacion", "_Classification"));
	//mPrincipal->add(Gtk::Action::create("SubMenuClasificacion",Gtk::Stock::DND,
					//					"Clasificador"),
					//Gtk::AccelKey("<control>L"),
					//sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::clasificacionAutomactica));
	mPrincipal->add(Gtk::Action::create("SubMenuClasificacion",Gtk::Stock::DND,
										"Launch classifier"),
					Gtk::AccelKey("<control><shift>L"),
					sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::clasificacionAutomactica));
	
	//Menu Ayuda
	//mPrincipal->add(Gtk::Action::create("MenuAyuda", "_Ayuda"));
	mPrincipal->add(Gtk::Action::create("MenuAyuda", "_Help"));
	//Submenu Ayuda
	//mPrincipal->add(Gtk::Action::create("SubMenuAcercaDe",Gtk::Stock::ABOUT, "Acerca de"),
	//					  sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAcercaDe));
	mPrincipal->add(Gtk::Action::create("SubMenuAcercaDe",Gtk::Stock::ABOUT, "About"),
						  sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAcercaDe));

		//Barra de herramientas
	//mPrincipal->add(Gtk::Action::create("BarraHAbrir",Gtk::Stock::OPEN, "Abrir"),
						  //sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrir));
	mPrincipal->add(Gtk::Action::create("BarraHAbrir",Gtk::Stock::OPEN, "Open"),
						  sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::menuAbrir));
}

/**
 Crea la estructura del menu principal y barra de herramientas
 */
void MenuBarraPrincipal::CreaUIManagerMenu()
{
	xmlMPrincipal = Gtk::UIManager::create();
	xmlMPrincipal->insert_action_group(mPrincipal);

	//add_accel_group(xmlMPrincipal->get_accel_group());

	//Distribucion del menu mediantel glib
	Glib::ustring ui_info = 
			"<ui>"
			"   <menubar name  = 'MenuBar'>"
			"	   <menu action = 'MenuArchivo'>"
			"	   <menu action = 'MenuLocal'>"
			"			<menuitem action = 'SubMenuAbrir' />"
			"			<menuitem action = 'SubMenuCargarCoord' />"
			"			<menuitem action = 'SubMenuAbrirIC' />"
			"	   </menu>"
			"	   <menu action = 'MenuServidor'>"
			"			<menuitem action = 'SubMenuAbrirRemoto' />"
			"			<menuitem action = 'SubMenuAbrirXmlRemoto' />"
			"			<menuitem action = 'SubMenuAbrirICRemoto' />"
			"	   </menu>"
			"	   <menu action = 'MenuGuardar'>"
			"			<menuitem action = 'SubMenuGuardarBD' />"
			"			<menuitem action = 'SubMenuGuardar' />"
			"			<menuitem action = 'SubMenuGuardarComo' />"
			"			<menuitem action = 'SubMenuGuardarImagen' />"
		//	"			<menuitem action = 'SubMenuGuardarMascara' />"
			"	   </menu>"
			"			<menuitem action = 'SubMenuCerrar' />"
			"			<menuitem action = 'SubMenuSalir' />"
			"	   </menu>"
			"	   <menu action = 'MenuEditar'>"
			"			<menuitem action = 'SubMenuSeleccionar' />"
			"			<menuitem action = 'SubMenuDeshacer' />"
			"			<menuitem action = 'SubMenuRehacer' />"
			"			<separator/>"
			"			<menuitem action = 'SubMenuPreferencias' />"
			"	   </menu>"
			"	   <menu action = 'MenuVer'>"		
			"			<menuitem action = 'SubMenuZoomIn' />"
			"			<menuitem action = 'SubMenuZoomOut' />"
			"			<menuitem action = 'SubMenuZoom100' />"
			"			<menuitem action = 'SubMenuZoomVentana' />"
			"	   </menu>"
			"	   <menu action = 'MenuHerramientas'>"
			"			<menuitem action = 'SubMenuEditor' />"
			"			<menuitem action = 'SubMenuRejilla' />"
			"	   </menu>"
			"	   <menu action = 'MenuCalcular'>"
			"			<menuitem action = 'SubMenuIndividuo' />"
			"	   <menu action = 'MenuDiametro'>"
			"			<menuitem action = 'SubCalcularDiam' />"
			"			<menuitem action = 'SubCalcularUnDiam' />"
			"	   </menu>"
			"			<menuitem action = 'SubCalcularEstadist' />"
			"	   </menu>"
/*			"	   <menu action = 'MenuAvanzado'>"
			"			<menuitem action = 'SubMenuAvanzado' />"
			"	   </menu>"*/
			"	   <menu action = 'MenuDeteccion'>"
			"			<menuitem action = 'SubMenuDeteccionSupervisada1' />"
			"	   </menu>"
			"	   <menu action = 'MenuClasificacion'>"
			"			<menuitem action = 'SubMenuClasificacion' />"
			"	   </menu>"
			"	   <menu action = 'MenuAyuda'>"		
			"			<menuitem action = 'SubMenuAcercaDe' />"
			"	   </menu>"
			"   </menubar>"
			"   <toolbar name = 'ToolBar'>"
			"			<toolitem action = 'BarraHAbrir' />"
			"			<toolitem action = 'SubMenuGuardar' />"
			"			<separator/>"
			"			<toolitem action = 'SubMenuDeshacer' />"
			"			<toolitem action = 'SubMenuRehacer' />"
			"			<separator/>"
			"			<toolitem action = 'SubMenuZoomIn' />"
			"			<toolitem action = 'SubMenuZoom100' />"
			"			<toolitem action = 'SubMenuZoomOut' />"
			"			<toolitem action = 'SubMenuZoomVentana' />"
			"			<separator/>"
			"			<toolitem action = 'SubMenuEditor' />"
			"			<separator/>"
			"			<toolitem action = 'SubMenuRejilla' />"
			"   </toolbar>"
			"</ui>";
	
	//Gestion de creacion de menu
	//En caso de que se produzca un error creando el menu se lanzara una excepcion
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
	  xmlMPrincipal->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex)
	{
	  cerr << "building menus failed: " << ex.what();
	}
	#else
	auto_ptr<Glib::Error> ex;
	xmlMPrincipal->add_ui_from_string(ui_info, ex);
	if(ex.get())
	{
	  cerr << "building menus failed: " << ex->what();
	}
	#endif //GLIBMM_EXCEPTIONS_ENABLED	
}
