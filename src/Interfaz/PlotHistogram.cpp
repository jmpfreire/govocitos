/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PlotHistogram.cpp
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

#include "PlotHistogram.h"

/**
 Constructor
 @param ancho, integer que contiene el maximo ancho de la zona de dibujo
 @param alto, integer que contiene el maximo alto de la zona de dibujo
 @param frecuencias, vector de doubles que contiene todas las frecuencias
 acumuladas de los diametros por clase de celula
 */
PlotHistogram::PlotHistogram(int ancho, int alto, vector<double> frecuencias)
{
	anchoPlot = ancho;
	altoPlot = alto;
	frecuenDiam = frecuencias;
	numX = numY = 0;

	timesnr_8 = new Pango::FontDescription("Times new roman 8");
	caligua_20_V = new Pango::FontDescription("Caligula 14");

}

/**
 Destructor
 */
PlotHistogram::~PlotHistogram()
{
	delete timesnr_8;
	delete caligua_20_V;
}

/**
 Calcula los valores maximos a representar en el histograma tanto para el eje x
 como para el eje y
 */
void PlotHistogram::calcularValoresMaxHistogram()
{
	int numDiam;
	double aux;

	aux = 0;

	numDiam = frecuenDiam.size();

	for(int i = 0; i < numDiam; i++)
	{
		if(aux <= frecuenDiam[i])
		{
			aux = frecuenDiam[i];
		}
	}

	numY = Utiles::redondearNDecimales(aux, 3);
	numX = numDiam - 1;
}

/**
 Funcion de refresco, que refresca la vista del histograma en la pantalla
 @param event, evento de tipo expose que contiene la informacion actual de la 
 pantalla
 */
bool PlotHistogram::on_expose_event(GdkEventExpose* event)
{
	int desplazaX, desplazaY;
	
	if(surfacePlot)
	{	
		cr = get_window()->create_cairo_context();
		
		//Obtenemos la zona de dibujado para poder obtener sus medidas 	 
		Gdk::Cairo::rectangle (cr, get_allocation()); 	
		
		//Tamaño de la ventana menos el tamaño de la imagen 	         
		desplazaX = ((get_allocation().get_width() - anchoPlot) / 2);
		desplazaY = ((get_allocation().get_height() - altoPlot) / 2);

		//Trasladamos la imagen al centro de la pantalla
		cr->translate(desplazaX, desplazaY);

		//Dibujamos el texto con pango
		pintaTextoPango(desplazaX, desplazaY);
		
		cr->set_source(surfacePlot, 0, 0);
		
  		cr->paint();
	}  	 
	
	return true;
}

/**
 Crea la capa en la que se pintara el histograma y tambien la capa para la escritura
 con pango
 */
void PlotHistogram::creaCapaPlot()
{
	if(surfacePlot)
	{
		surfacePlot->finish();
	}

	surfacePlot = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, anchoPlot, altoPlot);

	cr = Cairo::Context::create (surfacePlot);

	cr->set_operator(Cairo::OPERATOR_SOURCE);

	layout = create_pango_layout("");	 
  	 
    set_size_request(anchoPlot, altoPlot);
}

/**
 Dibuja el histograma, es decir el eje X y el eje Y con sus divisiones
 */
void PlotHistogram::dibujaHistograma()
{
	double ejeX, ejeY, incX, incY, actX, actY;
	actX = 75;
	actY = 375;
	
	cr->set_line_width(4);
	//Negro
	cr->set_source_rgba(0, 0, 0, 1);

	//Creamos el cuadro del histograma solo 2 ejes a 75 de separacion del borde
	cr->move_to(actX, actY);
	cr->line_to(actX, 25);
	cr->move_to(actX, actY);
	cr->line_to(705, actY);

	//Creamos las divisiones
	//Para el ejex queremos de 0 a 1000 en incremento 25 por lo que necesitaremos 40 divisiones
	//Para el ejey queremos de 0 a 1 en incremento 0.2 por lo que necesitamos 10 divisiones
	ejeX = anchoPlot -100;
	incX = ejeX / numX;
	ejeY = altoPlot - 100;
	incY = ejeY / 10;

	cr->set_line_width(1);
	int contX = -1;
	//Pintamos las separaciones del ejeX
	while(actX <= 705)
	{
		contX++;
		
		cr->move_to(actX, actY);

		if(contX == 4)
		{
			cr->line_to(actX, actY + 10);
			contX = 0;
		}
		else
		{
			cr->line_to(actX, actY + 6);
		}
		
		actX = actX + incX;
	}

	actX = 75;
	//Pintamos las separaciones del ejeY
	while(actY >= 25)
	{
		cr->move_to(actX, actY);
		cr->line_to(actX - 6, actY);

		actY = actY - incY;
	}

	cr->stroke();
}

/**
 Escribe los datos referentes a cada separacion de cada uno de los ejes del histograma
 @param dx, desplazamiento en el eje X cuando cambiamos el tamaño de la ventana
 @param dy, desplazamiento en el eje Y cuando cambiamos el tamaño de la ventana
 */
void PlotHistogram::pintaTextoPango(int dx, int dy)
{
	double ejeX, ejeY, incX, incY, actX, actY;
	double scala;
	double numYcorrect;
	int contX;

	scala = -25.0;

	ejeX = anchoPlot -100;
	incX = ejeX / numX;
	ejeY = altoPlot - 100;
	incY = ejeY / 10;

	actX = 75;
	actY = 375;

	layout->set_font_description(*timesnr_8);

	contX = -1;
	//Rellenado de nombres
	while(actX <= 705)
	{
		scala = scala + 25;		
		contX++;

		if(scala == 0)
		{
			layout->set_markup(Utiles::converString(scala));
			get_window()->draw_layout(Gdk::GC::create(get_window()), 
				        actX + 15, actY + dy + 20, layout);
		}
		else if(contX == 4)
		{
			layout->set_markup(Utiles::converString(scala));
			get_window()->draw_layout(Gdk::GC::create(get_window()), 
				        actX + 10, actY + dy + 20, layout);

			contX = 0;
		}
		
		actX = actX + incX;
	}

	actX = 75;
	numYcorrect = numY/10;
	//Ajustamos la escala para el numero mayor
	scala = numYcorrect - (2 * numYcorrect);
	
	//Pintamos las separaciones del ejeY
	while(actY >= 25)
	{
		scala = scala + numYcorrect;
		layout->set_markup(Utiles::converString(Utiles::redondearNDecimales(scala, 3)));
		get_window()->draw_layout(Gdk::GC::create(get_window()), 
				        actX - 20, actY - 5 + dy, layout);

		actY = actY - incY;
	}

	//Pintamos las referencias del histograma
	layout->set_font_description(*caligua_20_V);
	//Eje X
	layout->set_markup("Oocyte diameter (um)");
	get_window()->draw_layout(Gdk::GC::create(get_window()), 250 + dx, 410 + dy, layout);
	//Eje y
	layout->set_markup("Freq.");
	get_window()->draw_layout(Gdk::GC::create(get_window()), 5, 170 + dy, layout);
	
}

/**
 Pinta las barras del histograma representando los datos que contiene el vector
 frecuenDiam.
 */
void PlotHistogram::pintaBarrasHistograma()
{
	double ejeX, incX, actX, actY;
	double scala;
	int numDiam;

	numDiam = frecuenDiam.size();
	scala = -25.0;

	ejeX = anchoPlot -100;
	incX = ejeX / numX;

	actX = 75;
	actY = 375;
	
	cr->set_line_width(12);
	cr->set_source_rgba(0, 0, 0.8, 1);

	for(int i = 0; i < numDiam; i++)
	{
		if(frecuenDiam[i] != 0)
		{
			double posPaint;

			posPaint= (frecuenDiam[i] * 350);
			posPaint = posPaint / numY;
			cr->move_to(actX + (i * incX), actY);
			cr->line_to(actX + (i * incX), actY - posPaint);
		}
	}

	cr->stroke();
}
