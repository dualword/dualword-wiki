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

#include "Browser.h"
#include "app/DualwordWikiApp.h"
#include "app/NetworkAccessManager.h"

WebPage::WebPage(QObject *p) : QWebPage(p){
	setNetworkAccessManager(new NetworkAccessManager(this));
}

WebPage::~WebPage() {

}

Browser::Browser(QWidget *p) : QWebView(p){
	setPage(new WebPage(this));
	connect(page()->networkAccessManager(), SIGNAL(finished(QNetworkReply *)),
	    this, SLOT(finished(QNetworkReply *)));
}

Browser::~Browser() {

}

void Browser::finished(QNetworkReply * reply){
	switch (reply->error()) {
	    case QNetworkReply::NoError:
	    case QNetworkReply::OperationCanceledError:
	      return;
	    default:
	    	setHtml(reply->error() + reply->errorString());
	}
}

