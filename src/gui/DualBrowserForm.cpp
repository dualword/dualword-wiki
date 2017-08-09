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
#include "DualBrowser.h"
#include <QWebFrame>

DualBrowserForm::DualBrowserForm(QWidget *p) : Form(p),
	web1(new DualBrowser(this,1)), web2(new DualBrowser(this,2)), nextUrl("") {
	web1->setLang(DualwordWikiApp::instance()->window()->lang1());
	web2->setLang(DualwordWikiApp::instance()->window()->lang2());
	QVBoxLayout *box = new QVBoxLayout(this);
	QSplitter *sp = new QSplitter(this);
	sp->addWidget(web1);
	sp->addWidget(web2);
	box->addWidget(sp);
	setLayout(box);
    QObject::connect(web1,SIGNAL(titleChanged(const QString&)),
    		SIGNAL(titleChanged(const QString&)));
    QObject::connect(web1,SIGNAL(urlChanged(const QUrl&)),
    		SIGNAL(urlChanged(const QUrl&)));
    QObject::connect(web1,SIGNAL(statusBarMessage(const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(web2,SIGNAL(statusBarMessage(const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(web1->page(), SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(web1->page(),SIGNAL(statusBarMessage(const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(web2->page(), SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
    QObject::connect(web2->page(),SIGNAL(statusBarMessage(const QString&)),
    		SIGNAL(statusBarMessage(const QString&)));
	QObject::connect(web1,SIGNAL(linkClicked(QUrl)), SLOT(linkClicked1(QUrl)));
	QObject::connect(web2,SIGNAL(linkClicked(QUrl)), SLOT(linkClicked2(QUrl)));
    QObject::connect(web1,SIGNAL(loadFinished(bool)), SIGNAL(loadFinished(bool)));
    QObject::connect(web1,SIGNAL(loadFinished(bool)), SLOT(slotLoadFinished(bool)));
    QObject::connect(web1,SIGNAL(loadStarted()), SIGNAL(loadStarted()));
}

DualBrowserForm::~DualBrowserForm() {

}

QString DualBrowserForm::getTitle() const{
	QString t = web1->page()->currentFrame()->title();
	return t.mid(t.lastIndexOf("/")+1);
}

QString DualBrowserForm::getUrl() const{
	QString url = web1->page()->currentFrame()->url().toString();
	return url.mid(url.lastIndexOf("/")+1);
}

void DualBrowserForm::back (){
	web1->back();
	web2->back();
}

void DualBrowserForm::forward (){
	web1->forward();
	web2->forward();
}

void DualBrowserForm::reload (){
	web1->reload();
	web2->reload();
}

void DualBrowserForm::stop (){
	web1->stop();
	web2->stop();
}

void DualBrowserForm::home(){
	web1->getPage(DualwordWikiApp::instance()->window()->lang1(),
			DualwordWikiApp::instance()->window()->lang1(), "Main Page");
	web2->getPage(DualwordWikiApp::instance()->window()->lang2(),
			DualwordWikiApp::instance()->window()->lang2(), "Main Page");
}

void DualBrowserForm::load(const QString& str){
	QString name = str.mid(str.lastIndexOf("/")+1, str.lastIndexOf("#")-(str.lastIndexOf("/")+1));
	if(name.trimmed().length() <= 0) return;
	if(web1->getLang() == DualwordWikiApp::instance()->window()->lang1()){
		web1->getPage(DualwordWikiApp::instance()->window()->lang1(),
				DualwordWikiApp::instance()->window()->lang1(), name);
	}else{
		web1->getTitle(web1->getLang(), DualwordWikiApp::instance()->window()->lang1(), name);
	}
	web2->getTitle(DualwordWikiApp::instance()->window()->lang1(),
			DualwordWikiApp::instance()->window()->lang2(), name);
	web1->setFocus();
}

void DualBrowserForm::load(const QUrl& url, int id){
	QString name = getValidUrl(url.toString());
	QString lang = getLinkLang(url.toString());
	if(id == web1->getId()){
		if(lang == DualwordWikiApp::instance()->window()->lang1()){
			web1->getPage(lang,	DualwordWikiApp::instance()->window()->lang1(), name);
		}else{
			web1->getTitle(lang, DualwordWikiApp::instance()->window()->lang1(), name);
		}
		web2->getTitle(lang, DualwordWikiApp::instance()->window()->lang2(), name);
	}else if (id == web2->getId()){
		if(lang == DualwordWikiApp::instance()->window()->lang2()){
			web2->getPage(lang,	DualwordWikiApp::instance()->window()->lang2(), name);
		}else{
			web2->getTitle(lang, DualwordWikiApp::instance()->window()->lang2(), name);
		}
		web1->getTitle(lang, DualwordWikiApp::instance()->window()->lang1(), name);
	}
}

void DualBrowserForm::linkClicked1(const QUrl& url){
	QString name = getValidUrl(url.toString());
	QString lang = getLinkLang(url.toString());
	if(lang == DualwordWikiApp::instance()->window()->lang1()){
		web1->getPage(lang,	DualwordWikiApp::instance()->window()->lang1(), name);
	}else{
		web1->getTitle(lang, DualwordWikiApp::instance()->window()->lang1(), name);
	}
	web2->getTitle(lang, DualwordWikiApp::instance()->window()->lang2(), name);
}

void DualBrowserForm::linkClicked2(const QUrl& url){
	QString name = getValidUrl(url.toString());
	QString lang = getLinkLang(url.toString());
	if(lang == DualwordWikiApp::instance()->window()->lang2()){
		web2->getPage(lang,	DualwordWikiApp::instance()->window()->lang2(), name);
	}else{
		web2->getTitle(lang, DualwordWikiApp::instance()->window()->lang2(), name);
	}
	web1->getTitle(lang, DualwordWikiApp::instance()->window()->lang1(), name);
}

void DualBrowserForm::changeLang1(const QString& lang1){
	web1->getTitle(web1->getLang(),lang1, getUrl());
	web1->setLang(lang1);
}

void DualBrowserForm::changeLang2(const QString& lang2){
	web2->getTitle(web1->getLang(),lang2, getUrl());
	web2->setLang(lang2);
}

void DualBrowserForm::next (){
	if(nextUrl.length() == 0) return;
	if(web1->getLang() == DualwordWikiApp::instance()->window()->lang1()){
		web1->getPage(web1->getLang(),DualwordWikiApp::instance()->window()->lang1(),nextUrl);
	}else{
		web1->getTitle(web1->getLang(),DualwordWikiApp::instance()->window()->lang1(),nextUrl);
	}
	web2->getTitle(web1->getLang(),DualwordWikiApp::instance()->window()->lang2(),nextUrl);
}

void DualBrowserForm::slotLoadFinished(bool ok){
	QStringList list;
	QWebFrame *frame = web1->page()->mainFrame();
	if(!frame) return;
	QWebElement doc = frame->documentElement();
	if(doc.isNull()) return;
	QWebElementCollection elements = doc.findAll("a[rel=\"mw:WikiLink\"]");
	for(int i=0;elements.count();i++){
		if(i>1000) break;
		if(!(elements[i].attribute("href").startsWith("./"))) continue;
		if(elements[i].attribute("href").trimmed().length()<=0) continue;
		if(elements[i].attribute("href").contains(QRegExp("[\\[:#]"))) continue;
		list << elements[i].attribute("href");
	}
	if(list.size()>0){
		nextUrl = list.value(qrand() % list.size()).replace("./", "");
	}
}

QString DualBrowserForm::getValidUrl(const QString& url){
	 QRegExp reg("(?:\\s*)wikipedia\\.org/wiki/([^#]+)");
	 int pos = reg.indexIn(url);
	 if (pos > -1) {
		 return reg.cap(1);
	 }
	 return "";
}

QString DualBrowserForm::getLinkLang(const QString& link){
	 QRegExp reg("(?:\\s*)([a-zA-Z]{2,2})\\.wikipedia\\.org/wiki/.*");
	 int pos = reg.indexIn(link);
	 if (pos > -1) {
		 return reg.cap(1);
	 }
	 return "";
}

bool DualBrowserForm::scroll(const QUrl& url, Browser* web){
	if(url.hasFragment() & (getUrl() == getValidUrl(url.toString()))){
		web->page()->mainFrame()->scrollToAnchor(url.fragment());
		if(web1 == web){

		}else{

		}
		return true;
	}
	return false;
}

QWebHistory* DualBrowserForm::getHistory(){
	return web1->page()->history();
}

void DualBrowserForm::loadHistory(){
	QAction *a = qobject_cast<QAction*>(sender());
	web1->history()->goToItem(web1->history()->itemAt(a->data().toInt()));
}
