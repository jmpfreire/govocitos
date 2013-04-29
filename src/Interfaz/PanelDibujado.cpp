/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelDibujado.cpp
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

#include "PanelDibujado.h"
#include "Modulos/SistemaDibujado.h"
#include "Interfaz/InterfazGovocitos.h"

/**
 Constructor.
 @param ig, referencia del objeto InterfazGovocitos.
 */
PanelDibujado::PanelDibujado(InterfazGovocitos &ig)
{
	interfazPrincipal = &ig;

	desplazaY = desplazaX = 0;
	anchoRedimen = altoRedimen = 0;
	barraEst = interfazPrincipal->getBarraEstado();
	menuPrinc = interfazPrincipal->getMenuBarraPrincipal();
	verRejilla = false;
	pintadoAlzado = false;
	activaDetecSupervis = false;
	menuPopupCel = NULL;
	
	//Añadimos el evento que captura el movimiento del raton
	add_events(Gdk::ALL_EVENTS_MASK);
}

/**
 Destructor.
 */
PanelDibujado::~PanelDibujado()
{

}

/**
 */
void PanelDibujado::setSizeImgRedimen(const int &ancho, const int &alto)
{
	anchoRedimen = ancho;
	altoRedimen = alto;
}

/**
 Establece el sistema de dibujado.
 @param sd, referencias de SistemaDibujado.
 */
void PanelDibujado::setSistemaDibujado(SistemaDibujado &sd)
{
	sistemDibujo = &sd;
	capaCelula = sistemDibujo->getCapaCelula();
}

/**
 Establece la rejilla.
 @param rej, referencia de la Rejilla.
 */
void PanelDibujado::setRejilla(Rejilla &rej)
{
	rejilla = &rej;
}

/**
 Establece el atributo de visibilidad de la rejilla.
 @param vr, bool.
 */
void PanelDibujado::setVerRejilla(bool vr)
{
	verRejilla = vr;
}

/**
 Establece la visibilidad de la capa de ceĺulas.
 @param c, bool.
 */
void PanelDibujado::setActivaDetecSupervis(bool c)
{
	activaDetecSupervis = c;
}

/**
 Establece la visibilidad de la rejilla.
 @return bool, true si la rejilla esta visible false en caso contrario.
 */
bool PanelDibujado::getVerRejilla()
{
	return verRejilla;
}

/**
 Devuelve el objeto de la capa de celulas.
 @return DibujadoCeula, puntero del objeto DibujadoCelula.
 */
DibujadoCelula *PanelDibujado::getCapaCelula()
{
	return capaCelula;
}

/**
 Devuelve el objeto de la capa rejilla.
 @return Rejilla, puntero del objeto Rejilla.
 */
Rejilla *PanelDibujado::getCapaRejilla()
{
	return rejilla;
}

/**
 Devuelve verdadero si esta activado la deteccion supervisadad, faslse en caso contrario.
 @return bool.
 */
bool PanelDibujado::getActivaDetecSupervis()
{
	return activaDetecSupervis;
}

/**
 Evento que refresca la vista de la pantalla.
 @param event, puntero de GdkEventExpose.
 @return bool, true en caso de que se refresque, false en caso contrario.
 */
bool PanelDibujado::on_expose_event(GdkEventExpose* event)
{
	if(surfaceImagen)
	{
		cr = get_window()->create_cairo_context();
			   					   
		//Obtenemos la zona de dibujado para poder obtener sus medidas 	 
		Gdk::Cairo::rectangle (cr, get_allocation()); 	 

		//Tamaño de la ventana menos el tamaño de la imagen 	         
		desplazaX = ((get_allocation().get_width() - sistemDibujo->getAnchoRedimen()) / 2);
		desplazaY = ((get_allocation().get_height() - sistemDibujo->getAltoRedimen()) / 2);

		//Trasladamos la imagen al centro de la pantalla
		cr->translate(desplazaX, desplazaY); 	             
		cr->set_source(surfaceImagen, 0, 0);
					   
		if(event)
		{
			cr->rectangle(event->area.x, event->area.y,
			event->area.width, event->area.height);
			cr->clip(); 
		}
  		cr->paint();
	}  	 
	if(event)
	{
		repintaCapaCelulas();
		repintaCapaRejilla();				
	}
				
	return true;
}

/**
 Crea la capa de la imagen.
 @param iPixbuf, Glib::RefPtr<Gdk::Pixbuf> contiene el pixbuf de la imagen.
 @param ancho, entero que contiene el ancho de la imagen.
 @param alto, entero que contiene el alto de la imagen.
 */
void PanelDibujado::creaCapaImagen(Glib::RefPtr<Gdk::Pixbuf> iPixbuf, int ancho, int alto)
{
	if(surfaceImagen)
	{
		surfaceImagen->finish();
	}
	if(surfaceCelulas)
	{
		surfaceCelulas->finish();
	}
	surfaceImagen = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, ancho, alto);
	surfaceCelulas = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, ancho, alto);

	//Inicializamos la capa de las celulas
	sistemDibujo->getCapaCelula()->setContexCelulasPrin(surfaceCelulas);
	sistemDibujo->getCapaCelula()->setContexCelulasSecun(surfaceCelulas);
	
	//Creamos el contexto de cairo
	cr1 = Cairo::Context::create(surfaceCelulas);
    cr = Cairo::Context::create (surfaceImagen); 

	//Establecemos el operador de dibujado
	cr1->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_operator(Cairo::OPERATOR_SOURCE);
  	 
    Gdk::Cairo::set_source_pixbuf(cr, iPixbuf, 0, 0); 	 
    cr->rectangle(0, 0, ancho, alto); 	 
    cr->fill(); 	 
  	 
    set_size_request(ancho, alto);
}

/**
 Devuelve la surface de la imagen.
 @return Cairo::RefPtr<Cairo::ImageSurface>.
 */
Cairo::RefPtr<Cairo::ImageSurface> PanelDibujado::getSurfaceImagen()
{
	return surfaceImagen;
}

/**
 Devuelve la surface de las celulas.
 @return Cairo::RefPtr<Cairo::ImageSurface>.
 */
Cairo::RefPtr<Cairo::ImageSurface> PanelDibujado::getSurfaceCelulas()
{
	return surfaceCelulas;
}

/**
 Devuelve la surface de la rejilla.
 @return Cairo::RefPtr<Cairo::ImageSurface>.
 */
Cairo::RefPtr<Cairo::ImageSurface> PanelDibujado::getSurfaceRejilla()
{
	return surfaceRejilla;
}

/**
 Repinta la capa de celulas.
 */
void PanelDibujado::repintaCapaCelulas()
{
	if(surfaceCelulas)
	{
		cr1 = get_window()->create_cairo_context();
			
		//Trasladamos la imagen al centro de la pantalla
		cr1->translate(desplazaX, desplazaY);

		cr1->set_source(surfaceCelulas, 0, 0);
		cr1->paint();
	}
}

/**
 Repinta la capa rejilla
 */
void PanelDibujado::repintaCapaRejilla()
{	
	if(surfaceRejilla && verRejilla)
	{
		cr2 = get_window()->create_cairo_context();

		//Trasladamos la imagen al centro de la pantalla
		cr2->translate(desplazaX, desplazaY);

		cr2->set_source(surfaceRejilla, 0, 0);
		cr2->paint();
	}	
}

/**
 Detecta si se presiona un boton del raton.
 @param event, puntero de GdkEventButton.
 @return bool, true si la operacion es correcta, false en caso contrario.
 */
bool PanelDibujado::on_button_press_event(GdkEventButton *event)
{	
	PanelPropiedades *panelDer;
	int cX, cY;
	
	cX = event->x - desplazaX;
	cY = event->y - desplazaY;
	
	panelDer = interfazPrincipal->getPanelPropiedades();

	if(surfaceCelulas && (cX >= 0) && (cY >= 0) && (cX <= anchoRedimen) && (cY <= altoRedimen))
	{
		if(event->button == 1)
		{
			if(activaDetecSupervis)
			{
				double zoom = sistemDibujo->getZoom() / 10;

				//Comprobamos si los puntos no se encuentran dentro de una celula
				if(!capaCelula->puntoDentroCelula((cX / zoom), (cY / zoom)))
				{
					//Pintamos los puntos de la nueva celula
					capaCelula->dibujarPuntosCelula(cX, cY);

					//Repintado
					repintaCapaCelulas();
				}
			}
			else if(panelDer->getPagBlocnotas() == 0)
			{
				panelEdicionButtons(event);
			}
			else if(panelDer->getPagBlocnotas() == 1)
			{
				panelGridButtons(event);
			}
			else if(panelDer->getPagBlocnotas() == 2)
			{
				panelEdicionNonSupervised(event);
			}

		}
		else if(event->button == 3)
		{
			if(!panelDer->getPagBlocnotas())
			{
				m_pMenuPopup->popup(event->button, event->time);	
			}
		}
	}
	return true;		
}

/**
 Funciones del panel edicion.
 @param event, puntero de GdkEventButton.
 */
void PanelDibujado::panelEdicionButtons(GdkEventButton *event)
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();
	
	if(panelDer->getAnhadirCel())
	{
		capaCelula->destruyeDatos();

		if(capaCelula->getNumsCelulaSeleccionada())
		{
			capaCelula->vaciaVectorCelulaSeleccionada();
			capaCelula->pintaBorde();
			//Repintado
			repintaCapaCelulas();
		}
		if(panelDer->getAnhadirCelManoAL())
		{
			capaCelula->manoAlzadaPuntoInicial((event->x - desplazaX), 
				                               (event->y - desplazaY));
			capaCelula->setManoAlzada(true);
			pintadoAlzado = true;
		}
		else if(panelDer->getAnhadirCelPT())
		{
			//Pintamos los puntos de la nueva celula
			capaCelula->dibujarPuntosCelula((event->x - desplazaX), 
				                            (event->y - desplazaY));
		
			//Repintado
			repintaCapaCelulas();
			
			pPuntos.emit();
		}
	}
	else if(panelDer->getModifCel())
	{
		if(capaCelula->getNumsCelulaSeleccionada())
		{
			if(capaCelula->getPuntosModif())
			{	
				if(capaCelula->getSeccionBorrada())
				{	
					if(panelDer->getAnhadirCelManoAL())
					{
						capaCelula->manoAlzadaPuntoInicial((event->x - desplazaX),
									                       (event->y - desplazaY));
						capaCelula->setManoAlzada(true);
						pintadoAlzado = true;
					}
					else if(panelDer->getAnhadirCelPT())
					{
						//Pintamos los puntos de la nueva celula
						capaCelula->dibujarPuntosCelula((event->x - desplazaX), 
								                        (event->y - desplazaY));
						//Repintado
						repintaCapaCelulas();
					}
									
				}
				else
				{
					//Lanzamos la señal para añadir a la pila deshacer
					modifCell.emit();
			
					//Eliminamos el cacho de celula
					capaCelula->eliminaParteModif((event->x - desplazaX),
						                          (event->y - desplazaY));
					panelDer->setSensitiveAnhadirCelManoAL(true);
					panelDer->setSensitiveAnhadirCelPT(true);
					sistemDibujo->repintadoImagen();
					capaCelula->setContexCelulasPrin(surfaceImagen);
					capaCelula->pintaBorde();
					on_expose_event(NULL);
					capaCelula->setContexCelulasPrin(surfaceCelulas);
				}
			}
			else
			{
				capaCelula->modifcaCelula((event->x - desplazaX), 
					                      (event->y - desplazaY));
				//Repintado
				repintaCapaCelulas();
			}
		}
		else
		{
			double zoom = sistemDibujo->getZoom() / 10;

			capaCelula->busquedaCelula((event->x - desplazaX) / zoom, 
				                       (event->y - desplazaY) / zoom);
			capaCelula->pintaBorde();
			//Repintado
			repintaCapaCelulas();
		}
	}
	else if(panelDer->getNotUseAreaImage())
	{
		capaCelula->destruyeDatos();

		if(capaCelula->getNumsCelulaSeleccionada())
		{
			capaCelula->vaciaVectorCelulaSeleccionada();
			capaCelula->pintaBorde();
			//Repintado
			repintaCapaCelulas();
		}
				
		capaCelula->manoAlzadaPuntoInicial((event->x - desplazaX), 
			                               (event->y - desplazaY));
		capaCelula->setManoAlzada(true);
		pintadoAlzado = true;
	}
	else if(panelDer->getSelecCel())
	{
		double zoom = sistemDibujo->getZoom() / 10;
		capaCelula->destruyeDatos();
		//LLamamos a la funcion de busqueda del poligono seleccionado
		capaCelula->busquedaCelula((event->x - desplazaX) / zoom, 
			                       (event->y - desplazaY) / zoom);

		if(panelDer->getSelecCel() && capaCelula->getNumsCelulaSeleccionada())
		{
			if(capaCelula->getNumsCelulaSeleccionada() == 1)
			{	
				int celulaS = capaCelula->getCelulaSeleccionada(0);
				//Lanzamos señal para el treeview de diametros y estadisticos
				selecCellSignal.emit();
					
				barraEst->setClaseCell(capaCelula->getClaseCelulaSeleccionada(celulaS));
				barraEst->setEstadoCell(capaCelula->getEstadoCelulaSeleccionada(celulaS));
				menuPopupCel->setSensitivePopup("showDiam", true);
				panelDer->setSensitiveCalcDiam(true);
				menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam", true);
			}
			else
			{
				//barraEst->setClaseCell("sin clasificar");
				barraEst->setClaseCell("unclassified");
				//barraEst->setEstadoCell("sin estado");
				barraEst->setEstadoCell("without state");
			
				menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam", true);
				panelDer->setSensitiveCalcDiam(false);
				menuPopupCel->setSensitivePopup("showDiam");
			}
			
			panelDer->setSensitiveSelecClase(true);
			panelDer->setSensitiveSelecEstado(true);
			menuPopupCel->setSensitivePopup("eliminar", true);
			menuPopupCel->setSensitivePopup("popClases", true);
			menuPopupCel->setSensitivePopup("popEstados", true);
		}
		else
		{
			//Lanzamos señal para el treeview de diametros y estadisticos
			selecCellSignal.emit();
		
			menuPopupCel->setSensitiveInicialPopup();
			menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam");
			panelDer->setSensitiveCalcDiam(false);
			panelDer->setSensitiveSelecClase(false);
			panelDer->setSensitiveSelecEstado(false);				
			//barraEst->setClaseCell("sin clasificar");
			//barraEst->setEstadoCell("sin estado");
			barraEst->setClaseCell("unclassified");
			barraEst->setEstadoCell("without state");
			panelDer->setSeleccionaClase("");
			panelDer->setSeleccionaEstado("");
		}
		
		sistemDibujo->repintadoImagen();
		capaCelula->setContexCelulasPrin(surfaceImagen);
		capaCelula->pintaBorde();
	
		on_expose_event(NULL);
		capaCelula->setContexCelulasPrin(surfaceCelulas);
	}
}

/**
 Funciones del panel grid.
 @param event, puntero de GdkEventButton.
 */
void PanelDibujado::panelGridButtons(GdkEventButton *event)
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();

	double zoom = sistemDibujo->getZoom() / 10;

	capaCelula->destruyeDatos();
	//LLamamos a la funcion de busqueda del poligono seleccionado
	capaCelula->busquedaCelula((event->x - desplazaX) / zoom, (event->y - desplazaY) / zoom);
	
	if(capaCelula->getNumsCelulaSeleccionada() == 1)
	{	
		int celulaS = capaCelula->getCelulaSeleccionada(0);
		//Lanzamos señal para el treeview de diametros y estadisticos
		selecCellSignal.emit();
					
		barraEst->setClaseCell(capaCelula->getClaseCelulaSeleccionada(celulaS));
		barraEst->setEstadoCell(capaCelula->getEstadoCelulaSeleccionada(celulaS));
	}
	else
	{
		//barraEst->setClaseCell("sin clasificar");
		barraEst->setClaseCell("unclassified");
		//barraEst->setEstadoCell("sin estado");
		barraEst->setEstadoCell("without state");
	}

	sistemDibujo->repintadoImagen();
	capaCelula->setContexCelulasPrin(surfaceImagen);
	capaCelula->pintaBorde();

	if(verRejilla)
	{
		rejilla->setContexRejilla(surfaceImagen);	
		rejilla->pintaRejilla();
		rejilla->pintaBordeRejilla();
	}
	
	on_expose_event(NULL);
	capaCelula->setContexCelulasPrin(surfaceCelulas);
	
	if(verRejilla)
	{
		rejilla->setContexRejilla(surfaceRejilla);
	}
}

/**
 Funciones del panel edicion no supervisada.
 @param event, puntero de GdkEventButton.
 */
void PanelDibujado::panelEdicionNonSupervised(GdkEventButton *event)
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();

	if(panelDer->getModifCelNSup())
	{
		if(capaCelula->getNumsCelulaSeleccionada())
		{
			if(capaCelula->getPuntosModif())
			{	
				if(capaCelula->getSeccionBorrada())
				{	
					if(panelDer->getAnhadirCelManoALNSup())
					{
						capaCelula->manoAlzadaPuntoInicial((event->x - desplazaX),
								                           (event->y - desplazaY));
						capaCelula->setManoAlzada(true);
						pintadoAlzado = true;
					}
					else if(panelDer->getAnhadirCelPTNSup())
					{
						//Pintamos los puntos de la nueva celula
						capaCelula->dibujarPuntosCelula((event->x - desplazaX), 
								                        (event->y - desplazaY));
						//Repintado
						repintaCapaCelulas();
					}
				}
				else
				{
					//Lanzamos la señal para añadir a la pila deshacer
					modifCell.emit();
					
					//Eliminamos el cacho de celula
					capaCelula->eliminaParteModif((event->x - desplazaX),
							                      (event->y - desplazaY));
					panelDer->setSensitiveAnhadirCelManoAL(true);
					panelDer->setSensitiveAnhadirCelPT(true);
					sistemDibujo->repintadoImagen();
					capaCelula->setContexCelulasPrin(surfaceImagen);
					capaCelula->pintaBorde();
					on_expose_event(NULL);
					capaCelula->setContexCelulasPrin(surfaceCelulas);
				}
			}
			else
			{
				capaCelula->modifcaCelula((event->x - desplazaX), 
						                  (event->y - desplazaY));
				//Repintado
				repintaCapaCelulas();
			}
		}
		else
		{
			double zoom = sistemDibujo->getZoom() / 10;

			capaCelula->busquedaCelula((event->x - desplazaX) / zoom, 
					                   (event->y - desplazaY) / zoom);
			capaCelula->pintaBorde();
			//Repintado
			repintaCapaCelulas();
		}
	}
	else if(panelDer->getSelecCelNSup())
	{
		double zoom = sistemDibujo->getZoom() / 10;

		capaCelula->destruyeDatos();
		//LLamamos a la funcion de busqueda del poligono seleccionado
		capaCelula->busquedaCelula((event->x - desplazaX) / zoom, 
			                       (event->y - desplazaY) / zoom);

		sistemDibujo->repintadoImagen();
		capaCelula->setContexCelulasPrin(surfaceImagen);
		capaCelula->pintaBorde();

		on_expose_event(NULL);
		capaCelula->setContexCelulasPrin(surfaceCelulas);
	}
}

/**
 Detecta si se suelta el boton del raton.
 @param event, puntero de GdkEventButton.
 @return bool, devuelve true si la operación es correcta false en caso contrario.
 */
bool PanelDibujado::on_button_release_event(GdkEventButton *event)
{	
	if(capaCelula->getManoAlzada())
	{	
		PanelPropiedades *panelDer;

		panelDer = interfazPrincipal->getPanelPropiedades();
		
		pintadoAlzado = false;
		//La segunda opcion comprueba si la celula se va agregar y en caso afirmativo la 
		//agrega y devuelve true
		if(capaCelula->agregaCelula())
		{	
			if(!capaCelula->getSeccionBorrada())
			{

				//Lanzamos la señal para añadir a la pila deshacer
				modifCell.emit();
				
				//Comprobamos si es una celula fuera de area imagen
				if(panelDer->getNotUseAreaImage())
				{
					capaCelula->addCellToListCells(true);
				}
				else
				{
					capaCelula->addCellToListCells();
				}
			}
		}
		else
		{
			capaCelula->borrarCelulaNueva();
		}

		sistemDibujo->repintadoImagen();
		capaCelula->setContexCelulasPrin(surfaceImagen);
		capaCelula->pintaBorde();
		on_expose_event(NULL);
		capaCelula->setContexCelulasPrin(surfaceCelulas);

		barraEst->setCoordenadasACero();

		return true;
	}

	return false;
}

/**
 Elimina la celula seleccionada.
 */
void PanelDibujado::eliminaCelula()
{
	PanelPropiedades *panelDer;
	string mensaje, titulo;
	
	panelDer = interfazPrincipal->getPanelPropiedades();
	
	if(capaCelula->getNumsCelulaSeleccionada())
	{
		//titulo = "Confirmacion de eliminación";
		titulo = "Delete confirmation";
		
		if(capaCelula->getNumsCelulaSeleccionada() > 1)
		{
			//mensaje = "¿Confirma que desea eliminar las células seleccionadas?";
			mensaje = "Are you sure that you want to delete the selected cells?";
		}
		else
		{
			//mensaje = "¿Confirma que desea eliminar la célula seleccionada?";
			mensaje = "Are you sure that you want to delete the selected cell?";
		}

		if(Dialogos::dialogoConfirmacion(mensaje, titulo))
		{
			//Lanzamos la señal para añadir a la pila deshacer
			modifCell.emit();
			
			//Borramos el poligono
			capaCelula->eliminaCelulaSeleccionada();

			sistemDibujo->repintadoImagen();
			capaCelula->setContexCelulasPrin(surfaceImagen);
			capaCelula->pintaBorde();
			on_expose_event(NULL);
			capaCelula->setContexCelulasPrin(surfaceCelulas);
		}
		else
		{
			capaCelula->vaciaVectorCelulaSeleccionada();
			capaCelula->pintaBorde();
			repintaCapaCelulas();
		}

		menuPopupCel->setSensitiveInicialPopup();
		menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam");
		panelDer->setSensitiveCalcDiam(false);
		panelDer->setSensitiveSelecClase(false);
		panelDer->setSensitiveSelecEstado(false);
	}
	else
	{
		titulo = "Govocitos";
		//mensaje = "No hay ninguna célula seleccionada, no se puede eliminar ninguna célula";
		mensaje = "There is not any selected cell";
		
		Dialogos::dialogoAdvertencia(mensaje, titulo);
	}
}

/**
 Une los puntos de la nueva celula.
 */
void PanelDibujado::unePuntosPintado()
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades(); 
		   
	if(!capaCelula->getSeccionBorrada())
	{
		//Lanzamos la señal para añadir a la pila deshacer
		modifCell.emit();
	}
	
	//Agregamos la celula
	if(!capaCelula->agregaCelula())
	{
		capaCelula->borrarCelulaNueva();
	}
	else
	{
		capaCelula->addCellToListCells();
	}
	
	actualizarVista();
	
}

/**
 Crea la rejilla.
 */
void PanelDibujado::creaRejilla()
{
	int anchoRedimen, altoRedimen;

	anchoRedimen = sistemDibujo->getAnchoRedimen();
	altoRedimen = sistemDibujo->getAltoRedimen();

	//Provisional
//	rejilla->setValorMicras(1);
	
	surfaceRejilla  = Cairo::ImageSurface::create (Cairo::FORMAT_ARGB32, 
												   anchoRedimen, altoRedimen);

	cr2 = Cairo::Context::create(surfaceRejilla);
	rejilla->setContexRejilla(surfaceRejilla);
	cr2->set_operator(Cairo::OPERATOR_ATOP);

	rejilla->pintaRejilla();
	rejilla->pintaBordeRejilla();
	
	verRejilla = true;
}

/**
 Destruye la rejilla.
 */
void PanelDibujado::destrucRejilla()
{
	verRejilla = false;
	surfaceRejilla->finish();
	actualizarVista();
}

/**
 Crea el menu del boton derecho.
 @param clases, puntero del vector de clases.
 @param estados, puntero del vector de estados de maduración.
 */
void PanelDibujado::menuPopupCelula(vector<ClaseCelula> *clases, vector<EstadoCelula> *estados)
{	
	if(menuPopupCel)
	{
		delete menuPopupCel;
	}

	//Creamos el menu pasandole los estados y las clases
	menuPopupCel = new MenuPopup(*clases, *estados,  *this);
	
	m_pMenuPopup = dynamic_cast<Gtk::Menu*>(menuPopupCel->getUIManager()->get_widget("/PopupMenu"));

	if(!m_pMenuPopup)
		g_warning("menu no encontrado");
}

/**
 Establece la clase de las celulas.
 @param cl, stirng. 
 */
void PanelDibujado::estabClasePopup(string cl)
{
	int tam, numCelula;
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();

	tam = capaCelula->getNumsCelulaSeleccionada();
		
	modifClaseEstadoP.emit();

	//if(cl == "sin clase")
	if(cl == "unclassified")
	{
		cl = "";
	}
	
	for(int i = 0; i < tam; i++)
	{	
		numCelula = capaCelula->getCelulaSeleccionada(i);

		cl = capaCelula->setClaseCelulaSeleccionada(cl, numCelula);
	}

	barraEst->setClaseCell(cl);
	
	capaCelula->vaciaVectorCelulaSeleccionada();

	menuPopupCel->setSensitiveInicialPopup();
	menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam");
	panelDer->setSensitiveCalcDiam(false);
	panelDer->setSensitiveSelecClase(false);
	panelDer->setSensitiveSelecEstado(false);
	
	//Repintamos
	actualizarVista();
}

/**
 Establece el estado de las celulas.
 @param est, string.
 */
void PanelDibujado::estabEstadoPopup(string est)
{
	int tam, numCelula;
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();

	tam = capaCelula->getNumsCelulaSeleccionada();
		
	modifClaseEstadoP.emit();

	
	//if(est == "sin estado")
	if(est == "without state")
	{
		est = "";
	}
	
	for(int i = 0; i < tam; i++)
	{
		numCelula = capaCelula->getCelulaSeleccionada(i);
		
		est = capaCelula->setEstadoCelulaSeleccionada(est, numCelula);
	}

	barraEst->setEstadoCell(est);
	
	capaCelula->vaciaVectorCelulaSeleccionada();

	menuPopupCel->setSensitiveInicialPopup();
	menuPrinc->setSensitiveOpcMenu("SubCalcularUnDiam");
	panelDer->setSensitiveCalcDiam(false);
	panelDer->setSensitiveSelecClase(false);
	panelDer->setSensitiveSelecEstado(false);
	
	//Repintamos
	actualizarVista();
}

/**
 Abre los paneles de diametros.
 @param condicion, bool si vale true activa la vista 1 si vale false activa la vista 2.
 */
void PanelDibujado::obtieneDiametros(bool condicion)
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();

	if(condicion)
	{
		panelDer->activaVistaDatos(1);
	}
	else
	{
		panelDer->activaVistaDatos(2);
	}
}

/**
 Actualiza la vista del panel de dibujado.
 */
void PanelDibujado::actualizarVista()
{
	if(sistemDibujo->getImagenOvocito())
	{
		sistemDibujo->repintadoImagen();
	
		if(surfaceCelulas)
		{
			capaCelula->setContexCelulasPrin(surfaceImagen);
			capaCelula->pintaBorde();
			capaCelula->setContexCelulasPrin(surfaceCelulas);	
		}
		if(surfaceRejilla && verRejilla)
		{
			rejilla->setContexRejilla(surfaceImagen);	
			rejilla->pintaRejilla();
			rejilla->pintaBordeRejilla();
			rejilla->setContexRejilla(surfaceRejilla);
		}
	
		on_expose_event(NULL);
	}
}

/**
 Selecciona todas las celulas.
 */
void PanelDibujado::selecAllCell()
{
	PanelPropiedades *panelDer;

	panelDer = interfazPrincipal->getPanelPropiedades();
	
	capaCelula->selecAllCells();

	//Repintado
	repintaCapaCelulas();

	if(capaCelula->getNumsCelulaSeleccionada())
	{
		menuPopupCel->setSensitivePopup("eliminar", true);
		menuPopupCel->setSensitivePopup("popClases", true);
		menuPopupCel->setSensitivePopup("popEstados", true);
		panelDer->setSensitiveSelecClase(true);
		panelDer->setSensitiveSelecEstado(true);
	}
}

/**
 Pinta la imagen de la mascara y la guarda en formato png.
 */
void PanelDibujado::pintaImagenMascara(const string &ruta)
{
	on_expose_event(NULL);
	
	crExt = Cairo::Context::create(surfaceImagen);

	crExt->mask(surfaceCelulas, 0, 0);

	surfaceImagen->write_to_png(ruta);
}

/**
 Señal de pintado de puntos.
 */
PanelDibujado::pintado_puntos PanelDibujado::signal_cambiar_menu()
{
	return pPuntos;
}

/**
 Señal modificacion celulas.
 */
PanelDibujado::modifica_celulas PanelDibujado::signal_modificacion_celulas()
{
	return modifCell;
}

/**
 Senal para detectar si se cambia la clase o el estado de una celula.
 */
PanelDibujado::modificaClasEstPopup PanelDibujado::signal_modifica_classEstPopup()
{
	return modifClaseEstadoP;

}

/**
 Señanl para detectar si se selecciona una celula.
 @return tipo de datos seleccionCelula.
 */
PanelDibujado::seleccionaCelula PanelDibujado::signal_selecciona_celula()
{
	return selecCellSignal;
}
