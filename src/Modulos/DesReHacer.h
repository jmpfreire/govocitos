/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DesReHacer.h
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

#ifndef _DESREHACER_H_
	#define _DESREHACER_H_

	#include <iostream>
	#include <stack>
	#include "Estructuras/ListadoCelulas.h"
	#include <gtkmm.h>
	
	using namespace std;
				
	class DesReHacer
	{
		public:
			DesReHacer();
			~DesReHacer();
			void metePilaOper(ListadoCelulas op);
			ListadoCelulas sacaPilaOper();
			void borraElemento();
			bool pilaVacia();
			void vaciar();
		private:
			stack <ListadoCelulas,vector<ListadoCelulas> > pilaOperCelulas;
	};

#endif // _DESREHACER_H_
