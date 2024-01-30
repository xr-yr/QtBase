#include "sortThread.h"
#include <QDateTime>

GenerateDataThread::GenerateDataThread(QObject *parent, int countNum, int maxNum, int minNum)
        : QThread(parent), m_num(countNum), m_max(maxNum), m_min(minNum) {
    qRegisterMetaType<QVector<int>>("QVector<int>");
    randGenerator = new QRandomGenerator(QDateTime::currentSecsSinceEpoch());
    randGenerator->bounded(m_min, m_max + 1);
}

GenerateDataThread::~GenerateDataThread() {
    delete randGenerator;
}

void GenerateDataThread::run() {
    src_data.reserve(m_num);
    for (int i = 0; i < m_num; ++i) {
        src_data.push_back(randGenerator->bounded(m_min, m_max + 1));
    }
    emit dataReady(src_data);
}

SortThread::SortThread(QString sort_name, const QVector<int> *src_data, QObject *parent)
        : sortName(std::move(sort_name)), srcData(src_data), QThread(parent) {
}

void SortThread::run() {
    if (sortName == QuickSortName) {
        quickSort();
    } else if (sortName == BubbleSortName) {
        bubbleSort();
    }
    emit dataReady(data);
}

void SortThread::bubbleSort() {
    data = *srcData;
    int n = data.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (data[i] > data[j]) {
                std::swap(data[i], data[j]);
            }
        }
    }
}

static ssize_t partitionSingle(QVector<int> &data, ssize_t startIndex, ssize_t endIndex) {
    int tmpValue = data[startIndex];
    ssize_t mark = startIndex;

    for (ssize_t i = startIndex + 1; i <= endIndex; ++i) {
        if (data[i] < tmpValue) {
            mark++;
            std::swap(data[mark], data[i]);
        }
    }
    std::swap(data[mark], data[startIndex]);
    return mark;
}

static void singleQuickSort(QVector<int> &data, ssize_t startIndex, ssize_t endIndex) {
    if (startIndex >= endIndex) {
        return;
    }
    // 得到基准元素位置
    ssize_t pivot = partitionSingle(data, startIndex, endIndex);
    singleQuickSort(data, startIndex, pivot - 1);
    singleQuickSort(data, pivot + 1, endIndex);
}

void SortThread::quickSort() {
    data = *srcData;
    singleQuickSort(data, 0, data.size() - 1);
}
