#ifndef MOMENTEDIT_H
#define MOMENTEDIT_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QDateTime>
#include <QPointF>

// 朋友圈功能

namespace Ui {
class MomentEdit;
}

class MomentEdit : public QDialog
{
    Q_OBJECT

public:
    explicit MomentEdit(const QPointF &location, QWidget *parent = nullptr);
    ~MomentEdit();

signals:
    void momentSaved(const QString &imagePath, const QPointF &location);

private slots:
    void onSelectImage();
    void onSave();
    void onCancel();

private:
    Ui::MomentEdit *ui;
    QPointF m_location; // 记录发布动态的位置
    QTextEdit *m_textEdit;
    QLabel *m_imageLabel;
    QLabel *m_locationLabel;
    QPushButton *m_selectImageBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_cancelBtn;
    QString m_imagePath; // 用户选择的图片路径
    QString m_momentPath; // 生成的动态图片路径

    void createMomentImage();
};

#endif // MOMENTEDIT_H
