/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlWebIndividuo.cpp
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

#include "XmlWebIndividuo.h"

/**
 Constructor.
 @param vlI, vector<ListadoIndividuo>.
 */
XmlWebIndividuo::XmlWebIndividuo(vector<ListadoIndividuo> &vlI)
{
	punteroListI = &vlI;
	imagenW = new ImageCells();
	listIndiv = new ListadoIndividuo();
}

/**
 Destructor
 */
XmlWebIndividuo::~XmlWebIndividuo()
{


}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 @deprecated
 */
void XmlWebIndividuo::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
{	
	string calib;
	nodeName = name;
	
	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("nameimage" == iter->name)
			{
				imagenW->setNombreImg(iter->value);
			}
			if("namexml" == iter->name)
			{
				imagenW->setNombreXml(iter->value);
			}
			if("pathimage" == iter->name)
			{
				imagenW->setRutaImg(iter->value);
			}
			if("pathxml" == iter->name)
			{
				imagenW->setRutaXmlImg(iter->value);
			}
			if("calibracion" == iter->name)
			{
				calib = iter->value;
				imagenW->setCalibracionImg(atof(calib.data()));
			}
			if("codigo_campanha" == iter->name)
			{
				imagenW->setCampanhaImg(iter->value);
			}
			if("codigo_muestreo" == iter->name)
			{
				imagenW->setMuestreoImg(iter->value);
			}
			if("codigo_individuo" == iter->name)
			{
				imagenW->setIndividuoImg(iter->value);
			}
			if("codigo_imagen" == iter->name)
			{
				imagenW->setCodigoImagen(iter->value);
			}
			if("md5" == iter->name)
			{
				imagenW->setMd5Img(iter->value);
			}
			if("filas" == iter->name)
			{
				calib = iter->value;
				imagenW->setAltoImg(atoi(calib.data()));
			}
			if("columnas" == iter->name)
			{
				calib = iter->value;
				imagenW->setAnchoImg(atoi(calib.data()));
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
void XmlWebIndividuo::on_end_element(const Glib::ustring& name)
{
	if("image" == name)
	{
		int numL;
		int indice = 0;

		numL = punteroListI->size();

		while((indice < numL) && (((*punteroListI)[indice].getIndividuoInd() != imagenW->getIndividuoImg()) ||
		      ((*punteroListI)[indice].getMuestreoInd() != imagenW->getMuestreoImg()) ||
		      ((*punteroListI)[indice].getCampanhaInd() != imagenW->getCampanhaImg())))
		{
			indice++;
		}
	
		if((indice < numL) && ((*punteroListI)[indice].getCampanhaInd() == imagenW->getCampanhaImg()) &&
		      ((*punteroListI)[indice].getMuestreoInd() == imagenW->getMuestreoImg()) &&
		     ((*punteroListI)[indice].getIndividuoInd() == imagenW->getIndividuoImg()))
		{
			(*punteroListI)[indice].setImagenVector(*imagenW);

			if(imagenW->getRutaXmlImg() != "")
			{
				(*punteroListI)[indice].incrementaXmlAnalizado();
			}
			if(imagenW->getRutaImg() != "")
			{
				(*punteroListI)[indice].incrementaImagenes();
			}
		}
		else
		{	
			listIndiv->setCampanhaInd(imagenW->getCampanhaImg());
			listIndiv->setMuestreoInd(imagenW->getMuestreoImg());
			listIndiv->setIndividuoInd(imagenW->getIndividuoImg());
			                          
			listIndiv->setImagenVector(*imagenW);

			if(imagenW->getRutaXmlImg() != "")
			{
				listIndiv->incrementaXmlAnalizado();
			}
			if(imagenW->getRutaImg() != "")
			{
				listIndiv->incrementaImagenes();
			}
			punteroListI->push_back(*listIndiv);

			delete listIndiv;

			listIndiv = new ListadoIndividuo();
		}

		delete imagenW;

		imagenW = new ImageCells();
	}
}
