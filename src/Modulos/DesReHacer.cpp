/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DesReHacer.cpp
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

#include "DesReHacer.h"

/**
 Constructor.
 */
DesReHacer::DesReHacer()
{
	
}

/**
 Destructor.
 */
DesReHacer::~DesReHacer()
{
	
}

/**
 Introduce un objeto ListadoCelulas en la pila.
 @param op, objeto ListadoCelulas que contiene todas las celulas de la imagen.
 */
void DesReHacer::metePilaOper(ListadoCelulas op)
{
	this->pilaOperCelulas.push(op);
}

/**
 Saca el primer objeto ListadoCelulas de la pila.
 @return ListadoCelulas, primer elemento de la pila de tipo ListadoCeulas.
 */
ListadoCelulas DesReHacer::sacaPilaOper()
{
	return this->pilaOperCelulas.top();
}

/**
 Borra el elemento cabecera.
 */
void DesReHacer::borraElemento()
{
	this->pilaOperCelulas.pop();
}

/**
 Devuelve verdadero si la pila esta vacia.
 @return bool, true si la pila esta vacia, false en caso contrario.
 */
bool DesReHacer::pilaVacia()
{
	if(pilaOperCelulas.empty())
		return true;
	else
		return false;
}

/**
 Vacia la pila.
 */
void DesReHacer::vaciar()
{
	while(!pilaOperCelulas.empty())
	{
		pilaOperCelulas.pop();
	}
}
