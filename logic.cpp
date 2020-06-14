#include "logic.h"

Logic::Logic(QObject *parent) :
        QObject(parent)
{

}

bool Logic::running() const
{
    return m_running;
}

// Самый важный метод, в котором будет выполняться "полезная" работа объекта
void Logic::run()
{
    for(int i = 0; i < A.size() - 1; i++) {
        for(int j = 0; j < A.size() - i - 1; j++) {
            if (A[j] > A[j+1]) {
                A.swapItemsAt(j, j+1);
            }
            qDebug() << "Looking at " << A.at(j) << A.at(j+1);
            if (!m_running) {
                qDebug() << "Stopped";
                emit returnArray(&A);
                return;
            }
        }
    }
    emit returnArray(&A);
    qDebug() << "Finished";
    emit finished();
}

void Logic::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}


void Logic::giveArray(QList<qint32>* arr)
{
    this->A = *arr;
}
