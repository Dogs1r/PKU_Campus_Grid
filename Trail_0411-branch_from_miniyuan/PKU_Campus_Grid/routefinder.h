#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include "mapview.h"

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QToolBar>
#include <QVector>
#include <QMap>

// 路径查询功能

namespace Ui {
class RouteFinder;
}

class RouteFinder : public QWidget
{
    Q_OBJECT

    static const int INF=999999;

public:
    explicit RouteFinder(MapView *mapView, QWidget *parent = nullptr);
    ~RouteFinder();

    void setStart(double X, double Y);
    void setEnd(double X, double Y);
    void setNextPos(int index);
    void FindPath();

private slots:
    void setStartStation();
    void setEndStation();
    void triggerFindPath();

signals:
    void startStationChanged(double X, double Y);
    void endStationChanged(double X, double Y);
    void pathFound(const QVector<int>& path);
    void requestReturn();

private:
    Ui::RouteFinder *ui;
    QComboBox *startComboBox;
    QComboBox *endComboBox;
    QComboBox *pathComboBox;
    QLabel *startLabel;
    QLabel *endLabel;
    QToolBar *toolBar;
    MapView *mapView;

    double startX, startY;
    double endX, endY;

    QVector<int> nextPath;
    QMap<QString, QPair<double, double>> nameToLocMap; //字典：<名称，坐标>
    QVector<QString> indexToNameMap; //索引：<编号，名称>
    QVector<QGraphicsItem*> pathItems;

    class DijkstraFindPath {
    public:
        DijkstraFindPath();
        ~DijkstraFindPath();
        void dijkstra(int startPos);
        QVector<int> get_Path(int endPos);

    private:
        struct ArcCell {
            double adj; // 权重
        };

        struct MGraph {
            int vexnum; // 顶点数

            QVector<int> vexs; // 顶点表
            ArcCell arcs[200][200]; // 邻接矩阵
        };

        MGraph mgraph;
        double d[200]; // 从起点到各点的最短距离
        bool used[200]; // 标记数组
        int prev[200]; // 前驱数组
        QMap<int, QPair<double, double>> indexToLocMap; // 字典：<编号，坐标>

        double manhattan(const QPair<double, double>& x, const QPair<double, double>& y);
        void loadVertices();

        friend class RouteFinder;
    };

    DijkstraFindPath *dj;

    void loadVertices();
    void drawMap();
    void drawPath(const QVector<int>& path);
};

#endif // ROUTEFINDER_H
