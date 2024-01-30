#ifndef WIN_H
#define WIN_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include "Person.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Win; }
QT_END_NAMESPACE

class Win : public QWidget {
Q_OBJECT

public:
    explicit Win(QWidget *parent = nullptr);

    ~Win() override;

public slots:
    void on_btnStart_clicked();

private:
    Ui::Win *ui;
    Person *p1;
};


#endif //WIN_H
