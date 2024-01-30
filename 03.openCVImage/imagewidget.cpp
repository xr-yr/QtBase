// You may need to build the project (run Qt uic code generator) to get "ui_ImageWidget.h" resolved

#include "imagewidget.h"
#include "ui_ImageWidget.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QPixmap>


ImageWidget::ImageWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ImageWidget) {
    ui->setupUi(this);

    auto config_path = qApp->applicationDirPath() + CONFIG_PATH_NAME;
    m_pIniSet = new QSettings(config_path, QSettings::IniFormat, this);
    m_lastPath = m_pIniSet->value("/LastPath/path").toString();
    if (m_lastPath.isEmpty()) {
        // 若没有上传文件路径，则使用Windows系统默认图片路径
        m_lastPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    }

    connect(ui->btnGray, &QPushButton::clicked, this, &ImageWidget::grayImage);
    connect(ui->btnEdge, &QPushButton::clicked, this, &ImageWidget::edgeImage);
    connect(ui->btnMean, &QPushButton::clicked, this, &ImageWidget::meanImage);
}

ImageWidget::~ImageWidget() {
    delete ui;
}

void ImageWidget::on_btnLoad_clicked() {
    // 获取Windows系统默认图片路径
    // const QString &localPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    // 通过QFileDialog对话框选取图片
    const QString &fileName = QFileDialog::getOpenFileName(this, "加载图片", m_lastPath,
                                                           tr("Image (*.png *.jpeg *.jpg)"));
    if (fileName.isEmpty()) {
        return;
    }

    ui->PathEdit->setText(fileName);

    // 将选择图片去掉文件名，保留路径信息，保存到ini文件
    auto end = fileName.lastIndexOf("/");
    auto path = fileName.left(end);
    // 回写路径信息
    m_pIniSet->setValue("LastPath/path", path);
    m_pIniSet->sync();

    // Qt显示图片
    // QPixmap img(fileName);
    // ui->rawLabel->setPixmap(img);

    m_srcImage = cv::imread(fileName.toLocal8Bit().toStdString());
    showImageCenter(m_srcImage, ui->rawLabel);
}

/* 修正qImage实现适应qLabel的大小缩放 */
QImage ImageWidget::imageCenter(const QImage &qImage, QLabel *qLabel) {
    QImage image;
    QSize imageSize = qImage.size();
    QSize labelSize = qLabel->size();
    double dWidthRatio = 1.0 * imageSize.width() / labelSize.width();
    double dHeightRatio = 1.0 * imageSize.height() / labelSize.height();
    if (dWidthRatio > dHeightRatio) {
        image = qImage.scaledToWidth(labelSize.width());
    } else {
        image = qImage.scaledToHeight(labelSize.height());
    }
    return image;
}

void ImageWidget::showImageCenter(cv::Mat &resultArray, QLabel *label) {
    const QImage &image = QImage(resultArray.data,
                                 resultArray.cols, resultArray.rows,
                                 resultArray.channels() * resultArray.cols,
                                 QImage::Format_BGR888);
    const QImage &img = imageCenter(image, label);
    label->setPixmap(QPixmap::fromImage(img));
}

/* 对原始图片数据进行灰度处理 */
void ImageWidget::grayImage() {
    if (m_srcImage.empty()) {
        return;
    }
    cv::Mat resultImg;
    cv::cvtColor(m_srcImage, resultImg, cv::COLOR_BGR2GRAY);
    // 由于QImage需要的是RGB三元组，灰度值只有1个分量，需要进行灰度转为3个通道
    cv::cvtColor(resultImg, resultImg, cv::COLOR_GRAY2BGR);
    showImageCenter(resultImg, ui->imgLabel);
}

void ImageWidget::meanImage() {
    if (m_srcImage.empty()) {
        return;
    }
    cv::Mat blurImg;
    cv::blur(m_srcImage, blurImg, cv::Size(4, 4));
    auto displayImg = QImage(blurImg.data, blurImg.cols, blurImg.rows,
                             blurImg.channels() * blurImg.cols, QImage::Format_BGR888);

    const QImage &img = imageCenter(displayImg, ui->imgLabel);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageWidget::edgeImage() {
    if (m_srcImage.empty()) {
        return;
    }
    // 边缘检测先要转换为灰度图
    cv::Mat edgeImage, grayImage;
    cv::cvtColor(m_srcImage, grayImage, cv::COLOR_BGR2GRAY);
#if 0
    // 1. 调用canny边缘检测函数
    cv::Canny(grayImage, edgeImage, 200, 1);
#endif
#if 0
    // 2. 来普拉斯
    cv::Laplacian(grayImage, edgeImage, grayImage.depth());
#endif
#if 1
    // 3. 使用sobel 基于像素点的 x y方向检测
    cv::Mat sobel_x, sobel_y;
    // 计算x y方向的边缘检测
    cv::Sobel(grayImage, sobel_x, CV_8U, 1, 0);
    cv::Sobel(grayImage, sobel_y, CV_8U, 0, 1);
    // 把x y方向进行加权平均法
    cv::addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, edgeImage);
#endif
    cv::cvtColor(edgeImage, edgeImage, cv::COLOR_GRAY2BGR);
    showImageCenter(edgeImage, ui->imgLabel);
}

void ImageWidget::resizeEvent(QResizeEvent *event) {
    if (m_srcImage.empty()) {
        return;
    }
    showImageCenter(m_srcImage, ui->rawLabel);
    if (!ui->imgLabel->pixmap()) {
        return;
    }
    const QImage &img = imageCenter(ui->imgLabel->pixmap()->toImage(), ui->imgLabel);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img));
}
