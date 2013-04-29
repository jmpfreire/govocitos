/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ClasificaCelula.cpp
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

#include "ClasificaCelula.h"

/**
 Constructor.
 */
ClasificaCelula::ClasificaCelula()
{
	etiqueta = "";
	nombreTipo = "";
	descripcion = "";
	enUso = false;
}

/**
 Destructor.
 */
ClasificaCelula::~ClasificaCelula()
{

}

/**
 Constructor de copias.
 @param cc, objeto ClasificaCeula.
 */
ClasificaCelula::ClasificaCelula(const ClasificaCelula &cc)
{
	etiqueta = cc.etiqueta;
	nombreTipo = cc.nombreTipo;
	descripcion = cc.descripcion;
	enUso = cc.enUso;
}

/**
 Devuelve un string que contiene la etiqueta de clasificacion.
 @return string, contiene la etiqueta de clasificacion.
 */
string ClasificaCelula::getEtiquetaClasificacion()
{
	return etiqueta;
}

/**
 Devuelve un stirng que contiene el nombre de clasificacion.
 @return string, contiene el nombre de clasificacion.
 */
string ClasificaCelula::getNombreClasificacion()
{
	return nombreTipo;
}

/**
 Devuelve un string que contiene la descripcion de la clasificacion.
 @return string, contiene la descripcion de la clasificacion.
 */
string ClasificaCelula::getDescripcionClasificacion()
{
	return descripcion;
}

/**
 Devuelve el valor de enUso variable de tipo bool.
 @return bool, Verdadero si esta en uso, falos en caso contrario.
 */
bool ClasificaCelula::getEnUso()
{
	return enUso;
}

/**
 Establece el valor de la variable en uso de tipo bool.
 @param eu, parametro al que se iguala el valor de enUso.
 */
void ClasificaCelula::setEnUso(bool eu)
{
	enUso = eu;
}

/**
 Establece la etiqueta de clasificacion.
 @param eC, string con la etiqueta de clasificacion.
 */
void ClasificaCelula::setEtiquetaClasificacion(const string &eC)
{
	etiqueta = eC;
}

/**
 Establece el nombre de clasificacion.
 @param nEC, string con el nombre de la clasificacion.
 */
void ClasificaCelula::setNombreClasificacion(const string &nEC)
{
	nombreTipo = nEC;
}

/**
 Establece la descripcion de la clasificacion.
 @param dEC, string con la descripcion de la clasificacion.
 */
void ClasificaCelula::setDescripcionClasificacion(const string &dEC)
{
	descripcion = dEC;
}

/**
 Sobrecarga del operador de asignacion.
 @param ec, objeto de la clase ClasificaCeula.
 @return ClasificaCelula, devuelve el objeto de clasificacion.
 */
const ClasificaCelula &ClasificaCelula::operator=(const ClasificaCelula &ec)
{
	this->etiqueta = ec.etiqueta;
	this->nombreTipo = ec.nombreTipo;
	this->descripcion = ec.descripcion;
	this->enUso = ec.enUso;
	
	return *this;
}
