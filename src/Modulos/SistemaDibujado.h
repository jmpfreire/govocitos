/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * SistemaDibujado.h
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#ifndef _SISTEMADIBUJADO_H_
	#define _SISTEMADIBUJADO_H_

	#include "Estructuras/ImageCells.h"
	#include "Interfaz/PanelDibujado.h"
	#include "Modulos/DibujadoCelula.h"
	#include "Modulos/Rejilla.h"

	class SistemaDibujado
	{
		public:
			SistemaDibujado();
			~SistemaDibujado();
			double getAnchoRedimen();
			double getAltoRedimen();
			double getZoom();
			DibujadoCelula *getCapaCelula();
			Rejilla *getCapaRejilla();
			void setPanelDibujado(PanelDibujado &pd);
			void setRejilla(Rejilla &rej);
			void setImagenOvocito(ImageCells &imagen);
			ImageCells *getImagenOvocito();
			void cargaOpcionesDibujado(OpcionesPref &opc);
			void setImagen();
			void setZoomActual(int zoom);
			void repintadoImagen();
			void zoomImagenVentana(float ancho, float alto);
			void zoomImagen(int tamanhoImag);
		private:
			void aplicaOpcionesZoom();
			//Atributos
			double anchoRedimen, altoRedimen;
			double zoomActual;
			ImageCells *imagenOvocitos;
			Glib::RefPtr<Gdk::Pixbuf> copiaPixbuf;
			PanelDibujado *panelDibujo;
			DibujadoCelula *capaCelula;
			Rejilla *rejilla;			
	};
#endif //_SISTEMADIBUJADO_H_
