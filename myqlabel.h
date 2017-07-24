#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPainter>
#include <QColor>

class MyQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyQLabel(QWidget *parent = 0);

protected:
      void paintEvent(QPaintEvent *event);
public:
        void isHorizontal(bool isHorizontal);
private:
        bool horizontal;
};

#endif // MYLABEL_H
