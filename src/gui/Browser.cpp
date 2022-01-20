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
#include "Form.h"
#include "MainWindow.h"
#include "BrowserForm.h"
#include "DualBrowserForm.h"

#include <QInputDialog>
#include <QLineEdit>
#include <QShortcut>
#include <QMenu>
#include <QClipboard>

WebPage::WebPage(QObject *p, int flag) : QWebEnginePage(p){
//	history()->setMaximumItemCount(25);
//	if(flag != 0){
//		QWebSettings* qws = settings();
//		qws->setAttribute(QWebSettings::JavascriptEnabled, false);
//	}
}

bool WebPage::acceptNavigationRequest(const QUrl& url, QWebEnginePage::NavigationType type, bool mframe){
	emit linkClicked(url);
    return QWebEnginePage::acceptNavigationRequest(url, type, mframe);
}

WebPage::~WebPage() {
	history()->clear();
    profile()->cookieStore()->deleteAllCookies();
    profile()->clearHttpCache();
    profile()->clearAllVisitedLinks();
}

Browser::Browser(QWidget *p, int id) : QWebEngineView(p), searchString(""), id(id){
	setPage(new WebPage(this, id));
	new QShortcut(QKeySequence::Find, this, SLOT(findTxt()), nullptr, Qt::WidgetWithChildrenShortcut);
    QObject::connect(page(), SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
}

Browser::~Browser() {

}

void Browser::loadFinished(bool ok){
//	switch (reply->error()) {
//		case QNetworkReply::NoError:
//		case QNetworkReply::OperationCanceledError:
//		  break;
//		default:
//			QString status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
//			QString msg = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//			if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() > 0){
//				setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()+" ("+status+" "+msg+")").arg(reply->url().toString()));
//			}else{
//				setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()).arg(reply->url().toString()));
//			}
//	}
//	reply->close();
//	reply->deleteLater();
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
    auto r = page()->contextMenuData().linkUrl();
	if (!r.isEmpty()) {
		QMenu menu(this);
		if(isValidUrl(r)){
			QAction *a = menu.addAction(tr("Open Link in New Tab"), this, SLOT(openLink()));
			a->setData(r);
			menu.addSeparator();
		}
		menu.addAction(pageAction(QWebEnginePage::CopyLinkToClipboard));
		menu.exec(mapToGlobal(event->pos()));
		return;
	}
	QWebEngineView::contextMenuEvent(event);
}

void Browser::openLink(){
	QAction *a = qobject_cast<QAction*>(sender());
	QString url = a->data().toUrl().toString();
	Form *f = qobject_cast<Form*>(parentWidget());
	if(!f) f = qobject_cast<Form*>(parentWidget()->parentWidget()->parentWidget());
    Tab *tab = DualwordWikiApp::instance()->window()->getTab();
	if(qobject_cast<DualBrowserForm*>(f)){
		Form* f = new DualBrowserForm(tab);
		f->load(a->data().toUrl(), id);
		tab->createDualBrowser(f);
	}else if(qobject_cast<BrowserForm*>(f)){
		Form* f = new BrowserForm(tab);
		f->load(a->data().toUrl().toString());
		tab->createBrowser(f);
	}
}

bool Browser::isValidUrl(const QUrl& url){
	if(url.host().toLower().contains("wikipedia.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikimedia.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikidata.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikibooks.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikiquote.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikiversity.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikisource.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikivoyage.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wikinews.org",Qt::CaseInsensitive) ||
		url.host().toLower().contains("wiktionary.org",Qt::CaseInsensitive)){
		return true;
	}

	return false;
}
