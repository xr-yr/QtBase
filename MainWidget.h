#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>

class MainWidget : public QWidget {
public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget() override;

public slots:

    void openSigSlot();

    void openCalc();

    void openImage();

    void openThread();

    void openServer();

    void openClient();

    void openDefault();

private:
    QPushButton **btn;
    int countBtn;
};

#endif //MAIN_WIDGET_H
