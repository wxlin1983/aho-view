#ifndef PIC_H
#define PIC_H

#include <QPixmap>

class pic {

public:

    explicit pic(QString=QString());
    ~pic();

    bool showable();
    //return true if the pic is showable.
    //it causes the program to load the pic unless it has been unloaded before.

    bool load(); //try to load image, return true if the file is loaded.
    bool unload(); //try to unload image, return true if the file is unloaded.

    bool scale(QSize, unsigned);
    bool deleteme();

    QString name;

    double score_add(double);
    double score_set(double);

    bool isLoaded;

    QPixmap * scaled;

private:

    double score;

    bool isChecked;
    bool isShowable;

    QPixmap * original;

};

#endif // PIC_H
