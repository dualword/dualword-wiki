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

#include "Get.h"
#include "app/NetworkAccessManager.h"
#include "Browser.h"
#include "app/DualwordWikiApp.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QtXml>
#include <QXmlQuery>

Get::Get(QObject *p, const QString& lang1, const QString& lang2, const QString& name, Browser *w) :
QObject(p), nam(new NetworkAccessManager(this)), lang1(lang1), lang2(lang2), name(name), web(w){
	web->stop();
	connect(nam, SIGNAL(finished(QNetworkReply *)), SLOT(finished(QNetworkReply *)));
}

Get::~Get() {

}

GetTitle::GetTitle(QObject *p, const QString& lang1, const QString& lang2, const QString& name, Browser *w) :
		Get(p, lang1, lang2, name, w){

}

GetTitle::~GetTitle() {

}

void GetTitle::get(){
	QNetworkRequest req;
	req.setUrl(QUrl(title.arg(lang1).arg(name).arg(lang2)));
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
				web->load(QUrl::fromUserInput(api.arg(lang2).arg(t.replace(" ", "_"))));
				break;
			}
			query.setQuery("doc($inputDocument)/api/query/pages/page/@_idx/string()");
			query.evaluateTo(&t);
			if(t.length() >= 1){
				int i = t.toInt(&ok);
				if(ok & (i == -1)){
					web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(lang2+".wikipedia.org"));
					break;
				}
			}
			web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(lang2+".wikipedia.org"));
			break;
	    default:
	    	web->setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()).arg(reply->url().host()));
	}
	reply->close();
	reply->deleteLater();
}

GetPage::GetPage(QObject *p, const QString& lang1, const QString& lang2, const QString& name, Browser *w) :
		Get(p, lang1, lang2, name, w){

}

GetPage::~GetPage() {

}

void GetPage::get(){
	QNetworkRequest req;
	req.setUrl(QUrl(title.arg(lang1).arg(name).arg(lang2)));
	nam->get(req);

}

void GetPage::finished(QNetworkReply * reply){
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
			query.setQuery("doc($inputDocument)/api/query/pages/page/@_idx/string()");
			query.evaluateTo(&t);
			if(t.length() >= 1){
				int i = t.toInt(&ok);
				if(ok & (i == -1)){
					web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(lang2+".wikipedia.org"));
					break;
				}
			}
			query.setQuery("doc($inputDocument)/api/query/pages/page/@title/string()");
			query.evaluateTo(&t);
			if(t.trimmed().length() >= 1){
				web->load(QUrl::fromUserInput(api.arg(lang2).arg(t.replace(" ", "_"))));
				break;
			}
			web->setHtml((DualwordWikiApp::getHtml(":/article_not_found.html")).arg(name).arg(lang2+".wikipedia.org"));
			break;
	    default:
	    	web->setHtml((DualwordWikiApp::getHtml(":/error.html")).arg(reply->errorString()).arg(reply->url().host()));
	}
	reply->close();
	reply->deleteLater();
}
