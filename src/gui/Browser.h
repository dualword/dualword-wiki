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

#include <QtCore>
#include <QtWebKit>

class WebPage : public QWebPage{
	Q_OBJECT

public:
	WebPage(QObject *p = 0);
	virtual ~WebPage();

};

class Browser : public QWebView{
	Q_OBJECT

public:

	Browser(QWidget *p = 0);
	virtual ~Browser();

public slots:
	void finished(QNetworkReply * reply);
	void findTxt();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void openLinkInNewTab();

private:
	QString searchString;

};


#endif /* BROWSER_H_ */
