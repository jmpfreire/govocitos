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

#include "MenuPopup.h"
#include "PanelDibujado.h"

/**
 Constructor
 */
MenuPopup::MenuPopup(vector<ClaseCelula> &cl,vector<EstadoCelula> &est, PanelDibujado &pd)
{
	clases = &cl;
	estados = &est;
	panelDibuj = &pd;

	//Inicializamos el menu
	inicilizaMenuPopup();
	
	//Generamos la apariencia del menu
	CreaUIManagerPopup();   

	//Hacemos no sensibles de principio
	setSensitiveInicialPopup();
}

/**
 Destructor
 */
MenuPopup::~MenuPopup()
{

}

/**
 Devuelve el objeto del panel
 */
Glib::RefPtr<Gtk::UIManager> MenuPopup::getUIManager()
{
	return m_refUIManager;
}

/**
 Establece la sensibilidad del menu popup pasado en la variable string menu. Si condicion
 es verdadero el menu es sensible en caso contrario no es sensible
 @param menu string del menu que queremos hacer sensible o no
 @param condicion si es verdadero el menu es sensible en caso contrario no es sensible
 por defecto es falso si no se le pasa condicion
 */
void MenuPopup::setSensitivePopup(const string &menu, bool condicion)
{
	m_refActionGroup->get_action(menu)->set_sensitive(condicion);
}

/**
 Establece las opciones del menu popup al modo de inicio
 */
void MenuPopup::setSensitiveInicialPopup()
{
	m_refActionGroup->get_action("eliminar")->set_sensitive(false);
	m_refActionGroup->get_action("showDiam")->set_sensitive(false);
	m_refActionGroup->get_action("popClases")->set_sensitive(false);
	m_refActionGroup->get_action("popEstados")->set_sensitive(false);
}

/**
 Inicializa el menu de popup
 */
void MenuPopup::inicilizaMenuPopup()
{
	int numClases, numEstados;
	string clase, estado;

	numClases = clases->size();
	numEstados = estados->size();
	
	//Crea las funciones del menu
	m_refActionGroup = Gtk::ActionGroup::create();

	m_refActionGroup->add(Gtk::Action::create("seleccionarTodo", "Select all"),
	                      sigc::mem_fun(*panelDibuj, &PanelDibujado::selecAllCell));
	//m_refActionGroup->add(Gtk::Action::create("eliminar", "Eliminar"),
	                      //sigc::mem_fun(*panelDibuj, &PanelDibujado::eliminaCelula));
	m_refActionGroup->add(Gtk::Action::create("eliminar", "Delete"),
	                      sigc::mem_fun(*panelDibuj, &PanelDibujado::eliminaCelula));


	//Clases
	//m_refActionGroup->add(Gtk::Action::create("popClases", "Clases"));
	m_refActionGroup->add(Gtk::Action::create("popClases", "Classes"));

	//m_refActionGroup->add(Gtk::Action::create("popSinClasifi", "sin clasificar"),
		                      //sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabClasePopup), "sin clasificar"));
	m_refActionGroup->add(Gtk::Action::create("popSinClasifi", "unclassified"),
		                      sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabClasePopup), "unclassified"));

	//Añadimos todas las clases
	for(int i = 0; i < numClases; i++)
	{
		if((*clases)[i].getEnUso())
		{
			clase = (*clases)[i].getEtiquetaClasificacion();
		
			m_refActionGroup->add(Gtk::Action::create("pop" + clase, clase),
				                  sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabClasePopup), clase));
		}
	}

	//Estados
	//m_refActionGroup->add(Gtk::Action::create("popEstados", "Estados"));
	m_refActionGroup->add(Gtk::Action::create("popEstados", "States"));

	//m_refActionGroup->add(Gtk::Action::create("popSinEstado", "sin estado"),
		                      //sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabEstadoPopup), "sin estado"));
	m_refActionGroup->add(Gtk::Action::create("popSinEstado", "without state"),
		                      sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabEstadoPopup), "without state"));

	
	//Añadimos todos los estados
	for(int i = 0; i < numEstados; i++)
	{
		if((*estados)[i].getEnUso())
		{
			estado = (*estados)[i].getEtiquetaClasificacion();
		
			m_refActionGroup->add(Gtk::Action::create("pop" + estado, estado),
		                      sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::estabEstadoPopup), estado));
		}
	}

	//Diametros
	//m_refActionGroup->add(Gtk::Action::create("diametros", "Diametro"));
	m_refActionGroup->add(Gtk::Action::create("diametros", "Diameter"));
	
	//m_refActionGroup->add(Gtk::Action::create("showDiam", "Una Célula"),
	                     // sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::obtieneDiametros), true));
	m_refActionGroup->add(Gtk::Action::create("showDiam", "One cell"),
	                      sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::obtieneDiametros), true));

	
	//m_refActionGroup->add(Gtk::Action::create("showAllDiam", "Todas las Células"),
	                      //sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::obtieneDiametros), false));

	m_refActionGroup->add(Gtk::Action::create("showAllDiam", "All the cells"),
	                      sigc::bind(sigc::mem_fun(*panelDibuj, &PanelDibujado::obtieneDiametros), false));
}

/**
 Crea el ui manager
 */
void MenuPopup::CreaUIManagerPopup()
{
	string uiDinamico, clase, estado;
	int numClases, numEstados;

	numClases = clases->size();
	numEstados = estados->size();
	
	uiDinamico = "<ui>"
		" <popup name='PopupMenu'>"
		"    <menuitem action='seleccionarTodo'/>"
		"    <menuitem action='eliminar'/>"
		"	 <menu action = 'popClases'>"
		"	   <menuitem action='popSinClasifi'/>";
	
	for(int i = 0; i < numClases; i++)
	{
		if((*clases)[i].getEnUso())
		{
			clase = "pop" + (*clases)[i].getEtiquetaClasificacion();
		
			uiDinamico = uiDinamico + "	   <menuitem action='" + clase + "'/>";
		}
	}

	uiDinamico = uiDinamico + "	 </menu>"
		"	 <menu action = 'popEstados'>"
		"	   <menuitem action='popSinEstado'/>";
	
	for(int i = 0; i < numEstados; i++)
	{
		if((*estados)[i].getEnUso())
		{
			estado = "pop" + (*estados)[i].getEtiquetaClasificacion();

			uiDinamico = uiDinamico + "    <menuitem action='" + estado + "'/>";
		}
	}

	uiDinamico = uiDinamico + "	 </menu>"
		"	 <menu action = 'diametros'>"
		"	   <menuitem action='showDiam'/>"
		"	   <menuitem action='showAllDiam'/>"
		"	 </menu>"
		" </popup>"
		"</ui>";
	
	m_refUIManager = Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);

	add_accel_group(m_refUIManager->get_accel_group());

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info = uiDinamico;
	
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
	  m_refUIManager->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex)
	{
	  //std::cerr << "Fallo creando los menus " << ex.what();
	  std::cerr << "Error while creating the menus " << ex.what();
	}
	#else
	std::auto_ptr<Glib::Error> ex;
	m_refUIManager->add_ui_from_string(ui_info, ex);
	if(ex.get())
	{
	  //std::cerr << "Fallo creando los menus " << ex->what();
	  std::cerr << "Error while creating the menus " << ex.what();
	}
	#endif //GLIBMM_EXCEPTIONS_ENABLED
}
