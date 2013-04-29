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

#include "NucleoCelula.h"

/**
 Constructor
 */
NucleoCelula::NucleoCelula()
{

}

/**
 Destructor
 */
NucleoCelula::~NucleoCelula()
{

}

/**
 Constructor de copias
 */
NucleoCelula::NucleoCelula(const NucleoCelula &nc)
{
	nucleoX = nc.nucleoX;
	nucleoY = nc.nucleoY;
}

/**
 Devuelve una referencia del vector de coordenadas X
 @return referencia del vector
 */
const vector<int> *NucleoCelula::getNucleoX()
{
	return &nucleoX;
}

/**
 Devuelve una referencia del vector de coordenadas Y
 @return referencia del vector
 */
const vector<int> *NucleoCelula::getNucleoY()
{
	return &nucleoY;
}

/**
 Copia los datos del vector pasado por parametro en el vector nucleoX
 @param nx vector con las coordenadas X
 */
void NucleoCelula::setNucleoX(vector<int> nx)
{
	nucleoX = nx;
}

/**
 Copia los datos del vector pasado por parametro en el vector nucleoY
 @param ny vector con las coordenadas Y
 */
void NucleoCelula::setNucleoY(vector<int> ny)
{
	nucleoY = ny;
}

/**
 Sobrecarga del operador igual copia el contenido del vector pasado por parametro
 a otro vector
 @param nc objeto de la clase NucleoCelula
 @return objeto de la clase NucleoCelula
 */
const NucleoCelula &NucleoCelula::operator=(const NucleoCelula &nc)
{
	this->nucleoX = nc.nucleoX;
	this->nucleoY = nc.nucleoY;

	return *this;
}
