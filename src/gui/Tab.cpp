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

#include "Tab.h"

Tab::Tab(QWidget *p) : QTabWidget(p) {
	setTabsClosable(true);
	setElideMode(Qt::ElideRight);
	setContextMenuPolicy(Qt::CustomContextMenu);
    setTabsClosable(true);
    setMovable(true);
    connect(this, &QTabWidget::currentChanged, [this](){emit currentForm(qobject_cast<Form*>(currentWidget()));});
    connect(this, &QTabWidget::tabCloseRequested, this, &Tab::closeTab);
    connect(this, &QTabWidget::customContextMenuRequested, this, &Tab::contextMenuRequested);
}

Tab::~Tab() {

}

void Tab::contextMenuRequested(const QPoint &position) {
	QMenu menu;
    menu.addAction(tr("Browser Tab"), [this]{createBrowser<>();});
    menu.addAction(tr("Dual Browser Tab"), [this]{createBrowser<DualBrowserForm>();});
    menu.exec(QCursor::pos());
}

void Tab::closeTab(int i){
	if(this->count() == 1) createBrowser<>();
	widget(i)->deleteLater();
	removeTab(i);
}

void Tab::setToolTip(const QString& s){
	auto f = qobject_cast<Form*>(sender());
	int i = indexOf(f);
	if (i != -1) {
		setTabText(i, f->getTitle().left(25));
		setTabToolTip(i, f->getUrl());
	}
}
