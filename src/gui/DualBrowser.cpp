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

#include "DualBrowser.h"
#include "Get.h"

bool DualWebPage::acceptNavigationRequest(const QUrl& url, QWebEnginePage::NavigationType type, bool mframe){
	if(type == NavigationTypeLinkClicked){
		if(isValidUrl(url)){
			emit linkClicked(url);
		    return true;
		}else{
			return false;
		}
	}
    return QWebEnginePage::acceptNavigationRequest(url, type, mframe);
}

bool DualWebPage::isValidUrl(const QUrl& url){
	 QRegExp reg("(?:\\s*)([a-zA-Z]{2,6})\\.wikipedia\\.org/wiki/.+");
	 int pos = reg.indexIn(url.toString());
	 if (pos > -1) {
		 return true;
	 }
	 emit statusBarMessage("Blocked:" + url.host());
	 return false;
}

DualBrowser::DualBrowser(QWidget *p, int id) : Browser(p, id), lang("") {
	setPage(new DualWebPage(this));

}

DualBrowser::~DualBrowser() {

}

void DualBrowser::getTitle(const QString& lang1, const QString& lang2, const QString& name){
	req.reset(new GetTitle(this, lang1,	lang2, name, this));
	req->get();
}

void DualBrowser::getPage(const QString& lang1, const QString& lang2, const QString& name){
	req.reset(new GetPage(this, lang1, lang2, name, this));
	req->get();
}
