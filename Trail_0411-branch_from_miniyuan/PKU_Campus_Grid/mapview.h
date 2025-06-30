#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "bookmarkmanager.h"
#include "momentwidget.h"

#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsScene>

// 地图界面

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = nullptr);
    ~MapView();

    void moveBy(int dx, int dy);
    void zoomIn();
    void zoomOut();
    void mousePressEvent(QMouseEvent* event) override;
    void drawPath(const QList<QPointF>& pathPoints);
    void clearPath();
    void focusOnPath(const QList<QPointF>& pathPoints);
    void setBookmarkManager(BookmarkManager *manager);
    void handleMapClick(const QPointF &scenePos);
    void setMomentWidget(MomentWidget *widget) { momentWidget = widget; }
    QGraphicsScene* rtScene() { return this->scene; }

signals:
    void resized();
    void buildingClicked(const QString &buildingName);
    void momentCreated(const QString &imagePath, const QPointF &location);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    double scaleFactor = 1.15;  // 每次滚动缩放的倍率
    QGraphicsScene *scene; // 地图
    QGraphicsSvgItem *mainSvgItem;
    QVector<QPointF> markers;
    QList<QGraphicsItem*> pathItems; // 存储路径图形项
    BookmarkManager *m_bookmarkManager = nullptr;
    MomentWidget *momentWidget = nullptr;
    QLabel *timeLabel;
    QTimer *timer;
    QHash<QString, QGraphicsSvgItem*> m_buildings;
    QSet<QString> highlightBuildingIds;
    QGraphicsSvgItem* m_highlightItem = nullptr;
    QString m_highlightId = "";

    void loadHighlightBuildings();
    void processBuildings();
    void updateTime();
    void handleBuildingHighlight(const QPointF &scenePos);
    void handleMomentCreation(const QPointF &scenePos);

friend class MainWindow;
};

#endif // MAPVIEW_H
