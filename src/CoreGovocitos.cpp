/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CoreGovocitos.cpp
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jpfreire@correo.ei.uvigo.es>
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

#include "CoreGovocitos.h"

/**
 Constructor, Crea a su vez los objetos InterfazGovocitos y ModulosGovocitos.
 */
CoreGovocitos::CoreGovocitos()
: interfazGovocitos(new InterfazGovocitos()),
modeloGovocitos(new ModulosGovocitos())
{
	interfazGovocitos->setControlador(*this);

	//iniciamos todo el sistema
	inicializaSistema();

	//comprobamos la conectividad
	if(compruebaConectividadBD())
	{
		updateRejillasBD();
		updateClaseEstadoBD();
	}
}

/**
 Destructor, destuye los objetos de InterfazGovocitos y ModulosGovocitos.
 */
CoreGovocitos::~CoreGovocitos()
{
	delete interfazGovocitos;
	delete modeloGovocitos;
}

/**
 Devuelve un puntero del objeto ModulosGovocitos.
 @return ModulosGovocitos *, puntero del objeto modeloGovocitos.
 */
ModulosGovocitos *CoreGovocitos::getModeloGovocitos()
{
	return modeloGovocitos;
}

/**
 Devuelve un puntero del objeto InterfazGovocitos.
 @param InterfazGovocitos *, puntero del objeto interfazGovocitos.
 */
InterfazGovocitos *CoreGovocitos::getInterfazGovocitos()
{
	return interfazGovocitos;
}

/**
 Guarda los cambios realizados en el menu de Preferencias y los aplica a todo el
 sistema.
 @param pref, puntero del objeto Preferencias que contiene los cambios realizados,
 en el panel de preferencias.
 */
void CoreGovocitos::ejecMenuPreferencias(Preferencias &pref)
{
	ConexionBD *conMysql;
	ConfigGovocitos *confGovocitos;

	confGovocitos = modeloGovocitos->getConfiguracion();
	conMysql = modeloGovocitos->getConexionMySql();

	//Deseleccionamos las celulas seleccionadas
	modeloGovocitos->getSistemaDibujado()->getCapaCelula()->vaciaVectorCelulaSeleccionada();
	
	//Obtenemos los cambios realizados
	confGovocitos->setDatosRejilla(pref.getOpcionesRej());
	confGovocitos->setDatosClases(pref.getClasesCelula());
	confGovocitos->setDatosEstados(pref.getEstadosCelula());
	confGovocitos->setDatosPreferencias(pref.getOpcionesPref());

	//Actualizamos las rejillas de la Base de Datos
	conMysql->insertarRejillasPref(*confGovocitos->getDatosRejilla());

	//Guardamos la configuracion
	confGovocitos->escribirFicherosConf();

	//Establecemos los nuevo parametros de conexion
	modeloGovocitos->setNuevosDatosConexion();

	//Establece nuevas opciones
	modeloGovocitos->getSistemaDibujado()->cargaOpcionesDibujado(*confGovocitos->getDatosPreferencias());

	//Cargamos las clases en el popup y en el panel propiedades
	interfazGovocitos->getPanelDibujado()->menuPopupCelula(modeloGovocitos->getConfiguracion()->getDatosClases(),
	                                                       modeloGovocitos->getConfiguracion()->getDatosEstados());

	interfazGovocitos->getPanelPropiedades()->setConfiguracion(*modeloGovocitos->getConfiguracion());
	
	interfazGovocitos->getPanelDibujado()->actualizarVista();

	//Actualizamos las preferencias en la fecundidad
	if(interfazGovocitos->getPanelFecundidad()->getActivoPanelFec())
	{
		//Establecemos objetos para relalizar el calculo de fecundidad
		interfazGovocitos->getPanelFecundidad()->setRejilla(*modeloGovocitos->getRejilla());
		interfazGovocitos->getPanelFecundidad()->setConfiguracion(*modeloGovocitos->getConfiguracion());

		modeloGovocitos->getCalculoFecundidad()->setRejilla(*modeloGovocitos->getRejilla());
		modeloGovocitos->getCalculoFecundidad()->setConfiguracion(*modeloGovocitos->getConfiguracion());

		interfazGovocitos->getPanelFecundidad()->recalcularFecundidad();
	}
	
	//Establecemos las preferencias del sftp
	modeloGovocitos->setNuevoConexionSftp();
	
	//Establecemos las preferencias de conexion
	modeloGovocitos->setNuevoConexionMySql();

	//Comprobamos la conectividad
	if(compruebaConectividadBD(true))
	{
		//Obtenemos las rejillas
		updateRejillasBD();
		//Obtenemos Clases y Estados
		updateClaseEstadoBD();
	}
}

/**
 Abre una imagen que se encuentra en local.
 */
void CoreGovocitos::abrirImagenLocal()
{
	ImageCells *imgActual;
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	imgActual = modeloGovocitos->getImageActual();	
	
	//Cargamos imagen en el sistema
	if(imgActual->cargaImagenEnSistema())
	{
		//Cargar imagen en Gtk::Image e iniciar zoom
		paintSystem->setZoomActual(10);
		paintSystem->setImagen();
	}
}

/**
 Abre un fichero xml de celulas que se encuentra en local.
 */
void CoreGovocitos::abrirXmlLocal()
{
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	modeloGovocitos->setNuevasCelulas();

	paintSystem->getCapaCelula()->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());
	cargaDatosCelulas(modeloGovocitos->getImageActual()->getRutaXmlImg());
	interfazGovocitos->getPanelDibujado()->actualizarVista();

	//Vaciar las pilas
	modeloGovocitos->setNuevaPilaDeshacer();
	modeloGovocitos->setNuevaPilaRehacer();
}

/**
 Abre una imagen que se encuentra en el servidor remoto.
 */
bool CoreGovocitos::abrirImagenRemotaBD()
{
	ConexionBD *conMysql;
	ImageCells *imgActual;
	int imagenSeleccionada;
	ListadoCache *listCacheImag;
	string nombreImagen, rutaImagen;
	ListadoImagenes *listimag;
	SistemaDibujado *paintSystem;
	DataImage *imagenDescarga;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	listCacheImag = modeloGovocitos->getListadoCache();
	conMysql = modeloGovocitos->getConexionMySql();
	
	modeloGovocitos->setNuevaListaImagenes();

	listimag = modeloGovocitos->getListaImagenes();
	
	if(conMysql->obtenerImagenes(*listimag))
	{
		if(listimag->getTamanhoVectorImag())
		{
			DialogoRemoto *dialAbrirR;

			//dialAbrirR = new DialogoRemoto("Abrir imagenes BD", *listimag);
			dialAbrirR = new DialogoRemoto("Open DB Images", *listimag);

			if(dialAbrirR->abreDialogoRemoto(imagenSeleccionada))
			{	
				delete dialAbrirR;

				imgActual = modeloGovocitos->getImageActual();

				//Cargamos datos de la imagen
				imagenDescarga = listimag->getImagenVector(imagenSeleccionada);

				//Cargamos datos de la imagen
				imgActual->setMd5Img(imagenDescarga->getMd5Img());
				imgActual->setCalibracionImg(imagenDescarga->getCalibracionImg());
				imgActual->setCampanhaImg(imagenDescarga->getCampanhaImg());
				imgActual->setMuestreoImg(imagenDescarga->getMuestreoImg());
				imgActual->setIndividuoImg(imagenDescarga->getIndividuoImg());
				imgActual->setCodigoImagen(imagenDescarga->getCodigoImagen());
				imgActual->setSpecieImage(imagenDescarga->getSpecieImage());
				imgActual->setNombreXml(imagenDescarga->getNombreXml());
				imgActual->setRutaXmlImg(imagenDescarga->getRutaXmlImg());				
			
				//Obtenemos el nombre de la imagen a descargar
				nombreImagen = imagenDescarga->getNombreImgCompleto();
			
				imgActual->setNombreImg(nombreImagen);

				//Cargamos calibracion
				cargaValorMicrasSistema();
			
				//Comprobamos si la imagen se encuentra en la cache
				if(listCacheImag->getImagenLista(nombreImagen) == "")
				{
					HttpsConexion *conexionImagenes;
					conexionImagenes = modeloGovocitos->getConexionBD();
					/*Obtenemos el fichero y si la descarga es correcta se procedera
					a la apertura de la imagen en caso contrario se mostrara un 
					mensaje de error*/
					if(!conexionImagenes->descargaImagen(imagenDescarga))
					{			
						interfazGovocitos->menuCerrar();

						string titulo, mensaje;

						//titulo = "Error al obtener la imagen";
						titulo = "Error while obtaining the image";
						//mensaje = "La imagen descargada no coincide con la almacenada";
						mensaje = "The system can´t locate the file.";

						Dialogos::dialogoError(mensaje, titulo);
						
						return false;
					}
				}
				rutaImagen = Utiles::direccionCache(nombreImagen);

				imgActual->setRutaImg(rutaImagen);
					
				if(imgActual->cargaImagenEnSistema())
				{
					//Cargar imagen en Gtk::Image e iniciar zoom
					paintSystem->setZoomActual(10);
					paintSystem->setImagen();

					//Añadimos la imagen a la cache
					listCacheImag->addImagenCache(nombreImagen);	
					modeloGovocitos->getConfiguracion()->escribirFicheroCache();
					
					return true;
				}
				else
				{
					string titulo, mensaje;

					//titulo = "Error al obtener la imagen";
					titulo = "Error while obtaining the image";
					//mensaje = "La imagen descargada no coincide con la almacenada";
					mensaje = "The downloaded image is not the same as the saved one";

					Dialogos::dialogoError(mensaje, titulo);	
				}
			}
			else
			{
				delete dialAbrirR;
				
				string titulo, mensaje;

				//titulo = "Selección de imagenes";
				titulo = "Image Selection";
				//mensaje = "No se ha seleccionado ninguna imagen";
				mensaje = "No image selected";

				Dialogos::dialogoAdvertencia(mensaje, titulo);
			}
		}
		else
		{
			string titulo, mensaje;

			//titulo = "Error al obtener listado de imagenes";
			titulo = "Error while obtaining images list";
			//mensaje = "No se encuentran imagenes disponibles en el servidor";
			mensaje = "No available images found in the server";

			Dialogos::dialogoError(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo))
		{
			interfazGovocitos->menuPreferencias();
		}
	}
	
	return false;
}

/**
 Abre un fichero xml de celulas que se encuentra en un servidor remoto.
 */
bool CoreGovocitos::AbrirXmlRemotoBD()
{
	ConexionBD *conMysql;
	int xmlSeleccionada;
	DataImage *xmlDescarga;
	string xmlDes;
	DialogoRemoto *dialAbrirR;
	ListadoImagenes *listimag;
	ImageCells *imgActual;
	SistemaDibujado *paintSystem;
	
	paintSystem = modeloGovocitos->getSistemaDibujado();
	listimag = modeloGovocitos->getListaImagenes();
	imgActual = modeloGovocitos->getImageActual();
	conMysql = modeloGovocitos->getConexionMySql();

	modeloGovocitos->setNuevaListaImagenes();

	listimag = modeloGovocitos->getListaImagenes();
	
	if(conMysql->obtenerImagenes(*listimag))
	{
		//dialAbrirR = new DialogoRemoto("Abrir xml BD", *listimag);
		dialAbrirR = new DialogoRemoto("Open DB Xml", *listimag);
		
		if(dialAbrirR->abreDialogoRemoto(xmlSeleccionada, false))
		{
			delete dialAbrirR;
			
			modeloGovocitos->setNuevasCelulas();
			paintSystem->getCapaCelula()->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());
						
			xmlDescarga = listimag->getImagenVector(xmlSeleccionada);

			//Obtenemos el nombre del xml a descargar
			xmlDes = xmlDescarga->getNombreXml();
			imgActual->setNombreXml(xmlDes);
		
			/*Obtenemos el fichero y si la descarga es correcta se procedera
			a la apertura de la imagen en caso contrario se mostrara un 
			mensaje de error*/
			HttpsConexion *conexionImagenes;
			conexionImagenes = modeloGovocitos->getConexionBD();
			
			if(conexionImagenes->descargaFicheroXml(xmlDescarga))
			{
				cargaDatosCelulas(Utiles::direccionCache(xmlDes));;
	
				//Comenzamos el dibujado
				interfazGovocitos->getPanelDibujado()->actualizarVista();
	
				//Comprobamos si hay clases o estados
				interfazGovocitos->mensajeSinClasesEstados();

				//Borramos el xml del sistema
				Fichero::borraImagenSistema(Utiles::direccionCache(xmlDes));

				interfazGovocitos->setCambios(true);
			
				//Vaciar las pilas
				modeloGovocitos->setNuevaPilaDeshacer();
				modeloGovocitos->setNuevaPilaRehacer();

				return true;
			}
			else
			{
				string titulo, mensaje;

				//titulo = "Error al obtener la imagen";
				titulo = "Error while obtaining the image";
				//mensaje = "La imagen descargada no coincide con la almacenada";
				mensaje = "The system can´t locate the file.";

				Dialogos::dialogoError(mensaje, titulo);

				return false;
			}
		}
		else
		{
			delete dialAbrirR;
			
			string titulo, mensaje;

			//titulo = "Selección de células";
			titulo = "Cell selection";
			//mensaje = "No se ha seleccionado ninguna Archivo de células";
			mensaje = "No cells file selected";

			Dialogos::dialogoAdvertencia(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo))
		{
			interfazGovocitos->menuPreferencias();
		}
	}
	
	return false;
}			 

/**
 Abre una imagen y su correspondiente fichero xml de celulas que se encuentran
 en un servidor remoto.
 */
bool CoreGovocitos::AbrirXmlRemotoImgPre()
{
	HttpsConexion *conexionImagenes;
	string xmlDes;
	ImageCells *imgActual;
	
	conexionImagenes = modeloGovocitos->getConexionBD();
	imgActual = modeloGovocitos->getImageActual();

	xmlDes = imgActual->getNombreXml();
	/*Obtenemos el fichero y si la descarga es correcta se procedera
	a la apertura de la imagen en caso contrario se mostrara un 
	mensaje de error*/
	if(xmlDes != "")
	{
		if(conexionImagenes->descargaFicheroXml(imgActual))
		{
			cargaDatosCelulas(Utiles::direccionCache(xmlDes));;

			//Comenzamos el dibujado
			interfazGovocitos->getPanelDibujado()->actualizarVista();

			//Comprobamos si hay clases o estados
			interfazGovocitos->mensajeSinClasesEstados();

			//Borramos el xml del sistema
			Fichero::borraImagenSistema(Utiles::direccionCache(xmlDes));

			interfazGovocitos->setCambios(true);
			
			//Vaciar las pilas
			modeloGovocitos->setNuevaPilaDeshacer();
			modeloGovocitos->setNuevaPilaRehacer();
			
			return true;
		}
		else
		{
			string titulo, mensaje;

			//titulo = "Error al obtener la imagen";
			titulo = "Error while obtaining the image";
			//mensaje = "La imagen descargada no coincide con la almacenada";
			mensaje = "The system can´t locate the file.";

			Dialogos::dialogoError(mensaje, titulo);

			return false;
		}
	}
	else
	{
		//string texto = "No se ha encontrado su archivo de células";
		//string titulo = "Error al cargar las células";
		string texto = "Cell file not found";
		string titulo = "Error while loading cell file";

		Dialogos::dialogoError(texto, titulo);

		return false;
	}

	return false;
}

/**
 Abre un individuo y lanza el calculo de su fecundidad.
 */
bool CoreGovocitos::AbrirIndividuoBD()
{
	ConexionBD *conMysql;
	vector<ListadoIndividuo> vectorlistIndividuo;
	ListadoIndividuo *listIndividuo;
	DialogoIndividuo *dialogInd;
	int indivSeleccion;

	//Recreamos los objetos necesarios para el calculo de fecundidad
	modeloGovocitos->setNuevoCalculoFecundidad();
	modeloGovocitos->setNuevoListadoIndividuo();
	modeloGovocitos->setNuevoListaResultadosImg();
	conMysql = modeloGovocitos->getConexionMySql();

	if(conMysql->obtenerIndividuo(vectorlistIndividuo))
	{
		//dialogInd = new DialogoIndividuo("Individuos BD", vectorlistIndividuo);
		dialogInd = new DialogoIndividuo("DB Individuals", vectorlistIndividuo);
		
		if(dialogInd->abreDialogoIndividuo(indivSeleccion))
		{
			delete dialogInd;
			
			listIndividuo = modeloGovocitos->getListadoIndividuo();
			
			*listIndividuo = vectorlistIndividuo[indivSeleccion];
			
			if(listIndividuo->getNumXmlAnalizados())
			{
				HttpsConexion *conexionImagenes;
				int numIndividuosXml;
				string nombreXml;
				string nombreImg;
				ImageCells *imgActual;
				int auxCalibracion;

				auxCalibracion = 0;
				numIndividuosXml = listIndividuo->getTamanhoVectorImag();
				conexionImagenes = modeloGovocitos->getConexionBD();
				
				for(int i = 0; i < numIndividuosXml; i++)
				{	
					ListadoCelulas lc;

					imgActual = listIndividuo->getImagenVector(i);
					nombreXml = imgActual->getNombreXml();
					nombreImg = imgActual->getNombreImg();

					if(!auxCalibracion)
					{
						auxCalibracion = Utiles::doubleToIntWhichAllCharacter(imgActual->getCalibracionImg());
					}
					else 
					{
						if(auxCalibracion != Utiles::doubleToIntWhichAllCharacter(imgActual->getCalibracionImg()))
						{
							string titulo, mensaje;

							//titulo = "Panel Individuos";
							titulo = "Individuals Panel";
							mensaje = "The calibration is not the same for all images.";

							Dialogos::dialogoAdvertencia(mensaje, titulo);

							return false;
						}
					}
					if(nombreXml != "")
					{
						if(conexionImagenes->descargaFicheroXml(imgActual))
						{
							Fichero::leerFichXml(Utiles::direccionCache(nombreXml), lc);
							listIndividuo->setCelulasImagen(lc);
						}
						else
						{
							string titulo, mensaje;

							//titulo = "Panel Individuos";
							titulo = "Individuals Panel";
							mensaje = "The system can not locate the xml file at the server";

							Dialogos::dialogoAdvertencia(mensaje, titulo);

							return false;
						}
						if(conexionImagenes->descargaImagen(imgActual))
						{
							imgActual->setRutaImg(Utiles::direccionCacheReduced(nombreImg));

							imgActual->cargaImagenReducida();
							Fichero::borraImagenSistema(Utiles::direccionCacheReduced(nombreImg));
						}
						else
						{
							string titulo, mensaje;

							//titulo = "Panel Individuos";
							titulo = "Individuals Panel";
							mensaje = "The system can not locate the reduced image file at the server";

							Dialogos::dialogoAdvertencia(mensaje, titulo);

							return false;
						}
					}
					else
					{
						listIndividuo->borraImagenVector(i);
					}
				}

				//Cargamos la calibracion de la ultima imagen cargada para la fecundidad
				cargaValorMicrasSistema();
				
				//Lanzamos el calculo de fecundidad
				if(!calculoFecundidad())
				{
					return false;
				}
			}
			else
			{
				string titulo, mensaje;

				//titulo = "Panel Individuos";
				titulo = "Individuals Panel";
				//mensaje = "El individuo seleccionado no tiene asociado ningun fichero de celulas";
				mensaje = "The selected individual has no related cell file";

				Dialogos::dialogoAdvertencia(mensaje, titulo);

				return false;
			}
		}
		else
		{
			delete dialogInd;
			
			string titulo, mensaje;

			//titulo = "Panel Individuos";
			titulo = "Individuals Panel";
			//mensaje = "El individuo seleccionado no tiene asociado ningun fichero de celulas";
			mensaje = "You need to select a individual.";

			Dialogos::dialogoAdvertencia(mensaje, titulo);

			return false;
		}
	}
	else
	{
		string titulo, mensaje;

		//titulo = "Panel Individuos";
		titulo = "Individuals Panel";
		//mensaje = "El individuo seleccionado no tiene asociado ningun fichero de celulas";
		mensaje = "The data base system don´t have individuals";

		Dialogos::dialogoAdvertencia(mensaje, titulo);

		return false;
	}
	
	return true;
}

/**
 Guarda el fichero de las celulas de la imagen actual.
 @param ruta, string que contiene la ruta donde se almacenara el fichero xml.
 @param terminacion, string que contiene la terminacion del fichero.
 */
void CoreGovocitos::guardarCelulas(const string &ruta,const string &terminacion)
{
	if(terminacion == "xml")
	{
		Fichero::escribFichXml(ruta, *modeloGovocitos->getListaCelulas());
	}
	else
	{
		Fichero::escribFich(ruta, *modeloGovocitos->getListaCelulas());
	}
}

/**
 */
bool CoreGovocitos::guardarCelulasBD()
{
	ConexionBD *conMysql;
	SftpConexion *conSftp;
	ImageCells *imgActual;
	string pathFich;
	bool toret = true; 

	imgActual = modeloGovocitos->getImageActual();
	conSftp = modeloGovocitos->getConexionSftp();
	conMysql = modeloGovocitos->getConexionMySql();

	if(!Fichero::compruebaFich(imgActual->getRutaXmlImg()))
	{
		pathFich = Utiles::direccionCache(imgActual->getNombreImg() + ".xml");
		Fichero::escribFichXml(pathFich, *modeloGovocitos->getListaCelulas());
		imgActual->setRutaXmlImg(pathFich);
		imgActual->setNombreXml(imgActual->getNombreImg() + ".xml");
	}

	if(!conMysql->actualizarXMLPath(*imgActual, *conSftp))
	{
		toret = false;
	}

	Fichero::borraImagenSistema(pathFich);
	
	//Borramos los path de test
	int numXmlTest;
	vector<string> auxPath;
	
	auxPath = imgActual->getXmlTest();
	numXmlTest = auxPath.size();
	
	for(int i = 0; i < numXmlTest; i++)
	{
		Fichero::borraImagenSistema(auxPath[i]);
	}

	imgActual->vaciaXmlTest();
	imgActual->vaciaNombreXmlTest();
	
	modeloGovocitos->setNuevoConexionSftp();
	
	return toret;
}

/**
 Cierra la imagen actual cargada en el sistema e inicializa el sistema al momento
 inicial.
 */
void CoreGovocitos::cerrarImagen()
{
	modeloGovocitos->getRejilla()->setVisibleCapaRejilla(false);
	modeloGovocitos->getRejilla()->setBordeComp(false);
	
	modeloGovocitos->setNuevaImagen();
	modeloGovocitos->setNuevasCelulas();
	
	modeloGovocitos->setNuevaPilaDeshacer();
	modeloGovocitos->setNuevaPilaRehacer();

	modeloGovocitos->setNuevoDeteccionAut();
	
	//iniciamos todo el sistema
	inicializaSistema();

	compruebaConectividadBD(true);
}

/**
 Deshace los cambios realizados en las celulas.
 */
void CoreGovocitos::operacionDesHacer()
{
	DibujadoCelula *capaCelula;
	PanelDibujado *panelDibujo;
	DesReHacer *deshacer, *rehacer;
	ListadoCelulas *poligonosCell;
	MenuBarraPrincipal *menBarPrincipal;

	capaCelula = modeloGovocitos->getSistemaDibujado()->getCapaCelula();
	panelDibujo = interfazGovocitos->getPanelDibujado();
	deshacer = modeloGovocitos->getDeshacer();
	rehacer = modeloGovocitos->getRehacer();
	poligonosCell = modeloGovocitos->getListaCelulas();
	menBarPrincipal = interfazGovocitos->getMenuBarraPrincipal();
		
	if(capaCelula->getNumsCelulaSeleccionada())
	{
		capaCelula->vaciaVectorCelulaSeleccionada();
	}
	if(capaCelula->getTamanhoNuevaCelula() && interfazGovocitos->getPanelPropiedades()->getAnhadirCelPT())
	{
		capaCelula->borrarCelulaNueva();
		
		if(deshacer->pilaVacia())
		{
			menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer");
		}

		//Actualizamos la vista
		panelDibujo->actualizarVista();
	}
	else if(!deshacer->pilaVacia())
	{	
		if(!capaCelula->getSeccionBorrada())
		{	
			//Introducimos el objeto en la pila rehacer
			rehacer->metePilaOper(*poligonosCell);
			
			menBarPrincipal->setSensitiveOpcMenu("SubMenuRehacer", true);
		}
		else
		{
			capaCelula->destruyeDatos();
		}
		
		//Recuperamos el momento anterior
		*poligonosCell = deshacer->sacaPilaOper();
	
		//Borramos el elemento de la pila
		deshacer->borraElemento();
		
		if(deshacer->pilaVacia())
		{
			menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer");
		}
		//Actualizamos la vista
		panelDibujo->actualizarVista();
	}
}

/**
 Rehace los cambios realizados en las celulas.
 */
void CoreGovocitos::operacionReHacer()
{
	DesReHacer *deshacer, *rehacer;
	ListadoCelulas *poligonosCell;
	MenuBarraPrincipal *menBarPrincipal;

	deshacer = modeloGovocitos->getDeshacer();
	rehacer = modeloGovocitos->getRehacer();
	poligonosCell = modeloGovocitos->getListaCelulas();
	menBarPrincipal = interfazGovocitos->getMenuBarraPrincipal();
		
	if(!rehacer->pilaVacia())
	{
		//Introducimos el objeto en la pila deshacer
		deshacer->metePilaOper(*poligonosCell);
		//Recuperamos el momento anterior
		*poligonosCell = rehacer->sacaPilaOper();
		menBarPrincipal->setSensitiveOpcMenu("SubMenuDeshacer", true);
		//Borramos el elemento de la pila
		rehacer->borraElemento();
		if(rehacer->pilaVacia())
		{
			menBarPrincipal->setSensitiveOpcMenu("SubMenuRehacer");
		}
		//Actualizamos la vista
		interfazGovocitos->getPanelDibujado()->actualizarVista();
	}
}

/**
 Lanza el calculo de diametros.
 */
void CoreGovocitos::calculoDiametros()
{
	PanelDiametros *pDiametros;
	
	pDiametros = interfazGovocitos->getPanelDiametros();

	pDiametros->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());
}

/**
 Lanza el calculo de los datos estadisticos.
 */
void CoreGovocitos::calculoDatosEstadisticos()
{
	PanelDatosEstadisticos *pEstadisticos;

	pEstadisticos = interfazGovocitos->getPanelEstadisticos();

	pEstadisticos->setListaCelulas(*modeloGovocitos->getListaCelulas());

	modeloGovocitos->getRejilla()->setEstado(*modeloGovocitos->getConfiguracion()->getDatosEstados());
}

/**
 Aumenta el zoom de la imagen.
 */
bool CoreGovocitos::aumentaZoom()
{
	int valorZoom;
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();

	valorZoom = paintSystem->getZoom();

	if(valorZoom < 10)
	{
		valorZoom++;

		paintSystem->zoomImagen(valorZoom);

		if(valorZoom == 10)
		{
			return true;
		}
	}

	return false;
}

/**
 Disminuye el zoom de la imagen.
 */
bool CoreGovocitos::disminuyeZoom()
{	
	int valorZoom;
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();

	valorZoom = paintSystem->getZoom();

	if(valorZoom > 1)
	{
		valorZoom--;

		paintSystem->zoomImagen(valorZoom);

		if(valorZoom == 1)
		{
			return true;
		}
	}

	return false;
}

/**
 Establece el zoom de la imagen al valor inicial de la imagen.
 */
void CoreGovocitos::zoomOriginal()
{
	modeloGovocitos->getSistemaDibujado()->zoomImagen(10);
}

/**
 Establece el zoom de la imagen al tamaño de la ventana.
 @param wid, Gtk::Widget de la ventana principal.
 @return float, valor del zoom.
 */
float CoreGovocitos::zoomVentana(Gtk::Widget *wid)
{
	float valorZoom;
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	
	paintSystem->zoomImagenVentana((wid->get_width() - 10), (wid->get_height() - 10));
		
	valorZoom = paintSystem->getZoom();

	return valorZoom;
	
}

/**
 Carga los datos de las celulas que se encuentran en el fichero cuya ruta coincide
 con rutaCoord.
 @param rutaCoord, string que contiene la ruta del fichero de celulas.
 */
void CoreGovocitos::cargaDatosCelulas(const string &rutaCoord)
{
	string terminacion;
	
	terminacion = Utiles::obtieneTipoArch(rutaCoord);
	
	//Cargamos el fichero en el objeto de la clase OperPoligonos
	//Comprobamos si es xml o txt
	if(terminacion == "xml")
	{
		Fichero::leerFichXml(rutaCoord, *modeloGovocitos->getListaCelulas());
	}
	else if(terminacion == "txt")
	{
		Fichero::leerFich(rutaCoord, *modeloGovocitos->getListaCelulas());
	}
}

/**
 Combrueba la conectividad con el servidor de BD.
 @param cond, bool por defecto es falso, en caso de verdadero no se lanza el menu
 de preferencias.
 @return bool, devuelve verdadero si se puede conectar con el servidor de BD y falso
 en caso contrario.
 */
bool CoreGovocitos::compruebaConectividadBD(bool cond)
{
	ConexionBD *conMysql;

	conMysql = modeloGovocitos->getConexionMySql();

	if(conMysql->comprobarConectividad())
	{
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor", true);

		return true;
	}
	else
	{
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor");
			
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo) && !cond)
		{
			interfazGovocitos->menuPreferencias();
		}

		return false;
	}
}		

/**
 Actualiza las clases y los estados de las preferencias desde mysql y comprueba 
 que las clases y estados no existan ya en el sistema.
 */
void CoreGovocitos::updateClaseEstadoBD()
{
	ConexionBD *conMysql;
	vector<ClaseCelula> clCell;
	vector<EstadoCelula> estCell;

	conMysql = modeloGovocitos->getConexionMySql();
	
	if(conMysql->obtenerClase(clCell) && conMysql->obtenerEstado(estCell))
	{
		vector<ClaseCelula> *claseGovocitos;
		vector<EstadoCelula> *estadoGovocitos;
		int j, numClase, numClaseFile, numEstado, numEstadoFile;
		bool nuevaEstCl = false;

		//cargamos clases del fichero
		claseGovocitos = modeloGovocitos->getConfiguracion()->getDatosClases();
		estadoGovocitos = modeloGovocitos->getConfiguracion()->getDatosEstados();
		
		numClase = clCell.size();
		numClaseFile = claseGovocitos->size();
		
		for(int i = 0; i < numClase; i++)
		{
			j = 0;

			if(numClaseFile)
			{
				while(j < numClaseFile && clCell[i].getEtiquetaClasificacion() != (*claseGovocitos)[j].getEtiquetaClasificacion())
				{
					j++;
				}

				if(clCell[i].getEtiquetaClasificacion() == (*claseGovocitos)[j].getEtiquetaClasificacion())
				{
					(*claseGovocitos)[j].setNombreClasificacion(clCell[i].getNombreClasificacion());
					(*claseGovocitos)[j].setDescripcionClasificacion(clCell[i].getDescripcionClasificacion());
				}
				else
				{
					claseGovocitos->push_back(clCell[i]);
					nuevaEstCl = true;
				}
			}
			else
			{
				claseGovocitos->push_back(clCell[i]);
				nuevaEstCl = true;
			}
		}	

		numEstado = estCell.size();
		numEstadoFile = estadoGovocitos->size();
		
		for(int i = 0; i < numEstado; i++)
		{
			j = 0;

			if(numEstadoFile)
			{
				while(j < numEstadoFile && estCell[i].getEtiquetaClasificacion() != (*estadoGovocitos)[j].getEtiquetaClasificacion())
				{
					j++;
				}

				if(estCell[i].getEtiquetaClasificacion() == (*estadoGovocitos)[j].getEtiquetaClasificacion())
				{
					(*estadoGovocitos)[j].setNombreClasificacion(estCell[i].getNombreClasificacion());
					(*estadoGovocitos)[j].setDescripcionClasificacion(estCell[i].getDescripcionClasificacion());
				}
				else
				{
					estadoGovocitos->push_back(estCell[i]);
					nuevaEstCl = true;
				}
			}
			else
			{
				estadoGovocitos->push_back(estCell[i]);
				nuevaEstCl = true;
			}
		}

		//Guardamos la configuracion

		modeloGovocitos->getConfiguracion()->escribirFicherosConf();
		if(nuevaEstCl)
		{
			string mensaje, titulo;

			//mensaje = "Se han detectado nuevas clases/estados en el sistema. Pulse Aceptar para continuar";
			mensaje = "New Classes/States detected in the system. Click OK to continue, and if you want to configure it, go to the Preferences panel";
			//titulo = "Descarga de Clases y Estados";
			titulo = "Downloading Classes and States";

			Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
		}
	}
}

/**
 Obtiene las rejillas definidas en el servidor.
 */
void CoreGovocitos::updateRejillasBD()
{
	ConexionBD *conMysql;
	vector<OpcionesRej> *opcRej;
	vector<OpcionesRej> opcRejBD;
	int numRejBD, numRej;

	opcRej = modeloGovocitos->getConfiguracion()->getDatosRejilla();
	conMysql = modeloGovocitos->getConexionMySql();

	conMysql->consultaRejillas(opcRejBD);
	numRejBD = opcRejBD.size();
	numRej = opcRej->size();
	
	for(int i = 0; i < numRejBD; i++)
	{
		if(numRej)
		{
			int j = 0;
		
			while(j < numRej && (*opcRej)[j].getID() != opcRejBD[i].getID())
			{
				j++;
			}

			if((*opcRej)[j].getID() != opcRejBD[i].getID())
			{
				opcRej->push_back(opcRejBD[i]);
			}
		}
		else
		{
			opcRej->push_back(opcRejBD[i]);
		}
	}
}

/**
 Hace sensible deshacer.
 */
void CoreGovocitos::setSensibleDesHacer()
{
	DesReHacer *deshacer, *rehacer;

	deshacer = modeloGovocitos->getDeshacer();
	rehacer = modeloGovocitos->getRehacer();

	if(deshacer->pilaVacia())
	{
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubMenuDeshacer", true);
	}
	if(!rehacer->pilaVacia())
	{
		rehacer->vaciar();
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubMenuRehacer");
	}				
}

/**
 Guarda los datos del poligono en la pila deshacer para su posterior recuperacion 
 frente a cambios.
 */
void CoreGovocitos::guardaModificacionDeshacer()
{
	DesReHacer *deshacer, *rehacer;
	ListadoCelulas *poligonosCell;

	deshacer = modeloGovocitos->getDeshacer();
	rehacer = modeloGovocitos->getRehacer();
	poligonosCell = modeloGovocitos->getListaCelulas();
	
	deshacer->metePilaOper(*poligonosCell);

	if(!interfazGovocitos->getCambios())
	{
		interfazGovocitos->setCambios(true);
	}
	
	if(!rehacer->pilaVacia())
	{
		rehacer->vaciar();
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubMenuRehacer");
	}
	if(!deshacer->pilaVacia())
	{
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubMenuDeshacer", true);
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubCalcularDiam", true);
	}
	
	if(!interfazGovocitos->getPanelDibujado()->getActivaDetecSupervis())
	{
		//Habilitamos el menu de deteccion automatica 	 
	    interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("SubMenuClasificacion", true);
	}
}

/**
 Lanza el detector automatico de bordes de las celulas contenidas en la imagen actual.
 */
void CoreGovocitos::deteccionBordesImagen()
{
	SistemaDibujado *paintSystem;
	ImageCells *imgActual;
	ListadoCelulas *poligonosCell;
	DeteccionAut *detec;
	string ruta;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	
	//Establecemos las nuevas celulas
	modeloGovocitos->setNuevasCelulas();

	//Pasamos una referencia a las clases para que maneje el vector de poligonos
	paintSystem->getCapaCelula()->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());

	//Vaciar las pilas
	modeloGovocitos->setNuevaPilaDeshacer();
	modeloGovocitos->setNuevaPilaRehacer();

	interfazGovocitos->getPanelDibujado()->setActivaDetecSupervis(true);
	
	guardaModificacionDeshacer();
		
	//obtenemos referencias de los objetos
	imgActual = modeloGovocitos->getImageActual();
	poligonosCell = modeloGovocitos->getListaCelulas();
	detec = modeloGovocitos->getDeteccionAut();

	//Obtenemos los diametros max y min
	detec->setDiametrosMaxMin(imgActual->getDiametroMax(), imgActual->getDiametroMin());
	
	//Guardamos la imagen actual en bmp para que la lea el clasificador
	ruta = Utiles::direccionCache(imgActual->getNombreImg() + ".bmp");

	imgActual->getImagenCelulas()->save(ruta, "bmp");

	if (Glib::file_test(ruta, Glib::FILE_TEST_EXISTS))
	{
		//Asignamos datos al objeto de deteccion
		detec->setRutaImagen(ruta);
		detec->setListadoCelulas(*poligonosCell);

		//Lamamos al algoritmos de deteccion automatica con el diam max y min
		if(detec->deteccionBordesNoSupervisado())
		{
			/******************************************************************/
			//Guardar XML1
			
			guardarXMLIntermedios("-XML1");
			/******************************************************************/
			
			//Borramos el bmp creado para la deteccion
			Fichero::borraImagenSistema(ruta);
			
			//Actualizamos la vista
			interfazGovocitos->getPanelDibujado()->actualizarVista();
			
			//Lanzamos el cuadro de dialogo de seleccion de tarea
			Gtk::Dialog *SelecDialog;
			Gtk::RadioButton *seleDialogCells, *seleDialogMD, *finalizarDetec;

			Utiles::getWidgetGlade(Utiles::getGladeFile("SelecAccionDetec.glade"), "SelecDialog", 
			                       "SelecDialog", &SelecDialog,
			                       "seleDialogCells", &seleDialogCells,
			                       "seleDialogMD", &seleDialogMD,
			                       "finalizarDetec", &finalizarDetec,
			                       NULL);

			SelecDialog->add_button(Gtk::Stock::APPLY, Gtk::RESPONSE_OK);
			
			int opcion = SelecDialog->run();
	
			//Seleccion de opcion -Abrir o Cancelar
			switch(opcion)
			{
				case(Gtk::RESPONSE_OK):
				{
					if(seleDialogCells->get_active())
					{
						modeloGovocitos->setNuevasCelulas();
						poligonosCell = modeloGovocitos->getListaCelulas();
						
						paintSystem->getCapaCelula()->setCoordenadasPoligonos(*poligonosCell);
						detec->setListadoCelulas(*poligonosCell);

						//Actualizamos la vista
						interfazGovocitos->getPanelDibujado()->actualizarVista();
						
						//Ocultamos el dialogo
						SelecDialog->hide();

						//Lanzamos el sistema supervisado
						string texto = "You need to markup all the cells that you like to detect. When you finish push key F7 to release";
						string titulo = "Oocyte edge detection";
						Dialogos::dialogoAdvertencia(texto, titulo);
					}
					else if(seleDialogMD->get_active())
					{
						interfazGovocitos->getPanelDibujado()->setActivaDetecSupervis(false);
						SelecDialog->hide();

						interfazGovocitos->barraNoSupervised();
					}
					else if(finalizarDetec->get_active())
					{
						interfazGovocitos->getPanelDibujado()->setActivaDetecSupervis(false);
						SelecDialog->hide();

						interfazGovocitos->finalizarDeteccionaAutomactica();
					}
				}
			}
			
		}
	}
	else
	{
		string texto = "The selected image was not found in system file";
		string titulo = "File error";
		Dialogos::dialogoError(texto, titulo);
	}
}

/**
 Lanza los algoritmos de deteccion automatica de bordes supervisada.
 */
void CoreGovocitos::deteccionBordesSupervised()
{
	ListadoCelulas *poligonosCell;
	DibujadoCelula *dibujCel;
	DeteccionAut *detec;
		
	//obtenemos referencias de los objetos
	poligonosCell = modeloGovocitos->getListaCelulas();
	dibujCel = interfazGovocitos->getPanelDibujado()->getCapaCelula();

	//Declaramos el objeto de deteccion
	detec = modeloGovocitos->getDeteccionAut();
	detec->setListadoCelulas(*poligonosCell);
		
	//Lamamos al algoritmos de deteccion automatica supervisada
	detec->deteccionBordesSupervisado(dibujCel->getNuevaCelulaX(), dibujCel->getNuevaCelulaY());

	//Borramos la celula utilizada
	dibujCel->borrarCelulaNueva();

	//Reiniciamos el objeto de deteccion automatica
	modeloGovocitos->setNuevoDeteccionAut();

	/******************************************************************/
	//Guardar XML3	
	
	guardarXMLIntermedios("-XML3");
	/******************************************************************/
}

/**
 Lanza el clasificador automatico de estados y clases para la imagen actual.
 */
void CoreGovocitos::clasificacionEstClAutomatica()
{
	ImageCells *imgActual;
	ListadoCelulas *poligonosCell;
	Clasificador *clasificador;
	string ruta;
	
	imgActual = modeloGovocitos->getImageActual();
	poligonosCell = modeloGovocitos->getListaCelulas();

	guardaModificacionDeshacer();

	//Obtenemos la especie para asignar ficheros al clasificador
    if(imgActual->getSpecieImage () == "mz" )
    {
		//Creamos el clasificador para merluza
		clasificador = new Clasificador(Utiles::getClasificadorFile("fich_svm_clasif_estados_glrls_a0.dat", "merluza"),
			                            Utiles::getClasificadorFile("fich_med_desv_estados_glrls_a0.dat", "merluza"),
	    		                        Utiles::getClasificadorFile("fich_svm_clasif_clases_glrls_a0.dat", "merluza"),
	        		                    Utiles::getClasificadorFile ("fich_med_desv_clases_glrls_a0.dat", "merluza"));
	}
	else if(imgActual->getSpecieImage () == "tl" )
    {
		//Creamos el clasificador para faneca
		clasificador = new Clasificador(Utiles::getClasificadorFile("fich_svm_clasif_estados_glrls_a0.dat", "faneca"),
			                            Utiles::getClasificadorFile("fich_med_desv_estados_glrls_a0.dat", "faneca"),
	    		                        Utiles::getClasificadorFile("fich_svm_clasif_clases_glrls_a0.dat", "faneca"),
	        		                    Utiles::getClasificadorFile ("fich_med_desv_clases_glrls_a0.dat", "faneca"));
	}
	else if(imgActual->getSpecieImage () == "ls" )
    {
		//Creamos el clasificador para lusy
		clasificador = new Clasificador(Utiles::getClasificadorFile("fich_svm_clasif_estados_glrls_a0.dat", "lusy"),
			                            Utiles::getClasificadorFile("fich_med_desv_estados_glrls_a0.dat", "lusy"),
	    		                        Utiles::getClasificadorFile("fich_svm_clasif_clases_glrls_a0.dat", "lusy"),
	        		                    Utiles::getClasificadorFile("fich_med_desv_clases_glrls_a0.dat", "lusy"));
	}
	else
	{
		//Creamos el clasificador para merluza
		clasificador = new Clasificador(Utiles::getClasificadorFile("fich_svm_clasif_estados_glrls_a0.dat", "merluza"),
			                            Utiles::getClasificadorFile("fich_med_desv_estados_glrls_a0.dat", "merluza"),
	    		                        Utiles::getClasificadorFile("fich_svm_clasif_clases_glrls_a0.dat", "merluza"),
	        		                    Utiles::getClasificadorFile ("fich_med_desv_clases_glrls_a0.dat", "merluza"));
	}
	
	//Guardamos la imagen actual en bmp para que la lea el clasificador
	ruta = Utiles::direccionCache(imgActual->getNombreImg() + ".bmp");

	imgActual->getImagenCelulas()->save(ruta, "bmp");

	/******************************************************************/
	//Guardar XML4	
	
	guardarXMLIntermedios("-XML4");
	/******************************************************************/
	
	//Ejecutamos el clasificador
	clasificador->clasificarCelulas(ruta, *poligonosCell);

	/******************************************************************/
	//Guardar XML5	

	guardarXMLIntermedios("-XML5");
	/******************************************************************/
	
	//Borramos el bmp creado para la deteccion
	Fichero::borraImagenSistema(ruta);
}

/**
 Guarda la fecundidad de un individuo en la base de datos.
 */
bool CoreGovocitos::guardarFecundidadBD()
{
	ConexionBD *conMysql;
	ListadoIndividuo *listInd;
	ResultFecundidad *resFec;
	vector<EstadoCelula> *estados;

	conMysql = modeloGovocitos->getConexionMySql();
	listInd = modeloGovocitos->getListadoIndividuo();
	resFec = modeloGovocitos->getListaResultadosImg();
	estados = modeloGovocitos->getConfiguracion()->getDatosEstados();

	if(!conMysql->guardarDatosFecundidad(*listInd, *resFec, *estados))
	{
		return false;
	}

	return true;
}

/**
 Guarda las rejillas personalizadas en la bae de datos.
 */
bool CoreGovocitos::guardarRejillaBD()
{
	ConexionBD *conMysql;
	Rejilla *rejilla;
	vector<OpcionesRej> *opcRej;
	int numRej;
	int numCol, numFil, separRej;

	rejilla = modeloGovocitos->getRejilla();
	opcRej = modeloGovocitos->getConfiguracion()->getDatosRejilla();
	conMysql = modeloGovocitos->getConexionMySql();;

	numRej = opcRej->size();
	separRej = rejilla->getSeparPuntos();
	
	if(separRej == 1)
	{
		numCol = rejilla->getAncho();
		numFil = rejilla->getAlto();
	}
	else
	{
		numCol = rejilla->getNumColumnas();
		numFil = rejilla->getNumFilas();
	}
	
	if(conMysql->insertarRejilla(*rejilla, numFil, numCol ,separRej))
	{
		return true;
	}

	return false;
}

/**
 Guarda los ficheros Xml utilizados para realizar la evaluación del los sistemas 
 de detección y clasificacion automatica.
 @param numXml, string que contiene el numero del xml a generar.
 */
void CoreGovocitos::guardarXMLIntermedios(const string &numXml)
{
	string ruta, nombre;
	ImageCells *imgActual;
	ListadoCelulas *listCell;

	imgActual = modeloGovocitos->getImageActual();
	listCell = modeloGovocitos->getListaCelulas();

	nombre = imgActual->getNombreImg() + numXml + ".xml";
	ruta = Utiles::direccionCache(nombre);
	imgActual->addXmlTest(ruta);
	imgActual->addNombreXmlTest(nombre);
	
	Fichero::escribFichXml(ruta, *listCell);
}

/**
 Realiza el calculo de fecundidad del individuo actual y posteriormente lo muestra.
 */
bool CoreGovocitos::calculoFecundidad()
{
	vector<ClaseCelula> *clases;
	vector<EstadoCelula> *estados;
	bool toretCl, toretEst;

	toretCl = false;
	toretEst = false;

	clases = modeloGovocitos->getConfiguracion()->getDatosClases();
	estados = modeloGovocitos->getConfiguracion()->getDatosEstados();

	for(unsigned int i = 0; i < clases->size(); i++)
	{
		if((*clases)[i].getEnUso())
		{
			toretCl = true;
			break;
		}
	}

	for(unsigned int i = 0; i < estados->size(); i++)
	{
		if((*estados)[i].getEnUso())
		{
			toretEst = true;
			break;
		}
	}

	if(toretCl && toretEst)
	{
		ListadoIndividuo *listIndividuo;
		ConexionBD *conMysql;

		listIndividuo = modeloGovocitos->getListadoIndividuo();
		conMysql = modeloGovocitos->getConexionMySql();
	
		//Establecemos el ancho y el alto de la rejilla
		modeloGovocitos->getRejilla()->setAncho(listIndividuo->getImagenVector(0)->getAnchoImg());
		modeloGovocitos->getRejilla()->setAlto(listIndividuo->getImagenVector(0)->getAltoImg());

		//Creamos objetos del calculo de fecundidad y panel fecundidad
		PanelFecundidad *pfecundidad;
		CalculoFecundidad *cfecundidad;

		pfecundidad = interfazGovocitos->getPanelFecundidad();
		cfecundidad = modeloGovocitos->getCalculoFecundidad();
		
		//Activamos el panel fecundidad
		pfecundidad->setActivoPanelFec(true);
	
		//Establecemos objetos para relalizar el calculo de fecundidad
		pfecundidad->setRejilla(*modeloGovocitos->getRejilla());
		pfecundidad->setCalculoFecundidad(*modeloGovocitos->getCalculoFecundidad());
		pfecundidad->setConfiguracion(*modeloGovocitos->getConfiguracion());
		pfecundidad->setListaIndividuos(*listIndividuo);
		pfecundidad->setListaResultadosImg(*modeloGovocitos->getListaResultadosImg());

		cfecundidad->setRejilla(*modeloGovocitos->getRejilla());
		cfecundidad->setListaIndividuos(*listIndividuo);
		cfecundidad->setPanelFecundidad(*pfecundidad);
		cfecundidad->setConfiguracion(*modeloGovocitos->getConfiguracion());
		cfecundidad->setListaResultadosImg(*modeloGovocitos->getListaResultadosImg());

		//Obtenemos los factores de correccion de la especie
		conMysql->obtenerFactoresCorreccion(*cfecundidad, listIndividuo->getImagenVector(0)->getSpecieImage());

		//Lanzamos el calculo de fecundidad
		cfecundidad->calculoPuntosCelulas();
		cfecundidad->calculaValorDeK();
		cfecundidad->calculoAreaRejilla();
		cfecundidad->calculoFecundidad();

		//Mostramos los datos en el treview
		pfecundidad->iniciarTreeViewDatosEstadisticos();

		//Mostramos los resultados finales
		pfecundidad->estableceDatosFecundidad();

		//Mostramos el grafico
		pfecundidad->presentaHistograma();
	
		//Mostramos las imagenes en miniatura
		pfecundidad->cargarImagenesMiniatura();
	}
	else
	{
		string texto, titulo;

		texto = "They aren´t class or states defined in the system, check the preferences";
		titulo = "No class or states found";

		Dialogos::dialogoError(texto, titulo);

		return false;
	}

	return true;
}

/**
 Inicializa todos los objetos del sistema al momento inicial.
 */
void CoreGovocitos::inicializaSistema()
{
	SistemaDibujado *paintSystem;
	PanelDibujado *paintPanel;
	PanelPropiedades *propitiesPanel;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	paintPanel = interfazGovocitos->getPanelDibujado();
	propitiesPanel = interfazGovocitos->getPanelPropiedades();
	
	//Pasamos el panel de dibujo al sistema de dibujo y vicerversa
	paintSystem->setPanelDibujado(*paintPanel);
	paintPanel->setSistemaDibujado(*paintSystem);

	//Pasamos la rejilla al panel de propiedades, al sistema de dibujado y al panel de dibujado
	paintPanel->setRejilla(*modeloGovocitos->getRejilla());
	propitiesPanel->setRejilla(*modeloGovocitos->getRejilla());
	
	//Pasamos clases y estados al dibujado
	paintSystem->getCapaCelula()->setClaseEstado(*modeloGovocitos->getConfiguracion()->getDatosClases(),
	                                             *modeloGovocitos->getConfiguracion()->getDatosEstados());

	//Cargamos las clases en el popup y en el panel propiedades
	paintPanel->menuPopupCelula(modeloGovocitos->getConfiguracion()->getDatosClases(),
	                                                       modeloGovocitos->getConfiguracion()->getDatosEstados());
	propitiesPanel->setConfiguracion(*modeloGovocitos->getConfiguracion());

	//Cargamos la configuracion de preferencias
	paintSystem->cargaOpcionesDibujado(*modeloGovocitos->getConfiguracion()->getDatosPreferencias());

	paintSystem->setImagenOvocito(*modeloGovocitos->getImageActual());

	//Pasamos una referencia a las clases para que maneje el vector de poligonos
	paintSystem->getCapaCelula()->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());	

	//Señales
	paintPanel->signal_cambiar_menu().connect(sigc::mem_fun(this, &CoreGovocitos::setSensibleDesHacer));	
	paintPanel->signal_modificacion_celulas().connect(sigc::mem_fun(this, &CoreGovocitos::guardaModificacionDeshacer));
	propitiesPanel->signal_modifica_classEstado().connect(sigc::mem_fun(this, &CoreGovocitos::guardaModificacionDeshacer));
	paintPanel->signal_modifica_classEstPopup().connect(sigc::mem_fun(this, &CoreGovocitos::guardaModificacionDeshacer));
}

/**
 Carga el valor de micras en el sistema.
 */
void CoreGovocitos::cargaValorMicrasSistema()
{
	double calibracion;

	calibracion = modeloGovocitos->getImageActual()->getCalibracionImg();

	if(calibracion != 0)
	{
		CalculoMorfologico::setCalibracion(calibracion);
		modeloGovocitos->getCalculoFecundidad()->setCalibracion(calibracion);
		modeloGovocitos->getDeteccionAut()->setCalibracion(calibracion);
	}

	
}

/****************************************DEPRECATED*****************************/
/**
 Abre una imagen que se encuentra en el servidor remoto.
 @return bool.
 @deprecated
 */
bool CoreGovocitos::abrirImagenRemota()
{
	HttpsConexion *conexionImagenes;
	ImageCells *imgActual;
	int imagenSeleccionada;
	ListadoCache *listCacheImag;
	string nombreImagen, rutaImagen;
	ListadoImagenes *listimag;
	SistemaDibujado *paintSystem;
	DataImage *imagenDescarga;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	conexionImagenes = modeloGovocitos->getConexionBD();
	listCacheImag = modeloGovocitos->getListadoCache();

	if(conexionImagenes->obtenerDatosServidor("XmlImagenesWeb.xml"))
	{
		modeloGovocitos->setNuevaListaImagenes();

		listimag = modeloGovocitos->getListaImagenes();

		try
		{
			XmlWebImagenes p(*listimag);
			p.set_substitute_entities(true);
			p.parse_file(Utiles::direccionConfig("XmlImagenesWeb.xml"));
		}
		catch(...)
		{
			string mensaje, titulo;

			//mensaje = "Se ha encontrado un error en la lectura del fichero de la base de datos";
			mensaje = "An error occurred while reading the file from the database";
			//titulo = "Fallo al leer el fichero de datos";
			titulo = "Error while reading the data file";

			Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
		}

			if(listimag->getTamanhoVectorImag())
		{
			DialogoRemoto *dialAbrirR;

			//dialAbrirR = new DialogoRemoto("Abrir imagenes BD", *listimag);
			dialAbrirR = new DialogoRemoto("Open DB Images", *listimag);

			if(dialAbrirR->abreDialogoRemoto(imagenSeleccionada))
			{	
				delete dialAbrirR;

				imgActual = modeloGovocitos->getImageActual();

				//Cargamos datos de la imagen
				imagenDescarga = listimag->getImagenVector(imagenSeleccionada);

				//Cargamos datos de la imagen
				imgActual->setMd5Img(imagenDescarga->getMd5Img());
				imgActual->setCalibracionImg(imagenDescarga->getCalibracionImg());
				imgActual->setCampanhaImg(imagenDescarga->getCampanhaImg());
				imgActual->setMuestreoImg(imagenDescarga->getMuestreoImg());
				imgActual->setIndividuoImg(imagenDescarga->getIndividuoImg());
				imgActual->setCodigoImagen(imagenDescarga->getCodigoImagen());
				imgActual->setSpecieImage(imagenDescarga->getSpecieImage());
				imgActual->setNombreXml(imagenDescarga->getNombreXml());
				imgActual->setRutaXmlImg(imagenDescarga->getRutaXmlImg());
			
				//Obtenemos el nombre de la imagen a descargar
				nombreImagen = imagenDescarga->getNombreImgCompleto();

							imgActual->setNombreImg(nombreImagen);

				//Cargamos calibracion
				cargaValorMicrasSistema();

							//Comprobamos si la imagen se encuentra en la cache
				if(listCacheImag->getImagenLista(nombreImagen) == "")
				{
					/*Obtenemos el fichero y si la descarga es correcta se procedera
					a la apertura de la imagen en caso contrario se mostrara un 
					mensaje de error*/
					if(!conexionImagenes->descargaImagen(imagenDescarga))
					{			
						interfazGovocitos->menuCerrar();
						return false;
					}
				}
				rutaImagen = Utiles::direccionCache(nombreImagen);

				imgActual->setRutaImg(rutaImagen);
					
				if(imgActual->cargaImagenEnSistema())
				{
					//Cargar imagen en Gtk::Image e iniciar zoom
					paintSystem->setZoomActual(10);
					paintSystem->setImagen();

					//Añadimos la imagen a la cache
					listCacheImag->addImagenCache(nombreImagen);	
					modeloGovocitos->getConfiguracion()->escribirFicheroCache();

					return true;
				}
				else
				{
					string titulo, mensaje;

					//titulo = "Error al obtener la imagen";
					titulo = "Error while obtaining the image";
					//mensaje = "La imagen descargada no coincide con la almacenada";
					mensaje = "The downloaded image is not the same as the saved one";

					Dialogos::dialogoError(mensaje, titulo);	
				}
			}
			else
			{
				delete dialAbrirR;

								string titulo, mensaje;

				//titulo = "Selección de imagenes";
				titulo = "Image Selection";
				//mensaje = "No se ha seleccionado ninguna imagen";
				mensaje = "No image selected";

				Dialogos::dialogoAdvertencia(mensaje, titulo);
			}
		}
		else
		{
			string titulo, mensaje;

			//titulo = "Error al obtener listado de imagenes";
			titulo = "Error while obtaining images list";
			//mensaje = "No se encuentran imagenes disponibles en el servidor";
			mensaje = "No available images found in the server";

			Dialogos::dialogoError(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo))
		{
			interfazGovocitos->menuPreferencias();
		}
	}

	return false;
}	

/**
 Abre un fichero xml de celulas que se encuentra en un servidor remoto.
 @return bool.
 @deprecated
 */
bool CoreGovocitos::AbrirXmlRemoto()
{
	HttpsConexion *conexionImagenes;
	int xmlSeleccionada;
	DataImage *xmlDescarga;
	string xmlDes;
	DialogoRemoto *dialAbrirR;
	ListadoImagenes *listimag;
	ImageCells *imgActual;
	SistemaDibujado *paintSystem;

	paintSystem = modeloGovocitos->getSistemaDibujado();
	conexionImagenes = modeloGovocitos->getConexionBD();
	listimag = modeloGovocitos->getListaImagenes();
	imgActual = modeloGovocitos->getImageActual();

	if(conexionImagenes->obtenerDatosServidor("XmlImagenesWeb.xml"))
	{		
		modeloGovocitos->setNuevaListaImagenes();

		listimag = modeloGovocitos->getListaImagenes();
		
		try
		{
			XmlWebImagenes p(*listimag);
			p.set_substitute_entities(true);
			p.parse_file(Utiles::direccionConfig("XmlImagenesWeb.xml"));
		}
		catch(...)
		{
			string mensaje, titulo;

			//mensaje = "Se ha encontrado un error en la lectura del fichero de la base de datos";
			mensaje = "An error occurred while reading the file from the database";
			//titulo = "Fallo al leer el fichero de datos";
			titulo = "Error while reading the data file";

			Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
		}
		
		//dialAbrirR = new DialogoRemoto("Abrir xml BD", *listimag);
		dialAbrirR = new DialogoRemoto("Open DB Xml", *listimag);
		
		if(dialAbrirR->abreDialogoRemoto(xmlSeleccionada, false))
		{
			delete dialAbrirR;
			
			modeloGovocitos->setNuevasCelulas();
			paintSystem->getCapaCelula()->setCoordenadasPoligonos(*modeloGovocitos->getListaCelulas());
						
			xmlDescarga = listimag->getImagenVector(xmlSeleccionada);

			//Obtenemos el nombre del xml a descargar
			xmlDes = xmlDescarga->getNombreXml();
			imgActual->setNombreXml(xmlDes);
		
			/*Obtenemos el fichero y si la descarga es correcta se procedera
			a la apertura de la imagen en caso contrario se mostrara un 
			 mensaje de error*/
			if(conexionImagenes->descargaFicheroXml(xmlDescarga))
			{
				cargaDatosCelulas(Utiles::direccionCache(xmlDes));;
	
				//Comenzamos el dibujado
				interfazGovocitos->getPanelDibujado()->actualizarVista();
	
				//Comprobamos si hay clases o estados
				interfazGovocitos->mensajeSinClasesEstados();

				//Borramos el xml del sistema
				Fichero::borraImagenSistema(Utiles::direccionCache(xmlDes));

				interfazGovocitos->setCambios(true);
			
				//Vaciar las pilas
				modeloGovocitos->setNuevaPilaDeshacer();
				modeloGovocitos->setNuevaPilaRehacer();
			}
			return true;
		}
		else
		{
			delete dialAbrirR;
			
			string titulo, mensaje;

			//titulo = "Selección de células";
			titulo = "Cell selection";
			//mensaje = "No se ha seleccionado ninguna Archivo de células";
			mensaje = "No cells file selected";

			Dialogos::dialogoAdvertencia(mensaje, titulo);
		}
	}
	else
	{
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo))
		{
			interfazGovocitos->menuPreferencias();
		}
	}
	
	return false;
}		

/**
 Abre un individuo y lanza el calculo de su fecundidad.
 @return bool.
 @deprecated
 */
bool CoreGovocitos::AbrirIndividuo()
{
	HttpsConexion *conexionImagenes;
	vector<ListadoIndividuo> vectorlistIndividuo;
	ListadoIndividuo *listIndividuo;
	DialogoIndividuo *dialogInd;
	int indivSeleccion;

	//Recreamos los objetos necesarios para el calculo de fecundidad
	modeloGovocitos->setNuevoCalculoFecundidad();
	modeloGovocitos->setNuevoListadoIndividuo();
	modeloGovocitos->setNuevoListaResultadosImg();
	
	conexionImagenes = modeloGovocitos->getConexionBD();

	if(conexionImagenes->obtenerDatosServidor("XmlImagenesWeb.xml"))
	{
		try
		{
			XmlWebIndividuo p(vectorlistIndividuo);
			p.set_substitute_entities(true);
			p.parse_file(Utiles::direccionConfig("XmlImagenesWeb.xml"));
		}
		catch(...)
		{
			string mensaje, titulo;

			//mensaje = "Se ha encontrado un error en la lectura del fichero de la base de datos";
			mensaje = "An error occurred while reading the file from the database";
			//titulo = "Fallo al leer el fichero de datos";
			titulo = "Error while reading the data file";

			Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
		}

		//dialogInd = new DialogoIndividuo("Individuos BD", vectorlistIndividuo);
		dialogInd = new DialogoIndividuo("DB Individuals", vectorlistIndividuo);
		
		if(dialogInd->abreDialogoIndividuo(indivSeleccion))
		{
			delete dialogInd;
			
			listIndividuo = modeloGovocitos->getListadoIndividuo();
			
			*listIndividuo = vectorlistIndividuo[indivSeleccion];


			//Obtenemos scherle, beta, gonada
			if(conexionImagenes->obtenerDatosServidor("XmlFecundidadWeb.xml"))
			{
				try
				{
					XmlWebFecundidad p(*listIndividuo);
					p.set_substitute_entities(true);
					p.parse_file(Utiles::direccionConfig("XmlFecundidadWeb.xml"));
				}
				catch(...)
				{
					string mensaje, titulo;

					//mensaje = "Se ha encontrado un error en la lectura del fichero de la base de datos";
					mensaje = "An error occurred while reading the file from the database";
					//titulo = "Fallo al leer el fichero de datos";
					titulo = "Error while reading the data file";

					Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
				}

				if(listIndividuo->getNumXmlAnalizados())
				{
					int numIndividuosXml;
					string nombreXml;
					string nombreImg;
					ImageCells *imgActual;

					numIndividuosXml = listIndividuo->getTamanhoVectorImag();
				
					for(int i = 0; i < numIndividuosXml; i++)
					{	
						ListadoCelulas lc;

						imgActual = listIndividuo->getImagenVector(i);
						nombreXml = imgActual->getNombreXml();
						nombreImg = imgActual->getNombreImg();
					
						if(nombreXml != "")
						{
							if(conexionImagenes->descargaFicheroXml(imgActual))
							{
								Fichero::leerFichXml(Utiles::direccionCache(nombreXml), lc);
								listIndividuo->setCelulasImagen(lc);
							}
							if(conexionImagenes->descargaImagen(imgActual))
							{
								imgActual->setRutaImg(Utiles::direccionCacheReduced(nombreImg));

								imgActual->cargaImagenReducida();
								Fichero::borraImagenSistema(Utiles::direccionCacheReduced(nombreImg));
							}
						}
						else
						{
							listIndividuo->borraImagenVector(i);
						}
					}

					//Lanzamos el calculo de fecundidad
					calculoFecundidad();
				}
				else
				{
					string titulo, mensaje;

					//titulo = "Panel Individuos";
					titulo = "Individuals Panel";
					//mensaje = "El individuo seleccionado no tiene asociado ningun fichero de celulas";
					mensaje = "The selected individual has no related cell file";

					Dialogos::dialogoAdvertencia(mensaje, titulo);

					return false;
				}
			}
		}
		else
		{
			delete dialogInd;
			
			string titulo, mensaje;

			//titulo = "Selección de individuos";
			titulo = "Individual Selection";
			//mensaje = "No se ha seleccionado ninguna Individuo";
			mensaje = "No selected individual";

			Dialogos::dialogoAdvertencia(mensaje, titulo);

			return false;
		}
	}
	
	return true;
}

/**
 Combrueba la conectividad con el servidor de BD.
 @param cond, bool por defecto es falso, en caso de verdadero no se lanza el menu
 de preferencias.
 @return bool, devuelve verdadero si se puede conectar con el servidor de BD y falso
 en caso contrario.
 @deprecated
 */
bool CoreGovocitos::compruebaConectividad(bool cond)
{
	HttpsConexion *comprobarConexion;
	string conexion;

	comprobarConexion = modeloGovocitos->getConexionBD();
	
	if(comprobarConexion->obtenerDatosServidor("XmlConectividad.xml"))
	{	
		// Parse the entire document in one go:
		#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
		try
		{
		#endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
			XmlConectividad p(conexion);
			p.set_substitute_entities(true);
			p.parse_file(Utiles::direccionConfig("XmlConectividad.xml"));
		#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
		}
		catch(const xmlpp::exception& ex)
		{
			interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor");
			
			string mensaje, titulo;

			//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
			mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
			//titulo = "Conexion Base de Datos";
			titulo = "Database connection";

			if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo) && !cond)
			{
				interfazGovocitos->menuPreferencias();
			}

			return false;
		}
		#endif //LIBXMLCPP_EXCEPTIONS_ENABLED

		if(conexion == "OK")
		{
			interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor", true);

			return true;
		}
		else
		{
			interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor");

			string mensaje, titulo;

			//mensaje = "Usuario/contraseña incorrectos. Para habilitar el servidor de Base de Datos ir al menu de preferencias";
			mensaje = "Wrong user or password. Database server edition in the Preferences menu";
			//titulo = "Conexion Base de Datos";
			titulo = "Database connection";

			if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo) && !cond)
			{
					interfazGovocitos->menuPreferencias();
			}

			return false;
		}
	}
	else
	{
		interfazGovocitos->getMenuBarraPrincipal()->setSensitiveOpcMenu("MenuServidor");
		
		string mensaje, titulo;

		//mensaje = "Se ha encontrado un error en la conexion al servidor de Base de Datos. Compruebe la configuracion de preferencias. Pulse Aceptar para continuar";
		mensaje = "An error occurred while connecting to the database server. Check the configuration in the Preferences section. Click OK to continue";
		//titulo = "Conexion Base de Datos";
		titulo = "Database connection";

		if(Dialogos::dialogoAdvertenciaPref(mensaje, titulo) && !cond)
		{
				interfazGovocitos->menuPreferencias();
		}

		return false;
	}
}

/**
 Actualiza las clases y los estados de las preferencias desde http y comprueba 
 que las clases y estados no existan ya en el sistema.
 @deprecated
 */
void CoreGovocitos::updateClaseEstado()
{
	HttpsConexion *conexionDatos;
	vector<ClaseCelula> clCell;
	vector<EstadoCelula> estCell;
	
	conexionDatos = modeloGovocitos->getConexionBD();

	if(conexionDatos->obtenerDatosServidor("XmlClasesEstados.xml"))
	{
		try
		{
			XmlWebDatos p(clCell, estCell);
			p.set_substitute_entities(true);
			p.parse_file(Utiles::direccionConfig("XmlClasesEstados.xml"));
		}
		catch(const xmlpp::exception& ex)
		{
			//return false;
			//No hay conexion
		}

		vector<ClaseCelula> *claseGovocitos;
		vector<EstadoCelula> *estadoGovocitos;
		int j, numClase, numClaseFile, numEstado, numEstadoFile;
		bool nuevaEstCl = false;

		//cargamos clases del fichero
		claseGovocitos = modeloGovocitos->getConfiguracion()->getDatosClases();
		estadoGovocitos = modeloGovocitos->getConfiguracion()->getDatosEstados();
		
		numClase = clCell.size();
		numClaseFile = claseGovocitos->size();

				for(int i = 0; i < numClase; i++)
		{
			j = 0;

			if(numClaseFile)
			{
				while(j < numClaseFile && clCell[i].getEtiquetaClasificacion() != (*claseGovocitos)[j].getEtiquetaClasificacion())
				{
					j++;
				}

				if(clCell[i].getEtiquetaClasificacion() == (*claseGovocitos)[j].getEtiquetaClasificacion())
				{
					(*claseGovocitos)[j].setNombreClasificacion(clCell[i].getNombreClasificacion());
					(*claseGovocitos)[j].setDescripcionClasificacion(clCell[i].getDescripcionClasificacion());
				}
				else
				{
					claseGovocitos->push_back(clCell[i]);
					nuevaEstCl = true;
				}
			}
			else
			{
				claseGovocitos->push_back(clCell[i]);
				nuevaEstCl = true;
			}
		}	

		numEstado = estCell.size();
		numEstadoFile = estadoGovocitos->size();
		
		for(int i = 0; i < numEstado; i++)
		{
			j = 0;

			if(numEstadoFile)
			{
				while(j < numEstadoFile && estCell[i].getEtiquetaClasificacion() != (*estadoGovocitos)[j].getEtiquetaClasificacion())
				{
					j++;
				}

				if(estCell[i].getEtiquetaClasificacion() == (*estadoGovocitos)[j].getEtiquetaClasificacion())
				{
					(*estadoGovocitos)[j].setNombreClasificacion(estCell[i].getNombreClasificacion());
					(*estadoGovocitos)[j].setDescripcionClasificacion(estCell[i].getDescripcionClasificacion());
				}
				else
				{
					estadoGovocitos->push_back(estCell[i]);
					nuevaEstCl = true;
				}
			}
			else
			{
				estadoGovocitos->push_back(estCell[i]);
				nuevaEstCl = true;
			}
		}

		//Guardamos la configuracion
		modeloGovocitos->getConfiguracion()->escribirFicherosConf();

		if(nuevaEstCl)
		{
			string mensaje, titulo;

			//mensaje = "Se han detectado nuevas clases/estados en el sistema. Pulse Aceptar para continuar";
			mensaje = "New Classes/States detected in the system. Click OK to continue, and if you want to configure it, go to the Preferences panel";
			//titulo = "Descarga de Clases y Estados";
			titulo = "Downloading Classes and States";

			Dialogos::dialogoAdvertenciaPref(mensaje, titulo);
		}
	}
}	
