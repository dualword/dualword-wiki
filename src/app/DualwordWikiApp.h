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

#ifndef SRC_APP_DUALWORDWIKIAPP_H_
#define SRC_APP_DUALWORDWIKIAPP_H_

#include <QApplication>

class MainWindow;

class DualwordWikiApp : public QApplication {
    Q_OBJECT

public:
	DualwordWikiApp(int &argc, char **argv);
	virtual ~DualwordWikiApp();
	MainWindow* window() {return win;};
    static DualwordWikiApp *instance();
    static QString getHtml(const QString&);

public Q_SLOTS:
	void start();

private:
	MainWindow* win;

};


#endif /* SRC_APP_DUALWORDWIKIAPP_H_ */




