#ifndef AHOVIEW_H
#define AHOVIEW_H

#include "pic.h"
#include "picaxiv.h"

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsView>
#include <QDir>

namespace Ui {
class ahoview;
class pic;
class picaxiv;
}

class ahoview : public QMainWindow
{
    Q_OBJECT

public:

    explicit ahoview(QWidget *parent = 0);
    ~ahoview();

private slots:

    void openfile();
    void opendir();
    void closefiledir();

private:

    std::vector<picaxiv *> allaxiv;

    std::vector<picaxiv *>::iterator offset_it(int=0);
    std::vector<picaxiv *>::iterator axiv_it;
    //always need to check whether allaxiv is empty before dereference axiv_it.

    void plot();
    void clearplot();
    int changeaxiv(int);
    int closeaxiv(int);
    //return 0 if currentaxiv is changed.
    void createActions();
    void createMenus();

    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);

    unsigned picRescaleMode;
    unsigned windowSizeMode;

    Ui::ahoview *ui;
    QLabel *qimglabel;

    QAction *openfileAct;
    QAction *opendirAct;
    QAction *closeAct;
    QAction *exitAct;

    QMenu *fileMenu;

};

#endif // AHOVIEW_H
