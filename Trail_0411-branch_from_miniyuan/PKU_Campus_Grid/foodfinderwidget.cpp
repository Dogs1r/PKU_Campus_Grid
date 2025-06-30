#include "foodfinderwidget.h"
#include "ui_foodfinderwidget.h"
#include "canteenmanager.h"
#include "languagemanager.h"

#include <QToolButton>
#include <QComboBox>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimeEdit>

FoodFinderWidget::FoodFinderWidget(CanteenManager *canteenManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FoodFinderWidget)
    , m_canteenManager(canteenManager)
{
    ui->setupUi(this);

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    setWindowTitle(tr("饿鬼寻饭"));

    // 返回按钮
    QToolButton *returnButton = langManager->createTranslatableToolButton("FoodFinderWidget", tr("返回导航"), this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    returnButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(returnButton, &QToolButton::clicked, this, &FoodFinderWidget::requestReturn);

    // 使用垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    mainLayout->addWidget(returnButton);

    // ==== 第一部分：按时间查询开放餐厅 ====
    QLabel *timeLabel = langManager->createTranslatableLabel("FoodFinderWidget", tr("查询当前时间开放的餐厅："), this);
    timeLabel->setStyleSheet("font-weight: bold;");
    mainLayout->addWidget(timeLabel);

    // 时间输入控件
    m_timeEdit = new QTimeEdit(QTime::currentTime());
    m_timeEdit->setDisplayFormat("HH:mm");

    // 设置原生按钮为垂直箭头样式
    m_timeEdit->setStyleSheet(
        "QTimeEdit::up-button {"
        "   subcontrol-origin: border;"
        "   subcontrol-position: top right;"
        "   width: 20px;"
        "   border-left: 1px solid gray;"
        "   border-bottom: 1px solid gray;"
        "   background: #F0F0F0;"
        "}"
        "QTimeEdit::up-arrow {"
        "   image: url(:/icon/up_arrow.svg);"  // 使用SVG箭头图标
        "   width: 10px;"
        "   height: 10px;"
        "}"
        "QTimeEdit::down-button {"
        "   subcontrol-origin: border;"
        "   subcontrol-position: bottom right;"
        "   width: 20px;"
        "   border-left: 1px solid gray;"
        "   background: #F0F0F0;"
        "}"
        "QTimeEdit::down-arrow {"
        "   image: url(:/icon/down_arrow.svg);"  // 使用SVG箭头图标
        "   width: 10px;"
        "   height: 10px;"
        "}"
    );

    mainLayout->addWidget(m_timeEdit);

    // 查询开放餐厅按钮
    QPushButton *checkOpeningButton = langManager->createTranslatablePushButton("FoodFinderWidget", tr("查询开放餐厅"), this);
    connect(checkOpeningButton, &QPushButton::clicked, this, &FoodFinderWidget::onCheckOpeningClicked);
    mainLayout->addWidget(checkOpeningButton);

    // ==== 第二部分：按餐厅查询营业时间 ====
    QLabel *canteenLabel = langManager->createTranslatableLabel("FoodFinderWidget", tr("查询指定餐厅的营业时间："), this);
    canteenLabel->setStyleSheet("font-weight: bold; margin-top: 15px;");
    mainLayout->addWidget(canteenLabel);

    // 餐厅选择框
    m_canteenComboBox = new QComboBox(this);
    // 从CanteenManager获取所有餐厅并添加到选择框
    m_canteenComboBox->addItems(m_canteenManager->getAllCanteenNames());
    mainLayout->addWidget(m_canteenComboBox);

    // 查询营业时间按钮
    QPushButton *checkHoursButton = langManager->createTranslatablePushButton("FoodFinderWidget", tr("查询营业时间"), this);
    connect(checkHoursButton, &QPushButton::clicked, this, &FoodFinderWidget::onCheckHoursClicked);
    mainLayout->addWidget(checkHoursButton);
}

FoodFinderWidget::~FoodFinderWidget()
{
    delete ui;
}

void FoodFinderWidget::onCheckOpeningClicked()
{
    QTime selectedTime = m_timeEdit->time();

    // 获取开放餐厅列表
    QStringList openCanteens = m_canteenManager->findOpenCanteens(selectedTime);

    QString result;
    if (!openCanteens.isEmpty()) {
        result = QObject::tr("当前开放的餐厅：\n") + openCanteens.join("\n");
    } else {
        result = QObject::tr("该时间没有开放的餐厅~");
    }

    QMessageBox::information(this, tr("查询结果"), result);
}

void FoodFinderWidget::onCheckHoursClicked()
{
    QString canteenName = m_canteenComboBox->currentText();

    if (canteenName.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("请选择要查询的餐厅"));
        return;
    }

    QString hours = m_canteenManager->getOpeningHoursForPlace(canteenName);

    if (!hours.isEmpty()) {
        QMessageBox::information(this, tr("营业时间"),
                                 QString(tr("%1 的营业时间：\n%2")).arg(canteenName).arg(hours));
    } else {
        QMessageBox::warning(this, tr("错误"), tr("未找到该餐厅的营业时间信息"));
    }
}
