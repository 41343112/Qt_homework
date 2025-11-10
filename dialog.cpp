#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , firstNum(0.0)
    , waitingForOperand(true)
    , pendingOperator("")
{
    ui->setupUi(this);
    
    // Connect digit buttons
    connect(ui->btn0, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn1, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn2, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn3, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn4, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn5, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn6, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn7, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn8, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(ui->btn9, &QPushButton::clicked, this, &Dialog::digitPressed);
    
    // Connect operator buttons
    connect(ui->btnAdd, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(ui->btnSubtract, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(ui->btnDivide, &QPushButton::clicked, this, &Dialog::operatorPressed);
    
    // Connect other buttons
    connect(ui->btnEquals, &QPushButton::clicked, this, &Dialog::equalsPressed);
    connect(ui->btnClear, &QPushButton::clicked, this, &Dialog::clearPressed);
    connect(ui->btnDelete, &QPushButton::clicked, this, &Dialog::deletePressed);
    connect(ui->btnDecimal, &QPushButton::clicked, this, &Dialog::decimalPressed);
    
    // Initialize display
    ui->display->setText("0");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString digit = button->text();
    
    if (waitingForOperand) {
        ui->display->clear();
        waitingForOperand = false;
    }
    
    if (ui->display->text() == "0" && digit != "0") {
        ui->display->setText(digit);
    } else if (ui->display->text() != "0") {
        ui->display->setText(ui->display->text() + digit);
    }
}

void Dialog::operatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString clickedOperator = button->text();
    double operand = ui->display->text().toDouble();
    
    if (!pendingOperator.isEmpty()) {
        // Calculate the pending operation
        if (pendingOperator == "+") {
            firstNum += operand;
        } else if (pendingOperator == "-") {
            firstNum -= operand;
        } else if (pendingOperator == "×") {
            firstNum *= operand;
        } else if (pendingOperator == "÷") {
            if (operand != 0.0) {
                firstNum /= operand;
            } else {
                ui->display->setText("Error");
                firstNum = 0.0;
                waitingForOperand = true;
                pendingOperator.clear();
                return;
            }
        }
        ui->display->setText(QString::number(firstNum));
    } else {
        firstNum = operand;
    }
    
    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void Dialog::equalsPressed()
{
    double operand = ui->display->text().toDouble();
    
    if (!pendingOperator.isEmpty()) {
        if (pendingOperator == "+") {
            firstNum += operand;
        } else if (pendingOperator == "-") {
            firstNum -= operand;
        } else if (pendingOperator == "×") {
            firstNum *= operand;
        } else if (pendingOperator == "÷") {
            if (operand != 0.0) {
                firstNum /= operand;
            } else {
                ui->display->setText("Error");
                firstNum = 0.0;
                waitingForOperand = true;
                pendingOperator.clear();
                return;
            }
        }
        ui->display->setText(QString::number(firstNum));
        pendingOperator.clear();
    }
    
    waitingForOperand = true;
}

void Dialog::clearPressed()
{
    ui->display->setText("0");
    firstNum = 0.0;
    waitingForOperand = true;
    pendingOperator.clear();
}

void Dialog::deletePressed()
{
    QString text = ui->display->text();
    if (text.length() > 1) {
        text.chop(1);
        ui->display->setText(text);
    } else {
        ui->display->setText("0");
        waitingForOperand = true;
    }
}

void Dialog::decimalPressed()
{
    if (waitingForOperand) {
        ui->display->setText("0.");
        waitingForOperand = false;
    } else if (!ui->display->text().contains(".")) {
        ui->display->setText(ui->display->text() + ".");
    }
}
