#include "SlotMachineDialog.h"
#include "languagemanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QSettings>
#include <QDir>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>

// 老虎机

const QString SETTINGS_ORGANIZATION = "CampusMapViewer";
const QString SETTINGS_APPLICATION = "SlotMachine";
const QString COINS_KEY = "coins";
const QString EASY_MODE_KEY = "easyMode";

SlotMachineDialog::SlotMachineDialog(QWidget *parent)
    : QDialog(parent), spinCount(0), spinDuration(50), spinning(false),
    wheelsStopped(0), coins(0), easyMode(false)
{
    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    setWindowTitle(tr("燕园老虎机"));
    resize(600, 500); // 增加高度以容纳新模式选项
    //setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");

    // 加载保存的金币数量和模式状态
    loadCoins();

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 创建老虎机滚轮
    QHBoxLayout *wheelsLayout = new QHBoxLayout;
    wheelsLayout->setSpacing(15);

    for (int i = 0; i < 3; ++i) {
        WheelState state;

        QLabel *wheel = new QLabel("⭐", this);
        wheel->setAlignment(Qt::AlignCenter);
        QFont font = wheel->font();
        font.setPointSize(48);
        wheel->setFont(font);
        wheel->setStyleSheet(
            "border: 3px solid #F1C40F;"
            "border-radius: 15px;"
            "background-color: #34495E;"
            "color: #F1C40F;"
            "padding: 10px;"
            );
        wheel->setMinimumSize(150, 150);
        // 使用HTML和CSS放大符号
        wheel->setText(QString("<html><div style='font-size:72pt;'>%1</div></html>").arg("⭐"));

        state.label = wheel;
        state.currentIndex = 0;
        state.isSpinning = false;
        state.stopCount = spinDuration + (i * 10);

        wheelStates.append(state);
        wheelsLayout->addWidget(wheel);
    }
    mainLayout->addLayout(wheelsLayout);

    // 创建开始按钮
    startButton = langManager->createTranslatablePushButton("SlotMachineDialog", tr("开始游戏"), this);
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #27AE60;"
        "   color: white;"
        "   border: none;"
        "   padding: 15px 30px;"
        "   font-size: 20px;"
        "   border-radius: 10px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2ECC71;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #7F8C8D;"
        "}"
        );
    connect(startButton, &QPushButton::clicked, this, &SlotMachineDialog::startSpin);
    mainLayout->addWidget(startButton, 0, Qt::AlignCenter);

    // 创建结果标签
    resultLabel = langManager->createTranslatableLabel("SlotMachineDialog", tr("点击 '开始游戏' 试一试你的运气吧!"), this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #BDC3C7;");
    mainLayout->addWidget(resultLabel);

    // 创建底部面板（金币显示和模式选择）
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // 金币显示窗口（左下角）
    QHBoxLayout *coinsLayout = new QHBoxLayout();
    coinsLayout->setAlignment(Qt::AlignLeft);

    // 使用Unicode货币符号代替图标
    QLabel *coinIcon = new QLabel("💰", this);
    coinIcon->setStyleSheet("font-size: 24px; margin-left: 10px;");

    coinsLabel = langManager->createTranslatableLabel("SlotMachineDialog", QString("Coins: %1").arg(coins), this);
    coinsLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #F1C40F;"
        "background-color: rgba(0, 0, 0, 100);"
        "border-radius: 10px;"
        "padding: 5px 10px;"
        "margin: 10px;"
        );

    coinsLayout->addWidget(coinIcon);
    coinsLayout->addWidget(coinsLabel);

    // 弱者模式选项（右下角）
    QGroupBox *modeGroup = new QGroupBox("", this);
    modeGroup->setStyleSheet(
        "QGroupBox {"
        "   border: 2px solid #F1C40F;"
        "   border-radius: 10px;"
        "   margin-top: 1ex;"
        "   background-color: rgba(52, 73, 94, 150);"
        "   padding: 10px;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 0 5px;"
        "   color: #F1C40F;"
        "   font-weight: bold;"
        "}"
        );

    QVBoxLayout *modeLayout = new QVBoxLayout(modeGroup);

    easyModeCheckbox = new QCheckBox(tr("简易模式（只有中间的轮子会转动）"), this);
    easyModeCheckbox->setStyleSheet(
        "QCheckBox {"
        "   color: #ECF0F1;"
        "   font-size: 16px;"
        "}"
        "QCheckBox::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
        );
    easyModeCheckbox->setChecked(easyMode);
    connect(easyModeCheckbox, &QCheckBox::toggled, this, &SlotMachineDialog::toggleEasyMode);

    modeLayout->addWidget(easyModeCheckbox);
    modeGroup->setLayout(modeLayout);

    // 将金币显示和模式选择添加到底部布局
    bottomLayout->addLayout(coinsLayout);
    bottomLayout->addStretch();
    bottomLayout->addWidget(modeGroup);

    mainLayout->addLayout(bottomLayout);

    // 初始化定时器
    spinTimer = new QTimer(this);
    spinTimer->setInterval(80);
    connect(spinTimer, &QTimer::timeout, this, &SlotMachineDialog::updateWheels);
}

SlotMachineDialog::~SlotMachineDialog()
{
    // 保存金币数量和模式状态
    saveCoins();
}

void SlotMachineDialog::loadCoins()
{
    // 使用QSettings加载金币数量和模式状态
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    // 如果存在保存的值则加载，否则使用默认值
    coins = settings.value(COINS_KEY, 10).toInt();
    easyMode = settings.value(EASY_MODE_KEY, false).toBool();
}

void SlotMachineDialog::addCoins(int addVal)
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);
    int current = settings.value(COINS_KEY, 10).toInt();
    settings.setValue(COINS_KEY, current + addVal);
}

void SlotMachineDialog::saveCoins()
{
    // 使用QSettings保存金币数量和模式状态
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);
    settings.setValue(COINS_KEY, coins);
    settings.setValue(EASY_MODE_KEY, easyMode);
}

void SlotMachineDialog::toggleEasyMode(bool checked)
{
    easyMode = checked;

    // 保存模式状态
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);
    settings.setValue(EASY_MODE_KEY, easyMode);

    if (easyMode) {
        resultLabel->setText(tr("已启用简易模式，只有中间的轮子会转动。"));
    } else {
        resultLabel->setText(tr("已启用正常模式，所有的轮子都会转动。"));
    }

    resultLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498DB;");

    // 添加结果动画
    QPropertyAnimation *animation = new QPropertyAnimation(resultLabel, "geometry");
    animation->setDuration(500);
    animation->setKeyValueAt(0, resultLabel->geometry());
    animation->setKeyValueAt(0.3, resultLabel->geometry().adjusted(0, -10, 0, -10));
    animation->setKeyValueAt(1, resultLabel->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlotMachineDialog::startSpin()
{
    if (spinning) return;
    if (coins < 1)
    {
        QMessageBox::information(this, tr("注意"), tr("金币已耗尽！快去发布动态获取吧！"));
        return;
    }

    // 消耗一个金币
    coins--;
    updateCoinsDisplay();

    spinning = true;
    spinCount = 0;
    startButton->setEnabled(false);

    if (easyMode) {
        resultLabel->setText(tr("简易模式游戏中... （消耗1金币）"));

        // 在弱者模式下，固定第一个和第三个滚轮为相同符号
        fixedSymbol = symbols[QRandomGenerator::global()->bounded(symbols.size())];
        wheelStates[0].label->setText(fixedSymbol);
        wheelStates[2].label->setText(fixedSymbol);

        // 在弱者模式下，固定滚轮已经停止
        wheelsStopped = 2; // 第一个和第三个滚轮已经停止
    } else {
        resultLabel->setText(tr("正常模式模式游戏中... （消耗1金币）"));
        wheelsStopped = 0; // 正常模式重置停止计数器
    }

    resultLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #BDC3C7;");

    // 重置所有滚轮状态
    for (int i = 0; i < wheelStates.size(); ++i) {
        // 在弱者模式下，只有中间的滚轮会转动
        if (!easyMode || i == 1) {
            wheelStates[i].isSpinning = true;
            wheelStates[i].stopCount = spinDuration + (i * 10);
        } else {
            wheelStates[i].isSpinning = false;
        }

        // 清除旧残影
        for (QLabel* shadow : wheelStates[i].shadows) {
            shadow->deleteLater();
        }
        wheelStates[i].shadows.clear();
    }

    spinTimer->start();
}

void SlotMachineDialog::updateCoinsDisplay()
{
    coinsLabel->setText(QString("金币：%1").arg(coins));

    // 金币变化动画
    QPropertyAnimation *animation = new QPropertyAnimation(coinsLabel, "geometry");
    animation->setDuration(300);
    animation->setKeyValueAt(0, coinsLabel->geometry());
    animation->setKeyValueAt(0.3, coinsLabel->geometry().adjusted(-5, 0, 5, 0));
    animation->setKeyValueAt(1, coinsLabel->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // 金币数量变化时自动保存
    saveCoins();
}

void SlotMachineDialog::updateWheels()
{
    spinCount++;

    for (int i = 0; i < wheelStates.size(); ++i) {
        WheelState &state = wheelStates[i];

        if (state.isSpinning) {
            // 随机选择符号
            int randomIndex = QRandomGenerator::global()->bounded(symbols.size());
            QString symbol = symbols[randomIndex];

            // 更新滚轮显示
            state.label->setText(QString("<html><div style='font-size:72pt;'>%1</div></html>").arg(symbol));

            // 创建残影效果
            createShadowEffect(state.label, symbol);

            // 检查是否应该停止
            if (spinCount >= state.stopCount) {
                state.isSpinning = false;
                wheelsStopped++;

                // 添加停止动画
                QPropertyAnimation *animation = new QPropertyAnimation(state.label, "geometry");
                animation->setDuration(300);
                animation->setKeyValueAt(0, state.label->geometry());
                animation->setKeyValueAt(0.5, state.label->geometry().adjusted(-5, -5, 5, 5));
                animation->setKeyValueAt(1, state.label->geometry());
                animation->start(QAbstractAnimation::DeleteWhenStopped);
            }
        }
    }

    // 所有滚轮都停止后检查结果
    // 使用固定值3而不是wheelStates.size()确保在弱者模式下也能触发
    if (wheelsStopped >= 3) {
        spinTimer->stop();
        spinning = false;
        startButton->setEnabled(true);
        QTimer::singleShot(500, this, &SlotMachineDialog::checkResult);
    }
}

void SlotMachineDialog::createShadowEffect(QLabel* wheel, const QString& symbol)
{
    // 创建残影标签
    QLabel *shadow = new QLabel(this);
    shadow->setText(QString("<html><div style='font-size:72pt;'>%1</div></html>").arg(symbol));
    shadow->setAlignment(Qt::AlignCenter);
    shadow->setFont(wheel->font());

    // 设置半透明效果
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(shadow);
    opacityEffect->setOpacity(0.6);
    shadow->setGraphicsEffect(opacityEffect);

    // 设置样式
    shadow->setStyleSheet(
        "border: 2px solid rgba(241, 196, 15, 150);"
        "border-radius: 10px;"
        "background-color: rgba(52, 73, 94, 200);"
        "color: rgba(241, 196, 15, 150);"
        );

    // 设置位置和大小
    shadow->setGeometry(wheel->geometry());
    shadow->show();

    // 添加到当前滚轮的残影列表
    for (int i = 0; i < wheelStates.size(); ++i) {
        if (wheelStates[i].label == wheel) {
            wheelStates[i].shadows.append(shadow);
            break;
        }
    }

    // 创建渐隐动画
    QPropertyAnimation *fadeAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    fadeAnimation->setDuration(800);
    fadeAnimation->setStartValue(0.6);
    fadeAnimation->setEndValue(0.0);
    fadeAnimation->setEasingCurve(QEasingCurve::OutQuad);

    // 动画结束后删除残影标签
    connect(fadeAnimation, &QPropertyAnimation::finished, [shadow, this]() {
        shadow->deleteLater();

        // 从残影列表中移除
        for (int i = 0; i < wheelStates.size(); ++i) {
            if (wheelStates[i].shadows.contains(shadow)) {
                wheelStates[i].shadows.removeOne(shadow);
                break;
            }
        }
    });

    fadeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlotMachineDialog::checkResult()
{
    QString result1 = wheelStates[0].label->text();
    QString result2 = wheelStates[1].label->text();
    QString result3 = wheelStates[2].label->text();

    if (easyMode) {
        // 在弱者模式下，第一个和第三个是固定的相同符号
        // 所以只需要检查中间滚轮是否匹配两边的符号

        if (result2 == result1) { // 因为result1 == result3
            // 三个相同
            if (result2 == "7️⃣") {
                coins += 6;
                resultLabel->setText(tr("🎉 Jackpot！你赢得了6枚金币！🎉"));
                resultLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFD700;");
            } else {
                coins += 3;
                resultLabel->setText(tr("🎉 恭喜！你赢得了3枚金币！🎉"));
                resultLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2ECC71;");
            }
        } else {
            // 两个相同（第一个和第三个相同）
            resultLabel->setText(tr("👍 差一点！已经有两个一样了！👍"));
            resultLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #3498DB;");
        }
    } else {
        // 正常模式
        if (result1 == result2 && result2 == result3) {

            if (result1 == "7️⃣") {
                coins += 6;
                resultLabel->setText(tr("🎉 Jackpot！你赢得了6枚金币！🎉"));
                resultLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFD700;");
            } else {
                resultLabel->setText(tr("🎉 恭喜！你赢得了3枚金币！🎉"));
                resultLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2ECC71;");
            }
        } else if (result1 == result2 || result2 == result3 || result1 == result3) {
            resultLabel->setText(tr("👍 差一点！已经有两个一样了！👍"));
            resultLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #3498DB;");
        } else {
            resultLabel->setText(tr("😢 很遗憾，没有相同的哦。 😢"));
            resultLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #E74C3C;");
        }
    }

    // 更新金币显示
    updateCoinsDisplay();

    // 添加结果动画
    QPropertyAnimation *animation = new QPropertyAnimation(resultLabel, "geometry");
    animation->setDuration(500);
    animation->setKeyValueAt(0, resultLabel->geometry());
    animation->setKeyValueAt(0.3, resultLabel->geometry().adjusted(0, -10, 0, -10));
    animation->setKeyValueAt(1, resultLabel->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlotMachineDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    loadCoins(); // 重新从QSettings加载
    updateCoinsDisplay();
}
