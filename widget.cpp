#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new Server(this);
    connect(server, &Server::cilentInfo, this, &Widget::addCilentInfo);
    connect(server, &Server::delCilentInfo, this, &Widget::delCilentInfo);

}

Widget::~Widget()
{
    delete server;
    delete ui;
}

void Widget::addCilentInfo(QStringList cilentList)
{

    ui->listView->setModel(new QStringListModel(cilentList));
}

void Widget::delCilentInfo(QStringList cilentList)
{
    //ui->listView->clearMask();

   ui->listView->setModel(new QStringListModel(cilentList));


}

