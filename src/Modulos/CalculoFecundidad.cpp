/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoFecundidad.cpp
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

#include "CalculoFecundidad.h"
#include "Interfaz/PanelFecundidad.h"

/**
 Constructor.
 */
CalculoFecundidad::CalculoFecundidad()
{
	calibracion = 1;

	int aux = 0;
	
	for(int i = 0; i < 41; i++)
	{
		clasesDiametros.push_back(aux);
		factorCorreccion.push_back(1.0);
		aux = aux + 25;
	}
}

/**
 Destructor.
 */
CalculoFecundidad::~CalculoFecundidad()
{
	
}

/**
 Establece la calibracion.
 @param calib, double que contiene la calibracion.
 */
void CalculoFecundidad::setCalibracion(double calib)
{
	calibracion = calib;
}

/**
 Asigna la lista de individuos que contiene los datos de las n imagenes a procesar.
 @param lv, referencia del ListadoIndividuo.
 */
void CalculoFecundidad::setListaIndividuos(ListadoIndividuo &lv)
{
	listIndiv = &lv;
}

/**
 Asigna el objeto de la rejilla.
 @param rej, referencia de la rejilla.
 */
void CalculoFecundidad::setRejilla(Rejilla &rej)
{
	rejilla = &rej;
}

/**
 Asigna el objeto del Panel de Fecundidad.
 @param pf, referencia de PanelFecundidad.
 */
void CalculoFecundidad::setPanelFecundidad(PanelFecundidad &pf)
{
	pfecundidad = &pf;
}

/**
 Asgina el objeto de configuracion y obtiene el vector de estados definidos en el 
 sistema.
 @param cfg, referencia de ConfigGovocitos.
 */
void CalculoFecundidad::setConfiguracion(ConfigGovocitos &cfg)
{
	int numEstados;

	estadosEnUso.clear();
	configuracion = &cfg;

	estados = *configuracion->getDatosEstados();

	numEstados = estados.size();
	
	for(int i = 0; i < numEstados; i++)
	{
		if(estados[i].getEnUso())
		{
			estadosEnUso.push_back(i);
		}
	}
}

/**
 Asigna el objeto que guarda los resultados de fecundidad.
 @param lri referencia de ResulFecundidad.
 */
void CalculoFecundidad::setListaResultadosImg(ResultFecundidad &lri)
{
	listResultados = &lri;
}

/**
 Establece la clase de diametros para ver en que subgrupos se dividen los diametros.
 @param clDiam, vector de enteros con las clases de los diametros
 */
void CalculoFecundidad::setClasesDiametros(vector<int> clDiam)
{
	clasesDiametros.clear();

	clasesDiametros = clDiam;
}

/**
 Establece el factor de corrección de los diámetros.
 @param fc, vector de doubles que contiene los factores de corrección.
 */
void CalculoFecundidad::setFactorCorreccion(vector<double> fc)
{
	factorCorreccion.clear();

	factorCorreccion = fc;
}

/**
 Calcula los puntos de la rejilla contenidos dentro de cada celula y filtra las
 celulas que no se encuentran dentro de la rejilla. Tambien asigna el valor del 
 area y el diametro a cada una de las celulas.
 */
void CalculoFecundidad::calculoPuntosCelulas()
{
	vector<int> estSelec;
	int numEstados;
	int numImagenAnaliz;
	vector<Celula> celulaAceptedEst;
	vector<Celula> celulaAceptedGrid;
	vector<Celula> celulaAceptedNucleo;
	//Conteo del numero de objetos total
	int numTotalObjetos = 0;

	numEstados = estadosEnUso.size();
	
	//Para seleccionar todos los estados introducimos el indice de todos
	for(int i = 0; i < numEstados; i++)
	{
		estSelec.push_back(estadosEnUso[i]);
	}

	numImagenAnaliz = listIndiv->getNumXmlAnalizados();

	listResultados->setNumImagenes(numImagenAnaliz);

	//Hacemos un bucle para calcular los datos de todas las imagenes
	for(int i = 0; i < numImagenAnaliz; i++)
	{
		ListadoCelulas *lc;
		int numCelDentroGridRojo;
		ResultadosImagen resultImg;

		lc = listIndiv->getCelulasVector(i);

		//Inicializamos el numero de resultados
		resultImg.inicializarNumPunObj(numEstados);

		//Calculamos los diametros para cada celula
		int numCelulas;

		numCelulas = lc->getNumCelulas();

		for(int j = 0; j < numCelulas; j++)
		{
			Celula *cell;
			vector<double> diametRes;

			cell = lc->getCelula(j);

			if(cell->getEstadoCelula() != "outimage")
			{
				diametRes = CalculoMorfologico::diametroAreaFormula(*cell);

				cell->setDiametroCell(diametRes[1]);
				cell->setAreaCelula(diametRes[0]);
				
				//Solo diametro de celulas con nucleo y con diametro entre 100 y 750
				if(cell->getClaseCelula() == "cn" && (diametRes[1] >= 100) && (diametRes[1] <= 750))
				{
					resultImg.setDiametros(diametRes[1]);
				}
			}
		}
		
		//Eliminamos las celulas que no tienen estado
		celulaAceptedEst = CalculoEstadistico::celulasCoincidentesEstado(estados, estSelec, *lc);
	
		//Comprobamos si la rejilla tiene de separacion =! 1 en caso de que sea 1 se usara el area de la celula
		if(rejilla->getSeparPuntos() == 1)
		{
			//Pasamos los datos al vector de resultados
			for(int y = 0; y < numEstados; y++)
			{
				int numCellAcept;
				int numCelTotal = 0;
				double numPuntoTotal = 0;
			
				numCellAcept = celulaAceptedEst.size();
			
				string estado1 = estados[estSelec[y]].getEtiquetaClasificacion();
				
				for(int j = 0; j < numCellAcept; j++)
				{
					if(estado1 == celulaAceptedEst[j].getEstadoCelula())
					{
						numPuntoTotal = numPuntoTotal + celulaAceptedEst[j].getAreaCelula();
						numCelTotal++;
					}
				}

				resultImg.setnumPunAreaNoUse(areaNoUsada(*lc));
				
				//guardamos los datos para cada estado
				resultImg.setNumObj(numCelTotal, y);
				resultImg.setNumPun(numPuntoTotal, y);

				numTotalObjetos = numTotalObjetos + numCelTotal;
			}
		}
		else
		{
			//Eliminamos las celulas que no entran dentro del borde
			celulaAceptedGrid = CalculoEstadistico::puntosDentroLimite(rejilla->getBordeMaxX(), rejilla->getBordeMaxY(),
				                                                       rejilla->getBordeMinX(), rejilla->getBordeMinY(),
				                                                       numCelDentroGridRojo, celulaAceptedEst);

			int numCelAceptados = celulaAceptedGrid.size();

			int aciertosIndiv[numCelAceptados];

			for(int j = 0; j < numCelAceptados; j++)
			{
				aciertosIndiv[j] = 0;
			}
			
			//Calculamos los puntos dentro de cada celula
			CalculoEstadistico::calculoPuntosDentroRejilla(aciertosIndiv, celulaAceptedGrid, 
				                                           *rejilla->getVectorRejilla());

			//Pasamos los datos al vector de resultados
			for(int y = 0; y < numEstados; y++)
			{
				int numCellAcept;
				int numCelTotal = 0;
				int numPuntoTotal = 0;
			
				numCellAcept = celulaAceptedGrid.size();
			
				string estado1 = estados[estSelec[y]].getEtiquetaClasificacion();
				
				for(int j = 0; j < numCellAcept; j++)
				{
					if(estado1 == celulaAceptedGrid[j].getEstadoCelula())
					{
						numPuntoTotal = numPuntoTotal + aciertosIndiv[j];
					}
				}

				numCelTotal = CalculoEstadistico::objetosDentroLimite(rejilla->getBordeMaxX(), rejilla->getBordeMaxY(),
				                                                      rejilla->getBordeMinX(), rejilla->getBordeMinY(),
					                                                  estado1, celulaAceptedGrid);

				resultImg.setnumPunAreaNoUse(areaNoUsada(*lc));
				
				//guardamos los datos para cada estado
				resultImg.setNumObj(numCelTotal, y);
				resultImg.setNumPun(numPuntoTotal, y);

				numTotalObjetos = numTotalObjetos + numCelTotal;
			}
		}

		//Añadimos el objeto resultado de la imagen a la lista de resultados
		listIndiv->setResultadoImagenes(resultImg);
	}

	listResultados->setNumOvocitos(numTotalObjetos);
}

/**
 Calcula el valor de k para los diametros obtenidos por histologia.
 Momento 1 = sumatorio de todos los diametros / numero total de celulas||||Media aritmetica
 Momento 2 = ((sum(Diametros exp 3)/n)exp1/3
 K = sqrt((m2/m1) exp 3)
 */
void CalculoFecundidad::calculaValorDeK()
{
	double momento1, momento2, kValue;
	vector<double> diametros;
	vector<double> frecuenciaRelativa(clasesDiametros.size(),0);
	double numOvocitos;
	int numDiam;
	int numTotalOvocitos;

	numOvocitos = momento1 = momento2 = 0.0;
	numTotalOvocitos = 0;

	//Calculamos los diametros ajustados
	diametros = calculoDiametrosAjustados();
	
	numDiam = diametros.size();

	//Calculamos momento 2
	for(int i = 0; i < numDiam; i++)
	{
		double sizeCel;

		sizeCel = pow((double)clasesDiametros[i], 3);
		
		momento2 = momento2 + (diametros[i] * sizeCel * factorCorreccion[i]);
		numOvocitos = numOvocitos + (diametros[i] *factorCorreccion[i]);
		numTotalOvocitos = numTotalOvocitos + diametros[i];
	}

	//Calculamos momento 1
	for(int i = 0; i < numDiam; i++)
	{
		//Sumatorio de todos los diametros del momento 1
		momento1 = momento1 + (diametros[i] * clasesDiametros[i] * factorCorreccion[i]);
	}
	
	//Finalizamos calculo momento1
	momento1 = momento1 / numOvocitos;

	//Finalizamos el calculo del momento 2
	momento2 = momento2 / numOvocitos;
	momento2 = cbrt(momento2);
	//Calculo de K
	kValue = sqrt(pow((momento2 / momento1), 3));

	//Establecemos valor de k
	listResultados->setValorK(kValue);

	//Calculamos las frecuencias 
	for(int i = 0; i < numDiam; i++)
	{
		if(diametros[i] != 0)
		{
			frecuenciaRelativa[i] = diametros[i] / numTotalOvocitos;
		}
		else
		{
			frecuenciaRelativa[i] = diametros[i];
		}
	}

	//Pasamos las frecuencias de los diametros para el calculo del histograma
	pfecundidad->setFrecuenciaDiametros(frecuenciaRelativa);	

	//Establecemos el tipo de calculo del valor K
	listResultados->setMetodoCalculo("Hist");
}

/**
 Calcula el area que ocupa la rejilla en cm x cm.
 */
void CalculoFecundidad::calculoAreaRejilla()
{
	double areaR;

	//Ancho x Alto
	if(rejilla->getSeparPuntos() == 1)
	{
		areaR = rejilla->getAlto() * rejilla->getAncho();
	}
	else
	{
		areaR = rejilla->getAltoRej() * rejilla->getAnchoRej();
	}
	

	//Correccion con el factor de correlacion de pixel -> micra
	areaR = areaR * pow(calibracion, 2);

	//Pasamos a centimetros cuadrados 10000exp2
	areaR = areaR / 100000000;
	
	listResultados->setAreaRejilla(areaR);

	listResultados->setIdRejilla(rejilla->getID());
}

/**
 Calcula los datos finales para obtener la fecundidad de cada uno de los estados
 finales definidos en el sistema.
 */
void CalculoFecundidad::calculoFecundidad()
{
	int numEstados, numImag;
	ResultadosImagen resulImg;
	double aux;
	
	numEstados = estadosEnUso.size();
	numImag = listIndiv->getNumResultadoImagenes();
	listResultados->inicializaResulFec(numEstados);

	//Declaramos el vector de acumulacion de resultados
	vector<double> totArea(numEstados, 0);
	vector<double> totNum(numEstados, 0);
	
	//Obtenemos la suma del area y el numero de objetos de cada estado para todas las imagenes
	double puntosRejilla;

	for(int i = 0; i < numImag; i++)
	{
		if(rejilla->getSeparPuntos() == 1)
		{
			puntosRejilla = rejilla->getAncho() * rejilla->getAlto();
		}
		else
		{
			puntosRejilla = rejilla->getNumPuntos();
		}
			
		resulImg = listIndiv->getResultadosImg(i);
		
		aux = 0.0;

		//Restamos el area no usada en la imagen
		puntosRejilla = puntosRejilla - resulImg.getnumPunAreaNoUse();

		for(int j = 0; j < numEstados; j++)
		{
			aux = resulImg.getNumPun(j);
			
			if(aux)
			{
				aux = aux / puntosRejilla;
			}
			totArea[j] = totArea[j] + aux;

			//Numero celulas
			totNum[j] = totNum[j] + resulImg.getNumObj(j);
		}
	}		

	//Calculamos la media de las areas y los puntos para cada estado
	for(int i = 0; i < numEstados; i++)
	{
		if(totArea[i] && totNum[i])
		{
			double fecEst;
			
			totArea[i] = totArea[i] / numImag;
			totNum[i] = totNum[i] / numImag;

			fecEst = calculaFecunEstado(totArea[i], totNum[i]);

			listResultados->setFecundidadEst(fecEst, i);
		}
	}
}

/**
 Calcula la fecundidad para un estado en concreto, si se quiere obtener la fecundidad
 de todo el individuo se le pasa la media de puntos y objetos, si en cambio queremos
 calcular la media para un solo individuo se le pasa el numeroPuntos y el numero de
 objetos de la imagen deseada.
 @param mediaPuntos, la media de los puntos obtenidos en el conteo para el individuo.
 @param mediaObjetos, la media de objetos obtenidos en el conteo para el individuo.
 @return double, que contiene el valor de la fecundidad.
 */
double CalculoFecundidad::calculaFecunEstado(double mediaPuntos, double mediaObjetos)
{
	double fecundidad, valorScherle, valorK, valorBeta, areaR, volumenOvario;

	volumenOvario = areaR = valorBeta = fecundidad = valorScherle = valorK = 0.0;
	
	//Datos necesarios para la fecundidad
	//1/B
	valorBeta = listIndiv->getValorBeta();
	//scherle
	valorScherle = listIndiv->getValorScherle();
	//Volumen ovario
	volumenOvario = valorScherle * (listIndiv->getFormolFresco() *listIndiv->getPesoOvarioFresco());
	//Valor K
	valorK = listResultados->getValorK();
	//Area rejilla
	areaR = listResultados->getAreaRejilla();

	fecundidad = ((valorBeta * valorK * sqrt(pow((mediaObjetos / areaR), 3))) / sqrt(mediaPuntos)) * volumenOvario;

	return fecundidad;
}

/**
 Clasifica los diametros obtenidos en grupos de 25 en 25, de esta forma se obtiene
 la frecuencia de los diametros para una determinada clase.
 @return vector<double> vector que contiene las frecuencias obtenidas por clase, es
 decir en la posicion 0 los diametros en rango 0, en la posicion 1 los diametros entre
 1 y 25 en la posicion 2 los diametros entre 26 y 50 y asi hasta el rango 1000.
 */
vector<double> CalculoFecundidad::calculoDiametrosAjustados()
{
	vector<double> frecuenDiam(clasesDiametros.size(),0);	
	vector<double> diametros;
	int numClassDiam = clasesDiametros.size();
	int numImg;

	numImg = listIndiv->getNumResultadoImagenes();
	
	for(int i = 0; i < numImg; i++)
	{
		ResultadosImagen resulImg;
		int numDiam;
	
		resulImg = listIndiv->getResultadosImg(i);

		diametros = resulImg.getDiametros();
		numDiam = diametros.size();

		//Calculamos la frecuencia de repeticion de cada imagen y diametro
		for(int j = 0; j < numDiam; j++)
		{
			double diamActual;
			int h = 0;
			
			diamActual = diametros[j];

			while(h < numClassDiam && (diamActual >= clasesDiametros[h]))
			{
				h++;
				
			}

			if(h < numClassDiam)
			{
				if(h != 0 && diamActual >= clasesDiametros[h-1] && diamActual <= clasesDiametros[h])
				{
					frecuenDiam[h]++;
				}
				else if(h == 0 && diamActual <= clasesDiametros[h] && diamActual >= 100)
				{
					frecuenDiam[h]++;
				}
			}
		}
	}
	
	return  frecuenDiam;
}

/**
 Calcula los diametros ajustados para diametros obtenidos a traves de los diametros
 de la lupa
 @param diametros, vector de doubles que contiene los diametros de la lupa.
 @return vector<double>, devuelve un vector con los diametros ajustados calculados.
 */
vector<double> CalculoFecundidad::calculoDiametrosAjustadosLupa(vector<double> diametros)
{
	vector<double> frecuenDiam(clasesDiametros.size(),0);	
	int numClassDiam = clasesDiametros.size();
	int numDiam;
	
	numDiam = diametros.size();

	//Calculamos la frecuencia de repeticion de cada imagen y diametro
	for(int j = 0; j < numDiam; j++)
	{
		double diamActual;
		int h = 0;
			
		diamActual = diametros[j];

		cout<<diamActual<<endl;
		while(h < numClassDiam && (diamActual >= clasesDiametros[h]))
		{
			h++;		
		}

		if(h < numClassDiam)
		{
			if(h != 0 && diamActual >= clasesDiametros[h-1] && diamActual <= clasesDiametros[h])
			{
				frecuenDiam[h]++;
			}
			else if(h == 0 && diamActual <= clasesDiametros[h] && diamActual >= 100)
			{
				frecuenDiam[h]++;
			}
		}
	}
	
	return  frecuenDiam;
}

/**
 Calcula el valor de K utilizando los diametros de lupa.
 @param diam, vector de double que contiene los diametros divididos en subgrupos.
 */
void CalculoFecundidad::calculaValorDeKLupa(vector<double> diam)
{
	double momento1, momento2, kValue;
	vector<double> diametros;
	vector<double> frecuenciaRelativa(clasesDiametros.size(),0);
	double numOvocitos;
	int numDiam;
	int numTotalOvocitos;

	numOvocitos = momento1 = momento2 = 0.0;
	numTotalOvocitos = 0;

	//Calculamos los diametros ajustados
	diametros = calculoDiametrosAjustadosLupa(diam);
	
	numDiam = diametros.size();

	//Calculamos momento 2
	for(int i = 0; i < numDiam; i++)
	{
		double sizeCel;

		sizeCel = pow((double)clasesDiametros[i], 3);
		
		momento2 = momento2 + (diametros[i] * sizeCel);
		numOvocitos = numOvocitos + (diametros[i]);
		numTotalOvocitos = numTotalOvocitos + diametros[i];
	}

	//Calculamos momento 1
	for(int i = 0; i < numDiam; i++)
	{
		//Sumatorio de todos los diametros del momento 1
		momento1 = momento1 + (diametros[i] * clasesDiametros[i]);
	}
	
	//Finalizamos calculo momento1
	momento1 = momento1 / numOvocitos;

	//Finalizamos el calculo del momento 2
	momento2 = momento2 / numOvocitos;
	momento2 = cbrt(momento2);
	//Calculo de K
	kValue = sqrt(pow((momento2 / momento1), 3));

	//Establecemos valor de k
	listResultados->setValorK(kValue);

	//Calculamos las frecuencias 
	for(int i = 0; i < numDiam; i++)
	{
		if(diametros[i] != 0)
		{
			frecuenciaRelativa[i] = diametros[i] / numTotalOvocitos;
		}
		else
		{
			frecuenciaRelativa[i] = diametros[i];
		}
	}

	//Pasamos las frecuencias de los diametros para el calculo del histograma
	pfecundidad->setFrecuenciaDiametros(frecuenciaRelativa);	

	listResultados->setMetodoCalculo("Lupa");
}

/**
 Contabiliza el area no usada de la imagen para descartarla del calculo de fecundidad.
 @param lc, objeto de la clase ListadoCelulas que contiene todas las células identificadas.
 @return double, devuelve el area no usada.
 */
double CalculoFecundidad::areaNoUsada(ListadoCelulas &lc)
{
	int numCelulas;
	vector<Celula> regionOut;
	double areaNotUse;
	int *aciertosIndiv;

	numCelulas = lc.getNumCelulas();
	areaNotUse = 0.0;

	//Obtenemos solo las regiones vacias
	for(int i = 0; i < numCelulas; i++)
	{
		Celula cell;

		cell = *lc.getCelula(i);

		if(cell.getEstadoCelula() == "outimage")
		{
			regionOut.push_back(cell);
		}
	}

	if(regionOut.size())
	{
		bool calculoDatos = false;
		int numPolAceptados;
		
		//Comprobamos si la rejilla tiene de separacion =! 1 en caso de que sea 1 se usara el area de la celula
		if(rejilla->getSeparPuntos() == 1)
		{
			numPolAceptados = regionOut.size();

			aciertosIndiv = new int [numPolAceptados];

			for(int i = 0; i < numPolAceptados; i++)
			{
				aciertosIndiv[i] = 0;
			}
				
			calculoDatos = CalculoEstadistico::calculoRejillaSepar1(aciertosIndiv, regionOut);
		}
		else
		{
			numPolAceptados = regionOut.size();

			aciertosIndiv = new int [numPolAceptados];

			for(int i = 0; i < numPolAceptados; i++)
			{
				aciertosIndiv[i] = 0;
			}
				
			calculoDatos = CalculoEstadistico::calculoPuntosDentroRejilla(aciertosIndiv, regionOut,
				                                                          *rejilla->getVectorRejilla());
		}

		if(calculoDatos)
		{
			for(int i = 0; i < numPolAceptados; i++)
			{
				areaNotUse = areaNotUse + aciertosIndiv[i];
			}
		}
	}

	return areaNotUse;
}
