#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , firstNum(0.0)
    , waitingForOperand(true)
    , pendingOperator("")
    , currentExpression("")
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
    ui->formulaDisplay->clear();
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
    
    // Update the expression display
    if (currentExpression.isEmpty() || currentExpression.endsWith(" ")) {
        currentExpression += digit;
    } else {
        currentExpression += digit;
    }
    ui->formulaDisplay->setText(currentExpression);
}

void Dialog::operatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString clickedOperator = button->text();
    double operand = ui->display->text().toDouble();
    
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        // Calculate the pending operation only if a new operand was entered
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
                ui->formulaDisplay->setText("Error: Division by zero");
                firstNum = 0.0;
                waitingForOperand = true;
                pendingOperator.clear();
                currentExpression.clear();
                return;
            }
        }
        ui->display->setText(QString::number(firstNum));
    } else if (waitingForOperand) {
        // If we're waiting for operand (operator pressed immediately after another operator),
        // just replace the operator in the expression
        if (!currentExpression.isEmpty() && currentExpression.endsWith(" ")) {
            // Remove the last operator and space
            currentExpression.chop(2);
        }
    } else {
        // First operator pressed
        firstNum = operand;
    }
    
    // Add operator to expression if not already ending with a space
    if (!currentExpression.isEmpty() && !currentExpression.endsWith(" ")) {
        currentExpression += " " + clickedOperator + " ";
    } else if (!currentExpression.isEmpty()) {
        currentExpression += clickedOperator + " ";
    } else {
        currentExpression = QString::number(firstNum) + " " + clickedOperator + " ";
    }
    ui->formulaDisplay->setText(currentExpression);
    
    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void Dialog::equalsPressed()
{
    double operand = ui->display->text().toDouble();
    
    if (!pendingOperator.isEmpty()) {
        // Complete the expression with the last operand
        if (!currentExpression.endsWith(" ")) {
            // Expression already has the second operand
        } else {
            // Add the second operand to the expression
            currentExpression += QString::number(operand);
        }
        
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
                ui->formulaDisplay->setText("Error: Division by zero");
                firstNum = 0.0;
                waitingForOperand = true;
                pendingOperator.clear();
                currentExpression.clear();
                return;
            }
        }
        
        // Show the complete expression in the formula display
        ui->formulaDisplay->setText(currentExpression);
        // Show the result in the main display
        ui->display->setText(QString::number(firstNum));
        pendingOperator.clear();
    }
    
    waitingForOperand = true;
}

void Dialog::clearPressed()
{
    ui->display->setText("0");
    ui->formulaDisplay->clear();
    firstNum = 0.0;
    waitingForOperand = true;
    pendingOperator.clear();
    currentExpression.clear();
}

void Dialog::deletePressed()
{
    QString text = ui->display->text();
    if (text.length() > 1) {
        text.chop(1);
        ui->display->setText(text);
        // Update the expression by removing the last character
        if (!currentExpression.isEmpty()) {
            currentExpression.chop(1);
            ui->formulaDisplay->setText(currentExpression);
        }
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
        currentExpression += "0.";
    } else if (!ui->display->text().contains(".")) {
        ui->display->setText(ui->display->text() + ".");
        currentExpression += ".";
    }
    ui->formulaDisplay->setText(currentExpression);
}
