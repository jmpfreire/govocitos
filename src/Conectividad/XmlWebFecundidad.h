/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlWebFecundidad.h
 * Copyright (C) José Manuel Pintor Freire 2011 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _XMLWEBFECUNDIDAD_H_
	#define _XMLWEBFECUNDIDAD_H_

	#include <iostream>
	#include <libxml++/libxml++.h>
	#include <glibmm/convert.h>
	#include <cstdlib>

	#include "Estructuras/ListadoIndividuo.h"

	using namespace std;

	class XmlWebFecundidad : public xmlpp::SaxParser
	{
		public:
			XmlWebFecundidad(ListadoIndividuo &vlI);
			~XmlWebFecundidad();
		protected:
			virtual void on_start_element(const Glib::ustring& name,
		                            const AttributeList& properties);
		    virtual void on_end_element(const Glib::ustring& name);
		    //Atributos
		    string nodeName;
			ListadoIndividuo *punteroListI;
			ListadoIndividuo *auxInd;
	};
#endif //_XMLWEBFECUNDIDAD_H_
