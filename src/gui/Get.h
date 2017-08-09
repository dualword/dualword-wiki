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

#ifndef SRC_GUI_GET_H_
#define SRC_GUI_GET_H_

#include <QObject>

class Browser;
class NetworkAccessManager;
class QNetworkReply;

class Get : public QObject {
	Q_OBJECT

public:
	Get(QObject *p = 0, const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString(), Browser *b = 0);
	virtual ~Get();
	virtual void get() {};

protected slots:
	virtual void finished(QNetworkReply* reply){};

protected:
	NetworkAccessManager *nam;
	QString lang1, lang2;
	QString name;
	Browser *web;
	QString api = "https://%1.wikipedia.org/api/rest_v1/page/html/%2";
	QString title = "https://%1.wikipedia.org/w/api.php?action=query&redirects=yes&titles=%2&prop=langlinks&format=xml&lllang=%3";
};

class GetTitle : public Get {
	Q_OBJECT

public:
	GetTitle(QObject *p = 0, const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString(), Browser *b = 0);
	virtual ~GetTitle();
	void get();

protected slots:
	void finished(QNetworkReply* reply);
};

class GetPage : public Get {
	Q_OBJECT

public:
	GetPage(QObject *p = 0, const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString(), Browser *b = 0);
	virtual ~GetPage();
	void get();

protected slots:
	void finished(QNetworkReply* reply);

};

#endif /* SRC_GUI_GET_H_ */
