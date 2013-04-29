/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DataImage.cpp
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

#include "DataImage.h"

/**
 Constructor.
 */
DataImage::DataImage()
{
	md5CRC = "";
	rutaImg = "";
	nombreImg = "";
	codigoCampanha = "";
	codigoMuestreo = "";
	codigoIndividuo = "";
	codigoImagen = "";
	calibracionImg = 1;
	rutaXmlImg = "";
	anchoImg = altoImg = 0;
	specieImage = "";
	diametroMaximo = 0.0;
	diametroMinimo = 0.0;
}

/**
 Destructor.
 */
DataImage::~DataImage()
{

}

/**
 Constructor de copias.
 @param ic, referencia del objeto DataImage.
 */
DataImage::DataImage(const DataImage &ic)
{
	md5CRC = ic.md5CRC;
	rutaImg = ic.rutaImg;
	nombreImg = ic.nombreImg;
	codigoCampanha = ic.codigoCampanha;
	codigoMuestreo = ic.codigoMuestreo;
	codigoIndividuo = ic.codigoIndividuo;
	codigoImagen = ic.codigoImagen;
	calibracionImg = ic.calibracionImg;
	rutaXmlImg = ic.rutaXmlImg;
	nombreXml = ic.nombreXml;
	altoImg = ic.altoImg;
	anchoImg = ic.anchoImg;
	specieImage = ic.specieImage;
	nombreImgComp = ic.nombreImgComp;
	tipoImg = ic.tipoImg;
	diametroMaximo = ic.diametroMaximo;
	diametroMinimo = ic.diametroMinimo;
}
			
/**
 Devuelve un string que contiene el nombre de la imagen.
 @return string, nombre de la imagen.
 */
string DataImage::getNombreImg()
{
	return nombreImg;
}

/**
 Devuelve un double que contiene la calibracion de la imagen.
 @return double, calibracion de la imagen.
 */
double DataImage::getCalibracionImg()
{
	return calibracionImg;
}

/**
 Devuelve un string con el codigo de la campaña a la que pertenece la imagen.
 @return string, codigo de la campaña.
 */
string DataImage::getCampanhaImg()
{
	return codigoCampanha;
}

/**
 Devuelve un string con el codigo del muestreo al que pertenece la imagen.
 @return stirng, codigo de muestreo.
 */
string DataImage::getMuestreoImg()
{
	return codigoMuestreo;
}

/**
 Devuelve un string con el codigo del individuo al que pertenece la imagen.
 @return string, codigo de individuo.
 */
string DataImage::getIndividuoImg()
{
	return codigoIndividuo;
}

/**
 Devuelve un string con el codigo de la imagen.
 @return string, codigo de la imagen.
 */
string DataImage::getCodigoImagen()
{
	return codigoImagen;
}

/**
 Devuelve un string con la ruta del xml perteneciente a la imagen.
 @return string, ruta del xml.
 */
string DataImage::getRutaXmlImg()
{
	return rutaXmlImg;
}

/**
 Devuelve un string con la ruta de la imagen.
 @return string, ruta de la imagen.
 */
string DataImage::getRutaImg()
{
	return rutaImg;
}

/**
 Devuelve un string con el nombre del fichero xml.
 @return string, nombre del xml.
 */
string DataImage::getNombreXml()
{
	return nombreXml;
}

/**
 Devuevel un string que contiene el md5 de la imagen.
 @return string, md5 de la imagen.
 */
string DataImage::getMd5Img()
{
	return md5CRC;
}

/**
 Devuelve un entero que contiene el ancho de la imagen.
 @return int, ancho de la imagen.
 */
int DataImage::getAnchoImg()
{
	return anchoImg;
}

/**
 Devuelve un entero que contiene el alto de la imagen.
 @return int, alto de la imagen.
 */
int DataImage::getAltoImg()
{
	return altoImg;
}

/**
 Devuelve un string que contiene la specie de la imagen.
 @return string, specie de la imagen.
 */
string DataImage::getSpecieImage()
{
	return specieImage;
}

/**
 Devuelve un string que contiene el nombre completo de la imagen.
 @return string, nombre completo de la imagen.
 */
string DataImage::getNombreImgCompleto()
{
	return nombreImgComp;
}

/**
 Devuelve un string que contiene el tipo del fichero de la imagen.
 @return string, tipo del fichero de la imagen
 */
string DataImage::getTipoImg()
{
	return tipoImg;
}

/**
 Devuelve el diametro Maximo de los ovocitos a analizar.
 @return double, valor del diametro maximo.
 */
double DataImage::getDiametroMax()
{
	return diametroMaximo;
}

/**
 Devuelve el diametro minimo de los ovocitos a analizar.
 @return double, valor del diametro minimo.
 */
double DataImage::getDiametroMin()
{
	return diametroMinimo;
}

/**
 Establece la especie de la imagen.
 @param si, string que contiene la especie de la imagen.
 */
void DataImage::setSpecieImage(const string &si)
{
	specieImage = si;
}

/**
 Establece el nombre de la imagen pasado por parametro, ademas coge el nombre sin
 terminacio y el tipo de imagen.
 @param ni, string que contiene nombre de la imagen.
 */
void DataImage::setNombreImg(const string &ni)
{	
	size_t found;
	
	nombreImgComp = ni;	

	//Nombre y tipo
	found = nombreImgComp.find_last_of(".");	
	nombreImg = nombreImgComp.substr(0, found);
	tipoImg = nombreImgComp.substr(found+1);	
}

/**
 Establece el tipo de la imagen pasado por parametro.
 @param tp, string que contiene el tipo de la imagen.
 */
void DataImage::setTipoImg(const string &tp)
{
	tipoImg = tp;
}

/**
 Establece la calibracion de la imagen pasado por parametro.
 @param calibracion, double que contiene calibracion de la imagen.
 */
void DataImage::setCalibracionImg(double cl)
{
	calibracionImg = cl;
}

/**
 Establece la campaña a la que pertenece la imagen.
 @param campI, string que contiene campaña de la imagen.
 */
void DataImage::setCampanhaImg(const string &campI)
{
	codigoCampanha = campI;
}

/**
 Establece el muestreo al que pertenece la imagen.
 @param muestI, stirng que contiene muestreo de la imagen.
 */
void DataImage::setMuestreoImg(const string &muestI)
{
	codigoMuestreo = muestI;
}

/**
 Establece el individuo al que pertenece la imagen.
 @param indI, string que contiene individuo de la imagen.
 */
void DataImage::setIndividuoImg(const string &indI)
{
	codigoIndividuo = indI;
}

/**
 Establece el codigo de la imagen.
 @param cdI, string que contiene codigo de la imagen.
 */
void DataImage::setCodigoImagen(const string &cdI)
{
	codigoImagen = cdI;
}

/**
 Establece la ruta del xml de la imagen.
 @param rxi, string que contiene ruta del xml.
 */
void DataImage::setRutaXmlImg(const string &rxi)
{
	rutaXmlImg = rxi;
}

/**
 Establece la ruta de la imagen.
 @param ri, string que contiene la ruta de la imagen.
 */
void DataImage::setRutaImg(const string &ri)
{
	rutaImg = ri;
}

/**
 Establece el nombre del fichero xml
 @param nx, string que contiene el nombre del xml.
 */
void DataImage::setNombreXml(const string &nx)
{
	nombreXml = nx;
}

/**
 Establece el md5 de la imagen.
 @param md5, string que contiene el md5 de la imagen.
 */
void DataImage::setMd5Img(const string &md5)
{
	md5CRC = md5;
}

/**
 Establece el ancho de la imagen pasado por parametro.
 @param ancho, int que contiene ancho de la imagen.
 */
void DataImage::setAnchoImg(int ancho)
{
	anchoImg = ancho;
}

/**
 Establece el alto de la imagen pasado por parametro.
 @param alto, int que contiene el alto de la imagen.
 */
void DataImage::setAltoImg(int alto)
{
	altoImg = alto;
}

/**
 Establece el valor del diametro maximo de los ovocitos a analizar.
 @param diam, double que contiene el valor maximo de los diametros.
 */
void DataImage::setDiametroMax(double diam)
{
	diametroMaximo = diam;
}

/**
 Establece el valor del diametro minimo de los ovocitos a analizar.
 @param diam, double que contiene el valor minimo de los diametros.
 */
void DataImage::setDiametroMin(double diam)
{
	diametroMinimo = diam;
}

/**
 Sobrecarga del operador =.
 @param ic, objeto de la clase DataImage.
 @return DataImage, devuelve un objeto de la clase DataImage.
 */
const DataImage &DataImage::operator=(const DataImage &ic)
{
	this->md5CRC = ic.md5CRC;
	this->rutaImg = ic.rutaImg;
	this->nombreImg = ic.nombreImg;
	this->codigoCampanha = ic.codigoCampanha;
	this->codigoMuestreo = ic.codigoMuestreo;
	this->codigoIndividuo = ic.codigoIndividuo;
	this->codigoImagen = ic.codigoImagen;
	this->calibracionImg = ic.calibracionImg;
	this->rutaXmlImg = ic.rutaXmlImg;
	this->nombreXml = ic.nombreXml;
	this->altoImg = ic.altoImg;
	this->anchoImg = ic.anchoImg;
	this->specieImage = ic.specieImage;
	this->nombreImgComp = ic.nombreImgComp;
	this->tipoImg = ic.tipoImg;
	this->diametroMaximo = ic.diametroMaximo;
	this->diametroMinimo = ic.diametroMinimo;

	return *this;
}
