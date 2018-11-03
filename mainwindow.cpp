#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mproblem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new QWidget(), "Data");
    ui->tabWidget->addTab(new QWidget(), "Graph");
    ui->tabWidget->addTab(new QWidget(), "Graph");
    ui->tabWidget->addTab(new QWidget(), "Graph");
    ui->tabWidget->addTab(new QWidget(), "Graph");
    ui->tabWidget->addTab(new QWidget(), "Graph");
    ui->actionExit = new QAction(tr("&Exit"), this);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_Exit_clicked);
    on_Solve_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    return;
}

void MainWindow::on_Solve_clicked()
{
    QString str1 = ui->lineEdit->text(), str2 = ui->lineEdit_2->text();
    QString str3 = ui->lineEdit_3->text(), str4 = ui->lineEdit_4->text();
    long double x0 = static_cast<LD>(str1.toDouble()), y0 = static_cast<LD>(str2.toDouble()),
            h = static_cast<LD>(str3.toDouble()), X = static_cast<LD>(str4.toDouble());

    vector<vector<pair<LD, LD> > > t = solve(x0, y0, h, X);
    series0 = new QLineSeries();
    series1 = new QLineSeries();
    series2 = new QLineSeries();
    series3 = new QLineSeries();
    series4 = new QLineSeries();
    series00 = new QLineSeries(); series00->setName("Exact");
    series01 = new QLineSeries(); series01->setName("Euler's method");
    series02 = new QLineSeries(); series02->setName("Improved Euler's method");
    series03 = new QLineSeries(); series03->setName("Runga-Kutta");
    for(size_t i = 0;i < t[2].size();i ++){
        series0->append(static_cast<qreal>(t[0][i]._1), static_cast<qreal>(t[0][i]._2));
        series1->append(static_cast<qreal>(t[2][i]._1), static_cast<qreal>(t[2][i]._2));
        series2->append(static_cast<qreal>(t[3][i]._1), static_cast<qreal>(t[3][i]._2));
        series3->append(static_cast<qreal>(t[4][i]._1), static_cast<qreal>(t[4][i]._2));
        series00->append(static_cast<qreal>(t[0][i]._1), static_cast<qreal>(t[0][i]._2));
        series01->append(static_cast<qreal>(t[2][i]._1), static_cast<qreal>(t[2][i]._2));
        series02->append(static_cast<qreal>(t[3][i]._1), static_cast<qreal>(t[3][i]._2));
        series03->append(static_cast<qreal>(t[4][i]._1), static_cast<qreal>(t[4][i]._2));
        series4->append(static_cast<qreal>(t[4][i]._1), static_cast<qreal>(t[4][i]._2));
    }
    {
        chart0 = new QChart();
        chart0->legend()->hide();
        chart0->addSeries(series0);
        chart0->setTitle("Exact solution for -x-y function");
        chart0->setTheme(QChart::ChartThemeDark);
    }

    {
        chart1 = new QChart();
        chart1->legend()->hide();
        chart1->addSeries(series1);
        chart1->setTitle("Euler\'s method for -x-y function");
        chart1->setTheme(QChart::ChartThemeDark);
    }

    {
        chart2 = new QChart();
        chart2->legend()->hide();
        chart2->addSeries(series2);
        chart2->setTitle("Improved Euler\'s method for -x-y function");
        chart2->setTheme(QChart::ChartThemeDark);
    }

    {
        chart3 = new QChart();
        chart3->legend()->hide();
        chart3->addSeries(series3);
        chart3->setTitle("Runga-Kutta\'s method for -x-y function");
        chart3->setTheme(QChart::ChartThemeDark);
    }

    {
        chart4 = new QChart();
        chart4->legend()->attachToChart();

        //chart4->legend()->hide();
        chart4->addSeries(series00);
        chart4->addSeries(series01);
        chart4->addSeries(series02);
        chart4->addSeries(series03);
        chart4->setTitle("Comparing the results");
        chart4->setTheme(QChart::ChartThemeDark);
    }
    table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(static_cast<int>(t[2].size()));
    //QPalette pal = table->palette();
    //pal.setColor(QPalette::Background, Qt::red);
    //table->setPalette(pal);
    //table->setAutoFillBackground(true);
    //pal = table->horizontalHeader()->palette();
    //pal.setColor(table->horizontalHeader()->backgroundRole(), Qt::red);
    //table->horizontalHeader()->setPalette(pal);
    //table->setStyleSheet("QTableWidget{background-color: #1c222e;}");zz
    QStringList strlist;
    strlist.append("x");
    strlist.append("Exact");
    strlist.append("Euler");
    strlist.append("Improved Euler");
    strlist.append("Runga-Kutta");
    table->setHorizontalHeaderLabels(strlist);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LD minY0{y0}, maxY0{y0}, minY1{y0}, maxY1{y0}, minY2{y0}, maxY2{y0}, minY3{y0}, maxY3{y0};
    for(size_t i{0};i < t[2].size();i ++){
        stringstream ss;
        string x, y0, y1, y2, y3;
        x = to_string(t[2][i]._1);
        y0 = to_string(t[0][i]._2);
        y1 = to_string(t[2][i]._2);
        y2 = to_string(t[3][i]._2);
        y3 = to_string(t[4][i]._2);
        minY0 = fmin(minY0, t[0][i]._2); maxY0 = fmax(maxY0, t[0][i]._2);
        minY1 = fmin(minY1, t[2][i]._2); maxY1 = fmax(maxY1, t[2][i]._2);
        minY2 = fmin(minY2, t[3][i]._2); maxY2 = fmax(maxY2, t[3][i]._2);
        minY3 = fmin(minY3, t[4][i]._2); maxY3 = fmax(maxY3, t[4][i]._2);
        QString xx = QString::fromStdString(x),
               yy0 = QString::fromStdString(y0),
               yy1 = QString::fromStdString(y1),
               yy2 = QString::fromStdString(y2),
               yy3 = QString::fromStdString(y3);

        table->setItem(static_cast<int>(i), 0, new QTableWidgetItem(xx));
        table->setItem(static_cast<int>(i), 1, new QTableWidgetItem(yy0));
        table->setItem(static_cast<int>(i), 2, new QTableWidgetItem(yy1));
        table->setItem(static_cast<int>(i), 3, new QTableWidgetItem(yy2));
        table->setItem(static_cast<int>(i), 4, new QTableWidgetItem(yy3));
    }
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int numberOfTicks = static_cast<int>((X - x0) / static_cast<LD>(h) + 0.0001L) + 1;
    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY0), static_cast<qreal>(maxY0));
        yAxis->setTickCount(numberOfTicks);
        chart0->setAxisX(xAxis, series0);
        chart0->setAxisY(yAxis, series0);
        chartView0 = new QChartView(chart0);
        chartView0->setRubberBand(QChartView::HorizontalRubberBand);
        chartView0->setRubberBand(QChartView::VerticalRubberBand);
        chartView0->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY1), static_cast<qreal>(maxY1));
        yAxis->setTickCount(numberOfTicks);
        chart1->setAxisX(xAxis, series1);
        chart1->setAxisY(yAxis, series1);
        chartView1 = new QChartView(chart1);
        chartView1->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY2), static_cast<qreal>(maxY2));
        yAxis->setTickCount(numberOfTicks);
        chart2->setAxisX(xAxis, series2);
        chart2->setAxisY(yAxis, series2);
        chartView2 = new QChartView(chart2);
        chartView2->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY3), static_cast<qreal>(maxY3));
        yAxis->setTickCount(numberOfTicks);
        chart3->setAxisX(xAxis, series3);
        chart3->setAxisY(yAxis, series3);
        chartView3 = new QChartView(chart3);
        chartView3->setRenderHint(QPainter::Antialiasing);
    }
    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY0), static_cast<qreal>(maxY0));
        yAxis->setTickCount(numberOfTicks);
        chart4->addAxis(xAxis, Qt::AlignBottom);
        chart4->addAxis(yAxis, Qt::AlignLeft);
        series4->attachAxis(xAxis);
        series4->attachAxis(yAxis);
        chartView4 = new QChartView(chart4);
        chartView4->setRenderHint(QPainter::Antialiasing);
    }
    const int nColumn = 6;
    for(int i{};i < nColumn;i ++){
        ui->tabWidget->removeTab(0);
    }

    ui->tabWidget->addTab(table, "Data");
    ui->tabWidget->addTab(chartView0, "Exact");
    ui->tabWidget->addTab(chartView1, "Euler");
    ui->tabWidget->addTab(chartView2, "Improved Euler");
    ui->tabWidget->addTab(chartView3, "Runga-Kutta");
    ui->tabWidget->addTab(chartView4, "Compare");
    something();
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}

void MainWindow::something(){
    QPointF x = chartView0->mapToScene(chartView0->pos());
    chart0->mapFromScene(x);
    QPointF pos = chart0->mapToValue(chart0->pos(), chart0->series().back());
    cerr << pos.x() << " " << pos.y();
}
