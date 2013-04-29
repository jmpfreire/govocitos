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

#ifndef _DIALOGOINDIVIDUO_H_
	#define _DIALOGOINDIVIDUO_H_

	#include <iostream>
	#include "Utiles.h"
	#include "Estructuras/ListadoIndividuo.h"

	using namespace std;

	class DialogoIndividuo : public Gtk::Dialog
	{   
		public:
			DialogoIndividuo(const string &titulo, vector<ListadoIndividuo> lv);
			~DialogoIndividuo();
			bool abreDialogoIndividuo(int &indice);
		private:
			//Metodos
			void selecImagen();
			void reordenarPorColumnas();
			//Atributos
			vector<ListadoIndividuo> listIndiv;
			Gtk::TreeView *treeviewIndividuo;
			Gtk::ScrolledWindow scrollTreeView;
			int numIndivSelec;
			
			//modelo treeview para todos los datos
			class ModelColumnsI : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumnsI(){add(colNombre); add(numImagTotal); add(numImagGestionada);}
				Gtk::TreeModelColumn<string> colNombre;
				Gtk::TreeModelColumn<int> numImagTotal;
				Gtk::TreeModelColumn<int> numImagGestionada;
			};
			Glib::RefPtr<Gtk::ListStore> refTreeModelIndividuo;
			ModelColumnsI columIndividuos;
	};
#endif //_DIALOGOINDIVIDUO_H_
