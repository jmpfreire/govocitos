/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoRemoto.h
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

#ifndef _DIALOGOREMOTO_H_
	#define _DIALOGOREMOTO_H_

	#include <iostream>
	#include "Utiles.h"
	#include "Estructuras/ListadoImagenes.h"

	using namespace std;

	class DialogoRemoto : public Gtk::Dialog
	{
		public:
			DialogoRemoto(const string &titulo, ListadoImagenes &li);
			~DialogoRemoto();
			bool abreDialogoRemoto(int &indice, bool opcionS = true);
		private:
			//Metodos
			void selecImagen(bool opcion);
			//Atributos
			Gtk::TreeView *treeviewImagenes;
			Gtk::ScrolledWindow scrollTreeView;
			ListadoImagenes *listimag;
			int numImagSelec;
			
			//modelo treeview para todos los datos
			class ModelColumnsI : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumnsI(){add(colNombre);}
				Gtk::TreeModelColumn<string> colNombre;
			};
			Glib::RefPtr<Gtk::ListStore> refTreeModelImagenes;
			ModelColumnsI columImagenes;
	};

#endif // _DIALOGOREMOTO_H_
