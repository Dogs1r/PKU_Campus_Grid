#include "buildinginteractionsystem.h"

#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsEffect>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

// 建筑交互系统

BuildingInteractionSystem::BuildingInteractionSystem(QGraphicsView* mapView,
                                                     BuildingManager* buildingManager,
                                                     QObject* parent)
    : QObject(parent),
    m_mapView(mapView),
    m_buildingManager(buildingManager),
    m_tooltipGroup(nullptr),
    m_detailWidget(nullptr)
{
    Q_ASSERT(m_mapView);
    Q_ASSERT(m_buildingManager);

    m_mapView->viewport()->installEventFilter(this);
    m_mapView->setMouseTracking(true);

    m_hoverTimer.setSingleShot(true);
    connect(&m_hoverTimer, &QTimer::timeout, this, &BuildingInteractionSystem::handleDelayedTooltip);
}

BuildingInteractionSystem::~BuildingInteractionSystem()
{
    cleanupResources();
}

bool BuildingInteractionSystem::isViewValid() const
{
    return m_mapView && m_mapView->scene() && m_mapView->viewport();
}

void BuildingInteractionSystem::cleanupResources()
{
    m_hoverTimer.stop();
    hideTooltip();

    if (m_detailWidget) {
        m_detailWidget->deleteLater();
        m_detailWidget = nullptr;
    }

    if (m_mapView) {
        m_mapView->viewport()->removeEventFilter(this);
    }
}

void BuildingInteractionSystem::handleDelayedTooltip()
{
    if (!m_currentHoverId.isEmpty() && isViewValid()) {
        showTooltip(m_currentHoverId, m_lastScenePos);
    }
}

bool BuildingInteractionSystem::eventFilter(QObject* watched, QEvent* event)
{
    if (!isViewValid() || watched != m_mapView->viewport()) {
        return false;
    }

    switch (event->type()) {
    case QEvent::MouseMove: {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        m_lastScenePos = m_mapView->mapToScene(mouseEvent->pos());

        // 查找最近的建筑
        QString closestId;
        qreal minDistance = 20; // 像素阈值

        const auto& buildings = m_buildingManager->allBuildings();
        for (auto it = buildings.constBegin(); it != buildings.constEnd(); ++it) {
            qreal distance = QLineF(m_lastScenePos, it.value().position).length();
            if (distance < minDistance) {
                minDistance = distance;
                closestId = it.key();
            }
        }

        if (closestId != m_currentHoverId) {
            m_hoverTimer.stop();
            hideTooltip();
            m_currentHoverId = closestId;

            if (!m_currentHoverId.isEmpty()) {
                m_hoverTimer.start(500); // 500毫秒延迟显示
            }
        }
        break;
    }
    case QEvent::Leave:
        m_hoverTimer.stop();
        hideTooltip();
        m_currentHoverId.clear();
        break;
    case QEvent::MouseButtonPress: {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton && !m_currentHoverId.isEmpty()) {
            showBuildingDetails(m_currentHoverId);
            return true;
        }
        break;
    }
    default:
        break;
    }

    return false;
}

void BuildingInteractionSystem::showTooltip(const QString& buildingId, const QPointF& scenePos)
{
    if (!isViewValid() || buildingId.isEmpty()) {
        return;
    }

    const auto info = m_buildingManager->getBuildingInfo(buildingId);
    if (!info) {
        qDebug() << "Building info not found for:" << buildingId;
        return;
    }

    // 创建工具提示组（如果不存在）
    if (!m_tooltipGroup) {
        m_tooltipGroup = new QGraphicsItemGroup;
        m_tooltipGroup->setZValue(1000); // 确保在最上层

        // 背景矩形
        m_tooltip.background = new QGraphicsRectItem(m_tooltipGroup);
        m_tooltip.background->setBrush(QColor(255, 255, 200, 220));
        m_tooltip.background->setPen(QPen(Qt::gray, 1));

        // 文本
        m_tooltip.text = new QGraphicsSimpleTextItem(m_tooltipGroup);
        m_tooltip.text->setBrush(Qt::black);
        QFont font;
        font.setBold(true);
        font.setPointSize(10);
        m_tooltip.text->setFont(font);

        m_mapView->scene()->addItem(m_tooltipGroup);
    }

    // 设置文本内容
    m_tooltip.text->setText(info->name_CN);

    // 计算背景大小
    QRectF textRect = m_tooltip.text->boundingRect();
    m_tooltip.background->setRect(textRect.adjusted(-5, -3, 5, 3));

    // 设置位置（稍微偏移鼠标位置）
    QPointF pos = scenePos + QPointF(15, -15 - textRect.height());

    // 确保不会超出视图
    QRectF viewRect = m_mapView->mapToScene(m_mapView->viewport()->rect()).boundingRect();
    if (pos.y() < viewRect.top()) {
        pos.setY(scenePos.y() + 15);
    }

    m_tooltipGroup->setPos(pos);
    qDebug() << "Showing tooltip at:" << pos;
}

void BuildingInteractionSystem::hideTooltip()
{
    if (m_tooltipGroup && isViewValid()) {
        m_mapView->scene()->removeItem(m_tooltipGroup);
        delete m_tooltipGroup;
        m_tooltipGroup = nullptr;
    }
}

void BuildingInteractionSystem::showBuildingDetails(const QString& buildingId)
{
    if (!isViewValid()) return;

    const auto info = m_buildingManager->getBuildingInfo(buildingId);
    if (!info) return;

    emit showDetailsRequested(info->name_CN, info->details);
}
