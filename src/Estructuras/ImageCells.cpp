/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ImageCells.cpp
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

#include "ImageCells.h"

/**
 Constructor.
 */
ImageCells::ImageCells()
{
	pathIntermedios.clear();
	nombrePathIntermedios.clear();
}

/**
 Destructor.
 */
ImageCells::~ImageCells()
{

}

/**
 Constructor de copias.
 @param &ic, referencia a ImageCells.
 */
ImageCells::ImageCells(const ImageCells &ic) : DataImage(ic)
{
	imagenCelulas = ic.imagenCelulas;
	pathIntermedios = ic.pathIntermedios;
	nombrePathIntermedios = ic.nombrePathIntermedios;
}

/**
 */
void ImageCells::addXmlTest(const string &rutaXml)
{
	pathIntermedios.push_back(rutaXml);
}

/**
 */
void ImageCells::addNombreXmlTest(const string &nombreXml)
{
	nombrePathIntermedios.push_back(nombreXml);
}

void ImageCells::vaciaXmlTest()
{
	pathIntermedios.clear();
}

void ImageCells::vaciaNombreXmlTest()
{
	nombrePathIntermedios.clear();
}

/**
 */
vector<string> ImageCells::getXmlTest()
{
	return pathIntermedios;
}

/**
 */
vector<string> ImageCells::getNombreXmlTest()
{
	return nombrePathIntermedios;
}

/**
 Carga una imagen en el sistema y establece los atributos de la misma.
 @param condicion, bool por defecto es true, en caso de ser falso no se calcula 
 el md5.
 @return bool, falso si el md5 no coincide, verdadero en caso contrario.
 */
bool ImageCells::cargaImagenEnSistema(bool condicion)
{
	if(condicion)
	{
		string auxMd5;
		//Calculamos el md5
		FILE *fichero;

		fichero = fopen(rutaImg.c_str(), "rb");
	
		auxMd5 = calculoMD5Imagen(fichero);
		fclose(fichero);
	
		if(DataImage::md5CRC == auxMd5 || DataImage::md5CRC == "")
		{
			DataImage::md5CRC = auxMd5;
		}
		else
		{
			Fichero::borraImagenSistema(rutaImg);
			return false;
		}
	}
	
	//Crea el pixbuf de la imagen
	imagenCelulas = Gdk::Pixbuf::create_from_file(rutaImg);
	
	//Estable el ancho y el alto de la imagen
	DataImage::anchoImg = imagenCelulas->get_width();
	DataImage::altoImg = imagenCelulas->get_height();

	//Establecemos nombre, tipo y ruta
	DataImage::rutaImg = rutaImg;

	return true;
}

/**
 Carga una imagen reducida en el sistema, es utilizada especialmente para cuando
 se calcula la fecundidad de un individuo.
 */
void ImageCells::cargaImagenReducida()
{
	int ancho, alto;
	
	//Crea el pixbuf de la imagen
	imagenCelulas = Gdk::Pixbuf::create_from_file(rutaImg);

	ancho = imagenCelulas->get_width();
	alto = imagenCelulas->get_height();

	imagenCelulas = imagenCelulas->scale_simple((ancho * 0.4), (alto * 0.4), Gdk::INTERP_NEAREST);

}

/**
 Calcula el crc de la imagen con el algoritmo md5.
 @param fich, FILE flujo de datos que contiene la imagen.
 @return string, devuelve un string con el md5 de la imagen.
 */
string ImageCells::calculoMD5Imagen(FILE* fich)
{
	gsize tamImagen;
	long lSize;
	guchar *buffer;
	string result;

	//obtenemos el tamaño del fichero
	fseek(fich, 0 , SEEK_END);
	lSize = ftell (fich);
	rewind(fich);

	//Redimensionamos la memoria para guardar todo la informacion
	buffer = (guchar*) malloc (sizeof(guchar)*lSize);

	//Copiamos el fichero en un buffer
	tamImagen = fread (buffer, 1, lSize, fich);

	result = Glib::Checksum::compute_checksum(Glib::Checksum::CHECKSUM_MD5, buffer, tamImagen);
	free(buffer);
	
	return result;
}

/**
 Devuelve la referencia del puntero de la imagen almacenada en el sistema.
 @return Glib::RefPtr de la imagen actual.
 */
Glib::RefPtr<Gdk::Pixbuf> ImageCells::getImagenCelulas()
{
	return imagenCelulas;
}

/**
 Sobrecarga del operador igual.
 @param ic, objeto ImageCells.
 @return ImageCells, resultado de la operacion de asignacion.
 */
const ImageCells &ImageCells::operator=(const ImageCells &ic)
{
	DataImage::operator=(ic);
	this->imagenCelulas = ic.imagenCelulas;
	this->pathIntermedios = ic.pathIntermedios;
	this->nombrePathIntermedios = ic.nombrePathIntermedios;

	return *this;
}
