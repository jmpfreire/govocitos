/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Dialogos.cpp
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

#include "Dialogos.h"

/**
 Metodo estatico que muestra un Dialogo de confirmacion.
 @param t, string que contiene el texto del dialogo.
 @param tittle, string que contiene el titulo del dialogo.
 @return bool, true si el usuario responde yes, false si responde no.
 */
bool Dialogos::dialogoConfirmacion(const string &t, const string &title)
{
	Gtk::MessageDialog dialogoConf(t, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, false);
	
	dialogoConf.set_icon_from_file(Utiles::getIconoFile("pregunta.png"));
	dialogoConf.set_title(title);
	
	int opcion = dialogoConf.run();
		
	switch(opcion)
	{
		case(Gtk::RESPONSE_YES):
		{
			dialogoConf.hide();
			return true;
		}
		case(Gtk::RESPONSE_NO):
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
 Metodo estatico que muestra un Dialogo error.
 @param t, string que contiene el texto del dialogo.
 @param tittle, string que contiene el titulo del dialogo.
 */
void Dialogos::dialogoError(const string &t, const string &title)
{
	Gtk::MessageDialog dialogoConf(t, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, false);
	
	dialogoConf.set_icon_from_file(Utiles::getIconoFile("error.png"));
	dialogoConf.set_title(title);
	
	dialogoConf.run();
}


/**
 Metodo estatico que muesta un Dialogo de advertencia.
 @param t, string que contiene el texto del dialogo.
 @param tittle, string que contiene el titulo del dialogo.
 */
void Dialogos::dialogoAdvertencia(const string &t, const string &title)
{
	Gtk::MessageDialog dialogoConf(t, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_CLOSE, false);	
	
	dialogoConf.set_icon_from_file(Utiles::getIconoFile("advertencia.png"));
	dialogoConf.set_title(title);
	
	dialogoConf.run();
}

/**
 Metodo estatico que muestra un dialogo de advertencia para el menu preferencias.
 @param t mensaje que queremos que muestre el dialogo.
 @param title titulo del dialogo de advertencia.
 @return Devuelve verdadero si pulsamos el boton aceptar, falso si cerramos la ventana.
 */
bool Dialogos::dialogoAdvertenciaPref(const string &t, const string &title)
{
	Gtk::MessageDialog dialogoConf(t, false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, false);	
	
	dialogoConf.set_icon_from_file(Utiles::getIconoFile("advertencia.png"));
	dialogoConf.set_title(title);
	
	int opcion = dialogoConf.run();
	
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
			return true;
			break;
		default:
			return false;
	}
}

/**
 Metodo estatico que muestra el dialogo de guardar como el fichero de datos csv.
 @param &ruta, referencia del string que contiene la ruta del fichero de salida.
 @param bool, true si se va guardar el fichero, false en caso contrario.
 */
bool Dialogos::dialogoExportarCsv(string &ruta, const string &defaultPath)
{
	Gtk::FileChooserDialog *dialog;

	dialog = new Gtk::FileChooserDialog("Save Data", Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog->set_icon_from_file(Utiles::getIconoFile("guardar.png"));
	//Botones de respuesta del dialogo
	dialog->add_button(Gtk::Stock::SAVE_AS, Gtk::RESPONSE_OK);
	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	Gtk::FileFilter filtroCsv;
	filtroCsv.set_name("csv");
	filtroCsv.add_pattern("*.csv");
	dialog->add_filter(filtroCsv);

	//Ruta por defecto
	dialog->set_current_folder(defaultPath);
	
	//Muestra el dialogo y espera la respuesta del usuario
	int opcion = dialog->run();

	//Seleccion de opcion -Abrir o Cancelar
	switch(opcion)
	{
		case(Gtk::RESPONSE_OK):
		{	
			string tipoFile;

			tipoFile = dialog->get_filter()->get_name();
			
			if(Utiles::obtieneTipoArch(dialog->get_filename()) == tipoFile)
			{
				ruta = dialog->get_filename();
			}
			else
			{
				ruta = dialog->get_filename() + "." + tipoFile;
			}
			dialog->hide();
			return true;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			dialog->hide();
			return false;
		}
		default:
		{
			dialog->hide();
			return false;
		}
	}
}
