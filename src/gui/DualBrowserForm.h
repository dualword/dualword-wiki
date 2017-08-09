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

#ifndef SRC_GUI_DUALBROWSERFORM_H_
#define SRC_GUI_DUALBROWSERFORM_H_

#include "Form.h"
#include <QObject>
#include <QSplitter>

class DualBrowser;
class Browser;

class DualBrowserForm  : public Form {
	Q_OBJECT

public:
	DualBrowserForm(QWidget *p);
	virtual ~DualBrowserForm();

public:
	virtual QString getTitle() const;
	virtual QString getUrl() const;

public slots:
	void load(const QString&);
	void load(const QUrl&, int);
	void slotLoadFinished(bool);
	void back();
	void forward ();
	void reload ();
	void stop ();
	void home();
	void next ();
	bool isNext () {return true;};
	void changeLang1 (const QString&);
	void changeLang2 (const QString&);
	QWebHistory* getHistory();
	void loadHistory();

private slots:
	void linkClicked1 (const QUrl&);
	void linkClicked2 (const QUrl&);
	QString getValidUrl(const QString&);
	QString getLinkLang(const QString&);
	bool scroll(const QUrl&, Browser*);

private:
	DualBrowser *web1, *web2;
	QString nextUrl;
};

#endif /* SRC_GUI_DUALBROWSERFORM_H_ */
