/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cpp
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/main.h>
#include "Modulos/ModulosGovocitos.h"
#include "Interfaz/InterfazGovocitos.h"
#include "CoreGovocitos.h"

/**
 Metodo main.
 */
int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	std::setlocale(LC_ALL, "C");

	//Creamos el controlador
	CoreGovocitos *controlador = new CoreGovocitos();
	
	//Lanzamos la interfaz grafica
	Gtk::Main::run(*controlador->getInterfazGovocitos());
	
	return 0;
}
