#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setUp();
    // Запуск выполнения метода run будет осуществляться по сигналу запуска от соответствующего потока
    connect(&thread_1, &QThread::started, &sortMachina, &Logic::run);
//    connect(&thread_2, &QThread::started, &Logic_2, &Logic::run);
    // Остановка потока же будет выполняться по сигналу finished от соответствующего объекта в потоке
    connect(&sortMachina, &Logic::finished, &thread_1, &QThread::terminate);
//    connect(&Logic_2, &Logic::finished, &thread_2, &QThread::terminate);
    // коннект для передачи данных из первого объекта в первом потоке, ко второму объекту во втором потоке
//    connect(&sortMachina, &Logic::sendMessage, &Logic_2, &Logic::setMessage_2, Qt::DirectConnection);

//    connect(this->ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_write_1Clicked);
//    connect(this->ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_write_2Clicked);
    connect(this->ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(this->ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(&sortMachina, &Logic::returnArray, this, &MainWindow::refreshArray);

    sortMachina.moveToThread(&thread_1);    // Передаём объекты в соответствующие потоки
//    Logic_2.moveToThread(&thread_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUp()
{
    ui->setupUi(this);

    this->set = new QBarSet("Numbers");
    this->array = new QList<qint32>();

    genRandomValues();
    fullUpSet();

    this->series = new QBarSeries();
    series->append(set);

    this->chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Bubble sort");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    this->axisX = new QValueAxis();
    axisX->setRange(0, this->maxPresentableSize);
    chart->addAxis(axisX, Qt::AlignBottom);

    series->attachAxis(axisX);

    this->axisY = new QValueAxis();
    axisY->setRange(0, maxValue);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    this->chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(chartView, 0, 0);
    this->ui->widget->setLayout(grid);

    this->t = new QTimer();
    connect(t, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

void MainWindow::genRandomValues()
{
    QRandomGenerator *gen = new QRandomGenerator();
    for (int i = 0; i < this->maxSize; i++) {
        qint32 num = gen->bounded(0, maxValue);
//        qDebug() << num;
        this->array->push_back(num);
    }
}

void MainWindow::fullUpSet()
{
    int j = 0;
    for (int i = 0; i < this->maxSize; i++) {
        if (i % splitter == 0) {
            this->set->insert(j, array->at(i));
            j++;
        }
    }
}

//void MainWindow::on_write_1Clicked()
//{
//    // Устанавливаем текст в первый объект в первом потоке
//    sortMachina.setMessage(ui->lineEdit_1->text());
//}


void MainWindow::onStartClicked()
{
    // Запуск потоков
    sortMachina.setRunning(true);
    sortMachina.giveArray(this->array);
//    Logic_2.setRunning(true);
    thread_1.start();
//    thread_2.start();
    this->t->start(updateTime); // И запустим таймер
}

void MainWindow::onStopClicked()
{
    // Остановка потоков через завершение выполнения методов run в объектах
    sortMachina.setRunning(false);
    thread_1.terminate();
    this->t->stop();
    //    Logic_2.setRunning(false);
}

void MainWindow::refreshArray(QList<qint32> *arr)
{
    this->array = arr;
    qDebug() << arr;
    fullUpSet();
}

void MainWindow::slotTimerAlarm()
{
    sortMachina.setRunning(false);
    thread_1.terminate();

    t->start(updateTime);

    sortMachina.setRunning(true);
    sortMachina.giveArray(this->array);
//    Logic_2.setRunning(true);
    thread_1.start();
}
