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

#include "OpcionesRej.h"

/**
 Cosntructor.
 */
OpcionesRej::OpcionesRej()
{
	numFilas = 0;
	numColumnas = 0;
	numPuntos = 0;
	separaPuntos = 0;
	idRej = 0;
}

/**
 Destructor.
 */
OpcionesRej::~OpcionesRej()
{
	
}

/**
 Constructor de copias.
 */
OpcionesRej::OpcionesRej(const OpcionesRej &oR)
{
	numFilas = oR.numFilas;
	numColumnas = oR.numColumnas;
	numPuntos = oR.numPuntos;
	separaPuntos = oR.separaPuntos;
	idRej = oR.idRej;
}

/**
 Devuelve el numero de filas.
 @return int.
 */
int OpcionesRej::getNumFilas()
{
	return numFilas;
}

/**
 Devuelve el numero de columnas.
 @return int.
 */
int OpcionesRej::getNumColumnas()
{
	return numColumnas;
}

/**
 Devuelve el numero de puntos.
 @return int.
 */
int OpcionesRej::getNumPuntos()
{
	return numPuntos;
}

/**
 Devuelve la separacion de puntos de la rejilla.
 @return int.
 */
int OpcionesRej::getSeparaPuntos()
{
	return separaPuntos;
}

/**
 Devuelve el nombre.
 @return int.
 */
int OpcionesRej::getID()
{
	return idRej;
}

/**
 Establece el valor del numero de filas.
 @param f, int.
 */
void OpcionesRej::setNumFilas(int f)
{
		numFilas = f;
}

/**
 Establece el valor del numero de columnas.
 @param c, int.
 */
void OpcionesRej::setNumColumnas(int c)
{
	numColumnas = c;
}

/**
 Establece el valor del numero de puntos.
 @param p, int.
 */
void OpcionesRej::setNumPuntos(int p)
{
	numPuntos = p;
}

/**
 Establece el valor de la separacion de puntos de la rejilla.
 @param sp, int.
 */
void OpcionesRej::setSeparaPuntos(int sp)
{
	separaPuntos = sp;
}

/**
 Establece el nombre de la rejilla.
 @param id, int.
 */
void OpcionesRej::setID(int id)
{
	idRej = id;
}

/**
 Sobrecarga del operador =
 */
const OpcionesRej &OpcionesRej::operator=(const OpcionesRej &oR)
{
	this->numFilas = oR.numFilas;
	this->numColumnas = oR.numColumnas;
	this->numPuntos = oR.numPuntos;
	this->separaPuntos = oR.separaPuntos;
	this->idRej = oR.idRej;
	
	return *this;
}
