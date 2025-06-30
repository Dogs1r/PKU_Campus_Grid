#include "bookmarkwidget.h"
#include "ui_bookmarkwidget.h"
#include "languagemanager.h"

#include <QMessageBox>
#include <QComboBox>
#include <QCompleter>

BookmarkWidget::BookmarkWidget(BookmarkManager *bookmarkManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookmarkWidget)
    , m_bookmarkManager(bookmarkManager)
{
    ui->setupUi(this);

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 返回按钮
    returnButton = langManager->createTranslatablePushButton("BookmarkWidget", tr("返回主工具栏"), this);
    returnButton->setIcon(QIcon(":/icon/return.png"));
    connect(returnButton, &QPushButton::clicked, this, &BookmarkWidget::requestReturn);
    mainLayout->addWidget(returnButton);

    // 收藏列表
    bookmarkList = new QListWidget(this);
    bookmarkList->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(bookmarkList);

    // 添加收藏控件
    QHBoxLayout *addLayout = new QHBoxLayout();

    // 创建下拉框并设置属性
    buildingComboBox = new QComboBox(this);
    buildingComboBox->setEditable(true); // 允许用户输入
    buildingComboBox->setPlaceholderText(tr("输入或选择地点名称"));
    buildingComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 获取所有建筑物名称并填充下拉框
    QStringList allBuildings = m_bookmarkManager->getAllBuildingNames();
    buildingComboBox->addItems(allBuildings);

    // 设置自动补全
    QCompleter* completer = new QCompleter(allBuildings, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    buildingComboBox->setCompleter(completer);

    addButton = new QPushButton("", this);
    addButton->setIcon(QIcon(":/icon/star.png"));
    connect(addButton, &QPushButton::clicked, this, &BookmarkWidget::onAddBookmark);

    addLayout->addWidget(buildingComboBox);
    addLayout->addWidget(addButton);
    mainLayout->addLayout(addLayout);

    // 垂直布局
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setSpacing(5);

    removeButton = langManager->createTranslatablePushButton("BookmarkWidget", tr("移除选中"), this);
    removeButton->setIcon(QIcon(":/icon/clear.png"));
    connect(removeButton, &QPushButton::clicked, this, &BookmarkWidget::onRemoveBookmark);

    clearButton = langManager->createTranslatablePushButton("BookmarkWidget", tr("清除全部"), this);
    clearButton->setIcon(QIcon(":/icon/delete.png"));
    connect(clearButton, &QPushButton::clicked, this, &BookmarkWidget::onClearAll);

    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(clearButton);
    mainLayout->addLayout(buttonLayout);

    // 初始更新列表
    updateBookmarkList();

    // 监听收藏变化
    connect(m_bookmarkManager, &BookmarkManager::bookmarksChanged, this, &BookmarkWidget::updateBookmarkList);
}

BookmarkWidget::~BookmarkWidget()
{
    delete ui;
}

void BookmarkWidget::updateBookmarkList()
{
    bookmarkList->clear();
    for (const QString &name : m_bookmarkManager->rtBookmarkedBuildings()) {
        bookmarkList->addItem(name);
    }
}

void BookmarkWidget::onAddBookmark()
{
    QString name = buildingComboBox->currentText().trimmed();
    if (!name.isEmpty()) {
        // 检查地点是否有效
        QPoint pos = m_bookmarkManager->getBuildingPosition(name);
        if (!pos.isNull()) {
            m_bookmarkManager->toggleBookmark(name);
            buildingComboBox->clearEditText(); // 清空输入框
        } else {
            // 显示错误提示
            QMessageBox::warning(this, tr("无效地点"), tr("未找到该地点，请检查名称是否正确"));
        }
    }
}

void BookmarkWidget::onRemoveBookmark()
{
    QListWidgetItem *selected = bookmarkList->currentItem();
    if (selected) {
        m_bookmarkManager->toggleBookmark(selected->text());
    }
}

void BookmarkWidget::onClearAll()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("确认清除"), tr("确定要清除所有收藏地点吗？"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        for (const QString &name : m_bookmarkManager->rtBookmarkedBuildings()) {
            m_bookmarkManager->toggleBookmark(name);
        }
    }
}
