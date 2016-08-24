#ifndef AHOVIEW_H
#define AHOVIEW_H

#include "pic.h"
#include "picaxiv.h"

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsView>
#include <QDir>
#include <set>

namespace Ui {
class ahoview;
class pic2;
class picaxiv2;
}

class ahoview : public QMainWindow
{
    Q_OBJECT

public:

    explicit ahoview(QWidget *parent = 0);
    ~ahoview();

private slots:

    void opendir();
    void closefiledir();

private:

    std::list<picaxiv *> allaxiv;

    std::list<picaxiv *>::iterator offset_it(int=0);
    std::list<picaxiv *>::iterator axiv_it;
    //always need to check whether allaxiv is empty before dereference axiv_it.
    std::list<pic *>::iterator offsetboth(int, int);

    void updatemc();

    void plot();
    void toggleplot();
    void togglefullscreen();
    int changeaxiv(int);
    int closeaxiv(int);
    //return 0 if currentaxiv is changed.
    int openaxiv(QString);
    //return 0 if an axiv is opened.

    void createActions();
    void createMenus();

    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    unsigned picRescaleMode;
    unsigned windowSizeMode;

    Ui::ahoview *ui;
    QLabel *qimglabel;

    //QAction *openfileAct;
    QAction *opendirAct;
    QAction *closeAct;
    QAction *exitAct;

    QMenu *fileMenu;

};

#endif // AHOVIEW_H
