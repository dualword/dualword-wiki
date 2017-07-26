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

BrowserForm::BrowserForm(QWidget *p) : Form(p), browser(new Browser(this)) {
	QVBoxLayout *box = new QVBoxLayout(this);
	box->addWidget(browser);
	setLayout(box);
    QObject::connect(browser,SIGNAL(titleChanged(const QString&)),
    		this, SIGNAL(titleChanged(const QString&)));
    QObject::connect(browser,SIGNAL(urlChanged(const QUrl&)),
    		this, SIGNAL(urlChanged(const QUrl&)));
    QObject::connect(browser->page(), SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(browser->page(),SIGNAL(statusBarMessage(const QString&)),
    		this, SIGNAL(statusBarMessage(const QString&)));

}

BrowserForm::~BrowserForm() {

}

QString BrowserForm::getTitle() const{
	return browser->page()->currentFrame()->title();
}

QString BrowserForm::getUrl() const{
	return browser->page()->currentFrame()->url().toString();
}

bool BrowserForm::canChangeUrl(){
	return true;
}

void BrowserForm::load(const QString& url){
	browser->load(QUrl::fromUserInput(QUrl::fromEncoded(url.toUtf8()).toString()));
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
