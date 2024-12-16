#include "chatclient.h"
#include<QDataStream>
#include<QJsonObject>
#include<QJsonDocument>

ChatClient::ChatClient(QObject *parent):QObject(parent)
{
    m_clientSocket=new QTcpSocket(this);

    connect(m_clientSocket,&QTcpSocket::connected,this,&ChatClient::connected);
    connect(m_clientSocket,&QTcpSocket::readyRead,this,&ChatClient::onReadyRead);
}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    //
    for(;;){ // 无限循环，用于持续读取数据
        socketStream.startTransaction(); // 在数据流上开始一个事务
        socketStream >> jsonData; // 从套接字读取 JSON 数据到 QByteArray
        if(socketStream.commitTransaction()){ // 该函数用来确认事务是否成功
            QJsonParseError parseError;
            const QJsonDocument jsonDoc=QJsonDocument::fromJson(jsonData,&parseError);
            if(parseError.error==QJsonParseError::NoError){
                if(jsonDoc.isObject()){
                    emit jsonReceived(jsonDoc.object());
                }
            }
        }


        else{
            break;
        }
    }
}

void ChatClient::sendMessage(const QString &text, const QString &type)
{
    if(m_clientSocket->state()!=QAbstractSocket::ConnectedState)
        return;

    if(!text.isEmpty()){
        //create a
        QDataStream serverStream(m_clientSocket);
        serverStream.setVersion(QDataStream::Qt_5_12);


        //create
        QJsonObject message;
        message["type"] = type;
        message["text"] = text;
        //send
        serverStream << QJsonDocument(message).toJson();
    }
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address,port);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
