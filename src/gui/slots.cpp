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

#include "gui/MainWindow.h"

void MainWindow::setSlots() {
    QObject::connect(qApp,SIGNAL(aboutToQuit()), SLOT(writeSettings()));
    QObject::connect(actionQuit,SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionAbout,SIGNAL(triggered()), SLOT(showAbout()));
    QObject::connect(tab,SIGNAL(currentForm(Form*)), SLOT(currentForm(Form*)));
	QObject::connect(editUrl,SIGNAL(returnPressed()), SLOT(load()));
	QObject::connect(menuHistory,SIGNAL(aboutToShow()), SLOT(showHistory()));
	QObject::connect(combo2,SIGNAL(currentIndexChanged(const QString&)), SLOT(combo2change(const QString&)));
}
