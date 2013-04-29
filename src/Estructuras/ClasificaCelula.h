/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ClasificaCelula.h
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

#ifndef _CLASIFICACELULA_H_
	#define _CLASIFICACELULA_H_

	#include <string.h>
	#include <iostream>
	#include <gdkmm.h>
	#include "Utiles.h"
	
	using namespace std;

	class ClasificaCelula
	{
		public:
			ClasificaCelula();
			~ClasificaCelula();
			ClasificaCelula(const ClasificaCelula &cc);
			string getEtiquetaClasificacion();
			string getNombreClasificacion();
			string getDescripcionClasificacion();
			bool getEnUso();
			void setEnUso(bool eu);
			void setEtiquetaClasificacion(const string &eC);
			void setNombreClasificacion(const string &nEC);
			void setDescripcionClasificacion(const string &dEC);
			const ClasificaCelula &operator=(const ClasificaCelula &ec);
		private:
			//Atributos
			string etiqueta, nombreTipo, descripcion;
			//Verdadero esta en uso, falso no
			bool enUso;
	};
#endif //_CLASIFICACELULA_H_
