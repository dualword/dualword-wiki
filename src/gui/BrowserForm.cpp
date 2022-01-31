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

#include "BrowserForm.h"
#include "Browser.h"
#include "app/global.h"

BrowserForm::BrowserForm(QWidget *p) : MainForm(p), browser(new Browser(this)) {
	QVBoxLayout *box = new QVBoxLayout(this);
	box->addWidget(browser);
	setLayout(box);
    QObject::connect(browser,SIGNAL(titleChanged(const QString&)), SIGNAL(titleChanged(const QString&)));
    QObject::connect(browser,SIGNAL(urlChanged(const QUrl&)), SIGNAL(urlChanged(const QUrl&)));
    QObject::connect(browser,SIGNAL(loadFinished(bool)), SIGNAL(loadFinished(bool)));
    QObject::connect(browser,SIGNAL(loadStarted()), SIGNAL(loadStarted()));
    QObject::connect(browser->page(), SIGNAL(linkHovered(const QString&)), SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(browser->page(),SIGNAL(statusBarMessage(const QString&)), SIGNAL(statusBarMessage(const QString&)));
}

BrowserForm::~BrowserForm() {

}

QString BrowserForm::getTitle() const{
	return browser->page()->title();
}

QString BrowserForm::getUrl() const{
	return browser->page()->url().toString();
}

void BrowserForm::load(const QString& url){
	browser->load(QUrl::fromUserInput(QUrl::fromEncoded(url.toUtf8()).toString()));
	browser->setFocus();
}

void BrowserForm::load(const QUrl& url, int id){
	browser->load(url);
	browser->setFocus();
}

void BrowserForm::back (){
	browser->back();
}

void BrowserForm::forward (){
	browser->forward();
}

void BrowserForm::reload (){
	browser->reload();
}

void BrowserForm::stop (){
	browser->stop();
}

void BrowserForm::home(){
	browser->load(QUrl("http://www.wikipedia.org"));
}

void BrowserForm::next (){

}

QWebEngineHistory* BrowserForm::getHistory(){
	return browser->page()->history();
}

void BrowserForm::loadHistory(){
	QAction *a = qobject_cast<QAction*>(sender());
	browser->history()->goToItem(browser->history()->itemAt(a->data().toInt()));
}

