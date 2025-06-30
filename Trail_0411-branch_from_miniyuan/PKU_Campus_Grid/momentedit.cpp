#include "momentedit.h"
#include "ui_momentedit.h"
#include "languagemanager.h"

#include <QDir>
#include <QString>

// 朋友圈功能

MomentEdit::MomentEdit(const QPointF &location, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MomentEdit)
    , m_location(location)
{
    ui->setupUi(this);

    // 引入翻译管理器
    auto *langManager = LanguageManager::instance();

    setWindowTitle(tr("发布动态"));
    setFixedSize(500, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 位置信息
    m_locationLabel = langManager->createTranslatableLabel("MomentEdit", QString(tr("位置: (%1, %2)")).arg(location.x()).arg(location.y()), this);
    m_locationLabel->setStyleSheet("font-weight: bold;");
    mainLayout->addWidget(m_locationLabel);

    // 文本编辑框
    m_textEdit = new QTextEdit(this);
    m_textEdit->setPlaceholderText(tr("分享你的感受..."));
    m_textEdit->setMinimumHeight(100);
    mainLayout->addWidget(m_textEdit);

    // 图片显示区域
    m_imageLabel = langManager->createTranslatableLabel("MomentEdit", tr("点击下方按钮添加图片"), this);
    m_imageLabel->setFixedSize(300, 200);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setStyleSheet("border: 1px solid #ccc;");
    mainLayout->addWidget(m_imageLabel, 0, Qt::AlignHCenter);

    // 选择图片按钮
    m_selectImageBtn = langManager->createTranslatablePushButton("MomentEdit", tr("选择图片"), this);
    connect(m_selectImageBtn, &QPushButton::clicked, this, &MomentEdit::onSelectImage);
    mainLayout->addWidget(m_selectImageBtn, 0, Qt::AlignHCenter);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_saveBtn = langManager->createTranslatablePushButton("MomentEdit", tr("发布"), this);
    m_cancelBtn = langManager->createTranslatablePushButton("MomentEdit", tr("取消"), this);
    buttonLayout->addWidget(m_saveBtn);
    buttonLayout->addWidget(m_cancelBtn);
    mainLayout->addLayout(buttonLayout);

    connect(m_saveBtn, &QPushButton::clicked, this, &MomentEdit::onSave);
    connect(m_cancelBtn, &QPushButton::clicked, this, &MomentEdit::onCancel);

}

MomentEdit::~MomentEdit()
{
    delete ui;
}

void MomentEdit::onSelectImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("选择图片"), "", tr("图片文件 (*.png *.jpg *.jpeg)"));
    if (!filename.isEmpty()) {
        m_imagePath = filename;
        QPixmap pixmap(filename);
        if (!pixmap.isNull()) {
            m_imageLabel->setPixmap(pixmap.scaled(m_imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            QMessageBox::warning(this, tr("错误"), tr("无法加载图片！"));
        }
    }
}

void MomentEdit::onSave()
{
    QString text = m_textEdit->toPlainText().trimmed();
    if (text.isEmpty() && m_imagePath.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("内容不能为空！"));
        return;
    }

    // 创建动态图片
    createMomentImage();

    if (!m_momentPath.isEmpty()) {
        // 保存成功，发送信号
        emit momentSaved(m_momentPath, m_location);
        accept();
    } else {
        QMessageBox::critical(this, tr("错误"), tr("保存动态失败！"));
    }
}

void MomentEdit::onCancel()
{
    reject();
}

void MomentEdit::createMomentImage()
{
    // 创建目标目录（如果不存在）
    QDir dir("moments");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // 生成唯一文件名
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz");
    m_momentPath = dir.filePath(timestamp + ".png");

    // 创建动态图片
    QPixmap result(800, 600); // 动态图片尺寸
    result.fill(Qt::white);   // 背景填充白色

    QPainter painter(&result);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制标题
    QFont titleFont = painter.font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.setPen(Qt::darkBlue);
    painter.drawText(QRect(50, 50, 700, 100), Qt::AlignCenter, tr("校园动态"));

    // 绘制位置信息
    QFont locationFont = painter.font();
    locationFont.setPointSize(14);
    painter.setFont(locationFont);
    painter.setPen(Qt::darkGray);
    painter.drawText(QRect(50, 150, 700, 50), Qt::AlignCenter,
                     QString(tr("发布于位置: (%1, %2)")).arg(m_location.x()).arg(m_location.y()));

    // 绘制用户内容
    QFont contentFont = painter.font();
    contentFont.setPointSize(18);
    painter.setFont(contentFont);
    painter.setPen(Qt::black);
    painter.drawText(QRect(100, 200, 600, 200), Qt::TextWordWrap, m_textEdit->toPlainText());

    // 绘制用户图片（如果有）
    if (!m_imagePath.isEmpty()) {
        QPixmap userImage(m_imagePath);
        if (!userImage.isNull()) {
            // 缩放图片以适应空间
            QPixmap scaledImage = userImage.scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(200, 400, scaledImage);
        }
    }

    // 绘制底部信息
    painter.setFont(locationFont);
    painter.setPen(Qt::darkGray);
    painter.drawText(QRect(50, 550, 700, 50), Qt::AlignRight,
                     QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    // 保存图片
    if (!result.save(m_momentPath)) {
        m_momentPath = "";
    }
}
