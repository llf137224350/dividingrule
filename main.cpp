#include "dividingrulewidget.h"
#include <QApplication>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load(QString(":/qt_zh_CN"))){
        a.installTranslator(&translator);
    }
    QSettings setting("config.ini",QSettings::IniFormat);//生成配置文件
    setting.beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    if(setting.value("red").isNull())
        setting.setValue("red",QVariant("255"));
    if(setting.value("green").isNull())
        setting.setValue("green",QVariant("255"));
    if(setting.value("blue").isNull())
        setting.setValue("blue",QVariant("255"));
    if(setting.value("alpha").isNull())
        setting.setValue("alpha",QVariant("0.85"));
    if(setting.value("isShowScale").isNull())
        setting.setValue("isShowScale",QVariant("1"));
    if(setting.value("isTop").isNull())
        setting.setValue("isTop",QVariant("1"));
    if(setting.value("unit").isNull())
        setting.setValue("unit",QVariant("px"));
    setting.endGroup();
    DividingRuleWidget w;
    w.show();

    return a.exec();
}
