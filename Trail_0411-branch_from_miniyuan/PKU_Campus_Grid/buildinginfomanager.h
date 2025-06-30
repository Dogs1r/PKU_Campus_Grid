#ifndef BUILDINGINFOMANAGER_H
#define BUILDINGINFOMANAGER_H

#include <QObject>
#include <QPointF>
#include <QString>
#include <QHash>

// 管理建筑信息

namespace BuildingInfoManager {
    struct BuildingInfo {
        QString name_CN;
        QString name_US;
        QPointF position;
        QString details;
    };
}

class BuildingManager : public QObject {
    Q_OBJECT
public:
    explicit BuildingManager(QObject *parent = nullptr);

    bool loadFromFile(const QString &filePath);
    const BuildingInfoManager::BuildingInfo* getBuildingInfo(const QString &id) const;
    const QHash<QString, BuildingInfoManager::BuildingInfo>& allBuildings() const { return m_buildings; }

private:
    QHash<QString, BuildingInfoManager::BuildingInfo> m_buildings;
};

#endif // BUILDINGINFOMANAGER_H
