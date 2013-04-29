/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * SistemaDibujado.cpp
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#include "SistemaDibujado.h"

/**
 Constructor.
 */
SistemaDibujado::SistemaDibujado()
{	
	zoomActual = 10;
	anchoRedimen = altoRedimen = 0;
	panelDibujo = NULL;
	imagenOvocitos = NULL;

	//Creamos el objeto de dibujado de las celulas
	capaCelula = new DibujadoCelula();
}

/**
 Destructor.
 */
SistemaDibujado::~SistemaDibujado()
{
	delete imagenOvocitos;
	delete panelDibujo;
	delete capaCelula;
	delete rejilla;
}

/**
 Devuelve el ancho de la imagen redimensionada.
 @return double.
 */
double SistemaDibujado::getAnchoRedimen()
{
	return anchoRedimen;
}

/**
 Devuelve el alto de la imagen redimensionada.
 @return double.
 */
double SistemaDibujado::getAltoRedimen()
{
	return altoRedimen;
}

/**
 Devuelve el valor del zoom actual.
 @return double.
 */
double SistemaDibujado::getZoom()
{
	return zoomActual;
}

/**
 Devuelve el objeto encargado del dibujado de las celulas.
 @return DibujadoCelula, puntero que contiene el objeto de dibujado de las celulas.
 */
DibujadoCelula *SistemaDibujado::getCapaCelula()
{
	return capaCelula;
}

/**
 Establece el objeto del panel de dibujado.
 @param pd, PanelDibujado.
 */
void SistemaDibujado::setPanelDibujado(PanelDibujado &pd)
{
	panelDibujo = &pd;
}

/**
 Establece el objeto de la rejilla.
 @param rej, Rejilla.
 */
void SistemaDibujado::setRejilla(Rejilla &rej)
{
	rejilla = &rej;
}

/**
 Establece el objeto que contiene la imagen actual.
 @param imagen, ImagenCells.
 */
void SistemaDibujado::setImagenOvocito(ImageCells &imagen)
{
	//Crea el pixbuf de la imagen
	imagenOvocitos = &imagen;
}

/**
 Devuelve el objeto de la imagen actual cargada en el sistema.
 @return ImageCells.
 */
ImageCells *SistemaDibujado::getImagenOvocito()
{
	return imagenOvocitos;
}

/**
 Carga las opciones generales de la aplicacion.
 @param opc, OpcionesPref contiene la configuracion de la aplicacion.
 */
void SistemaDibujado::cargaOpcionesDibujado(OpcionesPref &opc)
{	
	Gdk::Color celDescC, celSelecC, ediCelC, limISC, limDIC, colRejC;
		
	//Color celula desconocida
	celDescC.set_rgb(opc.getCelSDetR(), opc.getCelSDetG(), opc.getCelSDetB());
	//Color celula selecionada
	celSelecC.set_rgb(opc.getSeleCelR(), opc.getSeleCelG(), opc.getSeleCelB());
	//Color de edicion
	ediCelC.set_rgb(opc.getEdiCelR(), opc.getEdiCelG(), opc.getEdiCelB());
	//Color de limite izquierdo superior
	limISC.set_rgb(opc.getLimISR(), opc.getLimISG(), opc.getLimISB());
	//Color de limite derecho inferior
	limDIC.set_rgb(opc.getLimDIR(), opc.getLimDIG(), opc.getLimDIB());
	//Color de la rejilla
	colRejC.set_rgb(opc.getColRejR(), opc.getColRejG(), opc.getColRejB());
	
	//Capa de Celulas
	//Establecemos los colores en el pintado de borde
	capaCelula->setEdiCel(ediCelC);
	capaCelula->setSeleCel(celSelecC);
	capaCelula->setSinIdCel(celDescC);
	
	//Establecemos el ancho de la linea y del punto
	capaCelula->setGrosPunto((opc.getGrosPunto()/2));
	capaCelula->setGrosLinea((opc.getGrosLinea()/2));
	
	//Capa de rejilla
	//Establecemos los colores
	rejilla->setLimDI(limDIC);
	rejilla->setLimIS(limISC);
	rejilla->setColRej(colRejC);
	
	//Establecemos los grosores
	rejilla->setGrosRej((opc.getGrosRej()/2));
	rejilla->setSeparPun(opc.getSeparPuntos());
	rejilla->setGrosBordeRej((opc.getGrosBordeRej()/2));
}

/**
 Establece la imagen a tratar.
 */
void SistemaDibujado::setImagen()
{
	if(panelDibujo->getVerRejilla())
	{
		panelDibujo->destrucRejilla();
	}

	//Establecemos el zoom de las imagenes
	capaCelula->setZoomCelulas(10);

	//Estable el ancho y el alto de la imagen
	anchoRedimen = imagenOvocitos->getAnchoImg();
	altoRedimen = imagenOvocitos->getAltoImg();

	panelDibujo->setSizeImgRedimen(anchoRedimen, altoRedimen);

	//Pasamos el tamaño de la imagen a la rejilla
	rejilla->setAncho(anchoRedimen);
	rejilla->setAlto(altoRedimen);
	
	//Creamos la superficie de la capa de celulas
	repintadoImagen();

	//Forzamos la llamada al metodo de exposicion 
	panelDibujo->on_expose_event(NULL);
}

/**
 Establece el valor del zoom actual.
 @param zoom, int.
 */
void SistemaDibujado::setZoomActual(int zoom)
{
	zoomActual = zoom;
}

/**
 Repintado de la imagen.
 */
void SistemaDibujado::repintadoImagen()
{
	if(imagenOvocitos && imagenOvocitos->getAltoImg() != 0)
	{
		if(zoomActual == 10)
		{
			copiaPixbuf = imagenOvocitos->getImagenCelulas();
			panelDibujo->creaCapaImagen(copiaPixbuf,anchoRedimen,altoRedimen);
		}
		else
		{
			copiaPixbuf = imagenOvocitos->getImagenCelulas()->scale_simple(anchoRedimen,altoRedimen,
														 Gdk::INTERP_NEAREST);
			panelDibujo->creaCapaImagen(copiaPixbuf,anchoRedimen,altoRedimen);
		}
	}
}

/**
 Establece el zoom a tamanho completo de la pantalla.
 @ancho, float contiene el nuevo ancho.
 @alto, float contiene el nuevo alto.
 */
void SistemaDibujado::zoomImagenVentana(float ancho, float alto)
{
	double factor1, factor2;
	float altoImag, anchoImag;

	anchoImag = imagenOvocitos->getAnchoImg();
	altoImag = imagenOvocitos->getAltoImg();

	factor1 = alto/altoImag;
	factor2 = ancho/anchoImag;

	if(factor1 > factor2)
	{
		altoRedimen = altoImag * factor2;
		anchoRedimen = anchoImag * factor2;
		zoomActual = factor2 * 10;
	}
	else
	{
		anchoRedimen = anchoImag * factor1;
		altoRedimen = altoImag * factor1;
		zoomActual = factor1 * 10;
	}

	//Llamamos a la funcion de aplicacion del zoomActual
	aplicaOpcionesZoom();
}

/**
 Establece el zoom de la imagen.
 @param tamanhoImag, int contiene el tamaño del zoom de la imagen al que se va
 establecer.
 */
void SistemaDibujado::zoomImagen(int tamanhoImag)
{
	int altoImag, anchoImag;

	anchoImag = imagenOvocitos->getAnchoImg();
	altoImag =imagenOvocitos->getAltoImg();
	
	switch(tamanhoImag)
	{
		case 1:
			anchoRedimen = anchoImag * 0.1;
			altoRedimen = altoImag * 0.1;
			zoomActual = 1;
			break;
		case 2:
			anchoRedimen = anchoImag * 0.2;
			altoRedimen = altoImag * 0.2;
			zoomActual = 2;
			break;
		case 3:
			anchoRedimen = anchoImag * 0.3;
			altoRedimen = altoImag * 0.3;				
			zoomActual = 3;
			break;
		case 4:
			anchoRedimen = anchoImag * 0.4;
			altoRedimen = altoImag * 0.4;
			zoomActual = 4;
			break;
		case 5:
			anchoRedimen = anchoImag * 0.5;
			altoRedimen = altoImag * 0.5;
			zoomActual = 5;
			break;
		case 6:
			anchoRedimen = anchoImag * 0.6;
			altoRedimen = altoImag * 0.6;
			zoomActual = 6;
			break;
		case 7:
			anchoRedimen = anchoImag * 0.7;
			altoRedimen = altoImag * 0.7;
			zoomActual = 7;
			break;
		case 8:
			anchoRedimen = anchoImag * 0.8;
			altoRedimen = altoImag * 0.8;
			zoomActual = 8;
			break;
		case 9:
			anchoRedimen = anchoImag * 0.9;
			altoRedimen = altoImag * 0.9;
			zoomActual = 9;
			break;
		case 10:
			anchoRedimen = anchoImag;
			altoRedimen = altoImag;
			zoomActual = 10;
			break;
	}
	
	//Llamamos a la funcion de aplicacion del zoomActual
	aplicaOpcionesZoom();
}

/**
 Aplica el zoom a la imagen y recoloca la imagen.
 */
void SistemaDibujado::aplicaOpcionesZoom()
{
	//Establecemos el zoom de la capa de celulas
	capaCelula->setZoomCelulas(zoomActual);

	//Establecemos el zoom para la rejilla
	rejilla->setZoomRejilla(zoomActual);

	panelDibujo->setSizeImgRedimen(anchoRedimen, altoRedimen);
	
	//Repintamos la imagen
	repintadoImagen();
	
	//Repintamos el borde
	capaCelula->pintaBorde();
	
	if(panelDibujo->getVerRejilla())
	{
		panelDibujo->creaRejilla();
	}

	if(panelDibujo->getActivaDetecSupervis())
	{
		capaCelula->repintadoPuntosCelulas();
	}
}
