#ifndef DIVIDINGRULEWIDGET_H
#define DIVIDINGRULEWIDGET_H
#include <windows.h>
#include <windowsx.h>
#include <QWidget>
#include <QMouseEvent>
#include <QtDebug>
#include <QPainter>
#include <QFontMetrics>
#include <QPen>
#include <QPushButton>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QSettings>
#include <QList>
#include <QScreen>
#include <QPaintDevice>
#include <QInputDialog>
#include "scalepreview.h"
namespace Ui {
class DividingRuleWidget;
}

class DividingRuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DividingRuleWidget(QWidget *parent = 0);
    ~DividingRuleWidget();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent*);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);//改变窗口大小

private slots:
    void on_closeButton_clicked();

    void on_directionButton_clicked();

    void on_minButton_clicked();

    void on_menuButton_clicked();

    void resetSlot();//重置刻度尺

    void pxSlot();//像素
    void cmSlot();//cm
    void inSlot();//英寸
    void adjustSlot();//校准

    void topSlot();//置顶
    void colorSlot();//颜色
    void showScaleSlot();//显示缩放窗口

    void alpha100Slot();//透明度
    void alpha95Slot() ;
    void alpha90Slot() ;
    void alpha85Slot() ;
    void alpha80Slot() ;
    void alpha75Slot() ;
    void alpha70Slot() ;
    void alpha65Slot() ;
    void alpha60Slot() ;
    void alpha55Slot() ;
    void alpha50Slot() ;
    void alpha45Slot() ;
    void alpha40Slot() ;
private:
    Ui::DividingRuleWidget *ui;
    scalePreview preview;
    int startX,startY,moveX,moveY;
    int big,middle,min,bigMore;//大中小刻度
    int windowX,windowY,windowW,windowH;//默认位置
    int red,green,blue;
    float alpha;
    double tempValue;
    bool isPressed,isShowScale,isTop;//显示缩放窗口
    QString unit;
    QSettings *setting;
    QCursor downCursor ;//下光标
    QCursor upCursor ;//上光标
    QCursor leftCursor ;//左光标
    QCursor rightCursor ;//右光标
    QFont font;
    QPixmap pixmap;
    QMenu *menu;
    QAction *horizontal;//水平
    QAction *vertical;//垂直
    QAction *reset;//重置

    QAction *pxAction;//像素
    QAction *cmAction;//cm
    QAction *inAction;//英寸
    QAction *adjustAction;//校准

    QAction *color;//颜色
    QAction *minAction;//最小化
    QAction *topAction;//窗口置顶
    QAction *closeAction;//关闭
    QMenu *subMenu;//不透明度
    QAction *showSale;//显示放大窗口
    QAction *alpha100;//透明度
    QAction *alpha95;//透明度
    QAction *alpha90;//透明度
    QAction *alpha85;//透明度
    QAction *alpha80;//透明度
    QAction *alpha75;//透明度
    QAction *alpha70;//透明度
    QAction *alpha65;//透明度
    QAction *alpha60;//透明度
    QAction *alpha55;//透明度
    QAction *alpha50;//透明度
    QAction *alpha45;//透明度
    QAction *alpha40;//透明度

    int logicalDpi;//获取dpi
    QString value;//英寸临时值

    bool isHorizontal;//是否水平
    void initMenu();//初始化菜单
    void conn();
    void initAlpha();//初始化透明度
    void setAlpha(QAction *action,float alpha);//改变透明度

};

#endif // DIVIDINGRULEWIDGET_H
