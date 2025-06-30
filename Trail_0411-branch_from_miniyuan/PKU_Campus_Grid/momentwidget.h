#ifndef MOMENTWIDGET_H
#define MOMENTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QPointF>

namespace Ui {
class MomentWidget;
}

class MomentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MomentWidget(QWidget *parent = nullptr);
    ~MomentWidget();

    void addMoment(const QString &imagePath, const QPointF &location);

signals:
    void requestReturn();

private slots:
    void onMomentClicked(QListWidgetItem *item);
    void onDeleteMoment();
    void onDeleteAllMoments();
    void onViewMoment();

private:
    Ui::MomentWidget *ui;
    QListWidget *momentList;
    QPushButton *deleteButton;
    QPushButton *deleteAllButton;
    QPushButton *viewButton;

    struct Moment {
        QString imagePath;
        QPointF location;
        QString description;
    };

    QList<Moment> moments;

    void loadMoments();
    void saveMoments();
};

#endif // MOMENTWIDGET_H
