#ifndef BUILDINGDETAILWIDGET_H
#define BUILDINGDETAILWIDGET_H

#include "fancytoolbar.h"

#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class BuildingDetailWidget : public FancyToolBar
{
    Q_OBJECT

public:
    explicit BuildingDetailWidget(QWidget *parent = nullptr);
    ~BuildingDetailWidget();

    void setBuildingInfo(const QString &title, const QString &details);
    void updatePosition();

signals:
    void requestReturn();

protected:
    void setupUI();

private:
    QLabel *m_titleLabel;
    QTextEdit *m_detailsText;
    QPushButton *m_closeButton;
};

#endif // BUILDINGDETAILWIDGET_H
