/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Fichero.cpp
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

#include "Fichero.h"
#include "Config/ConfigGovocitos.h"

/**
 Lee los datos del fichero y los asigna al objeto ListadoCelulas.
 @param ruta, string que contiene la ruta del fichero de celulas.
 @param &conjunCelulas, objeto ListadoCelulas que contendra los datos de las
 celulas contenidas en el fichero.
 */
void Fichero::leerFich(const string &ruta, ListadoCelulas &conjunCelulas)
{	
	Celula indivCelula;
	int coordX, coordY, comienzoSub, x, numCarac;
	string linea;
	Glib::ustring tipoPoligono, classPoligono;
	bool grabado = false;
	ifstream fentrada;
	coordX = coordY = 0;
	vector<int> cx, cy;
	
	//Abrimos el fichero y le asociamos el buffer
	fentrada.open(ruta.c_str(), ios::in);
	
	if(!fentrada)
	{
		//cout<<"Error, no se puede leer el fichero"<<endl;
		cout<<"Error while reading the file"<<endl;
	}
	
	while(!fentrada.eof())
	{
		//Leemos un linea entera hasta encontrar \n
		getline(fentrada,linea,'\n');
		
		if (linea[0] == 'P' || linea[0] == 'p')
		{	
			x = 0;
			tipoPoligono = classPoligono = "";
			
			if (grabado)//Solo no se ejecuta la primera vez el resto si
			{
				//Guardamos un poligono en el objeto de la clase OperPoligonos
				indivCelula.setCoordCellX(cx);
				indivCelula.setCoordCellY(cy);
				conjunCelulas.setCelula(indivCelula);
				//Reseteamos valores almacenados
				cx.clear();
				cy.clear();
				coordX = 0;
				coordY = 0;
			}
			for(unsigned int i = 0; i < linea.length(); i++)
			{
				if(linea[i] == ' ')
				{	
					x = ++i;
					
					do
					{
						x++;
					}while(linea[x] != ' ');
										
					//Asignamos el numero de poligono
					indivCelula.setIdCelula(atoi(linea.substr(i,x).data()));
					break;				
				}
			}
			for(unsigned int j = x; j < linea.length(); j++)
			{
				if(linea[j] != ' ')
				{
					comienzoSub = j;
					x = j;
					
					do
					{
						x++;
					}while(isxdigit(linea[x]));
						
					//Asignamos el tipo de poligono
					if(tipoPoligono == "")
					{
						x++;
						numCarac = x - comienzoSub;
						tipoPoligono = linea.substr(comienzoSub, numCarac);
						indivCelula.setClaseCelula(tipoPoligono.lowercase());
						j = x;
					}
					else
					{
						x++;
						numCarac = x - comienzoSub;
						classPoligono = linea.substr(comienzoSub, numCarac);
						indivCelula.setEstadoCelula(classPoligono.lowercase());
						j = x;
						break;
					}
				}
			}
			grabado = true;
		}
		else
		{
			for(unsigned int i = 0; i < linea.length(); i++)
			{
				if(linea[i] == ' ')
				{
					//Introducimos coordenadas x e y de cada linea
					coordX = atoi(linea.substr(0,i).data());
					coordY = atoi(linea.substr(i,linea.length()).data());
					
					//Introducimos las coordenadas en el vector de coordenadas
					cx.push_back(coordX);
					cy.push_back(coordY);
					
					//Calculamos las coord max y min
					Utiles::calculoCoordMaxMin(coordX,coordY,1,indivCelula);
					
					break;
				}
			}
		}	
	}
	
	//Cerramos el fichero
	fentrada.close();
	
	//Guardamos un poligono en el objeto de la clase OperPoligonos
	conjunCelulas.setCelula(indivCelula);
	
}//leerFich

/**
 Escribe los datos de los poligonos en un fichero txt.
 @param ruta, string que contiene la ruta del fichero de celulas.
 @param &conjunCelulas, objeto LstadoCelulas que contiene la informacion de todas
 las celulas de la imagen.
 */
void Fichero::escribFich(const string &ruta, ListadoCelulas &conjunCelulas)
{
	ofstream fsalida;
	string linea;
	Celula *cell;
	int numPoligonos, numCoordPol;
	vector<int> *cx, *cy;
	
	fsalida.open(ruta.c_str(), ios::out);
	
	if(!fsalida)
	{
		//cout<<"Error, no se puede leer el fichero"<<endl;
		cout<<"Error while reading the file"<<endl;
	}
	
	//Asignamos el tamaño del vector de poligonos
	numPoligonos = conjunCelulas.getNumCelulas();
	
	for(int i = 0; i < numPoligonos; i++)
	{
		//Obtenemos el poligono
		cell = conjunCelulas.getCelula(i);
		
		//Asignamos el numero de coordendas del poligono
		cx = cell->getBordeCellX();
		cy = cell->getBordeCellY();
		numCoordPol = cx->size();
			
		//Declaracion del flujo, en cada pasada se reseteara
		ostringstream flujo1;
		
		//Introducimos los datos en el flujo para obtenerlos todos en un string
		flujo1<<cell->getIdCelula();
		
		//Pasamos la informacion del flujo al string
		linea = "Poligono " + flujo1.str() + " " + cell->getClaseCelula() + " " 
			+ cell->getEstadoCelula();

		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;	
		
		for(int j = 0; j < numCoordPol; j++)
		{
			//Declaracion del flujo, en cada pasada se reseteara
			ostringstream flujo1, flujo2;
			
			//Coordenada x en flujo1 y coordenada y en flujo2
			flujo1 << (*cx)[j];
			flujo2 << (*cy)[j];
			
			//Concatenamos los dos flujos y los pasamos a linea
			linea = flujo1.str() + " " + flujo2.str();
			
			//Intoducimos la linea en el fichero
			fsalida<<linea<<endl;
		}
	}
	
	//Cerramos el fichero
	fsalida.close();
}

/**
 Abre el fichero xml y lo almacena en el objeto de la clase ListadoCelulas. El formato
 el fichero es el siguiente:
 <?xml version="1.0" encoding="UTF-8"?>
 <govocitos>
   <poligono numero=1 clase="sn" estado="class">
     <coords>
       <x>valor</x>
       <y>valor</y>
     </coords>
   </poligono>
 </govocitos>
 @parma ruta, string path del fichero xml.
 @param &conjunCelulas, referencia a ListadoCelulas que contendra los datos de
 las celulas contenidas en el fichero.
 */
void Fichero::leerFichXml(const string &ruta, ListadoCelulas &conjunCelulas)
{
	// Parse the entire document in one go:
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	try
	{
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
		XmlParse p(conjunCelulas);
		p.set_substitute_entities(true); //
		p.parse_file(ruta);
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	}
	catch(const xmlpp::exception& ex)
	{
		//cout << "Excepcion libxml " << ex.what() << endl;
		cout << "Exception libxml " << ex.what() << endl;
	}
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED

	//Leemos el ultimo id de celulas para acutalizarlo
	if(conjunCelulas.getLastIdCell() == -1)
	{
		int aux = -1;
		int idC = -1;
		int numCel = conjunCelulas.getNumCelulas();
		
		for(int i = 0; i < numCel; i++)
		{
			aux = conjunCelulas.getCelula(i)->getIdCelula();
			
			if(idC <= aux)
			{
				idC = aux;
			}
		}

		conjunCelulas.setLastIdCell(idC);
	}
}

/**
 Escribe los datos de las celulas en un fichero xml. 
 El formato del fichero sera el siguiente:
 <?xml version="1.0" encoding="UTF-8"?>
 <govocitos>
   <poligono numero=1 etiqueta="sn" clase="class">
     <coords>
       <x>valor</x>
       <y>valor</y>
     </coords>
   </poligono>
 </govocitos>
 @param ruta, string path del fichero xml.
 @param &conjunCelulas, referencia a ListadoCelulas que contiene las celulas de
 la imagen actual.
 */
void Fichero::escribFichXml(const string &ruta, ListadoCelulas &conjunCelulas)
{
	ofstream fsalida;
	string linea;
	Celula *cell;
	int numPoligonos, numCoordPol;
	ostringstream flujo0;
	vector<int> *cx, *cy;
	fsalida.open(ruta.c_str(), ios::out);
	
	if(!fsalida)
	{//Provisional luego hay que cambiarlo por excepciones-------------------
		//cout<<"Error, no se puede leer el fichero"<<endl;
		cout<<"Error while reading the file"<<endl;
	}

	flujo0<<conjunCelulas.getLastIdCell();
	
	//Creamos la cabecera del archivo
	fsalida<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
	fsalida<<"<govocitos idcelulas=\"" + flujo0.str() + "\">"<<endl;
	
	//Asignamos el tamaño del vector de poligonos
	numPoligonos = conjunCelulas.getNumCelulas();
	
	for(int i = 0; i < numPoligonos; i++)
	{
		//Obtenemos el poligono
		cell = conjunCelulas.getCelula(i);
		
		//Asignamos el numero de coordendas del poligono
		cx = cell->getBordeCellX();
		cy = cell->getBordeCellY();		
		numCoordPol = cx->size();
		
		//Declaracion del flujo, en cada pasada se reseteara
		ostringstream flujo1, flujo2, flujo3;
		
		//Introducimos los datos en el flujo para obtenerlos todos en un string
		flujo1<<cell->getIdCelula();
		flujo2<<cell->getDiametroCell();
		flujo3<<cell->getCelulaCandidata();
		
		//Pasamos la informacion del flujo al string
		linea = "  <poligono numero=\"" + flujo1.str() + "\" clase=\"" + 
			cell->getClaseCelula() + "\" estado=\"" + cell->getEstadoCelula() +
			"\" diametroCelula=\"" + flujo2.str() +  "\" numeroCandidato=\"" + 
			flujo3.str() + "\">";
		
		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;	
		
		fsalida<<"    <coords>"<<endl;		
		
		for(int j = 0; j < numCoordPol; j++)
		{
			//Declaracion del flujo, en cada pasada se reseteara
			ostringstream flujo1, flujo2;
	
			//Coordenada x en flujo1 y coordenada y en flujo2
			flujo1<<(*cx)[j];
			flujo2<<(*cy)[j];
			
			//Concatenamos los dos flujos y los pasamos a linea
			linea = "      <x>" + flujo1.str() + "</x>";
			fsalida<<linea<<endl;
			linea = "      <y>" + flujo2.str() + "</y>";
			fsalida<<linea<<endl;
		}
		fsalida<<"    </coords>"<<endl;
		fsalida<<"  </poligono>"<<endl;
	}
	fsalida<<"</govocitos>"<<endl;
	//Cerramos el fichero
	fsalida.close();
	
}

/**
 Lee los datos del archivo de configuracion que contiene las preferencias del programa.
 @param ruta, string path del fichero de configuracion.
 @param &ope, referencia a OpcionesPref que contiene las preferencias del programa.
 @deprecated
 */
void Fichero::leerFichConfig(const string &ruta, OpcionesPref &ope)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);

	if (!fentrada)
	{
		escribFichConfig(ruta, ope);
	}
	else
	{
		fentrada.read((char*)&ope,sizeof(OpcionesPref));
		
		fentrada.close();
	}
	
}

/**
 Escribe las preferencias del programa en el fichero de configuracion.
 @param ruta, string path del fichero de configuracion.
 @param &ops, referencia a OpcionesPref que contiene las preferencias del programa.
 @deprecated
 */
void Fichero::escribFichConfig(const string &ruta, OpcionesPref &ops)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);
	
	fsalida.write((char*)&ops,sizeof(OpcionesPref));
	
	fsalida.close();
	
}

/**
 Lee las clases almacenados en el fichero de estados.
 @param ruta, string path con la ruta del fichero.
 @param &ete, referencia al vector<EstadoCelula> que contiene las clases.
 @deprecated
 */
void Fichero::leerFichClases(const string &ruta, vector<ClaseCelula> &ete)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	ClaseCelula etiClas;
	
	if (!fentrada)
	{
		escribFichClases(ruta, ete);
	}
	else
	{
		fentrada.read((char*)&etiClas,sizeof(ClaseCelula));
		
		while(!fentrada.eof())
		{
			ete.push_back(etiClas);
			fentrada.read((char*)&etiClas,sizeof(ClaseCelula));
		}
		
		fentrada.close();
	}	
}

/**
 Guarda todas las clases del sistema en un fichero de configuracion para su posterior
 uso.
 @param ruta, string path con la ruta del fichero.
 @param &ets, referencia al vector<EstadoCelula> que contiene las clases.
 @deprecated
 */
void Fichero::escribFichClases(const string &ruta, vector<ClaseCelula> &ets)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);
	
	for(unsigned int i = 0; i < ets.size(); i++)
	{
		fsalida.write((char*)&ets[i],sizeof(ClaseCelula));
	}
	
	fsalida.close();
	
}

/**
 Lee los estados almacenados en el fichero de estados.
 @param ruta, string path con la ruta del fichero.
 @param &ete, referencia al vector<EstadoCelula> que contiene los estados.
 @deprecated
 */
void Fichero::leerFichEstados(const string &ruta, vector<EstadoCelula> &ete)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	EstadoCelula etiEst;
	
	if (!fentrada)
	{
		escribFichEstados(ruta, ete);
	}
	else
	{
		fentrada.read((char*)&etiEst,sizeof(EstadoCelula));
		
		while(!fentrada.eof())
		{
			ete.push_back(etiEst);
			fentrada.read((char*)&etiEst,sizeof(EstadoCelula));
		}
		
		fentrada.close();
	}	
}

/**
 Guarda todas los estados del sistema en un fichero de configuracion para su posterior
 uso.
 @param ruta, string path con la ruta del fichero.
 @param &ets, referencia al vector<EstadoCelula> que contiene los estados.
 @deprecated
 */
void Fichero::escribFichEstados(const string &ruta, vector<EstadoCelula> &ets)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);
	
	for(unsigned int i = 0; i < ets.size(); i++)
	{
		fsalida.write((char*)&ets[i],sizeof(EstadoCelula));
	}
	
	fsalida.close();	
}

/**
 Lee las opciones de la rejilla personalizada.
 @param ruta, string que contiene el path de la ruta del fichero de la rejilla.
 @param &ope, referencia al vector<OpcionesRej> que contiene los datos de las rejillas.
 @deprecated
 */
void Fichero::leerFichOpcionesRej(const string &ruta, vector<OpcionesRej> &ope)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	OpcionesRej opcR;
	
	if (!fentrada)
	{
		escribFichOpcionesRej(ruta, ope);
	}
	else
	{
		fentrada.read((char*)&opcR,sizeof(OpcionesRej));
		
		while(!fentrada.eof())
		{
			ope.push_back(opcR);
			fentrada.read((char*)&opcR,sizeof(OpcionesRej));
		}
		
		fentrada.close();
	}	
}

/**
 Escribe las opciones de la rejilla personalizada.
 @param ruta, string con el path que contiene la ruta del fichero.
 @param &ops, referencia al vector<OpcionesRej> que contiene los datos de las rejillas.
 @deprecated
 */
void Fichero::escribFichOpcionesRej(const string &ruta, vector<OpcionesRej> &ops)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);
	
	for(unsigned int i = 0; i < ops.size(); i++)
	{
		fsalida.write((char*)&ops[i],sizeof(OpcionesRej));
	}
	
	fsalida.close();
	
}

/**
 Lee el fichero de la cache que contiene los nombres de las imagenes almacenadas
 en la cache de imagenes.
 @param ruta, string con el path completo donde se encuentra la cache de imagenes.
 @param lce, list<string> lista donde se van almacenar los datos de la cache del fichero.
 @deprecated
 */
void Fichero::leerFichCache(const string &ruta, list<string> &lce)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	string buffer;
	
	if (!fentrada)
	{
		escribirFichCache(ruta, lce);
	}
	else
	{
		while(!fentrada.eof())
		{
			getline(fentrada,buffer,'\0');
			if(buffer != "")
			{
				lce.push_back(buffer);
			}
		}
		
		fentrada.close();
	}
}

/**
 Escribe el fichero de cache que contiene los nombres de las imagenes almacenadas
 en la cache de imagenes.
 @param ruta, string con el path completo donde se encuentra la cache de imagenes.
 @param lcs, list<string> lista que contiene los nombres de las imagenes de la cache.
 @deprecated
 */
void Fichero::escribirFichCache(const string &ruta, list<string> &lcs)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);

	for (list<string>::iterator it=lcs.begin(); it != lcs.end(); it++)
	{
			fsalida.write((char*)it->c_str(), it->length()+1);
	}
	
	fsalida.close();
}

/**
 Borra un fichero del sistema.
 @param ruta, string con el path del fichero a borrar.
 */
void Fichero::borraImagenSistema(const string &ruta)
{
	if (!Glib::file_test(ruta, Glib::FILE_TEST_IS_DIR))
	{
		Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(ruta) ;
		
		if (Glib::file_test(ruta, Glib::FILE_TEST_IS_REGULAR))
		{
			if (!fich->remove())
			{
				//cout<<"Error al borrar el fichero"<<endl;
				cout<<"Error while deleting the file"<<endl;
			}
		}
	}

}

/**
 Comprueba si existe el fichero en el sistema.
 @param ruta, string con el path completo del fichero a localizar.
 */
bool Fichero::compruebaFich(const string &ruta)
{
	ifstream fentrada;

	//Abrimos el fichero y le asociamos el buffer
	fentrada.open(ruta.c_str(), ios::in);
	
	if(!fentrada)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 */
void Fichero::escribXmlCache(const string &ruta, ConfigGovocitos &opcSistema)
{
	ofstream fsalida;
	string linea;
	list<string> dCache;
	
	dCache = *opcSistema.getDatosCache();
	
	fsalida.open(ruta.c_str(), ios::out);
	
	if(!fsalida)
	{
		//cout<<"Error, no se puede leer el fichero"<<endl;
		cout<<"Error while reading the file"<<endl;
	}

	//Creamos la cabecera del archivo
	fsalida<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
	fsalida<<"<govocitosCache>"<<endl;
	//Cache
	fsalida<<"  <listado_cache>"<<endl;

	for(list<string>::iterator it = dCache.begin(); it != dCache.end(); ++it)
	{
		linea = "    <cache nombre_imagen=\"" + *it + "\">" + "</cache>";
		
		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;
	}

	fsalida<<"  </listado_cache>"<<endl;

	fsalida<<"</govocitosCache>"<<endl;
	//Cerramos el fichero
	fsalida.close();
}

/**
 */
void Fichero::escribXmlPreferencias(const string &ruta, ConfigGovocitos &opcSistema)
{
	ofstream fsalida;
	string linea;
	vector<OpcionesRej> dRejilla;
	vector<ClaseCelula> dClases;
	vector<EstadoCelula> dEstados;
	OpcionesPref dPreferencias;

	dRejilla = *opcSistema.getDatosRejilla();
	dClases = *opcSistema.getDatosClases();
	dEstados = *opcSistema.getDatosEstados();
	dPreferencias = *opcSistema.getDatosPreferencias();
	
	fsalida.open(ruta.c_str(), ios::out);
	
	if(!fsalida)
	{
		//cout<<"Error, no se puede leer el fichero"<<endl;
		cout<<"Error while reading the file"<<endl;
	}

	//Creamos la cabecera del archivo
	fsalida<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
	fsalida<<"<govocitosPreferencias>"<<endl;
	//Clases
	fsalida<<"  <clases>"<<endl;

	int numClases = dClases.size();
	
	for(int i = 0; i < numClases; i++)
	{
		string enUso = "false";
		ostringstream flujo;

		flujo<<dClases[i].getLinea();
		
		if(dClases[i].getEnUso())
		{
			enUso = "true";
		}

		linea = "    <clase etiqueta=\"" + dClases[i].getEtiquetaClasificacion() + 
			"\" nombre=\"" + dClases[i].getNombreClasificacion() + 
			"\" descripcion=\"" + dClases[i].getDescripcionClasificacion() +
			"\" enUso=\"" + enUso +  "\" linea=\"" + flujo.str() + "\">" + "</clase>";

		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;
	}

	fsalida<<"  </clases>"<<endl;

	//Estados
	fsalida<<"  <estados>"<<endl;

	int numEstados = dEstados.size();

	for(int i = 0; i <  numEstados; i++)
	{
		string enUso = "false";
		ostringstream flujo1, flujo2, flujo3;

		flujo1<<dEstados[i].getColorEstadoR();
		flujo2<<dEstados[i].getColorEstadoG();
		flujo3<<dEstados[i].getColorEstadoB();
		
		if(dEstados[i].getEnUso())
		{
			enUso = "true";
		}

		linea = "    <estado etiqueta=\"" + dEstados[i].getEtiquetaClasificacion() + 
				"\" nombre=\"" + dEstados[i].getNombreClasificacion() + 
				"\" descripcion=\"" + dEstados[i].getDescripcionClasificacion() +
				"\" enUso=\"" + enUso +  "\" rojo=\"" + flujo1.str() + 
				"\" verde=\"" + flujo2.str() +  "\" azul=\"" + flujo3.str() +"\">" + "</estado>";

		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;
	}
	fsalida<<"  </estados>"<<endl;

	//Rejilla
	fsalida<<"  <rejillas>"<<endl;
	
	int numRejillas = dRejilla.size();
		
	for(int i = 0; i <  numRejillas; i++)
	{
		ostringstream flujo1, flujo2, flujo3, flujo4, flujo5;

		flujo1<<dRejilla[i].getID();
		flujo2<<dRejilla[i].getNumFilas();
		flujo3<<dRejilla[i].getNumColumnas();
		flujo4<<dRejilla[i].getNumPuntos();
		flujo5<<dRejilla[i].getSeparaPuntos();

		linea = "    <rejilla id=\"" + flujo1.str() + "\" numero_Filas=\"" + flujo2.str() +
			"\" numero_Columnas=\"" + flujo3.str() + "\" numero_Puntos=\"" + flujo4.str() +
			"\" separacion_puntos=\"" + flujo5.str() + "\">" + "</rejilla>";

		//Introducimos la linea en el fichero
		fsalida<<linea<<endl;
	}
	fsalida<<"  </rejillas>"<<endl;

	//Preferencias
	fsalida<<"  <preferencias>"<<endl;

	//Celula desconocida
	fsalida<<"    <celula_desconocida>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getCelSDetR()) + 
		"\" verde=\"" + Utiles::converString(dPreferencias.getCelSDetG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getCelSDetB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </celula_desconocida>"<<endl;

	//Celula seleccionada
	fsalida<<"    <celula_seleccionada>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getSeleCelR()) +
		"\" verde=\"" + Utiles::converString(dPreferencias.getSeleCelG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getSeleCelB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </celula_seleccionada>"<<endl;

	//Celula seleccionada
	fsalida<<"    <celula_edicion>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getEdiCelR()) + 
		"\" verde=\"" + Utiles::converString(dPreferencias.getEdiCelG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getEdiCelB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </celula_edicion>"<<endl;

	//Introducimos el grosor de la linea
	fsalida<<"    <grosor_celula linea=\"" + Utiles::converString(dPreferencias.getGrosLinea()) + "\">" + "</grosor_celula>"<<endl;
	
	//Introduciomos el grosor del punto
	fsalida<<"    <grosor_celula punto=\"" + Utiles::converString(dPreferencias.getGrosPunto()) + "\">" + "</grosor_celula>"<<endl;

	//Introducimos la localizacion de las imagenes
	fsalida<<"    <ruta imagenes=\"" + dPreferencias.getArchivImag() + "\">" + "</ruta>"<<endl;
	
	//Introducimos la localizacion de los ficheros de celulas
	fsalida<<"    <ruta celulas=\"" + dPreferencias.getArchivCel() + "\">" + "</ruta>"<<endl;
	
	//Introducimos la localizacion de los CSV
	fsalida<<"    <ruta csv=\"" + dPreferencias.getArchivCSV() + "\">" + "</ruta>"<<endl;

	//Borde rejilla limite derecho e inferior
	fsalida<<"    <rejilla_limite_derechoInferior>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getLimDIR()) + 
		"\" verde=\"" + Utiles::converString(dPreferencias.getLimDIG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getLimDIB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </rejilla_limite_derechoInferior>"<<endl;

	//Borde rejilla limite izquierdo y superior
	fsalida<<"    <rejilla_limite_izquierdoSuperior>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getLimISR()) + 
		"\" verde=\"" + Utiles::converString(dPreferencias.getLimISG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getLimISB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </rejilla_limite_izquierdoSuperior>"<<endl;

	//Color rejilla
	fsalida<<"    <color_rejilla>"<<endl;
	linea = "      <pref rojo=\"" + Utiles::converString(dPreferencias.getColRejR()) + 
		"\" verde=\"" + Utiles::converString(dPreferencias.getColRejG()) +
		"\" azul=\"" + Utiles::converString(dPreferencias.getColRejB()) + "\">" + "</pref>";
	//Introducimos la linea en el fichero
	fsalida<<linea<<endl;
	fsalida<<"    </color_rejilla>"<<endl;

	//Introducimos el grosor de la rejilla
	fsalida<<"    <grosor rejilla_completa=\"" + Utiles::converString(dPreferencias.getGrosRej()) + "\">" + "</grosor>"<<endl;

	//Introducimos el grosor borde de la rejilla
	fsalida<<"    <grosor borde_rejilla_completa=\"" + Utiles::converString(dPreferencias.getGrosBordeRej()) + "\">" + "</grosor>"<<endl;

	//Introducimos la separación de puntos de la rejilla completa
	fsalida<<"    <separacion puntos_rejilla_completa=\"" + Utiles::converString(dPreferencias.getSeparPuntos()) + "\">" + "</separacion>"<<endl;

	//Introducimos el login de la BD
	fsalida<<"    <bd loginBD=\"" + dPreferencias.getLoginBD() + "\">" + "</bd>"<<endl;

	//Introducimos el pass de la BD
	fsalida<<"    <bd passwordBD=\"" + dPreferencias.getPassBD() + "\">" + "</bd>"<<endl;
	
	//Introducimos la direccion de la BD
	fsalida<<"    <bd urlBD=\"" + dPreferencias.getDirecBD() + "\">" + "</bd>"<<endl;
	
	//Introducimos el nombre de la BD
	fsalida<<"    <bd nombreBD=\"" + dPreferencias.getDataBaseBD() + "\">" + "</bd>"<<endl;

	//Introducimos el login de la SFTP
	fsalida<<"    <sftp loginSFTP=\"" + dPreferencias.getLoginSFTP() + "\">" + "</sftp>"<<endl;

	//Introducimos el pass de la SFTP
	fsalida<<"    <sftp passwordSFTP=\"" + dPreferencias.getPassSFTP() + "\">" + "</sftp>"<<endl;
	
	//Introducimos la direccion de la SFTP
	fsalida<<"    <sftp urlSFTP=\"" + dPreferencias.getDirecSFTP() + "\">" + "</sftp>"<<endl;
	
	//Introducimos el nombre de la SFTP
	fsalida<<"    <sftp pathSFTP=\"" + dPreferencias.getPathSFTP() + "\">" + "</sftp>"<<endl;

	//Introducimos el tamaño de la cache
	fsalida<<"    <cache tamanho=\"" + Utiles::converString(dPreferencias.getTamCache()) + "\">" + "</cache>"<<endl;
	
	fsalida<<"  </preferencias>"<<endl;

	fsalida<<"</govocitosPreferencias>"<<endl;
	//Cerramos el fichero
	fsalida.close();
}

/**
 */
void Fichero::leerXmlPreferencias(const string &ruta, ConfigGovocitos &sistemConf)
{
	ConfigGovocitos *sc = &sistemConf;
	
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	
	if (!fentrada)
	{
		Fichero::escribXmlPreferencias(ruta, *sc);
	}
		
	fentrada.close();
	
	// Parse the entire document in one go:
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	try
	{
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
		XmlPreferencias p(*sc);
		p.set_substitute_entities(true); //
		p.parse_file(ruta);
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	}
	catch(const xmlpp::exception& ex)
	{
		//cout << "Excepcion libxml " << ex.what() << endl;
		cout << "Exception libxml " << ex.what() << endl;
	}
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
}	

/**
 */
void Fichero::leerXmlCache(const string &ruta, ConfigGovocitos &opcSistema)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);
	
	if (!fentrada)
	{
		Fichero::escribXmlCache(ruta, opcSistema);
	}
		
	fentrada.close();

	// Parse the entire document in one go:
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	try
	{
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
		XmlCache p(*opcSistema.getDatosCache());
		p.set_substitute_entities(true); //
		p.parse_file(ruta);
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	}
	catch(const xmlpp::exception& ex)
	{
		//cout << "Excepcion libxml " << ex.what() << endl;
		cout << "Exception libxml " << ex.what() << endl;
	}
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
}	