/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Celula.cpp
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

#include "Celula.h"

/**
 Constructor de la clase Celula.
 */
Celula::Celula()
{
	idCelula = 0;
	claseCelula = "";
	estadoCelula = "";
	maxMinPuntosCell[0] = 0;
	maxMinPuntosCell[1] = 0;
	maxMinPuntosCell[2] = 0;
	maxMinPuntosCell[3] = 0;
	diametroCell = 0.0;
	celulaCandidata = -1;
	areaCelula = 0;
}

/**
 Destructor.
 */
Celula::~Celula()
{

}

/**
 Constructor de copias de la clase Celula.
 @param cl, referencia del objeto de la clase Celula.
 */
Celula::Celula(const Celula &cl)
{
	idCelula = cl.idCelula;
	claseCelula = cl.claseCelula;
	estadoCelula = cl.estadoCelula;
	maxMinPuntosCell[0] = cl.maxMinPuntosCell[0];
	maxMinPuntosCell[1] = cl.maxMinPuntosCell[1];
	maxMinPuntosCell[2] = cl.maxMinPuntosCell[2];
	maxMinPuntosCell[3] = cl.maxMinPuntosCell[3];
	bordeCoordX = cl.bordeCoordX;
	bordeCoordY = cl.bordeCoordY;
	diametroCell = cl.diametroCell;
	celulaCandidata = cl.celulaCandidata;
	areaCelula = cl.areaCelula;
}

/**
 Devuelve el identificador de la celula.
 @return int, id de la celula.
 */
int Celula::getIdCelula()
{
	return idCelula;
}

/**
 Devuelve la clase a la que pertenece la celula.
 @return stirng, clase de la celula.
 */
string Celula::getClaseCelula()
{
	return claseCelula;
}

/**
 Devuelve el estado al que pertenece la celula.
 @return stirng, estado de la celula.
 */
string Celula::getEstadoCelula()
{
	return estadoCelula;
}

/**
 Devuelve una de las coordenadas maximas o minimas de la celula.
 @param indice,(int) posicion del array.
 @return int, coordenada contenida en el vector.
 */
int Celula::getCoordMaxMin(int indice)
{
	return maxMinPuntosCell[indice];
}

/**
 Devuelve el diametro de la celula.
 @return double, diametro de la celula.
 */
double Celula::getDiametroCell()
{
	return diametroCell;
}

/**
 Devuelve el numero de la celula candidata.
 @return int, numero celula candidata.
 */
int Celula::getCelulaCandidata()
{
	return celulaCandidata;
}

/**
 Devuelve el area de la celula.
 @return double, area de la celula.
 */
double Celula::getAreaCelula()
{
	return areaCelula;
}

/**
 Establece el valor del area de la celula.
 @param a, double con el area de la celula.
 */
void Celula::setAreaCelula(double a)
{
	areaCelula = a;
}

/**
 Establece la celula candidata que se ha utilizado.
 @param c, (int) indice de la celula candidata usada.
 */
void Celula::setCelulaCandidata(int c)
{
	celulaCandidata = c;
}

/**
 Establece el identificador de la celula.
 @param idc, (int) id de la celula.
 */
void Celula::setIdCelula(int idc)
{
	idCelula = idc;
}

/**
 Establece la clase a la que pertenece la celula.
 @param cc, stirng que contiene la clase de la celula.
 */
void Celula::setClaseCelula(const string &cc)
{
	claseCelula = cc;
}

/**
 Establece el estado al que pertenece la celula.
 @param ec, stirng que contiene el estado de la celula.
 */
void Celula::setEstadoCelula(const string &ec)
{
	estadoCelula = ec;
}

/**
 Borra las coordenads del vector X que contienen el borde de la celula.
 */
void Celula::borraDatosVectorX()
{
	bordeCoordX.clear();
}

/**
 Borra las coordenads del vector Y que contienen el borde de la celula.
 */
void Celula::borraDatosVectorY()
{
	bordeCoordY.clear();
}

/**
 Añade una coordenada X al vector que contiene todas las coordenadas x del borde
 de la celula.
 @param cx, vector de int que contiene las coordenadas X del borde.
 */
void Celula::setCoordCellX(vector<int> cx)
{
	bordeCoordX = cx;
}

/**
 Añade una coordenada Y al vector que contiene todas las coordenadas y del borde
 de la celula.
 @param cy, vector de int que contiene las coordenadas Y del borde.
 */
void Celula::setCoordCellY(vector<int> cy)
{
	bordeCoordY = cy;
}

/**
 Establece la coordenada max en la posicion determinada por el indice.
 @param indice, int que contiene la posicion del vector.
 @param coord, coordenada a introducir.
 */
void Celula::setCoordMaxMin(int indice, int coord)
{
	maxMinPuntosCell[indice] = coord;
}

/**
 Establece el diametro de la celula.
 @param dc, double que contiene el diametro de la celula.
 */
void Celula::setDiametroCell(double dc)
{
	diametroCell = dc;
}

/**
 Devuelve una referencia del vector de bordes que contiene las coordenadas X de
 la celula.
 @return vector<int>, que contiene coordenadas X del borde.
 */
vector<int> *Celula::getBordeCellX()
{
	return &bordeCoordX;
}

/**
 Devuelve una referencia del vector de bordes que contiene las coordenadas Y de
 la celula.
 @return vector<int>, que contiene coordenadas Y del borde.
 */
vector<int> *Celula::getBordeCellY()
{
	return &bordeCoordY;
}

/**
 Sobrecarga del operador = de la clase Celula.
 @param cl, objeto de la clase Celula.
 @return Celula, un objeto de la clase celula resultado de la operacion de asignacion.
 */
const Celula &Celula::operator=(const Celula &cl)
{
	this->idCelula = cl.idCelula;
	this->claseCelula = cl.claseCelula;
	this->estadoCelula = cl.estadoCelula;
	this->maxMinPuntosCell[0] = cl.maxMinPuntosCell[0];
	this->maxMinPuntosCell[1] = cl.maxMinPuntosCell[1];
	this->maxMinPuntosCell[2] = cl.maxMinPuntosCell[2];
	this->maxMinPuntosCell[3] = cl.maxMinPuntosCell[3];
	this->bordeCoordX = cl.bordeCoordX;
	this->bordeCoordY = cl.bordeCoordY;
	this->diametroCell = cl.diametroCell;
	this->celulaCandidata = cl.celulaCandidata;
	this->areaCelula = cl.areaCelula;

	return *this;
}
