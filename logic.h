#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QDebug>

class Logic : public QObject
{
    Q_OBJECT
    /// какое-то свойство для того, чтоб всё работало
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    /**
     * @brief m_running состояние потока
     */
    bool m_running;
    /**
     * @brief A копия массива-испытуемого
     */
    QList<qint32> A;
public:
    explicit Logic(QObject *parent = 0);
    /**
     * @brief running функция для определения состояния
     * @return возвращает состояние потока
     */
    bool running() const;
signals:
    /**
     * @brief finished сигнал естественного завершения потока
     */
    void finished();
    /**
     * @brief runningChanged сигнал изменения состояния
     * @param running состояние
     */
    void runningChanged(bool running);
    /**
     * @brief returnArray вернуть массив к MainWindow
     * @param array массив
     */
    void returnArray(QList<qint32>* array);
public slots:
    /**
     * @brief run полезный метод, в данном случае метод с сортировкой
     */
    void run();
    /**
     * @brief setRunning установить состояние
     * @param running состояние
     */
    void setRunning(bool running);
    /**
     * @brief giveArray функция забора массива из вне
     * @param arr сам массив
     */
    void giveArray(QList<qint32>* arr);
};

#endif // LOGIC_H
