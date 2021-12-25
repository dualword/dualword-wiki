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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets>
#include <QUrl>
#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindowForm {
  Q_OBJECT

public:
	MainWindow(QWidget *p=0, Qt::WindowFlags f=0);
	virtual ~MainWindow();
	void init();
	Tab* getTab();

protected:
    void closeEvent(QCloseEvent *);

public slots:
	void currentForm(Form*);
	void urlChanged(const QUrl&);
	const QString lang1() const {return combo1->currentText();};
	const QString lang2() const {return combo2->currentText();};
	void loadFinished(bool);
	void loadStarted();

private slots:
	void setSlots();
	void showAbout();
	void exit();
	void titleChanged (const QString& title);
	void load();
	void fillCombo();
	void writeSettings();
	void readSettings();
	void showHistory();
	void combo2change(const QString&);
	void refresh();

private:
	QLineEdit* editUrl;
	QComboBox *combo1, *combo2;
    Form* form;
    QToolButton *lang21, *lang22;
    QString lang;
};

#endif /* MAINWINDOW_H_ */
