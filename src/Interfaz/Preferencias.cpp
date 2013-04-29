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

#include "Preferencias.h"

/**
 Constructor.
 @param opc, OpcionesPref.
 @param cc, vector<ClaseCeula>.
 @param ce, vector<EstadoCeula>.
 @param rej, vector<OpcionesRej>.
 */
Preferencias::Preferencias(OpcionesPref opc, vector<ClaseCelula> cc, vector<EstadoCelula> ce, vector<OpcionesRej> rej)
{
	initDialogoPreferencias();
	iniciadorPreferencias();

	//dialogoPref->set_title("Preferencias");
	dialogoPref->set_title("Preferences");
	dialogoPref->set_icon_from_file(Utiles::getIconoFile("preferencias.png"));
	indiceClassEstado = -1;
	
	modificacion = false;	
	
	//Cargamos los datos pasados por referencia
	copiaPreferencias = opc;
	copiaClaseCelula = cc;
	copiaEstadoCelula = ce;
	copiaOpcRej = rej;
		
	//Carga opciones generales
	cargaDatosGenerales();
	
	//Inicia las Etiquetas y las clases
	iniciadorClassEstado();
	
	//Inicia las rejillas personalizadas
	iniciadorRejilla();

	//Señales
	treeviewGeneral->signal_cursor_changed().connect(sigc::mem_fun(*this, &Preferencias::selecPref));
	botonCerrar->signal_clicked().connect(sigc::mem_fun
										  (*this, &Preferencias::pulsarBotonCerrar));
	botonAceptar->signal_clicked().connect(sigc::mem_fun
										  (*this, &Preferencias::pulsarBotonAceptar));
	botonRevertir->signal_clicked().connect(sigc::mem_fun
											(*this, &Preferencias::pulsarBotonRevertir));
	selecImagG->signal_current_folder_changed().connect(sigc::mem_fun
										 (*this, &Preferencias::asignarRutaImag));
	selecCelG->signal_current_folder_changed().connect(sigc::mem_fun
										 (*this, &Preferencias::asignarRutaCel));
	selecCSVG->signal_current_folder_changed().connect(sigc::mem_fun
										 (*this, &Preferencias::asignarRutaCSV));
	treeviewClasesG->signal_cursor_changed().connect(sigc::mem_fun
													  (*this, &Preferencias::seleccionaClase));
	treeviewEstadosG->signal_cursor_changed().connect(sigc::mem_fun
													(*this, &Preferencias::seleccionaEstado));
	blocNotas->signal_switch_page().connect(sigc::mem_fun
											(*this, &Preferencias::borraDatosForm));
	guardarRejG->signal_clicked().connect(sigc::mem_fun
											 (*this, &Preferencias::guardarRejilla));
	colorEstadosG->signal_color_set().connect(sigc::mem_fun
	                                          (*this, &Preferencias::cambiaColEstado));
	claseLinea->signal_changed().connect(sigc::mem_fun
	                                      (*this, &Preferencias::cambiaLineaClass));
	addClase->signal_clicked().connect(sigc::bind(sigc::mem_fun
										  (*this, &Preferencias::addClaseDispUso), true));
	removeClase->signal_clicked().connect(sigc::bind(sigc::mem_fun
										  (*this, &Preferencias::addClaseDispUso), false));
	addEstado->signal_clicked().connect(sigc::bind(sigc::mem_fun
										  (*this, &Preferencias::addEstDispUso), true));
	removeEstado->signal_clicked().connect(sigc::bind(sigc::mem_fun
										  (*this, &Preferencias::addEstDispUso), false));
	clDisp->signal_cursor_changed().connect(sigc::bind(sigc::mem_fun
	                                      (*this, &Preferencias::selecUsoDispClEst), 1));
	clUso->signal_cursor_changed().connect(sigc::bind(sigc::mem_fun
	                                      (*this, &Preferencias::selecUsoDispClEst), 2));
	estDisp->signal_cursor_changed().connect(sigc::bind(sigc::mem_fun
										  (*this, &Preferencias::selecUsoDispClEst), 3));
	estUso->signal_cursor_changed().connect(sigc::bind(sigc::mem_fun
	                                      (*this, &Preferencias::selecUsoDispClEst), 4));

}

/**
 Destructor.
 */
Preferencias::~Preferencias()
{
	
}

/**
 Inicia las opcions basicas del menu de preferencias.
 */
void Preferencias::iniciadorPreferencias()
{
	treeviewGeneral->set_headers_visible(false);
	refTreeModelDialog = Gtk::TreeStore::create(columModel);
	treeviewGeneral->set_model(refTreeModelDialog);
	
	Gtk::TreeModel::Row row;
	Gtk::TreeModel::Row childrow;
	
	row = *(refTreeModelDialog->append());
	//row[columModel.nomCol] = "Clasificaciones";
	row[columModel.nomCol] = "Classifications";
	childrow = *(refTreeModelDialog->append(row.children()));
	//childrow[columModel.nomCol] = "Clases";
	childrow[columModel.nomCol] = "Classes";
	childrow = *(refTreeModelDialog->append(row.children()));
	//childrow[columModel.nomCol] = "Estados";
	childrow[columModel.nomCol] = "States";
	row = *(refTreeModelDialog->append());
	
	//row[columModel.nomCol] = "Directorios";
	row[columModel.nomCol] = "Folders";
	row = *(refTreeModelDialog->append());
	
	row[columModel.nomCol] = "Editor";
	row = *(refTreeModelDialog->append());
	
	//row[columModel.nomCol] = "Rejilla";
	row[columModel.nomCol] = "Grid";
	childrow = *(refTreeModelDialog->append(row.children()));
	//childrow[columModel.nomCol] = "Rejilla Completa";
	childrow[columModel.nomCol] = "Complete grid";
	childrow = *(refTreeModelDialog->append(row.children()));
	//childrow[columModel.nomCol] = "Rejilla Personalizada";
	childrow[columModel.nomCol] = "Custom grid";
	row = *(refTreeModelDialog->append());
	
	//row[columModel.nomCol] = "Base de Datos";
	row[columModel.nomCol] = "Database";
	row = *(refTreeModelDialog->append());

	row[columModel.nomCol] = "Secure FTP";
	row = *(refTreeModelDialog->append());
	
	//row[columModel.nomCol] = "Cache de imagenes";
	row[columModel.nomCol] = "Image cache";
	row = *(refTreeModelDialog->append());
	
	treeviewGeneral->append_column("",columModel.nomCol);
}

/**
 sistema de seleccion de las distintias opciones del menu preferencias.
 */
void Preferencias::selecPref()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada = treeviewGeneral->get_selection();
	Gtk::TreeModel::iterator it;
	
	iterG = it;
	
	iterG = filaSeleccionada->get_selected();
	
	if(iterG)
	{
		string nombreR;
		
		Gtk::TreeModel::Row row = *iterG;

		nombreR = row[columModel.nomCol];
			
		//if(nombreR == "Clasificaciones")
		if(nombreR == "Classifications")
		{
			blocNotas->set_current_page(0);
			//labelTitulo->set_label("Clases y Estados");
			labelTitulo->set_label("Classes and States");
		}
		//else if(nombreR == "Clases")
		else if(nombreR == "Classes")
		{
			blocNotas->set_current_page(1);
			//labelTitulo->set_label("Clases");
			labelTitulo->set_label("Classes");
		}
		//else if(nombreR == "Estados")
		else if(nombreR == "States")
		{
			blocNotas->set_current_page(2);
			//labelTitulo->set_label("Estados");
			labelTitulo->set_label("States");
		}
		//else if(nombreR == "Directorios")
		else if(nombreR == "Folders")
		{
			blocNotas->set_current_page(3);
			//labelTitulo->set_label("Directorios");
			labelTitulo->set_label("Folders");
		}
		else if(nombreR == "Editor")
		{
			blocNotas->set_current_page(4);			
			labelTitulo->set_label("Editor");
		}
		//else if(nombreR == "Rejilla")
		else if(nombreR == "Grid")
		{
			blocNotas->set_current_page(5);				
			//labelTitulo->set_label("Rejilla");
			labelTitulo->set_label("Grid");
		}
		//else if(nombreR == "Rejilla Completa")
		else if(nombreR == "Complete grid")
		{
			blocNotas->set_current_page(6);
			//labelTitulo->set_label("Rejilla Completa");
			labelTitulo->set_label("Complete grid");
		}
		//else if(nombreR == "Rejilla Personalizada")
		else if(nombreR == "Custom grid")
		{
			blocNotas->set_current_page(7);
			//labelTitulo->set_label("Rejilla Personalizada");
			labelTitulo->set_label("Custom grid");
		}
		//else if(nombreR == "Base de Datos")
		else if(nombreR == "Database")
		{
			blocNotas->set_current_page(8);	
			//labelTitulo->set_label("Base de Datos");
			labelTitulo->set_label("Database");
		}
		else if(nombreR == "Secure FTP")
		{
			blocNotas->set_current_page(10);	
			//labelTitulo->set_label("Base de Datos");
			labelTitulo->set_label("Secure FTP");
		}
		//else if(nombreR == "Cache de imagenes")
		else if(nombreR == "Image cache")
		{
			blocNotas->set_current_page(9);				
			//labelTitulo->set_label("Cache de Imagenes");
			labelTitulo->set_label("Image cache");
		}
	}
}

/**
 Inicializa el diálogo de preferencias.
 */
void Preferencias::initDialogoPreferencias()
{
	Utiles::getWidgetGlade(Utiles::getGladeFile("Preferencias.glade"), "dialogoPref",
	               "dialogoPref", &dialogoPref,
	               "labelTitulo", &labelTitulo,
	               "treeviewGeneral", &treeviewGeneral,
	               "blocNotas", &blocNotas,
				   "clasesG", &clasesG,
				   "nomClasesG", &nomClasesG,
				   "descripClasesG", &descripClasesG,
				   "treeviewClasesG", &treeviewClasesG,
				   "estadosG", &estadosG,
				   "nomEstadosG", &nomEstadosG,
				   "descripEstadosG", &descripEstadosG,
				   "treeviewEstadosG", &treeviewEstadosG,
				   "colorEstadosG", &colorEstadosG,	  
	               "claseLinea", &claseLinea,
				   "celSDetG", &celSDetG,
				   "seleCelG", &seleCelG,
				   "ediCelG", &ediCelG,
				   "grosLineaG", &grosLineaG, 
				   "grosPuntoG", &grosPuntoG,
				   "archivImagG", &archivImagG,
				   "archivCelG", &archivCelG,
				   "selecImagG", &selecImagG,
				   "selecCelG", &selecCelG,
				   "limDIG", &limDIG,
				   "limISG", &limISG,
				   "colRejG", &colRejG,
				   "grosRejG", &grosRejG,
				   "separPuntosG", &separPuntosG,
				   "botonCerrar", &botonCerrar,
				   "botonAceptar", &botonAceptar,
				   "separPuntosGPD", &separPuntosGPD,
				   "numColumnsG",&numColumnsG,
				   "numFilasG", &numFilasG,
				   "guardarRejG", &guardarRejG,
				   "treeviewRejG", &treeviewRejG,
	             //  "bordeRejComp", &bordeRejComp,
				   "grosBordeRejG", &grosBordeRejG,
				   "botonRevertir", &botonRevertir,
	               "loginBDG", &loginBDG,
	               "passBDG", &passBDG,
	               "rutaBDG", &rutaBDG,
	               "databaseBDG", &databaseBDG,
	               "cacheImagenesG", &cacheImagenesG,
	               "tamCacheG", &tamCacheG,
	               "clDisp", &clDisp,
	               "clUso", & clUso,
	               "estDisp", &estDisp,
	               "estUso", &estUso,
	               "addClase", &addClase,
	               "removeClase", &removeClase,
	               "addEstado", &addEstado,
	               "removeEstado", &removeEstado,
	               "rutaSFTP", &rutaSFTP,
	               "loginSFTP", &loginSFTP,
	               "passSFTP", &passSFTP,
	               "pathSFTP", &pathSFTP,
	               "archivCSVG", &archivCSVG,
	               "selecCSVG", &selecCSVG,
				   NULL);
}

/**
 Abre el dialogo de preferencias.
 */
void Preferencias::mostrarDialogoP()
{
	dialogoPref->run();
}

/**
 Muestra los datos en el panel y los carga.
 */
void Preferencias::cargaDatosGenerales()
{		
	celSDet.set_rgb(copiaPreferencias.getCelSDetR(),copiaPreferencias.getCelSDetG(),
					copiaPreferencias.getCelSDetB());
	seleCel.set_rgb(copiaPreferencias.getSeleCelR(),copiaPreferencias.getSeleCelG(),
					copiaPreferencias.getSeleCelB());
	ediCel.set_rgb(copiaPreferencias.getEdiCelR(),copiaPreferencias.getEdiCelG(),
				   copiaPreferencias.getEdiCelB());
	limDI.set_rgb(copiaPreferencias.getLimDIR(),copiaPreferencias.getLimDIG(),
				  copiaPreferencias.getLimDIB());
	limIS.set_rgb(copiaPreferencias.getLimISR(),copiaPreferencias.getLimISG(),
				  copiaPreferencias.getLimISB());
	colRej.set_rgb(copiaPreferencias.getColRejR(),copiaPreferencias.getColRejG(),
				   copiaPreferencias.getColRejB());

	//Cargamos los datos en el panel
	//Editor
	celSDetG->set_color(celSDet);
	seleCelG->set_color(seleCel);
	ediCelG->set_color(ediCel);
	grosLineaG->set_value(copiaPreferencias.getGrosLinea());
	grosPuntoG->set_value(copiaPreferencias.getGrosPunto());
	
	//Directorios
	archivImagG->set_text(copiaPreferencias.getArchivImag());
	archivCelG->set_text(copiaPreferencias.getArchivCel());
	archivCSVG->set_text(copiaPreferencias.getArchivCSV());
	
	//Rejilla
	limDIG->set_color(limDI);
	limISG->set_color(limIS);
	colRejG->set_color(colRej);
	grosRejG->set_value(copiaPreferencias.getGrosRej());
	separPuntosG->set_value(copiaPreferencias.getSeparPuntos());
	grosBordeRejG->set_value(copiaPreferencias.getGrosBordeRej());
	//bordeRejComp->set_active(copiaPreferencias.getBordeComp());

	//Base de datos
	loginBDG->set_text(copiaPreferencias.getLoginBD());
	passBDG->set_text(copiaPreferencias.getPassBD());
	rutaBDG->set_text(copiaPreferencias.getDirecBD());
	databaseBDG->set_text(copiaPreferencias.getDataBaseBD());

	//Secure ftp
	rutaSFTP->set_text(copiaPreferencias.getDirecSFTP());
	loginSFTP->set_text(copiaPreferencias.getLoginSFTP());
	passSFTP->set_text(copiaPreferencias.getPassSFTP());
	pathSFTP->set_text(copiaPreferencias.getPathSFTP());

	//Cache de imagenes
	cacheImagenesG->set_text(Utiles::direccionCache(""));
	tamCacheG->set_value(copiaPreferencias.getTamCache());
}

/**
 Devuelve el objeto OpcionesPref.
 @return OpcionesPref.
 */
OpcionesPref Preferencias::getOpcionesPref()
{
	return copiaPreferencias;
}

/**
 Devuelve el vector clases.
 @return vector<ClaseCelula>.
 */
vector<ClaseCelula> Preferencias::getClasesCelula()
{
	return copiaClaseCelula;
}

/**
 Devuelve el vector estados.
 @return vector<EstadoCelula>.
 */
vector<EstadoCelula> Preferencias::getEstadosCelula()
{
	return copiaEstadoCelula;
}

/**
 Devuelve el vector con las rejilla.
 @return vector<OpcionesRej>.
 */
vector<OpcionesRej> Preferencias::getOpcionesRej()
{
	return copiaOpcRej;
}

/**
 Devuelve verdadero si se produjo una modificacion y falso en caso contrario.
 @return bool.
 */
bool Preferencias::getModifi()
{
	return modificacion;
}

/**
 Se establece el valor de la variable modificacion.
 @param cond, bool.
 */
void Preferencias::setModifi(bool cond)
{
	modificacion = cond;
}

/**
 Guarda los cambios realizados y cierra el panel de preferencias con las nuevas 
 preferencias.
 */
void Preferencias::pulsarBotonAceptar()
{
	//Directorios
	copiaPreferencias.setArchivImag(archivImagG->get_text());
	copiaPreferencias.setArchivCel(archivCelG->get_text());
	copiaPreferencias.setArchivCSV(archivCSVG->get_text());
	
	//Cache imagenes
	copiaPreferencias.setTamCache(tamCacheG->get_value());
	
	//Editor
	copiaPreferencias.setCelSDet(celSDetG->get_color());	
	copiaPreferencias.setSeleCel(seleCelG->get_color());	
	copiaPreferencias.setEdiCel(ediCelG->get_color());
	copiaPreferencias.setGrosLinea(grosLineaG->get_value());
	copiaPreferencias.setGrosPunto(grosPuntoG->get_value());
	
	//Rejilla
	copiaPreferencias.setLimDI(limDIG->get_color());
	copiaPreferencias.setLimIS(limISG->get_color());
	copiaPreferencias.setColRej(colRejG->get_color());
	copiaPreferencias.setGrosRej(grosRejG->get_value());
	copiaPreferencias.setSeparPuntos(separPuntosG->get_value());
	copiaPreferencias.setGrosBordeRej(grosBordeRejG->get_value());
	//copiaPreferencias.setBordeComp(bordeRejComp->get_active());

	//Base de datos
	copiaPreferencias.setLoginBD(loginBDG->get_text());
	copiaPreferencias.setPassBD(passBDG->get_text());
	copiaPreferencias.setDirecBD(rutaBDG->get_text());
	copiaPreferencias.setDataBaseBD(databaseBDG->get_text());

	//Secure ftp
	copiaPreferencias.setDirecSFTP(rutaSFTP->get_text());
	copiaPreferencias.setLoginSFTP(loginSFTP->get_text());
	copiaPreferencias.setPassSFTP(passSFTP->get_text());
	copiaPreferencias.setPathSFTP(pathSFTP->get_text());
	
	//Se han realizado modificaciones
	modificacion = true;
	//Cerramos el dialogo de preferencias
	dialogoPref->hide();
}

/**
 Cierra el panel de prefencias y guarda los datos en el fichero de configuracion.
 */
void Preferencias::pulsarBotonCerrar()
{	
	dialogoPref->hide();
}

/**
 Carga los valores por defector de las pestañas rejilla, editor y variables.
 */
void Preferencias::pulsarBotonRevertir()
{
	//string mensaje = "Se van restaurar los valores por defecto del Editor, Rejilla y Variables, ¿Quiere proceder?";
	string mensaje = "Default values of Editor, Grid and Variables are going to be restores. Do you want to continue?";
	//string titulo = "Restaurar preferencias";
	string titulo = "Restore preferences";
	//Cargamos los datos por defecto
	copiaPreferencias.revertirDatos();
	
	if(Dialogos::dialogoConfirmacion(mensaje, titulo))
	{
		cargaDatosGenerales();
	
		modificacion = true;
	}
}

/**
 Asigna la ruta de las imagenes.
 */
void Preferencias::asignarRutaImag()
{	
	archivImagG->set_text(selecImagG->get_filename());
}

/**
 Asigna la ruta de los archivos de celulas.
 */
void Preferencias::asignarRutaCel()
{	
	archivCelG->set_text(selecCelG->get_filename());
}

/**
 */
void Preferencias::asignarRutaCSV()
{
	archivCSVG->set_text(selecCSVG->get_filename());
}

/**
 Detecta un cambio de color y guarda los cambios.
 */
void Preferencias::cambiaColEstado()
{
	if(iter)
	{
		copiaEstadoCelula[indiceClassEstado].setColorEstado(colorEstadosG->get_color());

		indiceClassEstado = -1;
	}
}

/**
 Cambia la linea de seleccion de las preferencias.
 */
void Preferencias::cambiaLineaClass()
{
	if(iter)
	{
		if(indiceClassEstado >= 0)
		{
			copiaClaseCelula[indiceClassEstado].setLinea(claseLinea->get_active_row_number());
		}
	}
}

/**
 Funcion que intercambia los clases del treeview de Clases en uso al de clases
 disponibles y viceversa.
 @param opc Si el valor es verdadero añadimos al clases en uso, si es falso añadimos
 a clases disponibles.
 */
void Preferencias::addClaseDispUso(bool opc)
{
	string labelClEst;
	Gtk::TreeModel::iterator it;
	int numClEst;
	int i;

	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		numClEst = copiaClaseCelula.size();
		i = 0;

		labelClEst = row[columModel.nomCol];

		while( i < numClEst && labelClEst != copiaClaseCelula[i].getEtiquetaClasificacion())
		{
			i++;
		}
	
		if(labelClEst == copiaClaseCelula[i].getEtiquetaClasificacion())
		{
			copiaClaseCelula[i].setEnUso(opc);
			
			if(opc)
			{
				refTreeModelClDisp->erase(iter);
				
				row = *(refTreeModelClUso->append());
				row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();

				addClase->set_sensitive(false);

				row = *(refTreeModelEtiq->append());
				row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();
			}
			else
			{
				int numCopClaseEst;
				Gtk::TreeModel::Row row;
				
				refTreeModelClUso->erase(iter);
				
				row = *(refTreeModelClDisp->append());
				row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();

				removeClase->set_sensitive(false);
				
				refTreeModelEtiq->clear();

				numCopClaseEst = copiaClaseCelula.size();

				//Clases
				treeviewClasesG->set_headers_visible(false);
				refTreeModelEtiq = Gtk::ListStore::create(columModel);
				treeviewClasesG->set_model(refTreeModelEtiq);
	
				for(int i = 0; i < numCopClaseEst; i++)
				{
					if(copiaClaseCelula[i].getEnUso())
					{		
						//Informacion clase
						row = *(refTreeModelEtiq->append());
						row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();
					}

				}
			}
		}
		iter = it;
	}
}

/**
 Funcion que intercambia los estados del treeview de Estados en uso al de estados
 disponibles y viceversa.
 @param opc Si el valor es verdadero añadimos al estados en uso, si es falso añadimos
 a estados disponibles.
 */
void Preferencias::addEstDispUso(bool opc)
{
	string labelClEst;
	Gtk::TreeModel::iterator it;
	int numClEst;
	int i;

	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		numClEst = copiaEstadoCelula.size();
		i = 0;

		labelClEst = row[columModel.nomCol];

		while( i < numClEst && labelClEst != copiaEstadoCelula[i].getEtiquetaClasificacion())
		{
			i++;
		}
	
		if(labelClEst == copiaEstadoCelula[i].getEtiquetaClasificacion())
		{
			copiaEstadoCelula[i].setEnUso(opc);

			if(opc)
			{	
				if(refTreeModelEstDisp->iter_is_valid(iter))
				{
					refTreeModelEstDisp->erase(iter);
				
					row = *(refTreeModelEstUso->append());
					row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();

					addEstado->set_sensitive(false);

					row = *(refTreeModelClass->append());
					row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();
				}
			}
			else
			{
				if(refTreeModelEstUso->iter_is_valid(iter))
				{
					int numCopClaseEst;
					Gtk::TreeModel::Row row;
					
					refTreeModelEstUso->erase(iter);
				
					row = *(refTreeModelEstDisp->append());
					row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();

					removeEstado->set_sensitive(false);

					numCopClaseEst = copiaEstadoCelula.size();
	
					//Estados
					treeviewEstadosG->set_headers_visible(false);
					refTreeModelClass = Gtk::ListStore::create(columModel);
					treeviewEstadosG->set_model(refTreeModelClass);

					for(int i = 0; i < numCopClaseEst; i++)
					{
						if(copiaEstadoCelula[i].getEnUso())
						{
							//Informacion estado
							row = *(refTreeModelClass->append());
							row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();
						}
					}
				}
			}
		}
		iter = it;
	}
}
			
/**
 Asigna el elemento seleccionado en un trevieww a un iterator para su posterior 
 tratamiento.
 @param opc Identifica al treeview que estamos usaron 1 ->Clases Disponibles, 2 ->
 Clases en Uso, 3 ->Estados Disponibles, 4 ->Estados en Uso.
 */
void Preferencias::selecUsoDispClEst(int opc)
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator it;
	string labelClEst;

	iter = it;

	//Segun la opcion de entrada seleccionamos el treeview
	switch(opc)
	{
		case 1:
			filaSeleccionada = clDisp->get_selection();
			addClase->set_sensitive();
			break;
		case 2:
			removeClase->set_sensitive();
			filaSeleccionada = clUso->get_selection();
			break;
		case 3:
			addEstado->set_sensitive();
			filaSeleccionada = estDisp->get_selection();
			break;
		case 4:
			removeEstado->set_sensitive();
			filaSeleccionada = estUso->get_selection();
			break;
	}

	iter = filaSeleccionada->get_selected();
}

/**
 Selecciona una de las clases disponibles.
 */
void Preferencias::seleccionaClase()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator it;
	string etiquetaClase;
	Glib::RefPtr<Gtk::TextBuffer> buf;
	Gdk::Color col;
	int i;

	iter = it;
	i = 0;

	filaSeleccionada = treeviewClasesG->get_selection();

	iter = filaSeleccionada->get_selected();
	
	if(iter)
	{
		int numCopClaseEst = copiaClaseCelula.size();
		
		Gtk::TreeModel::Row row = *iter;

		etiquetaClase = row[columModel.nomCol];

		while(i < numCopClaseEst && etiquetaClase != copiaClaseCelula[i].getEtiquetaClasificacion())
		{
			i++;
		}	

		if(etiquetaClase == copiaClaseCelula[i].getEtiquetaClasificacion())
		{
			indiceClassEstado = i;

			clasesG->set_text(copiaClaseCelula[i].getEtiquetaClasificacion());
			nomClasesG->set_text(copiaClaseCelula[i].getNombreClasificacion());
			buf = descripClasesG->get_buffer();
			buf->set_text(copiaClaseCelula[i].getDescripcionClasificacion());
			claseLinea->set_sensitive(true);
			claseLinea->set_active(copiaClaseCelula[i].getLinea());
		}
	}
}

/**
 Rellena los datos en el formulario correspondientes a la clase o el estado
 seleccionado por el usuario.
 */
void Preferencias::seleccionaEstado()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator it;
	string etiquetaClase;
	Glib::RefPtr<Gtk::TextBuffer> buf;
	Gdk::Color col;
	int i;

	iter = it;
	i = 0;
	
	filaSeleccionada = treeviewEstadosG->get_selection();
	
	iter = filaSeleccionada->get_selected();
	
	if(iter)
	{
		int numCopClaseEst = copiaEstadoCelula.size();
		
		Gtk::TreeModel::Row row = *iter;

		etiquetaClase = row[columModel.nomCol];

		while(i < numCopClaseEst && etiquetaClase != copiaEstadoCelula[i].getEtiquetaClasificacion())
		{
			i++;
		}	
			
		if(etiquetaClase == copiaEstadoCelula[i].getEtiquetaClasificacion())
		{
			col.set_rgb(copiaEstadoCelula[i].getColorEstadoR(),
									  copiaEstadoCelula[i].getColorEstadoG(),
									  copiaEstadoCelula[i].getColorEstadoB());
			indiceClassEstado = i;

			estadosG->set_text(copiaEstadoCelula[i].getEtiquetaClasificacion());
			nomEstadosG->set_text(copiaEstadoCelula[i].getNombreClasificacion());
			buf = descripEstadosG->get_buffer();
			buf->set_text(copiaEstadoCelula[i].getDescripcionClasificacion());
			colorEstadosG->set_sensitive(true);
			colorEstadosG->set_color(col);
		}
	}
}

/**
 Inicia el treeview de las etiquetas y clases y del sistema de disponibilidad de 
 clases y estados.
 */
void Preferencias::iniciadorClassEstado()
{	
	Gtk::TreeModel::Row row;

	//Clases
	treeviewClasesG->set_headers_visible(false);
	refTreeModelEtiq = Gtk::ListStore::create(columModel);
	treeviewClasesG->set_model(refTreeModelEtiq);
	
	//Sistema en uso y disp
	//disp
	clDisp->set_headers_visible(false);
	refTreeModelClDisp = Gtk::ListStore::create(columModel);
	clDisp->set_model(refTreeModelClDisp);
	//Uso
	clUso->set_headers_visible(false);
	refTreeModelClUso = Gtk::ListStore::create(columModel);
	clUso->set_model(refTreeModelClUso);
	
	//Estados
	treeviewEstadosG->set_headers_visible(false);
	refTreeModelClass = Gtk::ListStore::create(columModel);
	treeviewEstadosG->set_model(refTreeModelClass);

	//Sistema en uso y disp
	//disp
	estDisp->set_headers_visible(false);
	refTreeModelEstDisp = Gtk::ListStore::create(columModel);
	estDisp->set_model(refTreeModelEstDisp);
	//Uso
	estUso->set_headers_visible(false);
	refTreeModelEstUso = Gtk::ListStore::create(columModel);
	estUso->set_model(refTreeModelEstUso);

	int numCopClases = copiaClaseCelula.size();
	
	for(int i = 0; i < numCopClases; i ++)
	{
		if(copiaClaseCelula[i].getEnUso())
		{
			//Informacion clase
			row = *(refTreeModelEtiq->append());
			row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();
			//Treeview en uso
			row = *(refTreeModelClUso->append());
			row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();		
		}
		else
		{
			//Treeview disp
			row = *(refTreeModelClDisp->append());
			row[columModel.nomCol] = copiaClaseCelula[i].getEtiquetaClasificacion();
		}
	}

	int numCopEstados = copiaEstadoCelula.size();

	for(int i = 0; i < numCopEstados; i++)
	{
		if(copiaEstadoCelula[i].getEnUso())
		{
			//Informacion estado
			row = *(refTreeModelClass->append());
			row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();
			//Treeview uso
			row = *(refTreeModelEstUso->append());
			row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();
		}
		else
		{
			//Treeview disp
			row = *(refTreeModelEstDisp->append());
			row[columModel.nomCol] = copiaEstadoCelula[i].getEtiquetaClasificacion();
		}
	}

	treeviewClasesG->append_column("",columModel.nomCol);
	treeviewEstadosG->append_column("",columModel.nomCol);
	clDisp->append_column("",columModel.nomCol);
	clUso->append_column("",columModel.nomCol);
	estDisp->append_column("",columModel.nomCol);
	estUso->append_column("",columModel.nomCol);
}

/**
 Anhade o modifica una etiqueta o clase.
 */
void Preferencias::guardarRejilla()
{	
	if(datosCorrectorForm())
	{			
		OpcionesRej opcR;
		int idRejilla;
				
		if(copiaOpcRej.size())
		{
			idRejilla = (copiaOpcRej[copiaOpcRej.size() - 1].getID() + 1);
		}
		else
		{
			idRejilla = 1;
		}
		
		opcR.setID(idRejilla);
		opcR.setSeparaPuntos(separPuntosGPD->get_value());
			
		int numP = (numFilasG->get_value() * numColumnsG->get_value());
				
		opcR.setNumPuntos(numP);
		opcR.setNumFilas(numFilasG->get_value());
		opcR.setNumColumnas(numColumnsG->get_value());

		Gtk::TreeModel::Row row = *(refTreeModelRej->append());

		row[columModelRej.idCol] = idRejilla;
		row[columModelRej.nCol] = numColumnsG->get_value();
		row[columModelRej.nFil] = numFilasG->get_value();
		row[columModelRej.separP] = separPuntosGPD->get_value();
		row[columModelRej.numP] = numP;
		
		copiaOpcRej.push_back(opcR);
	}
}

/**
 Activa la reordenación de las columnas del treeView de las rejillas personalizadas.
 */
void Preferencias::reordenarPorColumnas()
{
	Gtk::TreeView::Column* pColumn1 = treeviewRejG->get_column(0);
	Gtk::TreeView::Column* pColumn2 = treeviewRejG->get_column(1);
	Gtk::TreeView::Column* pColumn3 = treeviewRejG->get_column(2);
	Gtk::TreeView::Column* pColumn4 = treeviewRejG->get_column(3);
	Gtk::TreeView::Column* pColumn5 = treeviewRejG->get_column(4);
	
	if(pColumn1)
	{
		pColumn1->set_sort_column(columModelRej.idCol);
	}
	if(pColumn2)
	{
		pColumn2->set_sort_column(columModelRej.nCol);
	}
	if(pColumn3)
	{
		pColumn3->set_sort_column(columModelRej.nFil);
	}
	if(pColumn4)
	{
		pColumn4->set_sort_column(columModelRej.separP);
	}
	if(pColumn5)
	{
		pColumn5->set_sort_column(columModelRej.numP);
	}

}

/**
 Inicia el treeview de las rejillas.
 */
void Preferencias::iniciadorRejilla()
{
	int numCopOpcRej;
	
	numCopOpcRej = copiaOpcRej.size();
	copiaOpcRej = copiaOpcRej;
	treeviewRejG->set_headers_visible(true);
	refTreeModelRej = Gtk::ListStore::create(columModelRej);
	treeviewRejG->set_model(refTreeModelRej);
	
	if(numCopOpcRej)
	{
		for(int i = 0; i < numCopOpcRej; i++)
		{
			Gtk::TreeModel::Row row = *(refTreeModelRej->append());
			row[columModelRej.idCol] = copiaOpcRej[i].getID();
			row[columModelRej.nCol] = copiaOpcRej[i].getNumColumnas();
			row[columModelRej.nFil] = copiaOpcRej[i].getNumFilas();
			row[columModelRej.separP] = copiaOpcRej[i].getSeparaPuntos();
			row[columModelRej.numP] = copiaOpcRej[i].getNumPuntos();
		}
	}
	treeviewRejG->append_column("ID",columModelRej.idCol);
	//treeviewRejG->append_column("Columnas",columModelRej.nCol);
	//treeviewRejG->append_column("Filas",columModelRej.nFil);
	//treeviewRejG->append_column("Separacion",columModelRej.separP);
	//treeviewRejG->append_column("Puntos",columModelRej.numP);
	treeviewRejG->append_column("Columns",columModelRej.nCol);
	treeviewRejG->append_column("Rows",columModelRej.nFil);
	treeviewRejG->append_column("Distance",columModelRej.separP);
	treeviewRejG->append_column("Points",columModelRej.numP);

	treeviewRejG->get_selection()->unselect_all();

	//Hacemos clickable la cabecera
	treeviewRejG->set_headers_clickable();

	//Dividimos el treeView en filas y columnas
	treeviewRejG->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

	reordenarPorColumnas();
}

/**
 Borra todos los datos de un formulario al cambiar de pagina.
 @param bloc, GtkNotebookPage.
 @param guint, pag contiene el numero de pagina.
 */
void Preferencias::borraDatosForm(GtkNotebookPage* bloc,guint pag)
{
	Gdk::Color col;
	Glib::RefPtr<Gtk::TextBuffer> buf;
	Gtk::TreeModel::iterator it;
	
	col.set_rgb(0,0,0);
	
	clasesG->set_text("");
	nomClasesG->set_text("");
	buf = descripClasesG->get_buffer();
	buf->set_text("");
	//claseLinea.set_active_text("");

	estadosG->set_text("");
	nomEstadosG->set_text("");
	buf = descripEstadosG->get_buffer();
	buf->set_text("");
	colorEstadosG->set_color(col);

	separPuntosGPD->set_value(0);
	numColumnsG->set_value(0);
	numFilasG->set_value(0);

	colorEstadosG->set_sensitive(false);
	claseLinea->set_sensitive(false);
	
	iter = it;
}

/**
 Comprueba los datos de los formularios.
 */
bool Preferencias::datosCorrectorForm()
{
	if(blocNotas->get_current_page() == 7)
	{
		string titulo, mensaje;

		if(separPuntosGPD->get_value() < 1)
		{
			//titulo = "Error al introducir la separacion de puntos de la rejilla";
			titulo = "Error while introducing grid point distance";
			//mensaje = "Introduzca un valor mayor de 1 micra para la separacion de puntos";
			mensaje = "Please introduce a value greater than 1 um for grid point distance";
			Dialogos::dialogoError(mensaje, titulo);
			return false;
		}
		if(numFilasG->get_value() < 1)
		{
			//titulo = "Error al introducir el número de filas";
			titulo = "Error while introducing the number of rows";
			//mensaje = "El número de filas minimo a introducir es 1";
			mensaje = "The minimum number of rows is 1";
			Dialogos::dialogoError(mensaje, titulo);
			return false;
		}
		if(numColumnsG->get_value() < 1)
		{
			//titulo = "Error al introducir el número de filas";
			titulo = "Error while introducing the number of columns";
			//mensaje = "El número de columnas minimo a introducir es 1";
			mensaje = "The minimum number of columns is 1";
			Dialogos::dialogoError(mensaje, titulo);
			return false;
		}

		int numRej = copiaOpcRej.size();

		if(numRej)
		{
			int i = 0;
			
			while(i < numRej && (copiaOpcRej[i].getSeparaPuntos() != separPuntosGPD->get_value() ||
				  copiaOpcRej[i].getNumColumnas() !=  numColumnsG->get_value() || 
				  copiaOpcRej[i].getNumFilas() != numFilasG->get_value()))
			{
				i++;
			}

			if(copiaOpcRej[i].getSeparaPuntos() == separPuntosGPD->get_value() &&
			   copiaOpcRej[i].getNumColumnas() ==  numColumnsG->get_value() && 
			   copiaOpcRej[i].getNumFilas() == numFilasG->get_value())
			{
				//titulo = "Error al crear la rejilla";
				titulo = "Error while creating the grid";
				//mensaje = "Ya hay una rejilla con las mismas caracteristicas";
				mensaje = "That grid already exists";
				Dialogos::dialogoError(mensaje, titulo);
				return false;
			}
		}
	}
	
	return true;
}

/**
 Establece la pagina de las preferencias pasada por la variable pg.
 @param pg numero de pagina que queremos establecer.
 */
void Preferencias::setPaginaPreferencias(int pg)
{
	blocNotas->set_current_page(pg);
}
