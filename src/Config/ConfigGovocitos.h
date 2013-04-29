/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConfigGovocitos.h
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

#ifndef _CONFIGGOVOCITOS_H_
	#define _CONFIGGOVOCITOS_H_

	#include "OpcionesRej.h"
	#include "OpcionesPref.h"
	#include "Utiles.h"	 
	#include "Fichero.h"
	#include "Estructuras/ListadoCache.h"

	class ConfigGovocitos
	{
		public:
			ConfigGovocitos();
			~ConfigGovocitos();
			vector<OpcionesRej> *getDatosRejilla();
			vector<ClaseCelula> *getDatosClases();
			vector<EstadoCelula> *getDatosEstados();
			OpcionesPref *getDatosPreferencias();
			list<string> *getDatosCache();
			void setDatosRejilla(vector<OpcionesRej> opr);
			void setDatosClases(vector<ClaseCelula> clc);
			void setDatosEstados(vector<EstadoCelula> esc);
			void setDatosPreferencias(OpcionesPref opc);
			void escribirFicherosConf();
			void escribirFicheroCache();
		private:
			//Metodos
			void leerFicheroCache();
			void crearDirectorios();
			void leerFicherosConf();
			//Atributos
			vector<OpcionesRej> datosRejilla;
			vector<ClaseCelula> datosClases;
			vector<EstadoCelula> datosEstados;
			OpcionesPref datosPreferencias;
			list<string> listaCache;
	};

#endif //_CONFIGGOVOCITOS
