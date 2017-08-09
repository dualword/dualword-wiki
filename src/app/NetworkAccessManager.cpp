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

#include "NetworkAccessManager.h"
#include <QCoreApplication>

BlockedNetworkReply::BlockedNetworkReply(QObject *p, const QNetworkRequest &req,
		QNetworkAccessManager::Operation op) : QNetworkReply(p) {
    setRequest(req);
    setUrl(req.url());
    setOperation(op);

    qRegisterMetaType<QNetworkReply::NetworkError>("QNetworkReply::NetworkError");

    QString msg = QCoreApplication::translate("NetworkAccessManager",
    		"Access to \"%1\" is blocked.").arg(req.url().host());
    setError(UnknownNetworkError, msg);

    QMetaObject::invokeMethod(this, "error", Qt::QueuedConnection,
        Q_ARG(QNetworkReply::NetworkError, UnknownNetworkError));
    QMetaObject::invokeMethod(this, "finished", Qt::QueuedConnection);
}

BlockedNetworkReply::~BlockedNetworkReply() {

}

NetworkCookieJar::NetworkCookieJar(QObject *p) : QNetworkCookieJar(p) {

}

NetworkCookieJar::~NetworkCookieJar() {

}

int NetworkCookieJar::count() {
	return allCookies().size();
}

NetworkAccessManager::NetworkAccessManager(QObject *p) : QNetworkAccessManager(p){
	setCookieJar(new NetworkCookieJar(this));
}

NetworkAccessManager::~NetworkAccessManager() {

}

QNetworkReply* NetworkAccessManager::createRequest(Operation op, const QNetworkRequest& req,
		QIODevice* outgoingData){
    if(req.url().host().length() == 0 ||
    		req.url().host().toLower().contains("wikipedia.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikimedia.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikidata.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikibooks.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikiquote.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikiversity.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikisource.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikivoyage.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wikinews.org",Qt::CaseInsensitive) ||
			req.url().host().toLower().contains("wiktionary.org",Qt::CaseInsensitive)){
        return QNetworkAccessManager::createRequest(op, req, outgoingData);
    }
    return new BlockedNetworkReply(this, req, op);
}

