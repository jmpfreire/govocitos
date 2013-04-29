/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
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

#include "PanelDiametros.h"

/**
 Constructor
 */
PanelDiametros::PanelDiametros(PanelDibujado &pd,  BarraEstado &be, vector<ClaseCelula> &cl, vector<EstadoCelula> &est)
{
	clases = &cl;
	estados = &est;
	panelDibuj = &pd;
	bEstado = &be;
	diamMax = diamMin = redondezMax = redondezMin = numCelulas = micras = 0;

	calib = false;
}

/**
 Destructor.
 */
PanelDiametros::~PanelDiametros()
{
	
}

/**
 */
void PanelDiametros::setCalibracion(bool c)
{
	calib = c;
}

/**
 Establece las coordenadas del poligono
 */
void PanelDiametros::setCoordenadasPoligonos(ListadoCelulas &lc)
{
	coordCelulas = &lc;
}

/**
 Cierra la ventana de calculo de diametros-
 */
void PanelDiametros::cerrarCalDiametros()
{
	hide();
	//Destruimos toda la memoria dinamica
	if(treeviewDiametro)
	{
		delete treeviewDiametro;
		refTreeModelCelula->clear();
	}
	panelDiamcierra.emit();
}

/**
 Hbox del boton cerrar.
 */
void PanelDiametros::botonCerrarDiametros()
{
	Utiles::getWidgetGlade(Utiles::getGladeFile("panelCerradoDatos.glade"),"hboxPanelDatos",
					   "hboxPanelDatos", &hboxPanelDatos,
					   "nombrePanel", &nombrePanel,
					   "cerrarPanelDatos", &cerrarPanelDatos,
					   NULL);
}

/**
 Calcula el diametro de la celula seleccionada.
 */
void PanelDiametros::calculoDiametro()
{
	Gtk::Dialog *calculoWindowC;
	Gtk::Label *numPoligC, *claseC, *estadoC, *centroC, *diamFormula, *redondezC, *areaCell, *perimetCell;
	/*diamCentroBorde,*diamPuntosSfl diamPuntos,*/
	Celula *cell;
	int celulaS;
	vector<double> datos;
	vector<double> datos1;
	vector<int> centroide;
	
	celulaS = panelDibuj->getCapaCelula()->getCelulaSeleccionada(0);
	
	if(celulaS != -1)
	{
		cell = coordCelulas->getCelula(celulaS);
		
		//Inicializamos las variables de la ventana
		Utiles::getWidgetGlade(Utiles::getGladeFile("CalculaDiametro.glade"),"calculoWindowC",
					   "calculoWindowC", &calculoWindowC,
					   "numPoligC", &numPoligC,
					   "claseC", &claseC,
					   "estadoC", &estadoC,
					   "centroC", &centroC,
					   //"diamCentroBorde", &diamCentroBorde,
					   //"diamPuntos", &diamPuntos,
		               "diamFormula", &diamFormula,
		               "areaCell", &areaCell,
		               "perimetCell", &perimetCell,
		               //"diamPuntosSfl", &diamPuntosSfl,
		               "redondezC", &redondezC,
					   NULL);
				calculoWindowC->set_title("Cell data");
		
		calculoWindowC->set_icon_from_file(Utiles::getIconoFile("calculoDatos.png"));
		
		//Solicitamos el calculo del poligono seleccionado
		datos1 = CalculoMorfologico::diametroAreaFormula(*cell);
		datos = CalculoMorfologico::calculoRedondez(*cell, datos1[0]);
		centroide = CalculoMorfologico::calcularCentroide(*cell);
		
		numPoligC->set_label(Utiles::converString(cell->getIdCelula()));
		claseC->set_label(cell->getClaseCelula());
		estadoC->set_label(cell->getEstadoCelula());
		centroC->set_label("(" + Utiles::converString(centroide[0]) + " , " + Utiles::converString(centroide[1]) + ")");
		//diamCentroBorde->set_label(converString(datos[4]*micras) + " micras");
		//diamPuntos->set_label(converString(datos[6]*micras) + " micras");
		//diamFormula->set_label(Utiles::converString(datos1[1]*micras) + " um");
		diamFormula->set_label(Utiles::converString(datos1[1]) + " um");
		areaCell->set_label(Utiles::converString(datos1[0]) + " um");
		//diamPuntosSfl->set_label(converString(datos[7]*micras) + " micras");
		perimetCell->set_label(Utiles::converString(datos[0]) + " um");
		redondezC->set_label(Utiles::converString(datos[1]));

		calculoWindowC->run();
		delete calculoWindowC;
		panelDiamcierra.emit();
	}
}

/**
 Calcula el diametro de las celulas seleccionadas, como su centroide y redondez,
 los datos obtenidos son mostrados en un treeview
 @return false si no se calcula ningun diametro, verdadero en caso contrario
 */
bool PanelDiametros::calculoDiametrosClass()
{
	if(clases->size() || estados->size())
	{	
		vector<double> datos;
		vector<double> datos1;
		//vector<double> datos2; 
		vector<int> centroide;
		vector<vector<string> > claseSelec;
		int numClasesSelec, numEstadosSelec, numPoligonos;
		Celula *cell;
		bool existenDatos;
		MenuSeleccion dialogSelec;

		diamMax = diamMin = redondezMax = redondezMin = numCelulas = 0;
		
		//Inicializamos el panel
		botonCerrarDiametros();

		pack_start(*hboxPanelDatos, false, false);
		boxFinal.set_spacing(10);
		scrollTreeView.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
		add(boxFinal);
		boxFinal.add(scrollTreeView);
		scroollDatosFinales.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
		boxFinal.pack_start(separador, false, false);
		boxFinal.add(scroollDatosFinales);

		cerrarPanelDatos->signal_clicked().
				connect(sigc::mem_fun(*this, &PanelDiametros::cerrarCalDiametros));
	
		//llamamos la funcion de seleccion de etiquetas
		//claseSelec = dialogSelec.seleccionClaEstDiametro(*clases, *estados, "Clases y Estados");
		claseSelec = dialogSelec.seleccionClaEstDiametro(*clases, *estados, "Classes and States");

		//Asignamos el nombre del panel
		//nombrePanel->set_label("<b>Cálculo de los diámetros de todas las células en micras</b>");

		if(calib)
		{
			nombrePanel->set_label("<b>Data cells (um)</b>");
		}
		else
		{
			nombrePanel->set_label("<b>Data cells (pixels)</b>");
		}
	
		//Numero de poligonos
		numPoligonos = coordCelulas->getNumCelulas();
		
		//Numero de clases seleccionados
		numClasesSelec = claseSelec[0].size();
		numEstadosSelec = claseSelec[1].size();

		if(numClasesSelec || numEstadosSelec)
		{
			int j, z;
			
			//Creamos el nuevo treeView
			treeviewDiametro = new Gtk::TreeView();
				
			//Añadimos la senal del treeView
			treeviewDiametro->signal_cursor_changed().connect(sigc::mem_fun
													  (*this, &PanelDiametros::selecCelula));
			
			existenDatos = false;
			
			refTreeModelCelula = Gtk::ListStore::create(columCelula);
			treeviewDiametro->set_model(refTreeModelCelula);
			
			for(int i = 0; i < numPoligonos; i++)
			{	
				cell = coordCelulas->getCelula(i);
				j = 0;
				z = 0;
				datos.clear();
				
				while(j < numClasesSelec && cell->getClaseCelula() != claseSelec[0][j])
				{
					j++;
				}

				while(z < numEstadosSelec && cell->getEstadoCelula() != claseSelec[1][z])
				{
					z++;
				}
				if(((j < numClasesSelec && cell->getClaseCelula() == claseSelec[0][j]) || numClasesSelec == 0) &&
				   ((z < numEstadosSelec && cell->getEstadoCelula() == claseSelec[1][z]) || numEstadosSelec == 0))
				{
					existenDatos = true;
					datos1 = CalculoMorfologico::diametroAreaFormula(*cell);
					datos = CalculoMorfologico::calculoRedondez(*cell, datos1[0]);
					centroide = CalculoMorfologico::calcularCentroide(*cell);
					//datos2 = CalculoMorfologico::diametroCentroBorde(*cell);
						
					//Creamos las etiquetas dinamicamente
					Gtk::TreeModel::Row row = *(refTreeModelCelula->append());
					row[columCelula.numCol] = cell->getIdCelula();
					row[columCelula.colClase] = cell->getClaseCelula();
					row[columCelula.colEstado] = cell->getEstadoCelula();
					//row[columCelula.diamCentroBorde] = datos2[4];
					//row[columCelula.diamPuntos] = CalculoMorfologico::diametroAreaPuntos2(*cell);
					//row[columCelula.diamPuntosSfl] = CalculoMorfologico::diametroAreaPuntos2(*cell);
					row[columCelula.diamFormula] = datos1[1];					
					row[columCelula.areaCel] = (int)datos1[0];
					row[columCelula.perimetro] = (int)datos[0];
					row[columCelula.redondez] = datos[1];
					row[columCelula.centroXY] = "(" + Utiles::converString(centroide[0]) + " . " + Utiles::converString(centroide[1]) + ")";

					//Almacenamos el id de la celula
					numCelulas++;

					if(diamMax <= (datos1[1]))
					{
						diamMax = datos1[1];
					}
					if(diamMin >= (datos1[1]) || diamMin == 0)
					{
						diamMin = datos1[1];
					}
					if(redondezMax <= datos[1])
					{
						redondezMax = datos[1];
					}
					if(redondezMin >= datos[1] || redondezMin == 0)
					{
						redondezMin = datos[1];
					}
				}
			}
			if(existenDatos)
			{
				/*
				treeviewDiametro->append_column("Número Célula ",columCelula.numCol);
				treeviewDiametro->append_column("Clase  ",columCelula.colClase);
				treeviewDiametro->append_column("Estado  ",columCelula.colEstado);
				//treeviewDiametro->append_column("Diámetro CB (micras)  ",columCelula.diamCentroBorde);
				//treeviewDiametro->append_column("Diámetro Area Puntos",columCelula.diamPuntos);
				//treeviewDiametro->append_column("Diámetro sfl (micras)",columCelula.diamPuntosSfl);
				treeviewDiametro->append_column("Diámetro (micras)", columCelula.diamFormula);
				treeviewDiametro->append_column("Area (micras)", columCelula.areaCel);
				treeviewDiametro->append_column("Perimetro (micras)", columCelula.perimetro);
				treeviewDiametro->append_column("Redondez", columCelula.redondez);
				treeviewDiametro->append_column("Centroide     ",columCelula.centroXY);
				*/
			
				treeviewDiametro->append_column("No. cell ",columCelula.numCol);
				treeviewDiametro->append_column("Class  ",columCelula.colClase);
				treeviewDiametro->append_column("State  ",columCelula.colEstado);
				/*treeviewDiametro->append_column("Diám CB (micras)  ",columCelula.diamCentroBorde);
				treeviewDiametro->append_column("Diám Area Puntos",columCelula.diamPuntos);
				treeviewDiametro->append_column("Diám sfl (micras)",columCelula.diamPuntosSfl);*/
				treeviewDiametro->append_column("Diameter (um)", columCelula.diamFormula);
				treeviewDiametro->append_column("Area (um)", columCelula.areaCel);
				treeviewDiametro->append_column("Perimeter (um)", columCelula.perimetro);
				treeviewDiametro->append_column("Roundness", columCelula.redondez);
				treeviewDiametro->append_column("Centroid     ",columCelula.centroXY);
				
				scrollTreeView.add(*treeviewDiametro);
				scrollTreeView.set_size_request(600, 170);
				show_all();
				
				if(panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada())
				{
					panelDibuj->getCapaCelula()->vaciaVectorCelulaSeleccionada();
					//Repintamos
					panelDibuj->actualizarVista();
				}
				//Deseleccionamos las filas
				treeviewDiametro->get_selection()->unselect_all();

				//Hacemos clickable la cabecera
				treeviewDiametro->set_headers_clickable();

				//Dividimos el treeView en filas y columnas
				treeviewDiametro->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);
				
				//Creamos la señal
				reordenarPorColumnas();

				//Añadimos los datos finales
				datosFinalesDiametros();

				return true;
			}
			else
			{
				string mensaje, titulo;
			
				//mensaje = "No hay ninguna célula coincidente con la/s clase/s o lo/s estado/s seleccionada/s";
				mensaje = "There are no cells belonging to the selected classes or states";
				titulo = "Govocitos";
			
				Dialogos::dialogoAdvertencia(mensaje, titulo);
			}
		}
		else
		{
			string mensaje, titulo;
			
			//mensaje = "No se ha seleccionado ninguna clase/estado";
			mensaje = "No class or state have been selected";
			titulo = "Govocitos";
			
			Dialogos::dialogoAdvertencia(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;
			
		//mensaje = "No hay estados/clases definidos en el sistema";
		mensaje = "No class or state has been defined in the system";
		//titulo = "Error al leer los estados/clases";
		titulo = "Error while reading classes and states";
		
		Dialogos::dialogoError(mensaje, titulo);
	}
	
	return false;
}

/**
 Marca la celula seleccionada.
 */
void PanelDiametros::selecCelula()
{
	Glib::RefPtr<Gtk::TreeSelection> filaSeleccionada;
	Gtk::TreeModel::iterator iter;
	int numCelula;
	Celula cell;

	filaSeleccionada = treeviewDiametro->get_selection();
	
	iter = filaSeleccionada->get_selected();

	if(panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		panelDibuj->getCapaCelula()->vaciaVectorCelulaSeleccionada();
	}
	
	if(iter)
	{	
		int i = 0;
		int numCels = coordCelulas->getNumCelulas(); 
	
		Gtk::TreeModel::Row row = *iter;

		numCelula = row[columCelula.numCol];

		//Seleccionamos la celula
		while(i < numCels && numCelula != coordCelulas->getCelula(i)->getIdCelula())
		{
			i++;
		}
		
		panelDibuj->getCapaCelula()->setCelulaSeleccionada(i);
		
		//Obtenemos el poligono
		cell = *coordCelulas->getCelula(i);

		//Establecemos el nombre de la clase en la barra de estado
		bEstado->setClaseCell(cell.getClaseCelula());

		//Establecemos el nombre del estado en la barra de estadoCelula
		bEstado->setEstadoCell(cell.getEstadoCelula());
		
		//Repintamos
		panelDibuj->actualizarVista();
	}
}

/**
 Selecciona la fila del treeview correpondiente a la celula seleccionada por el usuario.
 */
void PanelDiametros::selectFilaTreeDiam()
{
	int idCell;
	int numCellSelec;

	if(treeviewDiametro)
	{
		//Deseleccionamos las filas
		treeviewDiametro->get_selection()->unselect_all();
	}

	if(panelDibuj->getCapaCelula()->getNumsCelulaSeleccionada())
	{
		numCellSelec = panelDibuj->getCapaCelula()->getCelulaSeleccionada(0);
		idCell = coordCelulas->getCelula(numCellSelec)->getIdCelula();
	
		for(int i = 0; i < numCelulas; i++)
		{
			Gtk::TreeModel::Row row = refTreeModelCelula->children()[i];

			if(row[columCelula.numCol] == idCell)
			{
				treeviewDiametro->get_selection()->select(row);
				break;
			}
		}
	}	
}

/**
 Guarda los datos de las celulas en un flujo.
 @param &ios, referencia del flujo iostream que contiene los datos.
 */
void PanelDiametros::writeDataDiameter(ofstream &ios) const
{	
	string linea = "";
	string separador = ";";
	int numFilas, numColumnas, i;
	vector<Gtk::TreeViewColumn*> nombreColumnas;

	nombreColumnas = treeviewDiametro->get_columns();

	numColumnas = nombreColumnas.size();
	numFilas = refTreeModelCelula->children().size();

	//Obtenemos el nombre de las columnas
	for(i = 0; i < numColumnas - 1; i++)
	{
		linea = linea + nombreColumnas[i]->get_title() + separador;
	}

	linea = linea + nombreColumnas[i]->get_title();

	ios<<linea<<endl;

	//Obtenemos el contenido de cada fila
	for(i = 0; i < numFilas; i++)
	{
		string clase, estado, centro;
		Gtk::TreeModel::Row row = refTreeModelCelula->children()[i];

		clase = row[columCelula.colClase];
		estado = row[columCelula.colEstado];
		centro = row[columCelula.centroXY];

		linea = Utiles::converString(row[columCelula.numCol]) + separador + clase + separador + estado + separador +
/*			Utiles::converString(row[columCelula.diamCentroBorde]) + separador +
			Utiles::converString(row[columCelula.diamPuntos]) + separador +
			Utiles::converString(row[columCelula.diamPuntosSfl]) + separador +*/
			Utiles::converString(row[columCelula.diamFormula]) + separador +
			Utiles::converString(row[columCelula.areaCel]) + separador + 
			Utiles::converString(row[columCelula.perimetro]) + separador +
			Utiles::converString(row[columCelula.redondez]) + separador + centro;

		ios<<linea<<endl;
	}
}

/**
 Señal para detectar la apertura del panel de calculo de diametros.
 */
PanelDiametros::cierraPanelDiametros PanelDiametros::signal_cierra_diametros()
{
	return panelDiamcierra;
}

/**
 Hace que las columnas del treeview sean reordenables.
 */
void PanelDiametros::reordenarPorColumnas()
{
	Gtk::TreeView::Column* pColumn1 = treeviewDiametro->get_column(0);
	Gtk::TreeView::Column* pColumn2 = treeviewDiametro->get_column(1);
	Gtk::TreeView::Column* pColumn3 = treeviewDiametro->get_column(2);
	Gtk::TreeView::Column* pColumn4 = treeviewDiametro->get_column(3);
	Gtk::TreeView::Column* pColumn5 = treeviewDiametro->get_column(4);
	Gtk::TreeView::Column* pColumn6 = treeviewDiametro->get_column(5);
	Gtk::TreeView::Column* pColumn7 = treeviewDiametro->get_column(6);
	
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
		pColumn4->set_sort_column(columCelula.diamFormula);
	}
	if(pColumn5)
	{
		pColumn5->set_sort_column(columCelula.areaCel);
	}
	if(pColumn6)
	{
		pColumn6->set_sort_column(columCelula.perimetro);
	}
	if(pColumn7)
	{
		pColumn7->set_sort_column(columCelula.redondez);
	}

}

/**
 Establece los datos finales en el panel datos diametros.
 */
void PanelDiametros::datosFinalesDiametros()
{
	Utiles::getWidgetGlade(Utiles::getGladeFile("DatosDiametros.glade"),"vboxDiam",
	    "vboxDiam", &vboxDiam,
	    "numCelulasG", &numCelulasG,
		"diamMaxG", &diamMaxG,
		"diamMinG", &diamMinG,
	    "redMaxG", &redMaxG,
	    "redMinG", &redMinG,
		NULL);

	numCelulasG->set_text(Utiles::converString(numCelulas));
	diamMaxG->set_text(Utiles::converString(diamMax) + " um");
	diamMinG->set_text(Utiles::converString(diamMin) + " um");
	redMaxG->set_text(Utiles::converString(redondezMax));
	redMinG->set_text(Utiles::converString(redondezMin));
	    
	scroollDatosFinales.add(*vboxDiam);
}
