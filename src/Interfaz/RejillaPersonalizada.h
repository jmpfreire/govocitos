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

#ifndef _REJILLAPERSONALIZADA_H_
	#define _REJILLAPERSONALIZADA_H_

	#include <iostream>
	#include <gtkmm.h>
	#include "Utiles.h"
	#include "Config/OpcionesRej.h"
	#include <vector>

	using namespace std;

	class RejillaPersonalizada : public Gtk::Dialog
	{
		public:
			RejillaPersonalizada(vector<OpcionesRej> &opc);
			~RejillaPersonalizada();
			bool muestraMenuSeleccion(int &indice);
		private:
			//Metodos
			void selecRejilla();
			void reordenarPorColumnas();
			//Atributos
			Gtk::TreeView *treeviewRejC;
			vector<OpcionesRej> *opcRej;
			int indiceRej;
			Gtk::ScrolledWindow scrollTreeView;

			//modelo treeview
			class ModelColumnRej : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumnRej(){add(nomCol);add(separPun);add(numCol);add(numRow);add(numPoints);}
				Gtk::TreeModelColumn<int> nomCol;
				Gtk::TreeModelColumn<int> separPun;
				Gtk::TreeModelColumn<int> numCol;
				Gtk::TreeModelColumn<int> numRow;
				Gtk::TreeModelColumn<int> numPoints;
			};
			Glib::RefPtr<Gtk::ListStore> refTreeModelRej;
			ModelColumnRej columRej;
	};
#endif // _REJILLAPERSONALIZADA_H_
