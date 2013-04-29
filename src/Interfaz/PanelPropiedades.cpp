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

#include "PanelPropiedades.h"
#include "Interfaz/InterfazGovocitos.h"
#include "Interfaz/PanelDibujado.h"

/**
 Constructor.
 @param ig, InterfaGovocitos.
 @param pd, PanelDibujado.
 */
PanelPropiedades::PanelPropiedades(InterfazGovocitos &ig, PanelDibujado &pd)
{
	panelDibuj = &pd;
	interfazPrincipal = &ig;

	micras = 1;
	//Iniciamos el panel derecho y a continuacion lo añadimos al scrollPanDer
	iniciadorPanelDer();
	
	set_policy(Gtk::POLICY_NEVER,Gtk::POLICY_AUTOMATIC);
	add(*panDer);	
	
	//Establece la seleccion de tipos y clases a ""
	selecionaClase.set_active(0);
	selecionaEstado.set_active(0);
	selecionaClase.set_sensitive(false);
	selecionaEstado.set_sensitive(false);
	
	cierraPanel->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::cierraPaneLateral));
	EliminaCelula->signal_clicked().connect(sigc::mem_fun(*panelDibuj, &PanelDibujado::eliminaCelula));
	UnePuntos->signal_clicked().connect(sigc::mem_fun(*panelDibuj, &PanelDibujado::unePuntosPintado));
	activaCapaRejR->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::activaRejilla));
	activaBordeRejR->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::activaBordeRejilla));
	SelecCel->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	AnhadirCel->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	ModifCel->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	AnhadirCelPT->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	AnhadirCelManoAL->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	calcDiamet->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &PanelPropiedades::activaVistaDatos), 1));
	calcEstadist->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &PanelPropiedades::activaVistaDatos), 3));
	calcTodosDiam->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &PanelPropiedades::activaVistaDatos), 2));
	selecionaClase.signal_changed().connect(sigc::mem_fun(*this, &PanelPropiedades::estableceClase));
	selecionaEstado.signal_changed().connect(sigc::mem_fun(*this, &PanelPropiedades::estableceEstado));
	confRej->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::configurarRejilla));
	rejillaDefec->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	rejillaPersonal->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	activCapaCelE->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::activaCapaCelulas));
	activCapaCelR->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::activaCapaCelulas));
	printDataG->signal_clicked().connect(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::exportCsvDatosCell));
	selectAllG->signal_clicked().connect(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::seleccionaTodasCelulas));
	printDataG1->signal_clicked().connect(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::exportCsvStadisticalData));

	//Modo panel deteccion no supervisada
	printDataGNSup->signal_clicked().connect(sigc::mem_fun(*interfazPrincipal, &InterfazGovocitos::finalDetecNoSupervisada));
	EliminaCelulaNSup->signal_clicked().connect(sigc::mem_fun(*panelDibuj, &PanelDibujado::eliminaCelula));
	ModifCelNSup->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	AnhadirCelManoALNSup->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	AnhadirCelPTNSup->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	SelecCelNSup->signal_clicked().connect(sigc::mem_fun(*this, &PanelPropiedades::setSensiblePanel));
	UnePuntosNSup->signal_clicked().connect(sigc::mem_fun(*panelDibuj, &PanelDibujado::unePuntosPintado));
		
	show_all();
}

/**
 Destructor.
 */
PanelPropiedades::~PanelPropiedades()
{
	delete panDer;
}

/**
 Establece el objeto de la rejilla.
 @param rej, Rejilla.
 */
void PanelPropiedades::setRejilla(Rejilla &rej)
{
	rejilla = &rej;
}

/**
 Enlaza las variables de la clase a las del archivo glade.
 */
void PanelPropiedades::iniciadorPanelDer()
{	
	Utiles::getWidgetGlade(Utiles::getGladeFile("PanelPropiedades.glade"), "panDer", 
	                       "panDer", &panDer,
	                       "blocNotas", &blocNotas,
	                       "cierraPanel", &cierraPanel,
	                       "SelecCel", &SelecCel,
	                       "AnhadirCel", &AnhadirCel,
	                       "ModifCel", &ModifCel,
	                       "AnhadirCelManoAL", &AnhadirCelManoAL,
	                       "AnhadirCelPT", &AnhadirCelPT,
	                       "UnePuntos", &UnePuntos,
	                       "EliminaCelula", &EliminaCelula,
	                       "activCapaCelE", &activCapaCelE,
	                       "activCapaCelR", &activCapaCelR,
	                       "panelP", &panelP,
	                       "calcDiamet", &calcDiamet,
	                       "calcEstadist", &calcEstadist,
	                       "confRej", &confRej,
	                       "rejillaDefec", &rejillaDefec,
	                       "rejillaPersonal", &rejillaPersonal,
	                       "calcTodosDiam", &calcTodosDiam,
	                       "hboxClases", &hboxClases,
	                       "hboxEstados", &hboxEstados,
	                       "nPunR", &nPunR,
	                       "nColR", &nColR,
	                       "nFilasR", &nFilasR,
	                       "separR", &separR,
	                       "activaCapaRejR", &activaCapaRejR,
	                       "activaBordeRejR", &activaBordeRejR,
	                       "printDataG", &printDataG,
	                       "printDataGNSup", &printDataGNSup,
	                       "EliminaCelulaNSup", &EliminaCelulaNSup,
	                       "ModifCelNSup", &ModifCelNSup,
	                       "AnhadirCelManoALNSup", &AnhadirCelManoALNSup,
	                       "AnhadirCelPTNSup", &AnhadirCelPTNSup,
	                       "SelecCelNSup", &SelecCelNSup,
	                       "UnePuntosNSup", &UnePuntosNSup,
	                       "selectAllG", &selectAllG,
	                       "NotUseAreaG", &NotUseAreaG,
	                       "printDataG1", &printDataG1,
	                       NULL);

	hboxClases->add(selecionaClase);
	hboxEstados->add(selecionaEstado);
}

/**
 Carga las etiquetas y las clases de la aplicacion.
 */
void PanelPropiedades::cargaClasEstadPanel()
{	
	int numClases, numEstados;

	clases = configuracion->getDatosClases();
	estados = configuracion->getDatosEstados();
	
	numClases = clases->size();
	numEstados = estados->size();
	selecionaClase.clear();
	selecionaEstado.clear();
	selecionaClase.append_text("");
	//selecionaClase.append_text("sin clasificar");
	selecionaClase.append_text("unclassified");
	selecionaEstado.append_text("");
	//selecionaEstado.append_text("sin estado");
	selecionaEstado.append_text("whithout state");
	
	for(int i = 0; i < numClases; i++)
	{
		if((*clases)[i].getEnUso())
		{
			selecionaClase.append_text((*clases)[i].getEtiquetaClasificacion());
		}
	}
	for(int i = 0; i < numEstados; i++)
	{
		if((*estados)[i].getEnUso())
		{
			selecionaEstado.append_text((*estados)[i].getEtiquetaClasificacion());
		}
	}	
}

/**
 Establece el objeto que contiene la configuración del sistema.
 @param cfg, ConfigGovocitos.
 */
void PanelPropiedades::setConfiguracion(ConfigGovocitos &cfg)
{
	configuracion = &cfg;

	cargaClasEstadPanel();
	setOpcionesRej();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool. 
 */
bool PanelPropiedades::getAnhadirCel()
{
	return AnhadirCel->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getAnhadirCelManoAL()
{
	return AnhadirCelManoAL->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getAnhadirCelPT()
{
	return AnhadirCelPT->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getAnhadirCelManoALNSup()
{
	return AnhadirCelManoALNSup->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario
 @return bool.
 */
bool PanelPropiedades::getAnhadirCelPTNSup()
{
	return AnhadirCelPTNSup->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getModifCel()
{
	return ModifCel->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getModifCelNSup()
{
	return ModifCelNSup->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getSelecCel()
{
	return SelecCel->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getSelecCelNSup()
{
	return SelecCelNSup->get_active();
}

/**
 Devuelve verdadero si esta activado el atributo, falso en caso contrario.
 @return bool.
 */
bool PanelPropiedades::getNotUseAreaImage()
{
	return NotUseAreaG->get_active();
}

/**
 Devuelve la pagina actual del bloc de notas.
 @return bool.
 */
int PanelPropiedades::getPagBlocnotas()
{
	return blocNotas->get_current_page();
}

/**
 Devuelve el valor de la rejilla seleccionada.
 @return bool.
 */
bool PanelPropiedades::getRejillaDefec()
{
	return rejillaDefec->get_active();
}

/**
 Establece la pagina del bloc de notas.
 @param pag, entero con el valor de la pagina.
 */
void PanelPropiedades::setPagBlocNotas(int pag)
{
	blocNotas->set_current_page(pag);
}

/**
 Establece el nombre del panel actual.
 @param lab, string nombre del panel.
 */
void PanelPropiedades::setLabelPanel(const string &lab)
{
	panelP->set_label(lab);
}

/**
 Hace sensivel el atributo.
 @param s, bool.
 */
void PanelPropiedades::setSensitiveSelecCel(bool s)
{
	SelecCel->set_sensitive(s);
}

/**
 Hace sensivel el atributo.
 @param s, bool.
 */
void PanelPropiedades::setSensitiveEliminaCelula(bool s)
{
	EliminaCelula->set_sensitive(s);
}

/**
 Hace sensible el atributo
 @param s, bool.
 */
void PanelPropiedades::setSensitiveAnhadirCelManoAL(bool s)
{
	AnhadirCelManoAL->set_sensitive(s);
}

/**
 Hace sensible el atributo.
 @param s, bool.
 */
void PanelPropiedades::setSensitiveAnhadirCelPT(bool s)
{
	AnhadirCelPT->set_sensitive(s);
}

/**
 Hace sensivel el atributo.
 @param cl, bool.
 */
void PanelPropiedades::setSensitiveSelecClase(bool cl)
{
	selecionaClase.set_sensitive(cl);
}

/**
 Hace sensivel el atributo.
 @param est, bool.
 */
void PanelPropiedades::setSensitiveSelecEstado(bool est)
{
	selecionaEstado.set_sensitive(est);
}

/**
 Hace sensible el atributo.
 @param s, bool.
 */
void PanelPropiedades::setSensitiveUnePuntos(bool s)
{
	UnePuntos->set_sensitive(s);	
}

/**
 Hace sensible el atributo.
 @param c, bool.
 */
void PanelPropiedades::setSensitiveCalcDiam(bool c)
{
	calcDiamet->set_sensitive(c);
}

/**
 Hace sensible el atributo.
 @param c, bool.
 */
void PanelPropiedades::setSentiviePrintData(bool c)
{
	printDataG->set_sensitive(c);
}

/**
 Hace sensible el atributo.
 @param c, bool.
 */
void PanelPropiedades::setSensitivePrinData1(bool c)
{
	printDataG1->set_sensitive(c);
}

/**
 Activa el atributo.
 @param c, bool.
 */
void PanelPropiedades::setActivaRejilla(bool c)
{
	activaCapaRejR->set_active(c);
}

/**
 Activa el atributo.
 @param c, bool.
 */
void PanelPropiedades::setActivaBordeRej(bool c)
{
	activaBordeRejR->set_active(c);
}

/**
 Establece el texto activo de las etiquetas.
 @param t, string.
 */
void PanelPropiedades::setSeleccionaClase(const string &t)
{
	selecionaClase.set_active_text(t);
}

/**
 Establece el texto activo de las clases.
 @param t, string.
 */
void PanelPropiedades::setSeleccionaEstado(const string &t)
{
	selecionaEstado.set_active_text(t);
}

/**
 Establece como activo la seleccion de células.
 @param s, bool.
 */
void PanelPropiedades::setActiveSelec(bool s)
{
	SelecCel->set_active(s);
}

/**
 Establece como activo la rejilla por defecto.
 @param s, bool.
 */
void PanelPropiedades::setActiveRejillaDefec(bool s)
{
	rejillaDefec->set_active(s);
}

/**
 Pasa el vector de opciones.
 */
void PanelPropiedades::setOpcionesRej()
{	
	opcRej = configuracion->getDatosRejilla();
	
	rejillaDefec->set_active(true);

	rejilla->setSeparPun(configuracion->getDatosPreferencias()->getSeparPuntos());

	if(blocNotas->get_current_page() == 1)
	{
		preCalculaRejilla();
	}
}

/**
 Establece el valor de micras por pixel.
 @param m, double valor de micras.
 */
void PanelPropiedades::setValorMicras(double m)
{
	micras = m;
}

/**
 Cierra el panel lateral.
 */
void PanelPropiedades::cierraPaneLateral()
{
	hide();
}

/**
 Hace sensibles los menus del panel lateral.
 */
void PanelPropiedades::setSensiblePanel()
{	
	if(blocNotas->get_current_page() == 1)
	{
		if(rejillaDefec->get_active())
		{
			if(confRej->is_sensitive())
			{
				activaCapaRejR->set_active(false);
				activaBordeRejR->set_active(false);
				rejilla->setBordeComp(false);
				rejilla->setVisibleCapaRejilla(false);
		
				//Repintado
				panelDibuj->actualizarVista();
				
				interfazPrincipal->destruyeDatos();
				preCalculaRejilla();
				confRej->set_sensitive(false);
			}
		}
		else if(rejillaPersonal->get_active())
		{
			if(!confRej->is_sensitive())
			{
				configurarRejilla();
				confRej->set_sensitive(true);
			}
		}
	}
	else if(blocNotas->get_current_page() == 0)
	{
		if(SelecCel->get_active())
		{
			//Hacemos no sensibles
			AnhadirCelManoAL->set_sensitive(false);
			AnhadirCelPT->set_sensitive(false);
			UnePuntos->set_sensitive(false);

			//Hacemos sensible
			EliminaCelula->set_sensitive(true);
		}
		else if(AnhadirCel->get_active())
		{
			//Hacemos sensibles
			AnhadirCelManoAL->set_sensitive(true);
			AnhadirCelPT->set_sensitive(true);
		
			//Hacemos no sensibles
			selecionaClase.set_sensitive(false);
			selecionaEstado.set_sensitive(false);
			EliminaCelula->set_sensitive(false);
		
			if(AnhadirCelPT->get_active())
				UnePuntos->set_sensitive(true);
			else if(AnhadirCelManoAL->get_active())
				UnePuntos->set_sensitive(false);
		}
		else if(ModifCel->get_active())
		{
			//Hacemos sensibles
			AnhadirCelManoAL->set_sensitive(true);
			AnhadirCelPT->set_sensitive(true);

			//Hacemos no sensibles
			EliminaCelula->set_sensitive(false);
			selecionaClase.set_sensitive(false);
			selecionaEstado.set_sensitive(false);
		
			if(AnhadirCelPT->get_active())
				UnePuntos->set_sensitive(true);
			else if(AnhadirCelManoAL->get_active())
				UnePuntos->set_sensitive(false);
		}
		else if(NotUseAreaG->get_active())
		{
			//Hacemos no sensibles
			AnhadirCelManoAL->set_sensitive(false);
			AnhadirCelPT->set_sensitive(false);
			UnePuntos->set_sensitive(false);
			EliminaCelula->set_sensitive(false);
		}
	}
	else if(blocNotas->get_current_page() == 2)
	{
		if(SelecCelNSup->get_active())
		{
			//Hacemos no sensibles
			AnhadirCelManoALNSup->set_sensitive(false);
			AnhadirCelPTNSup->set_sensitive(false);
			UnePuntosNSup->set_sensitive(false);

			//Hacemos sensible
			EliminaCelulaNSup->set_sensitive(true);
		}
		else if(ModifCelNSup->get_active())
		{
			//Hacemos sensibles
			AnhadirCelManoALNSup->set_sensitive(true);
			AnhadirCelPTNSup->set_sensitive(true);

			//Hacemos no sensibles
			EliminaCelulaNSup->set_sensitive(false);
		
			if(AnhadirCelPTNSup->get_active())
			{
				UnePuntosNSup->set_sensitive(true);
			}
			else if(AnhadirCelManoALNSup->get_active())
			{
				UnePuntosNSup->set_sensitive(false);
			}
		}
	}
}

/**
 Activa la rejilla.
 */
void PanelPropiedades::activaRejilla()
{		
	//vista rejilla
	if(activaCapaRejR->get_active())
	{
		rejilla->setVisibleCapaRejilla(true);
	}
	else
	{
		rejilla->setVisibleCapaRejilla(false);
	}

	//Repintado
	panelDibuj->actualizarVista();
}

/**
 Activa el borde de la rejilla.
 */
void PanelPropiedades::activaBordeRejilla()
{
	//vista borde rejilla
	if(activaBordeRejR->get_active())
	{
		rejilla->setBordeComp(true);
	}
	else
	{
		rejilla->setBordeComp(false);
	}

	//Repintado
	panelDibuj->actualizarVista();
}	
			
/**
 Activa el bordeado de las celulas.
 */
void PanelPropiedades::activaCapaCelulas()
{
	if((activCapaCelE->get_active() && blocNotas->get_current_page() == 0) ||
	   (activCapaCelR->get_active() && blocNotas->get_current_page() == 1))
	{
		panelDibuj->getCapaCelula()->setVisibleCapaCelulas(true);
	}
	else
	{
		panelDibuj->getCapaCelula()->setVisibleCapaCelulas(false);
	}
	
	//Repintado
	panelDibuj->actualizarVista();
}

/**
 Establece la etiqueta.
 */
void PanelPropiedades::estableceClase()
{
	if(panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		string text = selecionaClase.get_active_text();
		int tam = panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada();
		int numCelula;
		
		modifClaseEstado.emit();
		
		for(int i = 0; i < tam; i++)
		{
			numCelula = panelDibuj->getCapaCelula()->getCelulaSeleccionada(i);

			//if(text == "sin clasificar")
			if(text == "unclassified")
			{
				text = "";
			}

			panelDibuj->getCapaCelula()->setClaseCelulaSeleccionada(text, numCelula);
		}
		
		panelDibuj->getCapaCelula()->vaciaVectorCelulaSeleccionada();
		selecionaClase.set_active_text("");
		selecionaClase.set_sensitive(false);
		selecionaEstado.set_sensitive(false);
		setSensitiveCalcDiam(false);
		
		//Repintamos
		panelDibuj->actualizarVista();
	}
}

/**
 Establece la clase.
 */
void PanelPropiedades::estableceEstado()
{
	if(panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		string text = selecionaEstado.get_active_text();
		int tam = panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada();
		int numCelula;
		
		modifClaseEstado.emit();
		
		for(int i = 0; i < tam; i++)
		{
			numCelula = panelDibuj->getCapaCelula()->getCelulaSeleccionada(i);

			//if(text == "sin estado")
			if(text == "whithout state")
			{
				text = "";
			}
		
			panelDibuj->getCapaCelula()->setEstadoCelulaSeleccionada(text, numCelula);
		}
		
		panelDibuj->getCapaCelula()->vaciaVectorCelulaSeleccionada();
		selecionaEstado.set_active_text("");
		selecionaClase.set_sensitive(false);
		selecionaEstado.set_sensitive(false);
		setSensitiveCalcDiam(false);
		
		//Repintamos
		panelDibuj->actualizarVista();
	}
}

/**
 Lanza ventana de seleccion de la rejilla.
 */
void PanelPropiedades::configurarRejilla()
{
	RejillaPersonalizada personalRej(*opcRej);
	int	rejillaUso;

	activaCapaRejR->set_active(false);
	activaBordeRejR->set_active(false);
	rejilla->setBordeComp(false);
	rejilla->setVisibleCapaRejilla(false);

	//Repintado
	panelDibuj->actualizarVista();
				
	interfazPrincipal->destruyeDatos();
	
	if(personalRej.muestraMenuSeleccion(rejillaUso))
	{
		rejilla->setSeparPun((*opcRej)[rejillaUso].getSeparaPuntos());
		rejilla->setNumColumnas((*opcRej)[rejillaUso].getNumColumnas());
		rejilla->setNumFilas((*opcRej)[rejillaUso].getNumFilas());
		rejilla->setAnchoRej(0);
		rejilla->setAltoRej(0);
	}
	else
	{
		rejilla->setAnchoRej(rejilla->getAncho());
		rejilla->setAltoRej(rejilla->getAlto());
		rejilla->setSeparPun(configuracion->getDatosPreferencias()->getSeparPuntos());
        rejilla->setNumColumnas(0);
        rejilla->setNumFilas(0);
		rejillaDefec->set_active(true);
	}

	rejilla->calculaRejilla();
	
	if(rejillaDefec->get_active() && rejilla->getSeparPuntos() == 1)
	{
		nPunR->set_text(Utiles::converString(rejilla->getAncho() * rejilla->getAlto()));
		nColR->set_text(Utiles::converString(rejilla->getAncho()));
		nFilasR->set_text(Utiles::converString(rejilla->getAlto()));
		separR->set_text(Utiles::converString(1));

		activaCapaRejR->set_sensitive(false);
		activaBordeRejR->set_sensitive(false);
	}
	else
	{	
		nPunR->set_text(Utiles::converString(rejilla->getNumPuntos()));
		nColR->set_text(Utiles::converString(rejilla->getNumColumnas()));
		nFilasR->set_text(Utiles::converString(rejilla->getNumFilas()));
		separR->set_text(Utiles::converString(rejilla->getSeparPuntos()));

		activaCapaRejR->set_sensitive(true);
		activaBordeRejR->set_sensitive(true);
	}
	
	panelDibuj->creaRejilla();
}

/**
 Precalcula la rejilla a utilizar para calcular los datos.
 */
void PanelPropiedades::preCalculaRejilla()
{
	rejilla->setAnchoRej(rejilla->getAncho());
	rejilla->setAltoRej(rejilla->getAlto());
	rejilla->setSeparPun(configuracion->getDatosPreferencias()->getSeparPuntos());
    rejilla->setNumColumnas(0);
    rejilla->setNumFilas(0);

	rejilla->calculaRejilla();
	
	if(rejilla->getSeparPuntos() != 1)
	{
		nPunR->set_text(Utiles::converString(rejilla->getNumPuntos()));
		nColR->set_text(Utiles::converString(rejilla->getNumColumnas()));
		nFilasR->set_text(Utiles::converString(rejilla->getNumFilas()));
		separR->set_text(Utiles::converString(rejilla->getSeparPuntos()));

		activaCapaRejR->set_sensitive(true);
		activaBordeRejR->set_sensitive(true);
	}
	else
	{
		nPunR->set_text(Utiles::converString(rejilla->getAncho() * rejilla->getAlto()));
		nColR->set_text(Utiles::converString(rejilla->getAncho()));
		nFilasR->set_text(Utiles::converString(rejilla->getAlto()));
		separR->set_text(Utiles::converString(1));

		activaCapaRejR->set_sensitive(false);
		activaBordeRejR->set_sensitive(false);
	}
	
	panelDibuj->creaRejilla();
}

/**
 Senal para detectar si se cambia la clase o el estado de una celula.
 */
PanelPropiedades::modificaClasEstadoC PanelPropiedades::signal_modifica_classEstado()
{
	return modifClaseEstado;
}

/**
 Señal para detectar que se activa la vista de datos.
 */
PanelPropiedades::abrePanelDatos PanelPropiedades::signal_abre_datos()
{
	return panelDatosAbierto;
}

/**
 Emite señal de activado de datos.
 */
void PanelPropiedades::activaVistaDatos(int numSen)
{
	panelDatosAbierto.emit(numSen);
}
