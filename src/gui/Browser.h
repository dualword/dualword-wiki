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

#ifndef BROWSER_H_
#define BROWSER_H_

#include <QtWebEngineWidgets/QtWebEngineWidgets>

class WebPage : public QWebEnginePage{
	Q_OBJECT

public:
	WebPage(QObject *p = 0){

	};
	virtual ~WebPage();
    virtual	bool isValidUrl(const QUrl&);

signals:
	void linkClicked(QUrl);
	void statusBarMessage (const QString&);

protected:
    virtual bool acceptNavigationRequest(const QUrl&, QWebEnginePage::NavigationType, bool);

};

class Interceptor: public QWebEngineUrlRequestInterceptor{
    Q_OBJECT

public:
    Interceptor(QObject* p = nullptr) : QWebEngineUrlRequestInterceptor(p) {
		list << "wikipedia.org" << "wikimedia.org" << "wikidata.org";
		list << "wikibooks.org" << "wikiquote.org" << "wikiversity.org";
		list << "wikisource.org" << "wikivoyage.org" << "wikinews.org";
		list << "wiktionary.org";
    }

    void interceptRequest(QWebEngineUrlRequestInfo &info){
    	if(info.requestUrl().host().length() == 0) return;
    	for(const QString& s : list){
    		if(info.requestUrl().host().contains(s, Qt::CaseInsensitive)) return;
    	}
		info.block(true);
    }

private:
    QList<QString> list;
};

class Browser : public QWebEngineView{
	Q_OBJECT

public:

	Browser(QWidget *p = 0, int id = 0);
	virtual ~Browser();
	int getId(){return id;};

signals:
	void statusBarMessage (const QString&);

public slots:
	void findTxt();

protected slots:
    virtual void contextMenuEvent(QContextMenuEvent *event);

protected:
	QString searchString;
	int id;

};


#endif /* BROWSER_H_ */
