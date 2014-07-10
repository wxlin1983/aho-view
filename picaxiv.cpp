#include "picaxiv.h"
#include <QDir>
#include <QStringList>

picaxiv::picaxiv(QString fn)
{
    QStringList picfilters;
    picfilters << "*.jpg" << "*.jpeg" << "*.png"<< "*.bmp";
    name=fn;
    status=0;
    QFileInfo info(fn);
    if (info.exists()) {
        if (info.isDir()) {
            QFileInfoList dirlist=QDir(fn).entryInfoList(picfilters,
                                                         QDir::Files|QDir::NoDotAndDotDot|QDir::Readable|QDir::NoSymLinks);
            axiv=std::vector<pic *> (dirlist.size());
            unsigned j=0;
            for (QFileInfoList::iterator i = dirlist.begin(); i != dirlist.end(); ++i) {
                axiv[j]=new pic((*i).absoluteFilePath());
                j++;
            }
            pic_it=axiv.begin();
            return;
        } else if (info.isFile()) {
            axiv=std::vector<pic *> (1);
            axiv[0]=new pic(info.absoluteFilePath());
            pic_it=axiv.begin();
            return;
        } else {}
    }
    name="";
    status=2;
}

picaxiv::~picaxiv() {
    std::vector<pic *>::iterator i;
    for (i = axiv.begin(); i != axiv.end(); ++i) {
        delete (*i);
    }
}

std::vector<pic *>::iterator picaxiv::offset_it(int offset) {
    if (axiv.empty()||(offset==0)) {return pic_it;}
    std::vector<pic *>::iterator tmp=pic_it;
    int k=1;
    if (offset<0) {k=-1;}
    for (int i=0;i<offset*k;i++) {
        if (offset<0&&tmp==axiv.begin()) {tmp=axiv.end();}
        tmp=tmp+k;
        if (offset>0&&tmp==axiv.end()) {tmp=axiv.begin();}
    }
    return tmp;
}

std::vector<pic *>::iterator picaxiv::offset_it_checked(int offset) {
    //should only be used for showable axiv
    if (axiv.empty()||(offset==0)) {return pic_it;}
    std::vector<pic *>::iterator tmp=pic_it;
    int k=1;
    if (offset<0) {k=-1;}
    for (int i=0;i<offset*k;i++) {
        if (offset<0&&tmp==axiv.begin()) {tmp=axiv.end();}
        tmp=tmp+k;
        if (offset>0&&tmp==axiv.end()) {tmp=axiv.begin();}
    }
    while((*tmp)->load()!=1) {
        tmp=axiv.erase(tmp);
        if (axiv.empty()) {return tmp;}
        //this should never happen!
        //always check showable before using mv.
        if (offset<0) {
            if (tmp==axiv.begin()) {tmp=axiv.end();}
            tmp--;
        } else if (offset>0) {
            if (tmp==axiv.end()) {tmp=axiv.begin();}
        }
    }
    return tmp;
}

bool picaxiv::isvalid() {
    if (status==2) {return false;}
    int ind=0;
    for(std::vector<pic*>::iterator i=axiv.begin();i!=axiv.end();i++) {
        if((*i)->load()==1) {
            if (status!=1) {
                status=1;
                pic_it=i;
            }
            return true;
        }
        ind++;
    }
    return false;
}

int picaxiv::load(int offset) {
    return (*offset_it(offset))->load();
}

int picaxiv::scale(int offset, QSize size, unsigned picRescaleMode) {
    return (*offset_it(offset))->scale(size, picRescaleMode);
}

std::vector<pic *>::iterator picaxiv::ptr(int m) {
    if (axiv.empty()) {return pic_it;}
    return offset_it(m);
}

std::vector<pic *>::iterator picaxiv::mv(int m) {
    //always check showable before using mv.
    if (axiv.empty()||(m==0)) {return pic_it;}
    pic_it=offset_it_checked(m);
    return pic_it;
}
