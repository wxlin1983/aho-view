#ifndef PIC_H
#define PIC_H

#include <QPixmap>

class pic {

public:

    explicit pic(QString=QString());
    ~pic();

    int load();
    //after load(), the status will be either 1 or 2.
    int scale(QSize, unsigned);
    //return 0 if scaled got updated, 1 if it's not updated

    QString name;
    int status;
    //0: unknown, 1: is a picture, 2: not a picture;
    QPixmap scaled;

private:

    QPixmap original;

};

#endif // PIC_H
