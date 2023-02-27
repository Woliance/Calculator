#include "calculatormainwindow.h"
#include "./ui_calculatormainwindow.h"

#include <QLineEdit>
#include <QToolBar>
#include <QString>
#include <QTextCursor>
#include <QKeyEvent>

#include <QProcess>

CalculatorMainWindow::CalculatorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorMainWindow)
{
    ui->setupUi(this);

    QLineEdit *inputLineEdit = ui->inputLineEdit;

//    addToolBar(toolBar);

    connect(inputLineEdit, &QLineEdit::returnPressed, this, &CalculatorMainWindow::on_inputLineEdit_returnPressed);

    startProcess();
}



void CalculatorMainWindow::startProcess() {
    // Start the command line program
    process.start("D:/Program Files (x86)/Calculator/ConsoleApplication1/x64/Release/ConsoleApplication1.exe");

    // Connect the readyReadStandardOutput() signal to the readOutput() slot
    connect(&process, &QProcess::readyReadStandardOutput, this, &CalculatorMainWindow::readOutput);

    // Connect the process's finished() signal to the stopProcess() slot
    connect(&process, SIGNAL(finished(int)), this, SLOT(stopProcess()));
}


void CalculatorMainWindow::readOutput() {
    // Read the output from the process
    QByteArray data = process.readAllStandardOutput();
    QString output = QString::fromLocal8Bit(data).trimmed();

    // Check if the output contains the original input followed by two newline characters
    QString inputString = ui->inputLineEdit->text().trimmed().remove('\n');
    QString pattern = inputString + "\n\n";
    int index = output.indexOf(pattern);
    if (index >= 0) {
        // Extract the result from the output
        QString result = output.mid(index + pattern.length());

        // Add the input and result to the outputTextEdit
        ui->outputTextEdit->moveCursor(QTextCursor::End);
        ui->outputTextEdit->insertPlainText(result + " = " + inputString + "\n");
        ui->outputTextEdit->moveCursor(QTextCursor::End);
    }

    // Add the output to the outputTextEdit
    ui->outputTextEdit->moveCursor(QTextCursor::End);
    ui->outputTextEdit->insertPlainText(output + "\n");
    ui->outputTextEdit->moveCursor(QTextCursor::End);
}

void CalculatorMainWindow::on_outputTextEdit_copyAvailable(bool)
{
    // Read the output from the process and add it to the outputTextEdit
    QString result = process.readAllStandardOutput().trimmed();

    // Add the result to the outputTextEdit
    ui->outputTextEdit->moveCursor(QTextCursor::End);
    ui->outputTextEdit->insertPlainText(result);
    ui->outputTextEdit->moveCursor(QTextCursor::End);
}


void CalculatorMainWindow::sendInput(QString input) {
    // Write input to the process
    process.write(input.toLocal8Bit());
}

void CalculatorMainWindow::stopProcess() {
    // Terminate the process
    process.terminate();
}

CalculatorMainWindow::~CalculatorMainWindow()
{
    process.kill();
    delete ui;
}

void CalculatorMainWindow::on_inputLineEdit_returnPressed()
{
    // Get the input string from the inputLineEdit
    QString inputString = ui->inputLineEdit->text();

    // Add the input string to the outputTextEdit
    ui->outputTextEdit->moveCursor(QTextCursor::End);
    //ui->outputTextEdit->insertPlainText(inputString + "\n");
    ui->outputTextEdit->moveCursor(QTextCursor::End);

    // Send the user's input to the process
    sendInput(inputString + "\n");

    // Clear the inputLineEdit
    ui->inputLineEdit->clear();
}
