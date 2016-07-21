#include "pic.h"
#include <QPixmap>
#include <QFileInfo>

pic::pic(QString fn) {

    name=fn;
    score=0;

    isChecked=false;
    isShowable=false;
    isLoaded=false;

    original=new QPixmap();
    scaled=new QPixmap();

}

pic::~pic() {

    delete scaled;
    delete original;

}

bool pic::showable() {

    if (!isChecked) {load();}
    return isShowable;

}

bool pic::load() {

    if (isLoaded) {return true;}
    if (isChecked) {
        if (!isShowable) {return false;}
    }

    isChecked=true;
    isShowable=false;
    QFileInfo fn(name);
    if (fn.exists()&&fn.isFile()) {
        delete original;
        original=new QPixmap(name);
        if (!original->isNull()) {
            isShowable=true;
            isLoaded=true;
            return true;
        }
    }
    return false;

}

bool pic::unload() {

    if (isLoaded) {
        if (!original->isNull()) {
            delete original;
            original=new QPixmap();
        }
        if (!scaled->isNull()) {
            delete scaled;
            scaled=new QPixmap();
        }
        isLoaded=false;
    }
    return true;

}

double pic::score_add(double n) {

    return score_set(score+n);

}

double pic::score_set(double n) {

    score=n;
    if (score<=0) {
        score=0;
        unload();
    } else {if (score>=1) {load();}}
    return score;

}

bool pic::deleteme() {

    if (isLoaded) {unload();}
    QFileInfo fn(name);
    if (fn.exists()&&fn.isFile()) {
        if (QFile::remove(name)) {
            isShowable=false;
            return true;
        } else {return false;}
    } else {return false;}

}

bool pic::scale(QSize size, unsigned picRescaleMode) {

    if (!showable()) {return false;}
    if (!isLoaded) {load();}
    switch (picRescaleMode) {
    case 0: {
        if (double(size.height())/double(size.width())>=double(original->height())/double(original->width())) {
            if(size.width()==scaled->width()) {break;}
        } else {
            if(size.height()==scaled->height()) {break;}
        }
        * scaled = original->scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return true;
    }
    case 1: {
        if (scaled->size()!=original->size()) {
            * scaled = * original;
            return true;
        }
    }
    case 2: {
        if (scaled->size()!=size) {
            * scaled = original->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            return true;
        }
    }
    case 3: {
        if (scaled->size().height()!=size.height()) {
            * scaled = original->scaled(2*size.width(), size.height(), Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            return true;
        }
    }
    case 4: {
        if (scaled->size().width()!=size.width()) {
            * scaled = original->scaled(size.width(), 2*size.height(), Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
            return true;
        }
    }
    }
    return false;
}
