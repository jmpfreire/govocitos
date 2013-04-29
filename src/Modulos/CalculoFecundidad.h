/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CalculoFecundidad.h
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

#ifndef _CALCULOFECUNDIDAD_H_
	#define _CALCULOFECUNDIDAD_H_

	#include <vector>
	#include <iostream>

	#include "Modulos/CalculoEstadistico.h"
	#include "Modulos/CalculoMorfologico.h"
	#include "Estructuras/ListadoIndividuo.h"
	#include "Modulos/Rejilla.h"
	#include "Estructuras/EstadoCelula.h"
	#include "Config/ConfigGovocitos.h"
	#include "Modulos/ResultFecundidad.h"

	using namespace std;

	class PanelFecundidad;

	class CalculoFecundidad
	{
		public:
			CalculoFecundidad();
			~CalculoFecundidad();
			void setCalibracion(double calib);
			void setListaIndividuos(ListadoIndividuo &lv);
			void setRejilla(Rejilla &rej);
			void setPanelFecundidad(PanelFecundidad &pf);
			void setConfiguracion(ConfigGovocitos &cfg);
			void setListaResultadosImg(ResultFecundidad &lri);
			void setClasesDiametros(vector<int> clDiam);
			void setFactorCorreccion(vector<double> fc);
			void calculoPuntosCelulas();
			void calculaValorDeK();
			void calculaValorDeKLupa(vector<double> diam);
			void calculoAreaRejilla();
			void calculoFecundidad();
			double calculaFecunEstado(double mediaPuntos, double mediaObjetos);
		private:
			//Metodos
			vector<double> calculoDiametrosAjustados();
			vector<double> calculoDiametrosAjustadosLupa(vector<double> diametros);
			double areaNoUsada(ListadoCelulas &lc);
			//Atributos
			ListadoIndividuo *listIndiv;
			Rejilla *rejilla;
			PanelFecundidad *pfecundidad;
			ConfigGovocitos *configuracion;
			vector<EstadoCelula> estados;
			ResultFecundidad *listResultados;
			vector<double> factorCorreccion;
			vector<int> clasesDiametros;
			double calibracion;
			vector<int> estadosEnUso;
	};
#endif //_CALCULOFECUNDIDAD_H_
