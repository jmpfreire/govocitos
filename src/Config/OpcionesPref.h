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

#ifndef _OPCIONESPREF_H_
	#define _OPCIONESPREF_H_

	#include <string.h>
	#include <iostream>
	#include <gtkmm.h>
	#include <gdkmm.h>
	
	using namespace std;
	
	class OpcionesPref
	{
		public:
			OpcionesPref();
			~OpcionesPref();
			OpcionesPref(const OpcionesPref &op);
			long int getCelSDetR();
			long int getCelSDetG();
			long int getCelSDetB();
			long int getSeleCelR();
			long int getSeleCelG();
			long int getSeleCelB();
			long int getEdiCelR();
			long int getEdiCelG();
			long int getEdiCelB();
			double getGrosLinea();
			double getGrosPunto();
			string getArchivImag();
			string getArchivCel();
			string getArchivCSV();
			long int getLimDIR();
			long int getLimDIG();
			long int getLimDIB();
			long int getLimISR();
			long int getLimISG();
			long int getLimISB();
			long int getColRejR();
			long int getColRejG();
			long int getColRejB();
			double getGrosRej();
			double getSeparPuntos();
			double getGrosBordeRej();
			double getValorMicras();
			double getValorBeta();
			bool getBordeComp();
			string getLoginBD();
			string getPassBD();
			string getDirecBD();
			string getDataBaseBD();
			string getLoginSFTP();
			string getPassSFTP();
			string getDirecSFTP();
			string getPathSFTP();
			int getTamCache();
			void setCelSDet(Gdk::Color cd);
			void setSeleCel(Gdk::Color sc);
			void setEdiCel(Gdk::Color ec);
			void setGrosLinea(double gl);
			void setGrosPunto(double gp);
			void setArchivImag(const string &ai);
			void setArchivCel(const string &ac);
			void setArchivCSV(const string &ac);
			void setLimDI(Gdk::Color ldi);
			void setLimIS(Gdk::Color lis);
			void setColRej(Gdk::Color crj);
			void setGrosRej(double grj);
			void setSeparPuntos(double sp);
			void setGrosBordeRej(double gbr);
			void setValorMicras(double m);
			void setValorBeta(double b);
			void setBordeComp(bool cond);
			void setLoginBD(const string &lbd);
			void setPassBD(const string &pbd);
			void setDirecBD(const string &dbd);
			void setDataBaseBD(const string &dbdb);
			void setLoginSFTP(const string &c);
			void setPassSFTP(const string &c);
			void setDirecSFTP(const string &c);
			void setPathSFTP(const string &c);
			void setTamCache(int tc);
			void revertirDatos();
			const OpcionesPref &operator=(const OpcionesPref &op);
		private:
			//Editor
			long int celSDetR, celSDetG, celSDetB, seleCelR, seleCelG, seleCelB,
			ediCelR, ediCelG, ediCelB;
			double grosLinea, grosPunto;
			//Directorios
			string archivImag, archivCel, archivCSV;
			//Rejilla
			long int limDIR, limDIG, limDIB, limISR, limISG, limISB, colRejR,
			colRejG, colRejB;
			double grosRej, separPuntos, grosBordeRej, valorMicras, valorBeta;
			bool actBordeRej;
			//Base de datos
			string loginBD, passBD, rutaBD, dataBaseBD;
			//Secure FTP
			string loginSFTP, passSFTP, rutaSFTP, pathSFTP;
			//Cache imagenes
			int tamCache;
	};
#endif // _OPCIONESPREF_H_
