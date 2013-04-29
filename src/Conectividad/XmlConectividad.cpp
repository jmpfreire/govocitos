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

#include "XmlConectividad.h"

/**
 Constructor.
 @param cn, string.
 */
XmlConectividad::XmlConectividad(string &cn)
{
	conectividad = &cn;
}

/**
 Destructor
 */
XmlConectividad::~XmlConectividad()
{


}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 @deprecated
 */
void XmlConectividad::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
{	
	nodeName = name;
	
	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("connection" == iter->name)
			{
				*conectividad = iter->value;
			}
		}
		catch(const Glib::ConvertError& ex)
		{
			//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
			cerr<<"XmlParse attributes Exception obtaining name or value"<<ex.what()<<endl;
		}
	}
}
