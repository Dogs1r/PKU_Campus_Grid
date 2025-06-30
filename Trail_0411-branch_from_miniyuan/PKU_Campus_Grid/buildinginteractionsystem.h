#ifndef BUILDINGINTERACTIONSYSTEM_H
#define BUILDINGINTERACTIONSYSTEM_H

#include "buildinginfomanager.h"

#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsItemGroup>
#include <QWidget>

// 建筑交互系统

class BuildingInteractionSystem : public QObject
{
    Q_OBJECT

public:
    explicit BuildingInteractionSystem(QGraphicsView* mapView,
                                       BuildingManager* buildingManager,
                                       QObject* parent = nullptr);
    ~BuildingInteractionSystem();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void showDetailsRequested(const QString& title, const QString& details);

private slots:
    void handleDelayedTooltip();

private:
    struct Tooltip {
        QGraphicsRectItem* background = nullptr;
        QGraphicsSimpleTextItem* text = nullptr;
    };

    void showTooltip(const QString& buildingId, const QPointF& scenePos);
    void hideTooltip();
    void showBuildingDetails(const QString& buildingId);
    void cleanupResources();
    bool isViewValid() const;

    QGraphicsView* m_mapView;
    BuildingManager* m_buildingManager;
    QTimer m_hoverTimer;
    QString m_currentHoverId;
    QGraphicsItemGroup* m_tooltipGroup;
    QWidget* m_detailWidget;
    QPointF m_lastScenePos;
    Tooltip m_tooltip;
};
#endif // BUILDINGINTERACTIONSYSTEM_H
