/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoBarraProgres.cpp
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

#include "DialogoBarraProgres.h"

/**
 Constructor.
 */
DialogoBarraProgres::DialogoBarraProgres(const string &titulo): m_VBox(false, 5),
											m_Alignment(0.5, 0.5, 0, 0),
											m_Button_Close("Cancel")
{	
	cancelarProgreso = false;
	set_resizable();
	set_title(titulo);
	set_icon_from_file(Utiles::getIconoFile("descarga.png"));
	m_VBox.set_border_width(10);
	add(m_VBox);
	m_ProgressBar.set_text("0.0 %");
	m_ProgressBar.set_size_request(280,25);
	m_VBox.pack_start(m_Alignment, Gtk::PACK_SHRINK, 5);
	m_Alignment.add(m_ProgressBar);
	
	//Add a button to exit the program.
	m_VBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);
	m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
		        &DialogoBarraProgres::on_button_close) );
	m_Button_Close.set_flags(Gtk::CAN_DEFAULT);
	m_Button_Close.grab_default();

	resize(300,50);
}


/**
 Destructor.
 */
DialogoBarraProgres::~DialogoBarraProgres()
{
	
}

/**
 Devuelve el valor de cancelacion de la Progreso cancelarProgreso = true se 
 cancela la Progreso.
 */
bool DialogoBarraProgres::getCancelaProgreso()
{
	return cancelarProgreso;
}

/**
 Establece el valor de la cancelacion de la Progreso.
 @param descC, bool si es verdadero se para la descarga.
 */
void DialogoBarraProgres::setCancelaProgreso(bool descC)
{
	cancelarProgreso = descC;
}

/**
 Muestra el dialogo de progreso de Progreso.
 */
void DialogoBarraProgres::ejectuaDialogoProgreso()
{
	show_all();
}

/**
 Establece el tanto por ciento de la barra de progreso.
 @param pr, double que contiene el porcentaje de avance de la descarga.
 */
void DialogoBarraProgres::setPercentText(double pr)
{
	string porcentaje;
	double porcentNum;
	
	porcentNum = pr * 100;
	porcentaje = Utiles::converString(porcentNum);
	
	if(porcentNum < 10.0)
	{
		porcentaje = porcentaje.substr(0, 4);
	}
	else
	{
		porcentaje = porcentaje.substr(0, 5);
	}
	
	m_ProgressBar.set_text(porcentaje + " %");
}

/**
 Aumenta el tamaño de la barra de progreso.
 @param pb, double que contiene el progreso de la descarga y lo establece en la barra.
 */
void DialogoBarraProgres::setEstadoBarraProgreso(double pb)
{
	m_ProgressBar.set_fraction(pb);
}

/**
 Cierra el dialogo de Progreso.
 */
void DialogoBarraProgres::cierraVentanaProgreso()
{
	hide();
}

/**
 En caso de presionar el boton cancelar se cancela la Progreso.
 */
void DialogoBarraProgres::on_button_close()
{
	cancelarProgreso = true;
	hide();
}
