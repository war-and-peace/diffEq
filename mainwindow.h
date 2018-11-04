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
#include <QMessageBox>

const int nCount = 9;

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
    QLineSeries *series0, *series1, *series2, *series3, *series4, *series5,
                *series6, *series7, *series8, *series9, *series10,
                *series00, *series01, *series02, *series03;
    QChart *chart0, *chart1, *chart2, *chart3, *chart4, *chart5,
            *chart6, *chart7, *chart8, *chart9, *chart10;
    QChartView *chartView0, *chartView1, *chartView2, *chartView3, *chartView4, *chartView5,
                *chartView6, *chartView7, *chartView8, *chartView9, *chartView10;
    QTableWidget *table;
    QMessageBox *msg;
private slots:

    void on_Solve_clicked();

    void on_Exit_clicked();

    void on_About_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
