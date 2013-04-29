/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ModulosGovocitos.cpp
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
 
#include "ModulosGovocitos.h"

/**
 Constructor
 */
ModulosGovocitos::ModulosGovocitos()
{
	//Creamos el objeto de configuracion
	confGovocitos = new ConfigGovocitos();

	//Creamos el objeto de Celulas
	listaCells = new ListadoCelulas();
	
	//Creamos el objeto de imagenes
	listaImag = new ListadoImagenes();

	//Creamos el objeto de conexion
	conexionHttp = NULL;
	setNuevosDatosConexion();

	//Creamos el contenedor de la imagen
	imagenCelulas = new ImageCells();

	//Creamos las pilas de deshacer y rehacer
	deshacer = new DesReHacer();
	rehacer = new DesReHacer();

	//Creamos el panel de dibujado
	paintSystem = new SistemaDibujado();
	//Creamos la rejilla
	rejilla = new Rejilla();

	//Cargamos opciones de dibujado y rejilla
	paintSystem->setRejilla(*rejilla);
	paintSystem->cargaOpcionesDibujado(*confGovocitos->getDatosPreferencias());

	//Creamos la lista de la cache
	listaCache = new ListadoCache(confGovocitos->getDatosPreferencias()->getTamCache(),
	                              *confGovocitos->getDatosCache());

	//Creamos el objeto para el calculo de fecundidad
	cFecundidad = new CalculoFecundidad();

	//Creamos el objeto que contiene las imagenes del individuo
	listIndividuo = new ListadoIndividuo();

	//Creamos el objeto de resultados de fecundidad
	listResultados = new ResultFecundidad();

	//Creamos el objeto para la deteccion de bordes
	detecAutomatica = new DeteccionAut();

	//Creamos el objeto para la conexion del ftp
	conexionSftp = new SftpConexion(*confGovocitos->getDatosPreferencias());

	//Creamos el objeto para la consulta de la BD
	consultBD = new ConexionBD(*confGovocitos->getDatosPreferencias());
}

/**
 Destructor.
 */
ModulosGovocitos::~ModulosGovocitos()
{
	delete confGovocitos;
	delete listaCells;
    delete listaImag;
    delete imagenCelulas;
    delete deshacer;
    delete rehacer;
    delete paintSystem;
    delete rejilla;
    delete listaCache;
    delete cFecundidad;
    delete listIndividuo;
	delete conexionSftp;
	delete consultBD;
}

/**
 Devuelve la configuración del sistema.
 @return ConfigGovocitos, puntero que contiene la configuración.
 */
ConfigGovocitos *ModulosGovocitos::getConfiguracion()
{
	return confGovocitos;
}

/**
 Devuelve el listado de celulas.
 @return ListadoCelulas, puntero que contiene los datos de las células.
 */
ListadoCelulas *ModulosGovocitos::getListaCelulas()
{
	return listaCells;
}

/**
 Devuelve el listado de Imagenes.
 @return ListadoImagenes, puntero que contiene los datos de las imagenes.
 */
ListadoImagenes *ModulosGovocitos::getListaImagenes()
{
	return listaImag;
}

/**
 Devuelve el objeto para la conexion https.
 @return HttpsConexion, puntero que contiene los datos de conexion https.
 */
HttpsConexion *ModulosGovocitos::getConexionBD()
{
	return conexionHttp;
}

/**
 Devuelve el objeto de la imagen actual cargada en el sistema.
 @return ImageCells, puntero que contiene los datos de la imagen actual.
 */
ImageCells *ModulosGovocitos::getImageActual()
{
	return imagenCelulas;
}

/**
 Devuelve el objeto de la pila deshacer que contiene los diferentes estados del
 dibujado y clasificacion de las celulas.
 @return DesRehacer, puntero contiene la pila deshacer.
 */
DesReHacer *ModulosGovocitos::getDeshacer()
{
	return deshacer;
}

/**
 Devuelve el objeto de la pila rehacer que contiene los diferentes estados del
 dibujado y clasificacion de las celulas.
 @return DesRehacer, puntero contiene la pila rehacer.
 */
DesReHacer *ModulosGovocitos::getRehacer()
{
	return rehacer;
}

/**
 Devuelve el objeto que contiene el sistema de dibujado y sus caracteristicas.
 @return SistemaDibujado, puntero del objeto dibujado.
 */
SistemaDibujado *ModulosGovocitos::getSistemaDibujado()
{
	return paintSystem;
}

/**
 Devuelve el objeto que contiene el listado de imagenes almacenadas en la cache.
 @return ListadoCache, puntero que contiene una lista con las imagenes de la cache.
 */
ListadoCache *ModulosGovocitos::getListadoCache()
{
	return listaCache;
}

/**
 Devuelve el objeto que contiene la rejilla.
 @return Rejilla, puntero del objeto de la rejilla.
 */
Rejilla *ModulosGovocitos::getRejilla()
{
	return rejilla;
}

/**
 Devuelve el objeto que se utliza para realizar el calculo de fecundidad.
 @return CalculoFecundidad, puntero que contiene los datos para realizar el calculo 
 de fecundidad.
 */
CalculoFecundidad *ModulosGovocitos::getCalculoFecundidad()
{
	return cFecundidad;
}

/**
 Devuelve un objeto que contiene el listado de individuos.
 @return ListadoIndividuo, puntero que contiene el listado de individuos.
 */
ListadoIndividuo *ModulosGovocitos::getListadoIndividuo()
{
	return listIndividuo;
}

/**
 Devuelve un objeto que contiene los resultados de fecundidad.
 @return ResultFecundidad, puntero que contiene los resultados del calculo de 
 fecundidad.
 */
ResultFecundidad *ModulosGovocitos::getListaResultadosImg()
{
	return listResultados;
}

/**
 Devuelve el objeto necesario para realizar la detección automatica de bordes.
 @return DeteccionAut, puntero que contiene al objeto encargado de la deteccion 
 de bordes automatica.
 */
DeteccionAut *ModulosGovocitos::getDeteccionAut()
{
	return detecAutomatica;
}

/**
 Devuelve el objeto que contiene los parametros de configuración de la conexion
 sftp.
 @return SftpConexion, puntero que contiene los datos de la conexion sftp.
 */
SftpConexion *ModulosGovocitos::getConexionSftp()
{
	return conexionSftp;
}

/**
 Devuelve el objeto que contiene los parametros de configuracion de la conexion
 con la base de datos del servidro.
 @return ConexionBD, puntero que contiene los datos de la conexion a la base de
 datos.
 */
ConexionBD *ModulosGovocitos::getConexionMySql()
{
	return consultBD;
}

/**
 Establece una nueva lista de imagenes.
 */
void ModulosGovocitos::setNuevaListaImagenes()
{
	if(listaImag)
	{
		delete listaImag;
	}
	
	listaImag = new ListadoImagenes();
}

/**
 Establece unos nuevos datos de conexion https.
 */
void ModulosGovocitos::setNuevosDatosConexion()
{
	if(conexionHttp)
	{
		delete conexionHttp;
	}
	
	conexionHttp = new HttpsConexion(*confGovocitos->getDatosPreferencias());
}

/**
 Establece una nueva lista de celulas.
 */
void ModulosGovocitos::setNuevasCelulas()
{
	if(listaCells)
	{
		delete listaCells;
	}

	listaCells = new ListadoCelulas();
}

/**
 Establece una nueva imagen.
 */
void ModulosGovocitos::setNuevaImagen()
{
	if(imagenCelulas)
	{
		delete imagenCelulas;
	}

	imagenCelulas = new ImageCells();
}

/**
 Establece una nueva pila de deshacer.
 */
void ModulosGovocitos::setNuevaPilaDeshacer()
{
	if(deshacer)
	{
		delete deshacer;
	}

	deshacer = new DesReHacer();
}

/**
 Establece una nueva pila de reahacer.
 */
void ModulosGovocitos::setNuevaPilaRehacer()
{
	if(rehacer)
	{
		delete rehacer;
	}

	rehacer = new DesReHacer();
}

/**
 Establece una nueva rejilla.
 */
void ModulosGovocitos::setNuevaRejilla()
{
	if(rejilla)
	{
		delete rejilla;
	}

	rejilla = new Rejilla();
}

/**
 Establece un nuevo calculo de fecundidad.
 */
void ModulosGovocitos::setNuevoCalculoFecundidad()
{
	if(cFecundidad)
	{
		delete cFecundidad;
	}

	cFecundidad = new CalculoFecundidad();
}

/**
 Establece un nuevo listado de individuos.
 */
void ModulosGovocitos::setNuevoListadoIndividuo()
{
	if(listIndividuo)
	{
		delete listIndividuo;
	}

	listIndividuo = new ListadoIndividuo();
}

/**
 Establece un nuevo listado de resultados del calculo de fecundidad.
 */
void ModulosGovocitos::setNuevoListaResultadosImg()
{
	if(listResultados)
	{
		delete listResultados;
	}

	listResultados = new ResultFecundidad();
}

/**
 Establece un nuevo sistema de deteccion de bordes automatico.
 */
void ModulosGovocitos::setNuevoDeteccionAut()
{
	if(detecAutomatica)
	{
		delete detecAutomatica;
	}

	detecAutomatica = new DeteccionAut();
}

/**
 Establece los nuevos datos del sftp para la subida de ficheros.
 */
void ModulosGovocitos::setNuevoConexionSftp()
{
	if(conexionSftp)
	{
		delete conexionSftp;
	}

	conexionSftp = new SftpConexion(*confGovocitos->getDatosPreferencias());
}

/**
 Establece los nuevos datos de conexion a la base de datos.
 */
void ModulosGovocitos::setNuevoConexionMySql()
{
	if(consultBD)
	{
		delete consultBD;
	}

	consultBD = new ConexionBD(*confGovocitos->getDatosPreferencias());
}
