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

#ifndef _XMLWEBIMAGENES_H_
	#define _XMLWEBIMAGENES_H_

	#include <iostream>
	#include <libxml++/libxml++.h>
	#include <glibmm/convert.h>
	#include <cstdlib>

	#include "Estructuras/ListadoImagenes.h"

	using namespace std;

	class XmlWebImagenes : public xmlpp::SaxParser
	{
		public:
			XmlWebImagenes(ListadoImagenes &lI);
			~XmlWebImagenes();
		protected:
			virtual void on_start_element(const Glib::ustring& name,
		                            const AttributeList& properties);
		    virtual void on_end_element(const Glib::ustring& name);
		    //Atributos
		    string nodeName;
			DataImage *imagenW;
			ListadoImagenes *punteroListI;
	};
#endif // _HTTPSCONEXION_H_
