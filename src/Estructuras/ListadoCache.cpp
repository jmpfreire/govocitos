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

#include "ListadoCache.h"

/**
 Constructor
 */
ListadoCache::ListadoCache(int nim, list<string> &vci)
{
	numImgMax = nim;
	vCacheImg = &vci;
}

/**
 Destructor
 */
ListadoCache::~ListadoCache()
{

}

/**
 Constructor de copias
 @param lc referencia del objeto de la clase ListadoCache original
 */
ListadoCache::ListadoCache(const ListadoCache &lc)
{
	numImgMax = lc.numImgMax;
	vCacheImg = lc.vCacheImg;
}

/**
 Devuelve el numero de imagenes almacenadas en la cache
 @return Numero maximo de imagenes que se pueden almacenar
 */
int ListadoCache::getNumImagenesMax()
{
	return numImgMax;
}

/**
 Devuelve el numero actual de imagenes almacenadas en la cache de imagenes
 @return Numero de imagenes almacenadas en la cache
 */
int ListadoCache::getNumImagenesActual()
{
	return vCacheImg->size();
}

/**
 Devuelve el nombre de la imagen nom contenido en la lista de imagenes de la cache
 y la coloca en el primer lugar de la lista
 @param nom nombre del fichero que queremos obtener
 @return devuelve el nombre del fichero
 */
string ListadoCache::getImagenLista(const string &nom)
{
	string toret;
	
	toret = "";
	
	for(list<string>::iterator it = vCacheImg->begin(); it != vCacheImg->end(); ++it)
	{
		if(*it == nom) 
		{
			vCacheImg->erase(it);
			
			if(Glib::file_test(Utiles::direccionCache(nom), Glib::FILE_TEST_EXISTS))
			{
				toret = nom;
			}

			break;
		}
	}
	return toret;
}

/**
 Establece el numero maximo de imagenes almacenadas en la cache
 @param nmi numero max de imagenes a almacenar
 */
void ListadoCache::setNumImagenesMax(unsigned int nmi)
{
	numImgMax = nmi;
}

/**
 Añade el nombre de una imagen a la lista de imagenes de la cache. La imagen se
 añade al principio de la lista. En el caso de que la cache este llena elimina la
 ultima imagen de la cache y del sistema
 @param img nombre de la imagen a añadir
 */
void ListadoCache::addImagenCache(const string &img)
{	
	if(vCacheImg->size() >= numImgMax)
	{
		list<string>::iterator itB = vCacheImg->end();

		itB--;
		//Borramos la imagen del sistema
		Fichero::borraImagenSistema(Utiles::direccionCache(*itB));

		//Borramos la imagen de la cache
		vCacheImg->pop_back();	
	}

	vCacheImg->push_front(img);
}

/**
 Devuelve la lista con la cache de imagenes
 @return lista con la cache de imagenes
 */
list<string> *ListadoCache::getListaCache()
{
	return vCacheImg;
}

/**
 Ordena la lista de nombres de las imagenes almacenadas en cache colocando en primer
 lugar la recientemete mas usada que es la que le pasamos por el parametro img
 @param img nombre de la imagen mas recientemente usada
 */
void ListadoCache::reordenarListaImagenes(const string &img)
{
	for(list<string>::iterator it = vCacheImg->begin(); it != vCacheImg->end(); ++it)
	{
		if(*it == img) 
		{
			it = vCacheImg->erase(it);
		}
	}

	vCacheImg->push_front(img);
}

/**
 Sobrecarga del operador = 
 @param lc objeto de la clase ListadoCache
 @return devuelve un objeto de la clase ListadoCache
 */
const ListadoCache &ListadoCache::operator=(const ListadoCache &lc)
{
	this->numImgMax = lc.numImgMax;
	this->vCacheImg = lc.vCacheImg;

	return *this;
}
