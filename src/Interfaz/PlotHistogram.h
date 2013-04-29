/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PlotHistogram.h
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

#ifndef _PLOTHISTOGRAM_H_
	#define _PLOTHISTOGRAM_H_

	#include <gtkmm.h>
	#include <pangomm.h>

	#include "Utiles.h"

	class PlotHistogram : public Gtk::DrawingArea
	{
		public:
			PlotHistogram(int ancho, int alto, vector<double> frecuencias);
			~PlotHistogram();
			void calcularValoresMaxHistogram();
			virtual bool on_expose_event(GdkEventExpose* event);
			void creaCapaPlot();
			void dibujaHistograma();
			void pintaBarrasHistograma();
		private:
			void pintaTextoPango(int dx, int dy);
			//Atributos
			Cairo::RefPtr<Cairo::Context> cr;
			Cairo::RefPtr<Cairo::ImageSurface> surfacePlot;
			Glib::RefPtr<Pango::Layout> layout;
			int anchoPlot, altoPlot;
			double numX, numY;
			vector<double> frecuenDiam;
			Pango::FontDescription *timesnr_8, *caligua_20_V;
	};
#endif //_PLOTHISTOGRAM_H_
