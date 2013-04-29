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

#include "XmlWebImagenes.h"

/**
 Constructor.
 @param lI, ListadoImagenes.
 */
XmlWebImagenes::XmlWebImagenes(ListadoImagenes &lI)
{
	punteroListI = &lI;
	imagenW = new DataImage();
}

/**
 Destructor
 */
XmlWebImagenes::~XmlWebImagenes()
{


}

/**
 Lee el xml y asigna los valores a los atributos
 @param name nombre del atributo
 @param attributes lista de atributos del xml
 @deprecated
 */
void XmlWebImagenes::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
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
			if("codigo_especie" == iter->name)
			{
				imagenW->setSpecieImage(iter->value);
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
void XmlWebImagenes::on_end_element(const Glib::ustring& name)
{
	if("image" == name)
	{
		//Añadimos el poligono al vector de poligonos
		punteroListI->setImagenVector(*imagenW);

		delete imagenW;

		imagenW = new DataImage();
	}
}
