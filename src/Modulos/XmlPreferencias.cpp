/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2008-2012 <jpfreire@correo.ei.uvigo.es>
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

#include "XmlPreferencias.h"
#include "Config/ConfigGovocitos.h"

/**
 Constructor.
 @param sistemConf, ConfigGovocitos.
 */
XmlPreferencias::XmlPreferencias(ConfigGovocitos &sc) : xmlpp::SaxParser()
{
	sistemConf = &sc;

	vClassCell = sistemConf->getDatosClases();
	vStateCell = sistemConf->getDatosEstados();
	vRejPers = sistemConf->getDatosRejilla();
	opcPref = sistemConf->getDatosPreferencias();

	clCell = new ClaseCelula();
	estCell = new EstadoCelula();
	rejPers = new OpcionesRej();

	col = new Gdk::Color();
}

/**
 Destructor.
 */
XmlPreferencias::~XmlPreferencias()
{

}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 */
void XmlPreferencias::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
{	
	string aux = "";

	nodeName = name;
	
	if(name == "clase")
	{
		//Atributos
		for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			try
			{
				if(iter->name == "etiqueta")
				{
					clCell->setEtiquetaClasificacion(iter->value);
				}
				if(iter->name == "nombre")
				{
					clCell->setNombreClasificacion(iter->value);
				}
				if(iter->name == "descripcion")
				{
					clCell->setDescripcionClasificacion(iter->value);
				}
				if(iter->name == "enUso")
				{
					if(iter->value == "true")
					{
						clCell->setEnUso(true);
					}
					else
					{
						clCell->setEnUso(false);
					}
				}
				if(iter->name == "linea")
				{
					aux = iter->value;
					clCell->setLinea(atoi(aux.data()));
				}
			}
			catch(const Glib::ConvertError& ex)
			{
				//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
				cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
			}
		}
	}
	else if(name == "estado")
	{
		//Atributos
		for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			try
			{
				if(iter->name == "etiqueta")
				{
					estCell->setEtiquetaClasificacion(iter->value);
				}
				if(iter->name == "nombre")
				{
					estCell->setNombreClasificacion(iter->value);
				}
				if(iter->name == "descripcion")
				{
					estCell->setDescripcionClasificacion(iter->value);
				}
				if(iter->name == "enUso")
				{
					if(iter->value == "true")
					{
						estCell->setEnUso(true);
					}
					else
					{
						estCell->setEnUso(false);
					}
				}
				if(iter->name == "rojo")
				{
					aux = iter->value;
					col->set_red(atoi(aux.data()));
				}
				if(iter->name == "verde")
				{
					aux = iter->value;
					col->set_green(atoi(aux.data()));
				}
				if(iter->name == "azul")
				{
					aux = iter->value;
					col->set_blue(atoi(aux.data()));
				}
			}
			catch(const Glib::ConvertError& ex)
			{
				//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
				cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
			}
		}
	}
	else if(name == "rejilla")
	{
		//Atributos
		for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			try
			{
				if(iter->name == "id")
				{
					aux = iter->value;
					rejPers->setID(atoi(aux.data()));
				}
				if(iter->name == "numero_Filas")
				{
					aux = iter->value;
					rejPers->setNumFilas(atoi(aux.data()));
				}
				if(iter->name == "numero_Columnas")
				{
					aux = iter->value;
					rejPers->setNumColumnas(atoi(aux.data()));
				}
				if(iter->name == "numero_Puntos")
				{
					aux = iter->value;
					rejPers->setNumPuntos(atoi(aux.data()));
				}
				if(iter->name == "separacion_puntos")
				{
					aux = iter->value;
					rejPers->setSeparaPuntos(atoi(aux.data()));
				}
			}
			catch(const Glib::ConvertError& ex)
			{
				//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
				cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
			}
		}
	}
	else if(name == "pref")
	{
		//Atributos
		for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			try
			{
				if(iter->name == "rojo")
				{
					aux = iter->value;
					col->set_red(atoi(aux.data()));
				}
				if(iter->name == "verde")
				{
					aux = iter->value;
					col->set_green(atoi(aux.data()));
				}
				if(iter->name == "azul")
				{
					aux = iter->value;
					col->set_blue(atoi(aux.data()));
				}
				if(iter->name == "linea")
				{
					aux = iter->value;
					opcPref->setGrosLinea(atof(aux.data()));
				}
				if(iter->name == "puntos")
				{
					aux = iter->value;
					opcPref->setGrosLinea(atof(aux.data()));
				}
				if(iter->name == "imagenes")
				{
					opcPref->setArchivImag(iter->value);
				}
				if(iter->name == "celulas")
				{
					opcPref->setArchivCel(iter->value);
				}
				if(iter->name == "csv")
				{
					opcPref->setArchivCSV(iter->value);
				}
			}
			catch(const Glib::ConvertError& ex)
			{
				//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
				cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
			}
		}
	}
	else
	{
		//Atributos
		for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			try
			{
				if(iter->name == "linea")
				{
					aux = iter->value;
					opcPref->setGrosLinea(atof(aux.data()));
				}
				if(iter->name == "puntos")
				{
					aux = iter->value;
					opcPref->setGrosLinea(atof(aux.data()));
				}
				if(iter->name == "imagenes")
				{
					opcPref->setArchivImag(iter->value);
				}
				if(iter->name == "celulas")
				{
					opcPref->setArchivCel(iter->value);
				}
				if(iter->name == "csv")
				{
					opcPref->setArchivCSV(iter->value);
				}
				if(iter->name == "rejilla_completa")
				{
					aux = iter->value;
					opcPref->setGrosRej(atof(aux.data()));
				}
				if(iter->name == "borde_rejilla_completa")
				{
					aux = iter->value;
					opcPref->setGrosBordeRej(atof(aux.data()));
				}
				if(iter->name == "puntos_rejilla_completa")
				{
					aux = iter->value;
					opcPref->setSeparPuntos(atof(aux.data()));
				}
				if(iter->name == "loginBD")
				{
					opcPref->setLoginBD(iter->value);
				}
				if(iter->name == "passwordBD")
				{
					opcPref->setPassBD(iter->value);
				}
				if(iter->name == "urlBD")
				{
					opcPref->setDirecBD(iter->value);
				}
				if(iter->name == "nombreBD")
				{
					opcPref->setDataBaseBD(iter->value);
				}
				if(iter->name == "loginSFTP")
				{
					opcPref->setLoginSFTP(iter->value);
				}
				if(iter->name == "passwordSFTP")
				{
					opcPref->setPassSFTP(iter->value);
				}
				if(iter->name == "urlSFTP")
				{
					opcPref->setDirecSFTP(iter->value);
				}
				if(iter->name == "pathSFTP")
				{
					opcPref->setPathSFTP(iter->value);
				}
				if(iter->name == "tamanho")
				{
					aux = iter->value;
					opcPref->setTamCache(atoi(aux.data()));
				}
			}
			catch(const Glib::ConvertError& ex)
			{
				//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
				cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
			}
		}
	}
}

/**
 Detecta el elemento de finalización del fichero xml.
 @param name, Glib::ustring.
 */
void XmlPreferencias::on_end_element(const Glib::ustring& name)
{
	if(name == "clase")
	{
		vClassCell->push_back(*clCell);

		if(clCell)
		{
			delete clCell;
		}

		clCell = new ClaseCelula();
	}
	else if(name == "estado")
	{
		estCell->setColorEstado(*col);

		vStateCell->push_back(*estCell);
		
		if(estCell)
		{
			delete estCell;
		}
		if(col)
		{
			delete col;
		}

		estCell = new EstadoCelula();
		col = new Gdk::Color();
	}
	else if(name == "rejilla")
	{
		vRejPers->push_back(*rejPers);

		if(rejPers)
		{
			delete rejPers;
		}
		
		rejPers = new OpcionesRej();
	}
	else
	{
		if(name == "celula_desconocida")
		{
			opcPref->setCelSDet(*col);
		}
		else if(name == "celula_seleccionada")
		{
			opcPref->setSeleCel(*col);
		}
		else if(name == "celula_edicion")
		{
			opcPref->setEdiCel(*col);
		}
		else if(name == "rejilla_limite_derechoInferior")
		{
			opcPref->setLimDI(*col);
		}
		else if(name == "rejilla_limite_izquierdoSuperior")
		{
			opcPref->setLimIS(*col);
		}
		else if(name == "color_rejilla")
		{
			opcPref->setColRej(*col);
		}
	}
}
