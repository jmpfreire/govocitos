/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * HttpsConexion.h
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

#ifndef _HTTPSCONEXION_H_
	#define _HTTPSCONEXION_H_

	#include <iostream>
	#include <stdio.h>
	#include <curl/curl.h> 
	#include "Utiles.h"
	#include "Interfaz/DialogoBarraProgres.h"
	#include "Fichero.h"
	#include "Estructuras/ImageCells.h"

	/*-------------Importante-------------------
	Para la compilacion en windows de libcurl hay que añadir lo siguiente
	fichero fileinfo.h de la libreria gtk #undef FILE_TYPE_UNKNOWN 
	fichero error.h de la libreria gtk #undef HOST_NOT_FOUND
	-------------------------------------------*/
	using namespace std;

	class HttpsConexion
	{
		public:
			HttpsConexion(OpcionesPref &opcP);
			~HttpsConexion();
			bool obtenerDatosServidor(const string &ficheroXml);
			bool descargaImagen(DataImage *imagDescarga);
			bool descargaFicheroXml(DataImage *imagDescarga);
			bool descargaFicheroXml(ImageCells *imagDescarga);
			bool descargaImagen(ImageCells *imagDescarga);
			friend int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
		private:
			bool detectarErrorCode(CURL *curl, const string &ruta);
			//urlPagina direccion de la pagina principal
			string urlPagina ,username, password;
	};

#endif // _HTTPSCONEXION_H_
