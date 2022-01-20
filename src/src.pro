include("dualword-wiki.version.pri")

TARGET = dualword-wiki
TEMPLATE = app
message(Building: = $${TARGET} - $${VERSION})

DEPENDPATH += .
INCLUDEPATH += .

QT += webenginewidgets xml xmlpatterns
CONFIG += c++11 thread release 

HEADERS += \
	app/DualwordWikiApp.h \
	app/NetworkAccessManager.h \
	gui/MainWindow.h \
	gui/Browser.h \
	gui/DualBrowser.h \
	gui/Tab.h \
	gui/Form.h \
	gui/BrowserForm.h \
	gui/DualBrowserForm.h \
	gui/Get.h
			
SOURCES += \
	app/main.cpp \
	app/DualwordWikiApp.cpp \
	app/NetworkAccessManager.cpp \
	gui/slots.cpp \
	gui/MainWindow.cpp \
	gui/Browser.cpp \
	gui/DualBrowser.cpp \
	gui/Tab.cpp \
	gui/Form.cpp \
	gui/BrowserForm.cpp \
	gui/DualBrowserForm.cpp \
	gui/Get.cpp

FORMS += \
	gui/MainWindow.ui
	
RESOURCES += html/html.qrc
		
unix {	
	include("dualword-wiki.unix.pri")
}

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
