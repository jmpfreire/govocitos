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


#include "MenuSeleccion.h"

/**
 Constructor.
 */
MenuSeleccion::MenuSeleccion()
{
	
}

/**
 Destructor.
 */
MenuSeleccion::~MenuSeleccion()
{
	
}

/**
 Ventana de seleccion de estados de celulas
 @param estados, referencias del vector de objetos EstadoCeula que contiene los
 estados de maduración.
 @param nomPanel, string que contiene el nombre del dialogo a generar.
 @return vector<int>, contiene los estados selecconados.
 */
vector<int> MenuSeleccion::seleccionClasesEstados(vector<EstadoCelula> &estados, const string &nomPanel)
{
	vector<int> clasEst;
	vector<Gtk::CheckButton*> punteroBotones;
	Gtk::VBox *vboxClasEst, vboxCE;
	Gtk::Button *aceptarCE;
	Gtk::Label *l1, *labelNom, *labelClasEst;
	Gtk::CheckButton *c1;
	Gtk::HBox *hboxCE;
	int numeroBotones;
	int numClasesEstados = estados.size();
								   
	//Inicializamos las variables de la nueva ventana
	Utiles::getWidgetGlade(Utiles::getGladeFile("seleccionaClaseEstado.glade"),"dialogoSeleccion",
				   "dialogoSeleccion", &dialogoSeleccion,
				   "vboxClasEst", &vboxClasEst,
				   "aceptarCE", &aceptarCE,
				   "labelNom", &labelNom,
				   "labelClasEst", &labelClasEst,
				   NULL);
	
	dialogoSeleccion->set_icon_from_file(Utiles::getIconoFile("calculoDatos.png"));
	
	//dialogoSeleccion->set_title("Seleccion de " + nomPanel);
	dialogoSeleccion->set_title("Selection of " + nomPanel);
	labelClasEst->set_label("<b>" + nomPanel + "</b>");
	//labelNom->set_label("<b>Nombre " + nomPanel + "</b>");
	labelNom->set_label("<b>Name " + nomPanel + "</b>");
	
	for(int i = 0; i < numClasesEstados; i++)
	{
		//Creamos las etiquetas dinamicamente
		c1 = new Gtk::CheckButton(estados[i].getEtiquetaClasificacion());
		l1 = new Gtk::Label(estados[i].getNombreClasificacion());
		hboxCE = new Gtk::HBox(true);

		hboxCE->add(*c1);
		hboxCE->add(*l1);
		
		punteroBotones.push_back(c1);
		//Añadimos el hbox al vbox
		vboxCE.add(*hboxCE);
	}
	//Añadimos una linea en blanco
	l1 = new Gtk::Label("");
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(*l1);
	vboxCE.add(*hboxCE);
	
	//Añadimos la seleccion del boton todos
	//c1 = new Gtk::CheckButton("Seleccionar Todos");
	c1 = new Gtk::CheckButton("Select All");
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(*c1);
	punteroBotones.push_back(c1);
	//Añadimos el hbox al vbox
	vboxCE.add(*hboxCE);
	
	vboxClasEst->add(vboxCE);
	vboxClasEst->show_all();

	numeroBotones = punteroBotones.size()-1;

	for(int i = 0; i < numeroBotones; i++)
	{
		//Añadimos las señales de cambio
		punteroBotones[i]->signal_released().
			connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecUnBoton),punteroBotones));
	}
	//Añadimos las señales de cambio
	punteroBotones[numeroBotones]->signal_released().
		connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecTodos),punteroBotones));
	
	//Lanzamos el dialogo
	dialogoSeleccion->run();
	
	for(int i = 0; i < numeroBotones; i++)
	{
		if(punteroBotones[i]->get_active())
		{
			for(int j = 0; j < numClasesEstados; j++)
			{
				if(estados[j].getEtiquetaClasificacion() == punteroBotones[i]->get_label())
				{
					clasEst.push_back(j);
				}
			}
		}
	}

	delete dialogoSeleccion;
	delete l1;
	delete c1;
	delete hboxCE;	

	return clasEst;
}

/**
 Ventana de seleccion de estados de celulas
 @param estados, referencias del vector de objetos EstadoCeula que contiene los
 estados de maduración.
 @param nomPanel, string que contiene el nombre del dialogo a generar.
 @return vector<int>, contiene los estados/clases selecconados.
 */
vector<vector<string> > MenuSeleccion::seleccionClaEstDiametro(vector<ClaseCelula> &clas, vector<EstadoCelula> &est, const string &nomPanel)
{
	vector<Gtk::CheckButton*> punteroBotonesCl;
	vector<Gtk::CheckButton*> punteroBotonesEst;
	vector<vector<string> > clasEst;
	vector<string> clasesSelec, estadosSelec;
	Gtk::VBox *vboxClasEst, vboxCE;
	Gtk::Button *aceptarCE;
	Gtk::Label *l1, *labelNom, *labelClasEst;
	Gtk::Label labNomEst, labEtiqEst;
	Gtk::CheckButton *c1;
	Gtk::HBox *hboxCE;
	Gtk::HSeparator separador1;
	int numeroBotonesCl, numeroBotonesEst;
	int numClases = clas.size();
	int numEstados = est.size();
								   
	//Inicializamos las variables de la nueva ventana
	Utiles::getWidgetGlade(Utiles::getGladeFile("seleccionaClaseEstado.glade"),"dialogoSeleccion",
				   "dialogoSeleccion", &dialogoSeleccion,
				   "vboxClasEst", &vboxClasEst,
				   "aceptarCE", &aceptarCE,
				   "labelNom", &labelNom,
				   "labelClasEst", &labelClasEst,
				   NULL);
	
	dialogoSeleccion->set_icon_from_file(Utiles::getIconoFile("calculoDatos.png"));
	/*
	dialogoSeleccion->set_title("Seleccion de " + nomPanel);
	labelClasEst->set_label("<b>Clases</b>");
	labelNom->set_label("<b>Nombre Clases</b>");
	labEtiqEst.set_label("<b>Estados</b>");
	labNomEst.set_label("<b>Nombre Estados</b>");
	*/
	dialogoSeleccion->set_title("Selection of " + nomPanel);
	labelClasEst->set_label("<b>Classes</b>");
	labelNom->set_label("<b>Classes names</b>");
	labEtiqEst.set_label("<b>States</b>");
	labNomEst.set_label("<b>States names</b>");
	labEtiqEst.set_use_markup();
	labNomEst.set_use_markup();
	
	for(int i = 0; i < numClases; i++)
	{
		if(clas[i].getEnUso())
		{
			//Creamos las etiquetas dinamicamente
			c1 = new Gtk::CheckButton(clas[i].getEtiquetaClasificacion());
			l1 = new Gtk::Label(clas[i].getDescripcionClasificacion());
			hboxCE = new Gtk::HBox(true);

			hboxCE->add(*c1);
			hboxCE->add(*l1);
		
			punteroBotonesCl.push_back(c1);
			//Añadimos el hbox al vbox
			vboxCE.add(*hboxCE);
		}
	}
	
	//Añadimos la seleccion del boton todos
	//c1 = new Gtk::CheckButton("Seleccionar todas las clases");
	c1 = new Gtk::CheckButton("Select all the classes");
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(*c1);
	punteroBotonesCl.push_back(c1);
	//Añadimos el hbox al vbox
	vboxCE.add(*hboxCE);

	//Añadimos una linea en blanco
	l1 = new Gtk::Label("");
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(*l1);
	vboxCE.add(*hboxCE);

	//Añadimos el titulo de estados
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(labEtiqEst);
	hboxCE->add(labNomEst);
	vboxCE.add(*hboxCE);
	vboxCE.add(separador1);

	for(int i = 0; i < numEstados; i++)
	{
		if(est[i].getEnUso())
		{
			//Creamos las etiquetas dinamicamente
			c1 = new Gtk::CheckButton(est[i].getEtiquetaClasificacion());
			l1 = new Gtk::Label(est[i].getNombreClasificacion());
			hboxCE = new Gtk::HBox(true);

			hboxCE->add(*c1);
			hboxCE->add(*l1);
		
			punteroBotonesEst.push_back(c1);
			//Añadimos el hbox al vbox
			vboxCE.add(*hboxCE);
		}
	}
	
	//Añadimos la seleccion del boton todos
	//c1 = new Gtk::CheckButton("Seleccionar todas los estados");
	c1 = new Gtk::CheckButton("Select all the states");
	hboxCE = new Gtk::HBox(true);
	hboxCE->add(*c1);
	punteroBotonesEst.push_back(c1);
	//Añadimos el hbox al vbox
	vboxCE.add(*hboxCE);

	
	vboxClasEst->add(vboxCE);
	vboxClasEst->show_all();

	numeroBotonesCl = punteroBotonesCl.size()-1;

	for(int i = 0; i < numeroBotonesCl; i++)
	{
		//Añadimos las señales de cambio
		punteroBotonesCl[i]->signal_released().
			connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecUnBoton),punteroBotonesCl));
	}
	//Añadimos las señales de cambio
	punteroBotonesCl[numeroBotonesCl]->signal_released().
		connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecTodos),punteroBotonesCl));

	numeroBotonesEst = punteroBotonesEst.size()-1;

	for(int i = 0; i < numeroBotonesEst; i++)
	{
		//Añadimos las señales de cambio
		punteroBotonesEst[i]->signal_released().
			connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecUnBoton),punteroBotonesEst));
	}
	//Añadimos las señales de cambio
	punteroBotonesEst[numeroBotonesEst]->signal_released().
		connect(sigc::bind(sigc::mem_fun(*this, &MenuSeleccion::DesSelecTodos),punteroBotonesEst));
	
	
	//Lanzamos el dialogo
	dialogoSeleccion->run();
	
	for(int i = 0; i < numeroBotonesCl; i++)
	{
		if(punteroBotonesCl[i]->get_active())
		{
			for(int j = 0; j < numClases; j++)
			{
				if(clas[j].getEtiquetaClasificacion() == punteroBotonesCl[i]->get_label())
				{
					clasesSelec.push_back(clas[j].getEtiquetaClasificacion());
				}
			}
		}
	}

	for(int i = 0; i < numeroBotonesEst; i++)
	{
		if(punteroBotonesEst[i]->get_active())
		{
			for(int j = 0; j < numEstados; j++)
			{
				if(est[j].getEtiquetaClasificacion() == punteroBotonesEst[i]->get_label())
				{
					estadosSelec.push_back(est[j].getEtiquetaClasificacion());
				}
			}
		}
	}

	clasEst.push_back(clasesSelec);
	clasEst.push_back(estadosSelec);

	delete dialogoSeleccion;
	delete l1;
	delete c1;
	delete hboxCE;	

	return clasEst;
}

/**
 Selecciona o deselecciona todas las opciones de los menus de seleccion de clases o estados
 @param puntBoton, vector de punteros del objeto ChecButton.
 */
void MenuSeleccion::DesSelecTodos(vector<Gtk::CheckButton*> puntBoton)
{
	int numeroBotones = (puntBoton.size() - 1);
	bool activado;

	if(puntBoton[numeroBotones]->get_active())
	{
		activado = true;
	}
	else
	{
		activado = false;
	}
	
	for(int i = 0; i < numeroBotones; i++)
	{
		puntBoton[i]->set_active(activado);
	}
}

/**
 Selecciona o deselecciona una opcion y deselecciona o selecciona la opcion todos
 @param punBoton, vector de punteros del objeto CheckButton.
 */
void MenuSeleccion::DesSelecUnBoton(vector<Gtk::CheckButton*> puntBoton)
{
	int numeroBotones = (puntBoton.size() - 1);
	int i = 0;

	if(puntBoton[numeroBotones]->get_active())
	{
		while(i < numeroBotones && puntBoton[i]->get_active())
		{
			i++;
		}
		if(i != numeroBotones)
		{
			puntBoton[numeroBotones]->set_active(false);
		}
	}
	else
	{
		while(i < numeroBotones && puntBoton[i]->get_active())
		{
			i++;
		}
		if(i == numeroBotones)
		{
			puntBoton[numeroBotones]->set_active(true);
		}
	}
}
