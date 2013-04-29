/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CoreGovocitos.h
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

#ifndef _COREGOVOCITOS_H_
	#define _COREGOVOCITOS_H_

	#include "Modulos/ModulosGovocitos.h"
	#include "Interfaz/InterfazGovocitos.h"
	#include "Interfaz/Preferencias.h"
	#include "Config/ConfigGovocitos.h"
	#include "Conectividad/XmlConectividad.h"
	#include "Conectividad/XmlWebDatos.h"
	#include "Conectividad/XmlWebImagenes.h"
	#include "Fichero.h"
	#include "Interfaz/DialogoRemoto.h"
	#include "Utiles.h"
	#include "Bordes/DeteccionAut.h"
	#include "Interfaz/DialogoIndividuo.h"
	#include "Conectividad/XmlWebIndividuo.h"
	#include "Conectividad/XmlWebFecundidad.h"
	#include "Modulos/ConexionBD.h"
	#include "Modulos/SftpConexion.h"

	class CoreGovocitos
	{
		public:
			CoreGovocitos();
			~CoreGovocitos();
			ModulosGovocitos *getModeloGovocitos();
			InterfazGovocitos *getInterfazGovocitos();
			void ejecMenuPreferencias(Preferencias &pref);
			void abrirImagenLocal();
			void abrirXmlLocal();
			bool abrirImagenRemotaBD();
			bool AbrirXmlRemotoBD();
			bool AbrirXmlRemotoImgPre();
			bool AbrirIndividuoBD();
			void guardarCelulas(const string &,const string &terminacion);
			bool guardarCelulasBD();
			void cerrarImagen();
			void operacionDesHacer();
			void operacionReHacer();
			void calculoDiametros();
			void calculoDatosEstadisticos();
			bool aumentaZoom();
			bool disminuyeZoom();
			void zoomOriginal();
			float zoomVentana(Gtk::Widget *wid);
			void cargaDatosCelulas(const string &rutaCoord);
			void updateClaseEstadoBD();
			void updateRejillasBD();
			bool compruebaConectividadBD(bool cond = false);
			void deteccionBordesImagen();
			void deteccionBordesSupervised();
			void clasificacionEstClAutomatica();
			bool guardarFecundidadBD();
			bool guardarRejillaBD();
			void guardarXMLIntermedios(const string &numXml);
			//Deprecated
			bool abrirImagenRemota();
			bool AbrirXmlRemoto();
			bool AbrirIndividuo();
			bool compruebaConectividad(bool cond = false);
			void updateClaseEstado();
		private:
			//Metodos
			void setSensibleDesHacer();
			void guardaModificacionDeshacer();
			bool calculoFecundidad();
			void inicializaSistema();
			void cargaValorMicrasSistema();
			//Atributos
			InterfazGovocitos *interfazGovocitos;
			ModulosGovocitos *modeloGovocitos;	
	};
#endif //_COREGOVOCITOS_H_
