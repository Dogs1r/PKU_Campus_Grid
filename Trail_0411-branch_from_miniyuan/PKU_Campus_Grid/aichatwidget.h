#ifndef AICHATWIDGET_H
#define AICHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTimer>

class AIChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AIChatWidget(QWidget *parent = nullptr);
    ~AIChatWidget();

signals:
    void requestReturn();

private slots:
    void onSendClicked();
    void onReadyRead();
    void processStreamData();

private:
    QTextEdit *m_chatDisplay;
    QLineEdit *m_inputEdit;
    QPushButton *m_sendButton;
    QPushButton *m_returnButton;
    QNetworkAccessManager *m_networkManager;
    QFile m_logFile;
    QNetworkReply *m_currentReply;
    QTimer m_streamTimer;
    QString m_currentResponse;
    QString m_streamBuffer;

    void setupUI();
    void sendToDeepSeekAPI(const QString &question);
    void appendMessage(const QString &sender, const QString &message, bool isStreaming = false);
    void logInteraction(const QString &question, const QString &response);
    void abortCurrentRequest();
    void handleReplyFinished(QNetworkReply *reply);
};

#endif // AICHATWIDGET_H
