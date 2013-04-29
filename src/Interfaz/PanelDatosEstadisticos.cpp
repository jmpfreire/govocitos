/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PanelDatosEstadisticos.cpp
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

#include "PanelDatosEstadisticos.h"

/**
 Constructor.
 @param sd, referencia del SistemaDibujado.
 @param pd, referencia del PanelDibujado.
 @param rej, referencia de la Rejilla.
 @param bd, referencia de la BarraEstado.
 @param est, referencia del vector de estados de maduración.
 */
PanelDatosEstadisticos::PanelDatosEstadisticos(SistemaDibujado &sd, PanelDibujado &pd, 
                                               Rejilla &rej, BarraEstado &be, vector<EstadoCelula> &est)
{
	sistemDibujo = &sd;
	panelDibujo = &pd;
	rejilla = &rej;
	estados = &est;
	bEstado = &be;
}

/**
 Destructor.
 */
PanelDatosEstadisticos::~PanelDatosEstadisticos()
{

}

/**
 */
void PanelDatosEstadisticos::setListaCelulas(ListadoCelulas &lc)
{
	coordCelulas = &lc;
}

/**
 Cierra la ventana de calculo de diametros
 */
void PanelDatosEstadisticos::cerrarCalEstadisticos()
{
	hide();
	//Destruimos toda la memoria dinamica
	if(treeviewTotales)
	{
		delete treeviewTotales;
		refTreeModelTotales->clear();
	}
	if(treeviewEstadist)
	{
		delete treeviewEstadist;
		refTreeModelCelula->clear();
	}
	panelEstacierra.emit();
}

/**
 Hbox del boton cerrar
 */
void PanelDatosEstadisticos::botonCerrarCalEstadisticos()
{
	Utiles::getWidgetGlade(Utiles::getGladeFile("panelCerradoDatos.glade"),"hboxPanelDatos",
					   "hboxPanelDatos", &hboxPanelDatos,
					   "nombrePanel", &nombrePanel,
					   "cerrarPanelDatos", &cerrarPanelDatos,
					   NULL);
}

/**
 Inicializa el panel de datos estadisticos.
 */
void PanelDatosEstadisticos::iniciarPanelDatosEstadisticos()
{
	botonCerrarCalEstadisticos();
	
	pack_start(*hboxPanelDatos, false, false);
	scrollTotal.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	scrollEstadist.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	add(hboxEstadisticos);
	hboxEstadisticos.set_spacing(10);
	hboxEstadisticos.add(scrollEstadist);
	hboxEstadisticos.pack_start(separador, false, false);
	hboxEstadisticos.add(scrollTotal);
	hboxEstadisticos.pack_start(separador1, false, false);
	hboxEstadisticos.add(scrollFinales);

	//Establecemos el scroll en automatico
	scrollTotal.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	scrollEstadist.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
	scrollFinales.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

	cerrarPanelDatos->signal_clicked().connect(sigc::mem_fun(*this, &PanelDatosEstadisticos::cerrarCalEstadisticos));

	//nombrePanel->set_label("<b>Cálculo de datos estadisticos</b>");
	nombrePanel->set_label("<b>Statistical data calculation</b>");
}

/**
 Calcula los datos estadisticos.
 */
bool PanelDatosEstadisticos::calculoEstadistico()
{	
	int numEstados;

	numEstados = estados->size();
	
	if(numEstados)
	{
		//Iniciamos la configuracion del panel
		iniciarPanelDatosEstadisticos();
			
		int numPolAceptados, numEstadoSelec, numCelDentroGridRojo;
		int numPuntosUsados;
		double areaTot;
		int *aciertosIndiv;
		vector<int> estadoSelec;
		vector<Celula> cellAceptedEst;
		vector<Celula> cellAceptedGrid;
		Celula cell;
		MenuSeleccion dialogSelec;

		numCelDentroGridRojo = numPuntosUsados = areaTot = 0;

		//llamamos la funcion de seleccion de etiquetas
		//estadoSelec = dialogSelec.seleccionClasesEstados(*estados, "Estados");
		estadoSelec = dialogSelec.seleccionClasesEstados(*estados, "States");
		
		numEstadoSelec = estadoSelec.size();

		if(numEstadoSelec)
		{
			bool calculoDatos = false;

			//Comprobamos si la rejilla tiene de separacion =! 1 en caso de que sea 1 se usara el area de la celula
			if(rejilla->getSeparPuntos() == 1)
			{
				for(int cx = 0; cx < coordCelulas->getNumCelulas(); cx++)
				{
					vector<double> diamRes;
					
					diamRes = CalculoMorfologico::diametroAreaFormula(*coordCelulas->getCelula(cx));

					coordCelulas->getCelula(cx)->setDiametroCell(diamRes[1]);
					coordCelulas->getCelula(cx)->setAreaCelula(diamRes[0]);
					
					calculoDatos = true;
				}

				//Eliminamos las celulas que no tienen estado
				cellAceptedGrid = CalculoEstadistico::celulasCoincidentesEstado(*estados, estadoSelec, *coordCelulas);

				numCelDentroGridRojo = cellAceptedGrid.size();

				aciertosIndiv = new int [numCelDentroGridRojo];
			}
			else
			{		
				//Eliminamos las celulas que no tienen estado
				cellAceptedEst = CalculoEstadistico::celulasCoincidentesEstado(*estados, estadoSelec, *coordCelulas);
				
				//Comprobamos los poligonos que son validos para la rejilla
				cellAceptedGrid = CalculoEstadistico::puntosDentroLimite(rejilla->getBordeMaxX(), rejilla->getBordeMaxY(), 
						                                                 rejilla->getBordeMinX(), rejilla->getBordeMinY(),
						                                                 numCelDentroGridRojo, cellAceptedEst);

				//Borramos el vector de seleccion de estados de celulas
				cellAceptedEst.clear();
	
				numPolAceptados = cellAceptedGrid.size();
				
				aciertosIndiv = new int [numPolAceptados];	
				
				for(int i = 0; i < numPolAceptados; i++)
				{
					aciertosIndiv[i] = 0;
				}
				
				calculoDatos = CalculoEstadistico::calculoPuntosDentroRejilla(aciertosIndiv, cellAceptedGrid,
				                                                              *rejilla->getVectorRejilla());
			}
			
			if(calculoDatos)
			{
				int numCellAcept;

				numCellAcept = cellAceptedGrid.size();

				//Panel de datos no totales con cada celula y sus puntos
			
				//Creamos el nuevo treeview
				treeviewEstadist = new Gtk::TreeView();

				//Añadimos la señal del treeview
				treeviewEstadist->signal_cursor_changed().connect(sigc::mem_fun
															  (*this, &PanelDatosEstadisticos::selecCelula));
			
				//Inicializamos las opciones del menu
				refTreeModelCelula = Gtk::ListStore::create(columCelula);
				treeviewEstadist->set_model(refTreeModelCelula);
			
				for(int i = 0; i < numCellAcept; i++)
				{
					double area;

					if(rejilla->getSeparPuntos() == 1)
					{
						area = cellAceptedGrid[i].getAreaCelula();
					}
					else
					{
						area = aciertosIndiv[i];
					}
					
					area = (area / rejilla->getNumPuntos()) * 100;
				
					//Creamos las etiquetas dinamicamente
					Gtk::TreeModel::Row row = *(refTreeModelCelula->append());
					row[columCelula.numCol] = cellAceptedGrid[i].getIdCelula();
					row[columCelula.colClase] = cellAceptedGrid[i].getClaseCelula();
					row[columCelula.colEstado] = cellAceptedGrid[i].getEstadoCelula();

					if(rejilla->getSeparPuntos() == 1)
					{
						row[columCelula.numPuntos] = cellAceptedGrid[i].getAreaCelula();
					}
					else
					{
						row[columCelula.numPuntos] = aciertosIndiv[i];
					}
					row[columCelula.areaRejilla] = area;

					idCelulas.push_back(cellAceptedGrid[i].getIdCelula());
				}

				/*
				 treeviewEstadist->append_column("Número Célula ",columCelula.numCol);
				treeviewEstadist->append_column("Clase  ",columCelula.colClase);
				treeviewEstadist->append_column("Estado  ",columCelula.colEstado);
				treeviewEstadist->append_column("Número de Puntos",columCelula.numPuntos);
				treeviewEstadist->append_column("Area Celula/Rejilla %",columCelula.areaRejilla);
				*/
				treeviewEstadist->append_column("No. cell ",columCelula.numCol);
				treeviewEstadist->append_column("Class  ",columCelula.colClase);
				treeviewEstadist->append_column("State  ",columCelula.colEstado);
				treeviewEstadist->append_column("Number of points",columCelula.numPuntos);
				treeviewEstadist->append_column("Area Cell/Grid %",columCelula.areaRejilla);
				scrollEstadist.set_size_request(280, 170);
				scrollEstadist.add(*treeviewEstadist);

				//Panel con los datos finales totales
			
				//Creamos el nuevo treeview
				treeviewTotales = new Gtk::TreeView();

				//Inicializamos las opciones del menu
				refTreeModelTotales = Gtk::ListStore::create(columTotales);
				treeviewTotales->set_model(refTreeModelTotales);
				
				for(int i = 0; i < numEstadoSelec; i++)
				{
					int numCelTotal = 0;
					int numPuntoTotal = 0;
					string estado1 = (*estados)[estadoSelec[i]].getEtiquetaClasificacion();
			
					for(int j = 0; j < numCellAcept; j++)
					{
						if(estado1 == cellAceptedGrid[j].getEstadoCelula())
						{
							if(rejilla->getSeparPuntos() == 1)
							{
								numCelTotal++;
								numPuntoTotal = numPuntoTotal + cellAceptedGrid[j].getAreaCelula();
							}
							else
							{
								numPuntoTotal = numPuntoTotal + aciertosIndiv[j];
							}
						}
						else if(estado1 == "out")
						{

						}
					}
					if(rejilla->getSeparPuntos() != 1)
					{
						numCelTotal = CalculoEstadistico::objetosDentroLimite(rejilla->getBordeMaxX(), rejilla->getBordeMaxY(),
							                                                  rejilla->getBordeMinX(), rejilla->getBordeMinY(),
							                                                  estado1, cellAceptedGrid);
					}					
					
					//Creamos las etiquetas dinamicamente
					Gtk::TreeModel::Row row = *(refTreeModelTotales->append());
					row[columTotales.colEstado] = (*estados)[estadoSelec[i]].getEtiquetaClasificacion();
					row[columTotales.numPuntos] = numPuntoTotal;
					row[columTotales.numCelulas] = numCelTotal;

					numPuntosUsados = numPuntosUsados + numPuntoTotal;
				}

				/*
				treeviewTotales->append_column("Estado ",columTotales.colEstado);
				treeviewTotales->append_column("Número puntos ",columTotales.numPuntos);
				treeviewTotales->append_column("Número de células",columTotales.numCelulas);
				*/
				treeviewTotales->append_column("State ",columTotales.colEstado);
				treeviewTotales->append_column("Number of points ",columTotales.numPuntos);
				treeviewTotales->append_column("Number of cells",columTotales.numCelulas);
				scrollTotal.set_size_request(100, 170);
				scrollTotal.add(*treeviewTotales);
				show_all();

				//Dividimos el treeView en filas y columnas
				treeviewTotales->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

				//Calculamos el area total usada
				areaTot = numPuntosUsados;
				areaTot = (areaTot / rejilla->getNumPuntos()) * 100;

				if(sistemDibujo->getCapaCelula()->getNumsCelulaSeleccionada())
				{
					sistemDibujo->getCapaCelula()->vaciaVectorCelulaSeleccionada();
					//Repintamos
					panelDibujo->actualizarVista();
					//bEstado->setClaseCell("sin clasificar");
					//bEstado->setEstadoCell("sin estado");
					bEstado->setClaseCell("unclassified");
					bEstado->setEstadoCell("without state");
				}
				//Deseleccionamos las filas
				treeviewEstadist->get_selection()->unselect_all();

				//Hacemos clickable la cabecera
				treeviewEstadist->set_headers_clickable();

				//Dividimos el treeView en filas y columnas
				treeviewEstadist->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);
				
				//Reordenacion de columnas
				reordenarPorColumnas();

				//Datos finales numPuntosUsados, numPuntosTotales
				datosFinalesEstadisticos(numCelDentroGridRojo, numPuntosUsados, areaTot);

				return true;		
			}
			else
			{
				string mensaje, titulo;
		
				//mensaje = "No hay ninguna célula concidente con el/los estado/s seleccionado/s";
				mensaje = "There is not any cell belonging to the selected states";
				titulo = "Govocitos";

				Dialogos::dialogoAdvertencia(mensaje, titulo);
			}
		}
		else
		{
			string mensaje, titulo;
		
			//mensaje = "No se ha seleccionado ningun estado";
			mensaje = "No state has been selected";
			titulo = "Govocitos";
			
			Dialogos::dialogoAdvertencia(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;
			
		//mensaje = "No hay estados definidos en el sistema";
		mensaje = "No states have been defined in the system";
		//titulo = "Error al leer los estados";
		titulo = "Error while reading states";
			
		Dialogos::dialogoError(mensaje, titulo);
	}
	
	return false;
}

/**
 Marca la celula seleccionada
 */
void PanelDatosEstadisticos::selecCelula()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	int numCelula;
	Celula cell;

	filaSeleccionada = treeviewEstadist->get_selection();
	
	iter = filaSeleccionada->get_selected();

	if(sistemDibujo->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		sistemDibujo->getCapaCelula()->vaciaVectorCelulaSeleccionada();
	}
	
	if(iter)
	{	
		int i = 0;
		int numCels;
		
		Gtk::TreeModel::Row row = *iter;

		numCelula = row[columCelula.numCol];
		numCels = coordCelulas->getNumCelulas();

		//Seleccionamos la celula
		while(i < numCels && numCelula != coordCelulas->getCelula(i)->getIdCelula())
		{
			i++;
		}
		
		//Seleccionamos la celula
		sistemDibujo->getCapaCelula()->setCelulaSeleccionada(i);

		//Obtenemos el poligono
		cell = *coordCelulas->getCelula(panelDibujo->getCapaCelula()->getCelulaSeleccionada(0));

		//Establecemos el nombre de la clase en la barra de estado
		bEstado->setClaseCell(cell.getClaseCelula());

		//Establecemos el nombre del estado en la barra de estadoCelula
		bEstado->setEstadoCell(cell.getEstadoCelula());
		
		//Repintamos
		panelDibujo->actualizarVista();
	}
}

/**
 Selecciona la fila del treeview correpondiente a la celula seleccionada por el usuario
 */
void PanelDatosEstadisticos::selectFilaTreeEst()
{
	int numCells;
	int idCell;
	int numCellSelec;

	if(treeviewEstadist)
	{
		//Deseleccionamos las filas
		treeviewEstadist->get_selection()->unselect_all();
	}
	
	if(sistemDibujo->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		numCellSelec = sistemDibujo->getCapaCelula()->getCelulaSeleccionada(0);
		numCells = idCelulas.size();
		idCell = coordCelulas->getCelula(numCellSelec)->getIdCelula();
	
		for(int i = 0; i < numCells; i++)
		{

			if(idCelulas[i] == idCell)
			{
				Gtk::TreeModel::Row row = refTreeModelCelula->children()[i];
				if(row)
					treeviewEstadist->get_selection()->select(row);
				break;
			}
		}
	}
}

/**
 Señal de apertura de panel diametros.
 */
PanelDatosEstadisticos::cierraPanelEstadistico PanelDatosEstadisticos::signal_cierra_estadisticos()
{
	return panelEstacierra;
}

/**
 Reordena el treeview por columnas.
 */
void PanelDatosEstadisticos::reordenarPorColumnas()
{		
	Gtk::TreeView::Column* pColumn1 = treeviewEstadist->get_column(0);
	Gtk::TreeView::Column* pColumn2 = treeviewEstadist->get_column(1);
	Gtk::TreeView::Column* pColumn3 = treeviewEstadist->get_column(2);
	Gtk::TreeView::Column* pColumn4 = treeviewEstadist->get_column(3);
	Gtk::TreeView::Column* pColumn5 = treeviewEstadist->get_column(4);
	
	if(pColumn1)
	{
		pColumn1->set_sort_column(columCelula.numCol);
	}
	if(pColumn2)
	{
		pColumn2->set_sort_column(columCelula.colClase);
	}
	if(pColumn3)
	{
		pColumn3->set_sort_column(columCelula.colEstado);
	}
	if(pColumn4)
	{
		pColumn4->set_sort_column(columCelula.numPuntos);
	}
	if(pColumn5)
	{
		pColumn5->set_sort_column(columCelula.areaRejilla);
	}
}

/**
 */
void PanelDatosEstadisticos::datosFinalesEstadisticos(int numCel, int numPUsados, double areaTotal)
{
	double areaNoUse;

	areaNoUse = 0.0;

	//Calculamos el area No usada
	areaNoUse = areaRejNoUsada();
	
	//Rellenamos el panel
	Utiles::getWidgetGlade(Utiles::getGladeFile("DatosEstadisticos.glade"),"vboxEst",
		"vboxEst", &vboxEst,
	    "numCelG", &numCelG,
	    "punTotalG", &punTotalG,
	    "percentNoCellG", &percentNoCellG,
	    "percentNoUseG", &percentNoUseG,
		"percentRejG", &percentRejG,
		NULL);

	numCelG->set_text(Utiles::converString(numCel));
	punTotalG->set_text(Utiles::converString(numPUsados));
	percentRejG->set_text(Utiles::converString(areaTotal) + " %");
	percentNoCellG->set_text(Utiles::converString(100 - areaTotal - areaNoUse) + " %");
	percentNoUseG->set_text(Utiles::converString(areaNoUse) + " %");
	    
	scrollFinales.add(*vboxEst);
}

/**
 */
double PanelDatosEstadisticos::areaRejNoUsada()
{
	int numCelulas;
	vector<Celula> regionOut;
	double areaNotUse;
	int *aciertosIndiv;

	numCelulas = coordCelulas->getNumCelulas();
	areaNotUse = 0.0;

	//Obtenemos solo las regiones vacias
	for(int i = 0; i < numCelulas; i++)
	{
		Celula cell;

		cell = *coordCelulas->getCelula(i);

		if(cell.getEstadoCelula() == "outimage")
		{
			regionOut.push_back(cell);
		}
	}

	if(regionOut.size())
	{
		bool calculoDatos = false;
		int numPolAceptados;
		
		//Comprobamos si la rejilla tiene de separacion =! 1 en caso de que sea 1 se usara el area de la celula
		if(rejilla->getSeparPuntos() == 1)
		{
			numPolAceptados = regionOut.size();

			aciertosIndiv = new int [numPolAceptados];

			for(int i = 0; i < numPolAceptados; i++)
			{
				aciertosIndiv[i] = 0;
			}
				
			calculoDatos = CalculoEstadistico::calculoRejillaSepar1(aciertosIndiv, regionOut);
		}
		else
		{
			numPolAceptados = regionOut.size();

			aciertosIndiv = new int [numPolAceptados];

			for(int i = 0; i < numPolAceptados; i++)
			{
				aciertosIndiv[i] = 0;
			}
				
			calculoDatos = CalculoEstadistico::calculoPuntosDentroRejilla(aciertosIndiv, regionOut,
				                                                          *rejilla->getVectorRejilla());
		}

		if(calculoDatos)
		{
			for(int i = 0; i < numPolAceptados; i++)
			{
				areaNotUse = areaNotUse + aciertosIndiv[i];
			}

			areaNotUse = (areaNotUse/ rejilla->getNumPuntos()) * 100;
		}
	}

	return areaNotUse;
}

/**
 Guarda los datos de las celulas en un flujo.
 @param &ios, referencia del flujo iostream que contiene los datos.
 */
void PanelDatosEstadisticos::writeDataStadistical(ofstream &ios) const
{		
	string linea = "";
	string separador = ";";
	int numFilasParcial, numColumnasParcial, numColumnasTotal, numFilasTotal, i;
	vector<Gtk::TreeViewColumn*> nombreColumnasParciales, nombreColumnasTotales;

	nombreColumnasParciales = treeviewEstadist->get_columns();
	nombreColumnasTotales = treeviewTotales->get_columns();

	numColumnasParcial = nombreColumnasParciales.size();
	numColumnasTotal = nombreColumnasTotales.size();
	numFilasParcial = refTreeModelCelula->children().size();
	numFilasTotal = refTreeModelTotales->children().size();

	//Obtenemos el nombre de las columnas
	for(i = 0; i < numColumnasParcial - 1; i++)
	{
		linea = linea + nombreColumnasParciales[i]->get_title() + separador;
	}

	linea = linea + nombreColumnasParciales[i]->get_title() + separador + " " + separador;

	for(i = 0; i < numColumnasTotal - 1; i++)
	{
		linea = linea + nombreColumnasTotales[i]->get_title() + separador;
	}

	linea = linea + nombreColumnasTotales[i]->get_title();
	
	ios<<linea<<endl;

	//Obtenemos el contenido de cada fila
	for(i = 0; i < numFilasParcial; i++)
	{
		string clase, estado;
		Gtk::TreeModel::Row row = refTreeModelCelula->children()[i];
		
		clase = row[columCelula.colClase];
		estado = row[columCelula.colEstado];
		
		linea = Utiles::converString(row[columCelula.numCol]) + separador + clase + separador + estado + separador +
			Utiles::converString(row[columCelula.numPuntos]) + separador +
			Utiles::converString(row[columCelula.areaRejilla]);

		if(i < numFilasTotal)
		{
			string estadoT;
			Gtk::TreeModel::Row row1 = refTreeModelTotales->children()[i];

			estadoT = row1[columTotales.colEstado];

			linea = linea + separador + " " + separador + estadoT + separador +
				Utiles::converString(row1[columTotales.numPuntos]) + separador +
				Utiles::converString(row1[columTotales.numCelulas]);
		}
		ios<<linea<<endl;
	}
}