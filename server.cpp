#include "server.h"

Server::Server(QWidget *parent):
    QDialog(parent)
{
    setFixedSize(400, 200);
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
    server->listen(QHostAddress::AnyIPv4, PORT);
}



void Server::newConnection()
{
    QTcpSocket* nextSocket = server->nextPendingConnection();
    QString ip = nextSocket->peerAddress().toString();
    QString port = QString::number(nextSocket->peerPort());
    cilentList.append(ip + ":" + port);
    emit cilentInfo(cilentList);
    sockets.push_back(nextSocket); //添加连接socket到容器
    sendList(cilentList); //发送在线列表
    connect(nextSocket, &QTcpSocket::readyRead, this, &Server::readMsg); //接受消息信号
    connect(nextSocket, &QTcpSocket::disconnected, this, &Server::onDisconnect); //断开连接信号
}

void Server::readMsg(){
    QTcpSocket* socket = (QTcpSocket*)sender();

    QByteArray msg = socket->readAll();
    QByteArray user;

    user.append(socket->peerAddress().toString());
    user.append(QString::number(socket->peerPort()));

    qDebug() << QString(msg);
    sendMsg(user, msg);
}


void Server::sendList(QStringList list) //标识1
{
    QByteArray listMsg;
    //listMsg.append(qint8(0));
    QDataStream stream(&listMsg, QIODevice::WriteOnly);
    stream << qint8(1);
    stream << list;
    for(int i = 0; i < sockets.size(); i++){

       sockets[i]->write(listMsg);
       //sockets[i]->waitForBytesWritten();
    }
}

void Server::sendMsg(const QByteArray& user, const QByteArray& msg){ //标识0
    QString userMsgStr(user + msg);
    QByteArray userMsg;
    QDataStream dataStream(&userMsg, QIODevice::WriteOnly);
    dataStream << qint8(0);
    dataStream << userMsgStr;
    for(int i = 0; i < sockets.size(); i++){       
        //qDebug() << QString(userMsg);
        sockets[i]->write(userMsg);
    }

}


void Server::onDisconnect()
{
    QTcpSocket* socket = (QTcpSocket*)sender();

    for(int i = 0; i < sockets.size(); i++){
        if(sockets[i] == socket)
        {
            sockets.remove(i);        
            break;
        }
    }

    QString ip = socket->peerAddress().toString();
    QString port = QString::number(socket->peerPort());
    cilentList.removeOne(ip + ":" + port);
    sendList(cilentList);
    emit delCilentInfo(cilentList);
    socket->close();
    //delete socket;
}
