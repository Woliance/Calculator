#ifndef CALCULATORMAINWINDOW_H
#define CALCULATORMAINWINDOW_H

#include "qprocess.h"
#include "ui_calculatormainwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CalculatorMainWindow; }
QT_END_NAMESPACE

class CalculatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorMainWindow(QWidget *parent = nullptr);
    ~CalculatorMainWindow();

public slots:
    void startProcess();
    void readOutput();
    void sendInput(QString input);
    void stopProcess();

private slots:
    void on_outputTextEdit_copyAvailable(bool available);
    void on_inputLineEdit_returnPressed();

private:
    Ui::CalculatorMainWindow *ui;
    QTextBrowser *outputTextEdit;
    QLineEdit *inputLineEdit;
    QProcess process;
};

#endif // CALCULATORMAINWINDOW_H
