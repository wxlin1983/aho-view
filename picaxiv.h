#ifndef PICAXIV_H
#define PICAXIV_H

#include "pic.h"

class picaxiv {

public:

    explicit picaxiv(QString=QString());
    ~picaxiv();

    bool showable();
    //return true if the axiv is showable.
    //it causes the program to search for showable pic in the axiv.

    bool load(int); //return true if the file is loaded.
    bool unload(int); //return true if the file is unloaded.
    bool scale(int, QSize, unsigned); //return 0 if scaled got updated, 1 if it's not updated

    std::list<pic *>::iterator ptr(int=0);
    //return an iterator to pic at an offset.
    std::list<pic *>::iterator mv(int=0);
    //return shifted pic_it.

    std::list<pic *>::iterator begin();
    std::list<pic *>::iterator end();

    QString name;

    std::list<pic *> axiv;

private:

    bool isChecked;
    bool isShowable;

    std::list<pic *>::iterator offset_it(int=0);
    std::list<pic *>::iterator pic_it;

};

#endif // PICAXIV_H
