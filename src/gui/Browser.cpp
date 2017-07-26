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

#include <QInputDialog>
#include <QLineEdit>
#include <QShortcut>
#include <QMenu>
#include <QClipboard>

WebPage::WebPage(QObject *p) : QWebPage(p){
	setNetworkAccessManager(new NetworkAccessManager(this));
}

WebPage::~WebPage() {

}

Browser::Browser(QWidget *p) : QWebView(p){
	setPage(new WebPage(this));
	new QShortcut(QKeySequence::Find, this, SLOT(findTxt()), nullptr, Qt::WidgetWithChildrenShortcut);
	connect(page()->networkAccessManager(), SIGNAL(finished(QNetworkReply *)),
	    this, SLOT(finished(QNetworkReply *)));
}

Browser::~Browser() {

}

void Browser::finished(QNetworkReply* reply){
	switch (reply->error()) {
	    case QNetworkReply::NoError:
	    case QNetworkReply::OperationCanceledError:
	      break;
	    default:
	    	setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()).arg(reply->url().toString()));

	}
}

void Browser::findTxt(){
    bool ok;
    QString search = QInputDialog::getText(this, tr("Find"), tr("Text:"), QLineEdit::Normal,
    		searchString, &ok);
    if (ok) {
    	searchString = search;
        findText(searchString);
    }
}

void Browser::contextMenuEvent(QContextMenuEvent *event){
    QWebHitTestResult r = page()->mainFrame()->hitTestContent(event->pos());
    if (!r.linkUrl().isEmpty()) {
        QMenu menu(this);
        menu.addAction(tr("Open Link in New Tab"), this, SLOT(openLinkInNewTab()));
        menu.addSeparator();
        menu.addAction(pageAction(QWebPage::OpenLink));
        menu.addSeparator();
        menu.addAction(pageAction(QWebPage::CopyLinkToClipboard));
        menu.exec(mapToGlobal(event->pos()));
        return;
    }
    QWebView::contextMenuEvent(event);
}

void Browser::openLinkInNewTab(){
    pageAction(QWebPage::OpenLinkInNewWindow)->trigger();
}

