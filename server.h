#ifndef SERVER_H
#define SERVER_H
#define PORT 8000

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QIODevice>

class Server : public QDialog
{
    Q_OBJECT
public:
    Server(QWidget *parent = nullptr);

private slots:
    void newConnection();
    void readMsg();
    void onDisconnect();

signals:
    void cilentInfo(QStringList cilentList);
    void delCilentInfo(QStringList cilentList);

private:
    QTcpServer *server;
    QVector<QTcpSocket*> sockets;
    QStringList cilentList;
    void sendMsg(const QByteArray& user, const QByteArray& bt);
    void sendList(QStringList list);
//  QTcpSocket *socket;
};

#endif // SERVER_H
