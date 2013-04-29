/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * SftpConexion.h
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

#ifndef _SFTPCONEXION_H_
	#define _SFTPCONEXION_H_

	#include "Utiles.h"
	#include "Estructuras/ImageCells.h"
	#include "Interfaz/DialogoBarraProgres.h"
	#include "Config/OpcionesPref.h"
	#include <libssh2.h>
	#include <libssh2_sftp.h>
	#include "libssh2_config.h"
	 
	#ifdef WIN32
	#include <windows.h>
	#include <winsock2.h>
	#else
	#include <sys/socket.h>
	#include <netdb.h>
	#endif

	using namespace std;

	class SftpConexion
	{
		public:
			SftpConexion(OpcionesPref &opcP);
			~SftpConexion();
			static int waitsocket(int socket_fd, LIBSSH2_SESSION *session);
			bool subirFicheroServidor(const string &rutaXml, ImageCells &img);
		private:
			bool envioDeDatos(LIBSSH2_SESSION *session, int sock, LIBSSH2_SFTP *sftp_session, 
								int &rc, const string &pathXml, const string &nombreXml);
			void systemshutdownFTP(LIBSSH2_SESSION *session, int sock);
			//Atributos
			string pathSftp, urlSftp, userSftp, passSftp;
	};
#endif //_SFTPCONEXION_H_
  