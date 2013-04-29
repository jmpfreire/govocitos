/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoIndividuo.h
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

#include "DialogoIndividuo.h"

/**
 Constructor.
*/
DialogoIndividuo::DialogoIndividuo(const string &titulo, vector<ListadoIndividuo> lv)
{
	listIndiv = lv;
	numIndivSelec = -1;

	set_title(titulo);
	set_icon_from_file(Utiles::getIconoFile("carpeta.png"));
}

/**
 Destructor.
 */
DialogoIndividuo::~DialogoIndividuo()
{

}

/**
 Carga las imagenes en el treview y muestra el dialogo, devuelve la imagen seleccionada.
 @param &indice, int referencia que contiene la posicion del individuo seleccionado.
 */
bool DialogoIndividuo::abreDialogoIndividuo(int &indice)
{
	int numIndividuos;

	scrollTreeView.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	this->get_vbox()->add(scrollTreeView);
	
	numIndividuos = listIndiv.size();

	//Creamos el treview
	treeviewIndividuo = new Gtk::TreeView();
	
	refTreeModelIndividuo = Gtk::ListStore::create(columIndividuos);
	treeviewIndividuo->set_model(refTreeModelIndividuo);

	//Rellenamos el treeview con los datos
	for(int i = 0; i < numIndividuos; i++)
	{	
		string nombre;

		nombre = listIndiv[i].getCampanhaInd() + "-" + listIndiv[i].getEspecieInd() + "-" +
		listIndiv[i].getMuestreoInd() + "-" + listIndiv[i].getIndividuoInd();
		Gtk::TreeModel::Row row = *(refTreeModelIndividuo->append());
		row[columIndividuos.colNombre] = nombre;
		row[columIndividuos.numImagTotal] = listIndiv[i].getNumImagenes();
		row[columIndividuos.numImagGestionada] = listIndiv[i].getNumXmlAnalizados();
	}
	
	/*
	treeviewIndividuo->append_column("Nombre ",columIndividuos.colNombre);
	treeviewIndividuo->append_column("Imagenes",columIndividuos.numImagTotal);
	treeviewIndividuo->append_column("Gestionadas",columIndividuos.numImagGestionada);
	*/
	treeviewIndividuo->append_column("Name ",columIndividuos.colNombre);
	treeviewIndividuo->append_column("Images",columIndividuos.numImagTotal);
	treeviewIndividuo->append_column("Managed Images",columIndividuos.numImagGestionada);

	scrollTreeView.add(*treeviewIndividuo);
	scrollTreeView.set_size_request(450, 350);

	show_all();
	
	//Añadimos la señal de seleccion
	treeviewIndividuo->signal_cursor_changed().connect(sigc::mem_fun(*this, &DialogoIndividuo::selecImagen));	

	treeviewIndividuo->get_selection()->unselect_all();

	//Dividimos el treeView en filas y columnas
	treeviewIndividuo->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
	
	//Hacemos clickable la cabecera
	treeviewIndividuo->set_headers_clickable();
				
	//Creamos la señal
	reordenarPorColumnas();
				
	add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		
	int opcion = this->run();
	
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{
			if(numIndivSelec != -1)
			{
				indice = numIndivSelec;

				return true;
			}
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			indice = -1;
			return false;
		}
		default:
		{
			return false;
		}
	}
}

/**
 Selecciona una imagen del panel de apertura.
 */
void DialogoIndividuo::selecImagen()
{
	int i, numIndiv;
	string nombreIndiv, nombreIndList;
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	
	i = 0;
	numIndiv = listIndiv.size();
	filaSeleccionada = treeviewIndividuo->get_selection();
	iter = filaSeleccionada->get_selected();

	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		
		nombreIndiv = row[columIndividuos.colNombre];
		
		while(i < numIndiv && (listIndiv[i].getCampanhaInd() + "-" + listIndiv[i].getEspecieInd() + "-" + 
							   listIndiv[i].getMuestreoInd() + "-" + listIndiv[i].getIndividuoInd()) != nombreIndiv)
		{
			i++;
		}	
		numIndivSelec = i;	
	}
	else
	{
		numIndivSelec = -1;
	}
}

/**
 Hace que las columnas del treeview sean reordenables.
 */
void DialogoIndividuo::reordenarPorColumnas()
{
	Gtk::TreeView::Column* pColumn1 = treeviewIndividuo->get_column(0);
	
	if(pColumn1)
	{
		pColumn1->set_sort_column(columIndividuos.colNombre);
	}
}