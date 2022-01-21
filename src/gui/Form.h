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

#include <QtWidgets>
#include <QWebEngineHistory>

class Form : public QWidget {
     Q_OBJECT

public:
	Form(QWidget *p = 0);
	virtual ~Form();
	virtual QString getTitle() const = 0;
	virtual QString getUrl() const = 0;

public slots:
	virtual void load(const QString&) {};
	virtual void load(const QUrl&, int) {};
	virtual void slotLoadFinished(bool) {};
	virtual void back () {};
	virtual void forward () {};
	virtual void reload () {};
	virtual void stop () {};
	virtual void home () {};
	virtual void next () {};
	virtual bool isNext () {return false;};
	virtual void changeLang1 (const QString&) {};
	virtual void changeLang2 (const QString&) {};
	virtual QWebEngineHistory* getHistory(){return 0;};
	virtual void loadHistory(){};
	virtual void changeLayout(){};
	virtual void like(){};
	virtual void dislike(){};
	virtual void clear(){};
	virtual int likeCount(){return 0;};
	virtual int dislikeCount(){return 0;};

signals:
	void titleChanged (const QString&);
	void urlChanged (const QUrl&);
	void statusBarMessage (const QString&);
	void loadFinished(bool);
	void loadStarted();
	void refresh();

};

#endif /* FORM_H_ */
