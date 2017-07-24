#include "myqlabel.h"
MyQLabel::MyQLabel(QWidget *parent):QLabel(parent)
{
    horizontal = true;
}
void MyQLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
    QColor color(221,80,68);
    QPen pen(color);
    pen.setWidth(5);
    QPainter painter(this) ;
    painter.setPen(pen);
   if(this->horizontal){//画竖直线
       painter.drawLine(this->width() / 2+3,0,this->width() / 2+3 ,this->height());
   }else{
         painter.drawLine(0,this->height() / 2 +7,this->width()  ,this->height() / 2+7);
   }
}
void MyQLabel::isHorizontal(bool isHorizontal){
    this->horizontal = isHorizontal;
}
