#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QTimer>
#include <QRandomGenerator>
#include "logic.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief maxSize размер массива для сортировки
     * @brief maxValue Максимальное значение в массиве
     * @brief splitter Разделитель соотношения количества элементов к количеству столбиков диаграммы
     * @brief updateTime время в миллисекундах, за которое будет производиться обновление столбиков
     * @brief maxPresentableSize количество столбиков диаграммы, расчитывается исходя из максимального количества и разделителя
     */
    int maxSize = 5000;
    int maxValue = 3000;
    int splitter = 10;
    int updateTime = 1000;
    int maxPresentableSize = maxSize / splitter;
    /**
     * @brief set Множество для диграммы
     */
    QBarSet* set;
    /**
     * @brief array массив-испытуемый
     */
    QList<qint32>* array;
    /**
     * @brief series ряд для диаграммы
     */
    QBarSeries *series;
    /**
     * @brief chart график
     */
    QChart* chart;
    /**
     * @brief axisX ось х
     */
    QValueAxis* axisX;
    /**
     * @brief axisY ось у
     */
    QValueAxis* axisY;
    /**
     * @brief chartView вью для графика
     */
    QChartView* chartView;
    /**
     * @brief t таймер для обновления
     */
    QTimer* t;
    /**
     * @brief thread_1 потог
     */
    QThread thread_1;
    /**
     * @brief sortMachina экземлпяр исполнителя сортировки
     */
    Logic sortMachina;
    ~MainWindow();

public slots:
    /**
     * @brief setUp слот начальной конфигурации программы
     */
    void setUp();
    /**
     * @brief genRandomValues заполняем массив случайным бредом
     */
    void genRandomValues();
    /**
     * @brief fullUpSet передача в множество с последующим соотношением столбик-элементы
     */
    void fullUpSet();
    /**
     * @brief onStartClicked запуск шайтан-машины
     */
    void onStartClicked();
    /**
     * @brief onStopClicked остановка
     */
    void onStopClicked();
    /**
     * @brief refreshArray слот обновления массива, полученного от объекта Logic
     * @param arr
     */
    void refreshArray(QList<qint32>* arr);
    /**
     * @brief slotTimerAlarm слот для сигнала готовности таймера
     */
    void slotTimerAlarm();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
