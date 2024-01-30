#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QSettings>
#include <QLabel>
#include <opencv2/opencv.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class ImageWidget; }
QT_END_NAMESPACE

class ImageWidget : public QWidget {
Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);

    ~ImageWidget() override;

    static QImage imageCenter(const QImage &qImage, QLabel *qLabel);    // 图像居中显示

    static void showImageCenter(cv::Mat &resultArray, QLabel *label);    // 将cv的BGR数据显示在UI的Label标签处

private:
    // 将窗口设置为随着窗口变化而变化
    void resizeEvent(QResizeEvent *event) override;

public slots:

    void on_btnLoad_clicked();

    void grayImage();

    void meanImage();

    void edgeImage();

private:
    Ui::ImageWidget *ui;
    QString m_lastPath;         // 上次打开文件路径信息
    QSettings *m_pIniSet;       // 配置文件
    const QString CONFIG_PATH_NAME = "/config/Setting.ini";
    cv::Mat m_srcImage;         // OpenCV处理的图像数据
};


#endif //IMAGE_WIDGET_H
