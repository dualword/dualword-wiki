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

#include "MainWindow.h"
#include "Form.h"

MainWindow::MainWindow(QWidget *p, Qt::WindowFlags f) : QMainWindow(p, f),
	editUrl(new QLineEdit(this)), combo1(new QComboBox(this)), combo2(new QComboBox(this)),
	form(0) {
	setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
	actionBack->setIcon(style()->standardIcon(QStyle::SP_ArrowBack, 0, this));
    actionForward->setIcon(style()->standardIcon(QStyle::SP_ArrowForward, 0, this));
    actionReload->setIcon(style()->standardIcon(QStyle::SP_BrowserReload, 0, this));
    actionStop->setIcon(style()->standardIcon(QStyle::SP_BrowserStop, 0, this));
    actionHome->setIcon(style()->standardIcon(QStyle::SP_DirHomeIcon, 0, this));
    actionNext->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward, 0, this));
    toolBar->insertWidget(actionNext,editUrl);
    toolBar->insertWidget(actionNext,combo1);
    toolBar->insertWidget(actionNext,combo2);
    fillCombo();
    setSlots();
}

MainWindow::~MainWindow() {

}

void MainWindow::init(){
	readSettings();
    tab->createBrowser();
}

void MainWindow::closeEvent(QCloseEvent *event) {
	writeSettings();
    event->accept();
}

void MainWindow::exit() {
	qApp->quit();
}

void MainWindow::showAbout() {
	QString str;
	str.append(qApp->applicationName());
	str.append(" ").append(qApp->applicationVersion()).append("<br>");
	str.append("License: GPL v3 <br/>");
	str.append("&copy;2017 Alexander Busorgin <br/>");
	QMessageBox::about(this, tr("About"), str );
}

void MainWindow::currentForm(Form* f) {
	if(form){
	    QObject::disconnect(actionBack,SIGNAL(triggered()), form, SLOT(back()));
	    QObject::disconnect(actionForward,SIGNAL(triggered()), form, SLOT(forward()));
	    QObject::disconnect(actionReload,SIGNAL(triggered()), form, SLOT(reload()));
	    QObject::disconnect(actionStop,SIGNAL(triggered()), form, SLOT(stop()));
	    QObject::disconnect(actionHome,SIGNAL(triggered()), form, SLOT(home()));
	    QObject::disconnect(form,SIGNAL(urlChanged(const QUrl&)),
	    		this, SLOT(urlChanged(const QUrl&)));
	    QObject::disconnect(form,SIGNAL(titleChanged(const QString&)),
	    		this, SLOT(titleChanged(const QString&)));
	    QObject::disconnect(form,SIGNAL(statusBarMessage(const QString&)),
	    		statusBar(), SLOT(showMessage(const QString&)));
		QObject::disconnect(combo2,SIGNAL(currentIndexChanged(const QString&)),
				form, SLOT(changeLang2(const QString&)));
	}
	form = f;
    QObject::connect(actionBack,SIGNAL(triggered()), form, SLOT(back()));
    QObject::connect(actionForward,SIGNAL(triggered()), form, SLOT(forward()));
    QObject::connect(actionReload,SIGNAL(triggered()), form, SLOT(reload()));
    QObject::connect(actionStop,SIGNAL(triggered()), form, SLOT(stop()));
    QObject::connect(actionHome,SIGNAL(triggered()), form, SLOT(home()));
    QObject::connect(form,SIGNAL(urlChanged(const QUrl&)),
    		this, SLOT(urlChanged(const QUrl&)));
    QObject::connect(form,SIGNAL(titleChanged(const QString&)),
    		this, SLOT(titleChanged(const QString&)));
    QObject::connect(form,SIGNAL(statusBarMessage(const QString&)),
    		statusBar(), SLOT(showMessage(const QString&)));
	QObject::connect(combo2,SIGNAL(currentIndexChanged(const QString&)),
			form, SLOT(changeLang2(const QString&)));

	titleChanged(form->getTitle());
	urlChanged(form->getUrl());
}

void MainWindow::titleChanged(const QString& title) {
	QString t(title);
	if(t.length() > 0)
		t.append(" - ");
	setWindowTitle(t.append(QApplication::applicationName()));
}

void MainWindow::load() {
	form->load(editUrl->text());
}

void MainWindow::urlChanged(const QUrl& url) {
	editUrl->setText(form->getUrl());
	editUrl->setCursorPosition(0);
}

void MainWindow::currentIndexChanged (const QString& text){
	if(combo1->currentText() == combo2->currentText()) return;
}

void MainWindow::fillCombo(){
	QStringList list;
	 list << "ar" << "az";
	 list << "bg" << "be";
	 list << "ca";
	 list << "de" << "da";
	 list << "en" << "es" << "el" << "et" << "eu";
	 list << "fr" << "fa" << "fi";
	 list << "hi" << "he" << "hu"  << "hy";
	 list << "ja";
	 list << "it";
	 list << "ka" << "ko" << "kk";
	 list << "lv" << "lt";
	 list << "mn";
	 list << "no" << "nl";
	 list << "pt" << "pl";
	 list << "ru" << "ro";
	 list << "sr" << "sk" << "sl" << "sv";
	 list << "tr" << "th" << "tr";
	 list << "uk" << "uz";
	 list << "vi";
	 list << "zh";
	 combo1->addItems(list);
	 combo2->addItems(list);
     combo1->setCurrentIndex(combo1->findText("en"));
     combo2->setCurrentIndex(combo2->findText("en"));
}

void MainWindow::writeSettings(){
     QSettings settings("Dualword", "Dualword-wiki");
     settings.beginGroup("MainWindow");
     settings.setValue("lang1", combo1->currentText());
     settings.setValue("lang2", combo2->currentText());
     settings.endGroup();
 }

 void MainWindow::readSettings(){
     QSettings settings("Dualword", "Dualword-wiki");
     settings.beginGroup("MainWindow");
	 if(settings.contains("lang1") & settings.contains("lang2")){
	     combo1->setCurrentIndex(combo1->findText(settings.value("lang1").toString()));
	     combo2->setCurrentIndex(combo2->findText(settings.value("lang2").toString()));
	 }
     settings.endGroup();
 }
