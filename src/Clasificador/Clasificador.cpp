/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Clasificador.cpp
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

#include "Clasificador.h"

/**
 Constructor
 @param clEst, string que contiene la ruta del fichero con datos para la clasificacion
 de estados.
 @param mdEst, string que contiene la ruta del fichero con las medias para la clasificacion
 de estados.
 @param clCL, string que contiene la ruta del fichero con datos para la clasificacion
 de clases.
 @param mdCL, string que contiene la ruta del fichero con las medias para la clasificacion
 de clases.
 */
Clasificador::Clasificador(string clEst, string mdEst, string clCl, string mdCl)
{
	fichClasificEst = clEst;
	fichMediaDesviaEst = mdEst;
	fichClasificCl = clCl;
	fichMediaDesviaCl = mdCl;
}

/**
 Destructor.
 */
Clasificador::~Clasificador()
{

}

void Clasificador::le_media_desv(const char *fich, float *media, float *desv) 
{
	FILE  *pf;
	unsigned int  i;


	pf = fopen(fich, "r");
	if(! pf) {
		fprintf(stderr, "svm_estados.cc: le_media_desv: erro en fopen abrindo %s: %s\n", fich, strerror(errno));
		exit(1);
	}
	for(i = 0; i < N_ENTRADAS; i++) 
	{
		(void)fscanf(pf, "%g %g\n", &media[i], &desv[i]);
	}
	fclose(pf);

	/*for(int j = 0; j < 7; j++)
	{
		cout<<"Media "<<media[j]<<" desviacion "<<desv[j]<<endl;
	}*/
}


struct svm_model *Clasificador::crea_svm(const char *f_svm, const char *f_med_desv, float *media, float *desv)
{
	svm_model  *svm;

	svm = svm_load_model(f_svm);
	le_media_desv(f_med_desv, media, desv);

	return(svm);
}



int Clasificador::saida_svm(struct svm_model *svm, float *x, float *media, float *desv) 
{
	unsigned int  i;
	int y;
	struct svm_node  t[1 + N_ENTRADAS];

	for(i = 0; i < N_ENTRADAS; i++) {
		t[i].index = i; 
		if(desv[i]) {
			t[i].value = (x[i] - media[i])/desv[i];
			//cout<<x[i]<<" ";
		} else {
			t[i].value = x[i];
		}
	}
	//cout<<endl;
	t[N_ENTRADAS].index = -1;
	y = svm_predict(svm, t);

	return(y);
}

void Clasificador::destrue_svm(struct svm_model *svm) 
{
	svm_destroy_model(svm);
}

/**
 Carga los ficheros de clasificacion automatica de estados y clases y clasifica las
 celulas de la imagen cuya ruta corresponde con la pasada por parametro.
 @param ruta, string de la ruta de la imagen a analizar.
 @param listCell, objeto ListadoCeulas que contiene todas las celulas de la imagen
 a analizar.
 */
void Clasificador::clasificarCelulas(string ruta, ListadoCelulas &listCell)
{	
	struct svm_model  *svmEst, *svmCl;
	
	float  media_est[N_ENTRADAS], desv_est[N_ENTRADAS];
	float  media_cl[N_ENTRADAS], desv_cl[N_ENTRADAS];
	int  y1, y2;
	int numCelulas, numPuntos;
	vector <int> *cx, *cy;
	Image *img, *img_grey, *img_bin;
	
	img = read_img ( ruta.c_str() );
	img_grey = rgb_to_gray (img);
	
	numCelulas = listCell.getNumCelulas();

	//Obtenemos path de los ficheros de clasificacion
	const char  *f_svm_Est = fichClasificEst.c_str();
	const char  *f_med_desv_Est = fichMediaDesviaEst.c_str();
	const char  *f_svm_Cl = fichClasificCl.c_str();
	const char  *f_med_desv_Cl = fichMediaDesviaCl.c_str();

	//Creamos los svm
	svmEst = crea_svm(f_svm_Est, f_med_desv_Est, media_est, desv_est);
	svmCl = crea_svm(f_svm_Cl, f_med_desv_Cl, media_cl, desv_cl);
	
	for(int i = 0; i < numCelulas; i++) 
	{
		PointList *puntos;

		if(listCell.getCelula(i)->getEstadoCelula() != "outimage" && 
		   listCell.getCelula(i)->getClaseCelula() != "outimage")
		{
			cx = listCell.getCelula(i)->getBordeCellX();
			cy = listCell.getCelula(i)->getBordeCellY();

			numPuntos = cx->size();
			puntos = alloc_point_list(numPuntos);
		
			//Convertimos puntos
			for(int j = 0; j < numPuntos; j++)
			{
				puntos->point[j] = alloc_point((*cy)[j], (*cx)[j]);
			}
			puntos->type = GEN_VALID;
		
			img_bin=computeBinImage ( puntos, get_num_rows ( img_grey ) , get_num_cols (img_grey));
		
			//  double* resul = texture_features_haralick(img, puntos, 1, 1);
			double * resul = texture_features_glrls_grey ( img_grey, img_bin, puntos, 1000, 0);
			float resul2[N_ENTRADAS], resul3[N_ENTRADAS];
		
			for(unsigned int z = 0; z < N_ENTRADAS; z++)
			{
				resul2[z] = (float)resul[z];
				resul3[z] = (float)resul[z];
			}

			//Salida clasificador clases
			y1 = saida_svm(svmCl, resul2, media_cl, desv_cl);

			switch(y1)
			{
				case 0:
					listCell.getCelula(i)->setClaseCelula("cn");
					break;
				case 1:
					listCell.getCelula(i)->setClaseCelula("sn");
					break;
			}
		
			//Salida clasificador estados
			y2 = saida_svm(svmEst, resul3, media_est, desv_est);

			switch (y2)
			{
				case 0:
					listCell.getCelula(i)->setEstadoCelula("ac");
					break;
				case 1:
					listCell.getCelula(i)->setEstadoCelula("hid");
					break;
				case 2:
					listCell.getCelula(i)->setEstadoCelula("vit");// vitelinas o atresicas
					break;
			}
		    free_point_list ( puntos );
		    free ( puntos->point );
		    free ( puntos );
		//	delete puntos;    
	
			free ( resul );
		}
	}
	destrue_svm(svmCl);
	destrue_svm(svmEst);
	
	free_img ( img );
	free ( img );
	free_img ( img_grey );
	free ( img_grey );
}
