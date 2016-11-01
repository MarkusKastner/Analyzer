#ifndef ANALYZER_H
#define ANALYZER_H

#include <QtWidgets/QMainWindow>
#include "ui_Analyzer.h"

class Analyzer : public QMainWindow
{
    Q_OBJECT

public:
    Analyzer(QWidget *parent = 0);
    ~Analyzer();

private:
    Ui::AnalyzerClass ui;
};

#endif // ANALYZER_H
