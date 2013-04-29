/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ResultFecundidad.cpp
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

#include "ResultFecundidad.h"

/**
 Constructor.
 */
ResultFecundidad::ResultFecundidad()
{
	valorK = 0.0;
	numImagenes = idRejilla = numOvocitos = 0;
	areaRejilla = 0.0;
	metodoCalc = "";
	fecundidadEst.clear();
}

/**
 Destructor.
 */
ResultFecundidad::~ResultFecundidad()
{

}

/**
 Constructor de copias.
 */
ResultFecundidad::ResultFecundidad(const ResultFecundidad &lr)
{
	valorK = lr.valorK;
	numOvocitos = lr.numOvocitos;
	areaRejilla = lr.areaRejilla;
	numImagenes = lr.numImagenes;
	idRejilla = lr.idRejilla;
	metodoCalc = lr.metodoCalc;

	fecundidadEst = lr.fecundidadEst;
}


/**
 */
void ResultFecundidad::inicializaResulFec(int numEstados)
{
	for(int i = 0; i < numEstados; i++)
	{
		fecundidadEst.push_back(0.0);
	}
}

/**
 */
double ResultFecundidad::getFecundidadEst(int indice)
{
	return fecundidadEst[indice];
}

/**
 Devuelve el valor de k.
 @return double.
 */
double ResultFecundidad::getValorK()
{
	return valorK;
}

/**
 Devuelve el numero de ovocitos.
 @return int.
 */
int ResultFecundidad::getNumOvocitos()
{
	return numOvocitos;
}

/**
 Devuelve el area de la rejilla.
 @return double.
 */
double ResultFecundidad::getAreaRejilla()
{
	return areaRejilla;
}

/**
 Devuelve el numero de las imagenes analizadas.
 @return int.
 */
int ResultFecundidad::getNumImagenes()
{
	return numImagenes;
}

/**
 Devuelve el identificador de la rejilla.
 @return int.
 */
int ResultFecundidad::getIdRejilla()
{
	return idRejilla;
}

/**
 Devuelve el metodo de calculo.
 @return string.
 */
string ResultFecundidad::getMetodoCalculo()
{
	return metodoCalc;
}

/**
 */
void ResultFecundidad::setFecundidadEst(double f, int indice)
{
	fecundidadEst[indice] = f;
}

/**
 Establece el valor del area de la rejilla.
 @param a, double.
 */
void ResultFecundidad::setAreaRejilla(double a)
{
	areaRejilla = a;
}

/**
 Establece el numero de ovocitos.
 @param num, int.
 */
void ResultFecundidad::setNumOvocitos(int num)
{
	numOvocitos = num;
}

/**
 Establece el valor de k.
 @param k, double.
 */
void ResultFecundidad::setValorK(double k)
{
	valorK = k;
}

/**
 Establece el numero de imagenes.
 @param nI, int.
 */
void ResultFecundidad::setNumImagenes(int nI)
{
	numImagenes = nI;
}

/**
 Establece el identificador de la rejilla.
 @param id, int.
 */
void ResultFecundidad::setIdRejilla(int id)
{
	idRejilla = id;
}

/**
 Establece el metodo de calculo.
 @param m, string.
 */
void ResultFecundidad::setMetodoCalculo(const string &m)
{
	metodoCalc = m;
}

/**
 Sobrecarga del operador =.
 */
const ResultFecundidad &ResultFecundidad::operator=(const ResultFecundidad &lr)
{
	this->valorK = lr.valorK;
	this->numOvocitos = lr.numOvocitos;
	this->areaRejilla = lr.areaRejilla;
	this->numImagenes = lr.numImagenes;
	this->idRejilla = lr.idRejilla;
	this->metodoCalc = lr.metodoCalc;

	this->fecundidadEst = lr.fecundidadEst;

	return *this;
}
