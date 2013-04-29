/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConexionBD.h
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jmpintorfreire@gmail.com>
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

#ifndef _CONEXIONBD_H_
	#define _CONEXIONBD_H_

	#include <iostream>
	#include <mysql++.h>
	#include <vector>
	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Estructuras/ListadoImagenes.h"
	#include "Estructuras/ListadoIndividuo.h"
	#include "Dialogos.h"
	#include "Modulos/SftpConexion.h"
	#include "Modulos/ResultFecundidad.h"
	#include "Estructuras/ListadoIndividuo.h"
	#include "Modulos/Rejilla.h"
	#include "Modulos/CalculoFecundidad.h"
	#include "Config/OpcionesPref.h"

	using namespace std;

	class ConexionBD
	{
		public:
			ConexionBD(OpcionesPref &opcP);
			~ConexionBD();
			bool comprobarConectividad();
			bool obtenerClase(vector<ClaseCelula> &cl);
			bool obtenerEstado(vector<EstadoCelula> &est);
			bool obtenerImagenes(ListadoImagenes &lI);
			bool obtenerIndividuo(vector<ListadoIndividuo> &li);
			bool guardarDatosFecundidad(ListadoIndividuo &listInd, ResultFecundidad &resF, 
			                            vector<EstadoCelula> &estados);
			bool actualizarXMLPath(ImageCells &image, SftpConexion &conex);
			bool insertarRejilla(Rejilla &rej, int pFila, int pColumna, int pDistancia);
			bool insertarRejillasPref(vector<OpcionesRej> &rejillas);
			bool consultaRejillas(vector<OpcionesRej> &rejillas);
			bool obtenerFactoresCorreccion(CalculoFecundidad &clFec,const string &especie);
		private:
			string dataBase, urlDataBase, userDataBase, passDataBase;			
	};
#endif //_CONEXIONBD_H_
