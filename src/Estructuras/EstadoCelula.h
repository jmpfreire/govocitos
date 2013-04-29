/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * EstadoCeula.h
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

#ifndef _ESTADOCELULA_H_
	#define _ESTADOCELULA_H_

	#include "ClasificaCelula.h"

	class EstadoCelula : public ClasificaCelula
	{
		public:
			EstadoCelula();
			~EstadoCelula();
			EstadoCelula(const EstadoCelula &ec);
			double getColorEstadoR();
			double getColorEstadoG();
			double getColorEstadoB();
			void setColorEstado(Gdk::Color cec);
			const EstadoCelula &operator=(const EstadoCelula &ec);
		private:
			//Atributos
			double colorEstadoR, colorEstadoG, colorEstadoB;
		
	};
#endif //_ESTADOCELULA_H_
