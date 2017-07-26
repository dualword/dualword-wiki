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

#include <QtGui>
#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindowForm {
  Q_OBJECT

public:
	MainWindow(QWidget *p=0, Qt::WindowFlags f=0);
	virtual ~MainWindow();
	void init();

protected:
    void closeEvent(QCloseEvent *);

public slots:
	void currentForm(Form*);
	void urlChanged(const QUrl&);
	const QString lang1() const {return combo1->currentText();};
	const QString lang2() const {return combo2->currentText();};

private slots:
	void setSlots();
	void showAbout();
	void exit();
	void titleChanged (const QString& title);
	void load();
	void currentIndexChanged (const QString&);
	void fillCombo();
	void writeSettings();
	void readSettings();

private:
	QLineEdit* editUrl;
	QComboBox *combo1, *combo2;
    Form* form;
};

#endif /* MAINWINDOW_H_ */
