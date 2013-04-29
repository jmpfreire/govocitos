/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * SftpConexion.cpp
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

#include "SftpConexion.h"

/**
 Constructor.
 @param opcP, referencia a OpcionesPref.
 */
SftpConexion::SftpConexion(OpcionesPref &opcP)
{
	userSftp = opcP.getLoginSFTP();
	passSftp = opcP.getPassSFTP();
	urlSftp = opcP.getDirecSFTP();
	pathSftp = opcP.getPathSFTP();
}

/**
 Destructor.
 */
SftpConexion::~SftpConexion()
{

}

/**
 Espera un socket para la conexon.
 @param socket_fd, int.
 @param session, puntero LIBSS2_SESSION.
 @return int.
 */
int SftpConexion::waitsocket(int socket_fd, LIBSSH2_SESSION *session)
{
    struct timeval timeout;
    int rc;
    fd_set fd;
    fd_set *writefd = NULL;
    fd_set *readfd = NULL;
    int dir;
 
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
 
    FD_ZERO(&fd);
 
    FD_SET(socket_fd, &fd);
 
    /* now make sure we wait in the correct direction */ 
    dir = libssh2_session_block_directions(session);

 
    if(dir & LIBSSH2_SESSION_BLOCK_INBOUND)
        readfd = &fd;
 
    if(dir & LIBSSH2_SESSION_BLOCK_OUTBOUND)
        writefd = &fd;
 
    rc = select(socket_fd + 1, readfd, writefd, NULL, &timeout);
 
    return rc;
}

/**
 Sube un fichero a la base de datos.
 @param urlXml, string que contiene la url del servidor ftp.
 @param pathXml, string que contiene el path del fichero de células.
 @return bool, true si se sube el fichero con exito, false en caso contrario.
 */
bool SftpConexion::subirFicheroServidor(const string &rutaXml, ImageCells &img)
{
	struct hostent * hostent;
    int sock, auth_pw = 1;
    struct sockaddr_in sin;
    LIBSSH2_SESSION *session;
    int rc;
    
    LIBSSH2_SFTP *sftp_session;
    
	//Ejecutamos la ventana de progreso de descarga y la actualizamos
    DialogoBarraProgres dProgres("Upload Files");
	dProgres.setEstadoBarraProgreso(0.1);
	dProgres.setPercentText(0.1);
	dProgres.ejectuaDialogoProgreso();
	Utiles::actualizarInterfaz();
	
#ifdef WIN32
    WSADATA wsadata;
 
    WSAStartup(MAKEWORD(2,0), &wsadata);
#endif

	//Completamos la ruta del xml
	pathSftp = pathSftp + "/" + rutaXml;
	
	hostent = gethostbyname(urlSftp.c_str());
	
	rc = libssh2_init (0);

    if (rc != 0) 
	{
        fprintf (stderr, "libssh2 initialization failed (%d)\n", rc);
        return false;
    }
 
    /*
     * The application code is responsible for creating the socket
     * and establishing the connection
     */ 
    sock = socket(AF_INET, SOCK_STREAM, 0);
 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
#ifdef G_OS_WIN32
	sin.sin_addr.s_addr = *(uint32_t*)hostent -> h_addr;
#else
	sin.sin_addr.s_addr = *(u_int32_t*)hostent -> h_addr;
#endif

    if(connect(sock, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in)) != 0) 
	{
        fprintf(stderr, "failed to connect!\n");
        return false;
    }
 
    // Create a session instance
    session = libssh2_session_init();

    if(!session)
	{
		systemshutdownFTP(session, sock);
        return false;
	}
 
    /* Since we have set non-blocking, tell libssh2 we are non-blocking */ 
    libssh2_session_set_blocking(session, 0);

 
    /* ... start it up. This will trade welcome banners, exchange keys,
        * and setup crypto, compression, and MAC layers
        */ 
    while((rc = libssh2_session_startup(session, sock)) == LIBSSH2_ERROR_EAGAIN);
    if (rc)
	{
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
		systemshutdownFTP(session, sock);
        return false;
    }
 
    /* At this point we havn't yet authenticated.  The first thing to do is
     * check the hostkey's fingerprint against our known hosts Your app may
     * have it hard coded, may go to a file, may present it to the user,
     * that's your call
     */ 
    libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
 
    if(auth_pw) 
	{
        /* We could authenticate via password */ 
        while ((rc = libssh2_userauth_password(session, userSftp.c_str(), passSftp.c_str())) 
               == LIBSSH2_ERROR_EAGAIN);
        if(rc) 
		{
            printf("Authentication by password failed.\n");
            systemshutdownFTP(session, sock);

			return false;
        }
    } 
	else 
	{
        /* Or by public key */ 
        while ((rc = libssh2_userauth_publickey_fromfile(session, userSftp.c_str(),
                                                         Utiles::direccionCache(".ssh/id_rsa.pub").c_str(),
                                                         Utiles::direccionCache(".ssh/id_rsa").c_str(),
                                                         passSftp.c_str())) == LIBSSH2_ERROR_EAGAIN);
		if (rc) 
		{
            printf("\tAuthentication by public key failed\n");
            systemshutdownFTP(session, sock);

			return false;
        }
    }

    do {
        sftp_session = libssh2_sftp_init(session);

 
        if (!sftp_session && (libssh2_session_last_errno(session) != LIBSSH2_ERROR_EAGAIN))
		{
            fprintf(stderr, "Unable to init SFTP session\n");
            systemshutdownFTP(session, sock);

			return false;
        }
    } while (!sftp_session);

    //Bucle de envio de datos
    //enviamos primero el xml original.
    if(!envioDeDatos(session, sock, sftp_session, rc, img.getRutaXmlImg(), img.getNombreXml()))
    {
	    fprintf(stderr, "Unable to send xml file\n");
	    systemshutdownFTP(session, sock);
		return false;
    }
    
    vector<string> xmlRutaTest, xmlNombreTest;
    int numXml;
    double percetUpload(0.0);
    
    xmlRutaTest = img.getXmlTest();
    xmlNombreTest = img.getNombreXmlTest();
    
    numXml = xmlRutaTest.size();
		
    //Envio del resto de los datos
    for(int i = 0; i < numXml; i++)
    {	
		if(!envioDeDatos(session, sock, sftp_session, rc, xmlRutaTest[i], xmlNombreTest[i]))
		{
			fprintf(stderr, "Unable to send xml test file number %d\n", i);
			systemshutdownFTP(session, sock);
			return false;
		}
		percetUpload = (i + 1) / numXml;
		dProgres.setEstadoBarraProgreso(percetUpload);
		dProgres.setPercentText(percetUpload);
		//Actualizamos la ventana
		Utiles::actualizarInterfaz();
    }
    
    dProgres.cierraVentanaProgreso();
    
    libssh2_sftp_shutdown(sftp_session);

	//Cerramos la sesion
	systemshutdownFTP(session, sock);

    return true;
}

/**
 */
bool SftpConexion::envioDeDatos(LIBSSH2_SESSION *session, int sock, LIBSSH2_SFTP *sftp_session,
								 int &rc, const string &pathXml, const string &nombreXml)
{	
    LIBSSH2_SFTP_HANDLE *sftp_handle;
	size_t nread;
    string auxPathSftp, strBuffer;
    ifstream buffer;
    
    auxPathSftp = pathSftp + "/" + nombreXml;
    nread = 0;
    strBuffer = "";
	
	buffer.open(pathXml.c_str(), ios::in);
	
	/* Request a file via SFTP */ 
    do {
        sftp_handle = libssh2_sftp_open(sftp_session, auxPathSftp.c_str(),
                                        LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_TRUNC,
                                        LIBSSH2_SFTP_S_IRUSR|LIBSSH2_SFTP_S_IWUSR|
                                        LIBSSH2_SFTP_S_IRGRP|LIBSSH2_SFTP_S_IROTH);
	
        if (!sftp_handle && (libssh2_session_last_errno(session) != LIBSSH2_ERROR_EAGAIN))
		{
            fprintf(stderr, "Unable to open file with SFTP\n");
            systemshutdownFTP(session, sock);

			return false;
        }
    } while (!sftp_handle);

	while(!buffer.eof())
	{
		string auxStr;
		//Leemos un linea entera hasta encontrar \n
		getline(buffer, auxStr, '\n');
		
		strBuffer = strBuffer + auxStr;
		
	}
	nread = strBuffer.size();
 
	if(nread > 25000)
	{
		size_t restante, uploaded;
		string aux;

		uploaded = 0;
		
		do
		{
			restante = nread - uploaded;
			
			if(restante > 20000)
			{
				aux = strBuffer.substr(uploaded, 20000);
				uploaded = uploaded + 20000;
			}
			else
			{
				aux = strBuffer.substr(uploaded, strBuffer.length());
				uploaded = uploaded + restante;
			}
			while ((rc = libssh2_sftp_write(sftp_handle, aux.c_str(), aux.length())) == LIBSSH2_ERROR_EAGAIN)
			{
				waitsocket(sock, session);
			}
			
		}while(restante);
	}
	else
	{
		while ((rc = libssh2_sftp_write(sftp_handle, strBuffer.c_str(), nread)) == LIBSSH2_ERROR_EAGAIN)
		{
			waitsocket(sock, session);
		}
	}
	
    //fclose(local);
	buffer.close();
	
    if (rc < 0)
	{
		systemshutdownFTP(session, sock);
		return false;
	}

	libssh2_sftp_close(sftp_handle);
    
    return true;
}

/**
 Cierra el sistema de subida de ficheros ante un posible error o una subida finalizada.
 @param session, puntero LIBSSH2_SESSION.
 @param sock, int.
 */
void SftpConexion::systemshutdownFTP(LIBSSH2_SESSION *session, int sock)
{
	if(libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing") == LIBSSH2_ERROR_EAGAIN)
	{
		libssh2_session_free(session);
	}

#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif
 
    libssh2_exit();
}
