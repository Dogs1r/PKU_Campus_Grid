#ifndef BOOKMARKWIDGET_H
#define BOOKMARKWIDGET_H

#include "bookmarkmanager.h"

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

namespace Ui {
class BookmarkWidget;
}

class BookmarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkWidget(BookmarkManager *bookmarkManager, QWidget *parent = nullptr);
    ~BookmarkWidget();

signals:
    void requestReturn();

public slots:
    void updateBookmarkList();

private slots:
    void onAddBookmark();
    void onRemoveBookmark();
    void onClearAll();

private:
    Ui::BookmarkWidget *ui;

    BookmarkManager *m_bookmarkManager;
    QListWidget *bookmarkList;
    QComboBox *buildingComboBox;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;
    QPushButton *returnButton;
};

#endif // BOOKMARKWIDGET_H
