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

#ifndef FORM_H_
#define FORM_H_

#include <QtGui>

#include "app/DualwordWikiApp.h"

class Form : public QWidget {
     Q_OBJECT

public:
	Form(QWidget *p = 0);
	virtual ~Form();
	virtual QString getTitle() const = 0;
	virtual QString getUrl() const = 0;
	virtual bool canChangeUrl() = 0;

public slots:
	virtual void load(const QString&) {};
	virtual void back () {};
	virtual void forward () {};
	virtual void reload () {};
	virtual void stop () {};
	virtual void home () {};

};

#endif /* FORM_H_ */
