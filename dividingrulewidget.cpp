#include "dividingrulewidget.h"
#include "ui_dividingrulewidget.h"

DividingRuleWidget::DividingRuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DividingRuleWidget)
{
    ui->setupUi(this);

    QDesktopWidget *desktop = new QDesktopWidget;
    //设置居中
    this->move(desktop->width() / 2 - this->width() / 2,desktop->height() /2 - this->height() / 2);
    //获取保存的值
    setting = new QSettings("config.ini",QSettings::IniFormat);
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    red = setting->value("red").toInt();
    green = setting->value("green").toInt();
    blue = setting->value("blue").toInt();
    alpha = setting->value("alpha").toFloat();
    isShowScale = setting->value("isShowScale").toBool();
    isTop = setting->value("isTop").toBool();
    unit = setting->value("unit").toString();
    setting->endGroup();
    //是否置顶
    if(isTop){
        this->setWindowFlags(Qt::FramelessWindowHint  |Qt::WindowStaysOnTopHint| Qt::X11BypassWindowManagerHint);
    }else{
        this->setWindowFlags(Qt::FramelessWindowHint  | Qt::X11BypassWindowManagerHint);
    }
    //设置鼠标 追踪
    this->setMouseTracking(true);
    //是否水平
    isHorizontal  = true;
    //是否按压
    isPressed = false;
    //记录窗口默认位置
    this->windowX = this->x();
    this->windowY = this->y();
    this->windowW = this->width();
    this->windowH = this->height();
    //设置肢体
    font.setPointSize(11);
    font.setBold(true);
    ui->label->setFont(font);
    font.setPointSize(10);
    font.setBold(false);
    //下刻度光标
    downCursor = QCursor(QPixmap(":/down"),2,-30);
    //上刻度光标
    upCursor = QCursor(QPixmap(":/up"),2,-30);
    //左刻度光标
    leftCursor = QCursor(QPixmap(":/left"),-30,2);
    //右刻度光标
    rightCursor = QCursor(QPixmap(":/right"),-30,2);
    //设置QPushButton样式
    ui->directionButton->setStyleSheet("QPushButton::hover {border:1px solid #999999;border-radius:2px;}");
    ui->directionButton->setCursor(Qt::ArrowCursor);
    ui->menuButton->setStyleSheet("QPushButton::hover {border:1px solid #999999;border-radius:2px;}");
    ui->menuButton->setCursor(Qt::ArrowCursor);
    ui->minButton->setStyleSheet("QPushButton::hover {border:1px solid #999999;border-radius:2px;}");
    ui->minButton->setCursor(Qt::ArrowCursor);
    ui->closeButton->setStyleSheet("QPushButton::hover {border:1px solid #999999;border-radius:2px;}");
    ui->closeButton->setCursor(Qt::ArrowCursor);


    //初始化菜单
    this->initMenu();

    this->conn();
    //设置背景色
    this->setStyleSheet(QString("background-color:rgb("+QString::number(red)+","+QString::number(green)+","+QString::number(blue)+")"));

    //设置透明度
    this->initAlpha();

    logicalDpi = QPaintDevice::logicalDpiX();

}

DividingRuleWidget::~DividingRuleWidget()
{
    delete ui;
}
void DividingRuleWidget::initMenu(){
    menu = new QMenu(this);
    menu->setStyleSheet("QMenu{background-color:#ffffff} QMenu::item:selected{background-color:rgba(0,0,0,56);color:black;}");
    this->horizontal = new QAction("水平",this);
    this->horizontal->setIcon(QIcon(":check"));

    this->vertical = new QAction("垂直",this);
    this->vertical->setIcon(QIcon(":check"));

    this->vertical->setIconVisibleInMenu(false);
    this->reset = new QAction("重置位置",this);

    this->pxAction = new QAction("像素",this);
    this->pxAction->setIcon(QIcon(":check"));
    this->pxAction->setIconVisibleInMenu(unit=="px"?true:false);

    this->cmAction = new QAction("厘米",this);
    this->cmAction->setIcon(QIcon(":check"));
    this->cmAction->setIconVisibleInMenu(unit=="cm"?true:false);

    this->inAction = new QAction("英寸",this);
    this->inAction->setIcon(QIcon(":check"));
    this->inAction->setIconVisibleInMenu(unit=="in"?true:false);

    this->adjustAction = new QAction("校准标尺(像素/英寸)",this);


    this->topAction = new QAction("窗口置顶",this);
    this->topAction->setIcon(QIcon(":check"));
    this->topAction->setIconVisibleInMenu(isTop);

    this->color = new QAction("颜色",this);

    this->subMenu = new QMenu("不透明度",this);
    this->subMenu->setStyleSheet("QMenu{background-color:#ffffff} QMenu::item:selected{background-color:rgba(0,0,0,56);color:black;}");
    this->alpha100 = new QAction("100%",this);
    this->alpha100->setIcon(QIcon(":check"));
    this->alpha100->setIconVisibleInMenu(false);

    this->alpha95 = new QAction("95%",this);
    this->alpha95->setIcon(QIcon(":check"));
    this->alpha95->setIconVisibleInMenu(false);

    this->alpha90 = new QAction("90%",this);
    this->alpha90->setIcon(QIcon(":check"));
    this->alpha90->setIconVisibleInMenu(false);

    this->alpha85 = new QAction("85%",this);
    this->alpha85->setIcon(QIcon(":check"));
    this->alpha85->setIconVisibleInMenu(false);

    this->alpha80 = new QAction("80%",this);
    this->alpha80->setIcon(QIcon(":check"));
    this->alpha80->setIconVisibleInMenu(false);

    this->alpha75 = new QAction("75%",this);
    this->alpha75->setIcon(QIcon(":check"));
    this->alpha75->setIconVisibleInMenu(false);

    this->alpha70 = new QAction("70%",this);
    this->alpha70->setIcon(QIcon(":check"));
    this->alpha70->setIconVisibleInMenu(false);

    this->alpha65 = new QAction("65%",this);
    this->alpha65->setIcon(QIcon(":check"));
    this->alpha65->setIconVisibleInMenu(false);

    this->alpha60 = new QAction("60%",this);
    this->alpha60->setIcon(QIcon(":check"));
    this->alpha60->setIconVisibleInMenu(false);

    this->alpha55 = new QAction("55%",this);
    this->alpha55->setIcon(QIcon(":check"));
    this->alpha55->setIconVisibleInMenu(false);

    this->alpha50 = new QAction("50%",this);
    this->alpha50->setIcon(QIcon(":check"));
    this->alpha50->setIconVisibleInMenu(false);

    this->alpha45 = new QAction("45%",this);
    this->alpha45->setIcon(QIcon(":check"));
    this->alpha45->setIconVisibleInMenu(false);

    this->alpha40 = new QAction("40%",this);
    this->alpha40->setIcon(QIcon(":check"));
    this->alpha40->setIconVisibleInMenu(false);

    this->showSale = new QAction("显示放大镜窗口",this);
    this->showSale->setIcon(QIcon(":check"));
    if(!isShowScale)
        this->showSale->setIconVisibleInMenu(false);
    this->minAction = new QAction("最小化",this);
    this->closeAction = new QAction("关闭",this);

    menu->addAction(this->horizontal);
    menu->addAction(this->vertical);
    menu->addAction(this->reset);
    menu->addSeparator();
    menu->addAction(this->pxAction);
    menu->addAction(this->cmAction);
    menu->addAction(this->inAction);
    menu->addAction(this->adjustAction);

    menu->addSeparator();
    menu->addAction(this->topAction);

    menu->addAction(this->color);
    subMenu->addAction(this->alpha100);
    subMenu->addAction(this->alpha95);
    subMenu->addAction(this->alpha90);
    subMenu->addAction(this->alpha85);
    subMenu->addAction(this->alpha80);
    subMenu->addAction(this->alpha75);
    subMenu->addAction(this->alpha70);
    subMenu->addAction(this->alpha65);
    subMenu->addAction(this->alpha60);
    subMenu->addAction(this->alpha55);
    subMenu->addAction(this->alpha50);
    subMenu->addAction(this->alpha45);
    subMenu->addAction(this->alpha40);
    menu->addMenu(subMenu);
    menu->addAction(this->showSale);
    menu->addSeparator();
    menu->addAction(this->minAction);
    menu->addAction(this->closeAction);
}
void DividingRuleWidget::conn(){
    connect(this->horizontal,SIGNAL(triggered(bool)),this,SLOT(on_directionButton_clicked()));
    connect(this->vertical,SIGNAL(triggered(bool)),this,SLOT(on_directionButton_clicked()));
    connect(this->reset,SIGNAL(triggered(bool)),this,SLOT(resetSlot()));
    connect(this->topAction,SIGNAL(triggered(bool)),this,SLOT(topSlot()));

    connect(this->pxAction,SIGNAL(triggered(bool)),this,SLOT(pxSlot()));
    connect(this->cmAction,SIGNAL(triggered(bool)),this,SLOT(cmSlot()));
    connect(this->inAction,SIGNAL(triggered(bool)),this,SLOT(inSlot()));
    connect(this->adjustAction,SIGNAL(triggered(bool)),this,SLOT(adjustSlot()));

    connect(this->color,SIGNAL(triggered(bool)),this,SLOT(colorSlot()));
    connect(this->minAction,SIGNAL(triggered(bool)),this,SLOT(on_minButton_clicked()));
    connect(this->closeAction,SIGNAL(triggered(bool)),this,SLOT(on_closeButton_clicked()));
    connect(this->showSale,SIGNAL(triggered(bool)),this,SLOT(showScaleSlot()));

    connect(this->alpha100,SIGNAL(triggered(bool)),this,SLOT(alpha100Slot()));
    connect(this->alpha95,SIGNAL(triggered(bool)),this,SLOT(alpha95Slot()));
    connect(this->alpha90,SIGNAL(triggered(bool)),this,SLOT(alpha90Slot()));
    connect(this->alpha85,SIGNAL(triggered(bool)),this,SLOT(alpha85Slot()));
    connect(this->alpha80,SIGNAL(triggered(bool)),this,SLOT(alpha80Slot()));
    connect(this->alpha75,SIGNAL(triggered(bool)),this,SLOT(alpha75Slot()));
    connect(this->alpha70,SIGNAL(triggered(bool)),this,SLOT(alpha70Slot()));
    connect(this->alpha65,SIGNAL(triggered(bool)),this,SLOT(alpha65Slot()));
    connect(this->alpha60,SIGNAL(triggered(bool)),this,SLOT(alpha60Slot()));
    connect(this->alpha55,SIGNAL(triggered(bool)),this,SLOT(alpha55Slot()));
    connect(this->alpha50,SIGNAL(triggered(bool)),this,SLOT(alpha50Slot()));
    connect(this->alpha45,SIGNAL(triggered(bool)),this,SLOT(alpha45Slot()));
    connect(this->alpha40,SIGNAL(triggered(bool)),this,SLOT(alpha40Slot()));
}
//初始化透明度
void DividingRuleWidget::initAlpha(){
    if(this->alpha ==0.95f)
        this->alpha95Slot();
    else  if(this->alpha ==0.9f)
        this->alpha90Slot();
    else  if(this->alpha ==0.85f)
        this->alpha85Slot();
    else  if(this->alpha == 0.8f)
        this->alpha80Slot();
    else  if(this->alpha ==0.75f)
        this->alpha75Slot();
    else  if(this->alpha ==0.7f)
        this->alpha70Slot();
    else  if(this->alpha ==0.65f)
        this->alpha65Slot();
    else  if(this->alpha ==0.6f)
        this->alpha60Slot();
    else  if(this->alpha ==0.55f)
        this->alpha55Slot();
    else  if(this->alpha ==0.50f)
        this->alpha50Slot();
    else  if(this->alpha ==0.45f)
        this->alpha45Slot();
    else  if(this->alpha ==0.4f)
        this->alpha40Slot();
    else
        this->alpha100Slot();
}
void DividingRuleWidget::enterEvent(QEvent *event){
    if(isShowScale){
        //获取截图
        this->pixmap =  QPixmap::grabWindow(QApplication::desktop()->winId());
        this->preview.setPixmap(this->pixmap);
    }
}
void DividingRuleWidget::leaveEvent(QEvent *event){
    if(isShowScale){
        //获取截图
        this->preview.hide();
    }
}
//鼠标按下
void DividingRuleWidget::mousePressEvent(QMouseEvent *event){
    startX = event->x();
    startY = event->y();
    isPressed = true;
}
//鼠标移动
void DividingRuleWidget::mouseMoveEvent(QMouseEvent *event){
    if(isShowScale){
        this->preview.setPoint(QCursor::pos());
    }
    moveX = event->x() - startX;
    moveY = event->y() - startY;

    //判断位置 水平方向
    if((event->y() < 15 || event->y() > this->height() - 15)&& !isPressed &&  isHorizontal){
        if(event->y() < 15)
            setCursor(upCursor);
        else
            setCursor(downCursor);
        if(this->unit =="px"){
            ui->label->setText("W = "+QString::number(event->x() > 0 ? event->x() : -event->x())+" px");
            if(isShowScale){
                this->preview.setPx("W = "+QString::number(event->x() > 0 ? event->x() : -event->x())+" px");
                this->preview.show();
            }
        }else if(this->unit =="cm"){
            tempValue = event->x() > 0 ? event->x() : -event->x();
            ui->label->setText("W = "+ QString::number(tempValue / 96 * 2.54,'f',1)+" cm");
            if(isShowScale){
                this->preview.setPx("W = "+QString::number(tempValue / 96 * 2.54,'f',1)+" cm");
                this->preview.show();
            }
        }else{
            tempValue = event->x() > 0 ? event->x() : -event->x();
            tempValue +=1;
            tempValue = tempValue * 1.0 / this->logicalDpi;
            ui->label->setText("W = "+QString::number(tempValue, 'f', 2)+" in");
            if(isShowScale){
                this->preview.setPx("W = "+QString::number(tempValue, 'f', 2)+" in");
                this->preview.show();
            }
        }

    }else if((event->x() < 15 || event->x() > this->width() - 15)&&!isPressed && !isHorizontal){
        //竖直方向
        if(event->x() < 15)
            setCursor(leftCursor);
        else
            setCursor(rightCursor);
        if(this->unit =="px"){
            ui->label->setText(QString::number(event->y() > 0 ? event->y() : -event->y())+" px");
            if(isShowScale){
                this->preview.setPx("H = "+QString::number(event->y() > 0 ? event->y() : -event->y())+" px");
                this->preview.show();
            }
        }else if(this->unit =="cm"){
            tempValue = event->y() > 0 ? event->y() : -event->y();
            ui->label->setText(QString::number(tempValue / 96 * 2.54,'f',1)+" cm");
            if(isShowScale){
                this->preview.setPx(QString::number(tempValue / 96 * 2.54,'f',1)+" cm");
                this->preview.show();
            }
        }else{
            tempValue = event->y() > 0 ? event->y() : -event->y();
            tempValue +=1;
            tempValue = tempValue * 1.0 / this->logicalDpi;
            ui->label->setText(QString::number(tempValue, 'f', 2)+" in");
            if(isShowScale){
                this->preview.setPx(QString::number(tempValue, 'f', 2)+" in");
                this->preview.show();
            }
        }

    }else{
        setCursor(Qt::ClosedHandCursor);//设置光标为手型
        if(isShowScale){//如果显示放大镜 则关闭
            this->preview.hide();
        }
        if(isPressed){//按住移动窗口
            this->move(this->x()+moveX,this->y()+moveY);
        }
    }
}

//鼠标释放
void DividingRuleWidget::mouseReleaseEvent(QMouseEvent *event){
    startX = 0;
    startY = 0;
    if(isShowScale){
        //获取截图
        this->pixmap =  QPixmap::grabWindow(QApplication::desktop()->winId());
        this->preview.setPixmap(this->pixmap);
    }
    this->moveX = 0;
    this->moveY = 0;
    isPressed = false;
}
//绘制刻度
void DividingRuleWidget::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setFont(font);
    painter.drawRect(QRect(0,0,this->width()-1,this->height()-1));
    if(isHorizontal){//水平
        if(this->unit =="px"){
            //绘制小刻度
            for(int i = 0;i < this->width() / 2 ;i++){
                if(i < this->width() / 50){   //绘制中刻度
                    big = i * 50;
                    painter.drawLine(big,0,big,12);
                    painter.drawLine(big,this->height() - 12,big,this->height());

                    QFontMetrics fm = painter.fontMetrics();

                    bigMore = (i+1)*50;
                    painter.drawText(QRectF(bigMore -  fm.width(QString::number(big)) / 2,15,
                                            fm.width(QString::number(bigMore)),12),QString::number(bigMore));

                    painter.drawText(QRectF(bigMore-  fm.width(QString::number(big)) / 2,this->height() - 15 -fm.height() ,
                                            fm.width(QString::number(bigMore)),12),QString::number(bigMore));
                }
                if(i < this->width()<10){  //绘制中刻度
                    middle = i*10;
                    painter.drawLine(middle,0,middle,8);
                    painter.drawLine(middle,this->height() - 8,middle,this->height());
                }
                min = i*2;
                painter.drawLine(min,0,min,5);//绘制小刻度
                painter.drawLine(min,this->height() - 5,min,this->height());
            }
        }else if(this->unit == "cm"){
            //将宽度换算为cm
            float cm = QString::number(this->width()*1.0 / 96 * 2.54,'f',1).toFloat();
            float px = 0.1  / 2.54 * this->logicalDpi;
            float temp = 0.1;
            QFontMetrics fm = painter.fontMetrics();
            while(temp <= cm){
                temp =   QString::number(temp,'f',1).toFloat();
                if((int)temp == temp){

                    painter.drawLine(temp*10 *px,0,temp*10 * px,15);//绘制大刻度
                    painter.drawLine(temp*10 *px,this->height(),temp*10 * px,this->height() - 15);//绘制大刻度

                    painter.drawText(QRectF(temp*10 *px -  fm.width(QString::number(temp)) / 2,16,
                                            fm.width(QString::number(temp)),12), QString::number(temp));
                    painter.drawText(QRectF(temp*10 *px -  fm.width(QString::number(temp)) / 2,this->height() - 16-fm.height(),
                                            fm.width(QString::number(temp)),12), QString::number(temp));
                }else{
                    painter.drawLine(temp*10 *px,0,temp*10 * px,5);//绘制小刻度
                    painter.drawLine(temp*10 *px,this->height(),temp*10 * px,this->height() - 5);//绘制小刻度
                }

                temp += 0.1;
            }

        }else{
            //将宽度换算为英寸
            float in = this->width()*1.0 / 96;
            float temp = 0.12;
            bool odd = true;

            //最想刻度偶数 0.12 奇数 0.13
            QFontMetrics fm = painter.fontMetrics();
            while(temp <= in){

                //绘线
                if(QString::number(temp).indexOf("99") != -1){
                    painter.drawLine(temp * this->logicalDpi,0,temp * this->logicalDpi,16);
                    painter.drawLine(temp * this->logicalDpi,this->height(),temp * this->logicalDpi,this->height() - 16);
                    //绘制文本
                    value = QString::number(temp, 'f', 1);
                    painter.drawText(QRectF(temp * this->logicalDpi -  fm.width(value) / 2,16,
                                            fm.width(value),12), value);

                    painter.drawText(QRectF(temp * this->logicalDpi -  fm.width(value) / 2,this->height() - 16-fm.height(),
                                            fm.width(value),12), value);
                }else if(QString::number(temp).indexOf("49") != -1){
                    painter.drawLine(temp * this->logicalDpi,0  ,temp * this->logicalDpi, 9);
                    painter.drawLine(temp * this->logicalDpi,this->height()  ,temp * this->logicalDpi,this->height() - 9);
                    //绘制文本
                    value = QString::number(temp, 'f', 1);
                    painter.drawText(QRectF(temp * this->logicalDpi -  fm.width(value) / 2,16,
                                            fm.width(value),12), value);
                    painter.drawText(QRectF(temp * this->logicalDpi -  fm.width(value) / 2,this->height() - 16-fm.height(),
                                            fm.width(value),12), value);
                }else{
                    painter.drawLine(temp * this->logicalDpi,0  ,temp * this->logicalDpi,5);
                    painter.drawLine(temp * this->logicalDpi,this->height()  ,temp * this->logicalDpi,this->height() - 5);

                }

                if(odd){

                    temp += 0.12;
                }else{

                    temp += 0.13;
                }
                odd = !odd;
            }
        }

        //绘制三竖
        painter.drawLine(5,this->height() / 2 - 4,5,this->height() / 2 + 4);
        painter.drawLine(8,this->height() / 2 - 5,8,this->height() / 2 + 5);
        painter.drawLine(11,this->height() / 2 - 6,11,this->height() / 2 + 6);

        painter.drawLine(this->width() - 5,this->height() / 2 - 4,this->width() -5,this->height() / 2 + 4);
        painter.drawLine(this->width() -8,this->height() / 2 - 5,this->width() -8,this->height() / 2 + 5);
        painter.drawLine(this->width() -11,this->height() / 2 - 6,this->width() -11,this->height() / 2 + 6);
    }else{//竖直
        if(this->unit=="px"){
            //绘制小刻度
            for(int i = 0;i < this->height() / 2 ;i++){
                if(i < this->height() / 50){   //绘制中刻度
                    big = i * 50;
                    painter.drawLine(0,big,12,big);
                    painter.drawLine(this->width() - 12,big,this->width(),big);

                    QFontMetrics fm = painter.fontMetrics();

                    bigMore = (i+1)*50;
                    painter.drawText(QRectF(15,bigMore -  fm.height() / 2,fm.width(QString::number(bigMore)),12),QString::number(bigMore));

                    painter.drawText(QRectF(this->width() - 15 -fm.width(QString::number(bigMore)) ,bigMore -  fm.height() / 2,fm.width(QString::number(bigMore)),12),QString::number(bigMore));

                }
                if(i < this->height()<10){  //绘制中刻度
                    middle = i*10;
                    painter.drawLine(0,middle,8,middle);
                    painter.drawLine(this->width() - 8,middle,this->width(),middle);
                }
                min = i*2;
                painter.drawLine(0,min,5,min);//绘制小刻度
                painter.drawLine(this->width() - 5,min,this->width(),min);
            }
        }else if(this->unit == "cm"){
            //将宽度换算为cm
            float cm = QString::number(this->height()*1.0 / 96 * 2.54,'f',1).toFloat();
            float px = 0.1  / 2.54 * this->logicalDpi;
            float temp = 0.1;
            QFontMetrics fm = painter.fontMetrics();
            while(temp <= cm){
                temp =   QString::number(temp,'f',1).toFloat();
                if((int)temp == temp){

                    painter.drawLine(0,temp*10 *px,15,temp*10 * px);//绘制大刻度
                    painter.drawLine(this->width(),temp*10 *px,this->width() - 15,temp*10 * px);//绘制大刻度

                    painter.drawText(QRectF(16,temp*10 *px -  fm.height() / 2,
                                            fm.width(QString::number(temp)),12), QString::number(temp));
                    painter.drawText(QRectF(this->width() - fm.width(QString::number(temp))-16,temp*10 *px -  fm.height() / 2,
                                            fm.width(QString::number(temp)),12), QString::number(temp));
                }else{
                    painter.drawLine(0,temp*10 *px,5,temp*10 * px);//绘制小刻度
                    painter.drawLine(this->width(),temp*10 *px,this->width() - 5,temp*10 * px);//绘制小刻度
                }

                temp += 0.1;
            }
        }else{
            //将宽度换算为英寸
            float in = this->height()*1.0 / 96;
            float temp = 0.12;
            bool odd = true;

            //最想刻度偶数 0.12 奇数 0.13
            QFontMetrics fm = painter.fontMetrics();
            while(temp <= in){

                //绘线
                if(QString::number(temp).indexOf("99") != -1){
                    painter.drawLine(0,temp * this->logicalDpi,16,temp * this->logicalDpi);
                    painter.drawLine(this->height(),temp * this->logicalDpi,this->width() - 16,temp * this->logicalDpi);
                    //绘制文本
                    value = QString::number(temp, 'f', 1);
                    painter.drawText(QRectF(18,temp * this->logicalDpi -  fm.height() / 2,
                                            fm.width(value),12), value);

                    painter.drawText(QRectF(this->width() - 18 - fm.width(value),temp * this->logicalDpi -  fm.height() / 2,
                                            fm.width(value),12), value);
                }else if(QString::number(temp).indexOf("49") != -1){
                    painter.drawLine(0  ,temp * this->logicalDpi, 8,temp * this->logicalDpi);
                    painter.drawLine(this->width()  ,temp * this->logicalDpi,this->width() - 8,temp * this->logicalDpi);
                    //绘制文本
                    value = QString::number(temp, 'f', 1);

                    painter.drawText(QRectF(18,temp * this->logicalDpi -  fm.height() / 2,
                                            fm.width(value),12), value);

                    painter.drawText(QRectF(this->width() - 18 - fm.width(value),temp * this->logicalDpi -  fm.height() / 2,
                                            fm.width(value),12), value);
                }else{
                    painter.drawLine(0  ,temp * this->logicalDpi,5,temp * this->logicalDpi);
                    painter.drawLine(this->width()  ,temp * this->logicalDpi,this->width() - 5,temp * this->logicalDpi);

                }

                if(odd){

                    temp += 0.12;
                }else{

                    temp += 0.13;
                }
                odd = !odd;
            }
        }
        //绘制三竖
        painter.drawLine(this->width() / 2 - 4,5,this->width() / 2 + 4,5);
        painter.drawLine(this->width() / 2 - 5,8,this->width() / 2 + 5,8);
        painter.drawLine(this->width() / 2 - 6,11,this->width() / 2 + 6,11);

        painter.drawLine(this->width() / 2 - 4,this->height()-5,this->width() / 2 + 4,this->height()-5);
        painter.drawLine(this->width() / 2 - 5,this->height()-8,this->width() / 2 + 5,this->height()-8);
        painter.drawLine(this->width() / 2 - 6,this->height()-11,this->width() / 2 + 6,this->height()-11);

    }
    if(isShowScale){
        //获取截图
        this->pixmap =  QPixmap::grabWindow(QApplication::desktop()->winId());
        this->preview.setPixmap(this->pixmap);
    }
}
//键盘按键松开
void DividingRuleWidget::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape://退出
        this->close();
        break;
    case Qt::Key_Left://光标移动精确定位颜色
        QCursor::setPos(QPoint(QCursor::pos().x()-1,QCursor::pos().y()));
        break;
    case Qt::Key_Up:
        QCursor::setPos(QPoint(QCursor::pos().x(),QCursor::pos().y()-1));
        break;
    case Qt::Key_Right:
        QCursor::setPos(QPoint(QCursor::pos().x()+1,QCursor::pos().y()));
        break;
    case Qt::Key_Down:
        QCursor::setPos(QPoint(QCursor::pos().x(),QCursor::pos().y()+1));
        break;

    }
}

//关闭窗口
void DividingRuleWidget::on_closeButton_clicked()
{
    this->close();
}
//改变水平或竖直
void DividingRuleWidget::on_directionButton_clicked()
{
    this->isHorizontal = !this->isHorizontal;
    if(this->isHorizontal){
        this->setGeometry(this->x(),this->y(),this->height(),this->width());
        ui->directionButton->setGeometry(26,37,26,26);
        ui->menuButton->setGeometry(60,37,26,26);
        ui->minButton->setGeometry(90,37,26,26);
        ui->closeButton->setGeometry(120,37,26,26);

        ui->label->setGeometry(170,37,100,20);
    }else{
        this->setGeometry(this->x(),this->y(),this->height(),this->width());
        ui->directionButton->setGeometry(37,26,26,26);
        ui->menuButton->setGeometry(37,60,26,26);
        ui->minButton->setGeometry(37,90,26,26);
        ui->closeButton->setGeometry(37,120,26,26);
        if(this->unit =="px")
            ui->label->setGeometry(20,166,60,20);
        else if(this->unit =="cm")
            ui->label->setGeometry(20,166,60,20);
        else
            ui->label->setGeometry(20,156,60,20);
    }
    this->horizontal->setIconVisibleInMenu(this->isHorizontal);
    this->vertical->setIconVisibleInMenu(!this->isHorizontal);
    this->update();
    this->preview.isHorizontal(this->isHorizontal);
    this->preview.setPoint(QCursor::pos());

}
//最小化
void DividingRuleWidget::on_minButton_clicked()
{

    this->setWindowState(Qt::WindowMinimized);
}
//双击
void DividingRuleWidget::mouseDoubleClickEvent(QMouseEvent *event){
    //非边缘位置双击
    if(event->x() > 15 && event->x()< this->width() - 15 && event->y() > 15 && event->y() < this->height() - 15){
        on_directionButton_clicked();
    }else{
        if(isHorizontal){
            this->move(event->x() + this->x(),this->y());
        }else{
            this->move(this->x(),event->y() + this->y());
        }
    }
}
bool DividingRuleWidget::nativeEvent(const QByteArray &eventType, void *message, long *result){
    MSG* msg = (MSG*)message;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos > 0 && xPos < 8 && (yPos > 15 && yPos < this->height() - 15)){
            if(!isHorizontal)
                return false;
            *result = HTLEFT;
            return true;
        }

        if(xPos > (this->width() - 8) && xPos < (this->width() - 0)&& (yPos > 15 && yPos < this->height() - 15)){
            if(!isHorizontal)
                return false;
            *result = HTRIGHT;
            return true;
        }
        if(yPos > 0 && yPos < 8&& (xPos > 15 && xPos < this->width() - 15)){
            if(isHorizontal)
                return false;
            *result = HTTOP;
            return true;
        }

        if(yPos > (this->height() - 8) && yPos < (this->height() - 0)&& (xPos > 15 && xPos < this->width() - 15)){
            if(isHorizontal)
                return false;
            *result = HTBOTTOM;
            return true;
        }
    }
    return false;

}

//显示菜单
void DividingRuleWidget::on_menuButton_clicked()
{

    menu->exec(QCursor::pos());
}
//重置
void DividingRuleWidget::resetSlot()
{
    this->setGeometry(this->windowX,this->windowY,this->windowW,this->windowH);
}
//像素
void DividingRuleWidget::pxSlot()
{
    this->unit = "px";
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("unit","px");
    setting->endGroup();
    this->pxAction->setIconVisibleInMenu(true);
    this->cmAction->setIconVisibleInMenu(false);
    this->inAction->setIconVisibleInMenu(false);
    ui->label->setText("");
    this->update();
}
//cm
void DividingRuleWidget::cmSlot()
{
    this->unit = "cm";
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("unit","cm");
    setting->endGroup();
    this->pxAction->setIconVisibleInMenu(false);
    this->cmAction->setIconVisibleInMenu(true);
    this->inAction->setIconVisibleInMenu(false);
    ui->label->setText("");
    this->update();
}
//英寸
void DividingRuleWidget::inSlot()
{
    this->unit = "in";
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("unit","in");
    setting->endGroup();
    this->pxAction->setIconVisibleInMenu(false);
    this->cmAction->setIconVisibleInMenu(false);
    this->inAction->setIconVisibleInMenu(true);
    ui->label->setText("");
    this->update();
}
//校准
void DividingRuleWidget::adjustSlot()
{

    bool ok;
    double d = QInputDialog::getDouble(this, tr("校准标尺"),
                                       tr("屏幕每英寸像素值(默认值："), this->logicalDpi, 0, 10000, 1, &ok);
    if (ok)
    {
        if(this->logicalDpi != (float)d){
            this->logicalDpi = (float)d;
            this->update();
        }
    }
}
//置顶
void DividingRuleWidget::topSlot()
{
    isTop = !isTop;
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("isTop",isTop?"1":"0");
    setting->endGroup();

    if(isTop){
        this->setWindowFlags(Qt::FramelessWindowHint  |Qt::WindowStaysOnTopHint| Qt::X11BypassWindowManagerHint);

    }else{
        this->setWindowFlags(Qt::FramelessWindowHint  | Qt::X11BypassWindowManagerHint);
    }
    //隐藏了就显示出来
    if (!this->isVisible())
    {
        this->setVisible(true);
    }
    topAction->setIconVisibleInMenu(isTop);
}
//设置颜色
void DividingRuleWidget::colorSlot()
{

    //显示对话框
    QColor color = QColorDialog::getColor(QColor(red,green,blue),this,tr("选择颜色"));
    if(color.isValid()){
        red = color.red();
        green = color.green();
        blue = color.blue();
        this->setStyleSheet(QString("background-color:rgb("+QString::number(red)+","+QString::number(green)+","+QString::number(blue)+")"));
        setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
        setting->setValue("red",QString::number(red));
        setting->setValue("green",QString::number(green));
        setting->setValue("blue",QString::number(blue));
        setting->endGroup();
    }
}
//是否显示缩放窗口
void DividingRuleWidget::showScaleSlot(){
    this->isShowScale = !isShowScale;
    this->showSale->setIconVisibleInMenu(this->isShowScale);
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("isShowScale",(isShowScale?"1":"0"));

    setting->endGroup();
}

void DividingRuleWidget::alpha100Slot()
{
    this->setAlpha(this->alpha100,1 );
}

void DividingRuleWidget::alpha95Slot()
{
    this->setAlpha(this->alpha95, 0.95);
}

void DividingRuleWidget::alpha90Slot()
{
    this->setAlpha(this->alpha90, 0.9);
}

void DividingRuleWidget::alpha85Slot()
{
    this->setAlpha(this->alpha85, 0.85);
}

void DividingRuleWidget::alpha80Slot()
{
    this->setAlpha(this->alpha80, 0.8);
}

void DividingRuleWidget::alpha75Slot()
{
    this->setAlpha(this->alpha75, 0.75);
}

void DividingRuleWidget::alpha70Slot()
{
    this->setAlpha(this->alpha70, 0.7);
}

void DividingRuleWidget::alpha65Slot()
{
    this->setAlpha(this->alpha65, 0.65);
}

void DividingRuleWidget::alpha60Slot()
{
    this->setAlpha(this->alpha60, 0.6);
}

void DividingRuleWidget::alpha55Slot()
{
    this->setAlpha(this->alpha55, 0.55);
}

void DividingRuleWidget::alpha50Slot()
{
    this->setAlpha(this->alpha50, 0.5);
}

void DividingRuleWidget::alpha45Slot()
{
    this->setAlpha(this->alpha45, 0.45);

}

void DividingRuleWidget::alpha40Slot()
{
    this->setAlpha(this->alpha40, 0.4);
}
//设置透明度
void DividingRuleWidget::setAlpha(QAction *action,float alpha)
{

    setWindowOpacity(alpha);
    this->alpha = alpha;
    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("alpha", QString::number(alpha));
    setting->endGroup();

    QList<QAction*> actions= subMenu->actions();
    for(int i = 0;i < actions.size();i++){
        actions.at(i)->setIconVisibleInMenu(false);
    }
    action->setIconVisibleInMenu(true);
}


