#ifndef SIGNAL_BASE_WIDGET_H
#define SIGNAL_BASE_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QThread>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class SignalBaseWidget; }
QT_END_NAMESPACE

class SignalBaseWidget : public QWidget {
Q_OBJECT

public:
    explicit SignalBaseWidget(QWidget *parent = nullptr);

    ~SignalBaseWidget() override;

public slots:

    void pressMakeBtn();

    void dataReady(const QVector<int> &data);

    void pressBubbleBtn();

    void bubbleSortReady(const QVector<int> &data);

    void pressQuickBtn();

    void quickSortReady(const QVector<int> &data);

private:
    Ui::SignalBaseWidget *ui;
    QVector<int> src_data;
    int maxNum;
    int minNum;
    int countNum;

private:
    void checkNum();
};

#endif //SIGNAL_BASE_WIDGET_H
