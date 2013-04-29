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

#include "Rejilla.h"

/**
 Constructor.
 */
Rejilla::Rejilla()
{
	bordeAct = visibleCapaRejilla = false;
	numFilas = numColumnas = numPuntos = anchoR = altoR = ancho = alto = 0;
	limISR = limISG = limISB = limDIR = limDIG = limDIB = 0;
	colRejR = colRejG = colRejB = 0;
	grosBordeRej = grosRej = separPun = 0;
	divisor = 65536;
	puntosRejilla.clear();
	bordeMaxY = bordeMaxX = bordeMinY = bordeMinX = 0;
	zoomRej = 1;
}

/**
 Destructor.
 */
Rejilla::~Rejilla()
{
	
}

/**
 Devuelve el valor maximo del borde x.
 @return int.
 */
int Rejilla::getBordeMaxX()
{
	return bordeMaxX;
}

/**
 Devuelve el valor maximo del borde y.
 @return int.
 */
int Rejilla::getBordeMaxY()
{
	return bordeMaxY;
}

/**
 Devuelve el valor minimo del borde x.
 @return int.
 */
int Rejilla::getBordeMinX()
{
	return bordeMinX;
}

/**
 Devuelve el valor minimo del borde y
 @return int.
 */
int Rejilla::getBordeMinY()
{
	return bordeMinY;
}

/**
 Devuelve el valor de la variable bordeAct si es verdadero el borde esta activo,
 falso en caso contrario.
 @return Verdadero si esta activo, falso si no esta activo.
 */
bool Rejilla::getBordeActivo()
{
	return bordeAct;
}

/**
 Devuelve el valor de la variable visibleCapaRejilla si vale true la rejilla esta
 activa, false en caso contrario.
 @return bool.
 */
bool Rejilla::getVisibleCapaRejilla()
{
	return visibleCapaRejilla;
}

/**
 Devuelve la separacion de puntos de la rejilla.
 @return int.
 */
int Rejilla::getSeparPuntos()
{
	return (int)separPun;
}

/**
 Devuelve el numero de filas de la rejilla.
 @return int.
 */
int Rejilla::getNumFilas()
{
	return numFilas;
}

/**
 Devuelve el numero de las columnas de la rejilla.
 @return int.
 */
int Rejilla::getNumColumnas()
{
	return numColumnas;
}

/**
 Devuelve el numero de puntos de la rejilla.
 @return int.
 */
int Rejilla::getNumPuntos()
{
	return numPuntos;
}

/**
 Devuelve el ancho de la rejilla.
 @return int.
 */
int Rejilla::getAncho()
{
	return ancho;
}

/**
 Devuelve el alto de la imagen.
 @return int.
 */
int Rejilla::getAlto()
{
	return alto;
}

/**
 Devuelve el alto de la rejilla.
 @return int.
 */
int Rejilla::getAltoRej()
{
	return altoR;
}

/**
 Devuelve el ancho de la rejilla.
 @return int.
 */
int Rejilla::getAnchoRej()
{
	return anchoR;
}

/**
 Devuelvel el vector de la rejilla.
 @return vector<vector<int>>.
 */
vector<vector<int> > *Rejilla::getVectorRejilla()
{
	return &puntosRejilla;
}

/**
 Devuelve el id de la rejilla.
 @return int.
 */
int Rejilla::getID()
{
	return idRej;
}

/**
 Establece el zoom de la rejilla.
 @param zoom, double.
 */
void Rejilla::setZoomRejilla(double zoom)
{
	zoomRej = (zoom/10);
}

/**
 Establece la visibilidad de la capa, en caso de true visible, caso contrario false.
 @param vc, bool.
 */
void Rejilla::setVisibleCapaRejilla(bool vc)
{
	visibleCapaRejilla = vc;
}

/**
 Establece si esta activo el borde con la regilla completa.
 @param cond, bool.
 */
void Rejilla::setBordeComp(bool cond)
{
	bordeAct = cond;
}

/**
 Devuelve el contexto de la rejilla.
 @return Cairo::RefPtr<Cairo::Context>. 
 */
Cairo::RefPtr<Cairo::Context> Rejilla::getCairoContext()
{
	return crRej;
}
		
/**
 Establece el color del limite izquiero y superior.
 @param is, Gdk::Color.
 */
void Rejilla::setLimIS(Gdk::Color is)
{
	limISR = (is.get_red()/divisor);
	limISG = (is.get_green()/divisor);
	limISB = (is.get_blue()/divisor);
}

/**
 Establece el color del limite derecho e inferior.
 @param di, Gdk::Color.
 */
void Rejilla::setLimDI(Gdk::Color di)
{
	limDIR = (di.get_red()/divisor);
	limDIG = (di.get_green()/divisor);
	limDIB = (di.get_blue()/divisor);
}

/**
 Establece el color de la rejilla.
 @param rej, Gdk::Color.
 */
void Rejilla::setColRej(Gdk::Color rej)
{
	colRejR = (rej.get_red()/divisor);
	colRejG = (rej.get_green()/divisor);
	colRejB = (rej.get_blue()/divisor);
}

/**
 Establece el grosor de la rejilla.
 @param gr, double.
 */
void Rejilla::setGrosRej(double gr)
{
	grosRej = gr;
}

/**
 Establece la separacion entre los puntos de la rejilla.
 @param sp, double.
 */
void Rejilla::setSeparPun(double sp)
{
	separPun = sp;
}

/**
 Establece el numero de filas.
 @param nf, int.
 */
void Rejilla::setNumFilas(int nf)
{
	numFilas = nf;
}

/**
 Establece el numero de columnas.
 @param nc, int.
 */
void Rejilla::setNumColumnas(int nc)
{
	numColumnas = nc;
}

/**
 Establece el alto de la imagen.
 @param al, int.
 */
void Rejilla::setAlto(int al)
{
	alto = al;
}

/**
 Establece el ancho de la imagen.
 @param ac,int.
 */
void Rejilla::setAncho(int ac)
{
	ancho = ac;
}

/**
 Establece el ancho de la rejilla.
 @param ac,int
 */
void Rejilla::setAnchoRej(int acR)
{
	anchoR = acR;
}

/**
 Establece el alto de la rejilla.
 @param al, int.
 */
void Rejilla::setAltoRej(int alR)
{
	altoR = alR;
}

/**
 Establece el grosor del borde.
 @param gbr, double.
 */
void Rejilla::setGrosBordeRej(double gbr)
{
	grosBordeRej = gbr;
}

/**
 Establece el contexto de la regilla.
 @param surfaceRejilla, Cairo::RefPtr<Cairo::ImageSurface>.
 */
void Rejilla::setContexRejilla(Cairo::RefPtr<Cairo::ImageSurface> surfaceRejilla)
{
	
	crRej = Cairo::Context::create(surfaceRejilla);
	crLat = Cairo::Context::create(surfaceRejilla);
}

/**
 Establece el vector con los estados de maduracion.
 @param est, vector<EstadoCelula>.
 */
void Rejilla::setEstado(vector<EstadoCelula> &est)
{
	estados = &est;
}

/**
 Establece el identificador de la rejilla.
 @param id, int.
 */
void Rejilla::setID(int id)
{
	idRej = id;
}

/**
 Calcula la rejilla.
 */
void Rejilla::calculaRejilla()
{
	double tam1, tam2, tam3, dist;
	double acumDistX, acumDistY;
	double x, y;
	bool tamInicio = false;

	//Distancia
	dist = separPun;
	
	//tam1 1/4
	tam1 = (0.25 * dist);
	//tam2 3/4
	tam2 = (0.75 * dist);
	//tam3 raiz de 3 partido de dos
	tam3 = ((sqrt(3) / 2) * dist);
	
	if(altoR != 0 && anchoR != 0)
	{
		numColumnas = ((anchoR - (tam1 + tam2)) / dist) + 1;
		numFilas = ((altoR - tam3) / tam3) + 1;

		numPuntos = numColumnas * numFilas;

		anchoR = tam1 + tam2 + ((numColumnas - 1) * dist);
		altoR = tam3 + ((numFilas - 1) * tam3);
	}
	else
	{
		anchoR = tam1 + tam2 + ((numColumnas - 1) * dist);
		altoR = tam3 + ((numFilas - 1) * tam3);

		numPuntos = numColumnas * numFilas;
	}
	
	x = (ancho/2) - (anchoR/2);
	y = (alto/2) - (altoR/2);

	bordeMaxX = x + anchoR;
	bordeMaxY = y + altoR;
	bordeMinX = x;
	bordeMinY = y;

	//Vaciamos el vector
	puntosRejilla.clear();

	puntosRejilla.resize(numFilas);
	
	//Creamos el vector que contendra los vectores de puntos
	for(int i = 0; i < numFilas; i++)
	{
		puntosRejilla[i].resize(numColumnas + 1);
	}
	
	acumDistY = y + tam3/2;
		
	for(int i = 0; i < numFilas; i++)
	{
		puntosRejilla[i][0] = acumDistY;
		
		if(tamInicio)
		{
			acumDistX = tam2 + x;
			puntosRejilla[i][1] = acumDistX;
			tamInicio = false;
		}
		else
		{
			acumDistX = tam1 + x;
			puntosRejilla[i][1] = acumDistX;
			tamInicio = true;
		}
		
		for(int j = 2; j < numColumnas + 1; j++)
		{
			acumDistX = acumDistX + dist;
			
			puntosRejilla[i][j] = acumDistX;
		}
			
		//Saltamos a la siguiente linea
		acumDistY = acumDistY + tam3;
			
	}
}

/**
 Pinta la rejilla.
 */
void Rejilla::pintaRejilla()
{
	if(visibleCapaRejilla)
	{
		int numCol, numFil;
	
		crRej->save();
		crRej->restore();
	
		//Ancho de la linea de dibujo
		crRej->set_line_width(grosRej * zoomRej);
	
		//Color del punto
		crRej->set_source_rgba(colRejR, colRejG, colRejB, 1);

		numCol = puntosRejilla[0].size();
		numFil = puntosRejilla.size();
	
		for(int i = 0; i < numFil; i++)
		{
			//puntosRejilla[0][y,x,x,....,x];
			crRej->move_to(puntosRejilla[i][1] * zoomRej, puntosRejilla[i][0] * zoomRej);
		
			for(int j = 2; j < numCol; j = j + 2)
			{
				crRej->line_to(puntosRejilla[i][j] * zoomRej, puntosRejilla[i][0] * zoomRej);
				crRej->move_to(puntosRejilla[i][j + 1] * zoomRej, puntosRejilla[i][0] * zoomRej);
			}

			if(fmod((double)(numCol - 1), 2) != 0)
			{
				crRej->arc(puntosRejilla[i][numCol - 1] * zoomRej, puntosRejilla[i][0] * zoomRej,
					       (1 * zoomRej), 0, 2 * M_PI);
			}
			//Pintamos linea de la rejilla
			crRej->stroke();
		}
	}
}

/**
 Pinta el borde de la rejilla.
 */
void Rejilla::pintaBordeRejilla()
{	
	if(bordeAct)
	{
		int x, y;
	
		x = (ancho/2) - (anchoR/2);
		y = (alto/2) - (altoR/2);		

		//Grosor de la linea
		crLat->set_line_width(grosBordeRej * zoomRej);
		//Color limite izquierdo superior
		crLat->set_source_rgba(limISR,limISG,limISB,1);
		
		crLat->move_to(x * zoomRej, (y + altoR) * zoomRej);
		crLat->line_to(x * zoomRej, y * zoomRej);
		crLat->line_to((x + anchoR) * zoomRej, y * zoomRej);
	
		//Pintado
		crLat->stroke();
	
		//Color limite derecho inferior
		crLat->set_source_rgba(limDIR,limDIG,limDIB,1);
		
		crLat->move_to((x + anchoR) * zoomRej , y * zoomRej);
		crLat->line_to((x + anchoR) * zoomRej, (y + altoR) * zoomRej);
		crLat->line_to(x * zoomRej, (y + altoR) * zoomRej);
	
		//Pintado
		crLat->stroke();
	}
}
