/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _LISTADOCACHE_H_
	#define _LISTADOCACHE_H_

	#include <list>
	#include <string.h>
	#include <iostream>
	#include <gdkmm.h>

	#include "Utiles.h"
	#include "Fichero.h"

	using namespace std;

	class ListadoCache
	{
		public:
			ListadoCache(int nim, list<string> &vci);
			~ListadoCache();
			ListadoCache(const ListadoCache &lc);
			int getNumImagenesMax();
			int getNumImagenesActual();
			string getImagenLista(const string &nom);
			void setNumImagenesMax(unsigned int nmi);
			void addImagenCache(const string &img);
			list<string> *getListaCache();
			void reordenarListaImagenes(const string &img);
			const ListadoCache &operator=(const ListadoCache &lc);
		private:
			//Atributos
			unsigned int numImgMax;
			list<string> *vCacheImg;		
	};
#endif //_LISTADOCACHE_H_
