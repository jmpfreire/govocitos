/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ClaseCelula.cpp
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

#include "ClaseCelula.h"

/**
 Constructor.
 */
ClaseCelula::ClaseCelula()
{
	linea = 0;
}

/**
 Destructor.
 */
ClaseCelula::~ClaseCelula()
{

}

/**
 Constructor de copias.
 @param cc, referencia de ClaseCelula.
 */
ClaseCelula::ClaseCelula(const ClaseCelula &cc) : ClasificaCelula(cc)
{
	linea = cc.linea;
}

/**
 Devuelve el tipo de linea que se esta usando.
 @return int, id del tipo de linea a usar.
 */
int ClaseCelula::getLinea()
{
 return linea;
}

/**
 Establece el tipo de linea que se va usar.
 @param l, int que contiene el tipo de linea a usar.
 */
void ClaseCelula::setLinea(int l)
{
	linea = l;
}

/**
 Sobrecarga del operador de asignacion.
 @param cc, objeto de la clase ClaseCelula.
 @return ClaseCelula, objeto de la clase ClaseCelula resultante de la asignacion.
 */
const ClaseCelula &ClaseCelula::operator=(const ClaseCelula &cc)
{
	ClasificaCelula::operator=(cc);
	this->linea = cc.linea;

	return *this;
}
