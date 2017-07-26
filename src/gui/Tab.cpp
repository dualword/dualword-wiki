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

#include "app/DualwordWikiApp.h"
#include "Tab.h"
#include "BrowserForm.h"
#include "DualBrowserForm.h"

Tab::Tab(QWidget *p) : QTabWidget(p) {
	setTabsClosable(true);
	setElideMode(Qt::ElideRight);
	setContextMenuPolicy(Qt::CustomContextMenu);
    setTabsClosable(true);
    setMovable(true);
    connect(this, SIGNAL(currentChanged (int)), this, SLOT(currentChanged(int)));
    connect(this, SIGNAL(tabCloseRequested (int)), this, SLOT(closeTab(int)));
    connect(this, SIGNAL(NewBrowser()), this, SLOT(createBrowser()));
    connect(this, SIGNAL(NewDualBrowser()), this, SLOT(createDualBrowser()));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
    		this, SLOT(contextMenuRequested(QPoint)));
}

Tab::~Tab() {

}

void Tab::contextMenuRequested(const QPoint &position) {
	QMenu menu;
    menu.addAction(tr("Browser Tab"), this, SIGNAL(NewBrowser()));
    menu.addAction(tr("Dual Browser Tab"), this, SIGNAL(NewDualBrowser()));
    menu.exec(QCursor::pos());
}

int Tab::createBrowser(){
	BrowserForm *f = new BrowserForm(this);
	f->home();
	return addTab(f,"Browser");
}

int Tab::createDualBrowser(){
	DualBrowserForm *f = new DualBrowserForm(this);
	f->home();
	return addTab(f,"Dual Browser");
}

void Tab::closeTab(int i){
	if(this->count() == 1)
		createBrowser();
	removeTab(i);
}

void Tab::currentChanged (int index){
	Form* f = qobject_cast<Form*>(currentWidget());
	emit currentForm(f);
}
