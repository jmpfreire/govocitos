/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _LISTADOCELULAS_H_
	#define _LISTADOCELULAS_H_

	#include <vector>
	#include "Celula.h"
	#include <iostream>

	using namespace std;

	class ListadoCelulas
	{
		public:
			ListadoCelulas();
			~ListadoCelulas();
			ListadoCelulas(const ListadoCelulas &lc);
			int getLastIdCell();
			void incrementaIdCell();
			void setLastIdCell(int idc);
			void setCelula(Celula cel);
			int getNumCelulas();
			Celula *getCelula(int indice);
			void borraCelula(int indice);
			const ListadoCelulas &operator=(const ListadoCelulas &lc);
		private:
			vector<Celula> listCells;
			int lastIdCell;
	};

#endif //_LISTADOCELULAS_H_
