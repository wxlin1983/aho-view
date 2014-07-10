#ifndef PICAXIV_H
#define PICAXIV_H

#include "pic.h"

class picaxiv {

public:

    explicit picaxiv(QString=QString());
    ~picaxiv();

    bool showable();
    int load(int);
    int scale(int, QSize, unsigned);
    //return 0 if scaled got updated, 1 if it's not updated

    std::vector<pic *>::iterator ptr(int=0);
    //return an iterator to pic at an offset.
    std::vector<pic *>::iterator mv(int=0);
    //return an iterator to pic at an offset.
    //also change pic_it that indicate the current position.

    QString name;
    int status;
    //0: unknown, 1: showable, 2: not showable;
    std::vector<pic *> axiv;

private:

    std::vector<pic *>::iterator offset_it(int=0);
    std::vector<pic *>::iterator offset_it_checked(int=0);
    //return iterator point to a "good" pic.
    std::vector<pic *>::iterator pic_it;

};

#endif // PICAXIV_H
