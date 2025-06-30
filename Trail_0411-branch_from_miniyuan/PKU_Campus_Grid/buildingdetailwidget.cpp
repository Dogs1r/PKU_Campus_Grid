#include "buildingdetailwidget.h"

#include <QScrollBar>
#include <QTimer>

BuildingDetailWidget::BuildingDetailWidget(QWidget *parent)
    : FancyToolBar(parent)
{
    setupUI();
    setObjectName("buildingDetailWidget");

    // 添加返回按钮
    addNavigationAction(":/icon/goback.png", "BuildingDetailWidget", tr("返回"));
    connect(action(tr("返回")), &QAction::triggered, this, [this]() {
        emit requestReturn();
    });
}

BuildingDetailWidget::~BuildingDetailWidget()
{
}

void BuildingDetailWidget::setupUI()
{
    // 主布局
    QWidget *contentWidget = new QWidget(this);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);

    // 标题标签
    m_titleLabel = new QLabel(contentWidget);
    m_titleLabel->setObjectName("buildingTitleLabel");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setMinimumHeight(40);

    // 字体设置
    QFont titleFont;
    titleFont.setFamily("Microsoft YaHei");
    titleFont.setPixelSize(30);
    titleFont.setWeight(QFont::Black);
    m_titleLabel->setFont(titleFont);
    mainLayout->addWidget(m_titleLabel);

    // 详细信息文本
    m_detailsText = new QTextEdit(contentWidget);
    m_detailsText->setObjectName("buildingDetailsText");
    m_detailsText->setReadOnly(true);
    m_detailsText->setFrameShape(QFrame::NoFrame);
    m_detailsText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_detailsText);

    // 设置主部件
    contentWidget->setLayout(mainLayout);
    addWidget(contentWidget);
}

void BuildingDetailWidget::setBuildingInfo(const QString &title, const QString &details)
{
    m_titleLabel->setText(title);
    m_detailsText->setText(details);

    // 自动滚动到顶部
    QTimer::singleShot(0, [this]() {
        m_detailsText->verticalScrollBar()->setValue(0);
    });
}

void BuildingDetailWidget::updatePosition()
{
    if (parentWidget()) {
        setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
    }
}
