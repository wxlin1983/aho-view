#ifndef PICAXIV_H
#define PICAXIV_H

#include "pic.h"

class picaxiv {

public:

    explicit picaxiv(QString=QString());
    ~picaxiv();

    bool isvalid();

    int load(int);
    int unload(std::vector<pic *>::iterator);
    //release the memory of qpixmap (original and scaled) of what is pointed at by the iterator if the iterator is not pic_it.
    //this is done by copying the name and status of the pic, creating a new one, and then deleting the old one.

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
    //return iterator pointing to a "good" pic.
    //this will load the picture.
    std::vector<pic *>::iterator pic_it;

};

#endif // PICAXIV_H
