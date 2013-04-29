/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelFecundidad.cpp
 * Copyright (C) José Manuel Pintor Freire 2011 <jpfreire@correo.ei.uvigo.es>
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

#include "PanelFecundidad.h"

/**
 Constructor.
 */
PanelFecundidad::PanelFecundidad()
{
	fecundidadActivada = false;
	
	//Iniciamos el panel de fecundidad
	iniciaPanelFecundidad();

	diametrosLupa.clear();
	plot = NULL;
	fecParcial = NULL;
	fecTotal = NULL;

	set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	
	//Añadimos el panel
	add(*panelFecG);
	
	show_all();

	selecRejG->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::configurarRejilla));
	rejCompletaG->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::seleccionTipoRejilla));
	rejPersonalG->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::seleccionTipoRejilla));
	exportCSVF->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::activaImprimeDatos));
	saveBDFec->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::activaGuardaDatosBD));
	histologicoG->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::setTipoCalculoK));
	diamLupaG->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::setTipoCalculoK));
	LupaButton->signal_clicked().connect(sigc::mem_fun(*this, &PanelFecundidad::configuraMetodoCalculoK));
}

/**
 Destructor.
 */
PanelFecundidad::~PanelFecundidad()
{
	delete plot;
	delete fecParcial;
	delete fecTotal;
}

/**
 Devuelve true si esta activo el boton de diametros histologicos, false en caso contario.
 @return bool.
 */
bool PanelFecundidad::getHistologicoK()
{
	return histologicoG->get_active();
}

/**
 Devuelve ture si esta activo el boton de diametros de lupa, false en caso contario.
 @return bool.
 */
bool PanelFecundidad::getLupaK()
{
	return diamLupaG->get_active();
}

/**
*/
bool PanelFecundidad::getActivoPanelFec()
{
	return fecundidadActivada;
}

/**
 Inicia el panel de fecundidad.
 */
void PanelFecundidad::iniciaPanelFecundidad()
{
	Utiles::getWidgetGlade(Utiles::getGladeFile("PanelResultados.glade"), "panelFecG", 
	                       "panelFecG", &panelFecG,
	                       "individuoG", &individuoG,
	                       "treeviewPuntosG", &treeviewPuntosG,
	                       "rejCompletaG", &rejCompletaG,
	                       "rejPersonalG", &rejPersonalG,
	                       "histologicoG", &histologicoG,
	                       "diamLupaG", &diamLupaG,
	                       "filRejG", &filRejG,
	                       "colRejG", &colRejG,
	                       "separRejG", &separRejG,
	                       "puntosRejG", &puntosRejG,
	                       "kFinalG", &kFinalG,
	                       "selecRejG", &selecRejG,
	                       "areaRejG", &areaRejG,
	                       "numImagG", &numImagG,
	                       "numObjG", &numObjG,
	                       "pesoOvarioG", &pesoOvarioG,
	                       "vboxImg", &vboxImg,
	                       "vboxPlot", &vboxPlot,
	                       "labFecunParcG", &labFecunParcG,
	                       "exportCSVF", &exportCSVF,
	                       "saveBDFec", &saveBDFec,
	                       "LupaButton", &LupaButton,
	                       "hboxFecContain", &hboxFecContain,
	                       "hboxFecParcialContain", &hboxFecParcialContain,
	                       NULL);
}

/**
*/
void PanelFecundidad::setActivoPanelFec(bool c)
{
	fecundidadActivada = c;
}

/**
 Establece el objeto del calculo de fecundidad.
 @param cF, CalculoFecundidad.
 */
void PanelFecundidad::setCalculoFecundidad(CalculoFecundidad &cF)
{
	calcFecun = &cF;
}

/**
 Establece el objeto de la rejilla.
 @param rej, Rejilla.
 */
void PanelFecundidad::setRejilla(Rejilla &rej)
{
	rejilla = &rej;
}

/**
 Establece el objeto de la configuracion del sistema.
 @param cfg, ConfigGovocitos.
 */
void PanelFecundidad::setConfiguracion(ConfigGovocitos &cfg)
{
	int numEstados;

	estadosEnUso.clear();
	
	configuracion = &cfg;
	setOpcionesRej();
	estados = configuracion->getDatosEstados();

	numEstados = estados->size();
	
	for(int i = 0; i < numEstados; i++)
	{
		if((*estados)[i].getEnUso())
		{
			estadosEnUso.push_back(i);
		}
	}
}

/**
 Establece el objeto que contiene el listado de individuos.
 @param lv, ListadoIndividuo.
 */
void PanelFecundidad::setListaIndividuos(ListadoIndividuo &lv)
{
	listIndiv = &lv;
}

/**
 Establece el objeto que contiene los resultados de fecundidad.
 @param lri, ResultFecundidad.
 */
void PanelFecundidad::setListaResultadosImg(ResultFecundidad &lri)
{
	listResultados = &lri;
}

/**
 Establece el vector de doubles que contiene la frecuencia de diametros.
 @param fd, vector<double>.
 */
void PanelFecundidad::setFrecuenciaDiametros(vector<double> fd)
{
	frecuenDiamet = fd;
}

/**
 Configura el metodo de calculo de K.
 */
void PanelFecundidad::configuraMetodoCalculoK()
{
	if(diamLupaG->get_active())
	{
		Gtk::Dialog *DialogMetK;
		Gtk::TextView *textDiam;

		LupaButton->set_sensitive(true);
		diametrosLupa.clear();

		Utiles::getWidgetGlade(Utiles::getGladeFile("DiametrosLupa.glade"), "DialogMetK", 
			                   "DialogMetK", &DialogMetK,
			                   "textDiam", &textDiam,
			                   NULL);

		DialogMetK->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
		DialogMetK->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	
		int opcion = DialogMetK->run();

		switch(opcion)
		{
			case(Gtk::RESPONSE_OK): 
			{
				Glib::RefPtr<Gtk::TextBuffer> buf;
				string diam;
				char * pch;
				
				buf = textDiam->get_buffer();
				diam = buf->get_text().c_str();

				pch = strtok ((char*)diam.c_str(),"\n");
				while (pch != NULL)
				{
					diametrosLupa.push_back(atof(pch));
					pch = strtok (NULL, "\n");
				}

				recalcularFecundidad();
				
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				histologicoG->set_active(true);
				LupaButton->set_sensitive(false);

				recalcularFecundidad();
				
				break;
			}
		}
			
		delete DialogMetK;
	}
}

/**
 Selecciona el tipo de Rejilla.
 */
void PanelFecundidad::seleccionTipoRejilla()
{
	if(rejCompletaG->get_active())
	{
		if(selecRejG->is_sensitive())
		{
			preCalculaRejilla();
			selecRejG->set_sensitive(false);

			recalcularFecundidad();
		}
	}
	else if(rejPersonalG->get_active())
	{
		if(!selecRejG->is_sensitive())
		{
			configurarRejilla();
			selecRejG->set_sensitive(true);
		}
	}
}

/**
 Establece el tipo de calculo de k.
 */
void PanelFecundidad::setTipoCalculoK()
{
	if(histologicoG->get_active())
	{
		if(LupaButton->is_sensitive())
		{
			recalcularFecundidad();
			LupaButton->set_sensitive(false);
		}
	}
	else if(diamLupaG->get_active())
	{
		if(!LupaButton->is_sensitive())
		{
			configuraMetodoCalculoK();
		}
	}
}

/**
 Pasa el vector de opciones.
 */
void PanelFecundidad::setOpcionesRej()
{	
	opcRej = configuracion->getDatosRejilla();
	
	rejCompletaG->set_active(true);

	rejilla->setSeparPun(configuracion->getDatosPreferencias()->getSeparPuntos());

	preCalculaRejilla();
}

/**
 Lanza ventana de seleccion de la rejilla.
 */
void PanelFecundidad::configurarRejilla()
{
	RejillaPersonalizada personalRej(*opcRej);
	int	rejillaUso;
	
	if(personalRej.muestraMenuSeleccion(rejillaUso))
	{
		rejilla->setID((*opcRej)[rejillaUso].getID());
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
		rejCompletaG->set_active(true);
	}

	rejilla->calculaRejilla();
	
	if(rejCompletaG->get_active() && rejilla->getSeparPuntos() == 1)
	{
		puntosRejG->set_text(Utiles::converString(rejilla->getAncho() * rejilla->getAlto()));
		colRejG->set_text(Utiles::converString(rejilla->getAncho()));
		filRejG->set_text(Utiles::converString(rejilla->getAlto()));
		separRejG->set_text(Utiles::converString(1));
	}
	else
	{
		puntosRejG->set_text(Utiles::converString(rejilla->getNumPuntos()));
		colRejG->set_text(Utiles::converString(rejilla->getNumColumnas()));
		filRejG->set_text(Utiles::converString(rejilla->getNumFilas()));
		separRejG->set_text(Utiles::converString(rejilla->getSeparPuntos()));
	}

	activaGuardarRejilla();
	
	//Recalculamos fecundidad
	recalcularFecundidad();

	if(fecParcial)
	{
		delete fecParcial;
		fecParcial = NULL;
	}
	
	labFecunParcG->set_text("");
}

/**
 Precalcula las caracteristicas de la rejilla seleccionada, num puntos, filas, columnas,
 separacion.
 */
void PanelFecundidad::preCalculaRejilla()
{
	rejilla->setAnchoRej(rejilla->getAncho());
	rejilla->setAltoRej(rejilla->getAlto());
	rejilla->setSeparPun(configuracion->getDatosPreferencias()->getSeparPuntos());
	rejilla->setNumColumnas(0);
	rejilla->setNumFilas(0);

	rejilla->calculaRejilla();
	
	if(rejilla->getSeparPuntos() != 1)
	{
		puntosRejG->set_text(Utiles::converString(rejilla->getNumPuntos()));
		colRejG->set_text(Utiles::converString(rejilla->getNumColumnas()));
		filRejG->set_text(Utiles::converString(rejilla->getNumFilas()));
		separRejG->set_text(Utiles::converString(rejilla->getSeparPuntos()));
	}
	else
	{
		puntosRejG->set_text(Utiles::converString(rejilla->getAncho() * rejilla->getAlto()));
		colRejG->set_text(Utiles::converString(rejilla->getAncho()));
		filRejG->set_text(Utiles::converString(rejilla->getAlto()));
		separRejG->set_text(Utiles::converString(1));

		activaGuardarRejilla();
	}

	activaGuardarRejilla();
	
	if(fecParcial)
	{
		delete fecParcial;
		fecParcial = NULL;
	}
	
	labFecunParcG->set_text("");
}

/**
 Inicia el treeView que contendra los datos estadisticos.
 */
void PanelFecundidad::iniciarTreeViewDatosEstadisticos()
{			
	int numResult, aux;
	double nonUse(0.0);
	vector<int> contEstados;
	vector<double> datosPunTotales, datosObjTotales;

	treeviewPuntosG->remove_all_columns();
	
	//Calculamos los totales por estado en caso de que no exista no se añadiran
	//Calculamos los totales del treeView
	datosPunTotales = datosPuntosTotales(nonUse);
	datosObjTotales = datosObjetosTotales();

	int numDatosTotales, numEnableEst;

	numDatosTotales = datosPunTotales.size();
	
	for(int i = 0; i < numDatosTotales; i++)
	{
		if((datosPunTotales[i] != 0) && (datosObjTotales[i] != 0))
		{
			contEstados.push_back(i);
		}
	}
	
	numEnableEst = contEstados.size();
	
	columDatos = new ModelColumns(numEnableEst, nonUse);
	
	numResult = listIndiv->getNumResultadoImagenes();

	//Inicializamos las opciones del menu
	refTreeModelDatos = Gtk::ListStore::create(*columDatos);
	treeviewPuntosG->set_model(refTreeModelDatos);

	//Añadimos la senal del treeView
	treeviewPuntosG->signal_cursor_changed().connect(sigc::mem_fun
	                                                 (*this, &PanelFecundidad::selecImagen));
	
	for(int i = 0; i < numResult; i++)
	{
		ResultadosImagen resImg;

		resImg = listIndiv->getResultadosImg(i);
		
		//Creamos las etiquetas dinamicamente
		Gtk::TreeModel::Row row = *(refTreeModelDatos->append());		
		row[columDatos->idCol] = listIndiv->getImagenVector(i)->getCodigoImagen();
					
		if(nonUse != 0)
		{
			row[columDatos->noUse] = resImg.getnumPunAreaNoUse();
		}	
		
		aux = 0;
		for(int j = 0; j < numEnableEst; j++)
		{
			row[columDatos->getItem(j)] = resImg.getNumPun(contEstados[j]);
			aux++;
		}
		
		for(int z = 0; z < numEnableEst; z++)
		{
			row[columDatos->getItem(z+aux)] = resImg.getNumObj(contEstados[z]);
		}
	}

	Gtk::TreeModel::Row row = *(refTreeModelDatos->append());
	row[columDatos->idCol] = "Total";
	
	if(nonUse != 0)
	{
		row[columDatos->noUse] = nonUse;
	}
	
	aux = 0;
	for(int i = 0; i < numEnableEst; i++)
	{
		row[columDatos->getItem(i)] = datosPunTotales[contEstados[i]]; 
		aux++;
	}
	
	for(int i = 0; i < numEnableEst; i++)
	{
		row[columDatos->getItem(i + aux)] = datosObjTotales[contEstados[i]]; 
	}
	
	treeviewPuntosG->append_column("ID",columDatos->idCol);
	
	if(nonUse != 0)
	{
		treeviewPuntosG->append_column("No Use",columDatos->noUse);
	}
	
	aux = 0;
	for(int i = 0; i < numEnableEst; i++)
	{
		treeviewPuntosG->append_column((*estados)[estadosEnUso[contEstados[i]]].getEtiquetaClasificacion() + " Points", columDatos->getItem(i));
		aux++;
	}
	
	for(int i = 0; i < numEnableEst; i++)
	{
		treeviewPuntosG->append_column((*estados)[estadosEnUso[contEstados[i]]].getEtiquetaClasificacion() + " Profiles", columDatos->getItem(i+aux));
	}

	treeviewPuntosG->get_column(0)->set_min_width(50);
	treeviewPuntosG->get_column(1)->set_min_width(60);

	int auxIndex;
	
	if(nonUse != 0)
	{
		treeviewPuntosG->get_column(1)->set_min_width(60);
		auxIndex = 2;
	}
	else
	{
		auxIndex = 1;
	}
	
	for(int index = auxIndex; index < ((numEnableEst * 2) + auxIndex); index++)
	{
		treeviewPuntosG->get_column(index)->set_min_width(80);
	}

	//Dividimos el treeView en filas y columnas
	treeviewPuntosG->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);
}

/**
 Carga las imagenes en miniatura del individuo.
 */
void PanelFecundidad::cargarImagenesMiniatura()
{
	int numImg;
	Gtk::Label *nombreImg;
	Gtk::Image *imageB;
	ImageCells *imgActual;
	Gtk::HBox *hvoxImg;
	vector<Gtk::VBox*> punteroBotones;
	
	numImg = listIndiv->getTamanhoVectorImag();
	
	for(int i = 0; i < numImg; i++)
	{
		Gtk::VBox *boxIndiv;

		boxIndiv = new Gtk::VBox(false, 6);
		
		imgActual = listIndiv->getImagenVector(i);

		//Creamos el objeto para 
		nombreImg = new Gtk::Label(imgActual->getNombreImg());
		imageB = new Gtk::Image(imgActual->getImagenCelulas());		
		boxIndiv->add(*nombreImg);
		boxIndiv->add(*imageB);

		punteroBotones.push_back(boxIndiv);
	}

	for(unsigned int i = 0; i < punteroBotones.size(); i++)
	{
		hvoxImg = new Gtk::HBox(false, 6);
		
		//Creamos el contenedor
		hvoxImg->add(*punteroBotones[i]);
		i++;
		if(i < punteroBotones.size())
		{
			hvoxImg->add(*punteroBotones[i]);
		}
		
		vboxImg->add(*hvoxImg);
	}

	show_all();
}

/**
 Estable los datos totales de los puntos y objetos por cada estado de maduración.
 */
vector<double> PanelFecundidad::datosObjetosTotales()
{
	int numResult, numEstados;
	vector<double> datosTotales;
	
	numResult = listIndiv->getNumResultadoImagenes();

	numEstados = estadosEnUso.size();

	vector<double> totObj(numEstados, 0);
	
	for(int i = 0; i < numResult; i++)
	{
		ResultadosImagen resImg;

		resImg = listIndiv->getResultadosImg(i);

		for(int j = 0; j < numEstados; j++)
		{
			totObj[j] = totObj[j] + resImg.getNumObj(j);
		}
	}

	for(int i = 0; i < numEstados; i++)
	{
		datosTotales.push_back(totObj[i]);
	}

	return datosTotales;
}

/**
 Estable los datos totales de los puntos y objetos por cada estado de maduración.
 */
vector<double> PanelFecundidad::datosPuntosTotales(double &nUse)
{
	int numResult, numEstados;
	double tnoUse(0.0);
	vector<double> datosTotales;
	
	numResult = listIndiv->getNumResultadoImagenes();

	numEstados = estadosEnUso.size();

	vector<double> totPun(numEstados, 0);
	
	for(int i = 0; i < numResult; i++)
	{
		ResultadosImagen resImg;

		resImg = listIndiv->getResultadosImg(i);

		tnoUse = tnoUse + resImg.getnumPunAreaNoUse();

		for(int j = 0; j < numEstados; j++)
		{
			totPun[j] = totPun[j] + resImg.getNumPun(j);
		}
	}

	nUse = tnoUse;
	
	for(int i = 0; i < numEstados; i++)
	{
		datosTotales.push_back(totPun[i]);
	}

	return datosTotales;
}
/**
 Establece los datos de fecundidad.
 */
void PanelFecundidad::estableceDatosFecundidad()
{
	int numEstados, numNoCero;
	Gtk::Label *labelEtiqueta, *labelResFec;
	
	numNoCero = 0;
	
	kFinalG->set_text(Utiles::converString(listResultados->getValorK()));
	numImagG->set_text(Utiles::converString(listIndiv->getNumXmlAnalizados()));
	numObjG->set_text(Utiles::converString(listResultados->getNumOvocitos()));
	areaRejG->set_text(Utiles::converString(listResultados->getAreaRejilla()));
	pesoOvarioG->set_text(Utiles::converString(listIndiv->getPesoOvarioFresco()));

	numEstados = estadosEnUso.size();

	if(fecTotal)
	{
		delete fecTotal;
	}
	
	for(int i = 0; i < numEstados; i++)
	{
		if(listResultados->getFecundidadEst(i) != 0)
		{
			numNoCero++;
		}
	}
	
	fecTotal = new Gtk::Table(numNoCero, 2);

	fecTotal->set_col_spacings(6);
	fecTotal->set_row_spacings(6);
	
	//Obtenemos los datos de fecundidad
	for(int i = 0; i < numEstados; i++)
	{
		if(listResultados->getFecundidadEst(i) != 0)
		{
			labelEtiqueta = new Gtk::Label((*estados)[estadosEnUso[i]].getNombreClasificacion(),Gtk::ALIGN_LEFT);
			labelResFec = new Gtk::Label(Utiles::converString(listResultados->getFecundidadEst(i)),Gtk::ALIGN_LEFT);
			fecTotal->attach(*labelEtiqueta,0,1,i,i+1);
			fecTotal->attach(*labelResFec,1,2,i,i+1);
		}
	}
	
	hboxFecContain->add(*fecTotal);

	show_all();
	
	individuoG->set_text(listIndiv->getCampanhaInd() + "-" + listIndiv->getEspecieInd() + "-" + listIndiv->getMuestreoInd() + "-" + listIndiv-> getIndividuoInd());
}

/**
 Recalcula la fecundidad del individuo.
 */
void PanelFecundidad::recalcularFecundidad()
{
	//Borramos los resultados anteriores
	listIndiv->vaciaVectorResultados();
	
	//Lanzamos el calculo de fecundidad
	calcFecun->calculoPuntosCelulas();

	if(diamLupaG->get_active())
	{
		calcFecun->calculaValorDeKLupa(diametrosLupa);
	}
	else
	{
		calcFecun->calculaValorDeK();
	}
	
	//Mostramos el grafico
	presentaHistograma();
	
	calcFecun->calculoAreaRejilla();
	calcFecun->calculoFecundidad();

	//Mostramos los datos en el treview
	iniciarTreeViewDatosEstadisticos();

	//Mostramos los resultados finales
	estableceDatosFecundidad();
}

/**
 Seleciona una imagen del individuo.
 */
void PanelFecundidad::selecImagen()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	string idColImg;
	string nombreImg;
	int numImg;
	ResultadosImagen result;

	filaSeleccionada = treeviewPuntosG->get_selection();
	
	iter = filaSeleccionada->get_selected();

	if(iter)
	{	
		Gtk::TreeModel::Row row = *iter;

		idColImg = row[columDatos->idCol];

		if(idColImg != "Total")
		{
			numImg = listIndiv->getNumResultadoImagenes();

			int i = 0;
		
			//Seleccionamos la imagen
			while(i < numImg && listIndiv->getImagenVector(i)->getCodigoImagen() != idColImg)
			{
				i++;
			}

			result = listIndiv->getResultadosImg(i);
			nombreImg = listIndiv->getImagenVector(i)->getNombreImg();

			calculoFecundidadParcial(result, nombreImg);
		}
		else
		{
			if(fecParcial)
			{
				delete fecParcial;
				fecParcial = NULL;
			}
		}
	}
}

/**
 Realiza el calculo de la fecundidad parcial, de 1 imagen.
 @param res, ResultadosImagen resultados para calcular la fecundidad de la imagen.
 @param nombre, string que contiene el nombre de la imagen.
 */
void PanelFecundidad::calculoFecundidadParcial(ResultadosImagen res, const string &nombre)
{
	int numEstados,numObj,nObjetos, areaEst, numNoCero, auxCero(0);
	double puntosRejilla;
	Gtk::Label *labelEtiqueta, *labelResFec;
	vector<double> fecEst;

	numNoCero = nObjetos = areaEst = numObj = 0;

	if(rejilla->getSeparPuntos() != 1)
	{
		puntosRejilla = rejilla->getNumPuntos();
	}
	else
	{
		puntosRejilla = rejilla->getAncho() * rejilla->getAlto();
	}

	puntosRejilla = puntosRejilla - res.getnumPunAreaNoUse();

	numEstados = estadosEnUso.size();
	
	for(int i = 0; i < numEstados; i++)
	{
		double fecEST(0.0);
		
		nObjetos = res.getNumObj(i);
		areaEst = res.getNumPun(i);
		numObj = numObj + nObjetos;

		if(areaEst && nObjetos)
		{
			fecEST = calcFecun->calculaFecunEstado(areaEst / puntosRejilla, nObjetos);
		}

		fecEst.push_back(fecEST);
		
		if(fecEST != 0)
		{
			auxCero++;
		}
	}
	
	numNoCero = (int)fecEst.size();
	
	if(fecParcial)
	{
		delete fecParcial;
	}
	
	fecParcial = new Gtk::Table((auxCero + 1), 2);
	
	fecParcial->set_col_spacings(6);
	fecParcial->set_row_spacings(6);
	
	for(int i = 0; i < numNoCero; i++)
	{
		if(fecEst[i] != 0)
		{
			labelEtiqueta = new Gtk::Label((*estados)[estadosEnUso[i]].getNombreClasificacion(),Gtk::ALIGN_LEFT);
			labelResFec = new Gtk::Label(Utiles::converString(fecEst[i]),Gtk::ALIGN_LEFT);
			fecParcial->attach(*labelEtiqueta,0,1,i,i+1);
			fecParcial->attach(*labelResFec,1,2,i,i+1);
		}
	}

	labelEtiqueta = new Gtk::Label("Number of profiles",Gtk::ALIGN_LEFT);
	labelResFec = new Gtk::Label(Utiles::converString(numObj),Gtk::ALIGN_LEFT);
	fecParcial->attach(*labelEtiqueta,0,1,numEstados,numEstados+1);
	fecParcial->attach(*labelResFec,1,2,numEstados,numEstados+1);
	
	hboxFecParcialContain->add(*fecParcial);

	show_all();

	labFecunParcG->set_text(nombre);
}

/**
 Muestra el histograma con la frecuencia de los diametros.
 */
void PanelFecundidad::presentaHistograma()
{
	//Ponemos el plot
	if(plot)
	{
		delete plot;
	}
	plot = new PlotHistogram(730, 450, frecuenDiamet);
	vboxPlot->add(*plot);
	plot->calcularValoresMaxHistogram();
	plot->creaCapaPlot();
	plot->dibujaHistograma();
	plot->pintaBarrasHistograma();

	show_all();
}

/**
 Guarda los datos de las celulas en un flujo.
 @param &ios, referencia del flujo iostream que contiene los datos.
 */
void PanelFecundidad::writeDataDiameter(ofstream &ios) const
{	
	string linea, separador;
	int numFilas, numColumnas, i, numEstados, numNoCero;
	vector<Gtk::TreeViewColumn*> nombreColumnas;
	vector<int> noUseCero;
	int numImg, auxAreaNoUse;

	auxAreaNoUse = numNoCero = 0;
	linea = "";
	separador = ";";
	nombreColumnas = treeviewPuntosG->get_columns();
	numEstados = estadosEnUso.size();

	numColumnas = nombreColumnas.size();
	numFilas = refTreeModelDatos->children().size();

	//Obtenemos el numero de area no usada de la imagen
	numImg = listIndiv->getNumResultadoImagenes();
	
	for(int j = 0; j < numImg; j++)
	{
		auxAreaNoUse = auxAreaNoUse + listIndiv->getResultadosImg(j).getnumPunAreaNoUse();
	}
	
	//Obtenemos el nombre de las columnas
	for(i = 0; i < numColumnas - 1; i++)
	{
		linea = linea + nombreColumnas[i]->get_title() + separador;
	}

	linea = linea + nombreColumnas[i]->get_title() + separador + " " + separador;

	//Columnas de resultados
	linea = linea + "k" + separador + "Numero Images" + separador + "Numero Profiles" + separador + 
		"Area Grid" + separador + "formol gonad weight" + separador;
	
	for(int j = 0; j < numEstados; j++)
	{
		if(listResultados->getFecundidadEst(j) != 0)
		{
			noUseCero.push_back(j);
		}
	}
	
	numNoCero = noUseCero.size();
	
	for(int j = 0; j < 	numNoCero; j++)
	{
		linea = linea + "Fecundity " + (*estados)[estadosEnUso[noUseCero[j]]].getEtiquetaClasificacion();
		
		if((j + 1) < numNoCero)
		{
			linea = linea + separador;
		}
	}
	
	ios<<linea<<endl;

	//Obtenemos el contenido de cada fila
	for(i = 0; i < numFilas-1; i++)
	{
		string idColumna;
		
		Gtk::TreeModel::Row row = refTreeModelDatos->children()[i];

		idColumna = row[columDatos->idCol];
		
		linea = idColumna + separador;
		
		if(auxAreaNoUse != 0)
		{
			linea = linea + Utiles::converString(row[columDatos->noUse]) + separador;
		}

		for(int j = 0; j < (numNoCero * 2) - 1; j++)
		{
			linea = linea + Utiles::converString(row[columDatos->getItem(j)]) + separador;
		}

		linea = linea + Utiles::converString(row[columDatos->getItem((numNoCero * 2) - 1)]);

		if(i == 0)
		{
			linea = linea + separador + " " + separador + kFinalG->get_text() + separador +
				numImagG->get_text() + separador + numObjG->get_text() + separador +
				areaRejG->get_text() + separador + pesoOvarioG->get_text() + separador;

			for(int j = 0; j < numNoCero - 1; j++)
			{
				if(listResultados->getFecundidadEst(noUseCero[j]) != 0)
				{
					linea = linea + Utiles::converString(listResultados->getFecundidadEst(noUseCero[j])) + separador;
				}
			}
			if(listResultados->getFecundidadEst(noUseCero[numNoCero - 1]) != 0)
			{
				linea = linea + Utiles::converString(listResultados->getFecundidadEst(noUseCero[numNoCero - 1]));
			}
		}

		ios<<linea<<endl;
	}
}

/**
 Señal para detectar que se activa la vista de datos
 */
PanelFecundidad::guardaDatos PanelFecundidad::signal_imprime_datos()
{
	return operacionCSVDatos;
}

/**
 Señal para detectar el guardado de datos en la bd.
 */
PanelFecundidad::guardaDatosBD PanelFecundidad::signal_datos_bd()
{
	return operacionBDDatos;
}

/**
 Señal para detectar el guardado de la rejilla en la bd.
 */
PanelFecundidad::guardaRejilla PanelFecundidad::signal_datos_rejilla()
{
	return operacionBDRejilla;
}

/**
 Emite señal de activado de datos.
 */
void PanelFecundidad::activaImprimeDatos()
{
	operacionCSVDatos.emit();
}

/**
 Activa el guardado de datos en la base de datos.
 */
void PanelFecundidad::activaGuardaDatosBD()
{
	operacionBDDatos.emit();
}

/**
 Activa el guardado de las rejillas en la bd.
 */
void PanelFecundidad::activaGuardarRejilla()
{
	operacionBDRejilla.emit();
}
