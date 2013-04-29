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

#ifndef _NUCLEOCELULA_H_
	#define _NUCELOCELULA_H_

	#include <vector>

	using namespace std;

	class NucleoCelula
	{
		public:
			NucleoCelula();
			~NucleoCelula();
			NucleoCelula(const NucleoCelula &nc);
			const vector<int> *getNucleoX();
			const vector<int> *getNucleoY();
			void setNucleoX(vector<int> nx);
			void setNucleoY(vector<int> ny);
			const NucleoCelula &operator=(const NucleoCelula &nc);
		private:
			vector<int> nucleoX;
			vector<int> nucleoY;
	};
#endif //_NUCLEOCELULA_H_
