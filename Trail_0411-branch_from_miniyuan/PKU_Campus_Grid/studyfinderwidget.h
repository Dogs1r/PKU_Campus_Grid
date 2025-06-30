#ifndef STUDYFINDERWIDGET_H
#define STUDYFINDERWIDGET_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>

// “我想学”功能

struct Classroom {
    QString building;
    QString room;
    bool isLarge;
    bool hasSocket;
};

namespace Ui {
class StudyFinderWidget;
}

class StudyFinderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudyFinderWidget(QWidget *parent = nullptr);
    ~StudyFinderWidget();

signals:
    void requestReturn();  // 返回导航信号

private slots:
    void onConfirmClicked();

private:
    QRadioButton *largeRoom;
    QRadioButton *smallRoom;
    QRadioButton *anySize;
    QRadioButton *needSocket;
    QRadioButton *anySocket;
    QList<Classroom> classrooms;
};

#endif // STUDYFINDERWIDGET_H
