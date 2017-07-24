#include "scalepreview.h"
#include "ui_scalepreview.h"

scalePreview::scalePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scalePreview)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    QDesktopWidget *desktop = new QDesktopWidget;
    this->move(desktop->width() - this->width(),desktop->height() - this->height());
    QFont font;
   font.setPointSize(11);
    font.setBold(true);
    ui->valuelabel->setFont(font);
}

scalePreview::~scalePreview()
{
    delete ui;
}
void scalePreview::setPx(QString px){
    ui->valuelabel->setText(px);
}
void scalePreview::setPixmap(QPixmap pixmap){
      this->pixmap = pixmap;

}
void scalePreview::setPoint(QPoint point){

    // 256 200 30
  ui->preLabel->setPixmap(pixmap.copy(point.x()-25,point.y()-21.33,50,42.7).scaled(ui->preLabel->width(),ui->preLabel->height()));
}
void scalePreview::isHorizontal(bool isHorizontal){
    this->horizontal = isHorizontal;
    ui->preLabel->isHorizontal(isHorizontal);
}
