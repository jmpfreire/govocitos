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

#include "RejillaPersonalizada.h"

/**
 Constructor.
 */
RejillaPersonalizada::RejillaPersonalizada(vector<OpcionesRej> &opc)
{
	opcRej = &opc;
	indiceRej = -1;
	
	//set_title("Selección rejilla personalizada");
	set_title("Custom grid selection");
	set_icon_from_file(Utiles::getIconoFile("configurar.png"));

}

/**
 Destructor.
 */
RejillaPersonalizada::~RejillaPersonalizada()
{

}

/**
 Muestra el dialogo principal de la rejilla.
 @param indice, int contiene el indice de la rejilla.
 @return bool, devuelve verdadero si se localiza la rejilla, false en caso contario.
 */
bool RejillaPersonalizada::muestraMenuSeleccion(int &indice)
{
	int numOpcRej;

	scrollTreeView.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	this->get_vbox()->add(scrollTreeView);
	
	numOpcRej = opcRej->size();

	//Creamos el nuevo treeView
	treeviewRejC = new Gtk::TreeView();
	
	refTreeModelRej = Gtk::ListStore::create(columRej);
	treeviewRejC->set_model(refTreeModelRej);
	
	if(numOpcRej)
	{
		for(int i = 0; i < numOpcRej; i++)
		{
			Gtk::TreeModel::Row row = *(refTreeModelRej->append());
			row[columRej.nomCol] = (*opcRej)[i].getID();
			row[columRej.numCol] = (*opcRej)[i].getNumColumnas();
			row[columRej.numRow] = (*opcRej)[i].getNumFilas();
			row[columRej.separPun] = (*opcRej)[i].getSeparaPuntos();
			row[columRej.numPoints] = (*opcRej)[i].getNumPuntos();	   
		}
	}
	treeviewRejC->append_column("ID",columRej.nomCol);
	//treeviewRejC->append_column("Nº Columnas",columRej.numCol);
	//treeviewRejC->append_column("Nº Filas",columRej.numRow);
	//treeviewRejC->append_column("Separacion(micras)",columRej.separPun);
	//treeviewRejC->append_column("Total Puntos",columRej.numPoints);
	treeviewRejC->append_column("No. columns",columRej.numCol);
	treeviewRejC->append_column("No. rows",columRej.numRow);
	treeviewRejC->append_column("Distance (um)",columRej.separPun);
	treeviewRejC->append_column("Total of points",columRej.numPoints);

	scrollTreeView.add(*treeviewRejC);
	scrollTreeView.set_size_request(500, 150);

	show_all();

	treeviewRejC->signal_cursor_changed().connect(sigc::mem_fun
													(*this, &RejillaPersonalizada::selecRejilla));
	
	treeviewRejC->get_selection()->unselect_all();

	//Hacemos clickable la cabecera
	treeviewRejC->set_headers_clickable();

	//Dividimos el treeView en filas y columnas
	treeviewRejC->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

	//Reordenar columnas
	reordenarPorColumnas();

	add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		
	int opcion = this->run();
	
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{
			if(indiceRej != -1)
			{
				indice = indiceRej;
				
				return true;
			}
			else
			{
				indice = -1;
				
				return false;
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
 Selecciona la rejilla.
 */
void RejillaPersonalizada::selecRejilla()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	int idR;

	indiceRej = -1;
	
	filaSeleccionada = treeviewRejC->get_selection();
	
	iter = filaSeleccionada->get_selected();
	
	if(iter)
	{
		int numOpcRej = opcRej->size();
		
		Gtk::TreeModel::Row row = *iter;

		idR = row[columRej.nomCol];
		
		for(int i = 0; i < numOpcRej; i++)
		{	
			if(idR == (*opcRej)[i].getID())
			{	
				indiceRej = i;
				break;
			}
		}
	}
}

/**
 Habilita la reordenacion de las columnas del dialogo de rejilla personalizada.
 */
void RejillaPersonalizada::reordenarPorColumnas()
{
	Gtk::TreeView::Column* pColumn1 = treeviewRejC->get_column(0);
	Gtk::TreeView::Column* pColumn2 = treeviewRejC->get_column(1);
	Gtk::TreeView::Column* pColumn3 = treeviewRejC->get_column(2);
	Gtk::TreeView::Column* pColumn4 = treeviewRejC->get_column(3);
	Gtk::TreeView::Column* pColumn5 = treeviewRejC->get_column(4);
	
	if(pColumn1)
	{
		pColumn1->set_sort_column(columRej.nomCol);
	}
	if(pColumn2)
	{
		pColumn2->set_sort_column(columRej.numCol);
	}
	if(pColumn3)
	{
		pColumn3->set_sort_column(columRej.numRow);
	}
	if(pColumn4)
	{
		pColumn4->set_sort_column(columRej.separPun);
	}
	if(pColumn5)
	{
		pColumn5->set_sort_column(columRej.numPoints);
	}
}
