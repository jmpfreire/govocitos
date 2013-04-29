/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Fichero.h
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

#ifndef _FICHERO_H_
	#define _FICHERO_H_

	#include <string>
	#include <vector>
	#include <iostream>
	#include <fstream>
	#include <cstdlib>
	#include <gtkmm.h>
	#include <list>
	#include <stdio.h>

	#include "Modulos/XmlParse.h"
	#include "Modulos/XmlPreferencias.h"
	#include "Modulos/XmlCache.h"
	#include "Estructuras/ListadoCelulas.h"
	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Config/OpcionesPref.h"
	#include "Config/OpcionesRej.h"
	#include "Utiles.h"

	using namespace std;

	class ConfigGovocitos;

	class Fichero
	{
		public:
			static void leerFich(const string &ruta, ListadoCelulas &conjunCelulas);
			static void escribFich(const string &ruta, ListadoCelulas &conjunCelulas);
			static void leerFichXml(const string &ruta, ListadoCelulas &conjunCelulas);
			static void escribFichXml(const string &ruta, ListadoCelulas &conjunCelulas);
			static void leerFichConfig(const string &ruta, OpcionesPref &op);
			static void escribFichConfig(const string &ruta, OpcionesPref &op);
			static void leerFichClases(const string &ruta, vector<ClaseCelula> &ete);
			static void escribFichClases(const string &ruta, vector<ClaseCelula> &ets);
			static void leerFichEstados(const string &ruta, vector<EstadoCelula> &ete);
			static void escribFichEstados(const string &ruta, vector<EstadoCelula> &ets);
			static void leerFichOpcionesRej(const string &ruta, vector<OpcionesRej> &ope);
			static void escribFichOpcionesRej(const string &ruta, vector<OpcionesRej> &ops);
			static void leerFichCache(const string &ruta, list<string> &lce);
			static void escribirFichCache(const string &ruta, list<string> &lcs);
			static void borraImagenSistema(const string &ruta);
			static bool compruebaFich(const string &ruta);
			static void escribXmlCache(const string &ruta, ConfigGovocitos &opcSistema);
			static void escribXmlPreferencias(const string &ruta, ConfigGovocitos &opcSistema);
			static void leerXmlPreferencias(const string &ruta, ConfigGovocitos &sistemConf);
			static void leerXmlCache(const string &ruta, ConfigGovocitos &opcSistema);
	};

#endif // _FICHERO_H_
