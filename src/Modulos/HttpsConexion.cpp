/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * HttpsConexion.cpp
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

#include "HttpsConexion.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 Funcion que analiza la cantidad descargada o subida actualmente y la 
 actualiza en el dialogo de progreso.
 @param *clientp, puntero void.
 @param dltotal, double que contiene el tamaño total de la descarga.
 @param dlnow, double que contiene el tamaño actual descargado.
 @param ultotal, double que contiene el tamaño total de la subida.
 @param ulnow, double que contiene el tamaño actual subido.
 */
int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	static DialogoBarraProgres *dProgres = NULL;
	double porcentajeDesc, finalizaDesc;
	
	finalizaDesc = (dltotal - dlnow);
	
	if(!dProgres)
	{
		//dProgres = new DialogoBarraProgres("Descarga Imagen");
		dProgres = new DialogoBarraProgres("Download Image");
	}
	else if(dProgres && dProgres->getCancelaProgreso() && finalizaDesc == 0.0)
	{
		delete dProgres;
		//dProgres = new DialogoBarraProgres("Descarga Imagen");
		dProgres = new DialogoBarraProgres("Download Image");
	}
	
	if(finalizaDesc >= 0.0)
	{
		if(dProgres->getCancelaProgreso())
		{
			dProgres->cierraVentanaProgreso();
			return -1;
		}
		else
		{
			//Ejecutamos la ventana de progreso de descarga y la actualizamos
			dProgres->ejectuaDialogoProgreso();
			Utiles::actualizarInterfaz();
			
			porcentajeDesc = (dlnow/dltotal);

			if(porcentajeDesc >= 0.0)
			{
				dProgres->setEstadoBarraProgreso(porcentajeDesc);
				dProgres->setPercentText(porcentajeDesc);
			}

			if(finalizaDesc == 0.0)
			{
				dProgres->cierraVentanaProgreso();
				return 0;
			}
		}
	}
	return 0;
}

/**
 Funcion de escritura de datos del fichero que se esta descargando.
 @param *ptr, puntero de tipo void.
 @param size, dato de tipo size_t. (tamaño total del fichero).
 @param nmemb, dato de tipo size_t. (tamaño del stream).
 @param *stream, puntero de tipo void. (stream a almacenar en el fichero).
 */
size_t writeFunction( void *ptr, size_t size, size_t nmemb, void *stream)
{
	fwrite(ptr, size, nmemb, (FILE *)stream);
    return nmemb*size;
} 

/**
 Constructor.
 @param urlP, string que contiene la URL de la pagina del servidor.
 @param user, string que contiene el nombre de usuario.
 @param pass, string que contiene la contraseña.
 */
HttpsConexion::HttpsConexion(OpcionesPref &opcP)
{
	size_t found;
	string path;

	path = opcP.getPathSFTP();
			
	found = path.find_last_of("/\\");
	path = path.substr(found+1);

	urlPagina = opcP.getDirecBD();
	urlPagina = urlPagina + ":8080/" + path;
	username = "";//@deprecated
	password = "";//@deprecated
}

/**
 Destructor.
 */
HttpsConexion::~HttpsConexion()
{


}

/**
 Descarga los ficheros xml con los datos que se quieren segun el tipo de fichero
 xml se obtenadran unos datos u otros.
 @param ficheroXml, string que contiene el nombre del fichero xml.
 */
bool HttpsConexion::obtenerDatosServidor(const string &ficheroXml)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile(0);
	string urlFinal;
	
	curl = curl_easy_init();

	//Comprobamos el tipo de conexion a realizar
	urlFinal = urlPagina + "/govocitos/govocitosService.jsp?user=" + username + 
		"&pass=" + password;
	
	if(ficheroXml == "XmlConectividad.xml")
	{
		urlFinal = urlFinal + "&option=connectivity";
	}
	else if(ficheroXml == "XmlClasesEstados.xml")
	{
		urlFinal = urlFinal + "&option=preferencias";
	}
	else if(ficheroXml == "XmlImagenesWeb.xml")
	{
		urlFinal = urlFinal + "&option=image";
	}
	else if(ficheroXml == "XmlFecundidadWeb.xml")
	{
		urlFinal = urlFinal + "&option=fecundity";
	}
	else
	{
		goto ErrorFind;
	}

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, urlFinal.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR,1);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000);

		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	  	
		destFile = fopen(Utiles::direccionConfig(ficheroXml).c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);
		
		if(res)
		{
			goto ErrorFind;
		}
		
		fclose(destFile);
		curl_easy_cleanup(curl);
		
		return true;
	}
	
ErrorFind:
	if (destFile)
	{
		fclose(destFile);
	}
	curl_easy_cleanup(curl);
	return false;
}

/**
 Descarga una imagen del servidor que contiene las imagenes con celulas.
 @param *imagDescarga, Puntero a DataImage que contiene los datos de la imagen.
 @return bool, verdadero si la descarga es correcta, falso en caso contrario.
 */
bool HttpsConexion::descargaImagen(DataImage *imagDescarga)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile(0);
	string urlFinal, pathsistema;

	//Comprobamos el tipo de conexion a realizar
	urlFinal = urlPagina + "/" + imagDescarga->getRutaImg() + "/" + imagDescarga->getNombreImgCompleto();

	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, urlFinal.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR,1);
		
		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			
		//Almacenando en la cache
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		pathsistema = Utiles::direccionCache(imagDescarga->getNombreImgCompleto());
		destFile = fopen(pathsistema.c_str(),"wb");
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &progress_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res || detectarErrorCode(curl,urlFinal.c_str()))
		{
			if(res == CURLE_ABORTED_BY_CALLBACK)
			{
				Fichero::borraImagenSistema(pathsistema);
			}

			goto ErrorFind;
		}
			
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);

		return true;
	}
	
ErrorFind:
	if (destFile)
	{
		fclose(destFile);
	}
	curl_easy_cleanup(curl);
	return false;	
}

/**
 Descarga un fichero xml del servidor que contiene las imagenes con celulas.
 @param *imagDescarga, Puntero a DataImage que contiene los datos de las celulas.
 @return bool, verdadero si la descarga es correcta, falso en caso contrario.
 */
bool HttpsConexion::descargaFicheroXml(DataImage *imagDescarga)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile(0);
	string urlFinal, pathsistema;

	//Comprobamos el tipo de conexion a realizar
	urlFinal = urlPagina + "/" + imagDescarga->getRutaXmlImg() + "/" + imagDescarga->getNombreXml();
	
	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, urlFinal.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		
		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		
		pathsistema = Utiles::direccionCache(imagDescarga->getNombreXml());
		destFile = fopen(pathsistema.c_str(),"wb");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res || detectarErrorCode(curl,urlFinal.c_str()))
		{
			goto ErrorFind;
		}
		
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);

		return true;
	}
	
ErrorFind:
	if (destFile)
	{
		fclose(destFile);
	}
	curl_easy_cleanup(curl);
	return false;
}

/**
 Descarga un fichero xml del servidor que contiene las imagenes con celulas.
 @param *imagDescarga, Puntero a ImageCells que contiene los datos de las celulas.
 @return bool, verdadero si la descarga es correcta, falso en caso contrario.
 */
bool HttpsConexion::descargaFicheroXml(ImageCells *imagDescarga)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile(0);
	string urlFinal, pathsistema;

	//Comprobamos el tipo de conexion a realizar
	urlFinal = urlPagina + "/" + imagDescarga->getRutaXmlImg() + "/" + imagDescarga->getNombreXml();
	
	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, urlFinal.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		
		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		
		pathsistema = Utiles::direccionCache(imagDescarga->getNombreXml());
		destFile = fopen(pathsistema.c_str(),"wb");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res || detectarErrorCode(curl,urlFinal.c_str()))
		{
			goto ErrorFind;
		}
			
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);

		return true;
	}
	
ErrorFind:
	if (destFile)
	{
		fclose(destFile);
	}
	curl_easy_cleanup(curl);
	return false;
}

/**
 Descarga una imagen del servidor que contiene las imagenes con celulas.
 @param *imagDescarga, Puntero a ImageCells que contiene los datos de la imagen.
 @return bool, verdadero si la descarga es correcta, falso en caso contrario.
 */
bool HttpsConexion::descargaImagen(ImageCells *imagDescarga)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile(0);
	string urlFinal, pathsistema;

	//Comprobamos el tipo de conexion a realizar
	urlFinal = urlPagina + "/" + imagDescarga->getRutaImg() + "/reduced/" + imagDescarga->getNombreImgCompleto();

	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, urlFinal.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR,1);
		
		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			
		//Almacenando en la cache
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		pathsistema = Utiles::direccionCacheReduced(imagDescarga->getNombreImg());
		destFile = fopen(pathsistema.c_str(),"wb");
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &progress_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res || detectarErrorCode(curl,urlFinal.c_str()))
		{
			if(res == CURLE_ABORTED_BY_CALLBACK)
			{
				Fichero::borraImagenSistema(pathsistema);
			}

			goto ErrorFind;
		}
			
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);

		return true;
	}

ErrorFind:
	if (destFile)
	{
		fclose(destFile);
	}
	curl_easy_cleanup(curl);
	return false;
}

/**
 Detecta un error producido en la conexion https.
 @param curl, puntero de tipo CURL que contiene el contexto de la conexion.
 @param ruta, string que contiene la ruta de conexion.
 @return bool, true si la conexión se puede realizar con exito y false en caso 
 contrario.
 */
bool HttpsConexion::detectarErrorCode(CURL *curl, const string &ruta)
{
	CURLcode res;

	res = curl_easy_getinfo(curl, CURLINFO_HTTP_CONNECTCODE, ruta.c_str());

	if(!res)
	{
		return false;
	}

	return true;
}
