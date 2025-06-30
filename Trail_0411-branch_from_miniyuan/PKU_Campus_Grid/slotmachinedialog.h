#ifndef SLOTMACHINEDIALOG_H
#define SLOTMACHINEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QList>
#include <QPropertyAnimation>
#include <QSettings>
#include <QCheckBox>
#include <QGroupBox>

// 老虎机

namespace Ui {
class SlotMachineDialog;
}

class SlotMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlotMachineDialog(QWidget *parent = nullptr);
    ~SlotMachineDialog();

    static void addCoins(int addVal);

private slots:
    void startSpin();
    void updateWheels();
    void checkResult();
    void toggleEasyMode(bool checked); // 弱者模式切换

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::SlotMachineDialog *ui;

    struct WheelState {
        QLabel *label;
        int currentIndex;
        bool isSpinning;
        int stopCount;
        QList<QLabel*> shadows;
    };

    QList<WheelState> wheelStates;
    QTimer *spinTimer;
    int spinCount = 0;
    int spinDuration = 50;
    bool spinning = false;
    int wheelsStopped = 0;
    int coins = 0;
    bool easyMode = false; // 弱者模式标志

    QPushButton *startButton;
    QLabel *resultLabel;
    QLabel *coinsLabel;
    QCheckBox *easyModeCheckbox; // 弱者模式复选框
    QString fixedSymbol; // 固定滚轮显示的符号

    QStringList symbols = {"⭐", "7️⃣", "🍎", "🍒", "🍋", "🍊"};

    void createShadowEffect(QLabel* wheel, const QString& symbol);
    void updateCoinsDisplay();
    void saveCoins();
    void loadCoins();
};

#endif // SLOTMACHINEDIALOG_H
