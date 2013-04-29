/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoAGLocal.cpp
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

#include "DialogoAGLocal.h"

/**
 Constructor.
 @param img, string que contiene la ruta por defecto de las imagenes.
 @param xml, string que contiene la ruta por defecto de los xml.
 */
DialogoAGLocal::DialogoAGLocal(const string &img, const string &xml)
{
	rutaImagenes = img;
	rutaXml = xml;
}

/**
 Destructor.
 */
DialogoAGLocal::~DialogoAGLocal()
{
	delete dialog;
}

/**
 Dialogo Abrir una imagen.
 @param *img, puntero al objeto ImageCells que contiene los datos de la imagen
 actual del sistema.
 @return bool, devuelve verdadero si el usuario selecciona una imagen y falso en
 caso contrario.
 */
bool DialogoAGLocal::dialogoAbrirImagen(ImageCells *img)
{	
	Gtk::Image *preview;
	vector<string> nomImg;
	string rutaImagen;
	
    preview	= new Gtk::Image;
	//dialog = new Gtk::FileChooserDialog("Abrir Imagen", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog = new Gtk::FileChooserDialog("Open Image", Gtk::FILE_CHOOSER_ACTION_OPEN);
	
	dialog->set_icon_from_file(Utiles::getIconoFile("carpeta.png"));
	
	dialog->set_preview_widget(*preview);
    dialog->signal_selection_changed().
		connect(sigc::bind(sigc::mem_fun(this, &DialogoAGLocal::on_update_preview), preview));

	//Botones de respuesta del dialogo
	dialog->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);	
	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	
	//Filtros de seleccion de archivos
	Gtk::FileFilter filtroImagen;
	//filtroImagen.set_name("Imagenes");
	filtroImagen.set_name("Images");
	filtroImagen.add_pattern("*.jpg");
	filtroImagen.add_pattern("*.jpeg");
	filtroImagen.add_pattern("*.jpe");
	filtroImagen.add_pattern("*.JPG");
	filtroImagen.add_pattern("*.JPEG");
	filtroImagen.add_pattern("*.JPE");
	filtroImagen.add_pattern("*.png");
	filtroImagen.add_pattern("*.PNG");
	filtroImagen.add_pattern("*.tif");
	filtroImagen.add_pattern("*.TIF");
	filtroImagen.add_pattern("*.tiff");
	filtroImagen.add_pattern("*.TIFF");
	dialog->add_filter(filtroImagen);
	Gtk::FileFilter filtroTodos;
	//filtroTodos.set_name("Todos los archivos");
	filtroTodos.set_name("All the files");
	filtroTodos.add_pattern("*");
	dialog->add_filter(filtroTodos);
	
	//Ruta por defecto
	dialog->set_current_folder(rutaImagenes);
	
	//Muestra el dialogo y espera la respuesta del usuario
	int opcion = dialog->run();
	
	//Seleccion de opcion -Abrir o Cancelar
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{
			size_t found;
			string nombreCompleto;
			 
			rutaImagen = dialog->get_filename();

			//Ruta
			img->setRutaImg(rutaImagen);
			
			//Nombre completo
			found = rutaImagen.find_last_of("/\\");
			nombreCompleto = rutaImagen.substr(found+1);
			img->setNombreImg(nombreCompleto);
			
			return true;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
	return false;
}

/**
 Dialogo Abrir ficheros xml que contienen los datos de las celulas de una imagen.
 @param *img, puntero al objeto ImageCells que contiene los datos de la imagen
 actual del sistema.
 @return bool, devuelve verdadero si el usuario selecciona un fichero xml y falso en
 caso contrario.
 */
bool DialogoAGLocal::dialogoAbrirXml(ImageCells *img)
{
	//dialog = new Gtk::FileChooserDialog("Abrir Xml", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog = new Gtk::FileChooserDialog("Open Xml", Gtk::FILE_CHOOSER_ACTION_OPEN);

	dialog->set_icon_from_file(Utiles::getIconoFile("carpeta.png"));
	
	//Botones de respuesta del dialogo
	dialog->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);	
	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	Gtk::FileFilter filtroXml;
	//filtroXml.set_name("Archivos xml");
	filtroXml.set_name("Xml files");

	filtroXml.add_pattern("*.xml");
	filtroXml.add_pattern("*.XML");
	dialog->add_filter(filtroXml);
	Gtk::FileFilter filtroTxt;
	//filtroTxt.set_name("Archivos txt");
	filtroTxt.set_name("Txt files");
	filtroTxt.add_pattern("*.txt");
	filtroTxt.add_pattern("*.TXT");
	dialog->add_filter(filtroTxt);
	Gtk::FileFilter filtroTodos;
	//filtroTodos.set_name("Todos los archivos");
	filtroTodos.set_name("All the files");
	filtroTodos.add_pattern("*");
	dialog->add_filter(filtroTodos);
	
	//Ruta por defecto
	dialog->set_current_folder(rutaXml);
	
	//Muestra el dialogo y espera la respuesta del usuario
	int opcion = dialog->run();
	
	//Seleccion de opcion -Abrir o Cancelar
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{
			img->setRutaXmlImg(dialog->get_filename());

			return true;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
}

/**
 Dialogo Guardar como fichero de celulas.
 @param nom, string que contiene la ruta por defecto de los ficheros xml.
 @return string, ruta final + el nombre del fichero xml.
 */
string DialogoAGLocal::dialogoGuardarComo(const string &nom)
{
	string rutaFinalXml = "";
	
	//dialog = new Gtk::FileChooserDialog("Guardar Datos", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog = new Gtk::FileChooserDialog("Save Data", Gtk::FILE_CHOOSER_ACTION_SAVE);
	
	dialog->set_icon_from_file(Utiles::getIconoFile("guardar.png"));
	//Botones de respuesta del dialogo
	dialog->add_button(Gtk::Stock::SAVE_AS, Gtk::RESPONSE_OK);
	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	
	//Nombre de la imagen para fichero de coordenadas
	dialog->set_current_name(nom);
	
	//Ruta por defecto
	dialog->set_current_folder(rutaXml);
	dialog->set_do_overwrite_confirmation();
	
	//Filtros
	Gtk::FileFilter filtroXml;
	filtroXml.set_name("xml");
	filtroXml.add_pattern("*.xml");
	dialog->add_filter(filtroXml);
	Gtk::FileFilter filtroTxt;
	filtroTxt.set_name("txt");
	filtroTxt.add_pattern("*.txt");
	dialog->add_filter(filtroTxt);
	
	//Muestra el dialogo y espera la respuesta del usuario
	int opcion = dialog->run();
	
	//Seleccion de opcion -Abrir o Cancelar
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{	
			string tipoFile;

			tipoFile = dialog->get_filter()->get_name();
			
			if(dialog->get_do_overwrite_confirmation())
			{
				if(Utiles::obtieneTipoArch(dialog->get_filename()) == tipoFile)
				{
					rutaFinalXml = dialog->get_filename();
				}
				else
				{
					rutaFinalXml = dialog->get_filename() + "." + tipoFile;
				}
			}
			else
			{
				if(Utiles::obtieneTipoArch(dialog->get_filename()) == tipoFile)
				{
					rutaFinalXml = dialog->get_filename();
				}
				else
				{
					rutaFinalXml = dialog->get_filename() + "." + tipoFile;
				}
			}
			return rutaFinalXml;
					
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			return rutaFinalXml;
		}
		default:
		{
			return rutaFinalXml;
		}	
	}
}

/**
 Dialogo de guardar como que guarda el pixbuf pasado por parametro en el metodo
 en un fichero.
 @param nombre, nombre del fichero original de la imagen.
 @param imagenCel, pixbuf que queremos almacenar en el fichero.
 @return bool, Devuelve verdadero si se ha guardado con exito la imagen, falso
 en caso contrario.
 */
bool DialogoAGLocal::dialogoGuardarImagen(const string &nombre, Glib::RefPtr<Gdk::Pixbuf> imagenCel)
{
	Gtk::FileFilter *filtro;

	//dialog = new Gtk::FileChooserDialog("Guardar Imagen", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog = new Gtk::FileChooserDialog("Save Image", Gtk::FILE_CHOOSER_ACTION_SAVE);
	
	dialog->set_icon_from_file(Utiles::getIconoFile("guardar.png"));
	//Botones de respuesta del dialogo
	dialog->add_button(Gtk::Stock::SAVE_AS, Gtk::RESPONSE_OK);
	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	//Nombre de la imagen
	dialog->set_current_name(nombre);
	
	//Ruta por defecto
	dialog->set_current_folder(rutaImagenes);
	dialog->set_do_overwrite_confirmation();
	
	//Filtros
	filtro = new Gtk::FileFilter();
	filtro->set_name("bmp");
	filtro->add_pattern("*.bmp");
	dialog->add_filter(*filtro);
	filtro = new Gtk::FileFilter();
	filtro->set_name("jpeg");
	filtro->add_pattern("*.jpeg");
	dialog->add_filter(*filtro);
	filtro = new Gtk::FileFilter();
	filtro->set_name("png");
	filtro->add_pattern("*.png");
	dialog->add_filter(*filtro);
	filtro = new Gtk::FileFilter();
	filtro->set_name("tiff");
	filtro->add_pattern("*.tiff");
	dialog->add_filter(*filtro);
	
	//Muestra el dialogo y espera la respuesta del usuario
	int opcion = dialog->run();
	
	//Seleccion de opcion -Abrir o Cancelar
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{	
			string tipoFile, rutaFinalImg;
			tipoFile = dialog->get_filter()->get_name();
			
			if(dialog->get_do_overwrite_confirmation())
			{
				if(Utiles::obtieneTipoArch(dialog->get_filename()) == tipoFile)
				{
					rutaFinalImg = dialog->get_filename();
				}
				else
				{
					rutaFinalImg = dialog->get_filename() + "." + tipoFile;
				}
				
				imagenCel->save(rutaFinalImg, tipoFile);
			}
			else
			{
				if(Utiles::obtieneTipoArch(dialog->get_filename()) == tipoFile)
				{
					rutaFinalImg = dialog->get_filename();
				}
				else
				{
					rutaFinalImg = dialog->get_filename() + "." + tipoFile;
				}
				
				imagenCel->save(rutaFinalImg, tipoFile);
			}
			return true;	
			break;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			return false;
		}
		default:
		{
			return false;
		}	
	}
}

/**
 Actualiza la previsualizacion de la imagen seleccionada.
 @param *preview, puntero del tipo Gtk::Image que contiene la imagen de previsualizacion.
 */
void DialogoAGLocal::on_update_preview(Gtk::Image *preview)
{
	string filename = dialog->get_preview_filename();
	
	Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(filename);
		
	if(filename != "")
	{
		if(!Glib::file_test(filename, Glib::FILE_TEST_IS_DIR))
		{
			try
			{
				Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(filename,150,150);
				preview->set(pixbuf);
			}
			catch (Glib::Error &ex)
			{
				filename = (Utiles::getIconoFile("archivoTexto.png"));
				Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(filename,150,150);
				preview->set(pixbuf);
			}
		}
		else
		{
			filename = (Utiles::getIconoFile("carpeta.png"));
			
			Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(filename,150,150);
			preview->set(pixbuf);		
		}
		dialog->set_preview_widget_active(true);
	}
}
