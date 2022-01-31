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

#ifndef SRC_GUI_DUALBROWSER_H_
#define SRC_GUI_DUALBROWSER_H_

#include "Browser.h"

class Get;

class DualWebPage : public WebPage{
	Q_OBJECT

public:
	DualWebPage(QObject *p = 0){};
	virtual ~DualWebPage(){};
    virtual bool acceptNavigationRequest(const QUrl&, QWebEnginePage::NavigationType, bool);
    bool isValidUrl(const QUrl&);
};

class DualBrowser : public Browser{
	Q_OBJECT

public:
	DualBrowser(QWidget *p = 0, int id = 0);
	virtual ~DualBrowser();
	void getTitle(const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString());
	void getPage(const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString());
	const QString& getLang() const {return lang;}
	void setLang(const QString& lang){this->lang = lang;}

signals:
	void linkClicked(QUrl);

protected:
	QString lang;

private:
	QScopedPointer<Get> req;
};


#endif /* SRC_GUI_DUALBROWSER_H_ */
