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

#include "DualBrowserForm.h"
#include "Browser.h"
#include "MainWindow.h"
#include "app/NetworkAccessManager.h"
#include <QWebFrame>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include <QtXml>
#include <QXmlQuery>

GetTitle::GetTitle(QObject *p, const QString& name, Browser *w) : QObject(p),
	nam(new NetworkAccessManager(this)), name(name), web(w){
	web->stop();
	connect(nam, SIGNAL(finished(QNetworkReply *)), SLOT(finished(QNetworkReply *)));
}

GetTitle::~GetTitle() {

}

void GetTitle::get(){
	QNetworkRequest req;
	req.setUrl(QUrl(title.arg(DualwordWikiApp::instance()->window()->lang1()).
						arg(name).arg(DualwordWikiApp::instance()->window()->lang2())));
	nam->get(req);
}

void GetTitle::finished(QNetworkReply * reply){
	QBuffer device;
	QString t;
	QXmlQuery query;
	QString xml;
	bool ok;
	xml =QString::fromUtf8(reply->readAll());
	device.setData(xml.toUtf8());
	device.open(QIODevice::ReadOnly);
	switch (reply->error()) {
	    case QNetworkReply::NoError:
			query.bindVariable("inputDocument", &device);
			query.setQuery("doc($inputDocument)/api/query/pages/page/langlinks/ll/string()");
			query.evaluateTo(&t);
			if(t.trimmed().length() >= 1){
				web->load(QUrl::fromUserInput(api.arg(DualwordWikiApp::instance()->window()->lang2()).arg(t)));
				break;
			}
			query.setQuery("doc($inputDocument)/api/query/pages/page/@_idx/string()");
			query.evaluateTo(&t);
			if(t.length() >= 1){
				int i = t.toInt(&ok);
				if(ok && i == -1){
					web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(reply->url().host()));
					break;
				}else{
					web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(DualwordWikiApp::instance()->window()->lang2()+".wikipedia.org"));
					break;
				}
			}
			query.setQuery("doc($inputDocument)/api/query/pages/page/@title/string()");
			query.evaluateTo(&t);
			if(t.trimmed().length() >= 1){
				web->load(QUrl::fromUserInput(QUrl::fromEncoded((api.arg(DualwordWikiApp::instance()->window()->lang2()).arg(t)).toUtf8()).toString()));
				break;
			}
	      break;
	    default:
	    	web->setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()).arg(reply->url().host()));
	}
}

DualBrowserForm::DualBrowserForm(QWidget *p) : Form(p),
	webview1(new Browser(this)), webview2(new Browser(this)), req1(0) {
	webview1->page()->currentFrame()->setScrollBarPolicy(Qt::Vertical,Qt::ScrollBarAlwaysOn);
	webview2->page()->currentFrame()->setScrollBarPolicy(Qt::Vertical,Qt::ScrollBarAlwaysOn);
	webview1->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	webview2->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	QVBoxLayout *box = new QVBoxLayout(this);
	QSplitter *sp = new QSplitter(this);
	//sp->setOrientation(Qt::Vertical);
	sp->addWidget(webview1);
	sp->addWidget(webview2);
	box->addWidget(sp);
	setLayout(box);
    QObject::connect(webview1,SIGNAL(titleChanged(const QString&)),
    		this, SIGNAL(titleChanged(const QString&)));
    QObject::connect(webview1,SIGNAL(urlChanged(const QUrl&)),
    		this, SIGNAL(urlChanged(const QUrl&)));
    QObject::connect(webview1->page(), SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(webview1->page(),SIGNAL(statusBarMessage(const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(webview2->page(), SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(webview2->page(),SIGNAL(statusBarMessage(const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));
	QObject::connect(webview1->page(),SIGNAL(linkClicked(QUrl)),
			this, SLOT(linkClicked1(QUrl)));
	QObject::connect(webview2->page(),SIGNAL(linkClicked(QUrl)),
			this, SLOT(linkClicked2(QUrl)));

}

DualBrowserForm::~DualBrowserForm() {

}

QString DualBrowserForm::getTitle() const{
	return "";
}

QString DualBrowserForm::getUrl() const{
	QString url = webview1->page()->currentFrame()->url().toString();
	return url.mid(url.lastIndexOf("/")+1);
}

bool DualBrowserForm::canChangeUrl(){
	return true;
}

void DualBrowserForm::load(const QString& name){
	QUrl url(QUrl::fromUserInput(name));
	if(url.host().contains(".")){
		emit statusBarMessage("Blocked:" + url.host());
		return;
	}
	//if(!name.contains(QRegExp("[a-zA-Z0-9\\s_\\xhhhh]"))) return;
	QString tmp(api.arg(DualwordWikiApp::instance()->window()->lang1()).arg(name));
	webview1->load(QUrl::fromEncoded(tmp.toUtf8()));
	req1.reset(new GetTitle(this, name, webview2));
	req1->get();
}

void DualBrowserForm::back (){
	webview1->back();
	webview2->back();
}

void DualBrowserForm::forward (){
	webview1->forward();
	webview2->forward();
}

void DualBrowserForm::reload (){
	webview1->reload();
	webview2->reload();
}

void DualBrowserForm::stop (){
	webview1->stop();
	webview2->stop();
}

void DualBrowserForm::home(){
	webview1->load(QUrl::fromEncoded(api.arg(DualwordWikiApp::instance()->window()->lang1()).arg("Main Page").toUtf8()));
	webview2->load(QUrl::fromEncoded(api.arg(DualwordWikiApp::instance()->window()->lang2()).arg("Main Page").toUtf8()));
}

void DualBrowserForm::linkClicked1(const QUrl& url){
	if(!url.host().toLower().contains("wikipedia.org")){
		emit statusBarMessage("Blocked:" + url.host());
		return;
	}
	QString name = url.toString().mid(url.toString().lastIndexOf("/")+1);
	if(name.trimmed().length()<=0) return;
	QString tmp(api.arg(DualwordWikiApp::instance()->window()->lang1()).arg(name));
	webview1->load(QUrl::fromEncoded(tmp.toUtf8()));
	req1.reset(new GetTitle(this, name, webview2));
	req1->get();
}

void DualBrowserForm::linkClicked2(const QUrl& url){

}

void DualBrowserForm::changeLang1(const QString& s){

}

void DualBrowserForm::changeLang2(const QString& s){
	req1.reset(new GetTitle(this, getUrl(), webview2));
	req1->get();
}
