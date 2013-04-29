/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * EstadoCeula.cpp
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

#include "EstadoCelula.h"

/**
 Constructor.
 */
EstadoCelula::EstadoCelula()
{

}

/**
 Destructor.
 */
EstadoCelula::~EstadoCelula()
{
	
}

/**
 Constructor de copias.
 @parm &ec, referencia de estado Celula.
 */
EstadoCelula::EstadoCelula(const EstadoCelula &ec) : ClasificaCelula(ec)
{
	colorEstadoR = ec.colorEstadoR;
	colorEstadoG = ec.colorEstadoG;
	colorEstadoB = ec.colorEstadoB;
}

/**
 Devuelve el color rojo del estado.
 @return double, valor de la componete R del sistema RGB.
 */
double EstadoCelula::getColorEstadoR()
{
	return colorEstadoR;
}

/**
 Devuelve el color verde del estado.
 @return double, valor de la componete G del sistema RGB.
 */
double EstadoCelula::getColorEstadoG()
{
	return colorEstadoG;
}

/**
 Devuelve el color azul del estado.
 @return double, valor de la componete B del sistema RGB.
 */
double EstadoCelula::getColorEstadoB()
{
	return colorEstadoB;
}

/**
 Establece el color del estado a traves del objeto Gdk::Color que contiene los 3
 colores del sistema RGB.
 @param cec, Gdk::Color que contiene el color.
 */
void EstadoCelula::setColorEstado(Gdk::Color cec)
{
	colorEstadoR = cec.get_red();
	colorEstadoG = cec.get_green();
	colorEstadoB = cec.get_blue();
}

/**
 Sobrecarga del operador de asignacion.
 @param ec, objeto de la clase EstadoCelula.
 @return EstadoCelula, objeto de la clase EstadoCelula resultante de la asignacion.
 */
const EstadoCelula &EstadoCelula::operator=(const EstadoCelula &ec)
{
	ClasificaCelula::operator=(ec);
	this->colorEstadoR = ec.colorEstadoR;
	this->colorEstadoG = ec.colorEstadoG;
	this->colorEstadoB = ec.colorEstadoB;
	
	return *this;
}
