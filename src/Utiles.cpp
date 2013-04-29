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

#include "Utiles.h"

/**
 Funcion que le un fichero escrito con glade y obtiene los nodos, los
 cuales son apuntados por un puntero. 
 */
void Utiles::getWidgetGlade(const string &filename,const char* root_node,const char *widget_name,...)
{
	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	Gtk::Widget *gui = 0;
	va_list args;
	const char *name;
	
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		refXml = Gnome::Glade::Xml::create(filename, root_node);
	}
	catch(const Gnome::Glade::XmlError& ex)
	{
		cerr << ex.what() <<endl;
	}
	#else
	auto_ptr<Gnome::Glade::XmlError> error;
	refXml = Gnome::Glade::Xml::create(filename.c_str(), root_node);
	if(error.get())
	{
		cerr << error->what() <<endl;
	}
	#endif
	
	va_start (args, widget_name);
	for (name = widget_name; name; name = va_arg (args, const char *) )
	{
		Gtk::Widget **wid;

		wid = va_arg (args, Gtk::Widget **);
		*wid = refXml->get_widget(name,gui);
	}
	va_end (args);
}

/**
 Funcion que le un fichero escrito con gtk builder y obtiene los nodos, los
 cuales son apuntados por un puntero.
 */
void Utiles::getObjectBuilder(const string &filename, const Glib::StringArrayHandle root_objects, const char *object_name,...)
{
	Glib::RefPtr<Gtk::Builder> builder;
	va_list args;
	const char *name;

	if(root_objects.size())
	{
		builder->add_from_file(filename, root_objects);
	}
	else
	{
		builder->add_from_file(filename);
	}

	va_start (args, object_name);
	for (name = object_name; name; name = va_arg (args, const char *))
	{
		Glib::RefPtr<Glib::Object> *objeto;

		objeto = va_arg(args, Glib::RefPtr<Glib::Object> *);
		*objeto = builder->get_object(name);
	}
	va_end (args);
}

/**
 Obtiene la terminación del fichero.
 @param tipo, string tipo de fichero.
 @return string.
 */
string Utiles::obtieneTipoArch(const string &tipo)
{
	return tipo.substr(((tipo.length())-3),(tipo.length()));
}

/**
 Obtiene el nombre de un fichero si su terminacion
 @param nomArch nombre del fichero con terminacion
 @return nombre del fichero sin la terminacion
 */
string Utiles::obtieneNombreArch(const string &nomArch)
{
	size_t found;

	found = nomArch.find_last_of(".");

	return nomArch.substr(0, found);
}

/**
 Funcion que devuelve la localizacion del archivo de configuracion
 @return string.
 */
string Utiles::obtenerDireccionConfig()
{
	#ifdef G_OS_WIN32
	return Glib::build_filename(getDataDir(), "config");
	#else
	return Glib::build_filename(Glib::get_user_config_dir(),"govocitos");
	#endif
}

/**
 Obtiene el directorio cache designado por defecto por gtk
 @return devuelve un string con la direccion del directorio cache
 */
string Utiles::obtenerDireccionCache()
{
	#ifdef G_OS_WIN32
	return Glib::build_filename(Glib::get_user_config_dir(),"imagenesGovocitos");
	#else
	return Glib::build_filename(Glib::get_user_cache_dir(),"govocitos");
	#endif
}

/**
 Obtiene el directorio cache designado para las imagenes reducidas.
 @return devuelve un string con la direccion del directorio cache.
 */
string Utiles::obtenerDireccionCacheImgReduced()
{
	#ifdef G_OS_WIN32
	return Glib::build_filename(Glib::get_user_config_dir(),"imgReducGovocitos");
	#else
	return Glib::build_filename(Glib::get_user_cache_dir(),"govocitosReduc");
	#endif
}

/**
 Convierte un int a un string.
 @param valor, int.
 @return string.
 */
string Utiles::converString(int valor)
{
	ostringstream flujo;
	
	flujo << valor;
	
	return flujo.str();

}

/**
 Convierte un long int a un string.
 @param valor, long int.
 @return string.
 */
string Utiles::converString(long int valor)
{
	ostringstream flujo;
	
	flujo << valor;
	
	return flujo.str();

} 

/**
 Convierte un double a un string.
 @param valor, double.
 @return string.
 */
string Utiles::converString(double valor)
{
	ostringstream flujo;
	
	flujo << valor;
	
	return flujo.str();

}

/**
 Convierte un char a un string.
 @param cad, char.
 @return string.
 */
string Utiles::convertCharToString(char *cad)
{
	ostringstream flujo;
	
	flujo << cad;
	
	return flujo.str();
}

/**
 Detecta el sistema operativo en el que nos encontramos.
 @return string.
 */
string Utiles::getDataDir()
{
	string packagedatadir;
	
	#ifdef G_OS_WIN32
	char *win32Dir;
	
	win32Dir = g_win32_get_package_installation_directory_of_module(NULL);
	packagedatadir = Glib::build_filename(win32Dir, "src");
	g_free(win32Dir);
	#else
	packagedatadir = Glib::build_filename(PACKAGE_DATA_DIR, "govocitos");
	#endif

	return packagedatadir;
}

/**
 Devuelve la ruta de los ficheros glade.
 @param file, string.
 @return string.
 */
string Utiles::getGladeFile(const string &file)
{	
	vector<string> datadir;
	
	datadir.push_back(getDataDir());
	datadir.push_back("Glade");
	datadir.push_back(file);
	
	return Glib::build_filename(datadir);
}

/**
 Devuelve la ruta de los iconos.
 @param file, string.
 @return string.
 */
string Utiles::getIconoFile(const string &file)
{
	vector<string> pixmapdir;
	
	pixmapdir.push_back(getDataDir());
	pixmapdir.push_back("Iconos");
	pixmapdir.push_back(file);
	
	return Glib::build_filename(pixmapdir);
}

/**
 Devuelve la ruta del fichero de clasificacion.
 @param file, string nombre del fichero.
 @param carpeta, string nombre de la carpeta.
 @return string.
 */
string Utiles::getClasificadorFile(const string &file, const string &carpeta)
{
	vector<string> clasificadordir;
	
	clasificadordir.push_back(getDataDir());
	#ifdef G_OS_WIN32
	clasificadordir.push_back("Clasificador");
	#endif
	clasificadordir.push_back(carpeta);
	clasificadordir.push_back(file);
	
	return Glib::build_filename(clasificadordir);
}

/**
 Obtiene la direccion del fichero de configuracion.
 @param fichero, string.
 @return string.
 */
string Utiles::direccionConfig(const string &fichero)
{
	return Glib::build_filename(obtenerDireccionConfig(), fichero);
}

/**
 Devuelve el path completo de la cache de imagenes
 @param fichero nombre con el que se almacena el fichero en la cache de imagenes
 @return Devuelve un string con el path completo de almacenamiento
 */
string Utiles::direccionCache(const string &fichero)
{
	return Glib::build_filename(obtenerDireccionCache(), fichero);
}

/**
 Devuelve el path completo de la cache de imagenes reducidas
 @param fichero nombre con el que se almacena el fichero en la cache de imagenes
 @return Devuelve un string con el path completo de almacenamiento
 */
string Utiles::direccionCacheReduced(const string &fichero)
{	
	return Glib::build_filename(obtenerDireccionCacheImgReduced(), fichero);
}

/**
 Crea un directorio en el caso de que no exista
 @param path path del directorio que deseamos crear
 */
void Utiles::creaDirectorio(const string &path)
{	
	if (!Glib::file_test(path, Glib::FILE_TEST_IS_DIR))
	{
		Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(path) ;
		
		if (Glib::file_test(path, Glib::FILE_TEST_IS_REGULAR))
		{
			if (!fich->remove())
			{
				//cout<<"Error al borrar el fichero"<<endl;
				cout<<"Error while deleting the file"<<endl;
			}
		}
		
		if (!fich->make_directory())
		{
			//cout<<"Error al crear el directorio"<<endl;
			cout<<"Error while creating the folder"<<endl;
		}
	}	
}

/**
 Funcion que localiza las coordenadas max y min de un poligono nuevo.
 @param cX, int coordenada x.
 @param cy, int coordenada y.
 @param zoom, double contiene valor del zoom.
 @param cell, objeto de la Celula.
 */
void Utiles::calculoCoordMaxMin(int cX, int cY, double zoom, Celula &cell)
{
	if(cell.getCoordMaxMin(0) == 0)
	{
		cell.setCoordMaxMin(0, (cX / zoom));
		cell.setCoordMaxMin(1, (cX / zoom));
		cell.setCoordMaxMin(2, (cY / zoom));
		cell.setCoordMaxMin(3, (cY / zoom));
	}
	else
	{
		if(cell.getCoordMaxMin(0) < (cX / zoom))
		{
			//Coordenada X Max
			cell.setCoordMaxMin(0, (cX / zoom));
		}
		if(cell.getCoordMaxMin(1) > (cX / zoom))
		{
			//Coordenada X Min
			cell.setCoordMaxMin(1, (cX / zoom));
		}
		if(cell.getCoordMaxMin(2) < (cY / zoom))
		{
			//Coordenada Y Max
			cell.setCoordMaxMin(2, (cY / zoom));
		}
		if(cell.getCoordMaxMin(3) > (cY / zoom))
		{
			//Coordenada Y Max
			cell.setCoordMaxMin(3, (cY / zoom));
		}
	}
}

/**
 Actualiza la vista de la interfaz
 */
void Utiles::actualizarInterfaz()
{
	while(Gtk::Main::events_pending())
	{
		Gtk::Main::iteration();
	}
}

/**
 Reordena N decimales.
 @param num, double.
 @param dec, int.
 */
double Utiles::redondearNDecimales(double num, int dec)
{
	double numOut;

	if(dec == 0)
	{
		numOut = (int)num;
	}
	else
	{
		numOut = double(int(num * pow(10.0, dec) +.5)) / pow(10.0, dec);
	}

	return numOut;
}

/**
 Convierte double con todos sus caracteres a un double.
 @param num, double.
 @return int.
 */
int Utiles::doubleToIntWhichAllCharacter(double num)
{
	int numInt;
	ostringstream flujo;
	string numStr;
	
	flujo << num;

	numStr = flujo.str();
	
	numInt = num * pow(10.0, (int)numStr.length());

	return numInt;
}

/**
 Obtiene el time stamp.
 @return string.
 */
string Utiles::timestamp()
{
	string fechHora;
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);

    fechHora = Utiles::convertCharToString(buffer);

	return fechHora;
}
