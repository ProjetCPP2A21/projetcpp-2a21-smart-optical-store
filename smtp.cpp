#include "smtp.h"
#include <QDebug>

Smtp::Smtp(QString user, QString pass, QString host, int port, QObject *parent)
    : QObject(parent), m_user(std::move(user)), m_pass(std::move(pass)),
    m_host(std::move(host)), m_port(port)
{
    m_socket = new QSslSocket();
    m_socket->setProtocol(QSsl::TlsV1_2OrLater);

    connect(m_socket, &QSslSocket::connected, this, &Smtp::onConnected);
    connect(m_socket, &QSslSocket::readyRead, this, &Smtp::onReadyRead);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &Smtp::onError);

    connect(m_socket, &QSslSocket::encrypted, this, [this]() {
        qDebug() << "Connexion chiffrée (TLS) établie avec succès";
        m_socket->write("EHLO localhost\r\n");
    });
}

Smtp::~Smtp()
{
    if (m_socket) {
        m_socket->abort();
        delete m_socket;
        m_socket = nullptr;
    }
}

void Smtp::sendMail(const QString &from, const QString &to,
                    const QString &subject, const QString &body)
{
    m_from = from;
    m_to = to;
    m_message = "To: " + to + "\r\n";
    m_message += "From: " + from + "\r\n";
    m_message += "Subject: " + subject + "\r\n\r\n";
    m_message += body + "\r\n.\r\n";

    m_sentMailFrom = false;
    m_sentRcptTo = false;

    m_socket->connectToHost(m_host, m_port);  // Connexion
    if (!m_socket->waitForConnected(15000)) {
        qDebug() << "Impossible de se connecter à" << m_host;
        emit errorReceived(QAbstractSocket::SocketTimeoutError);
    }
}

void Smtp::onConnected()
{
    qDebug() << "Connecté à" << m_host << "→ attente du 220";
}

void Smtp::onReadyRead()
{
    while (m_socket->canReadLine()) {
        QString line = m_socket->readLine();
        qDebug() << "SMTP ←" << line.trimmed();

        //  Réponse initiale 220
        if (line.startsWith("220") && line.contains("smtp.gmail.com ESMTP")) {
            qDebug() << "→ Envoi EHLO initial";
            m_socket->write("EHLO localhost\r\n");
        }
        //  Dernière ligne EHLO (250 avec espace, pas de tiret)
        else if (line.startsWith("250 ") && !m_socket->isEncrypted()) {
            qDebug() << "→ Envoi STARTTLS";
            m_socket->write("STARTTLS\r\n");
        }
        //  Gmail répond 220 Ready for TLS
        else if (line.startsWith("220") && !line.contains("ESMTP")) {
            qDebug() << "→ Démarrage encryption TLS";
            m_socket->startClientEncryption();
            // Le signal encrypted() enverra EHLO automatiquement
        }
        //  Après encryption, dernière ligne du nouveau EHLO
        else if (line.startsWith("250 ") && m_socket->isEncrypted() && !m_sentMailFrom) {
            qDebug() << "→ Envoi AUTH LOGIN";
            m_socket->write("AUTH LOGIN\r\n");
        }
        //  Demande username
        else if (line.startsWith("334 VXNlcm5hbWU6")) {
            qDebug() << "→ Envoi username";
            m_socket->write(m_user.toUtf8().toBase64() + "\r\n");
        }
        //  Demande password
        else if (line.startsWith("334 UGFzc3dvcmQ6")) {
            qDebug() << "→ Envoi password";
            m_socket->write(m_pass.toUtf8().toBase64() + "\r\n");
        }
        //  Auth réussie (235)
        else if (line.startsWith("235")) {
            qDebug() << "→ Auth OK, envoi MAIL FROM";
            m_socket->write("MAIL FROM:<" + m_from.toUtf8() + ">\r\n");
            m_sentMailFrom = true;  // ← MARQUE ICI
        }
        //  MAIL FROM accepté
        else if (line.startsWith("250") && m_sentMailFrom && !m_sentRcptTo) {
            qDebug() << "→ Envoi RCPT TO";
            m_socket->write("RCPT TO:<" + m_to.toUtf8() + ">\r\n");
            m_sentRcptTo = true;
        }
        //  RCPT TO accepté
        else if (line.startsWith("250") && m_sentRcptTo && !m_sentData) {
            qDebug() << "→ Envoi DATA";
            m_socket->write("DATA\r\n");
        }
        //  Serveur prêt pour le contenu
        else if (line.startsWith("354")) {
            qDebug() << "→ Envoi du message";
            m_socket->write(m_message.toUtf8());
            m_sentData = true;
        }
        //  Message accepté
        else if (line.startsWith("250") && m_sentData) {
            qDebug() << "✓ EMAIL ENVOYÉ AVEC SUCCÈS À" << m_to;
            emit envoiTermine();
            m_socket->write("QUIT\r\n");
            return;
        }
    }
}

void Smtp::onError(QAbstractSocket::SocketError err)
{
    qDebug() << "Erreur SMTP :" << err << m_socket->errorString();
    emit errorReceived(err);
}


