#include "buildinginfomanager.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

BuildingManager::BuildingManager(QObject *parent) : QObject(parent) {}

bool BuildingManager::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open building info file:" << filePath;
        return false;
    }

    QTextStream in(&file);
    QString currentId;
    BuildingInfoManager::BuildingInfo currentInfo;
    bool readingDetails = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // 跳过空行
        if (line.isEmpty()) {
            continue;
        }

        // 检查是否是新的建筑ID行 (格式: #1 中文名 英文名 x y)
        if (line.startsWith("#")) {
            // 如果已经有正在读取的建筑，先保存
            if (!currentId.isEmpty()) {
                m_buildings.insert(currentId, currentInfo);
                currentInfo = BuildingInfoManager::BuildingInfo(); // 重置
            }

            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() < 5) {
                qWarning() << "Invalid building header line:" << line;
                continue;
            }

            currentId = parts[0];
            currentInfo.name_CN = parts[1];
            currentInfo.name_US = parts[2];
            currentInfo.position = QPointF(parts[3].toDouble(), parts[4].toDouble());
            currentInfo.details.clear();
            readingDetails = true;
        }
        // 否则作为详细信息追加
        else if (readingDetails) {
            if (!currentInfo.details.isEmpty()) {
                currentInfo.details += "\n"; // 添加换行分隔
            }
            currentInfo.details += line;
        }
    }

    // 保存最后一个建筑信息
    if (!currentId.isEmpty()) {
        m_buildings.insert(currentId, currentInfo);
    }

    file.close();
    return true;
}

const BuildingInfoManager::BuildingInfo* BuildingManager::getBuildingInfo(const QString &id) const {
    auto it = m_buildings.find(id);
    return it != m_buildings.end() ? &it.value() : nullptr;
}
