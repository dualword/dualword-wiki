include("dualword-wiki.version.pri")

TARGET = dualword-wiki
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += qt webkit network xml release
message(Building: = $${TARGET} - $${VERSION})

HEADERS = \
	app/DualwordWikiApp.h \
	app/NetworkAccessManager.h \
	gui/MainWindow.h \
	gui/Browser.h \
	gui/Tab.h \
	gui/Form.h \
	gui/BrowserForm.h
			
SOURCES = \
	app/main.cpp \
	app/DualwordWikiApp.cpp \
	app/NetworkAccessManager.cpp \
	gui/slots.cpp \
	gui/MainWindow.cpp \
	gui/Browser.cpp \
	gui/Tab.cpp \
	gui/Form.cpp \
	gui/BrowserForm.cpp

FORMS += \
	gui/MainWindow.ui
			
unix {	
	include("dualword-wiki.unix.pri")
}

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
