/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConexionBD.cpp
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jmpintorfreire@gmail.com>
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

#include "ConexionBD.h"

/**
 Constructor, establece los datos principales del servidador de BD como son base
 de datos, url de la base de datos, usuario y contraseña.
 @param opcP, OpcionesPref que contiene los datos de conexion de la bd.
 */
ConexionBD::ConexionBD(OpcionesPref &opcP)
{
	dataBase = opcP.getDataBaseBD();
	urlDataBase = opcP.getDirecBD();
	userDataBase = opcP.getLoginBD();
	passDataBase = opcP.getPassBD();
}

/**
 Destructor.
 */
ConexionBD::~ConexionBD()
{

}

/**
 Comprueba si es posible realizar la conectividad con la Base de datos.
 @return bool, true si es posible conectar con la BD y false en caso contrario.
 */
bool ConexionBD::comprobarConectividad()
{
	mysqlpp::Connection conn(false);
	
    if (conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		return true;
	}

	cerr << "Failed to connect: " << conn.error() << endl;
	return false;
}

/**
 Obtiene los estados de maduración definidos en la base de datos.
 @param est, referencia al vector de objetos de EstadoCelula donde se guardaran los
 estados obtenidos de la Base de datos.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::obtenerEstado(vector<EstadoCelula> &est)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		mysqlpp::Query query = conn.query("select * from estados_madurez");
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{	
            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) 
			{	
				EstadoCelula auxEst;

				auxEst.setEtiquetaClasificacion((string)res[i]["codigo_estado_madurez"]);
				auxEst.setNombreClasificacion((string)res[i]["nombre"]);
				auxEst.setDescripcionClasificacion((string)res[i]["descripcion"]);
				
				est.push_back(auxEst);
			}

			return true;
        }
		else 
		{
            cerr << "Failed to get item list: " << query.error() << endl;
            return false;
        }
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
}

/**
 Obiene las clases que estan almacenadas en la base de datos.
 @param cl, referencia al vector del objeto ClaseCelula que contiene las clases.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::obtenerClase(vector<ClaseCelula> &cl)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		mysqlpp::Query query = conn.query("select * from clases");
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{	
            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) 
			{	
				ClaseCelula auxCl;

				auxCl.setEtiquetaClasificacion((string)res[i]["codigo_clase"]);
				auxCl.setNombreClasificacion((string)res[i]["nombre"]);
				auxCl.setDescripcionClasificacion((string)res[i]["descripcion"]);
				cl.push_back(auxCl);
			}

			return true;
        }
		else 
		{
            cerr << "Failed to get item list: " << query.error() << endl;
            return false;
        }
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
}

/**
 Obtiene las imagenes almacenadas en el servidor de la base de datos.
 @param li, objeto de la clase ListadoImagenes en la que se guardan las imagenes
 obtenidas del servidor.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::obtenerImagenes(ListadoImagenes &lI)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		mysqlpp::Query query = conn.query("select * from imagenes INNER JOIN especies ON especies.codigo_especie = imagenes.codigo_especie");
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{	
            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) 
			{	
				DataImage imagenW;
				size_t found;
				string rutaImagen, rutaXml, codigoCamp, codigoMues, codigoEsp;
			
				//Calculamos la ruta y nombre de la imagen
				rutaImagen = (string)res[i]["path_original"];
				found = rutaImagen.find_last_of("/\\");
				imagenW.setNombreImg(rutaImagen.substr(found+1));			
				imagenW.setRutaImg(rutaImagen.substr(0, found));

				//Calculamos la ruta y nombre del xml
				rutaXml = (string)res[i]["path_ovocitos"];
				found = rutaXml.find_last_of("/\\");
				imagenW.setNombreXml(rutaXml.substr(found+1));
				imagenW.setRutaXmlImg(rutaXml.substr(0, found));				
			
				imagenW.setCalibracionImg(atof(res[i]["calibracion"]));

				codigoCamp = (string)res[i]["codigo_campanha"];
				codigoMues = (string)res[i]["codigo_muestreo"];
				codigoEsp = (string)res[i]["codigo_especie"];
				imagenW.setCampanhaImg(codigoCamp);
				imagenW.setMuestreoImg(codigoMues);
				imagenW.setSpecieImage(codigoEsp);
				imagenW.setIndividuoImg((string)res[i]["codigo_individuo"]);
				imagenW.setCodigoImagen((string)res[i]["codigo_imagen"]);
				imagenW.setMd5Img((string)res[i]["md5"]);
				imagenW.setDiametroMin(atof(res[i]["diametro_min"]));
				imagenW.setDiametroMax(atof(res[i]["diametro_max"]));
				
				lI.setImagenVector(imagenW);
			}

			return true;
        }
		else 
		{
            cerr << "Failed to get item list: " << query.error() << endl;
            return false;
        }
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
}

/**
 Obtiene los individuos definidos en la base de datos del servidor.
 @param li, vector de objetos ListadoIndividuo que contiene los individuos descargados
 de la base de datosCelulas
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::obtenerIndividuo(vector<ListadoIndividuo> &li)
{
	vector<string> almacenados;

	almacenados.clear();

	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentencia;
		size_t i = 0;
		
		sentencia = "SELECT * FROM imagenes INNER JOIN individuos ON individuos.codigo_individuo = imagenes.codigo_individuo ";
		sentencia = sentencia + "AND individuos.codigo_campanha = imagenes.codigo_campanha ";
		sentencia = sentencia + "AND individuos.codigo_muestreo = imagenes.codigo_muestreo ";
		sentencia = sentencia + "AND individuos.codigo_especie = imagenes.codigo_especie ";
		sentencia = sentencia + "INNER JOIN especies ON especies.codigo_especie = imagenes.codigo_especie ";
		sentencia = sentencia + "ORDER BY individuos.codigo_individuo, imagenes.codigo_imagen";
		
		mysqlpp::Query query = conn.query(sentencia);
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{	
			while(i < res.num_rows())
			{
				bool new_individual = false;
				string aux_individual;
				int num_almacenados;
				int index_check = 0;

				string codigoIndividuo, codigoCampanha, codigoMuestreo, codigoEspecie;
				ListadoIndividuo listIndiv;
				
				codigoIndividuo = (string)res[i]["codigo_individuo"];
				codigoCampanha = (string) res[i]["codigo_campanha"];
				codigoMuestreo = (string) res[i]["codigo_muestreo"];
				codigoEspecie = (string) res[i]["codigo_especie"];

				aux_individual = codigoCampanha + codigoEspecie + codigoMuestreo + codigoIndividuo;
				num_almacenados = almacenados.size();
				
				//Comprobamos si no se han introducido ya
				if(num_almacenados == 0)
				{
					new_individual = true;

					almacenados.push_back(aux_individual);
				}
				else
				{
					while((index_check < num_almacenados) && (aux_individual != almacenados[index_check]))
					{
						index_check++;
					}

					if(index_check == num_almacenados && aux_individual != almacenados[index_check - 1])
					{
						new_individual = true;

						almacenados.push_back(aux_individual);
					}
					else
					{
						new_individual = false;
						i++;
					}
				}

				if(new_individual)
				{
					listIndiv.setCampanhaInd(codigoCampanha);
					listIndiv.setMuestreoInd(codigoMuestreo);
					listIndiv.setIndividuoInd(codigoIndividuo);
					listIndiv.setEspecieInd(codigoEspecie);
					listIndiv.setPesoOvarioFresco(atof(res[i]["peso_gonadas_fresco"]));
					listIndiv.setValorBeta(atof(res[i]["uno_beta"]));
					listIndiv.setValorScherle(atof(res[i]["scherle"]));
					listIndiv.setFormolFresco(atof(res[i]["formol_fresco_a"]));

					while((i < res.num_rows()) && (codigoIndividuo == (string)res[i]["codigo_individuo"]) &&
					(codigoCampanha == (string) res[i]["codigo_campanha"]) && (codigoMuestreo == (string) res[i]["codigo_muestreo"]) &&
					(codigoEspecie == (string) res[i]["codigo_especie"]))
					{
						ImageCells imagenW;
						size_t found;
						string rutaImagen, rutaXml;

						//Calculamos la ruta y nombre de la imagen
						rutaImagen = (string)res[i]["path_original"];
						found = rutaImagen.find_last_of("/\\");
						imagenW.setNombreImg(rutaImagen.substr(found+1));
						imagenW.setRutaImg(rutaImagen.substr(0, found));

						//Calculamos la ruta y nombre del xml
						rutaXml = (string)res[i]["path_ovocitos"];
						found = rutaXml.find_last_of("/\\");
						imagenW.setNombreXml(rutaXml.substr(found+1));
						imagenW.setRutaXmlImg(rutaXml.substr(0, found));
						imagenW.setCalibracionImg(atof(res[i]["calibracion"]));

						imagenW.setCampanhaImg(codigoCampanha);
						imagenW.setMuestreoImg(codigoMuestreo);
						imagenW.setSpecieImage(codigoEspecie);
						imagenW.setIndividuoImg(codigoIndividuo);
						imagenW.setCodigoImagen((string)res[i]["codigo_imagen"]);
						imagenW.setMd5Img((string)res[i]["md5"]);
						imagenW.setAltoImg(atoi(res[i]["filas"]));
						imagenW.setAnchoImg(atoi(res[i]["columnas"]));

						//Añadimos la imagen
						listIndiv.setImagenVector(imagenW);

						if(imagenW.getRutaXmlImg() != "NULL")
						{
							listIndiv.incrementaXmlAnalizado();
						}

						if(imagenW.getRutaImg() != "")
						{
							listIndiv.incrementaImagenes();
						}

						i++;
					}
					li.push_back(listIndiv);
				}
			}
        }
		else 
		{
            cerr << "Failed to get item list: " << query.error() << endl;
            return false;
        }
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
	
	return true;
}

/**
 Guarda los datos de fecundidad en la base de datos.
 @param listInd, objeto ListadoIndividuo que contiene el individuo del que se calcula
 la fecundidad.
 @param resF, objeto ResultFecundidad que contiene los resultados de fecundidad obtenidos.
 @param estados, vector de objetos de la clase estados que contiene los estados de 
 maduración.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::guardarDatosFecundidad(ListadoIndividuo &listInd, 
                                        ResultFecundidad &resF,
                                        vector<EstadoCelula> &estados)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		int numEst, codRej;
		vector<EstadoCelula> estAux;
		string codCamp, codMues, codInd, codEsp;

		numEst = estados.size();
		
		for(int i = 0; i < numEst; i++)
		{
			if(estados[i].getEnUso())
			{
				estAux.push_back(estados[i]);
			}
		}
		
		numEst = (int)estAux.size();
		
		codCamp = listInd.getCampanhaInd();
		codMues = listInd.getMuestreoInd();
		codInd = listInd.getIndividuoInd();
		codEsp = listInd.getEspecieInd();
		codRej = resF.getIdRejilla();

		for(int i = 0; i < numEst; i++)
		{
			string sentencia, codEst;
			double fecundidad(0.0);
			
			codEst = estAux[i].getEtiquetaClasificacion();

			fecundidad = resF.getFecundidadEst(i);

			if(fecundidad != 0)
			{
				codEst = estados[i].getEtiquetaClasificacion();
				
				sentencia = "select * from individuos_fecundidad where codigo_campanha = \"" + codCamp +
					"\" AND codigo_muestreo = \"" + codMues + "\" AND codigo_individuo = \"" + codInd + 
					"\" AND codigo_estado_madurez = \"" + codEst + "\" AND codigo_rejilla = \"" +  
					Utiles::converString(codRej) + "\" AND codigo_especie = \"" +  codEsp + "\"";
			
				mysqlpp::Query query = conn.query(sentencia);
				mysqlpp::StoreQueryResult resInd = query.store();
			
				if(!resInd.empty())
				{
					//Update
					if(i < 1)
					{
						string titulo, mensaje;

						titulo = "Save Fecundity BD";
						mensaje = "The actual individual have the fecundity calculate for " + 
							Utiles::converString(resF.getNumImagenes()) + " images are you sure to overwrite it?";

						if(!Dialogos::dialogoConfirmacion(mensaje, titulo))
						{
							return false;
						}
					}
				
					sentencia = "update individuos_fecundidad set fecundidad = \"" + Utiles::converString(fecundidad) + "\"" +
						",k = \"" + Utiles::converString(resF.getValorK()) + "\"" + ",img_usadas = \"" + 
						Utiles::converString(resF.getNumImagenes()) + "\"" + ",fecha_fecundidad = \"" + 
						Utiles::timestamp() + "\"" + ",metodo = \"" + resF.getMetodoCalculo() + "\"" +
						" where codigo_campanha = \"" +  codCamp + "\" AND codigo_muestreo = \"" + codMues +
						"\" AND codigo_individuo = \"" + codInd + "\" AND codigo_estado_madurez = \"" + codEst +
						"\" AND codigo_rejilla = \"" + Utiles::converString(codRej) + "\" AND codigo_especie = \"" +  codEsp + "\"";
				}
				else
				{
					//Insert	
					sentencia = "insert into individuos_fecundidad values (\"" + codCamp + "\",\"" + codEsp + "\",\"" + 
					codMues + "\",\"" + codInd + "\",\"" + Utiles::converString(codRej) + "\",\"" + codEst + "\",\"" + 
					Utiles::converString(fecundidad) + "\",\"" + Utiles::timestamp() + "\",\"" + Utiles::converString(resF.getValorK()) + "\",\"" +
					resF.getMetodoCalculo() + "\",\"" + Utiles::converString(resF.getNumImagenes()) + "\")";
				}
				
				mysqlpp::Query query1 = conn.query(sentencia);

				query1.execute();
			}
		}
		
		return true;
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
}

/**
 Actualiza la información en la base de datos del servidor del fichero de células
 @param image, objeto de la clase ImageCells que contiene la información de la imagen.
 @param conex, objeto de la SftpConexion, contiene los datos de conexion para realizar
 la subida de ficheros al servidor.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::actualizarXMLPath(ImageCells &image, SftpConexion &conex)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentSelect, codInd, codCamp, codImg, codMues;

		codCamp = image.getCampanhaImg();
		codMues = image.getMuestreoImg();
		codInd = image.getIndividuoImg();
		codImg = image.getCodigoImagen();

		sentSelect = "select path_original,path_ovocitos from imagenes where codigo_campanha = \"" +  codCamp + 
		                                  "\" AND codigo_muestreo = \"" + codMues + 
		                                  "\" AND codigo_individuo = \"" + codInd +
		                                  "\" AND codigo_imagen = \"" + codImg + "\"";
		
		mysqlpp::Query query = conn.query(sentSelect);
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{	
			if(res[0]["path_ovocitos"] != "NULL")
			{
				string titulo, mensaje;

				titulo = "Save Xml BD";
				mensaje = "The actual image have a cells files. Are you sure to overwrite?";

				if(!Dialogos::dialogoConfirmacion(mensaje, titulo))
				{
					return false;
				}
				Utiles::actualizarInterfaz();
			}
			
			string rutaXml, sentUpdate;
			size_t found;
				
			//Calculamos la ruta y nombre de la imagen
			rutaXml = (string)res[0]["path_original"];
			found = rutaXml.find_last_of("/");
			rutaXml = rutaXml.substr(0, found);
			rutaXml = rutaXml + "/";

			//Subimos el fichero con el sftp
			if(conex.subirFicheroServidor(rutaXml, image))
			{
				vector<string> nombreXmlTest;
				int numNombreTest;
				
				nombreXmlTest = image.getNombreXmlTest();
				
				numNombreTest = nombreXmlTest.size();
				
				sentUpdate = "update imagenes set path_ovocitos = \"" + rutaXml + image.getNombreXml() +"\"";
						
				for(int i = 0; i < numNombreTest; i++)
				{
					string auxStr;
					size_t found1;
					
					found1 = nombreXmlTest[i].find_last_of(".");
					auxStr = nombreXmlTest[i].substr((found1 - 1), 1);

					sentUpdate = sentUpdate + ", path_xml_paso_" + auxStr + " = \"" + rutaXml + nombreXmlTest[i] + "\"";
					
				}
				
				sentUpdate = sentUpdate + " where codigo_campanha = \"" +  codCamp + 
							                      "\" AND codigo_muestreo = \"" + codMues + 
							                      "\" AND codigo_individuo = \"" + codInd +
							                      "\" AND codigo_imagen = \"" + codImg + "\"";
		
				mysqlpp::Query query1 = conn.query(sentUpdate);

				query1.execute();
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}

	return true;
}

/**
 Inserta una nueva rejilla en la base de datos del servidor.
 @param rej, objeto de la clase Rejilla que contiene la rejilla.
 @param pFila, numero de filas de la rejilla.
 @param pColumna, numero de columnas de la rejilla.
 @param pDistancia, separación entre los puntos de la rejilla.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::insertarRejilla(Rejilla &rej, int pFila, int pColumna, int pDistancia)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentencia;

		sentencia = "select * from rejillas where puntos_fila = \"" +  Utiles::converString(pFila) + 
			 "\" AND puntos_columna = \"" + Utiles::converString(pColumna) + "\" AND distancia = \"" +
			Utiles::converString(pDistancia) + "\"";

		mysqlpp::Query query = conn.query(sentencia);
        mysqlpp::StoreQueryResult res = query.store();

        // Display results
        if(res.empty()) 
		{	
			string idRejilla;
				
			sentencia = "select MAX(codigo_rejilla) from rejillas";

			mysqlpp::Query query = conn.query(sentencia);
			mysqlpp::StoreQueryResult resRej = query.store();

			if(resRej.empty())
			{
				idRejilla = "1";
			}
			else
			{
				idRejilla = Utiles::converString(atoi(resRej[0]["MAX(codigo_rejilla)"]) + 1);
			}

			sentencia = "insert into rejillas values (" + idRejilla + "," + Utiles::converString(pFila) + "," + 
					Utiles::converString(pColumna) + "," + Utiles::converString(pDistancia) + ")";

			query = conn.query(sentencia);

			query.execute();

			rej.setID(atoi(idRejilla.c_str()));
		}
		else
		{
			rej.setID(atoi(res[0]["codigo_rejilla"]));
			return false;
		}
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}

	return true;
}

/**
 Guarda todas las rejillas almacenadas en preferencias en la base de datos del servidor
 @param rejillas, vector de objetos de la clase OpcionesRej que contiene todas las
 rejillas definidas en preferencias.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::insertarRejillasPref(vector<OpcionesRej> &rejillas)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentencia, idRejilla;
		int numRej;

		numRej = rejillas.size();

		for(int i = 0; i < numRej; i++)
		{
			idRejilla = Utiles::converString(rejillas[i].getID());

			sentencia = "select * from rejillas where codigo_rejilla = \"" +  idRejilla + "\"";

			mysqlpp::Query query = conn.query(sentencia);
			mysqlpp::StoreQueryResult res = query.store();
		
		    // Display results
		    if(res.empty()) 
			{
				string filas, columnas, distancia;

				filas = Utiles::converString(rejillas[i].getNumFilas());
				columnas = Utiles::converString(rejillas[i].getNumColumnas());
				distancia = Utiles::converString(rejillas[i].getSeparaPuntos());
			
				sentencia = "insert into rejillas values (" + idRejilla + "," + filas + "," + columnas + "," + distancia + ")";

				query = conn.query(sentencia);

				query.execute();
			}
		}
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}

	return true;
}

/**
 Consulta las rejillas disponibles en el servidor.
 @param rejillas, referencia al vector de OpcionesRej que contiene las rejillas.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::consultaRejillas(vector<OpcionesRej> &rejillas)
{
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentencia;

		sentencia = "select * from rejillas";

		mysqlpp::Query query = conn.query(sentencia);
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if(!res.empty()) 
		{
			for (size_t i = 0; i < res.num_rows(); ++i) 
			{
				OpcionesRej rejillaBD;
				
				rejillaBD.setID(atoi(res[i]["codigo_rejilla"]));
				rejillaBD.setNumFilas(atoi(res[i]["puntos_fila"]));
				rejillaBD.setNumColumnas(atoi(res[i]["puntos_columna"]));
				rejillaBD.setSeparaPuntos(atoi(res[i]["distancia"]));
				rejillaBD.setNumPuntos(rejillaBD.getNumFilas() * rejillaBD.getNumColumnas());

				rejillas.push_back(rejillaBD);
			}
		}
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}

	return true;
}

/**
 Obtiene los factores de corrección definidos en la base de datos.
 @param clFec, referencia al objeto de la clase CalculoFecundidad.
 @param especie, string que contiene la especie.
 @return bool, devuelve true si la consulta es correcta false en caso contrario.
 */
bool ConexionBD::obtenerFactoresCorreccion(CalculoFecundidad &clFec,const string &especie)
{
	vector<double> facCorreccion;
	vector<int> rangoDiam;
	mysqlpp::Connection conn(false);
	
    if(conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		string sentencia;

		sentencia = "select * from factores_correccion where codigo_especie = \"" +  especie + "\" order by rango";

		mysqlpp::Query query = conn.query(sentencia);
        mysqlpp::StoreQueryResult res = query.store();

		// Display results
        if(!res.empty()) 
		{
			for(size_t i = 0; i < res.num_rows(); ++i)
			{
				rangoDiam.push_back(atof(res[i]["rango"]));
				facCorreccion.push_back(atof(res[i]["factor"]));
			}

			clFec.setClasesDiametros(rangoDiam);
			clFec.setFactorCorreccion(facCorreccion);
		}
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}

	return true;
}
