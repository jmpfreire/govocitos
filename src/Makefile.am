## Process this file with automake to produce Makefile.in

## Created by Anjuta

INCLUDES =                                                      \
	-I$(top_srcdir) 				\
	-I$(top_srcdir)/src				\
	-DPIXMAPSDIR=\""$(datadir)"/govocitos/Iconos/\"       \
	-DDATADIR=\""$(pkgdatadir)"/Glade/\"

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GOVOCITOS_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = govocitos 

gladedir = $(pkgdatadir)/Glade/

glade_DATA = \
	Glade/Preferencias.glade\
	Glade/AcercaDe.glade \
	Glade/PanelPropiedades.glade \
	Glade/CalculaDiametro.glade \
	Glade/seleccionaClaseEstado.glade \
	Glade/panelCerradoDatos.glade \
	Glade/DatosDiametros.glade \
	Glade/DatosEstadisticos.glade \
	Glade/PanelResultados.glade \
	Glade/SelecAccionDetec.glade \
	Glade/DiametrosLupa.glade

pixmaps_dir = $(datadir)/govocitos/Iconos/
pixmaps__DATA = \
	Iconos/logoGovocitos.png\
	Iconos/preferencias.png \
	Iconos/acercaDe.png \
	Iconos/advertencia.png \
	Iconos/anhadir.png \
	Iconos/aplicacionGrafica.png \
	Iconos/archivoTexto.png \
	Iconos/calculoDatos.png \
	Iconos/carpeta.png \
	Iconos/configurar.png \
	Iconos/descarga.png \
	Iconos/error.png \
	Iconos/guardar.png \
	Iconos/pregunta.png \
	Iconos/logoAbout.png

govocitos_SOURCES = \
	CoreGovocitos.cpp    \
	CoreGovocitos.h    \
	Modulos/ModulosGovocitos.cpp    \
	Modulos/ModulosGovocitos.h    \
	Interfaz/InterfazGovocitos.cpp    \
	Interfaz/InterfazGovocitos.h    \
	main.cpp    \
	Interfaz/MenuBarraPrincipal.cpp    \
	Interfaz/MenuBarraPrincipal.h    \
	Interfaz/BarraEstado.cpp    \
	Interfaz/BarraEstado.h    \
	Config/OpcionesPref.cpp    \
	Config/OpcionesPref.h    \
	Config/OpcionesRej.cpp    \
	Config/OpcionesRej.h    \
	Config/ConfigGovocitos.cpp    \
	Config/ConfigGovocitos.h    \
	Utiles.cpp    \
	Utiles.h    \
	Fichero.cpp    \
	Fichero.h    \
	Estructuras/Celula.cpp    \
	Estructuras/Celula.h    \
	Estructuras/ListadoCelulas.cpp    \
	Estructuras/ListadoCelulas.h    \
	Estructuras/NucleoCelula.cpp    \
	Estructuras/NucleoCelula.h    \
	Modulos/XmlParse.cpp    \
	Modulos/XmlParse.h    \
	Estructuras/ClaseCelula.cpp    \
	Estructuras/ClaseCelula.h    \
	Estructuras/ClasificaCelula.cpp    \
	Estructuras/ClasificaCelula.h    \
	Estructuras/EstadoCelula.cpp    \
	Estructuras/EstadoCelula.h    \
	Estructuras/DataImage.cpp    \
	Estructuras/DataImage.h    \
	Estructuras/ListadoImagenes.cpp    \
	Estructuras/ListadoImagenes.h    \
	Interfaz/DialogoBarraProgres.cpp    \
	Interfaz/DialogoBarraProgres.h    \
	Conectividad/XmlConectividad.cpp    \
	Conectividad/XmlConectividad.h    \
	Conectividad/XmlWebDatos.cpp    \
	Conectividad/XmlWebDatos.h    \
	Conectividad/XmlWebImagenes.cpp    \
	Conectividad/XmlWebImagenes.h    \
	Interfaz/Preferencias.cpp    \
	Interfaz/Preferencias.h    \
	Modulos/HttpsConexion.cpp    \
	Modulos/HttpsConexion.h    \
	Interfaz/DialogoAGLocal.cpp    \
	Interfaz/DialogoAGLocal.h    \
	Estructuras/ImageCells.cpp    \
	Estructuras/ImageCells.h    \
	Modulos/DesReHacer.cpp    \
	Modulos/DesReHacer.h    \
	Interfaz/PanelDibujado.cpp    \
	Interfaz/PanelDibujado.h    \
	Modulos/SistemaDibujado.cpp    \
	Modulos/SistemaDibujado.h    \
	Modulos/DibujadoCelula.cpp    \
	Modulos/DibujadoCelula.h    \
	Interfaz/PanelPropiedades.cpp    \
	Interfaz/PanelPropiedades.h    \
	Interfaz/MenuPopup.cpp    \
	Interfaz/MenuPopup.h    \
	Interfaz/DialogoRemoto.cpp    \
	Interfaz/DialogoRemoto.h    \
	Estructuras/ListadoCache.cpp    \
	Estructuras/ListadoCache.h    \
	Modulos/ScanFillLine.cpp    \
	Modulos/ScanFillLine.h    \
	Interfaz/PanelDiametros.cpp    \
	Interfaz/PanelDiametros.h    \
	Interfaz/MenuSeleccion.cpp    \
	Interfaz/MenuSeleccion.h    \
	Modulos/Rejilla.cpp    \
	Modulos/Rejilla.h    \
	Interfaz/PanelDatosEstadisticos.cpp    \
	Interfaz/PanelDatosEstadisticos.h    \
	Clasificador/Clasificador.cpp    \
	Clasificador/Clasificador.h    \
	Clasificador/svm.cpp    \
	Clasificador/svm.h    \
	Bordes/DeteccionAut.cpp    \
	Bordes/DeteccionAut.h    \
	Interfaz/RejillaPersonalizada.cpp    \
	Interfaz/RejillaPersonalizada.h    \
	Modulos/CalculoMorfologico.cpp    \
	Modulos/CalculoMorfologico.h    \
	Dialogos.cpp    \
	Dialogos.h    \
	Modulos/CalculoEstadistico.cpp    \
	Modulos/CalculoEstadistico.h    \
	Interfaz/PanelFecundidad.cpp    \
	Interfaz/PanelFecundidad.h    \
	Modulos/CalculoFecundidad.cpp    \
	Modulos/CalculoFecundidad.h    \
	Estructuras/ListadoIndividuo.cpp    \
	Estructuras/ListadoIndividuo.h    \
	Interfaz/DialogoIndividuo.cpp    \
	Interfaz/DialogoIndividuo.h    \
	Conectividad/XmlWebIndividuo.cpp    \
	Conectividad/XmlWebIndividuo.h    \
	Estructuras/ResultadosImagen.cpp    \
	Estructuras/ResultadosImagen.h    \
	Interfaz/PlotHistogram.cpp    \
	Interfaz/PlotHistogram.h    \
	Modulos/ResultFecundidad.cpp    \
	Modulos/ResultFecundidad.h    \
	Conectividad/XmlWebFecundidad.cpp    \
	Conectividad/XmlWebFecundidad.h    \
	Modulos/ConexionBD.cpp    \
	Modulos/ConexionBD.h    \
	Modulos/SftpConexion.cpp    \
	Modulos/SftpConexion.h    \
	Modulos/XmlPreferencias.cpp    \
	Modulos/XmlPreferencias.h    \
	Modulos/XmlCache.cpp    \
	Modulos/XmlCache.h

govocitos_LDFLAGS = \
	-L/usr/lib \
	-L/usr/lib/local

govocitos_CXXFLAGS = \
	-I/usr/include/mysql \
	-I/usr/include/mysql++ \
	-Wall

govocitos_LDADD = \
	-lcurl \
	-lgthread-2.0 \
	$(GOVOCITOS_LIBS) \
	libbordes32.a \
	-lmysqlpp \
	-lmysqlclient \
	/usr/local/lib/libssh2.a

EXTRA_DIST = $(glade_DATA) \
	$(Clasificador_DATA)\
	$(merluza_DATA)    \
	$(faneca_DATA)    \
	$(luzy_DATA)    \
	$(lusy_DATA)

merluza_DATA = \
	Clasificador/merluza/fich_med_desv_clases_glrls_a0.dat\
	Clasificador/merluza/fich_med_desv_estados_glrls_a0.dat \
	Clasificador/merluza/fich_svm_clasif_clases_glrls_a0.dat \
	Clasificador/merluza/fich_svm_clasif_estados_glrls_a0.dat

merluzadir = \
	$(pkgdatadir)/merluza/

faneca_DATA = \
	Clasificador/faneca/fich_med_desv_clases_glrls_a0.dat\
	Clasificador/faneca/fich_med_desv_estados_glrls_a0.dat \
	Clasificador/faneca/fich_svm_clasif_clases_glrls_a0.dat \
	Clasificador/faneca/fich_svm_clasif_estados_glrls_a0.dat

fanecadir = \
	$(pkgdatadir)/faneca/

lusy_DATA = \
	Clasificador/lusy/fich_med_desv_clases_glrls_a0.dat\
	Clasificador/lusy/fich_med_desv_estados_glrls_a0.dat \
	Clasificador/lusy/fich_svm_clasif_clases_glrls_a0.dat \
	Clasificador/lusy/fich_svm_clasif_estados_glrls_a0.dat

lusydir = \
	$(pkgdatadir)/lusy/

# Remove glade directory on uninstall
uninstall-local:
	-rm -r $(gladedir)
	-rm -r $(datadir)/govocitos
