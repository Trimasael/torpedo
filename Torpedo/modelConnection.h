#ifndef MODELCHAT_H
#define MODELCHAT_H

#include <QTcpSocket>
#include "basebuildingblocks.h"


class modelConnection : public QObject
{
    Q_OBJECT
public:
    modelConnection();
    void sendMessenge(QString);
    void sendStep(QString);
    void sendShotResponse(QString);
    void connectToHost(QString hostname, quint16 port);
    void setNickName(QString name);
    QString getNickName();
    QTcpSocket* getSocket() const;
    void setSocket(QTcpSocket* S);

signals:
    void msgRecieved(QString msg);
    void dataRecieved(NewGameData data);
    void stepRecieved(Coordinate c);
    void shotResponseRecieved(int shot);

private:
    QTcpSocket *mSocket;
    QString nickName;
};

#endif // MODELCHAT_H
