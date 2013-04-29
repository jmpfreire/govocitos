/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Dialogos.h
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

#ifndef _DIALOGOS_H_
	#define _DIALOGOS_H_

	#include <gtkmm.h>
	#include <iostream>

	#include "Utiles.h"

	using namespace std;

	class Dialogos
	{
		public:
			static bool dialogoConfirmacion(const string &t, const string &title);
			static void dialogoError(const string &t, const string &title);
			static void dialogoAdvertencia(const string &t, const string &title);
			static bool dialogoAdvertenciaPref(const string &t, const string &title);
			static bool dialogoExportarCsv(string &ruta, const string &defaultPath);
	};
#endif //_DIALOGOS_H_
