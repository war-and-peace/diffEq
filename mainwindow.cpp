#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mproblem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i{};i < nCount;i ++)
        ui->tabWidget->addTab(new QWidget(), "Data");
    msg = new QMessageBox();
    //About message to be written
    msg->setText("Something to be written here soon...");
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_Exit_clicked);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_About_clicked);
    on_Solve_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    series5 = new QLineSeries();
    series6 = new QLineSeries();
    series7 = new QLineSeries();
    series8 = new QLineSeries();
    series9 = new QLineSeries();
    series10 = new QLineSeries();

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
        series5->append(static_cast<qreal>(t[5][i]._1), static_cast<qreal>(t[5][i]._2));
        series6->append(static_cast<qreal>(t[6][i]._1), static_cast<qreal>(t[6][i]._2));
        series7->append(static_cast<qreal>(t[7][i]._1), static_cast<qreal>(t[7][i]._2));
        series8->append(static_cast<qreal>(t[8][i]._1), static_cast<qreal>(t[8][i]._2));
        series9->append(static_cast<qreal>(t[9][i]._1), static_cast<qreal>(t[9][i]._2));
        series10->append(static_cast<qreal>(t[10][i]._1), static_cast<qreal>(t[10][i]._2));
    }
    {
        chart0 = new QChart();
        chart0->legend()->hide();
        chart0->addSeries(series0);
        chart0->setTitle("Exact solution for y'=-x-y function");
        chart0->setTheme(QChart::ChartThemeDark);
    }

    {
        chart1 = new QChart();
        chart1->legend()->hide();
        chart1->addSeries(series1);
        chart1->setTitle("Euler\'s method for y'=-x-y function");
        chart1->setTheme(QChart::ChartThemeDark);
    }

    {
        chart2 = new QChart();
        chart2->legend()->hide();
        chart2->addSeries(series2);
        chart2->setTitle("Improved Euler\'s method for y'=-x-y function");
        chart2->setTheme(QChart::ChartThemeDark);
    }

    {
        chart3 = new QChart();
        chart3->legend()->hide();
        chart3->addSeries(series3);
        chart3->setTitle("Runga-Kutta\'s method for y'=-x-y function");
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

    {
        chart5 = new QChart();
        chart5->legend()->hide();
        chart5->addSeries(series5);
        chart5->setTitle("Error function for Euler`s method");
        chart5->setTheme(QChart::ChartThemeDark);
    }

    {
        chart6 = new QChart();
        chart6->legend()->hide();
        chart6->addSeries(series6);
        chart6->setTitle("Error function for Euler`s improved method");
        chart6->setTheme(QChart::ChartThemeDark);
    }

    {
        chart7 = new QChart();
        chart7->legend()->hide();
        chart7->addSeries(series7);
        chart7->setTitle("Error function for Runga-Kutta method");
        chart7->setTheme(QChart::ChartThemeDark);
    }

    {
        chart8 = new QChart();
        chart8->legend()->hide();
        chart8->addSeries(series8);
        chart8->setTitle("Error for euler method with different step(h)");
        chart8->setTheme(QChart::ChartThemeDark);
    }

    {
        chart9 = new QChart();
        chart9->legend()->hide();
        chart9->addSeries(series9);
        chart9->setTitle("Error for improved euler method with different step(h)");
        chart9->setTheme(QChart::ChartThemeDark);
    }

    {
        chart10 = new QChart();
        chart10->legend()->hide();
        chart10->addSeries(series10);
        chart10->setTitle("Error for runga-kutta method with different step(h)");
        chart10->setTheme(QChart::ChartThemeDark);
    }

    table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(static_cast<int>(t[2].size()));

    QStringList strlist;
    strlist.append("x");
    strlist.append("Exact");
    strlist.append("Euler");
    strlist.append("Improved Euler");
    strlist.append("Runga-Kutta");
    table->setHorizontalHeaderLabels(strlist);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LD minY0{y0}, maxY0{y0}, minY1{y0}, maxY1{y0}, minY2{y0}, maxY2{y0}, minY3{y0}, maxY3{y0},
        maxY5{0}, minY5{10000.0L}, maxY6{0}, minY6{numeric_limits<LD>::max()}, maxY7{0}, minY7{numeric_limits<LD>::max()};
    for(size_t i{0};i < t[2].size();i ++){
        //stringstream ss;
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
        minY5 = fmin(minY5, t[5][i]._2); maxY5 =  fmax(maxY5, t[5][i]._2);
        minY6 = fmin(minY6, t[6][i]._2); maxY6 =  fmax(maxY6, t[6][i]._2);
        minY7 = fmin(minY7, t[7][i]._2); maxY7 =  fmax(maxY7, t[7][i]._2);
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
    numberOfTicks = min(numberOfTicks, 35);
    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY0), static_cast<qreal>(maxY0));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("y");
        xAxis->setTitleText("x");
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
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY1), static_cast<qreal>(maxY1));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("y");
        xAxis->setTitleText("x");
        chart1->setAxisX(xAxis, series1);
        chart1->setAxisY(yAxis, series1);
        chartView1 = new QChartView(chart1);
        chartView1->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY2), static_cast<qreal>(maxY2));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("y");
        xAxis->setTitleText("x");
        chart2->setAxisX(xAxis, series2);
        chart2->setAxisY(yAxis, series2);
        chartView2 = new QChartView(chart2);
        chartView2->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY3), static_cast<qreal>(maxY3));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("y");
        xAxis->setTitleText("x");
        chart3->setAxisX(xAxis, series3);
        chart3->setAxisY(yAxis, series3);
        chartView3 = new QChartView(chart3);
        chartView3->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(minY0), static_cast<qreal>(maxY0));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("y");
        xAxis->setTitleText("x");
        chart4->addAxis(xAxis, Qt::AlignBottom);
        chart4->addAxis(yAxis, Qt::AlignLeft);
        series4->attachAxis(xAxis);
        series4->attachAxis(yAxis);
        chartView4 = new QChartView(chart4);
        chartView4->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        if(abs(minY5 - maxY5) <= numeric_limits<LD>::epsilon()){maxY5++;}
        yAxis->setRange(static_cast<qreal>(minY5), static_cast<qreal>(maxY5));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Local absolute error");
        xAxis->setTitleText("x");
        chart5->setAxisX(xAxis, series5);
        chart5->setAxisY(yAxis, series5);
        chartView5 = new QChartView(chart5);
        chartView5->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        if(abs(minY6 - maxY6) <= numeric_limits<LD>::epsilon()){maxY6++;}
        yAxis->setRange(static_cast<qreal>(minY6), static_cast<qreal>(maxY6));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Local absolute error");
        xAxis->setTitleText("x");
        chart6->setAxisX(xAxis, series6);
        chart6->setAxisY(yAxis, series6);
        chartView6 = new QChartView(chart6);
        chartView6->setRenderHint(QPainter::Antialiasing);
    }

    {
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(x0), static_cast<qreal>(X));
        xAxis->setTickCount(numberOfTicks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        if(abs(minY7 - maxY7) <= numeric_limits<LD>::epsilon()){maxY7++;}
        yAxis->setRange(static_cast<qreal>(minY7), static_cast<qreal>(maxY7));
        yAxis->setTickCount(min(numberOfTicks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Local absolute error");
        xAxis->setTitleText("x");
        chart7->setAxisX(xAxis, series7);
        chart7->setAxisY(yAxis, series7);
        chartView7 = new QChartView(chart7);
        chartView7->setRenderHint(QPainter::Antialiasing);
    }

    {
        int ticks{25};
        size_t tmp = fno_of_ticks(t[8]);
        if(tmp < 25)ticks = static_cast<int>(tmp);
        pair<pair<LD, LD>, pair<LD, LD> > st = arrange(t[8]);
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(st.first.first), static_cast<qreal>(st.second.first));
        xAxis->setTickCount(ticks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(st.first.second), static_cast<qreal>(st.second.second));
        yAxis->setTickCount(min(ticks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Maximum Error");
        xAxis->setTitleText("Step(h)");
        chart8->setAxisX(xAxis, series8);
        chart8->setAxisY(yAxis, series8);
        chartView8 = new QChartView(chart8);
        chartView8->setRenderHint(QPainter::Antialiasing);
    }

    {
        int ticks{25};
        size_t tmp = fno_of_ticks(t[9]);
        if(tmp < 25)ticks = static_cast<int>(tmp);
        pair<pair<LD, LD>, pair<LD, LD> > st = arrange(t[9]);
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(st.first.first), static_cast<qreal>(st.second.first));
        xAxis->setTickCount(ticks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(st.first.second), static_cast<qreal>(st.second.second));
        yAxis->setTickCount(min(ticks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Maximum Error");
        xAxis->setTitleText("Step(h)");
        chart9->setAxisX(xAxis, series9);
        chart9->setAxisY(yAxis, series9);
        chartView9 = new QChartView(chart9);
        chartView9->setRenderHint(QPainter::Antialiasing);
    }

    {
        int ticks{25};
        size_t tmp = fno_of_ticks(t[10]);
        if(tmp < 25)ticks = static_cast<int>(tmp);
        pair<pair<LD, LD>, pair<LD, LD> > st = arrange(t[10]);
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setRange(static_cast<qreal>(st.first.first), static_cast<qreal>(st.second.first));
        xAxis->setTickCount(ticks);
        QFont my_font("Times", 10);
        xAxis->setLabelsFont(my_font);
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(static_cast<qreal>(st.first.second), static_cast<qreal>(st.second.second));
        yAxis->setTickCount(min(ticks, 20));
        yAxis->setLabelsFont(my_font);
        yAxis->setTitleText("Maximum Error");
        xAxis->setTitleText("Step(h)");
        chart10->setAxisX(xAxis, series10);
        chart10->setAxisY(yAxis, series10);
        chartView10 = new QChartView(chart10);
        chartView10->setRenderHint(QPainter::Antialiasing);
    }

    for(int i{};i < nCount;i ++){
        ui->tabWidget->removeTab(0);
    }

    ui->tabWidget->addTab(table, "Data");
    ui->tabWidget->addTab(chartView0, "Exact");
    ui->tabWidget->addTab(chartView1, "Euler");
    ui->tabWidget->addTab(chartView5, "Euler error");
    ui->tabWidget->addTab(chartView2, "Improved Euler");
    ui->tabWidget->addTab(chartView6, "Improved Euler error");
    ui->tabWidget->addTab(chartView3, "Runga-Kutta");
    ui->tabWidget->addTab(chartView7, "Runga-Kutta error");
    ui->tabWidget->addTab(chartView4, "Compare");
    ui->tabWidget->addTab(chartView8, "euler error");
    ui->tabWidget->addTab(chartView9, "imp. euler err");
    ui->tabWidget->addTab(chartView10, "runga-kutta error");
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}

void MainWindow::on_About_clicked()
{
    msg->show();
}
