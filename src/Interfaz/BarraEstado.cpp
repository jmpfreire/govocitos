/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * BarraEstado.cpp
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


#include "BarraEstado.h"

/**
 Constructor
 */
BarraEstado::BarraEstado()
{	
	set_spacing(25);
	
	//Ancho de la barra de estado
	set_border_width(4);
	
	//Colocamos los textos a la derecha
	coord.set_alignment(Gtk::ALIGN_RIGHT,Gtk::ALIGN_CENTER);
	estadoCelula.set_alignment(Gtk::ALIGN_RIGHT,Gtk::ALIGN_CENTER);
	claseCelula.set_alignment(Gtk::ALIGN_RIGHT,Gtk::ALIGN_CENTER);
	nivelZoom.set_alignment(Gtk::ALIGN_RIGHT,Gtk::ALIGN_CENTER);
	resImagen.set_alignment(Gtk::ALIGN_RIGHT,Gtk::ALIGN_CENTER);
	
	//Añadimos los elementos de la barra de estado
	pack_start(p1, true, false);
	pack_start(coord, false, false);
	pack_start(claseCelula, false, false);
	pack_start(estadoCelula, false, false);
	pack_start(resImagen, false, false);
	pack_start(nivelZoom, false, false);
	pack_start(p2, false, false);
}

/**
 Destructor
 */
BarraEstado::~BarraEstado()
{
	
}

/**
 Establece la clase de la celula seleccionada.
 @param cl, clase de la celula.
 */
void BarraEstado::setClaseCell(const string &cl)
{
	claseCelula.set_label("Class: " + cl);
	//claseCelula.set_label("Clase: " + cl);
}

/**
 Establece el estado de la celula seleccionada.
 @param est, estado de la celula.
 */
void BarraEstado::setEstadoCell(const string &est)
{
	//estadoCelula.set_label("Estado: " + est);
	estadoCelula.set_label("State: " + est);
}

/**
 Establece el nivel de zoom en la barra de estado.
 @param zoom, zoom actual de la imagen.
 */
void BarraEstado::setNivelZoom(float zoom)
{
	string zoomStatus, nivZoom;
	
	zoomStatus = Utiles::converString(zoom * 10);
	
	//nivZoom = "Zoom Actual: " + zoomStatus.substr(0,5) + "%";
	nivZoom = "Current zoom: " + zoomStatus.substr(0,5) + "%";
	nivelZoom.set_label(nivZoom);
}

/**
 Establece la resolucion de la imagen.
 @param ancho, ancho de la imagen.
 @param alto, alto de la imagen.
 */
void BarraEstado::setResolucionImagen(int ancho, int alto)
{
	string resImag;
	
	//resImag = "Resolucion: " + Utiles::converString(ancho) + "x" + Utiles::converString(alto) + " pixels";
	resImag = "Resolution: " + Utiles::converString(ancho) + "x" + Utiles::converString(alto) + " pixels";
	resImagen.set_label(resImag);
}

/**
 Borra las coordenadas del raton.
 */
void BarraEstado::setCoordenadasACero()
{
	coord.set_label("");
}

/**
 Establece las coordenadas del raton.
 @param x, coordenada x del raton.
 @para y, coordenada y del raton.
 */
void BarraEstado::setCoordenadas(int x, int y)
{
	string coordenadas;

	if(x >= 0 && y >= 0)
	{
		coordenadas = "X: " + Utiles::converString(x) + " Y: " + Utiles::converString(y);	
	}
	else
	{
		coordenadas = "";
	}
	coord.set_label(coordenadas);
}

/**
 Establece todos los atributos en blanco.
 */
void BarraEstado::setTodosEnBlanco()
{
	claseCelula.set_label("");
	estadoCelula.set_label("");
	nivelZoom.set_label("");
	resImagen.set_label("");
}
