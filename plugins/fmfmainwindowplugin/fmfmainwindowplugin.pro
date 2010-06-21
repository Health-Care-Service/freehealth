TEMPLATE = lib
TARGET = MainWindow
PACKAGE_VERSION = 0.0.2
DEFINES += FMF_MAINWIN_LIBRARY
include(../fmf_plugins.pri)
include( fmfmainwindowplugin_dependencies.pri )
HEADERS = mainwindowplugin.h \
    mainwindow_exporter.h \
    mainwindow.h \
    mainwindowpreferences.h \
    appconfigwizard.h \
    virtualdatabasepreferences.h \
    patientmodelwrapper.h

SOURCES = mainwindowplugin.cpp \
    mainwindow.cpp \
    mainwindowpreferences.cpp \
    appconfigwizard.cpp \
    virtualdatabasepreferences.cpp \
    patientmodelwrapper.cpp

FORMS = virtualbasepage.ui
TRANSLATIONS += $${SOURCES_TRANSLATIONS}/fmfmainwindowplugin_fr.ts \
    $${SOURCES_TRANSLATIONS}/fmfmainwindowplugin_de.ts \
    $${SOURCES_TRANSLATIONS}/fmfmainwindowplugin_es.ts
OTHER_FILES = MainWindow.pluginspec
