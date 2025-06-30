#include "canteenmanager.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

CanteenManager::CanteenManager(QWidget *parent)
    : QWidget(parent)
{
}

CanteenManager::~CanteenManager()
{
}

bool CanteenManager::loadCanteens(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开餐厅文件:" << filePath;
        return false;
    }

    canteens.clear();
    openingHours.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        Canteen canteen = Canteen::fromString(line);
        if (!canteen.name.isEmpty()) {
            canteens.append(canteen);
            openingHours.insert(canteen.name, canteen.getOpeningHoursString());
        }
    }

    file.close();
    qDebug() << "已加载" << canteens.size() << "家餐厅信息";
    return true;
}

bool CanteenManager::saveCanteens(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法保存餐厅文件:" << filePath;
        return false;
    }

    QTextStream out(&file);
    for (const Canteen &canteen : canteens) {
        out << canteen.toString() << "\n";
    }

    file.close();
    qDebug() << "餐厅信息已保存到:" << filePath;
    return true;
}

QStringList CanteenManager::findOpenCanteens(const QTime &time, const QString &place) const
{
    QStringList openCanteens;

    for (const Canteen &canteen : canteens) {
        // 如果指定了地点但匹配不上就跳过
        if (!place.isEmpty() &&
            !canteen.name.contains(place, Qt::CaseInsensitive) &&
            !canteen.description.contains(place, Qt::CaseInsensitive)) {
            continue;
        }

        for (const auto &period : canteen.openingTimes) {
            if (time >= period.first && time <= period.second) {
                QString timePeriod;
                if (period.first == canteen.openingTimes.first().first) {
                    timePeriod = "早餐";
                } else if (period.first == canteen.openingTimes.last().first) {
                    timePeriod = "晚餐";
                } else {
                    timePeriod = "午餐";
                }
                openCanteens << canteen.name + " - " + timePeriod + "开放 (" + canteen.description + ")";
                break;
            }
        }
    }

    return openCanteens;
}

QString CanteenManager::getOpeningHoursForPlace(const QString &place) const
{
    return openingHours.value(place, tr("未找到该餐厅的营业时间信息"));
}

QStringList CanteenManager::getAllCanteenNames() const
{
    QStringList names;
    for (const Canteen &canteen : canteens) {
        names << canteen.name;
    }
    return names;
}

// Canteen 类方法实现
Canteen Canteen::fromString(const QString &line)
{
    Canteen canteen;
    QStringList parts = line.split(" ", Qt::SkipEmptyParts);

    if (parts.size() < 3) {  // 至少需要名称、描述和一个时间段
        qWarning() << "无效的餐厅数据行:" << line;
        return canteen;
    }

    canteen.name = parts[0].trimmed();
    canteen.description = parts[1].trimmed();

    // 解析时间段 (从第2个元素开始)
    for (int i = 2; i < parts.size(); i++) {
        QStringList timeRange = parts[i].split("-");
        if (timeRange.size() == 2) {
            QTime start = QTime::fromString(timeRange[0], "HH:mm");
            QTime end = QTime::fromString(timeRange[1], "HH:mm");
            if (start.isValid() && end.isValid()) {
                canteen.openingTimes.append(qMakePair(start, end));
            }
        }
    }

    return canteen;
}

QString Canteen::toString() const
{
    QStringList parts;
    parts << name;
    parts << description;

    for (const auto &period : openingTimes) {
        parts << period.first.toString("HH:mm") + "-" + period.second.toString("HH:mm");
    }

    return parts.join(" ");
}

QString Canteen::getOpeningHoursString() const
{
    if (openingTimes.isEmpty()) {
        return QObject::tr("全天不营业");
    }

    QStringList periods;
    for (const auto &period : openingTimes) {
        periods << period.first.toString("HH:mm") + "-" + period.second.toString("HH:mm");
    }

    return name + QObject::tr(" 营业时间: ") + periods.join(", ") + " (" + description + ")";
}
