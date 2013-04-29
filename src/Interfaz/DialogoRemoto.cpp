/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoRemoto.cpp
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

#include "DialogoRemoto.h"

/**
 Constructor.
 */
DialogoRemoto::DialogoRemoto(const string &titulo, ListadoImagenes &li)
{
	listimag = &li;
	numImagSelec = -1;

	set_title(titulo);
	set_icon_from_file(Utiles::getIconoFile("carpeta.png"));
}

/**
 Destructor.
 */
DialogoRemoto::~DialogoRemoto()
{
	
}

/**
 Carga las imagenes en el treview y muestra el dialogo, devuelve la imagen seleccionada.
 @param &indice, int referencia que contiene la posicion de la imagen seleccionada.
 @param opcionS, bool si es verdaredo estamos abriendo imagenes si es falso estamos
 abriendo ficheros de celulas.
 @return bool, verdadero si el usuario abre imagen o fichero, falso en caso contrario.
 */
bool DialogoRemoto::abreDialogoRemoto(int &indice, bool opcionS)
{
	int numImagenes;

	scrollTreeView.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	this->get_vbox()->add(scrollTreeView);
	
	numImagenes = listimag->getTamanhoVectorImag();

	//Creamos el treview
	treeviewImagenes = new Gtk::TreeView();
	
	refTreeModelImagenes = Gtk::ListStore::create(columImagenes);
	treeviewImagenes->set_model(refTreeModelImagenes);

	if(opcionS)
	{
		//Rellenamos el treeview con los datos
		for(int i = 0; i < numImagenes; i++)
		{	
			Gtk::TreeModel::Row row = *(refTreeModelImagenes->append());
			row[columImagenes.colNombre] = listimag->getImagenVector(i)->getNombreImg();
		}
	}
	else
	{
		//Rellenamos el treeview con los datos
		for(int i = 0; i < numImagenes; i++)
		{	
			if(listimag->getImagenVector(i)->getNombreXml() != "")
			{
				Gtk::TreeModel::Row row = *(refTreeModelImagenes->append());
				row[columImagenes.colNombre] = listimag->getImagenVector(i)->getNombreXml();
			}
		}
	}
	
	//treeviewImagenes->append_column("Nombre ",columImagenes.colNombre);
	treeviewImagenes->append_column("Name ",columImagenes.colNombre);

	scrollTreeView.add(*treeviewImagenes);
	scrollTreeView.set_size_request(450, 350);

	show_all();
	
	//Añadimos la señal de seleccion
	treeviewImagenes->signal_cursor_changed().connect(sigc::bind(sigc::mem_fun
													  (*this, &DialogoRemoto::selecImagen), opcionS));	

	treeviewImagenes->get_selection()->unselect_all();

	//Dividimos el treeView en filas y columnas
	treeviewImagenes->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
	
	add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		
	int opcion = this->run();
	
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{
			if(numImagSelec != -1)
			{
				indice = numImagSelec;

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
 @param opcion, bool verdadero si es imagen, falso si es fichero celulas.
 */
void DialogoRemoto::selecImagen(bool opcion)
{
	int i, numImagenes;
	string nombreImag;
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	
	i = 0;
	numImagenes = listimag->getTamanhoVectorImag();
	filaSeleccionada = treeviewImagenes->get_selection();
	iter = filaSeleccionada->get_selected();

	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		
		nombreImag = row[columImagenes.colNombre];

		if(opcion)
		{
			while(i < numImagenes && listimag->getImagenVector(i)->getNombreImg() != nombreImag)
			{
				i++;
			}	
		}
		else
		{
			while(i < numImagenes && listimag->getImagenVector(i)->getNombreXml() != nombreImag)
			{
				i++;
			}
		}
		numImagSelec = i;	
	}
	else
	{
		numImagSelec = -1;
	}
}
