#include "picaxiv.h"
#include <QDir>
#include <QStringList>

picaxiv::picaxiv(QString fn)
{
    QStringList picfilters;
    picfilters << "*.jpg" << "*.jpeg" << "*.png"<< "*.bmp";
    name=fn;
    isChecked=false;
    isShowable=false;
    QFileInfo info(fn);
    if (info.exists()) {
        if (info.isDir()) {
            QFileInfoList dirlist=QDir(fn).entryInfoList(picfilters,
                                                         QDir::Files|QDir::NoDotAndDotDot|QDir::Readable|QDir::NoSymLinks);
            if(dirlist.size()==0) {
                isChecked=true;
                isShowable=false;
                return;
            }
            axiv=std::list<pic *> (dirlist.size());
            std::list<pic *>::iterator j=axiv.begin();
            for (QFileInfoList::iterator i = dirlist.begin(); i != dirlist.end(); i++) {
                *j=new pic((*i).absoluteFilePath());
                j++;
            }
            pic_it=axiv.begin();
            return;
        } else if (info.isFile()) {
            axiv=std::list<pic *> (1);
            *(axiv.begin())=new pic(info.absoluteFilePath());
            pic_it=axiv.begin();
            return;
        } else {}
    }
    isChecked=true;
    isShowable=false;
    axiv=std::list<pic *>();
    pic_it=axiv.begin();

}

picaxiv::~picaxiv() {

    for (std::list<pic *>::iterator i = axiv.begin(); i != axiv.end(); ++i) {delete (*i);}

}

std::list<pic *>::iterator picaxiv::offset_it(int offset) {

    if (axiv.empty()) {return pic_it;}
    std::list<pic *>::iterator tmp=pic_it;
    if (offset<0) {
        for (int i=0;i<-1*offset;i++) {
            if (tmp==axiv.begin()) {tmp=axiv.end();}
            tmp--;
        }
    } else if (offset>0) {
        for (int i=0;i<offset;i++) {
            tmp++;
            if (offset>0&&tmp==axiv.end()) {tmp=axiv.begin();}
        }
    } else {}
    return tmp;

}

bool picaxiv::showable() {

    if (isChecked) {return isShowable;}
    int ind=0;
    for(std::list<pic*>::iterator i=axiv.begin();i!=axiv.end();i++) {
        if((*i)->showable()) {
            isShowable=true;
            isChecked=true;
            pic_it=i;
            return true;
        }
        ind++;
    }
    isShowable=false;
    isChecked=true;
    return isShowable;

}

bool picaxiv::load(int offset) {

    if (axiv.empty()) {return false;}
    return (*offset_it(offset))->load();

}

bool picaxiv::scale(int offset, QSize size, unsigned picRescaleMode) {

    if (axiv.empty()) {return false;}
    return (*offset_it(offset))->scale(size, picRescaleMode);

}

std::list<pic *>::iterator picaxiv::ptr(int m) {

    if (axiv.empty()) {return pic_it;}
    return offset_it(m);

}

std::list<pic *>::iterator picaxiv::mv(int m) {

    if (axiv.empty()) {return pic_it;}
    pic_it=offset_it(m);
    return pic_it;

}

std::list<pic *>::iterator picaxiv::begin() {

    if (axiv.empty()) {return pic_it;}
    pic_it=axiv.begin();
    return pic_it;

}

std::list<pic *>::iterator picaxiv::end() {

    if (axiv.empty()) {return pic_it;}
    pic_it=axiv.end();
    pic_it--;
    return pic_it;

}
