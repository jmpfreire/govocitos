/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoBarraProgres.h
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

#ifndef _DIALOGOBARRAPROGRES_H_
	#define _DIALOGOBARRAPROGRES_H_

	#include <gtkmm.h>

	#include "Utiles.h"

	class DialogoBarraProgres : public Gtk::Window
	{
		public:
			DialogoBarraProgres(const string &titulo);
			~DialogoBarraProgres();
			bool getCancelaProgreso();
			void setCancelaProgreso(bool descC);
			void ejectuaDialogoProgreso();
			void setPercentText(double pr);
			void setEstadoBarraProgreso(double pb);
			void cierraVentanaProgreso();
			virtual void on_button_close();
		private:
			//Signal handlers:
			Gtk::VBox m_VBox;
			Gtk::Alignment m_Alignment;
			Gtk::ProgressBar m_ProgressBar;
			Gtk::HSeparator m_Separator;
			Gtk::Button m_Button_Close;
			bool cancelarProgreso;
	};

#endif // _DIALOGOBARRAPROGRES_H_
