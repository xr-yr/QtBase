#ifndef SORT_THREAD_H
#define SORT_THREAD_H

#include <QThread>
#include <QVector>
#include <QRandomGenerator>

class GenerateDataThread : public QThread {
Q_OBJECT
public:
    explicit GenerateDataThread(QObject *parent = nullptr, int countNum = 10, int maxNum = 100, int minNum = 1);

    ~GenerateDataThread() override;

protected:
    void run() override;

signals:

    void dataReady(const QVector<int> &data);

private:
    QRandomGenerator *randGenerator;
    QVector<int> src_data;
    int m_num;
    int m_max;
    int m_min;
};

class SortThread : public QThread {
Q_OBJECT
public:
    explicit SortThread(QString sort_name, const QVector<int> *src_data = nullptr, QObject *parent = nullptr);

    ~SortThread() override = default;

protected:
    void run() override;

signals:

    void dataReady(const QVector<int> &data);

private:
    QVector<int> data;
    const QVector<int> *srcData;
    QString sortName;

public:
    static constexpr char BubbleSortName[] = "BubbleSort";
    static constexpr char QuickSortName[] = "QuickSort";

private:
    void bubbleSort();

    void quickSort();
};

#endif //SORT_THREAD_H
