/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoMorfologico.cpp
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

#include "CalculoMorfologico.h"

static double calibracion = 1;

/**
 Establece la calibración.
 @param calib, double que contiene la calibración.
 */
void CalculoMorfologico::setCalibracion(double calib)
{
	calibracion = calib;
}

/**
 Metodo estatico que calcula el perimetro de una celula conociendo la celula.
 @param cell, objeto de la celula de la cual se quiere calcular el perimetro.
 @return int, valor del perimetro de la celula pasada por referencia.
 */
int CalculoMorfologico::calcularPerimetro(Celula &cell)
{
	return calcularPerimetro(*cell.getBordeCellX(), *cell.getBordeCellY());
}

/**
 Metodo estatico que calcula el perimetro de una celula conociento las coordenadas
 x e y del borde de la misma.
 @param cX, vector de int que contiene las coordenadas x del borde de la celula.
 @param cY, vector de int que contiene las coordenadas y del borde de la celula.
 @return int, valor del perimetro correspondiente a los bordes pasados por parametro.
 */
int CalculoMorfologico::calcularPerimetro(vector<int> cX, vector<int> cY)
{
	int tam;
	double perimetro, hipotenusa;

	tam = cX.size();
	perimetro = 0.0;

	/*Para calcular el perimetro (longitud total de la celula) calculamos el valor
	de la hipotenusa para x e y con respecto a x+1 e y+1*/
	for(int i = 0; i < tam - 1; i++)
	{
		hipotenusa = 0.0;

		hipotenusa = sqrt(pow((double)(cX[i + 1] - cX[i]), 2) + pow((double)(cY[i + 1] - cY[i]), 2));

		perimetro = perimetro + hipotenusa;
	}

	perimetro = perimetro + sqrt(pow((double)(cX[0] - cX[tam - 1]), 2) + pow((double)(cY[0] - cY[tam - 1]), 2));

	//Covertimos a micras
	perimetro = perimetro * calibracion;
	
	return (int)perimetro;
}

/**
 Metodo estatico que calcula la redonde de una celula conociendo la celula y su area.
 @param cell, objeto de la celula de la cual se quiere calcular la redondez.
 @param area, double que contiene el valor del area de la celula a calcular.
 @return vector<double>, devuelve un vector de double en la primera posicion devuelve
 el perimetro y en la segunda posicion devuelve la redondez.
 */
vector<double> CalculoMorfologico::calculoRedondez(Celula &cell, double area)
{
	vector<double> datos;
	double perimetro, redondez, cuadrado;

	redondez = 0.0;
	
	perimetro = calcularPerimetro(cell);

	//Calculamos la redondez
	//R = Perimeter^2/(4pi Area 1.064)
	cuadrado = pow(perimetro,2);
	
	redondez = (1.064 * cuadrado) / (4.0 * M_PI * area);
	
	//Primera posicion guardamos el perimetro
	datos.push_back(perimetro);
	//Segunda posicion guardamos la redondez
	datos.push_back(redondez);
	
	return datos;
}

/**
 Metodo estatico que calcula el centroide de la celula pasada por parametro.
 @param cell, objeto de la celula de la cual se quiere calcular el centroide.
 @return vector<int>, devuelve un vector de int que contiene en la primera posicion
 la coordenada x y en la segunda la coordenada y del centroide de la celula.
 */
vector<int> CalculoMorfologico::calcularCentroide(Celula &cell)
{
	vector<int> centroide;
	int x, y;

	x = (cell.getCoordMaxMin(0) + cell.getCoordMaxMin(1)) / 2;
	y = (cell.getCoordMaxMin(2) + cell.getCoordMaxMin(3)) / 2;

	centroide.push_back(x);
	centroide.push_back(y);

	return centroide;
}

/**
 Metodo estatico que calcula el diametro de una celula calculando previamente el 
 area de la celula. Este area se calcula contando los puntos contenidos dentro de
 la celula. Una vez calculada el area se calcula el radio a traver de la formula 
 r = sqrt(Area/PI). Complejidad O(n ^ k).
 @param datosCelula, objeto de la celula de la cual se quiere calcular el diametro.
 @return double, que contienen el diametro medio calculado a partir del area de la 
 celula.
 */
double CalculoMorfologico::diametroAreaPuntos1(Celula &datosCelula)
{
	int numPuntos, xMedia, yMedia;
	int cMaxMinCel[4];
	double diametro;
	int areaCelula;
	vector<int> *x1;
	vector<int> *y1;
	
	x1 = datosCelula.getBordeCellX();
	y1 = datosCelula.getBordeCellY();
	numPuntos = x1->size();
	
	int cx[numPuntos];
	int cy[numPuntos];

	for(int i = 0; i < numPuntos; i++)
	{
		cx[i] = (*x1)[i];
		cy[i] = (*y1)[i];
	}
	
	areaCelula = 0;
	
	for(int i = 0; i < 4; i++)
	{
		cMaxMinCel[i] = datosCelula.getCoordMaxMin(i);
	}
	
	//Calculamos el centro de la celula
	//(XMax - XMin) / 2 -> resultado + XMin punto medio de coordenada x
	xMedia = ((cMaxMinCel[0] - cMaxMinCel[1]) / 2);
	xMedia = (cMaxMinCel[1] + xMedia);
		
	//(YMax - YMin) / 2 -> resultado + YMin punto medio de coordenada y
	yMedia = ((cMaxMinCel[2] - cMaxMinCel[3]) / 2);
	yMedia = (cMaxMinCel[3] + yMedia);
	
	for(int y = cMaxMinCel[3]; y < cMaxMinCel[2]; y++)
	{
		for(int x = cMaxMinCel[1]; x < cMaxMinCel[0]; x++)
		{
			for(int i = 0; i < numPuntos; i++)
			{
				//Comprobamos si la coordenada cX y cY se encuentra dentro del poligono
				//Cuadrante 1
				if((x <= cx[i] && y >= cy[i]) && (x >= xMedia && y <= yMedia))
				{
					areaCelula++;
					break;
				}
				//Cuadrante 2
				else if((x >= cx[i] && y >= cy[i]) && (x <= xMedia && y <= yMedia))
				{
					areaCelula++;
					break;						
				}
				//Cuadrante 3
				else if((x >= cx[i] && y <= cy[i]) && (x <= xMedia && y >= yMedia))
				{
					areaCelula++;
					break;
				}
				//Cuadrante 4
				else if((x <= cx[i] && y <= cy[i]) && (x >= xMedia && y >= yMedia))
				{
					areaCelula++;
					break;
				}
			}
		}
	}

	areaCelula = areaCelula * pow(calibracion, 2);
	
	diametro = (sqrt((areaCelula/M_PI))) * 2;
	
	return diametro;
}

/**
 Metodo estatico que calcula el diametro de una celula calculando previamente el
 area de la celula usando el algoritmo ScanFillLine complejidad O(n).
 @param datosCelula, objeto de la celula de la cual se quiere calcular el diametro.
 @return double, el diametro de la celula.
 */
double CalculoMorfologico::diametroAreaPuntos2(Celula &datosCelula)
{
	double diametro;
	vector<int> *x1;
	vector<int> *y1;
	int cMaxMinCel[4];
	int numPx, numPy;
	
	x1 = datosCelula.getBordeCellX();
	y1 = datosCelula.getBordeCellY();


	vector<int> x(x1->size());
	vector<int> y(y1->size());
	
	for(int i = 0; i < 4; i++)
	{
		cMaxMinCel[i] = datosCelula.getCoordMaxMin(i);
	}

	numPx = cMaxMinCel[0] - cMaxMinCel[1];
	numPy = cMaxMinCel[2] - cMaxMinCel[3];

	for(unsigned int i = 0; i < x1->size(); i++)
	{
		x[i] = (*x1)[i] - cMaxMinCel[1];
		y[i] = (*y1)[i] - cMaxMinCel[3];
	}
	
	ScanFillLine escaneo(numPy);
	
	//TestCell test(*datosCelula);

	//test.testScanFill();
	
	int areaCelula = escaneo.scanFill(x.size(),x,y);

	areaCelula = areaCelula * pow(calibracion, 2);
	
	diametro = (sqrt((areaCelula/M_PI))) * 2;
	
	return diametro;
}

/**
 Metodo estatico que calculo del diametro de una celula mediante la formujla 
 Area = ((xi*yi+1) - (xi+1*yi))/2. Una vez calculada el area se calcula el radio 
 a traver de la formula r = sqrt(Area/PI). Complejidad O(n).
 @param datosCelula, objeto de la celula de la cual se quiere calcular el diametro.
 @return vector de double, que contiene el area de la celula en la primera posicion
 y el diametro de la celula en la segunda posicion.
 */
vector<double> CalculoMorfologico::diametroAreaFormula(Celula &datosCelula)
{
	int numPuntos;
	double areaCelula;
	double diametro;
	vector<int> *x;
	vector<int> *y;
	vector<double> datos;
	
	x = datosCelula.getBordeCellX();
	y = datosCelula.getBordeCellY();
	numPuntos = x->size();
	areaCelula = 0;
	
	for(int i = 0; i < numPuntos - 1; i++)
	{
		areaCelula =  areaCelula + ( ((*x)[i] * (*y)[i+1]) - ((*x)[i+1] * (*y)[i]) );
	}

	areaCelula =  areaCelula + ( ((*x)[numPuntos-1] * (*y)[0]) - ((*x)[0] * (*y)[numPuntos-1]) );
	
	areaCelula = areaCelula/2;

	if(areaCelula < 0)
	{
		areaCelula = areaCelula * -1;
	}
	areaCelula = areaCelula * pow(calibracion, 2);
	
	diametro = (sqrt((areaCelula/M_PI))) * 2;

	datos.push_back(areaCelula);
	datos.push_back(diametro);
cout<<datos[0]<<endl;	
	return datos;
}

/**
 Metodo estatico que calcula el diametro de una celula calculando la distancia 
 desde el centro a cada unos de los puntos del borde de la celula.
 @param datosCelula, objeto de la celula de la cual se quiere calcular el diametro.
 @return vector de double, que contienen el diametro mas largo (pos3), diametro mas
 corto (pos4) y diametro medio (pos5), en las posiciones 1 y 2 se encuentra el centroide
 de la celula x e y respectivamente.
 */
vector<double> CalculoMorfologico::diametroCentroBorde(Celula &datosCelula)
{
	vector<double> diametro;
	double diamLargo, diamCorto;
	double centro[2];
	int numPuntos;
	vector<int> *x;
	vector<int> *y;
	
	x = datosCelula.getBordeCellX();
	y = datosCelula.getBordeCellY();
	numPuntos = x->size();
	diamLargo = diamCorto = 0;
	double radio[numPuntos];
	
	//Calculamos el centroide
	centroide(*x, *y, centro);

	//Calculamos los radios
	for (int i = 0; i < numPuntos; i++)
	{
		radio[i] = sqrt(((centro [0] - (*x)[i]) * (centro [0] - (*x)[i])) + 
						((centro [1] - (*y)[i]) * (centro [1] - (*y)[i])));

	}

	//El diámetro es el doble del radio.
	diamLargo = 2 * maximo (radio, numPuntos);
	diamCorto = 2 * minimo (radio, numPuntos);

	diamLargo = diamLargo * calibracion;
	diamCorto = diamCorto * calibracion;

	diametro.push_back(centro[0]);
	diametro.push_back(centro[1]);
	diametro.push_back(diamLargo);
	diametro.push_back(diamCorto);
	diametro.push_back((diamLargo + diamCorto)/2);
	diametro.push_back(diamLargo/diamCorto);

	return diametro;
}

/**
 Metodo estatico que calcula el centroide de una celula
 @param coordX, vector de int que contiene las coordenadas x del borde de la celula.
 @param coordY, vector de int que contiene las coordenadas y del borde de la celula.
 @param centro, array de doubles que contendra el centriode centro[0] coordenada
 x y centro[1] coordenada y.
 */
void CalculoMorfologico::centroide(vector<int> coordX, vector<int> coordY, double centro[])
{
	int numPuntos;

	numPuntos = coordX.size();
	centro[0] = centro[1] = 0;
	
	for(int i = 0; i < numPuntos; i++)
	{
		centro[0] += coordX[i];
		centro[1] += coordY[i];
	}
	
	centro[0] /= numPuntos;
	centro[1] /= numPuntos;
}

/**
 Metodo estatico que calcula el radio maximo de la una celula.
 @param vector, array de doubles que contiene todos los radios.
 @param fin, numero de radios.
 @return double, que contiene el radio maximo.
 */
double CalculoMorfologico::maximo(double vector [], unsigned int fin)
{
	double max = vector[0];

	for (unsigned int i = 0; i < fin; i++)
	{
		if (vector[i] > max)
		{
			max = vector[i];
		}
	}
	return max;
}

/**
 Metodo estatico que calcula el radio minimo de una celula.
 @param vector, array de doubles que contiene todos los radios.
 @param fin, numero de radios.
 @return double, que contiene el radio minimo.
 */
double CalculoMorfologico::minimo(double vector[], unsigned int fin)
{
	double min = vector[0];

	for (unsigned int i = 0; i < fin; i++)
	{
		if (vector[i] < min)
		{
			min = vector[i];
		}
	}
	return min;
}
