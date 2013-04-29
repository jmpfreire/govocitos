/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ModulosGovocitos.h
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
 
#ifndef _MODULOSGOVOCITOS_H_
	#define _MODULOSGOVOCITOS_H_

	#include "Estructuras/ListadoCelulas.h"
	#include "Estructuras/ListadoImagenes.h"
	#include "Config/ConfigGovocitos.h"
	#include "Modulos/HttpsConexion.h"
	#include "Estructuras/ImageCells.h"
	#include "Modulos/DesReHacer.h"
	#include "Modulos/SistemaDibujado.h"
	#include "Estructuras/ListadoCache.h"
	#include "Clasificador/Clasificador.h"
	#include "Modulos/Rejilla.h"
	#include "Modulos/CalculoFecundidad.h"
	#include "Estructuras/ListadoIndividuo.h"
	#include "Modulos/ResultFecundidad.h"
	#include "Bordes/DeteccionAut.h"
	#include "Modulos/SftpConexion.h"
	#include "Modulos/ConexionBD.h"

	class ModulosGovocitos
	{
		public:
			ModulosGovocitos();
			~ModulosGovocitos();
			ConfigGovocitos *getConfiguracion();
			ListadoCelulas *getListaCelulas();
			ListadoImagenes *getListaImagenes();
			HttpsConexion *getConexionBD();
			ImageCells *getImageActual();
			DesReHacer *getDeshacer();
			DesReHacer *getRehacer();
			SistemaDibujado *getSistemaDibujado();
			ListadoCache *getListadoCache();
			Rejilla *getRejilla();
			CalculoFecundidad *getCalculoFecundidad();
			ListadoIndividuo *getListadoIndividuo();
			ResultFecundidad *getListaResultadosImg();
			DeteccionAut *getDeteccionAut();
			SftpConexion *getConexionSftp();
			ConexionBD *getConexionMySql();
			void setNuevaListaImagenes();
			void setNuevosDatosConexion();
			void setNuevasCelulas();
			void setNuevaImagen();
			void setNuevaPilaDeshacer();
			void setNuevaPilaRehacer();
			void setNuevaRejilla();
			void setNuevoCalculoFecundidad();
			void setNuevoListadoIndividuo();
			void setNuevoListaResultadosImg();
			void setNuevoDeteccionAut();
			void setNuevoConexionSftp();
			void setNuevoConexionMySql();
		private:
			ConfigGovocitos *confGovocitos;
			ListadoCelulas *listaCells;
			ListadoImagenes *listaImag;
			HttpsConexion *conexionHttp;
			ImageCells *imagenCelulas;
			DesReHacer *deshacer, *rehacer;
			SistemaDibujado *paintSystem;
			ListadoCache *listaCache;
			Rejilla *rejilla;
			CalculoFecundidad *cFecundidad;
			ListadoIndividuo *listIndividuo;
			ResultFecundidad *listResultados;
			DeteccionAut *detecAutomatica;
			SftpConexion *conexionSftp;
			ConexionBD *consultBD;
			
	};
#endif //_MODULOSGOVOCITOS_H_
