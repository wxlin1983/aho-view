#include "ahoview.h"
#include "ui_ahoview.h"

//my include
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QMimeData>
//end my include

ahoview::ahoview(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ahoview)
{

    ui->setupUi(this);

    //QRect rec = QApplication::desktop()->screenGeometry();
    //setFixedSize(rec.width()*0.75,rec.height()*0.75);

    qimglabel=new QLabel;
    setCentralWidget(qimglabel);

    picRescaleMode=0;
    windowSizeMode=0;

    createActions();
    createMenus();

    setWindowTitle("The AHO Viewer");

    setAcceptDrops(true);

}

void ahoview::updatemc() {


    double totalscore=0;
    for (std::list<picaxiv *>::iterator i=allaxiv.begin();i!=allaxiv.end();i++) {
        for (std::list<pic *>::iterator j=(*i)->axiv.begin();j!=(*i)->axiv.end();j++) {
            totalscore=totalscore+(*j)->score_add(0);
        }
    }
    for (std::list<picaxiv *>::iterator i=allaxiv.begin();i!=allaxiv.end();i++) {
        for (std::list<pic *>::iterator j=(*i)->axiv.begin();j!=(*i)->axiv.end();j++) {
            (*j)->score_set(30*((*j)->score_set(0)/totalscore)-1);
        }
    }

    std::set<pic *> tmpall=std::set<pic *> ();

    pic * tmp= *offsetboth(0,0);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(1,0);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(-1,0);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(0,10);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(0,-10);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(0,1);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}
    tmp= *offsetboth(0,-1);
    if (tmpall.count(tmp)==0) {tmpall.insert(tmp);}

    for(std::set<pic *>::iterator kkk=tmpall.begin();kkk!=tmpall.end();kkk++) {
        (*kkk)->score_add(2);
    }

}

ahoview::~ahoview() {

    for (std::list<picaxiv *>::iterator i = allaxiv.begin(); i != allaxiv.end(); i++) {delete (*i);}
    delete ui;

}

std::list<pic *>::iterator ahoview::offsetboth(int axivm, int picm) {

    return ((*(offset_it(axivm)))->ptr)(picm);

}

std::list<picaxiv *>::iterator ahoview::offset_it(int offset) {
    if (allaxiv.empty()||(allaxiv.size()==1)||(offset==0)) {return axiv_it;}
    std::list<picaxiv *>::iterator tmp(axiv_it);
    int k=1;
    if (offset<0) {k=-1;}
    for (int i=0;i<offset*k;i++) {
        if (k<0&&tmp==allaxiv.begin()) {tmp=allaxiv.end();}
        if (k>0) {tmp++;} else {tmp--;}
        if (k>0&&tmp==allaxiv.end()) {tmp=allaxiv.begin();}
    }
    return tmp;
}

int ahoview::changeaxiv(int offset) {
    //doesn't make change if the axiv is not showable
    if ((offset==0)||allaxiv.empty()) {return 1;}
    std::list<picaxiv *>::iterator tmp=offset_it(offset);
    if (tmp==axiv_it) {return 1;}
    axiv_it=tmp;
    return 0;
}

int ahoview::closeaxiv(int offset) {
    if (allaxiv.empty()) {return 0;}
    if (allaxiv.size()>1) {
        std::list<picaxiv *>::iterator tmp=offset_it(offset);
        delete *axiv_it;
        axiv_it=allaxiv.erase(tmp);
        if (axiv_it==allaxiv.end()) {axiv_it=allaxiv.begin();}
        plot();
        return 0;
    } else {
        //size=1.
        delete *axiv_it;
        axiv_it=allaxiv.erase(axiv_it);
        toggleplot();
        setWindowTitle("The AHO Viewer");
        return 0;
    }
    return 1;
}

int ahoview::openaxiv(QString dir) {
    if (!QFileInfo(dir).exists()) {
        dir = QFileDialog::getExistingDirectory(this,
                                                tr("Open a folder"), QDir::homePath(),
                                                QFileDialog::ShowDirsOnly);
    }
    if (!dir.isEmpty()) {
        picaxiv* picfolderptrtmp=new picaxiv(QFileInfo(dir).absoluteFilePath());
        if (picfolderptrtmp->showable()) {
            allaxiv.push_front(picfolderptrtmp);
            axiv_it=allaxiv.begin();
            plot();
        } else {delete picfolderptrtmp;}
        return 0;
    }
    return 1;
}

void ahoview::closefiledir() {
    closeaxiv(0);
}

void ahoview::opendir() {
    openaxiv("");
}

void ahoview::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(1)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_Right) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(-1)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_PageUp) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(-10)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_PageDown) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(10)) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_End) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->end()) {
            plot();
        }
    }
    else if(event->key() == Qt::Key_Home) {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->begin()) {
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
        toggleplot();
    }
    else if(event->key() == Qt::Key_G) {
        togglefullscreen();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void ahoview::mouseReleaseEvent ( QMouseEvent * event ) {

    if(event->button() == Qt::LeftButton)
    {
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(1)) {
            plot();
        }
    } else if (event->button() == Qt::RightButton){
        if (allaxiv.empty()) {return;}
        std::list<pic *>::iterator tmp=offsetboth(0,0);
        if (tmp!=(*axiv_it)->mv(-1)) {
            plot();
        }
    } else {
        QWidget::mouseReleaseEvent(event);
    }
}

void ahoview::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void ahoview::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QString dirtmp;
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            dirtmp=urlList.at(i).toLocalFile();
            openaxiv(dirtmp);
        }
    }
}

void ahoview::resizeEvent(QResizeEvent *) {
    plot();
}

void ahoview::plot() {
    if (allaxiv.empty()) {return;}
    if((*(*axiv_it)->ptr())->showable()) {
        (*axiv_it)->scale(0,qimglabel->size(),picRescaleMode);
        qimglabel->setAlignment(Qt::AlignCenter);
        qimglabel->setPixmap(*((*(*axiv_it)->ptr())->scaled));
        updatemc();
        setWindowTitle((*(*axiv_it)->ptr())->name);
    }
}

void ahoview::toggleplot() {
    qimglabel->clear();
}

void ahoview::togglefullscreen() {

    if (this->isFullScreen()) {this->showNormal();}
    else if (this->isMaximized()){this->showFullScreen();}
    else {this->showMaximized();}

}

void ahoview::createMenus() {
    fileMenu = new QMenu(tr("&File"), this);
    //    fileMenu->addAction(openfileAct);
    fileMenu->addAction(opendirAct);
    fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addMenu(fileMenu);
}

void ahoview::createActions() {

    opendirAct = new QAction(tr("Open &Directory..."), this);
    opendirAct->setShortcut(tr("Ctrl+D"));
    connect(opendirAct, SIGNAL(triggered()), this, SLOT(opendir()));

    closeAct = new QAction(tr("Close Vie&w..."), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closefiledir()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}
