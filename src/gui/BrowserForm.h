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

#ifndef SRC_GUI_BROWSERFORM_H_
#define SRC_GUI_BROWSERFORM_H_

#include "Form.h"
#include <QScopedPointer>
#include <QObject>

class Browser;

class BrowserForm : public Form {
	Q_OBJECT

public:
	BrowserForm(QWidget *p);
	virtual ~BrowserForm();

public:
	virtual QString getTitle() const;
	virtual QString getUrl() const;
	virtual bool canChangeUrl();


public slots:
	void load(const QString&);
	void back();
	void forward ();
	void reload ();
	void stop ();
	void home();

signals:
	void titleChanged (const QString&);
	void urlChanged (const QUrl&);
	void statusBarMessage (const QString&);

private:
	QScopedPointer<Browser> browser;

};

#endif /* SRC_GUI_BROWSERFORM_H_ */
