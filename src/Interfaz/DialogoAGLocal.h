/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoAGLocal.h
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

#ifndef _DIALOGOAGLOCAL_H_
	#define _DIALOGOAGLOCAL_H_

	#include <string>
	#include <vector>
	#include <gtkmm.h>

	#include "Utiles.h"
	#include "Estructuras/ImageCells.h"

	using namespace std;

	class DialogoAGLocal
	{
		public:
			DialogoAGLocal(const string &img, const string &xml);
			~DialogoAGLocal();
			bool dialogoAbrirImagen(ImageCells *img);
			bool dialogoAbrirXml(ImageCells *img);
			bool dialogoGuardarImagen(const string &nombre, Glib::RefPtr<Gdk::Pixbuf> imagenCel);
			string dialogoGuardarComo(const string &nom);
		private:
			//Metodos
			void on_update_preview(Gtk::Image *preview);
			//Atributos
			string rutaImagenes, rutaXml;
			Gtk::FileChooserDialog *dialog;
	};
#endif //_DIALOGOAGLOCAL_H_
