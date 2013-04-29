/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DataImage.h
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

#ifndef _DATAIMAGE_H_
	#define _DATAIMAGE_H_

	#include <string>

	using namespace std;

	class DataImage
	{
		public:
			DataImage();
			~DataImage();
			DataImage(const DataImage &ic);
			string getNombreImg();
			double getCalibracionImg();
			string getCampanhaImg();
			string getMuestreoImg();
			string getIndividuoImg();
			string getCodigoImagen();
			string getRutaXmlImg();
			string getRutaImg();
			string getNombreXml();
			string getMd5Img();
			int getAnchoImg();
			int getAltoImg();
			double getFormolFresco();
			string getSpecieImage();
			string getNombreImgCompleto();
			string getTipoImg();
			double getDiametroMax();
			double getDiametroMin();
			void setSpecieImage(const string &si);
			void setNombreImg(const string &ni);
			void setTipoImg(const string &tp);
			void setCalibracionImg(double cl);
			void setCampanhaImg(const string &campI);
			void setMuestreoImg(const string &muestI);
			void setIndividuoImg(const string &indI);
			void setCodigoImagen(const string &cdI);
			void setRutaXmlImg(const string &rxi);
			void setRutaImg(const string &ri);
			void setNombreXml(const string &nx);
			void setMd5Img(const string &md5);
			void setAnchoImg(int ancho);
			void setAltoImg(int alto);
			void setDiametroMax(double diam);
			void setDiametroMin(double diam);
			const DataImage &operator=(const DataImage &ic);
		protected:
			string nombreImg, rutaImg, nombreImgComp, tipoImg;
			string codigoCampanha, codigoMuestreo, codigoIndividuo, codigoImagen, specieImage;
			string rutaXmlImg, nombreXml;
			string md5CRC;
			int anchoImg, altoImg;
			double calibracionImg, diametroMaximo, diametroMinimo;
	};
#endif //_DATAIMAGE_H_
