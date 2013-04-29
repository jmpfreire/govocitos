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

#include "OpcionesPref.h"

/**
 Constructor.
 */
OpcionesPref::OpcionesPref()
{
	//Editor
	celSDetR = 6656;
	celSDetG = 59136;
	celSDetB = 52992;
	seleCelR = 13568;
	seleCelG = 60416;
	seleCelB = 768;
	ediCelR = 63488;
	ediCelG = 63232;
	ediCelB = 1792;
	grosLinea = 20;
	grosPunto = 26;
	//Directorios
	archivImag = "";
	archivCel = "";
	archivCSV = "";
	//Rejilla
	limDIR = 63488;
	limDIG = 4864;
	limDIB = 1792;
	limISR = 9216;
	limISG = 63488;
	limISB = 1792;
	colRejR = 46592;
	colRejG = 63488;
	colRejB = 1792;
	grosRej = 20;
	separPuntos = 180;
	grosBordeRej = 20;
	actBordeRej = false;
	//Variables
	valorMicras = 3.45;
	valorBeta = 1;
	//Base de datos
	loginBD = "";
	passBD = "";
	rutaBD = "";
	dataBaseBD = "";
	//Cache imagenes
	tamCache = 30;
	//Sftp
	loginSFTP = "";
    passSFTP = "";
    rutaSFTP = "";
    pathSFTP = "";
}

/**
 Destructor.
 */
OpcionesPref::~OpcionesPref()
{
	
}

/**
 Constructor de copias
 */
OpcionesPref::OpcionesPref(const OpcionesPref &op)
{	
	//Editor
	celSDetR = op.celSDetR;
	celSDetG = op.celSDetG;
	celSDetB = op.celSDetB;
	seleCelR = op.seleCelR;
	seleCelG = op.seleCelG;
	seleCelB = op.seleCelB;
	ediCelR = op.ediCelR;
	ediCelG = op.ediCelG;
	ediCelB = op.ediCelB;
	grosLinea = op.grosLinea;
	grosPunto = op.grosPunto;
	
	//Directorios
	archivImag = op.archivImag;
	archivCel = op.archivCel;
	archivCSV = op.archivCSV;
	
	//Rejilla
	limDIR = op.limDIR;
	limDIG = op.limDIG;
	limDIB = op.limDIB;
	limISR = op.limISR;
	limISG = op.limISG;
	limISB = op.limISB;
	colRejR = op.colRejR;
	colRejG = op.colRejG;
	colRejB = op.colRejB;
	grosRej = op.grosRej;
	separPuntos = op.separPuntos;
	grosBordeRej = op.grosBordeRej;
	actBordeRej = op.actBordeRej;
	
	//Variables
	valorMicras = op.valorMicras;
	valorBeta = op.valorBeta;

	//Base de datos
	loginBD = op.loginBD;
	passBD = op.passBD;
	rutaBD = op.rutaBD;
	dataBaseBD = op.dataBaseBD;

	//Secure FTP
	loginSFTP = op.loginSFTP;
    passSFTP = op.passSFTP;
    rutaSFTP = op.rutaSFTP;
    pathSFTP = op.pathSFTP;
	
	//Cache imagenes
	tamCache = op.tamCache;
}

/**
 Devuelve el color rojo de la celula sin determinar.
 @return long int.
 */
long int OpcionesPref::getCelSDetR()
{
	return celSDetR;
}

/**
 Devuelve el color verde de la celula sin determinar.
 @return long int.
 */
long int OpcionesPref::getCelSDetG()
{
	return celSDetG;
}

/**
 Devuelve el color azul de la celula sin determinar.
 @return long int.
 */
long int OpcionesPref::getCelSDetB()
{
	return celSDetB;
}

/**
 Devuelve el color rojo de la celula seleccionada.
 @return long int.
 */
long int OpcionesPref::getSeleCelR()
{
	return seleCelR;
}

/**
 Devuelve el color verde de la celula seleccionada.
 @return long int.
 */
long int OpcionesPref::getSeleCelG()
{
	return seleCelG;
}

/**
 Devuelve el color azul de la celula seleccionada.
 @return long int.
 */
long int OpcionesPref::getSeleCelB()
{
	return seleCelB;
}

/**
 Devuelve el color rojo de la celula en edicion.
 @return long int.
 */
long int OpcionesPref::getEdiCelR()
{
	return ediCelR;
}

/**
 Devuelve el color verde de la celula en edicion.
 @return long int.
 */
long int OpcionesPref::getEdiCelG()
{
	return ediCelG;
}

/**
 Devuelve el color azul de la celula en edicion.
 @return long int.
 */
long int OpcionesPref::getEdiCelB()
{
	return ediCelB;
}

/**
 Devuelve el grosor de la linea que bordean las celulas.
 @return double.
 */
double OpcionesPref::getGrosLinea()
{
	return grosLinea;
}

/**
 Devuelve el grosor del punto de dibujado.
 @return double.
 */
double OpcionesPref::getGrosPunto()
{
	return grosPunto;
}

/**
 Devuelve la ubicacion por defecto de las imagenes de las celulas.
 @return string.
 */
string OpcionesPref::getArchivImag()
{
	return archivImag;
}

/**
 Devuelve la ubicacion por defecto de los archivos de coordenadas.
 @return string.
 */
string OpcionesPref::getArchivCel()
{
	return archivCel;
}

/**
 Devuelve la ubicacion por defecto de los archivos CSV.
 @return string.
 */
string OpcionesPref::getArchivCSV()
{
	return archivCSV;
}

/**
 Devuelve el color rojo del limite derecho e inferior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimDIR()
{
	return limDIR;
}

/**
 Devuelve el color verde del limite derecho e inferior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimDIG()
{
	return limDIG;
}

/**
 Devuelve el color azul del limite derecho e inferior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimDIB()
{
	return limDIB;
}

/**
 Devuelve el color rojo del limite izquierdo superior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimISR()
{
	return limISR;
}

/**
 Devuelve el color verde del limite izquierdo superior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimISG()
{
	return limISG;
}

/*
 Devuelve el color azul del limite izquierdo superior de la rejilla.
 @return long int.
 */
long int OpcionesPref::getLimISB()
{
	return limISB;
}

/**
 Devuelve el color rojo de la rejilla.
 @return long int.
 */
long int OpcionesPref::getColRejR()
{
	return colRejR;
}

/**
 Devuelve el color verde de la rejilla.
 @return long int.
 */
long int OpcionesPref::getColRejG()
{
	return colRejG;
}

/**
 Devuelve el color azul de la rejilla.
 @return long int.
 */
long int OpcionesPref::getColRejB()
{
	return colRejB;
}

/**
 Devuelve el grosor de la rejilla.
 @return double.
 */
double OpcionesPref::getGrosRej()
{
	return grosRej;
}

/**
 Devuelve la separacion de los puntos de la rejilla.
 @return double.
 */
double OpcionesPref::getSeparPuntos()
{
	return separPuntos;
}

/**
 Devuelve el grosor del borde de la rejilla.
 @return double.
 */
double OpcionesPref::getGrosBordeRej()
{
	return grosBordeRej;
}

/**
 Devuelve el valor de las micras por pixel.
 @return double.
 @deprecated
 */
double OpcionesPref::getValorMicras()
{
	return valorMicras;
}

/**
 Devuelve el valor de la beta que se usa para el calculo del umbral.
 @return double.
 @deprecated
 */
double OpcionesPref::getValorBeta()
{
	return valorBeta;
}

/**
 Devuelve si esta activo el borde de la rejilla.
 @return bool.
 @deprecated
 */
bool OpcionesPref::getBordeComp()
{
	return actBordeRej;
}

/**
 Devuelve el login de la bd.
 @return string.
 */
string OpcionesPref::getLoginBD()
{
	return loginBD;
}

/**
 Devuelve la contraseña de la bd.
 @return string.
 */
string OpcionesPref::getPassBD()
{
	return passBD;
}

/**
 Devuelve la direccion de la bd.
 @return string.
 */
string OpcionesPref::getDirecBD()
{
	return rutaBD;
}

/**
 Devuelve el nombre de la base de datos.
 @return string.
 */
string OpcionesPref::getDataBaseBD()
{
	return dataBaseBD;
}

/**
 Devuelve el login para el sftp.
 @return string.
 */
string OpcionesPref::getLoginSFTP()
{
	return loginSFTP;
}

/**
 Devuelve la pass para el sftp.
 @return string.
 */
string OpcionesPref::getPassSFTP()
{
	return passSFTP;
}

/**
 Devuelve la direccion del sftp.
 @return string.
 */
string OpcionesPref::getDirecSFTP()
{
	return rutaSFTP;
}

/**
 Devuelve el path del sftp.
 @return string.
 */
string OpcionesPref::getPathSFTP()
{
	return pathSFTP;
}

/**
 Devuelve el tamaño de la cache
 @return int.
 */
int OpcionesPref::getTamCache()
{
	return tamCache;
}

/**
 Establece el color de las celulas sin determinar.
 @param cd, Gdk::Color.
 */
void OpcionesPref::setCelSDet(Gdk::Color cd)
{
	celSDetR = cd.get_red();
	celSDetG = cd.get_green();
	celSDetB = cd.get_blue();
}

/**
 Estable el color de las celulas seleccionadas.
 @param sc, Gdk::Color.
 */
void OpcionesPref::setSeleCel(Gdk::Color sc)
{
	seleCelR = sc.get_red();
	seleCelG = sc.get_green();
	seleCelB = sc.get_blue();
}

/**
 Establece el color de las celulas en modo edicion.
 @param ec, Gdk::Color.
 */
void OpcionesPref::setEdiCel(Gdk::Color ec)
{
	ediCelR = ec.get_red();
	ediCelG = ec.get_green();
	ediCelB = ec.get_blue();
}

/**
 Estable el grosor de la linea que bordea las celulas.
 @param gl, double.
 */
void OpcionesPref::setGrosLinea(double gl)
{
	grosLinea = gl;
}

/**
 Establece el grosor del punto de edicion de celulas.
 @param gp, double.
 */
void OpcionesPref::setGrosPunto(double gp)
{
	grosPunto = gp;
}

/**
 Establece la ruta por defecto de los archivos de imagenes.
 @param ai, string.
 */
void OpcionesPref::setArchivImag(const string &ai)
{
	archivImag = ai;
}

/**
 Establece la ruta por defecto de los archivos de celula.
 @param ac, string.
 */
void OpcionesPref::setArchivCel(const string &ac)
{
	archivCel = ac;
}

/**
 Establece la ruta por defecto de los archivos de celula.
 @param ac, string.
 */
void OpcionesPref::setArchivCSV(const string &ac)
{
	archivCSV = ac;
}

/**
 Establece el color del limite derecho y inferior de la rejilla.
 @para ldi, Gdk::Color.
 */
void OpcionesPref::setLimDI(Gdk::Color ldi)
{
	limDIR = ldi.get_red();
	limDIG = ldi.get_green();
	limDIB = ldi.get_blue();
}

/**
 Establece el color del limite izquierdo y superior de la rejilla.
 @para lis, Gdk::Color.
 */
void OpcionesPref::setLimIS(Gdk::Color lis)
{
	limISR = lis.get_red();
	limISG = lis.get_green();
	limISB = lis.get_blue();
}

/**
 Establece el color de la rejilla.
 @para crj, Gdk::Color.
 */
void OpcionesPref::setColRej(Gdk::Color crj)
{
	colRejR = crj.get_red();
	colRejG = crj.get_green();
	colRejB = crj.get_blue();
}

/**
 Establece el grosor de la rejilla.
 @param grj, double.
 */
void OpcionesPref::setGrosRej(double grj)
{
	grosRej = grj;
}

/**
 Establece la separacion entre los puntos de la rejilla.
 param sp, double.
 */
void OpcionesPref::setSeparPuntos(double sp)
{
	separPuntos = sp;
}

/**
 Establece el grosor del borde de la rejilla.
 @param gbr, double.
 */
void OpcionesPref::setGrosBordeRej(double gbr)
{
	grosBordeRej = gbr;
}

/**
 Estabelce el valor de las micras por pixel.
 @param m, double.
 @deprecated
 */
void OpcionesPref::setValorMicras(double m)
{
	valorMicras = m;
}

/**
 Establece el valor de la beta para calculo del umbral.
 @param b, double.
 @deprecated
 */
void OpcionesPref::setValorBeta(double b)
{
	valorBeta = b;
}

/**
 Establece el valor de la activacion del borde de la rejilla.
 @param cond, bool.
 @deprecated
 */
void OpcionesPref::setBordeComp(bool cond)
{
	actBordeRej = cond;
}

/**
 Establece el valor del login de la bd.
 @param lbd, string.
 */
void OpcionesPref::setLoginBD(const string &lbd)
{
	loginBD = lbd;
}

/**
 Establece el pass de la bd.
 @param pbd, string.
 */
void OpcionesPref::setPassBD(const string &pbd)
{
	passBD = pbd;
}

/**
 Establece la ruta de la bd.
 @param dbd, string.
 */
void OpcionesPref::setDirecBD(const string &dbd)
{
	rutaBD = dbd;
}

/**
 Establece el nombre de la base de datos.
 @param dbdb, string.
 */
void OpcionesPref::setDataBaseBD(const string &dbdb)
{
	dataBaseBD = dbdb;
}

/**
 Establece el login del sftp.
 @param c, string.
 */
void OpcionesPref::setLoginSFTP(const string &c)
{
	loginSFTP = c;
}

/**
 Establece la contraseña del sftp.
 @param c, string.
 */
void OpcionesPref::setPassSFTP(const string &c)
{
	passSFTP = c;
}

/**
 Establece la direccion del sftp.
 @param c, string.
 */
void OpcionesPref::setDirecSFTP(const string &c)
{
	rutaSFTP = c;
}

/**
 Establece el path del sftp.
 @param c, string.
 */
void OpcionesPref::setPathSFTP(const string &c)
{
	pathSFTP = c;
}

/**
 Establece el tamaño de la cache
 @param tc, int.
 */
void OpcionesPref::setTamCache(int tc)
{
	tamCache = tc;
}

/**
 Recarga los valores por defecto del panel de preferencias
 */
void OpcionesPref::revertirDatos()
{
	//Editor
	this->celSDetR = 6656;
	this->celSDetG = 59136;
	this->celSDetB = 52992;
	this->seleCelR = 13568;
	this->seleCelG = 60416;
	this->seleCelB = 768;
	this->ediCelR = 63488;
	this->ediCelG = 63232;
	this->ediCelB = 1792;
	this->grosLinea = 20;
	this->grosPunto = 26;
	//Rejilla
	this->limDIR = 63488;
	this->limDIG = 4864;
	this->limDIB = 1792;
	this->limISR = 9216;
	this->limISG = 63488;
	this->limISB = 1792;
	this->colRejR = 46592;
	this->colRejG = 63488;
	this->colRejB = 1792;
	this->grosRej = 20;
	this->separPuntos = 180;
	this->grosBordeRej = 20;
	this->actBordeRej = false;
	//Variables
	this->valorMicras = 3.45;
	this->valorBeta = 1;
	
	//Cache imagenes
	tamCache = 30;
}

/**
 Sobrecarga del operador de asignacion
 */
const OpcionesPref &OpcionesPref::operator=(const OpcionesPref &op)
{	
	//Editor
	this->celSDetR = op.celSDetR;
	this->celSDetG = op.celSDetG;
	this->celSDetB = op.celSDetB;
	this->seleCelR = op.seleCelR;
	this->seleCelG = op.seleCelG;
	this->seleCelB = op.seleCelB;
	this->ediCelR = op.ediCelR;
	this->ediCelG = op.ediCelG;
	this->ediCelB = op.ediCelB;
	this->grosLinea = op.grosLinea;
	this->grosPunto = op.grosPunto;
	
	//Directorios
	this->archivImag =op.archivImag;
	this->archivCel = op.archivCel;
	this->archivCSV = op.archivCSV;
	
	//Rejilla
	this->limDIR = op.limDIR;
	this->limDIG = op.limDIG;
	this->limDIB = op.limDIB;
	this->limISR = op.limISR;
	this->limISG = op.limISG;
	this->limISB = op.limISB;
	this->colRejR = op.colRejR;
	this->colRejG = op.colRejG;
	this->colRejB = op.colRejB;
	this->grosRej = op.grosRej;
	this->separPuntos = op.separPuntos;
	this->grosBordeRej = op.grosBordeRej;
	this->actBordeRej = op.actBordeRej;
	
	//Variables
	this->valorMicras = op.valorMicras;
	this->valorBeta = op.valorBeta;

	//Base de datos
	this->loginBD = op.loginBD;
	this->passBD = op.passBD;
	this->rutaBD = op.rutaBD;
	this->dataBaseBD = op.dataBaseBD;

	//Secure ftp
	this->loginSFTP = op.loginSFTP;
    this->passSFTP = op.passSFTP;
    this->rutaSFTP = op.rutaSFTP;
    this->pathSFTP = op.pathSFTP;
	
	//Cache imagenes
	this->tamCache = op.tamCache;
	
	return *this;
}
