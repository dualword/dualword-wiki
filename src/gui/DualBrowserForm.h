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

class Browser;
class QNetworkReply;
class NetworkAccessManager;

class GetTitle  : public QObject {
	Q_OBJECT

public:
	GetTitle(QObject *p = 0, const QString& name = QString(), Browser *b = 0);
	virtual ~GetTitle();
	void get();

private slots:
	void finished(QNetworkReply* reply);

private:
	NetworkAccessManager *nam;
	QString name;
	Browser *web;
	QString api = "https://%1.wikipedia.org/api/rest_v1/page/html/%2";
	QString title = "https://%1.wikipedia.org/w/api.php?action=query&redirects=yes&titles=%2&prop=langlinks&format=xml&lllang=%3";

};

class DualBrowserForm  : public Form {
	Q_OBJECT

public:
	DualBrowserForm(QWidget *p);
	virtual ~DualBrowserForm();

public:
	virtual QString getTitle() const;
	virtual QString getUrl() const;
	virtual bool canChangeUrl();

public slots:
	void load(const QString&);
	void back();
	void forward ();
	void reload ();
	void stop ();
	void home();
	void changeLang1 (const QString&);
	void changeLang2 (const QString&);

private slots:
	void linkClicked1 (const QUrl&);
	void linkClicked2 (const QUrl&);

private:
	QString api = "https://%1.wikipedia.org/api/rest_v1/page/html/%2";
	Browser *webview1, *webview2;
	QScopedPointer<GetTitle> req1;

};

#endif /* SRC_GUI_DUALBROWSERFORM_H_ */
