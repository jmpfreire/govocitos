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

#ifndef _MENUPOPUP_H_
	#define _MENUPOPUP_H_

	#include <gtkmm.h>
	#include <iostream>
	#include <glibmm.h>

	#include "Estructuras/ClaseCelula.h"
	#include "Estructuras/EstadoCelula.h"

	using namespace std;

	class PanelDibujado;

	class MenuPopup : public Gtk::Window
	{
		public:
			MenuPopup(vector<ClaseCelula> &cl,vector<EstadoCelula> &est, PanelDibujado &pd);
			~MenuPopup();
			Glib::RefPtr<Gtk::UIManager> getUIManager();
			void setSensitivePopup(const string &menu, bool condicion = false);
			void setSensitiveInicialPopup();
			void inicilizaMenuPopup();
			void CreaUIManagerPopup();
		private:
			Glib::RefPtr<Gtk::UIManager> m_refUIManager;
			Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
			vector<ClaseCelula> *clases;
			vector<EstadoCelula> *estados;
			PanelDibujado *panelDibuj;
	};
#endif //_MENUPOPUP_H_
