/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DibujadoCelula.h
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


#include "DibujadoCelula.h"

/**
 Constuctor.
 */
DibujadoCelula::DibujadoCelula()
{
	zoomCelulas = 1;
	celulaModificandose = -1;
	numTotalPolig = 0;
	modificacion = seccionBorrada = manoAlzada = false;
	visibleCapaCelulas = true;
	nuevaCelula = new Celula();
	ediCelR = ediCelG = ediCelB = seleCelR = seleCelG = seleCelB = 0;
	posi1 = posi2 = sinIdCelR = sinIdCelG = sinIdCelB = 0;
	divisor = 65536;
	celulaSeleccionada.clear();
	seleccionMultiple = puntosModif = false;
	for(int i = 0; i < 2; i++)
	{
		modifPos1[i] = 0;
		modifPos2[i] = 0;
	}
}

/**
 Destructor.
 */
DibujadoCelula::~DibujadoCelula()
{
	
}

/**
 Establece el zoom de la capa de celulas.
 @param zoom, double zoom auctual.
 */
void DibujadoCelula::setZoomCelulas(double zoom)
{
	zoomCelulas = (zoom/10);
}

/**
 Borra la nueva celula.
 */
void DibujadoCelula::borrarCelulaNueva()
{
	nuevaCelulaX.clear();
	nuevaCelulaY.clear();
	
	if(nuevaCelula)
	{
		delete nuevaCelula;
	}
	nuevaCelula = new Celula();
}

/**
 Devuelve un puntero de la nueva celula.
 @return Celula, objeto de la clase Celula que contiene la celula nueva.
 */
Celula DibujadoCelula::getNuevaCelula()
{
	return *nuevaCelula;
}

/**
 Devuelve el numero de coordenadas de la celula nueva.
 @return int, tamaño del vector de coordenadas de la celula nueva.
 */
int DibujadoCelula::getTamanhoNuevaCelula()
{
	return nuevaCelulaX.size();
}

/**
 Devuelve el vector de coordenadas X de la nueva celula.
 @return vector<int>, vector con las coordenadas x de la nueva celula.
 */
vector<int> DibujadoCelula::getNuevaCelulaX()
{
	return nuevaCelulaX;
}

/**
 Devuelve el vector de coordenadas Y de la nueva celula.
 @return vector<int>, vector con las coordenadas y de la nueva celula.
 */
vector<int> DibujadoCelula::getNuevaCelulaY()
{
	return nuevaCelulaY;
}

/**
 Devuelve verdadero si los puntos estan marcados.
 @return bool, devuelve el valor de puntosModif. True hay puntos modificados, false
 en caso contrario.
 */
bool DibujadoCelula::getPuntosModif()
{
	return puntosModif;	
}

/**
 Devuelve el valor de la variable que activa el dibujado a mano alzado.
 @return bool, devuelve el valor de manoAlzada. True mano Alzada ativado, false
 caso contrario.
 */
bool DibujadoCelula::getManoAlzada()
{
	return manoAlzada;
}

/**
 Devuelve verdadero si se ha borrado la seccion de modificacion.
 @return bool, devuelve el valor de seccionBorrada. True si hay una seccion borrada
 false en caso contrario.
 */
bool DibujadoCelula::getSeccionBorrada()
{
	return seccionBorrada;
}

/**
 Devuelve verdadero si se esta modificando una celula.
 @return bool, devuelve el valor de modificacion. True si se esta modificando una
 celula, false en caso contrario.
 */
bool DibujadoCelula::getModificacion()
{
	return modificacion;
}

/**
 Devuelve si esta activa la seleccion multiple.
 @return bool, devuelve el valor de seleccionMultiple. True si esta activa la seleccion
 multiple y false en caso contrario.
 */
bool DibujadoCelula::getSelecMultiple()
{
	return seleccionMultiple;
}

/**
 Devuelve una celula seleccionada.
 @param indice, int que contiene la posicion del vector de celulas seleccionadas.
 @return int, numero de celula seleccionada.
 */
int DibujadoCelula::getCelulaSeleccionada(int indice)
{
	return celulaSeleccionada[indice];
}

/**
 Vacia el vector de celulas seleccionadas.
 */
void DibujadoCelula::vaciaVectorCelulaSeleccionada()
{
	celulaSeleccionada.clear();
}

/**
 Devuelve el tamaño del vector de celulas seleccionadas.
 @return int, delvuelve el numero de celulas seleccionadas por el usuario.
 */
int DibujadoCelula::getNumsCelulaSeleccionada()
{
	return celulaSeleccionada.size();
}

/**
 Devuelve la clase de la celula seleccionada.
 @param s, int que contiene el numero de la celula de la que se desea conocer la clase.
 @return string, clase de la celula seleccionada.
 */
string DibujadoCelula::getClaseCelulaSeleccionada(int s)
{
	return coordCelulas->getCelula(s)->getClaseCelula();
}

/**
 Devuelve el estado de la celula seleccionada.
 @param s, int que contiene el numero de la celula de la que se desea conocer el estado.
 @return string, estado de la celula seleccionada. 
 */
string DibujadoCelula::getEstadoCelulaSeleccionada(int s)
{
	return coordCelulas->getCelula(s)->getEstadoCelula();
}

/**
 Establece la clase de la celula indicada por el parametro s.
 @param cl, string que contiene la clase de la celula que queremos establecer.
 @param s, int que contiene el numero de la celula de la cual queremos establecer
 la clase.
 @return string, contiene la nueva clase
 */
string DibujadoCelula::setClaseCelulaSeleccionada(const string &cl, int s)
{
	string clNueva;
	
	if(coordCelulas->getCelula(s)->getClaseCelula() != "outimage")
	{
		coordCelulas->getCelula(s)->setClaseCelula(cl);
		clNueva = cl;
	}
	else
	{
		clNueva = "outimage";
	}

	return clNueva;
}

/**
 Establece el estado de la celula indicada por el parametro s.
 @param cl, string que contiene el estado de la celula que queremos establecer.
 @param s, int que contiene el numero de la celula de la cual queremos establecer
 el estado.
 @return string, contiene el nuevo estado
 */
string DibujadoCelula::setEstadoCelulaSeleccionada(const string &est, int s)
{
	string estNueva;

	if(coordCelulas->getCelula(s)->getEstadoCelula() != "outimage")
	{
		coordCelulas->getCelula(s)->setEstadoCelula(est);
		estNueva = est;
	}
	else
	{
		estNueva = "outimage";
	}

	return estNueva;
}

/**
 Añade una nueva celula al vector.
 @param i, int que contiene el numero de la celula que queremos seleccionar para
 introducirlo en el vector de celulasSeleccionadas.
 */
void DibujadoCelula::setCelulaSeleccionada(int i)
{
	celulaSeleccionada.push_back(i);
}

/**
 Establece el valor de la seleccion multiple.
 @param s, bool si true se activa la seleccion multiple de celulas, false en caso
 contrario.
 */
void DibujadoCelula::setSelecMultiple(bool s)
{
	seleccionMultiple = s;
}

/**
 Establece si se ha borrado la seccion de modificacion.
 @param s, bool si true se ha borrado una seccion de la celula que se esta modificando
 false en caso contrario.
 */
void DibujadoCelula::setSeccionBorrada(bool s)
{
	seccionBorrada = s;
}

/**
 Establece el valor de la variable que activa el dibujado a mano alzado.
 @param valor, bool si true se esta usando la opcion de mano alzada, false en caso
 contrario.
 */
void DibujadoCelula::setManoAlzada(bool valor)
{
	manoAlzada = valor;
}

/**
 Establece el color de edicion.
 @param ec, Gdk::Color que contiene el valor del color de la edicion.
 */
void DibujadoCelula::setEdiCel(Gdk::Color ec)
{
	ediCelR = (ec.get_red()/divisor);
	ediCelG = (ec.get_green()/divisor);
	ediCelB = (ec.get_blue()/divisor);
}

/**
 Establece el color de la celula seleccionada.
 @param sc, Gdk::Color que contiene el valor del color de la seleccion.
 */
void DibujadoCelula::setSeleCel(Gdk::Color sc)
{
	seleCelR = (sc.get_red()/divisor);
	seleCelG = (sc.get_green()/divisor);
	seleCelB = (sc.get_blue()/divisor);
}

/**
 Establece el color de la celula sin determinar.
 @param sic, Gdk::Color que contiene el valor del color de las celulas sin identificarD.
 */
void DibujadoCelula::setSinIdCel(Gdk::Color sic)
{
	sinIdCelR = (sic.get_red()/divisor);
	sinIdCelG = (sic.get_green()/divisor);
	sinIdCelB = (sic.get_blue()/divisor);
}

/**
 Establece el grosor del punto.
 @param gp, double que contiene el grosor del punto de dibujado.
 */
void DibujadoCelula::setGrosPunto(double gp)
{
	grosPunto = gp;
}

/**
 Establece el grosor de la linea.
 @param gl, double que contien el grosor de la linea de dibujao de las celulas.
 */
void DibujadoCelula::setGrosLinea(double gl)
{
	grosLinea = gl;
}

/**
 Establece el contexto a usar.
 @param surfaceCelulas, Cairo::ImageSurface que contiene la superficie de dibujado.
 */
void DibujadoCelula::setContexCelulasPrin(Cairo::RefPtr<Cairo::ImageSurface> surfaceCelulas)
{
	cr1 = Cairo::Context::create(surfaceCelulas);
}

/**
 Establece el contexto de las operaciones secundarias.
 @param surfaceOperaciones, Cairo::ImageSurface que contiene la superficie de dibujado secundario.
 */
void DibujadoCelula::setContexCelulasSecun(Cairo::RefPtr<Cairo::ImageSurface> surfaceOperaciones)
{
	crPuntos = Cairo::Context::create(surfaceOperaciones);
	crLinea = Cairo::Context::create(surfaceOperaciones);
	crModifi = Cairo::Context::create(surfaceOperaciones);
}

/**
 Establece las clases y los estados.
 @param &cl, referencia del vector de ClaseCelula que contiene todas las clases.
 @param &est, referencia del vector De EstadoCelula que contiene todos los estados.
 */
void DibujadoCelula::setClaseEstado(vector<ClaseCelula> &cl, vector<EstadoCelula> &est)
{
	clases = &cl;
	estados = &est;
}

/**
 Establece las coordenadas del poligono.
 @param &lc, referencia a ListadoCelulas que contiene todas las celulas de la imagen.
 */
void DibujadoCelula::setCoordenadasPoligonos(ListadoCelulas &lc)
{
	coordCelulas = &lc;
}

/**
 Hace visible la capa de celulas.
 @param c, bool si es true la capa de celulas es visible, si false no es visible.
 */
void DibujadoCelula::setVisibleCapaCelulas(bool c)
{
	visibleCapaCelulas = c;
}

/**
 Busqueda de la celula que se ha seleccionado
 @param &cX, int const referencia de la coordenada x.
 @param &cY, int const referencia de la coordenada y.
 */
void DibujadoCelula::busquedaCelula(const int &cX, const int &cY)
{
	int x1, y1, xMedia, yMedia, numCelula;
	register int numPoligonos, numCoordPol;
	Celula *cell;
	vector<int> *coordX, *coordY;
	int i(0);
	bool encontrado = false;
	
	numCelula = -1;
	
	//En caso de no tener activa la seleccion multiple vaciamos el vector
	if(!seleccionMultiple)
	{
		celulaSeleccionada.clear();
	}

	//Numero de poligonos 	 
    numPoligonos = coordCelulas->getNumCelulas();

	while((i < numPoligonos) && (!encontrado))
	{		
		//Poligono actual
		cell = coordCelulas->getCelula(i);
		
		//Si el raton se encuentra entre la Max X e Y y la Min X e Y se comprueba 
		//el poligono
		if((cell->getCoordMaxMin(0)) > cX && (cell->getCoordMaxMin(1)) < cX 
		   && (cell->getCoordMaxMin(2)) > cY && (cell->getCoordMaxMin(3)) < cY)
		{
			//(XMax - XMin) / 2 -> resultado + XMin punto medio de coordenada x
			xMedia = (cell->getCoordMaxMin(0) - cell->getCoordMaxMin(1)) / 2;
			xMedia = cell->getCoordMaxMin(1) + xMedia;
		
			//(YMax - YMin) / 2 -> resultado + YMin punto medio de coordenada y
			yMedia = (cell->getCoordMaxMin(2) - cell->getCoordMaxMin(3)) / 2;
			yMedia = cell->getCoordMaxMin(3) + yMedia;

			//Asignamos el numero de coordenadas del poligono
			coordX = cell->getBordeCellX();
			coordY = cell->getBordeCellY();
			numCoordPol = coordX->size();

			//Recorremos el poligono
			for(register int j = 0; j < numCoordPol; j++)
			{
				//Obtenemos las coordenas x e y del poligono
				x1 = (*coordX)[j];
				y1 = (*coordY)[j];
				
				//Comprobamos si la coordenada cX y cY se encuentra dentro del poligono
				//Cuadrante 1
				if((cX <= x1 && cY >= y1) && (cX >= xMedia && cY <= yMedia))
				{
					encontrado = true;
					numCelula = i;
					break;
				}
				//Cuadrante 2
				else if((cX >= x1 && cY >= y1) && (cX <= xMedia && cY <= yMedia))
				{
					encontrado = true;
					numCelula = i;
					break;
				}
				//Cuadrante 3
				else if((cX >= x1 && cY <= y1) && (cX <= xMedia && cY >= yMedia))
				{
					encontrado = true;
					numCelula = i;
					break;
				}
				//Cuadrante 4
				else if((cX <= x1 && cY <= y1) && (cX >= xMedia && cY >= yMedia))
				{
					encontrado = true;
					numCelula = i;
					break;
				}
			}
		}
		i++;
	}
	if(!compruebaCelulaSeleccionada(numCelula) && numCelula != -1)
	{
		celulaSeleccionada.push_back(numCelula);
	}	
}

/**
 Selecciona todas las células disponibles en la imagen.
 */
void DibujadoCelula::selecAllCells()
{
	int numCelulas;

	numCelulas = coordCelulas->getNumCelulas();

	for(int i = 0; i < numCelulas; i++)
	{
		celulaSeleccionada.push_back(i);
	}

	pintaBorde();
}

/**
 Comprueba si los puntos pasador por parametro se encuentran dentro de una celula.
 @param cX, int que contiene la coordenada x.
 @param cY, int que contiene la coordenada y.
 @return bool, true si los puntos se encuentran dentro de una celula, false en caso
 contrario.
 */
bool DibujadoCelula::puntoDentroCelula(int cX, int cY)
{
	int x1, y1, xMedia, yMedia;
	register int numPoligonos, numCoordPol;
	Celula *cell;
	vector<int> *coordX, *coordY;

	//Numero de poligonos 	 
    numPoligonos = coordCelulas->getNumCelulas();
	
	for(register int i = 0; i < numPoligonos; i++)
	{		
		//Poligono actual
		cell = coordCelulas->getCelula(i);
		
		//Si el raton se encuentra entre la Max X e Y y la Min X e Y se comprueba 
		//el poligono
		if((cell->getCoordMaxMin(0)) > cX && (cell->getCoordMaxMin(1)) < cX 
		   && (cell->getCoordMaxMin(2)) > cY && (cell->getCoordMaxMin(3)) < cY)
		{
			//(XMax - XMin) / 2 -> resultado + XMin punto medio de coordenada x
			xMedia = (cell->getCoordMaxMin(0) - cell->getCoordMaxMin(1)) / 2;
			xMedia = cell->getCoordMaxMin(1) + xMedia;
		
			//(YMax - YMin) / 2 -> resultado + YMin punto medio de coordenada y
			yMedia = (cell->getCoordMaxMin(2) - cell->getCoordMaxMin(3)) / 2;
			yMedia = cell->getCoordMaxMin(3) + yMedia;

			//Asignamos el numero de coordenadas del poligono
			coordX = cell->getBordeCellX();
			coordY = cell->getBordeCellY();
			numCoordPol = coordX->size();
		
			//Recorremos el poligono
			for(register int j = 0; j < numCoordPol; j++)
			{
				//Obtenemos las coordenas x e y del poligono
				x1 = (*coordX)[j];
				y1 = (*coordY)[j];
				
				//Comprobamos si la coordenada cX y cY se encuentra dentro del poligono
				//Cuadrante 1
				if((cX <= x1 && cY >= y1) && (cX >= xMedia && cY <= yMedia))
				{
					return true;
				}
				//Cuadrante 2
				else if((cX >= x1 && cY >= y1) && (cX <= xMedia && cY <= yMedia))
				{
					return true;
				}
				//Cuadrante 3
				else if((cX >= x1 && cY <= y1) && (cX <= xMedia && cY >= yMedia))
				{
					return true;
				}
				//Cuadrante 4
				else if((cX <= x1 && cY <= y1) && (cX >= xMedia && cY >= yMedia))
				{
					return true;
				}
			}
		}
	}	

	return false;
}

/**
 Comprueba si la celula ya se encuentra seleccionada en caso afirmativo devuelve
 verdadero en caso contrario falso.
 @param &numCel, referencia int const de la celula seleccionada.
 @return bool, true si la celula ya estaba seleccionada, false en caso contrario.
 */
bool DibujadoCelula::compruebaCelulaSeleccionada(const int &numCel)
{
	int tamVecCelSelec, i;
	
	i = 0;
	tamVecCelSelec = celulaSeleccionada.size();
	
	while(i < tamVecCelSelec && celulaSeleccionada[i] != numCel)
	{
		i++;
	}
	if(i == tamVecCelSelec)
	{
		return false;
	}
	else
	{
		celulaSeleccionada.erase(celulaSeleccionada.begin() + i);
		return true;
	}
}

/**
 Elimina la celula seleccionada.
 */
void DibujadoCelula::eliminaCelulaSeleccionada()
{	
	if(celulaSeleccionada.size())
	{
		int numCelulaSelec;
			
		numCelulaSelec = celulaSeleccionada.size();
		
		//Ordenamos los datos de menor a mayor para no tener problemas a la hora de borrar
		sort(celulaSeleccionada.begin(), celulaSeleccionada.end());
		//Le damos la vuelta al vector
		reverse(celulaSeleccionada.begin(), celulaSeleccionada.end());
		
		//Borramos el objeto del vector correpondiente al poligono seleccionado
		for(int i = 0; i < numCelulaSelec; i++)
		{
			coordCelulas->borraCelula(celulaSeleccionada[i]);
		}
		
		//Vaciamos el vector de celulas
		celulaSeleccionada.clear();
	}	
}

/**
 Pintamos unos puntos y despues se pintara la celula.
 @param cX, double coordenada x.
 @param cY, double coordenada y.
 */
void DibujadoCelula::dibujarPuntosCelula(double cX, double cY)
{	
	//Añadimos las coordenadas en el poligono
	nuevaCelulaX.push_back((cX / zoomCelulas));
	nuevaCelulaY.push_back((cY / zoomCelulas));

	//Ancho de la linea de dibujo
	crPuntos->set_line_width(grosPunto * zoomCelulas * 1.5);

	//Color del punto
	crPuntos->set_source_rgba(ediCelR, ediCelG, ediCelB, 1);
	
	//Dibujamos un circulo con el centro cX,cY
	crPuntos->arc(cX, cY, (1 * zoomCelulas), 0, 2 * M_PI);
	
	//Pintamos el circulo
	crPuntos->stroke();
}

/**
 Repinta los puntos de las células.
 */
void DibujadoCelula::repintadoPuntosCelulas()
{
	int numPuntos;

	numPuntos = nuevaCelulaX.size();

	//Ancho de la linea de dibujo
	crPuntos->set_line_width(grosPunto * zoomCelulas * 1.5);

	//Color del punto
	crPuntos->set_source_rgba(ediCelR, ediCelG, ediCelB, 1);
	
	for(int i = 0; i < numPuntos; i++)
	{
		//Dibujamos un circulo con el centro cX,cY
		crPuntos->arc(nuevaCelulaX[i] * zoomCelulas, nuevaCelulaY[i] * zoomCelulas,
		              (1 * zoomCelulas), 0, 2 * M_PI);
		//Pintamos el circulo
		crPuntos->stroke();
	}
}

/**
 Establecemos el punto de origen del pintado a mano alzada.
 @param &cX, referencia int const de la coordenada X.
 @param &cY, referencia int const de la coordenada Y.
 */
void DibujadoCelula::manoAlzadaPuntoInicial(const int &cX, const int &cY)
{	
	borrarCelulaNueva();
	
	//Ancho de la linea de dibujo
	crLinea->set_line_width(grosLinea * zoomCelulas);
	
	//Color del punto
	crLinea->set_source_rgba(ediCelR, ediCelG, ediCelB, 1);
	
	//Posicionamos el puntero en donde hemos hecho click
	crLinea->move_to(cX, cY);

	//Añadimos las coordenadas en el poligono
	nuevaCelulaX.push_back((cX / zoomCelulas));
	nuevaCelulaY.push_back((cY / zoomCelulas));
}

/**
 Añade la celula al vector de poligonos, en caso de ser a mano alzada completa
 la celula.
 @return bool, true si se agrega una nueva celula, false en caso contrario.
 */
bool DibujadoCelula::agregaCelula()
{		
	if(manoAlzada)
	{
		if(!seccionBorrada)
		{
			//Cerramos el poligono
			crLinea->close_path();
		}
	
		//Dibujamos el nuevo poligono
		crLinea->stroke();
		
		manoAlzada = false;
		
	}
	if(seccionBorrada)
	{
		uneCelulaModificada();
		
		pintaBorde();
		
		borrarCelulaNueva();
		
		return false;
	}
	else
	{
		int numCoordPol;
		
		//Asginamos el numero de coordenadas del nuevo poligono
		numCoordPol = nuevaCelulaX.size();

		if(CalculoMorfologico::calcularPerimetro(nuevaCelulaX, nuevaCelulaY) > 120)
		{
			//Incrementamos el valor del id
			coordCelulas->incrementaIdCell();
			//Asignamos el numero del poligono
			nuevaCelula->setIdCelula(coordCelulas->getLastIdCell());

			//Añadimos las coordenadas max y min del vector
			for(int i = 0; i < numCoordPol; i++)
			{
				//Llamamos al metodo de busqueda de coordenadas max y min
				Utiles::calculoCoordMaxMin(nuevaCelulaX[i],nuevaCelulaY[i], 1, *nuevaCelula);
			}
			
			return true;
		}
	}	
	return false;
}

/**
 Añade una celula a la lista de celulas disponibles.
 @param cond, bool en caso de ser verdadero no es una celula si no zona fuera de
 la imagen.
 */
void DibujadoCelula::addCellToListCells(bool cond)
{
	if(cond)
	{
		nuevaCelula->setEstadoCelula("outimage");
		nuevaCelula->setClaseCelula("outimage");
	}
	
	nuevaCelula->setCoordCellX(nuevaCelulaX);
	nuevaCelula->setCoordCellY(nuevaCelulaY);
	coordCelulas->setCelula(*nuevaCelula);	
			
	pintaBorde();
	
	borrarCelulaNueva();
}

/**
 Modifica la Celula seleccionada.
 @param &cX, referencia int const de la coordenada X donde se corta la celula.
 @param &cY, referencia int const de la coordenada Y donde se corta la celula. 
 */
void DibujadoCelula::modifcaCelula(const int &cX, const int &cY)
{
	if(!modifPos1[0] && !modifPos1[0])
	{
		modificacion = true;
		modifPos1[0] = (cX / zoomCelulas);
		modifPos1[1] = (cY / zoomCelulas);
	}
	else
	{
		modifPos2[0] = (cX / zoomCelulas);
		modifPos2[1] = (cY / zoomCelulas);
		buscaCoordCelula(modifPos1,modifPos2);
		puntosModif = true;
	}
	
	//Ancho de la linea de dibujo
	crModifi->set_line_width(grosPunto * zoomCelulas * 1.5);
	
	//Color del punto
	crModifi->set_source_rgba(ediCelR, ediCelG, ediCelB, 1);
	
	//Dibujamos un circulo con el centro cX,cY
	crModifi->arc(cX, cY, (1 * zoomCelulas), 0, 2 * M_PI);

	//Pintamos el circulo
	crModifi->stroke();

	//Rellenamos el circulo
	crModifi->fill();
}

/**
 Busca las coordenadas correspondientes al punto.
 @param pos1, array de int que contiene las coordenadas x e y del primer punto de
 corte.
 @param pos2, array de int que contiene las coordenadas x e y del segundo punto de
 corte.
 */
void DibujadoCelula::buscaCoordCelula(int pos1[2], int pos2[2])
{
	Celula cell;
	int x1, y1, x2, y2, numCoordPol;
	vector<int> *cx, *cy;
	
	cell = *coordCelulas->getCelula(celulaSeleccionada[0]);
	posi1 = posi2 = x1 = x2 = y1 = y2 = 0;
	cx = cell.getBordeCellX();
	cy = cell.getBordeCellY();
	numCoordPol = cx->size();
	
	for(int i = 0; i < numCoordPol; i++)
	{		
		if(abs(abs(pos1[0] - x1) + abs(pos1[1] - y1)) > 
		   abs(abs(pos1[0] - (*cx)[i]) + abs(pos1[1] - (*cy)[i])))
		{
			x1 = (*cx)[i];
			y1 = (*cy)[i];
			//Posicion del vector valor x
			posi1 = i;
		}
		if(abs(abs(pos2[0] - x2) + abs(pos2[1] - y2)) > 
		   abs(abs(pos2[0] - (*cx)[i]) + abs(pos2[1] - (*cy)[i])))
		{
			x2 = (*cx)[i];
			y2 = (*cy)[i];
			//Posicion del vector valor x
			posi2 = i;
		}
	}
}

/**
 Elimina la parte de la celula seleccionada, con las coordenadas pasadas por parametro
 localiza que lado de la celula esta mas proxima y la elimina.
 @param &cX, referencia int const de la coordenada X de la seccion de la celula.
 @param &cY, referencia int const de la coordenada Y de la seccion de la celula.
 */
void DibujadoCelula::eliminaParteModif(const int &cX, const int &cY)
{
	int minX, minY, posicion, numCoordPol, posAux, tamAux1, tamAux2;
	Celula *cell;
	int x,y;
	vector<int> auxiliarmod1X, auxiliarmod1Y, auxiliarmod2X, auxiliarmod2Y;
	vector<int> *coordX, *coordY;
	
	seccionBorrada = true;
	modificacion = false;
	posicion = minX = minY = posAux = 0;
	
	//Ponemos la celula en modo modificacion
	celulaModificandose = celulaSeleccionada[0];
	
	//Obtenemos el poligono
	cell = coordCelulas->getCelula(celulaSeleccionada[0]);
	//Numero de coordenadas del poligono
	coordX = cell->getBordeCellX();
	coordY = cell->getBordeCellY();
	numCoordPol = coordX->size();
	
	x = (cX / zoomCelulas);
	y = (cY / zoomCelulas);

	//Comprobamos que pos1 no tenga el valor de indice mas pequeño
	if(posi1 >= posi2)
	{
		//revertimos el valor de los indices de las coordenadas coordenadas
		posAux = posi2;
		posi2 = posi1;
		posi1 = posAux;
	}
	
	//Localizamos las coordenadas mas proximas de pulsacion
	for(int i = 0; i < numCoordPol; i++)
	{
		if(abs(abs(x -minX) + abs(y - minY)) > 
		   abs(abs(x - (*coordX)[i])) + abs(y - (*coordY)[i]))
		{
			minX = (*coordX)[i];
			minY = (*coordY)[i];
			posicion = i;
		}
	}
	
	/*Localizamos el caso en el que nos encontramos, si se cumple la afirmacion
	estamos en el caso 1 necesitaremos dos vectores auxiliares en caso contrario
	necesitaremos un solo vector*/
	if((posi1 <= posicion) && (posi2 >= posicion))
	{
		//Rellenamos el primer vector
		for(int i = 0; i < posi1; i++)
		{
			auxiliarmod1X.push_back((*coordX)[i]);
			auxiliarmod1Y.push_back((*coordY)[i]);
		}

		//Rellenamos el segundo vector
		for(int i = posi2; i < numCoordPol; i++)
		{
			auxiliarmod2X.push_back((*coordX)[i]);
			auxiliarmod2Y.push_back((*coordY)[i]);
		}

		//Vaciamos las coordenadas del poligono seleccionado
		cell->borraDatosVectorX();
		cell->borraDatosVectorY();
		tamAux1 = auxiliarmod1X.size();
		tamAux2 = auxiliarmod2X.size();

		//Primer trozo de la celula
		for(int i = 0; i < tamAux2; i++)
		{
			coordX->push_back(auxiliarmod2X[i]);
			coordY->push_back(auxiliarmod2Y[i]);
		}

		//Segundo trozo de la celula
		for(int i = 0; i < tamAux1; i++)
		{
			coordX->push_back(auxiliarmod1X[i]);
			coordY->push_back(auxiliarmod1Y[i]);
		}
	}
	else
	{
		//Rellenamos el primer vector
		for(int i = posi1; i < posi2; i++)
		{
			auxiliarmod1X.push_back((*coordX)[i]);
			auxiliarmod1Y.push_back((*coordY)[i]);
		}

		//Vaciamos por seguridad el segundo vector
		auxiliarmod2X.clear();
		auxiliarmod2Y.clear();

		//Vaciamos las coordenadas del poligono seleccionado
		cell->borraDatosVectorX();
		cell->borraDatosVectorY();
		
		tamAux1 = auxiliarmod1X.size();
		
		//Rellenamos el vector de coordenadas para pintarlo
		for(int i = 0; i < tamAux1; i++)
		{
			coordX->push_back(auxiliarmod1X[i]);
			coordY->push_back(auxiliarmod1Y[i]);
		}
	}		
	posi1 = posi2 = modifPos1[0] = modifPos1[1] = modifPos2[0] = modifPos2[1] = 0;
}

/**
 Completa la celula modificada y une los segmentos de coordenadas.
 */
void DibujadoCelula::uneCelulaModificada()
{
	int x1, x2, y1, y2, tamanho, sumaXY1, sumaXY2, tamNueva;
	vector<int> *cx, *cy;

	cx = coordCelulas->getCelula(celulaSeleccionada[0])->getBordeCellX();
	cy = coordCelulas->getCelula(celulaSeleccionada[0])->getBordeCellY();
	
	sumaXY1 = sumaXY2 = x1 = x2 = y1 = y2 = 0;		
	tamanho = (cx->size() - 1);
	x1 = (*cx)[0];
	y1 = (*cy)[0];
	x2 = (*cx)[tamanho];
	y2 = (*cy)[tamanho];

	sumaXY1 = (abs(x1 - nuevaCelulaX[0]) + abs(y1 - nuevaCelulaY[0]));
	sumaXY2 = (abs(x2 - nuevaCelulaX[0]) + abs(y2 - nuevaCelulaY[0]));

	tamNueva = nuevaCelulaX.size();

	//Comprobamos de que forma unimos el nuevo vector si de menor a mayor o al reves
	if(sumaXY1 > sumaXY2)
	{
		for(int i = 0; i < tamNueva; i++)
		{
			cx->push_back(nuevaCelulaX[i]);
			cy->push_back(nuevaCelulaY[i]);
			
			//Calculo de las coordenadas maximas y minimas
			Utiles::calculoCoordMaxMin(nuevaCelulaX[i],nuevaCelulaY[i], 1, 
			                   *coordCelulas->getCelula(celulaSeleccionada[0]));
		}
	}
	else
	{	
		for(int i = (tamNueva - 1); i > 0; i--)
		{
			cx->push_back(nuevaCelulaX[i]);
			cy->push_back(nuevaCelulaY[i]);
			
			//Calculo de las coordenadas maximas y minimas
			Utiles::calculoCoordMaxMin(nuevaCelulaX[i],nuevaCelulaY[i],
								   1, *coordCelulas->getCelula(celulaSeleccionada[0]));
		}
	}
	
	puntosModif = seccionBorrada = false;
	celulaModificandose = -1;
	celulaSeleccionada.clear();
}

/**
 Establece los colores del dibujado de las celulas.
 @param &indice, referencia int const que contiene el numero de la celula de la 
 que se quiere obtener el color de dibujado.
 @return vector<double>, valor de los 3 componetes del color seleccionado, RGB respectivamente.
 */
vector<double> DibujadoCelula::estableceColores(const int &indice)
{
	vector<double> color;
	double rojo, verde, azul;
	string pref, polig;
	bool seleccionada = false;
	int numEstados, numSeleCel;
	
	color.clear();
	polig = coordCelulas->getCelula(indice)->getClaseCelula();
	numSeleCel = celulaSeleccionada.size();
		;
	for(int i = 0; i < numSeleCel; i ++)
	{		
		if(celulaSeleccionada[i] == indice)
		{
			seleccionada = true;
			break;
		}
	}
	
	if(seleccionada)
	{
		//Color de la celula seleccionada
		color.push_back(seleCelR);
		color.push_back(seleCelG);
		color.push_back(seleCelB);
	}
	else
	{
		polig = coordCelulas->getCelula(indice)->getEstadoCelula();
		numEstados = estados->size();
		
		for(int j = 0; j < numEstados; j++)
		{
			pref = (*estados)[j].getEtiquetaClasificacion();
	
			if(polig == pref)
			{
				
				rojo = ((*estados)[j].getColorEstadoR()/divisor);
				verde = ((*estados)[j].getColorEstadoG()/divisor);
				azul = ((*estados)[j].getColorEstadoB()/divisor);
				color.push_back(rojo);
				color.push_back(verde);
				color.push_back(azul);
				break;
			}
		}
	}
	if(color.size() == 0)
	{
		//Color de las celulas
		color.push_back(sinIdCelR);
		color.push_back(sinIdCelG);
		color.push_back(sinIdCelB);	
	}
	
	return color;
}

/**
 Destruye todas las variables auxiliares de dibujado y modificacion de las celulas.
 */
void DibujadoCelula::destruyeDatos()
{
	posi1 = posi2 = modifPos1[0] = modifPos1[1] = modifPos2[0] = modifPos2[1] = 0;
	modificacion = puntosModif = seccionBorrada = false;
	if(celulaSeleccionada.size())
	{
		celulaModificandose = -1;
	}
}
