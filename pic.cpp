#include "pic.h"
#include <QPixmap>
#include <QFileInfo>

pic::pic(QString fn) {
    name=fn;
    status=0;
}

pic::~pic() {}

int pic::load() {
    //after load(), the status will be either 1 or 2.
    if (status==1) {return 1;}
    if (status==0) {
        status=2;
        QFileInfo fn(name);
        if (fn.exists()&&fn.isFile()) {
            QImage image(name);
            if (!image.isNull()) {
                original=QPixmap::fromImage(image);
                if (!original.isNull()) {
                    status=1;
                }
            }
        }
    }
    return status;
}

int pic::scale(QSize size, unsigned picRescaleMode) {
    //return 0 if scaled got updated, 1 if it's not updated
    if (status==0) {load();}
    if (status==1) {
        switch (picRescaleMode) {
        case 0: {
            if (double(size.height())/double(size.width())>=double(original.height())/double(original.width())) {
                if(size.width()==scaled.width()) {break;}
            } else {
                if(size.height()==scaled.height()) {break;}
            }
            scaled = original.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            return 0;
        }
        case 1: {
            if (scaled.size()!=original.size()) {
                scaled = QPixmap(original);
                return 0;
            }
        }
        case 2: {
            if (scaled.size()!=size) {
                scaled = original.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                return 0;;
            }
        }
        case 3: {
            if (scaled.size().height()!=size.height()) {
                scaled = original.scaled(2*size.width(), size.height(), Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
                return 0;;
            }
        }
        case 4: {
            if (scaled.size().width()!=size.width()) {
                scaled = original.scaled(size.width(), 2*size.height(), Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
                return 0;;
            }
        }
        }
    }
    return 1;
}
