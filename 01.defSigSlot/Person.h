#ifndef PERSON_H
#define PERSON_H

/* 自定义一个处理类，这个类要有自己的信号和槽
 * 自定义信号流程：
 *      1. 在类中，最开始引入Q_OBJECT宏
 * */

#include <QObject>
#include <QDebug>
#include <QString>

class Person : public QObject {
Q_OBJECT

public:
    explicit Person(QObject *parent = nullptr);

    ~Person() override;

signals:

    void eat();

    void eat(const QString &food);

};

class House : public QObject {
Q_OBJECT

public:
    explicit House(QObject *parent = nullptr);

    ~House() override;

public slots:

    void doCook();

    void doCook(const QString &food);

private:
    int count;
};

#endif //PERSON_H
