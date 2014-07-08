#include "ahoview.h"
#include "ui_ahoview.h"

//my include
#include <vector>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QKeyEvent>
//end my include

ahoview::ahoview(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ahoview)
{
    ui->setupUi(this);

    qimglabel=new QLabel;
    setCentralWidget(qimglabel);

    picRescaleMode=0;
    windowSizeMode=0;

    //std::vector<picaxiv *> allaxiv (0);

    createActions();
    createMenus();
}

ahoview::~ahoview() {
    for (std::vector<picaxiv *>::iterator i = allaxiv.begin(); i != allaxiv.end(); ++i) {delete (*i);}
    delete ui;
}

std::vector<picaxiv *>::iterator ahoview::offset_it(int offset) {
    if (allaxiv.empty()||(allaxiv.size()==1)||(offset==0)) {return axiv_it;}
    std::vector<picaxiv *>::iterator tmp(axiv_it);
    int k=1;
    if (offset<0) {k=-1;}
    for (int i=0;i<offset*k;i++) {
        if (k<0&&tmp==allaxiv.begin()) {tmp=allaxiv.end();}
        tmp=tmp+k;
        if (k>0&&tmp==allaxiv.end()) {tmp=allaxiv.begin();}
    }
    return tmp;
}

int ahoview::changeaxiv(int offset) {
    //doesn't make change if the axiv is not showable
    if ((offset==0)||allaxiv.empty()) {return 1;}
    std::vector<picaxiv *>::iterator tmp=offset_it(offset);
    if (tmp==axiv_it) {return 1;}
    if (!(*tmp)->showable()) {return 1;}
    else {
        axiv_it=tmp;
        return 0;
    }
    return 1;
}

int ahoview::closeaxiv(int offset) {
    if (allaxiv.empty()) {return 0;}
    if (allaxiv.size()>1) {
        std::vector<picaxiv *>::iterator tmp=offset_it(offset);
        delete *axiv_it;
        axiv_it=allaxiv.erase(tmp);
        if (axiv_it==allaxiv.end()) {axiv_it=allaxiv.begin();}
        plot();
        return 0;
    } else {
        //size=1.
        delete *axiv_it;
        axiv_it=allaxiv.erase(axiv_it);
        clearplot();
        return 0;
    }
    return 1;
}

void ahoview::closefiledir() {
    closeaxiv(0);
}

void ahoview::openfile() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
    if (!fn.isEmpty()) {
        picaxiv* picfolderptrtmp=nullptr;
        picfolderptrtmp=new picaxiv(QFileInfo(fn).absoluteFilePath());
        if (picfolderptrtmp!=nullptr) {
            //add file only when it's showable, i.e., status!=2.
            if (picfolderptrtmp->showable()) {
                allaxiv.push_back(picfolderptrtmp);
                axiv_it=allaxiv.end()-1;
                plot();
            }
        }
    }
}

void ahoview::opendir() {
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open Folder"), QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty()) {
        picaxiv* picfolderptrtmp=nullptr;
        picfolderptrtmp=new picaxiv(QFileInfo(dir).absoluteFilePath());
        if (picfolderptrtmp!=nullptr) {
            //add folder only when it's showable.
            if (picfolderptrtmp->showable()) {
                allaxiv.push_back(picfolderptrtmp);
                axiv_it=allaxiv.end()-1;
                plot();
            }
        }
    }
}

void ahoview::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        if (allaxiv.empty()) {return;}
        std::vector<pic *>::iterator tmp=(*axiv_it)->ptr();
        if (tmp!=(*axiv_it)->mv(-1)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_Right) {
        if (allaxiv.empty()) {return;}
        std::vector<pic *>::iterator tmp=(*axiv_it)->ptr();
        if (tmp!=(*axiv_it)->mv(1)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_PageUp) {
        if (allaxiv.empty()) {return;}
        std::vector<pic *>::iterator tmp=(*axiv_it)->ptr();
        if (tmp!=(*axiv_it)->mv(-10)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_PageDown) {
        if (allaxiv.empty()) {return;}
        std::vector<pic *>::iterator tmp=(*axiv_it)->ptr();
        if (tmp!=(*axiv_it)->mv(10)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_Up) {
        if (!allaxiv.empty()) {
            if (changeaxiv(1)==0) {
                plot();
            }
        }
    }
    else if(event->key() == Qt::Key_Down) {
        if (!allaxiv.empty()) {
            if (changeaxiv(-1)==0) {
                plot();
            }
        }
    }
    else if(event->key() == Qt::Key_Escape) {
        clearplot();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void ahoview::resizeEvent(QResizeEvent * event) {
    plot();
}

void ahoview::plot() {
    if (allaxiv.empty()) {return;}
    if (!(*axiv_it)->showable()) {return;}
    (*axiv_it)->scale(0,qimglabel->size(),picRescaleMode);
    if((*(*axiv_it)->ptr())->status!=2) {
        qimglabel->setAlignment(Qt::AlignHCenter);
        qimglabel->setAlignment(Qt::AlignVCenter);
        qimglabel->setPixmap((*(*axiv_it)->ptr())->scaled);
    }
}

void ahoview::clearplot() {
    qimglabel->clear();
}

void ahoview::createMenus() {
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openfileAct);
    fileMenu->addAction(opendirAct);
    fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addMenu(fileMenu);
}

void ahoview::createActions() {
    openfileAct = new QAction(tr("Open &file..."), this);
    openfileAct->setShortcut(tr("Ctrl+O"));
    connect(openfileAct, SIGNAL(triggered()), this, SLOT(openfile()));

    opendirAct = new QAction(tr("Open &directory..."), this);
    opendirAct->setShortcut(tr("Ctrl+D"));
    connect(opendirAct, SIGNAL(triggered()), this, SLOT(opendir()));

    closeAct = new QAction(tr("Close file or directory..."), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closefiledir()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

//        QMessageBox msgBox;
//        msgBox.setText("The document has been +1.");
//        msgBox.exec();