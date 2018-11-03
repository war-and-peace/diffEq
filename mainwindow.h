#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <sstream>
#include <QValueAxis>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <QSizePolicy>

const int nCount = 7;

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineSeries *series0, *series1, *series2, *series3, *series4, *series5, *series00, *series01, *series02, *series03;
    QChart *chart0, *chart1, *chart2, *chart3, *chart4, *chart5;
    QChartView *chartView0, *chartView1, *chartView2, *chartView3, *chartView4, *chartView5;
    QTableWidget *table;
private slots:

    void on_Solve_clicked();

    void on_Exit_clicked();

    void something();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
