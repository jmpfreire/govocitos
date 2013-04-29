/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlWebFecundidad.cpp
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

#include "XmlWebFecundidad.h"

/**
 Constructor.
 @param vlI, ListadoCelulas.
 */
XmlWebFecundidad::XmlWebFecundidad(ListadoIndividuo &vlI)
{
	punteroListI = &vlI;
	auxInd = new ListadoIndividuo();
	
}

/**
 Destructor
 */
XmlWebFecundidad::~XmlWebFecundidad()
{


}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 @deprecated
 */
void XmlWebFecundidad::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
{	
	string calib;
	nodeName = name;
	
	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("codigo_campanha" == iter->name)
			{
				auxInd->setCampanhaInd(iter->value);
			}
			if("codigo_muestreo" == iter->name)
			{
				auxInd->setMuestreoInd(iter->value);
			}
			if("codigo_individuo" == iter->name)
			{
				auxInd->setIndividuoInd(iter->value);
			}
			if("scherle" == iter->name)
			{
				calib = iter->value;
				auxInd->setValorScherle(atof(calib.data()));
			}
			if("beta" == iter->name)
			{
				calib = iter->value;
				auxInd->setValorBeta(atof(calib.data()));
			}
			if("peso_ovario_fresco" == iter->name)
			{
				calib = iter->value;
				auxInd->setPesoOvarioFresco(atof(calib.data()));
			}
			if("formol_fresco" == iter->name)
			{
				calib = iter->value;
				auxInd->setFormolFresco(atof(calib.data()));
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
void XmlWebFecundidad::on_end_element(const Glib::ustring& name)
{	
	if("individuo" == name)
	{
		if(punteroListI->getIndividuoInd() == auxInd->getIndividuoInd() &&
		   punteroListI->getMuestreoInd() == auxInd->getMuestreoInd() &&
		   punteroListI->getCampanhaInd() == auxInd->getCampanhaInd())
		{
			punteroListI->setValorBeta(auxInd->getValorBeta());
			punteroListI->setValorScherle(auxInd->getValorScherle());
			punteroListI->setFormolFresco(auxInd->getFormolFresco());
			punteroListI->setPesoOvarioFresco(auxInd->getPesoOvarioFresco());
		}
		else
		{
			if(auxInd)
			{
				delete auxInd;
			}

			auxInd = new ListadoIndividuo();
		}
	}
}
