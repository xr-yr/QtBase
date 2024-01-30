#ifndef CALC_H
#define CALC_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QGridLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

class Calc : public QWidget {
Q_OBJECT

public:
    explicit Calc(QWidget *parent = nullptr);

    ~Calc() override;

    const static QVector<QString> numsBtn;
    const static QVector<QString> cmdLines;
    const static QVector<QString> cmdOps;

public slots:

    void pressNumBtn();

    void pressOpBtn();

    void pressLineBtn();

private:
    Ui::Calc *ui;
    static QString buf;

private:

    void setText();

    double toNums();

    void defQString();

    void acQString();

    void percent();
};


#endif //CALC_H
