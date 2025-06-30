#include "bookmarkmanager.h"

#include <QFile>
#include <QSvgRenderer>
#include <QGraphicsScene>
#include <QDebug>
#include <QSettings>
#include <QDir>

// 地点收藏

BookmarkManager::BookmarkManager(QObject *parent)
    : QObject(parent)
{
    // 确保应用数据目录存在
    QDir dir("marked_places");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    loadBuildings();
    loadBookmarks();  // 加载保存的收藏
}

BookmarkManager::~BookmarkManager()
{
    saveBookmarks();  // 保存收藏到文件
}

bool BookmarkManager::loadBuildings()
{
    QFile file(":/info/building_info.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开建筑物文件";
        return false;
    }

    QTextStream in(&file);
    buildings.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(' ', Qt::SkipEmptyParts);

        // 处理名称中包含空格的情况
        QString name = parts.mid(0, parts.size() - 2).join(" ");
        bool okX, okY;
        double x = parts[parts.size() - 2].toDouble(&okX);
        double y = parts[parts.size() - 1].toDouble(&okY);

        if (!okX || !okY) {
            qDebug() << "无效的坐标:" << line;
            continue;
        }

        buildings.append({name, QPoint(x, y)});
    }

    file.close();
    return true;
}

void BookmarkManager::saveBookmarks()
{
    QString settingsPath = QString("marked_places") + QString("/bookmarks.ini");
    QSettings settings(settingsPath, QSettings::IniFormat);

    // 保存收藏列表
    settings.beginWriteArray("bookmarks");
    int i = 0;
    for (const QString &building : bookmarkedBuildings) {
        settings.setArrayIndex(i);
        settings.setValue("name", building);
        i++;
    }
    settings.endArray();

    settings.sync();
    qDebug() << "收藏地点已保存到:" << settingsPath;
}

void BookmarkManager::loadBookmarks()
{
    QString settingsPath = QString("marked_places") + QString("/bookmarks.ini");
    QSettings settings(settingsPath, QSettings::IniFormat);

    // 加载收藏列表
    int size = settings.beginReadArray("bookmarks");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString name = settings.value("name").toString();
        if (!name.isEmpty()) {
            bookmarkedBuildings.insert(name);
        }
    }
    settings.endArray();

    emit bookmarksChanged();

    qDebug() << "已加载" << bookmarkedBuildings.size() << "个收藏地点";
}

void BookmarkManager::toggleBookmark(const QString &buildingName)
{
    if (bookmarkedBuildings.contains(buildingName)) {
        bookmarkedBuildings.remove(buildingName);
    } else {
        bookmarkedBuildings.insert(buildingName);
    }

    // 保存更改
    saveBookmarks();

    emit bookmarksChanged();
}

bool BookmarkManager::isBookmarked(const QString &buildingName) const
{
    return bookmarkedBuildings.contains(buildingName);
}

QPoint BookmarkManager::getBuildingPosition(const QString &buildingName) const
{
    for (const auto &building : buildings) {
        if (building.name == buildingName) {
            return building.position;
        }
    }
    return QPoint(-1, -1);
}

void BookmarkManager::updateBookmarkMarks(QGraphicsScene *scene)
{
    // 移除旧标记
    for (auto marker : bookmarkMarkers) {
        scene->removeItem(marker);
        delete marker;
    }
    bookmarkMarkers.clear();

    // 添加新标记
    for (const QString &name : bookmarkedBuildings) {
        QPoint pos = getBuildingPosition(name);
        if (pos.isNull()) continue;

        // 创建五角星SVG标记
        QGraphicsSvgItem *star = new QGraphicsSvgItem();
        star->setSharedRenderer(new QSvgRenderer(QString(":/assets/star.svg"))); // 需要资源文件
        star->setPos(pos.x() - star->boundingRect().width()/2,
                     pos.y() - star->boundingRect().height()/2);
        star->setZValue(100); // 确保在最上层
        scene->addItem(star);
        bookmarkMarkers.insert(name, star);
    }
}
