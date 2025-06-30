#ifndef CANTEENMANAGER_H
#define CANTEENMANAGER_H

#include <QWidget>
#include <QTime>
#include <QStringList>
#include <QMap>

struct Canteen {
    QString name;
    QString description;  // 餐厅描述
    QList<QPair<QTime, QTime>> openingTimes;  // 改为时间段列表

    static Canteen fromString(const QString &line);
    QString toString() const;
    QString getOpeningHoursString() const;
};

class CanteenManager : public QWidget
{
    Q_OBJECT

public:
    explicit CanteenManager(QWidget *parent = nullptr);
    ~CanteenManager();

    bool loadCanteens(const QString &filePath);
    bool saveCanteens(const QString &filePath);
    QStringList findOpenCanteens(const QTime &time, const QString &place = "") const;
    QString getOpeningHoursForPlace(const QString &place) const;
    QStringList getAllCanteenNames() const;

private:
    QList<Canteen> canteens;
    QMap<QString, QString> openingHours;  // 餐厅名称 -> 营业时间描述
};

#endif // CANTEENMANAGER_H
