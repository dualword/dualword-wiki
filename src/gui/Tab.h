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

#include "app/DualwordWikiApp.h"
#include "BrowserForm.h"
#include "DualBrowserForm.h"

class Tab : public QTabWidget {
  Q_OBJECT

public:
	Tab(QWidget *p=0);
	virtual ~Tab();
	template <typename T = BrowserForm>
	int createBrowser(){
		auto f = new T(this);
		QObject::connect(f,SIGNAL(titleChanged(const QString&)), SLOT(setToolTip(const QString&)));
		f->home();
		return addTab(f, "");

	};

public slots:
	void closeTab(int);
	void setToolTip(const QString&);

	void openLink(const QUrl& url, int id){
		auto p = qobject_cast<Form*>(currentWidget());
		auto f = p->clone();
		QObject::connect(f,SIGNAL(titleChanged(const QString&)), SLOT(setToolTip(const QString&)));
		f->load(url.toString(), id);
		addTab(f, "");
	}

signals:
	void currentForm(Form*);

private slots:
    void contextMenuRequested(const QPoint &position);

};

#endif /* TAB_H_ */
