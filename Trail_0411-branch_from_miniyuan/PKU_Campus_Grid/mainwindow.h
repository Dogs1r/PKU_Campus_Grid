#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mapview.h"
#include "floattingtoolbar.h"
#include "mapmenubar.h"
#include "buildinginteractionsystem.h"
#include "buildingdetailwidget.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPointF>
#include <QLabel>
#include <QTranslator>

// 主界面

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onThemeChanged(const QString &themeName);
    void onLanguageChanged(const QString &languageCode);

private:
    Ui::MainWindow *ui;
    MapView *view;
    QHBoxLayout *mainLayout;
    QLabel *coordLabel;
    QLabel *scaleLabel;
    FloattingToolBar *floatTool;
    QWidget *toolbarContainer;
    MapMenubar *menubar;
    QTranslator *m_translator;
    BuildingManager m_buildingManager;
    BuildingInteractionSystem *m_buildingInteractor;
    BuildingDetailWidget *m_buildingDetailWidget = nullptr;

    void showBuildingDetails(const QString& title, const QString& details);
};
#endif // MAINWINDOW_H
