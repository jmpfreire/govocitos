/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ImageCells.h
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

#ifndef _IMAGECELLS_H_
	#define _IMAGECELLS_H_

	#include "DataImage.h"
	#include <gdkmm.h>
	#include "Fichero.h"
	#include "Utiles.h"

	using namespace std;

	class ImageCells : public DataImage
	{
		public:
			ImageCells();
			~ImageCells();
			ImageCells(const ImageCells &ic);
			void addXmlTest(const string &rutaXml);
			void addNombreXmlTest(const string &nombreXml);
			void vaciaXmlTest();
			void vaciaNombreXmlTest();
			vector<string> getXmlTest();
			vector<string> getNombreXmlTest();
			bool cargaImagenEnSistema(bool condicion = true);
			void cargaImagenReducida();
			string calculoMD5Imagen(FILE* fich);
			Glib::RefPtr<Gdk::Pixbuf> getImagenCelulas();
			bool existeImagen();
			void setExisteImagen(bool ei);
			const ImageCells &operator=(const ImageCells &ic);
		private:
			Glib::RefPtr<Gdk::Pixbuf> imagenCelulas;
			vector<string> pathIntermedios;
			vector<string> nombrePathIntermedios;
	};

#endif //_IMAGECELLS_H_
