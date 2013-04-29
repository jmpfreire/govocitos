/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2008 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _OPCIONESREJ_H_
	#define _OPCIONESREJ_H_

	#include <iostream>
	#include <gtkmm.h>
	#include <string.h>

	using namespace std;

	class OpcionesRej
	{
		public:
			OpcionesRej();
			~OpcionesRej();
			OpcionesRej(const OpcionesRej &oR);
			int getNumFilas();
			int getNumColumnas();
			int getNumPuntos();
			int getSeparaPuntos();
			int getID();
			void setNumFilas(int f);
			void setNumColumnas(int c);
			void setNumPuntos(int p);
			void setSeparaPuntos(int sp);
			void setID(int id);
			const OpcionesRej &operator=(const OpcionesRej &oR);
		private:
			int numFilas, numColumnas, numPuntos, separaPuntos, idRej;
	};
#endif // _OPCIONESREJ_H_
