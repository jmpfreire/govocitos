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

#include "XmlWebDatos.h"

/**
 Constructor.
 @param cc, vector<ClaseCelula>.
 @param ec, vector<EstadoCelula>.
 */
XmlWebDatos::XmlWebDatos(vector<ClaseCelula> &cc, vector<EstadoCelula> &ec)
{
	punteroCC = &cc;
	punteroEC = &ec;

	clasifyCell = new ClasificaCelula();
}

/**
 Destructor
 */
XmlWebDatos::~XmlWebDatos()
{


}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 @deprecated
 */
void XmlWebDatos::on_start_element(const Glib::ustring& nameXml, const AttributeList& attributes)
{	
	string calib;
	nodeName = nameXml;
	
	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("etiq" == iter->name)
			{
				clasifyCell->setEtiquetaClasificacion(iter->value);
			}
			if("name" == iter->name)
			{
				clasifyCell->setNombreClasificacion(iter->value);
			}
			if("descrip" == iter->name)
			{
				clasifyCell->setDescripcionClasificacion(iter->value);
			}
		}
		catch(const Glib::ConvertError& ex)
		{
			//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
			cerr<<"XmlParse attributes Exception obtaining name or value"<<ex.what()<<endl;
		}
	}
}

/**
 Detecta el elemento de finalización del fichero xml.
 @param name, Glib::ustring.
 @deprecated
 */
void XmlWebDatos::on_end_element(const Glib::ustring& nameXml)
{
	if("cl" == nameXml || "est" == nameXml)
	{
		if("cl" == nameXml)
		{
			ClaseCelula *auxClase = new ClaseCelula();

			auxClase->setEtiquetaClasificacion(clasifyCell->getEtiquetaClasificacion());
			auxClase->setNombreClasificacion(clasifyCell->getNombreClasificacion());
			auxClase->setDescripcionClasificacion(clasifyCell->getDescripcionClasificacion());

			punteroCC->push_back(*auxClase);

			delete auxClase;
		}
		else
		{
			EstadoCelula *auxEstado = new EstadoCelula();

			auxEstado->setEtiquetaClasificacion(clasifyCell->getEtiquetaClasificacion());
			auxEstado->setNombreClasificacion(clasifyCell->getNombreClasificacion());
			auxEstado->setDescripcionClasificacion(clasifyCell->getDescripcionClasificacion());

			punteroEC->push_back(*auxEstado);

			delete auxEstado;
		}
	}

	if(clasifyCell)
	{
		delete clasifyCell;
	}
	
	clasifyCell = new ClasificaCelula();
}
