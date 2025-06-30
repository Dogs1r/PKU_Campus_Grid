#include "studyfinderwidget.h"
#include "languagemanager.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>

StudyFinderWidget::StudyFinderWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("教室查询");

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    // 初始化教室数据
    classrooms = {{"二教", "101", true, true},
                  {"二教", "102", false, true},
                  {"理教", "201", true, false},
                  {"理教", "202", false, false},
                  {"三教", "301", true, true},
                  {"三教", "302", true, false},
                  {"图书馆", "二层西区", false, true},
                  {"图书馆", "二层东区", true, false},
                  {"文史楼", "401", true, true},
                  {"文史楼", "402", false, true}};

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 返回按钮
    QToolButton *returnButton = langManager->createTranslatableToolButton("StudyFinderWidget", tr("返回导航"), this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    returnButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(returnButton, &QToolButton::clicked, this, &StudyFinderWidget::requestReturn);
    mainLayout->addWidget(returnButton);

    // 教室要求
    QGroupBox *sizeGroup = langManager->createTranslatableGroupBox("StudyFinderWidget", tr("教室要求"), this);
    QVBoxLayout *sizeLayout = new QVBoxLayout;
    largeRoom = new QRadioButton(tr("大教室"), sizeGroup);
    smallRoom = new QRadioButton(tr("小教室"), sizeGroup);
    anySize = new QRadioButton(tr("我没意见"), sizeGroup);
    anySize->setChecked(true);

    sizeLayout->addWidget(largeRoom);
    sizeLayout->addWidget(smallRoom);
    sizeLayout->addWidget(anySize);
    sizeGroup->setLayout(sizeLayout);
    mainLayout->addWidget(sizeGroup);

    // 插座要求
    QGroupBox *socketGroup = langManager->createTranslatableGroupBox("StudyFinderWidget", tr("插座要求"), this);
    QVBoxLayout *socketLayout = new QVBoxLayout;
    needSocket = new QRadioButton(tr("有要求"), socketGroup);
    anySocket = new QRadioButton(tr("我没意见"), socketGroup);
    anySocket->setChecked(true);

    socketLayout->addWidget(needSocket);
    socketLayout->addWidget(anySocket);
    socketGroup->setLayout(socketLayout);
    mainLayout->addWidget(socketGroup);

    // 按钮组
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *confirmButton = langManager->createTranslatablePushButton("StudyFinderWidget", tr("确认"), this);
    QPushButton *cancelButton = langManager->createTranslatablePushButton("StudyFinderWidget", tr("取消"), this);

    connect(confirmButton, &QPushButton::clicked, this, &StudyFinderWidget::onConfirmClicked);
    connect(cancelButton, &QPushButton::clicked, this, &StudyFinderWidget::close);

    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

StudyFinderWidget::~StudyFinderWidget()
{
}

void StudyFinderWidget::onConfirmClicked()
{
    // 获取用户选择
    bool requireLarge = largeRoom->isChecked();
    bool requireSmall = smallRoom->isChecked();
    bool requireSocket = needSocket->isChecked();

    // 过滤符合条件的教室
    QList<Classroom> availableClassrooms;
    for (const Classroom &room : classrooms) {
        // 检查大小要求
        bool sizeMatch = true;
        if (requireLarge) sizeMatch = room.isLarge;
        else if (requireSmall) sizeMatch = !room.isLarge;

        // 检查插座要求
        bool socketMatch = !requireSocket || room.hasSocket;

        if (sizeMatch && socketMatch) {
            availableClassrooms.append(room);
        }
    }

    // 随机推荐教室
    if (!availableClassrooms.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(availableClassrooms.size());
        Classroom recommended = availableClassrooms[index];

        QMessageBox::information(
            this,
            tr("推荐教室"),
            QString(tr("为您推荐：\n教学楼：%1\n教室号：%2\n%3\n%4"))
                .arg(recommended.building)
                .arg(recommended.room)
                .arg(recommended.isLarge ? tr("类型：大教室") : tr("类型：小教室"))
                .arg(recommended.hasSocket ? tr("有插座") : tr("无插座"))
            );
    } else {
        QMessageBox::warning(this, tr("提示"), tr("没有找到符合条件的教室"));
    }
}
