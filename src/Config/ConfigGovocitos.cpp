/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConfigGovocitos.cpp
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

#include "ConfigGovocitos.h"

/**
 Constructor.
 */
ConfigGovocitos::ConfigGovocitos()
{		
	//Crea el directorio de configuracion
	crearDirectorios();

	//Cargar el archivo de configuracion de la aplicacion
	leerFicherosConf();
	
	//Carga el fichero de la cache de imagenes
	leerFicheroCache();
}

/**
 Destructor.
 */
ConfigGovocitos::~ConfigGovocitos()
{
	
}

/**
 Devuelve un puntero al vector de OpcionesRej que contiene los datos de la rejilla.
 @return vector<OpcionesRej> *, puntero al objeto datosRejilla.
 */
vector<OpcionesRej> *ConfigGovocitos::getDatosRejilla()
{
	return &datosRejilla;
}

/**
 Devuelve un puntero al vector ClaseCeula que contiene las clases de las celulas.
 @return vector<ClaseCelula> *, puntero al objeto datosClases.
 */
vector<ClaseCelula> *ConfigGovocitos::getDatosClases()
{
	return &datosClases;
}

/**
 Devuelve un puntero al vector EstadoCeula que contiene los estados de las celulas.
 @return vector<EstadoCelula> *, puntero al objeto datosEstados.
 */
vector<EstadoCelula> *ConfigGovocitos::getDatosEstados()
{
	return &datosEstados;
}

/**
 Devuelve un puntero del objeto OpcionesPref que contiene los datos de las preferencias
 del programa.
 @return OpcionesPref *, puntero al objeto datosPreferencias.
 */
OpcionesPref *ConfigGovocitos::getDatosPreferencias()
{
	return &datosPreferencias;
}

/**
 Devuelve un puntero de la lista de la cache que contiene la cache de imagenes
 almacenadas en el sistema.
 @return list<string> *, puntero al objeto listaCache.
 */
list<string> *ConfigGovocitos::getDatosCache()
{
	return &listaCache;
}

/**
 Establece los datos de la rejilla sustituyendo todos los que ya se tenian.
 @param opr, vector<OpcionesRej> que contiene todas las rejillas almacenadas en 
 el sistema.
 */
void ConfigGovocitos::setDatosRejilla(vector<OpcionesRej> opr)
{
	datosRejilla.clear();

	datosRejilla = opr;
}

/**
 Establece los datos de las clases que estaban almacenadas en el sistema por los 
 nuevos.
 @param clc, vector<ClaseCelula> que contiene todas las clases almacenadas en el
 sistema.
 */
void ConfigGovocitos::setDatosClases(vector<ClaseCelula> clc)
{
	datosClases.clear();

	datosClases = clc;
}

/**
 Establece los datos de los estados que estaban almacenadas en el sistema por los 
 nuevos.
 @param esc, vector<EstadoCelula> que contiene todas los estados almacenados en el
 sistema. 
 */
void ConfigGovocitos::setDatosEstados(vector<EstadoCelula> esc)
{
	datosEstados.clear();

	datosEstados = esc;
}

/**
 Establece los datos de las preferencias del programa.
 @param opc, objeto de OpcionesPref que contiene las preferencias del programa.
 */
void ConfigGovocitos::setDatosPreferencias(OpcionesPref opc)
{
	datosPreferencias = opc;
}

/**
 Guarda los cambios realizados en la cache (contenidos en el objeto de la cache)
 en un fichero para hacer permanente estos cambios.
 */
void ConfigGovocitos::escribirFicheroCache()
{
	Fichero::escribXmlCache(Utiles::direccionConfig("cacheImagenes.xml"), *this);
}

/**
 Lee el fichero que contiene la cache del programa principal y lo carga en el objeto
 de la cache.
 */
void ConfigGovocitos::leerFicheroCache()
{
	Fichero::leerXmlCache(Utiles::direccionConfig("cacheImagenes.xml"), *this);
}
                                        
/**
 Guarda los cambios realizados en la configuracion, clases, estados y rejilla en sus
 ficheros correspondientes para hacer estos cambios permanentes.
 */
void ConfigGovocitos::escribirFicherosConf()
{
	//Configuracion general
//	Fichero::escribFichConfig(Utiles::direccionConfig("configuracion2.dat"), datosPreferencias);
	//Clases
//	Fichero::escribFichClases(Utiles::direccionConfig("clases1.dat"), datosClases);
	//Estados
//	Fichero::escribFichEstados(Utiles::direccionConfig("estados1.dat"), datosEstados);
	//Rejillas personalizadas
//	Fichero::escribFichOpcionesRej(Utiles::direccionConfig("opcionesRejilla3.dat"), datosRejilla);

	//Fichero::escribXmlPreferencias("/home/kote/Desktop/prueba.xml", *this);
	Fichero::escribXmlPreferencias(Utiles::direccionConfig("preferenciasGovocitos.xml"), *this);
}

/**
 Lee los ficheros de configuracion, clases, estados y rejilla para carga los datos en los
 correspondientes ficheros de configuracion del sistema.
 */
void ConfigGovocitos::leerFicherosConf()
{
	//Configuracion general
//	Fichero::leerFichConfig(Utiles::direccionConfig("configuracion2.dat"), datosPreferencias);
	//Rejillas personalizadas
//	Fichero::leerFichOpcionesRej(Utiles::direccionConfig("opcionesRejilla3.dat"), datosRejilla);
	//Clases
//	Fichero::leerFichClases(Utiles::direccionConfig("clases1.dat"), datosClases);
	//Estados
//	Fichero::leerFichEstados(Utiles::direccionConfig("estados1.dat"), datosEstados);

//	Fichero::leerXmlPreferencias("/home/kote/Desktop/prueba.xml", *this);
	Fichero::leerXmlPreferencias(Utiles::direccionConfig("preferenciasGovocitos.xml"), *this);
}

/**
 Crea los directorios necesarios para almacenar los ficheros de configuracion,
 cache e imagenes reducidas.
 */
void ConfigGovocitos::crearDirectorios()
{
	Utiles::creaDirectorio(Utiles::obtenerDireccionConfig());
	Utiles::creaDirectorio(Utiles::obtenerDireccionCache());
	Utiles::creaDirectorio(Utiles::obtenerDireccionCacheImgReduced());
}
