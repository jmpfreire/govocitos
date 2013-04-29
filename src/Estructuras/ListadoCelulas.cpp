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

#include "ListadoCelulas.h"

/**
 Constructo
 */
ListadoCelulas::ListadoCelulas()
{
	lastIdCell = -1;
}

/**
 Destructor
 */
ListadoCelulas::~ListadoCelulas()
{

}

/**
 Constructor de copias de la clase ListadoCelulas
 @param lc referencia objeto de la clase ListadoCelulas
 */
ListadoCelulas::ListadoCelulas(const ListadoCelulas &lc)
{
	listCells = lc.listCells;
	lastIdCell = lc.lastIdCell;
}

/**
 Devuelve el valor del ultimo id introducido correspondiente a la anterior celula
 @return ultimo id introducido
 */
int ListadoCelulas::getLastIdCell()
{
	return lastIdCell;
}

/**
 Aumenta el id de la celula en 1
 */
void ListadoCelulas::incrementaIdCell()
{
	lastIdCell++;
}

/**
 Establece el id de la ultima celula
 @param idc id de la ultima celula
 */
void ListadoCelulas::setLastIdCell(int idc)
{
	lastIdCell = idc;
}

/**
 Añade una nueva celula al vector que almacena las celulas
 @param cel objeto de la clase Celula
 */
void ListadoCelulas::setCelula(Celula cel)
{
	listCells.push_back(cel);
}

/**
 Devuelve el numero de celulas introducidas
 @return numero de celulas
 */
int ListadoCelulas::getNumCelulas()
{
	return listCells.size();
}

/**
 Devuelve una referencia a la celula seleccionada en el indice
 @param indice posicion del vector donde se encuentra la celula
 @return referencia de la celula
 */
Celula *ListadoCelulas::getCelula(int indice)
{
	return &listCells[indice];
}

/**
 Borra una celula contenida en el vector de celulas, la celula borrada es la que 
 ocupa la posicion indice en el vector
 @param indice posicion del vector de celulas
 */
void ListadoCelulas::borraCelula(int indice)
{
	listCells.erase(listCells.begin() + indice);
}

/**
 Sobrecarga del operador = para la clase ListadoCelulas
 @param lc objeto de la clase ListadoCelulas
 @return objeto de la clase ListadoCelulas
 */
const ListadoCelulas &ListadoCelulas::operator=(const ListadoCelulas &lc)
{
	this->listCells = lc.listCells;
	this->lastIdCell = lc.lastIdCell;
	
	return *this;
}
