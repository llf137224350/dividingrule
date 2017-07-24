#ifndef SCALEPREVIEW_H
#define SCALEPREVIEW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPixmap>
#include "myqlabel.h"

namespace Ui {
class scalePreview;
}

class scalePreview : public QWidget
{
    Q_OBJECT

public:
    explicit scalePreview(QWidget *parent = 0);
    ~scalePreview();
public:
    void setPx(QString px);
    void setPixmap(QPixmap pixmap);
    void setPoint(QPoint pixmap);
    void isHorizontal(bool isHorizontal);
private:
    Ui::scalePreview *ui;
    QPixmap pixmap;
    bool horizontal;

};

#endif // SCALEPREVIEW_H
