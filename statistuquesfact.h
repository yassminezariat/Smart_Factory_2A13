#ifndef STATISTUQUESFACT_H
#define STATISTUQUESFACT_H

#include <QMainWindow>
#include<QtCharts/QtCharts>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>
#include "facture.h"
#include"grade.h"
namespace Ui {
class statistuquesfact;
}

class statistuquesfact : public QMainWindow
{
    Q_OBJECT

public:
    explicit statistuquesfact(QWidget *parent = nullptr);
    ~statistuquesfact();

private:
    Ui::statistuquesfact *ui;
    facture f;
    grade tmpgrade;
};

#endif // STATISTUQUESFACT_H
