#include "Person.h"

Person::Person(QObject *parent) : QObject(parent) {

}

Person::~Person() = default;

House::House(QObject *parent) : QObject(parent), count(0) {

}

House::~House() = default;

void House::doCook() {
    qDebug() << "做默认菜单";
}

void House::doCook(const QString &food) {
    qDebug() << "做" << food;
}
