/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Clasificador.h
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

#ifndef _CLASIFICADOR_H_
	#define _CLASIFICADOR_H_

	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	#include <stdlib.h>
	#include <errno.h>

	#include "Bordes/image.h"
	#include "Estructuras/ListadoCelulas.h"
	#include "Clasificador/svm.h"

	const unsigned int N_ENTRADAS = 11;

	class Clasificador
	{
		public:
			Clasificador(string clEst, string mdEst, string clCl, string mdCl);
			~Clasificador();
			void clasificarCelulas(string ruta, ListadoCelulas &listCell);
		private:
			void le_media_desv(const char *fich, float *media, float *desv);
			struct svm_model *crea_svm(const char *f_svm, const char *f_med_desv, float *media, float *desv);
			int saida_svm(struct svm_model *svm, float *x, float *media, float *desv);
			void destrue_svm(struct svm_model *svm);
			//Atributos
			string fichClasificEst, fichMediaDesviaEst, fichClasificCl, fichMediaDesviaCl;
	};
#endif //_CLASIFICADOR_H_
