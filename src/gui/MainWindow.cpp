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
#include "BrowserForm.h"
#include "DualBrowserForm.h"

MainWindow::MainWindow(QWidget *p, Qt::WindowFlags f) : QMainWindow(p, f),
	editUrl(new QLineEdit(this)), combo1(new QComboBox(this)), combo2(new QComboBox(this)),
	form(0), lang("") {
	setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
	actionBack->setIcon(style()->standardIcon(QStyle::SP_ArrowBack, 0, this));
    actionForward->setIcon(style()->standardIcon(QStyle::SP_ArrowForward, 0, this));
    actionReload->setIcon(style()->standardIcon(QStyle::SP_BrowserReload, 0, this));
    actionStop->setIcon(style()->standardIcon(QStyle::SP_BrowserStop, 0, this));
    actionHome->setIcon(style()->standardIcon(QStyle::SP_DirHomeIcon, 0, this));
    actionLike->setIcon(style()->standardIcon(QStyle::SP_ArrowUp, 0, this));
    actionDislike->setIcon(style()->standardIcon(QStyle::SP_ArrowDown, 0, this));
    actionClear->setIcon(style()->standardIcon(QStyle::SP_TrashIcon, 0, this));
    actionLayout->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon, 0, this));
    actionNext->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward, 0, this));
    toolBar->insertWidget(actionLayout,editUrl);
    toolBar->insertSeparator(actionLike);
    toolBar->insertWidget(actionLike,combo1);
    toolBar->insertWidget(actionLike,combo2);
    toolBar->insertSeparator(actionLike);
    setSlots();
    fillCombo();
}

MainWindow::~MainWindow() {

}

void MainWindow::init(){
	readSettings();
	lang = combo2->currentText();
    tab->createBrowser<>();
}

Tab* MainWindow::getTab(){
	return tab;
}

void MainWindow::closeEvent(QCloseEvent *event) {
	writeSettings();
	QMainWindow::closeEvent(event);
}

void MainWindow::showAbout() {
	QString str;
	str.append(qApp->applicationName());
	str.append(" ").append(qApp->applicationVersion()).append("<br>");
	str.append("License: GPL v3 <br/>");
	str.append("Website: <a href='http://github.com/dualword/dualword-wiki'>Dualword-wiki</a><br/>");
	str.append("&copy;2017-2022 Alexander Busorgin <br/>");
	QMessageBox::about(this, tr("About"), str );
}

void MainWindow::currentForm(Form* f) {
	if(form){
	    QObject::disconnect(actionBack,SIGNAL(triggered()), form, SLOT(back()));
	    QObject::disconnect(actionForward,SIGNAL(triggered()), form, SLOT(forward()));
	    QObject::disconnect(actionReload,SIGNAL(triggered()), form, SLOT(reload()));
	    QObject::disconnect(actionStop,SIGNAL(triggered()), form, SLOT(stop()));
	    QObject::disconnect(actionHome,SIGNAL(triggered()), form, SLOT(home()));
	    QObject::disconnect(actionNext,SIGNAL(triggered()), form, SLOT(next()));
	    QObject::disconnect(actionLayout,SIGNAL(triggered()), form, SLOT(changeLayout()));
	    QObject::disconnect(actionLike,SIGNAL(triggered()), form, SLOT(like()));
	    QObject::disconnect(actionDislike,SIGNAL(triggered()), form, SLOT(dislike()));
	    QObject::disconnect(actionClear,SIGNAL(triggered()), form, SLOT(clear()));
	    QObject::disconnect(form,SIGNAL(urlChanged(const QUrl&)), this, SLOT(urlChanged(const QUrl&)));
	    QObject::disconnect(form,SIGNAL(titleChanged(const QString&)), this, SLOT(titleChanged(const QString&)));
	    QObject::disconnect(form,SIGNAL(statusBarMessage(const QString&)),
	    		statusBar(), SLOT(showMessage(const QString&)));
	    QObject::disconnect(form,SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
	    QObject::disconnect(form,SIGNAL(loadStarted()), this, SLOT(loadStarted()));
	    QObject::disconnect(form,SIGNAL(refresh()), this, SLOT(refresh()));
		QObject::disconnect(combo1,SIGNAL(currentIndexChanged(const QString&)),
				form, SLOT(changeLang1(const QString&)));
		QObject::disconnect(combo2,SIGNAL(currentIndexChanged(const QString&)),
				form, SLOT(changeLang2(const QString&)));
	}
	form = f;
    QObject::connect(actionBack,SIGNAL(triggered()), form, SLOT(back()));
    QObject::connect(actionForward,SIGNAL(triggered()), form, SLOT(forward()));
    QObject::connect(actionReload,SIGNAL(triggered()), form, SLOT(reload()));
    QObject::connect(actionStop,SIGNAL(triggered()), form, SLOT(stop()));
    QObject::connect(actionHome,SIGNAL(triggered()), form, SLOT(home()));
    QObject::connect(actionNext,SIGNAL(triggered()), form,SLOT(next()));
    QObject::connect(actionLayout,SIGNAL(triggered()), form,SLOT(changeLayout()));
    QObject::connect(actionLike,SIGNAL(triggered()), form, SLOT(like()));
    QObject::connect(actionDislike,SIGNAL(triggered()), form, SLOT(dislike()));
    QObject::connect(actionClear,SIGNAL(triggered()), form, SLOT(clear()));
    QObject::connect(form,SIGNAL(urlChanged(const QUrl&)), SLOT(urlChanged(const QUrl&)));
    QObject::connect(form,SIGNAL(titleChanged(const QString&)), SLOT(titleChanged(const QString&)));
    QObject::connect(form,SIGNAL(statusBarMessage(const QString&)),	statusBar(), SLOT(showMessage(const QString&)));
    QObject::connect(form,SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
    QObject::connect(form,SIGNAL(loadStarted()), SLOT(loadStarted()));
    QObject::connect(form,SIGNAL(refresh()), SLOT(refresh()));
	QObject::connect(combo1,SIGNAL(currentIndexChanged(const QString&)), form, SLOT(changeLang1(const QString&)));
	QObject::connect(combo2,SIGNAL(currentIndexChanged(const QString&)), form, SLOT(changeLang2(const QString&)));

	titleChanged(form->getTitle());
	urlChanged(form->getUrl());
	actionNext->setEnabled(form->isNext());
	actionLayout->setEnabled(form->isNext());
	actionLike->setEnabled(form->isNext());
	actionDislike->setEnabled(form->isNext());
	actionClear->setEnabled(form->isNext());
	refresh();
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

void MainWindow::fillCombo(){
	QStringList list;
	 list << "ace" << "af" << "als" << "am" << "an" << "ar" << "arz" << "ast" << "az" << "azb";
	 list  << "ba" << "bar" << "be" << "bcl" << "bpy" << "bg" << "bn" << "bs" << "br" << "bug";
	 list << "ca" << "cdo" << "ce" << "ceb" << "ckb" << "crh" << "cs" << "cv" << "cy";
	 list << "da" << "de" << "diq";
	 list << "en" << "es" << "el" << "eml" << "eo" << "et" << "eu";
	 list << "fa" << "fr" << "fi" << "fo" << "frr" << "fy";
	 list << "ga" << "gd" << "gl" << "gu";
	 list << "ha" << "hi" << "he" << "hr" << "hsb" << "ht" << "hu"  << "hy";
	 list << "ia" << "it" << "id" << "io" << "ilo" << "is";
	 list << "ja" << "jv";
	 list << "ka" << "ko" << "kk" << "kn" << "ku" << "ky";
	 list << "la" << "lb" << "li" << "lij" << "lmo" << "lv" << "lt";
	 list << "mai" << "mg" << "mhr" << "min"<< "ml" << "mk" << "mn" << "mrj" << "mr" << "ms" << "my" << "mzn";
	 list << "nap" << "nds" << "nn" << "ne" << "new" << "no" << "nl" << "nv";
	 list << "oc" << "or" << "os";
	 list << "pa" << "pl" << "pms" << "pnb" << "ps" << "pt";
	 list << "qu";
	 list << "ro" << "ru";
	 list << "sa" << "sah" << "sco" << "scn" << "sd" << "simple" << "se" << "sh" << "si" << "sr" << "sq" << "sk" << "sl" << "su" << "sv" << "sw" << "szl";
	 list << "ta" << "te" << "tg" << "th" << "tr" << "tl" << "tt";
	 list << "uk" << "ur" << "uz";
	 list << "vec" << "vi" << "vo";
	 list << "xmf";
	 list << "yi" << "yo";
	 list << "wa" << "war" << "wuu";
	 list << "zh" << "zu";

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

void MainWindow::loadFinished(bool ok){
	actionStop->setEnabled(false);
	actionReload->setEnabled(true);
	if(form->isNext()){
		actionLike->setEnabled(true);
		actionDislike->setEnabled(true);
	}
}

void MainWindow::loadStarted(){
	actionStop->setEnabled(true);
	actionReload->setEnabled(false);
	if(form->isNext()){
		actionLike->setEnabled(false);
		actionDislike->setEnabled(false);
	}
}

void MainWindow::showHistory(){
	menuHistory->clear();
	QWebEngineHistory* h;
	if(!form) return;
	h = form->getHistory();
	if(!h) return;
	for(int i=h->items().size()-1; i>=0; i--){
		QAction *a = new QAction(h->itemAt(i).title(), menuHistory);
		a->setData(i);
		QObject::connect(a, SIGNAL(triggered()), form, SLOT(loadHistory()));
		menuHistory->addAction(a);
	}
}

void MainWindow::combo2change(const QString& txt){
	if(combo2->currentText() == lang) return;
	lang = txt;
}

void MainWindow::refresh(){
	actionLike->setToolTip("Like (" + QString::number(form->likeCount()) + ")");
	actionDislike->setToolTip("Dislike (" + QString::number(form->dislikeCount()) + ")");
}
