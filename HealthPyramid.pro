QT += widgets sql

CONFIG += c++11

HEADERS       = \
    view/HealthPyramidMainWindow.hpp \
    view/HealthPyramidView.hpp \
    view/PyramidItem.hpp \
    view/PyramidItemPathFactory.hpp \
    model/DatabaseHandler.hpp

SOURCES       = main.cpp \
                view/PyramidItem.cpp \
                view/HealthPyramidView.cpp \
    view/HealthPyramidMainWindow.cpp \
    view/PyramidItemPathFactory.cpp \
    model/DatabaseHandler.cpp

RESOURCES     = healthpyramid.qrc

TEMPLATE    = app

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
