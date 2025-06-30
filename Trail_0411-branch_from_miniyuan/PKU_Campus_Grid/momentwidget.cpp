#include "momentwidget.h"
#include "ui_momentwidget.h"
#include "languagemanager.h"

#include <QDebug>

MomentWidget::MomentWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MomentWidget)
{
    ui->setupUi(this);

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 返回按钮
    QPushButton *returnButton = langManager->createTranslatablePushButton("MomentWidget", tr("返回主工具栏"), this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    connect(returnButton, &QPushButton::clicked, this, &MomentWidget::requestReturn);
    mainLayout->addWidget(returnButton);

    // 动态列表
    momentList = new QListWidget(this);
    momentList->setViewMode(QListWidget::IconMode);
    momentList->setIconSize(QSize(100, 100));
    momentList->setResizeMode(QListWidget::Adjust);
    connect(momentList, &QListWidget::itemClicked, this, &MomentWidget::onMomentClicked);
    mainLayout->addWidget(momentList);

    // 按钮布局
    QVBoxLayout *buttonLayout = new QVBoxLayout();

    // 查看按钮
    viewButton = langManager->createTranslatablePushButton("MomentWidget", tr("查看动态"), this);
    viewButton->setIcon(QIcon(":/icon/view.png"));
    viewButton->setEnabled(false);
    connect(viewButton, &QPushButton::clicked, this, &MomentWidget::onViewMoment);
    buttonLayout->addWidget(viewButton);

    // 删除按钮
    deleteButton = langManager->createTranslatablePushButton("MomentWidget", tr("删除动态"), this);
    deleteButton->setIcon(QIcon(":/icon/clear.png"));
    deleteButton->setEnabled(false);
    connect(deleteButton, &QPushButton::clicked, this, &MomentWidget::onDeleteMoment);
    buttonLayout->addWidget(deleteButton);

    // 清空按钮
    deleteAllButton = langManager->createTranslatablePushButton("MomentWidget", tr("清空所有"), this);
    deleteAllButton->setIcon(QIcon(":/icon/delete.png"));
    connect(deleteAllButton, &QPushButton::clicked, this, &MomentWidget::onDeleteAllMoments);
    buttonLayout->addWidget(deleteAllButton);

    mainLayout->addLayout(buttonLayout);

    // 加载已有的动态
    loadMoments();
}

MomentWidget::~MomentWidget()
{
    delete ui;
}

void MomentWidget::loadMoments()
{
    QFile file("moments/moments.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        Moment moment;
        in >> moment.imagePath >> moment.location >> moment.description;
        moments.append(moment);

        // 添加到列表
        QListWidgetItem *item = new QListWidgetItem(
            QIcon(moment.imagePath),
            QString(tr("位置: (%1, %2)")).arg(moment.location.x()).arg(moment.location.y())
            );
        item->setData(Qt::UserRole, moment.imagePath);
        momentList->addItem(item);
    }

    file.close();
}

void MomentWidget::saveMoments()
{
    QDir dir("moments");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile file("moments/moments.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("错误"), tr("无法保存动态数据"));
        return;
    }

    QDataStream out(&file);
    for (const Moment &moment : moments) {
        out << moment.imagePath << moment.location << moment.description;
    }

    file.close();
}

void MomentWidget::addMoment(const QString &imagePath, const QPointF &location)
{
    // 请求用户输入描述
    bool ok;
    QString description = QInputDialog::getText(this, tr("添加描述"),
                                                tr("请输入动态描述:"), QLineEdit::Normal, "", &ok);

    if (!ok || description.isEmpty()) {
        description = tr("未添加描述");
    }

    // 创建新动态
    Moment moment;
    moment.imagePath = imagePath;
    moment.location = location;
    moment.description = description;
    moments.append(moment);

    // 添加到列表
    QListWidgetItem *item = new QListWidgetItem(
        QIcon(imagePath),
        QString(tr("位置: (%1, %2)")).arg(location.x()).arg(location.y())
        );
    item->setData(Qt::UserRole, imagePath);
    momentList->addItem(item);

    // 保存数据
    saveMoments();
}

void MomentWidget::onMomentClicked(QListWidgetItem *item)
{
    // 启用按钮
    viewButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void MomentWidget::onViewMoment()
{
    QListWidgetItem *item = momentList->currentItem();
    if (!item) return;

    QString imagePath = item->data(Qt::UserRole).toString();
    QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath));
}

void MomentWidget::onDeleteMoment()
{
    QListWidgetItem *item = momentList->currentItem();
    if (!item) return;

    int row = momentList->row(item);
    if (row < 0 || row >= moments.size()) return;

    // 删除文件
    QString imagePath = moments[row].imagePath;
    QFile::remove(imagePath);

    // 从数据结构中移除
    moments.removeAt(row);

    // 从列表中移除
    delete momentList->takeItem(row);

    // 保存更新
    saveMoments();

    // 禁用按钮
    viewButton->setEnabled(false);
    deleteButton->setEnabled(false);
}

void MomentWidget::onDeleteAllMoments()
{
    if (moments.isEmpty()) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("确认删除"),
                                  tr("确定要删除所有动态吗？此操作不可撤销！"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 删除所有文件
        for (const Moment &moment : moments) {
            QFile::remove(moment.imagePath);
        }

        // 清空数据
        moments.clear();
        momentList->clear();

        // 删除数据文件
        QFile::remove("moments/moments.dat");

        // 禁用按钮
        viewButton->setEnabled(false);
        deleteButton->setEnabled(false);
    }
}
