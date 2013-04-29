/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ListadoIndividuo.cpp
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

#include "ListadoIndividuo.h"

/**
 Constructor
 */
ListadoIndividuo::ListadoIndividuo()
{
	numImagenes = numXmlAnalizados = 0;
	codigoCampanha = "";
	codigoMuestreo = "";
	codigoIndividuo = "";
	codigoEspecie = "";
	pesoOvarioFresco = 0.0;
	valorBeta = 0.0;
	valorScherle = 0.0;
	formolFresco = 0.0;
}

/**
 Destructor
 */
ListadoIndividuo::~ListadoIndividuo()
{

}

/**
 Constructor de copias
 */
ListadoIndividuo::ListadoIndividuo(const ListadoIndividuo &li)
{
	datosIndiv = li.datosIndiv;
	datosCelulas = li.datosCelulas;
	listaResult = li.listaResult;

	codigoCampanha = li.codigoCampanha;
	codigoMuestreo = li.codigoMuestreo;
	codigoIndividuo = li.codigoIndividuo;
	codigoEspecie = li.codigoEspecie;
	numImagenes = li.numImagenes;
	numXmlAnalizados = li.numXmlAnalizados;

	pesoOvarioFresco = li.pesoOvarioFresco;
	valorBeta = li.valorBeta;
	valorScherle = li.valorScherle;
	formolFresco = li.formolFresco;
}

/**
 Devuelve un string con el codigo de la campaña a la que pertenece la imagen
 @return codigo de la campaña
 */
string ListadoIndividuo::getCampanhaInd()
{
	return codigoCampanha;
}

/**
 Devuelve un string con el codigo del muestreo al que pertenece la imagen
 @return codigo de muestreo
 */
string ListadoIndividuo::getMuestreoInd()
{
	return codigoMuestreo;
}

/**
 Devuelve un string con el codigo del individuo al que pertenece la imagen
 @return codigo de individuo
 */
string ListadoIndividuo::getIndividuoInd()
{
	return codigoIndividuo;
}

/**
 */
string ListadoIndividuo::getEspecieInd()
{
	return codigoEspecie;
}

/**
 Devuelve el numero de imagenes.
 @return int, que contiene el numero de imagenes.
 */
int ListadoIndividuo::getNumImagenes()
{
	return numImagenes;
}

/**
 Devuelve el numero del xml analizados.
 @return int, contiene el numero de xml analizados.
 */
int ListadoIndividuo::getNumXmlAnalizados()
{
	return numXmlAnalizados;
}

/**
 Devuelve el peso del ovario fresco.
 @return double, contiene el valor del peso ovario fresco.
 */
double ListadoIndividuo::getPesoOvarioFresco()
{
	return pesoOvarioFresco;
}

/**
 Devuelve el valor de beta.
 @return double, contiene el valor de beta.
 */
double ListadoIndividuo::getValorBeta()
{
	return valorBeta;
}

/**
 Devuelve el valor del scherle.
 @return double, contiene el valor del scherle.
 */
double ListadoIndividuo::getValorScherle()
{
	return valorScherle;
}

/**
 Devuelve el formol fresco.
 @return double, contiene el valor del peso en formol fresco
 */
double ListadoIndividuo::getFormolFresco()
{
	return formolFresco;
}

/**
 Establece el valor del peso del ovario fresco.
 @param d, double que contiene el valor del peso del ovario fresco.
 */
void ListadoIndividuo::setPesoOvarioFresco(double d)
{
	pesoOvarioFresco = d;
}

/**
 Establece el valor de beta.
 @param d, double que cotienen el valor de beta.
 */
void ListadoIndividuo::setValorBeta(double d)
{
	valorBeta = d;
}

/**
 Establece el valor del scherle.
 @param d, double que contiene el valor del scherle.
 */
void ListadoIndividuo::setValorScherle(double d)
{
	valorScherle = d;
}

/**
 Establece el valor del formol fresco.
 @param d, double que contiene el valor del formol fresco.
 */
void ListadoIndividuo::setFormolFresco(double d)
{
	formolFresco = d;
}

/**
 Establece la campaña a la que pertenece la imagen
 @param campI campaña de la imagen
 */
void ListadoIndividuo::setCampanhaInd(const string &campI)
{
	codigoCampanha = campI;
}

/**
 Establece el muestreo al que pertenece la imagen
 @param muestI muestreo de la imagen
 */
void ListadoIndividuo::setMuestreoInd(const string &muestI)
{
	codigoMuestreo = muestI;
}

/**
 */
void ListadoIndividuo::setEspecieInd(const string &espI)
{
	codigoEspecie = espI;
}

/**
 Establece el individuo al que pertenece la imagen
 @param indI individuo de la imagen
 */
void ListadoIndividuo::setIndividuoInd(const string &indI)
{
	codigoIndividuo = indI;
}

/**
 Establece el valor del resutaldo de la imagen.
 @param ri, objeto del tipo ResultadoImagen.
 */
void ListadoIndividuo::setResultadoImagenes(ResultadosImagen ri)
{
	listaResult.push_back(ri);
}

/**
 Introduce una imagen en el vector
 @param iw, objeto ImageCells que contiene la imagen.
 */
void ListadoIndividuo::setImagenVector(ImageCells iw)
{
	datosIndiv.push_back(iw);
}

/**
 Introduce el listado de celulas de una imagen
 @param lc, objeto ListadoCeulas que contiene las celulas.
 */
void ListadoIndividuo::setCelulasImagen(ListadoCelulas lc)
{
	datosCelulas.push_back(lc);
}

/**
 Incrementa el numero de imagenes dle individuo.
 */
void ListadoIndividuo::incrementaImagenes()
{
	numImagenes++;
}

/**
 Incrementa el numero de xml analizados del individuo.
 */
void ListadoIndividuo::incrementaXmlAnalizado()
{
	numXmlAnalizados++;
}

/**
 Borra una imagen del vector
 @param indice, entero con el indice de la imagen.
 */
void ListadoIndividuo::borraImagenVector(int indice)
{
	datosIndiv.erase(datosIndiv.begin() + indice);
}

/**
 Borra las celulas de una imagen
 @param indice, entero con el indice de las celulas.
 */
void ListadoIndividuo::borraCelulasImagen(int indice)
{
	datosCelulas.erase(datosCelulas.begin() + indice);
}

/**
 Vacia el vector de resutaldos.
 */
void ListadoIndividuo::vaciaVectorResultados()
{
	listaResult.clear();
}

/**
 Devuelve el objeto que contiene los resultados de la imagen.
 @param indice, entero que contiene la posición de los resultados de la imagen.
 @return ResultadosImagen, objeto con los resultados de la imagen.
 */
ResultadosImagen ListadoIndividuo::getResultadosImg(int indice)
{
	return listaResult[indice];
}

/**
 Devuelve un objeto imagenweb almacenado en el vector.
 @param indice, entero con el indice del vector de la imagen.
 @return ImageCells, puntero que contiene la información de la imagen.
 */
ImageCells *ListadoIndividuo::getImagenVector(int indice)
{
	return &datosIndiv[indice];
}

/**
 Devuelve un objeto ListadoCelulas almacenado en el vector
 @param indice, entero con el indice del vector de las celulas.
 @return ListadoCelulas, puntero que contiene la información de las celulas de la
 imagen.
 */
ListadoCelulas *ListadoIndividuo::getCelulasVector(int indice)
{
	return &datosCelulas[indice];
}

/**
 Devuelve el tamaño del vector de resultados.
 @return int, tamaño del vector de resultados.
 */
int ListadoIndividuo::getNumResultadoImagenes()
{
	return listaResult.size();
}

/**
 Devuelve el tamaño del vector de imagenes
 @return int, tamaño del vector de imagenes.
 */
int ListadoIndividuo::getTamanhoVectorImag()
{
	return datosIndiv.size();
}

/**
 Devuelve el tamaño del vector de celulas
 @param int, tamaño del vector de celulas.
 */
int ListadoIndividuo::getTamanhoVectorCelulas()
{
	return datosCelulas.size();
}

/**
 Sobrecarga del operador =
 */
const ListadoIndividuo &ListadoIndividuo::operator=(const ListadoIndividuo &li)
{
	this->datosIndiv = li.datosIndiv;
	this->datosCelulas = li.datosCelulas;
	this->listaResult = li.listaResult;

	this->codigoCampanha = li.codigoCampanha;
	this->codigoMuestreo = li.codigoMuestreo;
	this->codigoIndividuo = li.codigoIndividuo;
	this->codigoEspecie = li.codigoEspecie;
	this->numImagenes = li.numImagenes;
	this->numXmlAnalizados = li.numXmlAnalizados;
	this->pesoOvarioFresco = li.pesoOvarioFresco;
	this->valorBeta = li.valorBeta;
	this->valorScherle = li.valorScherle;
	this->formolFresco = li.formolFresco;
	
	return *this;
}
