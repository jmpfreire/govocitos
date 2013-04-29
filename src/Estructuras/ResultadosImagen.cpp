/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ResultadosImagen.cpp
 * Copyright (C) José Manuel Pintor Freire 2011 <jpfreire@correo.ei.uvigo.es>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ResultadosImagen.h"

/**
 Constructor.
 */
ResultadosImagen::ResultadosImagen()
{
	numAreaNoUse = 0;

	diametros.clear();
}

/**
 Destructor.
 */
ResultadosImagen::~ResultadosImagen()
{

}

/**
 Constructor de copias.
 */
ResultadosImagen::ResultadosImagen(const ResultadosImagen &ri)
{
	numAreaNoUse = ri.numAreaNoUse;

	numObj = ri.numObj;
	numPun = ri.numPun;

	diametros = ri.diametros;
}

/**
 */
void ResultadosImagen::inicializarNumPunObj(int numEst)
{
	for(int i = 0; i < numEst; i++)
	{
		numObj.push_back(0);
		numPun.push_back(0);
	}
}

/**
 */
double ResultadosImagen::getNumPun(int indice)
{
	return numPun[indice];
}

/**
 */
double ResultadosImagen::getNumObj(int indice)
{
	return numObj[indice];
}

/**
 Devuelve el area no usada de la imagen.
 @return double.
 */
double ResultadosImagen::getnumPunAreaNoUse()
{
	return numAreaNoUse;
}

/**
 Devuelve los diametros de los ovocitos de la imagen.
 @vector<double>.
 */
vector<double> ResultadosImagen::getDiametros()
{
	return diametros;
}

/**
*/
void ResultadosImagen::setNumObj(double no, int indice)
{
	numObj[indice] = no;
}

/**
 */
void ResultadosImagen::setNumPun(double no, int indice)
{
	numPun[indice] = no;
}

/**
 Establece el area no usable de la imagen.
 @param np, double.
 */
void ResultadosImagen::setnumPunAreaNoUse(double np)
{
	numAreaNoUse = np;
}

/**
 Establece los diametros de los ovocitos de la imagen.
 @param d, double, diametro de un ovocito.
 */
void ResultadosImagen::setDiametros(double d)
{
	diametros.push_back(d);
}

/**
 Sobrecarga del operador =.
 */
const ResultadosImagen &ResultadosImagen::operator=(const ResultadosImagen &ri)
{
	this->numAreaNoUse = ri.numAreaNoUse;

	this->numObj = ri.numObj;
	this->numPun = ri.numPun;

	this->diametros = ri.diametros;

	return *this;
}
