#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSvgItem>

// 地点收藏

namespace BookmarkSystem
{
    struct BuildingInfo {
        QString name;
        QPoint position;
    };
}


class BookmarkManager : public QObject
{
    Q_OBJECT

public:
    explicit BookmarkManager(QObject *parent = nullptr);
    ~BookmarkManager();

    bool loadBuildings();
    void toggleBookmark(const QString &buildingName);
    bool isBookmarked(const QString &buildingName) const;
    QPoint getBuildingPosition(const QString &buildingName) const;
    void updateBookmarkMarks(QGraphicsScene *scene);
    const QList<BookmarkSystem::BuildingInfo>& rtBuildings() const { return buildings; }
    QSet<QString> rtBookmarkedBuildings() const { return bookmarkedBuildings; }
    QStringList getAllBuildingNames() const
    {
        QStringList names;
        for (const auto& building : buildings) {
            names.append(building.name);
        }
        return names;
    };

signals:
    void bookmarksChanged();

private:
    QVector<BookmarkSystem::BuildingInfo> buildings;
    QSet<QString> bookmarkedBuildings;
    QMap<QString, QGraphicsSvgItem*> bookmarkMarkers;

    void saveBookmarks();   // 保存收藏到文件
    void loadBookmarks();   // 从文件加载收藏
};

#endif // BOOKMARKMANAGER_H
