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

#ifndef _MENUBARRAPRINCIPAL_H_
	#define _MENUBARRAPRINCIPAL_H_

	#include <iostream>
	#include <gtkmm.h>

	using namespace std;

	class InterfazGovocitos;
	
	class MenuBarraPrincipal : public Gtk::ActionGroup
	{
		public:
			MenuBarraPrincipal(InterfazGovocitos &inter);
			~MenuBarraPrincipal();
			Glib::RefPtr<Gtk::UIManager> getUIManager();
			Gtk::Widget *getWidgetMenuBarraPrincipal(const string &tipo);
			void setSensitiveOpcMenu(const string &menu, bool condicion = false);
			void setSensibleOpcionesBasicas();			
			void estableceMenuPosiconInicial();
			void InicializaMenuBarraPrincipal();
		private:
			//Metodos
			void CreaUIManagerMenu();
			//Atributos
			Glib::RefPtr<Gtk::ActionGroup> mPrincipal;
			Glib::RefPtr<Gtk::UIManager> xmlMPrincipal;
			InterfazGovocitos *interfazPrincipal;
	};
#endif // _MENUBARRAPRINCIPAL_H_
