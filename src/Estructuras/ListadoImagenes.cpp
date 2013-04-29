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

#include "ListadoImagenes.h"

/**
 Constructor
 */
ListadoImagenes::ListadoImagenes()
{

}

/**
 Destructor
 */
ListadoImagenes::~ListadoImagenes()
{

}

/**
 Constructor de copias
 */
ListadoImagenes::ListadoImagenes(const ListadoImagenes &li)
{
	int numImag;

	numImag = li.listaImagenesWeb.size();
	
	listaImagenesWeb.resize(numImag);

	for(int i = 0; i < numImag; i++)
	{
		listaImagenesWeb[i] = li.listaImagenesWeb[i];
	}
}

/**
 Introduce una imagen en el vector.
 @param iw, objeto DataImage que contiene datos de una imagen.
 */
void ListadoImagenes::setImagenVector(DataImage iw)
{
	listaImagenesWeb.push_back(iw);
}

/**
 Borra una imagen del vector.
 @param indice, entero con el indice del vector del dato que queremos borrar.
 */
void ListadoImagenes::borraImagenVector(int indice)
{
	listaImagenesWeb.erase(listaImagenesWeb.begin() + indice);
}

/**
 Devuelve un objeto imagenweb almacenado en el vector
 @param indice, entero que contiene el indice del vector.
 @return DataImage, puntero del objeto que queremos obtener del vector de imagenes.
 */
DataImage *ListadoImagenes::getImagenVector(int indice)
{
	return &listaImagenesWeb[indice];
}

/**
 Devuelve el tamaño del vector de imagenes.
 @return int, tamaño del vector de imagenes web.
 */
int ListadoImagenes::getTamanhoVectorImag()
{
	return listaImagenesWeb.size();
}

/**
 Sobrecarga del operador =
 */
const ListadoImagenes &ListadoImagenes::operator=(const ListadoImagenes &li)
{
	int numImag;

	numImag = li.listaImagenesWeb.size();
	
	this->listaImagenesWeb.resize(numImag);

	for(int i = 0; i < numImag; i++)
	{
		this->listaImagenesWeb[i] = li.listaImagenesWeb[i];
	}

	return *this;
}
