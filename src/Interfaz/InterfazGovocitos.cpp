/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InterfazGovoctios.cpp
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

#include "InterfazGovocitos.h"
#include "CoreGovocitos.h"

/**
 Cosntructor.
 */
InterfazGovocitos::InterfazGovocitos()
{
	set_title("Govocitos");
	set_default_size(1024, 768);
	set_icon_from_file(Utiles::getIconoFile("logoGovocitos.png"));
	cambios = false;
	datosE = NULL;
	datosD = NULL;
	
	//Creamos la barra de estado
	bEstado = new BarraEstado();

	//Creamos el menu principal
	menBarPrincipal = new MenuBarraPrincipal(*this);

	//Crea el menu principal y la barra de herramientas
	menuPrincipal();
	
	//Creamos el panel de dibujado
	panelDibujo = new PanelDibujado(*this);

	//Creamos el panel de propiedades
	panelProp = new PanelPropiedades(*this, *panelDibujo);
	
	//Pone el scrollbar en automatico para el panel Izquierdo y añadel el panel Izquierdo
	scrollPanIzq.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	scrollPanIzq.add(*panelDibujo);

	//Creamos el panel de fecundidad
	panelFec = new PanelFecundidad();
	
	//Contenedor que contendra los elementos de la pantalla principal
	add(m_Box);

	//Crea el panel principal donde se cargara la imagen y las estadisticas
	panelCentral();

	//Añade la barra de estado
	m_Box.pack_start(*bEstado, false, true);
	
	show_all_children(); 
	noteBookPrin.set_current_page(0);

	//Oculta el panel derecho
	panelProp->cierraPaneLateral();

	signal_key_press_event().connect(sigc::mem_fun(*this, &InterfazGovocitos::multiSelecPressRelease));
	signal_key_release_event().connect(sigc::mem_fun(*this, &InterfazGovocitos::multiSelecPressRelease));

	panelProp->signal_abre_datos().connect(sigc::mem_fun(this, &InterfazGovocitos::activaPanelAuxiliarDatos));
	panelFec->signal_imprime_datos().connect(sigc::mem_fun(this, &InterfazGovocitos::exporFecundidadCSV));
	panelFec->signal_datos_bd().connect(sigc::mem_fun(this, &InterfazGovocitos::exporFecundidadBD));
	panelFec->signal_datos_rejilla().connect(sigc::mem_fun(this, &InterfazGovocitos::exporRejillaBD));
}

/**
 Destructor.
 */
InterfazGovocitos::~InterfazGovocitos()
{
	delete menBarPrincipal;
	delete panelProp;
	delete panelDibujo;
	delete bEstado;
	delete panelProp;
}

/**
 Establece el objeto controlador de la case CoreGovocitos.
 @param cg, referencia del objeto CoreGovocitos que controla la aplicación.
 */
void InterfazGovocitos::setControlador(CoreGovocitos &cg)
{
	driverGovocitos = &cg;
}

/**
 Crea el menu principal y la barra de herramientas del programa
 */
void InterfazGovocitos::menuPrincipal()
{	
	//Añade el menu al contenedor widget
	Gtk::Widget* pMenubar = menBarPrincipal->getWidgetMenuBarraPrincipal("/MenuBar");
	if(pMenubar)
		m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);
	
	//Añade la barra de herramientas al contenedor widget
	Gtk::Widget* pToolbar = menBarPrincipal->getWidgetMenuBarraPrincipal("/ToolBar");
	if(pToolbar)
		m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);

	add_accel_group(menBarPrincipal->getUIManager()->get_accel_group());
}

/**
 Carga el panel central y inicializa los dos paneles izquierdo y derecho
 */
void InterfazGovocitos::panelCentral()
{	
	//Añadimos el panIzq y el panDer al panel central
	panelC.pack1(panelDatos, true, false);
	panelC.pack2(*panelProp, false, false);
	panelDatos.pack1(scrollPanIzq, true, true);

	//Añadimos al blocNotas el panelCentral y el de fecundidad
	noteBookPrin.insert_page(panelC, 0);
	noteBookPrin.insert_page(*panelFec, 1);
	noteBookPrin.set_show_tabs(false);
	
	//Añadimos el panel central al contenedor
	m_Box.add(noteBookPrin);
}

/**
 Destruye el objeto de datos
 */
void InterfazGovocitos::destruyeDatos()
{
	if(panelDibujo->getActivaDetecSupervis())
	{
		panelDibujo->setActivaDetecSupervis(false);

		panelDibujo->getCapaCelula()->borrarCelulaNueva();
	}
	
	if(panelDatos.get_child2())
	{
		if(datosE)
		{
			panelProp->setSensitivePrinData1(false);
			panelDatos.remove(*datosE);
			delete datosE;
			datosE = NULL;
		}
		else if(datosD)
		{
			panelProp->setSentiviePrintData(false);
			panelDatos.remove(*datosD);
			delete datosD;
			datosD = NULL;
		}
	}
}

/**
 Abre el diálogo de abrir imagenes.
 */
void InterfazGovocitos::menuAbrir()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	//Detectamos si se han realizado cambios
	menuCerrar();
	
	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();
	
	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	noteBookPrin.set_current_page(0);
	
	if(dialogoLocal->dialogoAbrirImagen(imgNueva))
	{	
		driverGovocitos->abrirImagenLocal();
		
		//Activamos el menu de abrir fichero xml
		menBarPrincipal->setSensibleOpcionesBasicas();

		set_title(imgNueva->getNombreImg() + " (Govocitos)");

		menBarPrincipal->setSensitiveOpcMenu("SubMenuAbrirXmlRemoto", true);
		//Habilitamos el menu de deteccion automatica
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeteccionSupervisada1", true);

		//Metemos datos en la barra de estado
		bEstado->setNivelZoom(10);
		bEstado->setResolucionImagen(imgNueva->getAnchoImg(), imgNueva->getAltoImg());
		//bEstado->setClaseCell("sin clasificar");
		//bEstado->setEstadoCell("sin estado");
		bEstado->setClaseCell("unclassified");
		bEstado->setEstadoCell("without state");

		//Destruimos los datos de los diametros y la rejilla
		destruyeDatos();	

		//Desactivamos la rejilla
		panelProp->setActivaRejilla(false);
		panelProp->setActivaBordeRej(false);
	}
	
	delete dialogoLocal;
}

/**
 Abre el dialogo Cargar fichero de células.
 */
void InterfazGovocitos::menuCargarCoord()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	//Detectamos si se han realizado cambios
	dialogoCambios();
	
	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();

	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	if(dialogoLocal->dialogoAbrirXml(imgNueva))
	{
		driverGovocitos->abrirXmlLocal();

		menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion", true);

		//Si hay algun panel de datos se destruira
		destruyeDatos();

		menBarPrincipal->setSensitiveOpcMenu("SubMenuRehacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuSeleccionar", true);
		menBarPrincipal->setSensitiveOpcMenu("SubCalcularDiam", true);
	}

	delete dialogoLocal;	

	//Comprobamos si hay clases o estados
	mensajeSinClasesEstados();

}

/**
 Abre el dialogo de abrir imagenes y ficheros de células.
 */
void InterfazGovocitos::menuAbrirIC()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	//Detectamos si se han realizado cambios
	menuCerrar();
	
	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();
	
	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	noteBookPrin.set_current_page(0);
	
	if(dialogoLocal->dialogoAbrirImagen(imgNueva))
	{
		driverGovocitos->abrirImagenLocal();
		
		//Activamos el menu de abrir fichero xml
		menBarPrincipal->setSensibleOpcionesBasicas();

		set_title(imgNueva->getNombreImg() + " (Govocitos)");

		menBarPrincipal->setSensitiveOpcMenu("SubMenuAbrirXmlRemoto", true);
		//Habilitamos el menu de deteccion automatica
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeteccionSupervisada1", true);

		//Metemos datos en la barra de estado
		bEstado->setNivelZoom(10);
		bEstado->setResolucionImagen(imgNueva->getAnchoImg(), imgNueva->getAltoImg());
		bEstado->setClaseCell("sin clasificar");
		bEstado->setEstadoCell("sin estado");

		string rutaNombreImagen;
		
		rutaNombreImagen = datosPrefG->getArchivCel() + "/" + imgNueva->getNombreImg();

		if(Fichero::compruebaFich(rutaNombreImagen + ".xml"))
		{
			imgNueva->setRutaXmlImg(rutaNombreImagen + ".xml");

			driverGovocitos->abrirXmlLocal();
			menBarPrincipal->setSensitiveOpcMenu("SubCalcularDiam", true);
		}
		else if(Fichero::compruebaFich(rutaNombreImagen + ".txt"))
		{
			imgNueva->setRutaXmlImg(rutaNombreImagen + ".txt");

			driverGovocitos->abrirXmlLocal();
			menBarPrincipal->setSensitiveOpcMenu("SubCalcularDiam", true);
		}
		else
		{
			//string texto = "No se ha encontrado su archivo de células";
			//string titulo = "Error al cargar las células";
			string texto = "Cell file not found";
			string titulo = "Error while loading cell file";

			Dialogos::dialogoError(texto, titulo);
		}

		menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion", true);	
		menBarPrincipal->setSensitiveOpcMenu("SubMenuSeleccionar", true);
	}

	delete dialogoLocal;

	//Comprobamos si hay clases o estados
	mensajeSinClasesEstados();
}

/**
 Abre el dialogo de abrir imagen del servidor.
 */
void InterfazGovocitos::menuAbrirRemoto()
{
	//Detectamos si se han realizado cambios
	menuCerrar();

	noteBookPrin.set_current_page(0);
	
	if(driverGovocitos->abrirImagenRemotaBD())
	//if(driverGovocitos->abrirImagenRemota())
	{	
		ImageCells *imgNueva;

		imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();
		
		menBarPrincipal->setSensibleOpcionesBasicas();
		menBarPrincipal->setSensitiveOpcMenu("SubMenuAbrirXmlRemoto", true);
		menBarPrincipal->setSensitiveOpcMenu("SubMenuGuardarBD", true);
		
		//Establecemos el titulo de la imagen en la barra principal del programa
		set_title(imgNueva->getNombreImg() + " (Govocitos)");

		//Habilitamos el menu de deteccion automatica
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeteccionSupervisada1", true);

		//Metemos datos en la barra de estado
		bEstado->setNivelZoom(10);
		bEstado->setResolucionImagen(imgNueva->getAnchoImg(), imgNueva->getAltoImg());
		//bEstado->setClaseCell("sin clasificar");
		//bEstado->setEstadoCell("sin estado");
		bEstado->setClaseCell("unclassified");
		bEstado->setEstadoCell("without state");

		//Si hay algun panel de datos se destruira
		destruyeDatos();

		//Desactivamos la rejilla
		panelProp->setActivaRejilla(false);
		panelProp->setActivaBordeRej(false);
	}
}

/**
 Abre el dialogo de abrir fichero de celulas del servidor.
 */
void InterfazGovocitos::menuAbrirXmlRemoto()
{
	//Detectamos si se han realizado cambios
	dialogoCambios();

	if(driverGovocitos->AbrirXmlRemotoBD())
	//if(driverGovocitos->AbrirXmlRemoto())
	{
		//Habilitamos el menu de deteccion automatica
		menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion", true);

		//Si hay algun panel de datos se destruira
		destruyeDatos();

		menBarPrincipal->setSensitiveOpcMenu("SubMenuRehacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuSeleccionar", true);
		menBarPrincipal->setSensitiveOpcMenu("SubMenuGuardarBD", true);
		menBarPrincipal->setSensitiveOpcMenu("SubCalcularDiam", true);
	}
}

/**
 Abre el dialogo que abre las imagenes y los ficheros de células relacionados del 
 servidor.
 */
void InterfazGovocitos::menuAbrirICRemoto()
{
	menuAbrirRemoto();

	if(driverGovocitos->AbrirXmlRemotoImgPre())
	{
		//Habilitamos el menu de deteccion automatica
		menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion", true);

		//Si hay algun panel de datos se destruira
		destruyeDatos();

		menBarPrincipal->setSensitiveOpcMenu("SubMenuRehacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuSeleccionar", true);
		menBarPrincipal->setSensitiveOpcMenu("SubMenuGuardarBD", true);
		menBarPrincipal->setSensitiveOpcMenu("SubCalcularDiam", true);
	}
}

/**
 Abre el dialogo de seleccionar individuo.
 */
void InterfazGovocitos::menuAbrirIndividuo()
{
	menuCerrar();
	
	if(driverGovocitos->AbrirIndividuoBD())
	//if(driverGovocitos->AbrirIndividuo())
	{
		string indiv;
		ListadoIndividuo *listIndi;

		listIndi = driverGovocitos->getModeloGovocitos()->getListadoIndividuo();

		indiv = listIndi->getCampanhaInd() + "-" + listIndi->getEspecieInd() + "-" + listIndi->getMuestreoInd() + "-" + listIndi->getIndividuoInd();
		set_title(indiv +  " (Govocitos)");
		
		noteBookPrin.set_current_page(1);
		
	}
}

/**
 Abre el dialgo de guardar fichero de células.
 */
void InterfazGovocitos::menuGuardar()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();
	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	string rutaCoordenadas = imgNueva->getRutaXmlImg();
	
	if(rutaCoordenadas == "" || rutaCoordenadas == "NULL")
	{
		rutaCoordenadas = dialogoLocal->dialogoGuardarComo(imgNueva->getNombreImg());

		if(rutaCoordenadas != "")
		{
			driverGovocitos->guardarCelulas(rutaCoordenadas, Utiles::obtieneTipoArch(rutaCoordenadas));

			imgNueva->setRutaXmlImg(rutaCoordenadas);
		}

		delete dialogoLocal;
	}
	else
	{
		string terminacion;

		terminacion = Utiles::obtieneTipoArch(rutaCoordenadas);

		driverGovocitos->guardarCelulas(rutaCoordenadas, terminacion);
	}

	cambios = false;
}

/**
 Abre el dialogo de guardar como ficheros de células.
 */
void InterfazGovocitos::menuGuardarComo()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();

	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	string rutaCoordenadas;

	rutaCoordenadas = dialogoLocal->dialogoGuardarComo(imgNueva->getNombreImg());

	if(rutaCoordenadas != "")
	{
		driverGovocitos->guardarCelulas(rutaCoordenadas, Utiles::obtieneTipoArch(rutaCoordenadas));

		cambios = false;
	}

	delete dialogoLocal;	
}

/**
 Guarda un fichero de células en el servidor.
 */
void InterfazGovocitos::menuGuardarXmlBD()
{
	string titulo, mensaje;
	
	//Procedemos a guardarlo en la BD
	if(!driverGovocitos->guardarCelulasBD())
	{
		titulo = "Upload File";
		mensaje = "The sftp can´t upload the selected file";

		Dialogos::dialogoError(mensaje, titulo);
	}
	else
	{
		titulo = "Save Xml BD";
		mensaje = "The cell file was save correctly at Data Base.";

		Dialogos::dialogoAdvertencia(mensaje, titulo);
		cambios = false;
	}
}

/**
 Abre el dialogo de guardar imagen.
 */
void InterfazGovocitos::menuGuardarImagen()
{
	OpcionesPref *datosPrefG;
	DialogoAGLocal *dialogoLocal;
	ImageCells *imgNueva;

	imgNueva = driverGovocitos->getModeloGovocitos()->getImageActual();
	datosPrefG = driverGovocitos->getModeloGovocitos()->getConfiguracion()->
		getDatosPreferencias();
	dialogoLocal = new DialogoAGLocal(datosPrefG->getArchivImag(), 
	                                  datosPrefG->getArchivCel());

	dialogoLocal->dialogoGuardarImagen(imgNueva->getNombreImg(), imgNueva->getImagenCelulas());

	delete dialogoLocal;	
}

/**
 Abre el dialogo de guardar mascara.
 */
void InterfazGovocitos::menuGuardarMascara()
{
	panelDibujo->pintaImagenMascara("/home/kote/Escritorio/prueba.png");
}

/**
 Cierra la aplicación.
 */
void InterfazGovocitos::menuSalir()
{
	if(cambios)
	{
		//string texto = "¿Desea guardar los cambios efectuados?";
		string texto = "Save changes?";
		string titulo = "Govocitos";
		
		if(Dialogos::dialogoConfirmacion(texto, titulo))
		{
			menuGuardarComo();
		}
	}
	
	hide();
}

/**
 Cierra la imagen y el fichero de células actualmente cargado.
 */
void InterfazGovocitos::menuCerrar()
{
	if(cambios)
	{
		//string texto = "¿Desea guardar los cambios efectuados?";
		string texto = "Save changes?";
		string titulo = "Govocitos";
		
		if(Dialogos::dialogoConfirmacion(texto, titulo))
		{
			menuGuardarComo();
		}
		cambios = false;
	}

	//Establecemos la sensibilidad del menu al modo inicial
	menBarPrincipal->estableceMenuPosiconInicial();
	
	if(panelDibujo)
	{
		delete panelDibujo;
		
		//Creamos el panel de dibujado
		panelDibujo = new PanelDibujado(*this);
	
		//Pone el scrollbar en automatico para el panel Izquierdo y añadel el panel Izquierdo
		scrollPanIzq.add(*panelDibujo);
	}
	
	if(panelProp)
	{
		delete panelProp;
		
		//Creamos el panel de propiedades
		panelProp = new PanelPropiedades(*this, *panelDibujo);

		panelC.pack2(*panelProp, false, false);
	}

	if(panelFec)
	{
		delete panelFec;
		
		panelFec = new PanelFecundidad();

		noteBookPrin.insert_page(*panelFec, 1);

		panelFec->signal_imprime_datos().connect(sigc::mem_fun(this, &InterfazGovocitos::exporFecundidadCSV));
		panelFec->signal_datos_bd().connect(sigc::mem_fun(this, &InterfazGovocitos::exporFecundidadBD));
		panelFec->signal_datos_rejilla().connect(sigc::mem_fun(this, &InterfazGovocitos::exporRejillaBD));
	}
	
	//Si hay algun panel de datos se destruira
	destruyeDatos();
	
	show_all_children();

	//Oculta el panel derecho
	panelProp->cierraPaneLateral();

	//Borramos los atributos de la barra de estado
	bEstado->setTodosEnBlanco();
	
	panelProp->signal_abre_datos().connect(sigc::mem_fun(this, &InterfazGovocitos::activaPanelAuxiliarDatos));

	driverGovocitos->cerrarImagen();
}

/**
 Abre el dialogo preferencias.
 */
void InterfazGovocitos::menuPreferencias()
{		
	ConfigGovocitos *datosConf;

	datosConf = driverGovocitos->getModeloGovocitos()->getConfiguracion();

	panelPreferencias = new Preferencias(*datosConf->getDatosPreferencias(), 
	                                     *datosConf->getDatosClases(), 
	                                     *datosConf->getDatosEstados(), 
	                                     *datosConf->getDatosRejilla());


	//Mostramos el dialogo de preferencias
	panelPreferencias->mostrarDialogoP();
	
	//En caso de que se produzca alguna modificacion se aplicaran los cambios
	if(panelPreferencias->getModifi())
	{
		driverGovocitos->ejecMenuPreferencias(*panelPreferencias);
	}

	//Comprobamos si estamos ejecutando el panel de fecundidad en caso afirmativo 
	//hay que comprobar la rejilla
	if(noteBookPrin.get_current_page() == 1)
	{
		panelFec->preCalculaRejilla();
		panelFec->recalcularFecundidad();
	}
	
	//Se deberia lanzar comprobar conectividar PENDIENTE
	delete panelPreferencias;
}

/**
 Abre el dialogo acerca de...
 */
void InterfazGovocitos::menuAcercaDe()
{
	Gtk::Dialog *dialogoAcercaDe;
	Gtk::Image *logoAbout;
	
	Utiles::getWidgetGlade(Utiles::getGladeFile("AcercaDe.glade"),"dialogoAcercaDe",
	                       "dialogoAcercaDe", &dialogoAcercaDe,
	                       "logoAbout", &logoAbout,
	                       NULL);
	
	dialogoAcercaDe->set_icon_from_file(Utiles::getIconoFile("acercaDe.png"));
	logoAbout->set(Utiles::getIconoFile("logoAbout.png"));

	dialogoAcercaDe->run();
	
	delete dialogoAcercaDe;
}

/**
 Ejecuta la accion deshacer.
 */
void InterfazGovocitos::desHacer()
{
	driverGovocitos->operacionDesHacer();
}

/**
 Ejecuta la accion rehacer.
 */
void InterfazGovocitos::reHacer()
{
	driverGovocitos->operacionReHacer();
}

/**
 Abre el panel edicion no supervisado.
 */
void InterfazGovocitos::barraNoSupervised()
{
	//Establece la vista del panel
	panelProp->setPagBlocNotas(2);
	panelProp->show();
	
	//panelProp->setLabelPanel("<b>Panel Editor</b>");
	panelProp->setLabelPanel("<b>Auto Detection Panel</b>");
}

/**
 Abre el panel barra editor.
 */
void InterfazGovocitos::barraEditor()
{
	//Si hay algun panel de datos se destruira
	destruyeDatos();
	
	//Desactivamos la rejilla
	panelProp->setActivaRejilla(false);
	panelProp->setActivaBordeRej(false);
	panelProp->setActiveRejillaDefec(true);
	menBarPrincipal->setSensitiveOpcMenu("SubCalcularEstadist");
	
	//Establece la vista del panel
	panelProp->setPagBlocNotas(0);
	panelProp->activaCapaCelulas();
	panelProp->show();
	
	//panelProp->setLabelPanel("<b>Panel Editor</b>");
	panelProp->setLabelPanel("<b>Edition Panel</b>");
}

/**
 Abre el panel de la rejilla.
 */
void InterfazGovocitos::activaRegilla()
{
	//Si hay algun panel de datos se destruira
	destruyeDatos();

	menBarPrincipal->setSensitiveOpcMenu("SubCalcularEstadist", true);
	
	//Establece la vista del panel
	panelProp->setPagBlocNotas(1);
	panelProp->activaCapaCelulas();	
	panelProp->preCalculaRejilla();
	panelProp->show();
	
	//panelProp->setLabelPanel("<b>Panel Rejilla</b>");
	panelProp->setLabelPanel("<b>Grid Panel</b>");
	
	if(!panelProp->getSelecCel())
	{
		panelProp->setActiveSelec(true);
		panelProp->setSensiblePanel();
	}
}

/**
 Aumenta el zoom de la imagen.
 */
void InterfazGovocitos::aumentaZoom()
{
	int zoomActual;
	
	if(driverGovocitos->aumentaZoom())
	{
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomIn");
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoom100");
	}

	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomOut", true);

	//Actualizamos el varlo de la barra de estado
	zoomActual = driverGovocitos->getModeloGovocitos()->getSistemaDibujado()->getZoom();
	bEstado->setNivelZoom(zoomActual);
}

/**
 Disminuye el zoom de la imagen.
 */
void InterfazGovocitos::disminuyeZoom()
{
	int zoomActual;
	
	if(driverGovocitos->disminuyeZoom())
	{
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomOut");
	}

	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomIn", true);
	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoom100", true);

	//Actualizamos el varlo de la barra de estado
	zoomActual = driverGovocitos->getModeloGovocitos()->getSistemaDibujado()->getZoom();
	bEstado->setNivelZoom(zoomActual);
}

/**
 Establece el zoom de la imagen al tamaño original.
 */
void InterfazGovocitos::originalZoom()
{
	driverGovocitos->zoomOriginal();

	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomOut", true);
	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomIn");
	menBarPrincipal->setSensitiveOpcMenu("SubMenuZoom100");

	//Actualizamos el varlo de la barra de estado
	bEstado->setNivelZoom(10);
}

/**
 Establece el zoom de la imagen al tamaño de la ventana.
 */
void InterfazGovocitos::ventanaZoom()
{
	float zoomActual;
	
	zoomActual = driverGovocitos->zoomVentana(panelDatos.get_child1());

	//Actualizamos el valor del zoom en la barra de estado
	bEstado->setNivelZoom(zoomActual);
		
	if (zoomActual > 1)
	{
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomIn", true);
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoom100", true);
	}
		
	if (zoomActual < 10)
	{
		menBarPrincipal->setSensitiveOpcMenu("SubMenuZoomOut", true);
	}
}

/**
 */
/*void InterfazGovocitos::recortaOvocito()
{

}*/

/**
 Lanza la deteccion automatica de bordes.
 */
void InterfazGovocitos::deteccionAutomactica()
{
	//Desactivamos la rejilla
	panelProp->setActivaRejilla(false);
	panelProp->setActivaBordeRej(false);
	panelProp->setActiveRejillaDefec(true);
	menBarPrincipal->setSensitiveOpcMenu("SubCalcularEstadist");
	panelDibujo->setVerRejilla(false);

	panelProp->hide();
	
	//Desabilidamos las opciones de rejilla y editor
	menBarPrincipal->setSensitiveOpcMenu("SubMenuEditor");
	menBarPrincipal->setSensitiveOpcMenu("SubMenuRejilla");
	menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion");
	
	driverGovocitos->deteccionBordesImagen();
	
	panelDibujo->actualizarVista();

	//Se han realizado cambios
	cambios = true;
}

/**
 Finaliza la deteccion no supervisada de bordes.
 */
void InterfazGovocitos::finalDetecNoSupervisada()
{
	/******************************************************************/
	//Guardar XML2
	
	driverGovocitos->guardarXMLIntermedios("-XML2");
	/******************************************************************/
	
	//Lanzamos el sistema supervisado
	string texto = "You need to markup all the cells that you like to detect. When you finish push key F7 to release";
	string titulo = "Oocyte edge detection";
	Dialogos::dialogoAdvertencia(texto, titulo);
		
	panelDibujo->setActivaDetecSupervis(true);

	panelProp->cierraPaneLateral();
}

/**
 Finaliza la deteccion automatica de bordes.
 */
void InterfazGovocitos::finalizarDeteccionaAutomactica()
{
	panelProp->setSensitiveAnhadirCelManoAL(false);
	panelProp->setSensitiveAnhadirCelPT(false);
	
	//Habilitamos el menu de deteccion automatica
	menBarPrincipal->setSensitiveOpcMenu("SubMenuClasificacion", true);
	//Habilidamos las opciones de rejilla y editor
	menBarPrincipal->setSensitiveOpcMenu("SubMenuEditor", true);
	menBarPrincipal->setSensitiveOpcMenu("SubMenuRejilla", true);
}

/**
 Lanza la clasificacion automatica de ovocitos.
 */
void InterfazGovocitos::clasificacionAutomactica()
{
	driverGovocitos->clasificacionEstClAutomatica();
	
	panelDibujo->actualizarVista();

	//Se han realizado cambios
	cambios = true;

	panelProp->setPagBlocNotas(0);
}

/**
 Activa el panel auxiliar de datos
 */
void InterfazGovocitos::activaPanelAuxiliarDatos(int panel)
{
	ConfigGovocitos *configuracion;

	configuracion = driverGovocitos->getModeloGovocitos()->getConfiguracion();

	destruyeDatos();

	if(((panel == 1) || (panel == 2)) && !datosD)
	{
		double calibracion;
		
		//Creamos el objeto de calculo de los diametros
		datosD = new PanelDiametros(*panelDibujo, *bEstado, *configuracion->getDatosClases(),
		                            *configuracion->getDatosEstados());

		calibracion = driverGovocitos->getModeloGovocitos()->getImageActual()->getCalibracionImg();

		if(calibracion != 1)
		{
			datosD->setCalibracion(true);
		}
	}
	
	switch(panel)
	{
		case 1:
		{
			driverGovocitos->calculoDiametros();

			datosD->calculoDiametro();
			datosD->signal_cierra_diametros().connect(sigc::mem_fun(*this, &InterfazGovocitos::destruyeDatos));

			break;
		}
		case 2:
		{	
			driverGovocitos->calculoDiametros();
			
			panelDatos.pack2(*datosD, false, false);
			
			if(datosD->calculoDiametrosClass())
			{
				//Conectamos las celulas con el panel
				panelDibujo->signal_selecciona_celula().connect(sigc::mem_fun(datosD, &PanelDiametros::selectFilaTreeDiam));
				datosD->signal_cierra_diametros().connect(sigc::mem_fun(*this, &InterfazGovocitos::destruyeDatos));

				panelProp->setSentiviePrintData(true);
			}
			
			break;
		}
		case 3:
		{
			SistemaDibujado *sistemDibujo = driverGovocitos->getModeloGovocitos()->getSistemaDibujado();
			Rejilla *rejilla = driverGovocitos->getModeloGovocitos()->getRejilla();
			
			//Creamos el objeto de calculo de los datos estadisticos
			datosE = new PanelDatosEstadisticos(*sistemDibujo, *panelDibujo, *rejilla, *bEstado, 
			                                    *configuracion->getDatosEstados());

			driverGovocitos->calculoDatosEstadisticos();
			
			panelDatos.pack2(*datosE, false, false);

			if(datosE->calculoEstadistico())
			{
				//Conectamos las celulas con el panel
				panelDibujo->signal_selecciona_celula().connect(sigc::mem_fun(datosE, &PanelDatosEstadisticos::selectFilaTreeEst));
				datosE->signal_cierra_estadisticos().connect(sigc::mem_fun(*this, &InterfazGovocitos::destruyeDatos));

				panelProp->setSensitivePrinData1(true);
			}
			
			break;
		}
	}	
}

/**
 Selecciona todas las células disponibles en la imagen.
 */
void InterfazGovocitos::seleccionaTodasCelulas()
{
	panelDibujo->selecAllCell();
}

/**
 Exporta los datos morfologicos de una celula a un formato csv.
 */
void InterfazGovocitos::exportCsvDatosCell()
{
	ofstream fsalida;
	string ruta;
	string defaultPath;

	defaultPath = driverGovocitos->getModeloGovocitos()->getConfiguracion()->getDatosPreferencias()->getArchivCSV();

	//Lanzamos el dialogo de guardar como para obtener la ruta
	if(Dialogos::dialogoExportarCsv(ruta,defaultPath))
	{
		//Abrimos y Escribimos datos en el fichero
		fsalida.open(ruta.c_str(), ios::out);

		//Obtenemos los datos
		datosD->writeDataDiameter(fsalida);

		//Cerramos el fichero
		fsalida.close();
	}
}

/**
 */
void InterfazGovocitos::exportCsvStadisticalData()
{
	ofstream fsalida;
	string ruta;
	string defaultPath;

	defaultPath = driverGovocitos->getModeloGovocitos()->getConfiguracion()->getDatosPreferencias()->getArchivCSV();
	
	//Lanzamos el dialogo de guardar como para obtener la ruta
	if(Dialogos::dialogoExportarCsv(ruta, defaultPath))
	{
		//Abrimos y Escribimos datos en el fichero
		fsalida.open(ruta.c_str(), ios::out);

		//Obtenemos los datos
		datosE->writeDataStadistical(fsalida);

		//Cerramos el fichero
		fsalida.close();
	}
}

/**
 Exporta los datos obtendios del calculo de fecundidad a un formato csv.
 */
void InterfazGovocitos::exporFecundidadCSV()
{
	ofstream fsalida;
	string ruta;
	string defaultPath;

	defaultPath = driverGovocitos->getModeloGovocitos()->getConfiguracion()->getDatosPreferencias()->getArchivCSV();
	
	//Lanzamos el dialogo de guardar como para obtener la ruta
	if(Dialogos::dialogoExportarCsv(ruta, defaultPath))
	{
		//Abrimos y Escribimos datos en el fichero
		fsalida.open(ruta.c_str(), ios::out);

		//Obtenemos los datos
		panelFec->writeDataDiameter(fsalida);

		//Cerramos el fichero
		fsalida.close();
	}
}

/**
 Exporta los datos de fecundidad calcualdos a la base de datos.
 */
void InterfazGovocitos::exporFecundidadBD()
{
	string titulo, mensaje;

	titulo = "Save Fecundity BD";
	
	if(driverGovocitos->guardarFecundidadBD())
	{
		mensaje = "The actual data fecundity of the individual was saved at DB.";
	}
	else
	{
		mensaje = "The actual data fecundity of the individual was not saved at DB.";
	}

	Dialogos::dialogoAdvertencia(mensaje, titulo);
}

/**
 Exporta los datos de la rejilla a la BD.
 */
void InterfazGovocitos::exporRejillaBD()
{
	driverGovocitos->guardarRejillaBD();
}

/**
 Detecta si se ha pulsado una tecla
 */
bool InterfazGovocitos::multiSelecPressRelease(GdkEventKey *event)
{
	if(event->type == GDK_KEY_PRESS && event->keyval == GDK_F7)
	{
		if(panelDibujo->getActivaDetecSupervis())
		{
			panelDibujo->setActivaDetecSupervis(false);

			//Lanzamos la deteccion de bordes supervisada
			driverGovocitos->deteccionBordesSupervised();

			panelDibujo->actualizarVista();

			finalizarDeteccionaAutomactica();
		}

		return true;
	}
	
	if(panelDibujo->getSurfaceCelulas())
	{
		if(event->type == GDK_KEY_PRESS && !panelDibujo->getCapaCelula()->getSelecMultiple())
		{
			if(panelProp->getSelecCel())
			{
				if(event->keyval == GDK_Control_L)
				{
					panelDibujo->getCapaCelula()->setSelecMultiple(true);
				}
				else if(event->keyval == GDK_Delete)
				{
					panelDibujo->eliminaCelula();
				}
			}
		}
		else if(event->type == GDK_KEY_RELEASE && event->keyval == GDK_Control_L)
		{
			panelDibujo->getCapaCelula()->setSelecMultiple(false);
		}
		
		return true;
	}
	
	return false;
}

/**
 Detecta si se han realizado cambios en un fichero xml en caso afirmativo abre un
 dialogo que pregunta si se quiere abrir el dialogo de guardar como.
 */
void InterfazGovocitos::dialogoCambios()
{
	if(cambios)
	{
		//string texto = "¿Desea guardar los cambios efectuados?";
		string texto = "Save changes?";
		string titulo = "Govocitos";
		
		if(Dialogos::dialogoConfirmacion(texto, titulo))
		{
			menuGuardarComo();
		}
		
		cambios = false;
	}
}

//Dialogo que se muestra en caso de que no haya definida ninguna clase o estado
void InterfazGovocitos::mensajeSinClasesEstados()
{
	ConfigGovocitos *datosClEst;

	datosClEst = driverGovocitos->getModeloGovocitos()->getConfiguracion();
	
	//Comprobamos si no hay introducidas clases
	if(!datosClEst->getDatosClases()->size())
	{
		string mensaje, titulo;

		//mensaje = "No hay ninguna clase definida";
		mensaje = "No class defined";
		titulo = "Govocitos";
		
		Dialogos::dialogoAdvertencia(mensaje, titulo);
	}

	//Comprobamos si no hay introducidos estados
	if(!datosClEst->getDatosEstados()->size())
	{
		string mensaje, titulo;

		//mensaje = "No hay ningun estado definido";
		mensaje = "No state defined";
		titulo = "Govocitos";
		
		Dialogos::dialogoAdvertencia(mensaje, titulo);
	}
}

/**
 Devuelve el objeto del panel de dibujado.
 @return PanelDibujado, puntero del panel de dibujado.
 */
PanelDibujado *InterfazGovocitos::getPanelDibujado()
{
	return panelDibujo;
}

/**
 Devuelve el objeto de la barra de estado.
 @return BarraEstado, puntero de la barra de estado.
 */
BarraEstado *InterfazGovocitos::getBarraEstado()
{
	return bEstado;
}

/**
 Devuelve el objeto del panel de propiedades.
 @return PanelPropiedades, puntero del panel de propiedades.
 */
PanelPropiedades *InterfazGovocitos::getPanelPropiedades()
{
	return panelProp;
}

/**
 Devuelve el objeto de la barra y el menu principal.
 @return MenuBarraPrincipal, puntero del menu y la barra principal.
 */
MenuBarraPrincipal *InterfazGovocitos::getMenuBarraPrincipal()
{
	return menBarPrincipal;
}

/**
 Devuelve el objeto del panel de diametros.
 @return PanelDiametros, puntero del panel de diametros.
 */
PanelDiametros *InterfazGovocitos::getPanelDiametros()
{
	return datosD;
}

/**
 Devuelve el objeto del panel de datos estadisticos.
 @return PanelDatosEstadisticos, puntero del panel de datos estadisticos.
 */
PanelDatosEstadisticos *InterfazGovocitos::getPanelEstadisticos()
{
	return datosE;
}

/**
 Devuelve el objeto del panel fecundidad.
 @return PanelFecundidad, puntero del panel de fecundidad.
 */
PanelFecundidad *InterfazGovocitos::getPanelFecundidad()
{
	return panelFec;
}

/**
 Devuelve el valor del atributo cambios.
 @return bool, devuelve true si se realizaron cambios en la imagen y false en caso
 contrario.
 */
bool InterfazGovocitos::getCambios()
{
	return cambios;
}

/**
 Establece el valor del atributo cambios.
 @param c, bool que contiene el valor del atributo cambios.
 */
void InterfazGovocitos::setCambios(bool c)
{
	cambios = c;
}
