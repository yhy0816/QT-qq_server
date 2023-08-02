#ifndef WIDGET_H
#define WIDGET_H

#include "server.h"
#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void addCilentInfo(QStringList cilentList);
    void delCilentInfo(QStringList cilentList);

private:

    Server* server;
    //QStringList cilentList;
    Ui::Widget *ui;
};
#endif // WIDGET_H
