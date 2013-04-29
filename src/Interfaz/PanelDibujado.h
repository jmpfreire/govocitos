/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelDibujado.h
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

#ifndef _PANELDIBUJADO_H_
	#define _PANELDIBUJADO_H_

	#include <gtkmm.h>

	#include "Estructuras/ImageCells.h"
	#include "Interfaz/PanelPropiedades.h"
	#include "Interfaz/BarraEstado.h"
	#include "Modulos/DibujadoCelula.h"
	#include "Interfaz/MenuBarraPrincipal.h"
	#include "Interfaz/MenuPopup.h"
	#include "Modulos/Rejilla.h"

	class InterfazGovocitos;
	class SistemaDibujado;

	class PanelDibujado : public Gtk::DrawingArea
	{
		public:
			PanelDibujado(InterfazGovocitos &ig);
			~PanelDibujado();
			void setSizeImgRedimen(const int &ancho, const int &alto);
			void setSistemaDibujado(SistemaDibujado &sd);
			void setRejilla(Rejilla &rej);
			void setVerRejilla(bool vr);
			void setActivaDetecSupervis(bool c);
			bool getVerRejilla();
			DibujadoCelula *getCapaCelula();
			Rejilla *getCapaRejilla();
			bool getActivaDetecSupervis();
			virtual bool on_expose_event(GdkEventExpose* event);
			void creaCapaImagen(Glib::RefPtr<Gdk::Pixbuf> iPixbuf, int ancho, int alto);
			Cairo::RefPtr<Cairo::ImageSurface> getSurfaceImagen();
			Cairo::RefPtr<Cairo::ImageSurface> getSurfaceCelulas();
			Cairo::RefPtr<Cairo::ImageSurface> getSurfaceRejilla();
			void repintaCapaRejilla();
			void eliminaCelula();
			void unePuntosPintado();
			void creaRejilla();
			void destrucRejilla();
			void menuPopupCelula(vector<ClaseCelula> *clases, vector<EstadoCelula> *estados);
			void estabClasePopup(string cl);
			void estabEstadoPopup(string est);
			void obtieneDiametros(bool condicion);
			void actualizarVista();
			void selecAllCell();
			void pintaImagenMascara(const string &ruta);
			typedef sigc::signal<void> pintado_puntos;
			pintado_puntos signal_cambiar_menu();
			typedef sigc::signal<void> modifica_celulas;
			modifica_celulas signal_modificacion_celulas();
			typedef sigc::signal<void> modificaClasEstPopup;
			modificaClasEstPopup signal_modifica_classEstPopup();
			typedef sigc::signal<void> seleccionaCelula;
			seleccionaCelula signal_selecciona_celula();
		private:
			void repintaCapaCelulas();
			virtual bool on_button_press_event(GdkEventButton *event);
			void panelEdicionButtons(GdkEventButton *event);
			void panelGridButtons(GdkEventButton *event);
			void panelEdicionNonSupervised(GdkEventButton *event);
			virtual bool on_button_release_event(GdkEventButton *event);
			/**
			 Notifica el movimiento del raton por la pantalla.
			 @param event, puntero de GdkEventMotion.
			 @return bool, true si la operacion se realiza, false en caso contrario.
			 */
			inline virtual bool on_motion_notify_event(GdkEventMotion *event)
			{	
				int cX, cY;

				cX = event->x - desplazaX;
				cY = event->y - desplazaY;
				
				if(pintadoAlzado && (cX >= 0) && (cY >= 0) && (cX <= anchoRedimen) && (cY <= altoRedimen))
				{
					capaCelula->pintaManoAlzada(cX, cY);
					repintaCapaCelulas();

					//Pintamos coordenadas
					barraEst->setCoordenadas(cX, cY);
		
					return true;
				}
				return false;
			}
			//Atributos
			int desplazaY, desplazaX;
			int anchoRedimen, altoRedimen;
			SistemaDibujado *sistemDibujo;
			DibujadoCelula *capaCelula;
			Rejilla *rejilla;
			BarraEstado *barraEst;
			MenuBarraPrincipal *menuPrinc;
			Cairo::RefPtr<Cairo::Context> cr;
			Cairo::RefPtr<Cairo::Context> cr1;
			Cairo::RefPtr<Cairo::Context> cr2;
			Cairo::RefPtr<Cairo::Context> crExt;
			Cairo::RefPtr<Cairo::ImageSurface> surfaceImagen;
			Cairo::RefPtr<Cairo::ImageSurface> surfaceCelulas;
			Cairo::RefPtr<Cairo::ImageSurface> surfaceRejilla;
			InterfazGovocitos *interfazPrincipal;
			MenuPopup *menuPopupCel;
			vector<ClaseCelula> *clases;
			vector<EstadoCelula> *estados;
			Gtk::Menu *m_pMenuPopup;
			bool pintadoAlzado, verRejilla, activaDetecSupervis;
			modificaClasEstPopup modifClaseEstadoP;
			seleccionaCelula selecCellSignal;
			pintado_puntos pPuntos;
			modifica_celulas modifCell;
	};
#endif //_PANELDIBUJADO_H_
