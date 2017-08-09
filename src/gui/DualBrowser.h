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

#ifndef SRC_GUI_DUALBROWSER_H_
#define SRC_GUI_DUALBROWSER_H_

#include "Browser.h"

class Get;

class DualBrowser : public Browser{
	Q_OBJECT

public:
	DualBrowser(QWidget *p = 0, int id = 0);
	virtual ~DualBrowser();
	void getTitle(const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString());
	void getPage(const QString& lang1 = QString(), const QString& lang2 = QString(),
			const QString& name = QString());
	const QString& getLang() const {return lang;}
	void setLang(const QString& lang){this->lang = lang;}

signals:
	void linkClicked(QUrl);

protected slots:
	bool isValidUrl(const QUrl&);
	virtual void slotLinkClicked2(const QUrl&) {};

protected:
	QString lang;

private slots:
	void slotLinkClicked(const QUrl&);

private:
	QScopedPointer<Get> req;
};


#endif /* SRC_GUI_DUALBROWSER_H_ */