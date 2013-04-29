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

#include "XmlParse.h"

/**
 Constructor.
 @param lc, ListadoCelulas.
 */
XmlParse::XmlParse(ListadoCelulas &lc) : xmlpp::SaxParser()
{
	punteroCells = &lc;
	coordX.clear();
	coordY.clear();
	x = y = -1;
	indivCelula = new Celula();
}

/**
 Destructor.
 */
XmlParse::~XmlParse()
{

}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 */
void XmlParse::on_start_element(const Glib::ustring& name,
								const AttributeList& attributes)
{	
	string numPolig;
	string ultId;
	string candidat;
	nodeName = name;
	
	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("idcelulas" == iter->name)
			{
				ultId = iter->value;
				punteroCells->setLastIdCell(atoi(ultId.data()));
			}
			if("numero" == iter->name)
			{
				numPolig = iter->value;
				indivCelula->setIdCelula(atoi(numPolig.data()));
			}
			if("clase" == iter->name)
			{
				indivCelula->setClaseCelula(iter->value.lowercase());
			}
			if("estado" == iter->name)
			{
				indivCelula->setEstadoCelula(iter->value.lowercase());
			}
			if("numeroCandidato" == iter->name)
			{
				candidat = iter->value;
				indivCelula->setCelulaCandidata(atoi(candidat.data()));
			}
		}
		catch(const Glib::ConvertError& ex)
		{
			//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
			cerr<<"XmlParse attributes, Exception while obtaining name or value"<<ex.what()<<endl;
		}
	}
}

/**
 Lee cada uno de los elementos del fichero xml.
 @param text, Glib::ustring.
 */
void XmlParse::on_characters(const Glib::ustring& text)
{
	try
	{
		if(nodeName == "x")  
		{
			if(x == -1)
			{
				x = atoi(text.data());
			}
		}
		else if(nodeName == "y")
		{
			y = atoi(text.data());

			if(x != -1 && y != -1)
			{	
				//Introduciomos las coordenadas en el vector
				coordX.push_back(x);
				coordY.push_back(y);

				//Calculamos las coord max y min
				Utiles::calculoCoordMaxMin(x,y,1,*indivCelula);
			
				//Reseteamos el valor de las variables
				x = y = -1;
			}
		}
	}
	catch(const Glib::ConvertError& ex)
	{
		//cerr<<"XmlParse coordenada Excepcion obteniendo el texto "<<ex.what()<<endl;
		cerr<<"XmlParse coordinate, Exception while obtaining text"<<ex.what()<<endl;
	}
}

/**
 Detecta el elemento de finalización del fichero xml.
 @param name, Glib::ustring.
 */
void XmlParse::on_end_element(const Glib::ustring& name)
{
	if("coords" == name)
	{
		//Añadimos el poligono al vector de poligonos
		indivCelula->setCoordCellX(coordX);
		indivCelula->setCoordCellY(coordY);
		punteroCells->setCelula(*indivCelula);

		//Reseteamos el poligono
		coordX.clear();
		coordY.clear();
		
		if(indivCelula)
		{
			delete indivCelula;
		}
		
		indivCelula = new Celula();
	}
}
