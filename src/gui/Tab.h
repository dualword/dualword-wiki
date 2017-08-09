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

#ifndef TAB_H_
#define TAB_H_

#include <QObject>
#include <QTabWidget>
#include <QUrl>

class Form;

class Tab : public QTabWidget {
  Q_OBJECT

public:
	Tab(QWidget *p=0);
	virtual ~Tab();

signals:
	void NewBrowser();
	void NewDualBrowser();
	void currentForm(Form*);

public slots:
	int createBrowser(Form* f = 0);
	int createDualBrowser(Form* f = 0);
	void closeTab(int);
	void currentChanged (int index);
	void setToolTip(const QString&);

private slots:
    void contextMenuRequested(const QPoint &position);

};

#endif /* TAB_H_ */
