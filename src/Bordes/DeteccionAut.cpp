/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DeteccionAut.cpp
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

#include "DeteccionAut.h"

/* edges_govocitos */
PointList ** detect_edge_multiscalar_canny ( const Image * in_img, const double blur_factor, int *num_edges, int min_size);

/* cell_detection */
//PointList ** nonSuperviseDetection( PointList ** contour, const int num_edges, const int num_cols, const int num_rows, const int min_dim, const int max_dim, const double max_round, int *nout);
//PointList ** superviseDetection(PointList ** contour, const int num_edges, const int num_cols, const int num_rows, const int min_dim, const int max_dim, const double max_round,  PointList ** truecells, const int ntruecells, const int *xcs, const int *ycs, const int ncells, int *nout);

/**
 Constructor.
 */
DeteccionAut::DeteccionAut()
{
	vectorPol = 0;
	ruta = "";
	contour = NULL;
	num_edges = 0;
	img = NULL;
	img_grey = NULL;
	num_rows = 0;
	num_cols = 0;
	diamMax = 0.0;
	diamMin = 0.0;
	calibracion = 1;

	MIN_DIAMETER = 100;
	MAX_DIAMETER = 2000;
}

/**
 Constructor
 */
DeteccionAut::DeteccionAut(const DeteccionAut &d)
{
	vectorPol = d.vectorPol;
	ruta = d.ruta;
	contour = d.contour;
	num_edges = d.num_edges;
	img = d.img;
	img_grey = d.img_grey;
	num_rows = d.num_rows;
	num_cols = d.num_cols;
	MIN_DIAMETER = d.MIN_DIAMETER;
	MAX_DIAMETER = d.MAX_DIAMETER;
	diamMax = d.diamMax;
	diamMin = d.diamMin;
}

/**
 Destructor.
 */
DeteccionAut::~DeteccionAut()
{
	for(int i = 0; i < num_edges;i++)
	{
			free_point_list(contour[i]);
			free(contour[i]->point);
			free(contour[i]);
	}
	free(contour);
	
	img = NULL;
	img_grey = NULL;
	contour = NULL;
}

/**
 Establece la calibración de la imagen.
 @param calib, double que contiene la calibracion
 */
void DeteccionAut::setCalibracion(double calib)
{
	calibracion = calib;
}

/**
 Establece la ruta de la imagen.
 @param r, string que contiene la ruta de la imagen.
 */
void DeteccionAut::setRutaImagen(const string &r)
{
	ruta = r;
}

/**
 Establece una referencia del objeto que contiene todas las células.
 @param lc, referencia de ListadoCelulas que contiene las células.
 */
void DeteccionAut::setListadoCelulas(ListadoCelulas &lc)
{
	vectorPol = &lc;
}

/**
 Establece los diametros maximo y minimo de los diametros a analizar.
 @param max, double que contiene el diametro maximo.
 @param min, double que contiene el diametro minimo.
 */
void DeteccionAut::setDiametrosMaxMin(double max, double min)
{
	diamMax = max;
	diamMin = min;
}

/**
 Realiza la deteccion de todas las celulas de la imagen de forma automatica.
 */
bool DeteccionAut::deteccionBordesNoSupervisado()
{
	// Maximun number of objects in the image
	int NUM_CELLS (10000 );
	// Maximun roundness of interested objects in the image for unsupervised algorithm
	double  MAX_ROUND 	( 1.4 );
	int i, l;
	int nout;
	PointList **out;

	if(diamMax != 0)
	{
		MAX_DIAMETER = diamMax / calibracion;
	}
	else
	{
		MAX_DIAMETER = MAX_DIAMETER / calibracion;
	}

	if(diamMin != 0)
	{
		MIN_DIAMETER = diamMin / calibracion;
	}
	else
	{
		MIN_DIAMETER = MIN_DIAMETER / calibracion;
	}

	// Read the input image
	img = read_img ( ruta.c_str() );
	if ( !is_rgb_img ( img ) || (img == NULL))
	{
   		fprintf ( stderr, "Input image ( %s ) must be color image !", ruta.c_str() );
   		return false;
	}

	/********************************Reloj**************************************/
	// comienzo = clock();
	/***************************************************************************/

	/***************************************************************************/
	 string mensaje, titulo;

	//mensaje = "Se va a proceder al cálculo de los bordes de los ovocitos, el proceso durara aproximadamente 1 minuto durante el cual la aplicación quedara bloqueada, ¿Esta seguro de continuar?";
	mensaje = "The automatic oocyte edge detection is going to be performed. The application will be unaccesible during this process. Are you sure that you want to continue?";
	
	//titulo = "Cálculo automatico de bordes de los ovocitos";
	titulo = "Oocyte edge detection";
	
	if(Dialogos::dialogoConfirmacion(mensaje, titulo))
	{
		//DialogoBarraProgres dProgres("Detectando Bordes");
		DialogoBarraProgres dProgres("Oocyte edge detection");
		dProgres.ejectuaDialogoProgreso();
		dProgres.setEstadoBarraProgreso(0.1);
		dProgres.setPercentText(0.1);
		Utiles::actualizarInterfaz();
		/***************************************************************************/
		// Detect the edges in the input image
		num_rows=get_num_rows(img);
		num_cols=get_num_cols(img);

		/*Este dobre bucle que ven a continuacion e a aplicacion do filtro de Canny para distintos umbrais 
		e suavizados (distintas escalas). O que obtemos e en contour (unha estrutura da libreria fourier.0.8 
		que almacena os bordes que teñen mais de MIN_LENGTH pixels) e en n_all o numero de borde. */
		// Este paso e independente de que o algoritmo se aplique de forma supervisada ou non supervisada.
		//num_edges = 0;
	
		img_grey=rgb_to_gray(img);
		// Aplicando o filtro de canny multiescalar
		contour=detect_edge_multiscalar_canny ( img_grey,  &num_edges, MIN_DIAMETER, NUM_CELLS);
		if ( IS_NULL( contour)) {	printf ( "Invalid point list objects !"); }
		//	printf("Tempo transcurrido: %f bordes= %d \n", stop_timer ( start_time), num_edges) ;

		/**********************************fase 1****************************/
		/* final = clock();
		cout<<"Tiempo fase 1 "<<(final - comienzo)/(double) CLOCKS_PER_SEC<<endl;
		comienzo = clock();*/		

		dProgres.setEstadoBarraProgreso(0.5);
		dProgres.setPercentText(0.5);
		Utiles::actualizarInterfaz(); 
		/**************************************************************************/
		// A partir de aqui fanse calculos para analizar os bordes que hai en contour e asi mostrar so os que cremos que son bordes de govocitos maduros.
		
		//utilizando funcion aplico a deteccion non supervisada
		out=nonSuperviseDetection(contour, num_edges, num_cols, num_rows, MIN_DIAMETER, MAX_DIAMETER, MAX_ROUND, &nout);
		
		/**********************************Reloj fase 2****************************/
		/* final = clock();
		cout<<"Tiempo fase 2 "<<(final - comienzo)/(double) CLOCKS_PER_SEC<<endl;
		comienzo = clock();*/

		dProgres.setEstadoBarraProgreso(0.9);
		dProgres.setPercentText(0.9);
		Utiles::actualizarInterfaz();
		/**************************************************************************/

		for ( l = 0; l <nout; l++)		
		{
			/************************Pintado govocitos*************************/
			PointList *p = out[l];

			/*Guardamos los puntos en un objeto celula y lo añadimos al objeto de
			listado de celulas*/
			pasoCoordSistemaGovocitos(p);
			/*******************************************************************/
		}

		for(i=0; i<nout; i++)
		{
			free_point_list(out[i]);
			free(out[i]->point);
			free(out[i]);
		}
		free(out); 	
		free_img(img); free_img(img_grey);
		free(img); free(img_grey);
	
	/**********************************Reloj fase 3****************************/
		/* final = clock();
		cout<<"Tiempo fase 3 "<<(final - comienzo)/(double) CLOCKS_PER_SEC<<endl;*/

		dProgres.setEstadoBarraProgreso(1);
		dProgres.setPercentText(1);
		Utiles::actualizarInterfaz();
		dProgres.cierraVentanaProgreso();
		/**************************************************************************/
	}
	else
	{
		return false;
	}

	return true;
}

/**
 Realiza la deteccion de todas las celulas de la imagen de forma automatica.
 */
void DeteccionAut::deteccionBordesSupervisado(vector <int> x, vector <int> y)
{
	// Maximun roundness of interested objects in the image for unsupervised algorithm
	double  MAX_ROUND 	( 1.4 );
	int i, l;
	PointList  **nsdetection=NULL;
	PointList  **supervised;
	int ns=0, nsupervised;
	int *xs, *ys, ncs;	
	    
    // Se convierten los dos vectores de coordenadas (puntos introducidos por el usuario) a dos arrays dinámicos
    ncs = x.size ( );
    xs = (int *) calloc (ncs, sizeof (int));
    ys = (int *) calloc (ncs, sizeof (int));
    for (i = 0; i < ncs; i++)
	{
          xs [i ]  = x [i];
          ys [i ]  = y [i];
    }	

	//Pasamos las coordenadas obtenidas por el algoritmo no supervisado
	pasoCoordGovocitosPointList(nsdetection);
	
	//utilizando funcion aplico a deteccion non supervisada
	supervised = superviseDetection(contour, num_edges, num_cols, num_rows, MIN_DIAMETER, MAX_DIAMETER, MAX_ROUND, 
	                                nsdetection, ns, xs, ys, ncs, &nsupervised);
		
	for ( l = 0; l <nsupervised; l++)		
	{
		/************************Pintado govocitos*************************/
		PointList *p = supervised[l];

		/*Guardamos los puntos en un objeto celula y lo añadimos al objeto de
		listado de celulas*/
		pasoCoordSistemaGovocitos(p);
		/*******************************************************************/
	}

	for(i=0; i<nsupervised; i++)
	{
			free_point_list(supervised[i]);
			free(supervised[i]->point);
			free(supervised[i]);
	}
	free(supervised);

	for(i=0; i<ns;i++)
	{
			free_point_list(nsdetection[i]);
			free(nsdetection[i]->point);
			free(nsdetection[i]);
	}
	free(nsdetection);

	free(xs);  free(ys);			
} 

/**
 Transforma las coordenadas obtenidas por el detector automatico al tipo de coordenadas
 del programa principal para su dibujado.
 @param *p, puntero de tipo PointList que contiene las coordenadas de 1 celula.
 */
void DeteccionAut::pasoCoordSistemaGovocitos(PointList *p)
{
	Celula cell;
	vector <int> cx, cy;
	int numPun;
	int numPuntos;
	
	numPuntos = get_num_pts(p);
	
	for (int ik = 0; ik < numPuntos - 1; ik++ )
	{
		cx.push_back(p->point[ik]->col);
		cy.push_back(p->point[ik]->row);
	}
	numPun = cx.size();
	
	for(int cnt = 0; cnt < numPun; cnt++)
	{
		//Llamamos al metodo de busqueda de coordenadas max y min
		Utiles::calculoCoordMaxMin(cx[cnt], cy[cnt], 1, cell);
	}
	
	//Incrementamos el valor del id
	vectorPol->incrementaIdCell();
	
	//Asignamos el numero del poligono
	cell.setIdCelula(vectorPol->getLastIdCell());
	cell.setCoordCellX(cx);	
	cell.setCoordCellY(cy);
	
	vectorPol->setCelula(cell);
}

/**
 */
void DeteccionAut::pasoCoordGovocitosPointList(PointList  **nsd)
{
	int numCelulas;
	vector<int> cx, cy;

	numCelulas = vectorPol->getNumCelulas();
	
	nsd = (PointList **)calloc(numCelulas, sizeof(PointList *));

	for(int i = 0; i < numCelulas; i++)
	{
		int numCoords;
		PointList *cellI;
		
		cx = *vectorPol->getCelula(i)->getBordeCellX();
		cy = *vectorPol->getCelula(i)->getBordeCellY();

		numCoords = cx.size();

		cellI = (PointList *)calloc(numCelulas, sizeof(PointList));
		cellI->point = (Point **)calloc(numCoords, sizeof(Point *));
		cellI->num_pts = numCoords;
		
		for(int j = 0; j < numCoords; j++)
		{
			cellI->point[j] = alloc_point(cx[j],cy[j]);
		}
		
		nsd[i] = cellI;
	}
}

/**
 Sobrecarga del operador =
 */
const DeteccionAut &DeteccionAut::operator=(const DeteccionAut &d)
{
	this->vectorPol = d.vectorPol;
	this->ruta = d.ruta;
	this->contour = d.contour;
	this->num_edges = d.num_edges;
	this->img = d.img;
	this->img_grey = d.img_grey;
	this->num_rows = d.num_rows;
	this->num_cols = d.num_cols;
	this->diamMax = d.diamMax;
	this->diamMin = d.diamMin;
	this->diamMax = d.diamMax;
	this->diamMin = d.diamMin;

	return *this;
}