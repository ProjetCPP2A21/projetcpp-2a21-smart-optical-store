#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QSslSocket>

class Smtp : public QObject
{
    Q_OBJECT
public:
    explicit Smtp(QString user, QString pass, QString host, int port, QObject *parent = nullptr);
    ~Smtp();

    void sendMail(const QString &from, const QString &to,
                  const QString &subject, const QString &body);

signals:
    void envoiTermine();
    void errorReceived(QAbstractSocket::SocketError);

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError err);

private:
    QSslSocket *m_socket = nullptr;
    QString m_user, m_pass, m_host, m_from, m_to, m_message;
    int m_port;
    bool m_sentMailFrom = false;
    bool m_sentRcptTo = false;
    bool m_sentData = false;
};

#endif // SMTP_H
