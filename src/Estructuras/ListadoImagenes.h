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

#ifndef _LISTADOIMAGENES_H_
	#define _LISTADOIMAGENES_H_

	#include <iostream>
	#include <vector>
	#include "DataImage.h"

	using namespace std;

	class ListadoImagenes
	{
		public:
			ListadoImagenes();
			~ListadoImagenes();
			ListadoImagenes(const ListadoImagenes &li);
			void setImagenVector(DataImage iw);
			void borraImagenVector(int indice);
			DataImage *getImagenVector(int indice);
			int getTamanhoVectorImag();
			const ListadoImagenes &operator=(const ListadoImagenes &li);
		private:
			vector<DataImage> listaImagenesWeb;
	};

#endif // _LISTADOIMAGENES_H_
