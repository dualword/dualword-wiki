/*
 *	Dualword-wiki is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Dualword-wiki is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Dualword-wiki. If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "DualwordWikiApp.h"
#include "gui/MainWindow.h"
#include "gui/Browser.h"

DualwordWikiApp::DualwordWikiApp(int &argc, char **argv) : QApplication(argc, argv) {
	setApplicationName("Dualword-wiki");
	#ifdef _VER
		QApplication::setApplicationVersion(_VER);
	#endif
	QApplication::setQuitOnLastWindowClosed(true);
	qsrand(QTime::currentTime().msec());
    //QWebEngineProfile::defaultProfile()->setRequestInterceptor(new Interceptor(this));
}

DualwordWikiApp::~DualwordWikiApp() {

}

DualwordWikiApp *DualwordWikiApp::instance() {
    return (static_cast<DualwordWikiApp *>(QCoreApplication::instance()));
}

QString DualwordWikiApp::getHtml(const QString& f){
	QFile file(f);
	bool ok = file.open(QIODevice::ReadOnly);
	return QString(QLatin1String(file.readAll()));
}

void DualwordWikiApp::start() {
	win = new MainWindow();
	win->init();
	win->show();
}
