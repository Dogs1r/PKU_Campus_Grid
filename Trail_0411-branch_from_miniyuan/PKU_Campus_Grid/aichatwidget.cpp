#include "aichatwidget.h"

#include <QScrollBar>
#include <QDebug>
#include <QDateTime>

namespace {
    const char* API_KEY = "sk-e914e06a5a0f4827b57c747f11e145f1";
    const char* MODEL_NAME = "deepseek-chat";
}

AIChatWidget::AIChatWidget(QWidget *parent)
    : QWidget(parent), m_currentReply(nullptr)
{
    setupUI();
    m_networkManager = new QNetworkAccessManager(this);

    m_streamTimer.setInterval(100);
    connect(&m_streamTimer, &QTimer::timeout, this, &AIChatWidget::processStreamData);

    m_logFile.setFileName("ai_chat_log.txt");
    if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "无法打开日志文件:" << m_logFile.errorString();
    }
}

AIChatWidget::~AIChatWidget()
{
    abortCurrentRequest();
    m_logFile.close();
    delete m_networkManager;
}

void AIChatWidget::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_chatDisplay = new QTextEdit(this);
    m_chatDisplay->setReadOnly(true);
    m_chatDisplay->setStyleSheet("background-color: white;");
    layout->addWidget(m_chatDisplay);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    m_inputEdit = new QLineEdit(this);
    m_inputEdit->setPlaceholderText(tr("请输入关于北京大学校园的问题..."));
    m_sendButton = new QPushButton(tr("发送"), this);
    inputLayout->addWidget(m_inputEdit);
    inputLayout->addWidget(m_sendButton);
    layout->addLayout(inputLayout);

    m_returnButton = new QPushButton(tr("返回"), this);
    layout->addWidget(m_returnButton);

    connect(m_sendButton, &QPushButton::clicked, this, &AIChatWidget::onSendClicked);
    connect(m_returnButton, &QPushButton::clicked, this, &AIChatWidget::requestReturn);
    connect(m_inputEdit, &QLineEdit::returnPressed, this, &AIChatWidget::onSendClicked);

    appendMessage("AI", tr("您好！我是北京大学校园AI助手，请问有什么可以帮助您的吗？"));
}

void AIChatWidget::onSendClicked()
{
    QString question = m_inputEdit->text().trimmed();
    if (!question.isEmpty()) {
        abortCurrentRequest();
        appendMessage("您", question);
        m_inputEdit->clear();
        sendToDeepSeekAPI(question);
    }
}

void AIChatWidget::sendToDeepSeekAPI(const QString &question)
{
    QUrl url("https://api.deepseek.com/v1/chat/completions");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + QString(API_KEY)).toUtf8());
    request.setRawHeader("Accept", "text/event-stream");

    QJsonObject messageObj;
    messageObj["role"] = "user";
    messageObj["content"] = QString("你是一个北京大学校园助手。请回答关于北京大学校园的问题。问题：%1").arg(question);

    QJsonArray messagesArray;
    messagesArray.append(messageObj);

    QJsonObject jsonData;
    jsonData["model"] = MODEL_NAME;
    jsonData["messages"] = messagesArray;
    jsonData["temperature"] = 0.7;
    jsonData["max_tokens"] = 1000;
    jsonData["stream"] = true;

    QJsonDocument doc(jsonData);
    QByteArray data = doc.toJson();

    m_currentReply = m_networkManager->post(request, data);
    connect(m_currentReply, &QNetworkReply::readyRead, this, &AIChatWidget::onReadyRead);
    connect(m_currentReply, &QNetworkReply::finished, this, [this]() {
        handleReplyFinished(m_currentReply);
    });
    connect(m_currentReply, &QNetworkReply::errorOccurred, this, [this](QNetworkReply::NetworkError code) {
        Q_UNUSED(code);
        handleReplyFinished(m_currentReply);
    });

    m_currentResponse.clear();
    m_streamBuffer.clear();
    appendMessage("AI", "", true);
    m_streamTimer.start();
}

void AIChatWidget::onReadyRead()
{
    if (m_currentReply) {
        m_streamBuffer += m_currentReply->readAll();
    }
}

void AIChatWidget::processStreamData()
{
    if (m_streamBuffer.isEmpty()) {
        return;
    }

    QStringList events = m_streamBuffer.split("\n\n", Qt::SkipEmptyParts);
    m_streamBuffer.clear();

    for (const QString &event : events) {
        if (event.startsWith("data:") && !event.contains("[DONE]")) {
            QString data = event.mid(5).trimmed();
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            if (!doc.isNull()) {
                QJsonObject obj = doc.object();
                if (obj.contains("choices")) {
                    QJsonArray choices = obj["choices"].toArray();
                    if (!choices.isEmpty()) {
                        QJsonObject choice = choices[0].toObject();
                        if (choice.contains("delta")) {
                            QJsonObject delta = choice["delta"].toObject();
                            if (delta.contains("content")) {
                                QString content = delta["content"].toString();
                                m_currentResponse += content;

                                QTextCursor cursor = m_chatDisplay->textCursor();
                                cursor.movePosition(QTextCursor::End);
                                cursor.select(QTextCursor::BlockUnderCursor);
                                cursor.removeSelectedText();
                                cursor.insertHtml(QString("<b>AI:</b> %1<br>").arg(m_currentResponse));
                                m_chatDisplay->verticalScrollBar()->setValue(m_chatDisplay->verticalScrollBar()->maximum());
                            }
                        }
                    }
                }
            }
        }
    }
}

void AIChatWidget::handleReplyFinished(QNetworkReply *reply)
{
    m_streamTimer.stop();

    if (reply == m_currentReply) {
        m_currentReply = nullptr;
    }

    if (reply->error() == QNetworkReply::NoError) {
        processStreamData();
        logInteraction(m_inputEdit->text().trimmed(), m_currentResponse);
    } else if (reply->error() != QNetworkReply::OperationCanceledError) {
        QString errorMsg = tr("网络错误，请稍后再试。");
        appendMessage("AI", errorMsg);
        logInteraction(m_inputEdit->text().trimmed(), errorMsg);
        qDebug() << "Error:" << reply->errorString();
    }

    reply->deleteLater();
}

void AIChatWidget::appendMessage(const QString &sender, const QString &message, bool isStreaming)
{
    if (!isStreaming) {
        QString formattedMessage = QString("<b>%1:</b> %2<br>").arg(sender, message);
        m_chatDisplay->append(formattedMessage);
    } else {
        m_chatDisplay->append(QString("<b>%1:</b> <span id='streaming-message'></span><br>").arg(sender));
    }
    m_chatDisplay->verticalScrollBar()->setValue(m_chatDisplay->verticalScrollBar()->maximum());
}

void AIChatWidget::logInteraction(const QString &question, const QString &response)
{
    if (m_logFile.isOpen()) {
        QTextStream out(&m_logFile);
        out << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n";
        out << "问题: " << question << "\n";
        out << "回答: " << response << "\n";
        out << "----------------------------------------\n";
        out.flush();
    }
}

void AIChatWidget::abortCurrentRequest()
{
    if (m_currentReply) {
        m_streamTimer.stop();
        m_currentReply->disconnect(this);
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
}
