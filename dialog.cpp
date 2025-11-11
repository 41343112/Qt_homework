#include "dialog.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , waitingForOperand(true)
    , currentExpression("")
    , lastOperand(0.0)
    , lastOperator("")
    , equalsPressedBefore(false)
{
    createUI();
    
    // Connect digit buttons
    connect(btn0, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn1, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn2, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn3, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn4, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn5, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn6, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn7, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn8, &QPushButton::clicked, this, &Dialog::digitPressed);
    connect(btn9, &QPushButton::clicked, this, &Dialog::digitPressed);
    
    // Connect operator buttons
    connect(btnAdd, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnSubtract, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnMultiply, &QPushButton::clicked, this, &Dialog::operatorPressed);
    connect(btnDivide, &QPushButton::clicked, this, &Dialog::operatorPressed);
    
    // Connect other buttons
    connect(btnEquals, &QPushButton::clicked, this, &Dialog::equalsPressed);
    connect(btnClear, &QPushButton::clicked, this, &Dialog::clearPressed);
    connect(btnDelete, &QPushButton::clicked, this, &Dialog::deletePressed);
    connect(btnDecimal, &QPushButton::clicked, this, &Dialog::decimalPressed);
    
    // Initialize display
    display->setText("0");
    formulaDisplay->clear();
}

Dialog::~Dialog()
{
}

void Dialog::createUI()
{
    setWindowTitle("Calculator");
    setFixedSize(400, 500);
    
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create formula display
    formulaDisplay = new QLabel(this);
    formulaDisplay->setMinimumHeight(40);
    formulaDisplay->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QFont formulaFont = formulaDisplay->font();
    formulaFont.setPointSize(14);
    formulaDisplay->setFont(formulaFont);
    mainLayout->addWidget(formulaDisplay);
    
    // Create main display
    display = new QLineEdit(this);
    display->setMinimumHeight(60);
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    display->setReadOnly(true);
    QFont displayFont = display->font();
    displayFont.setPointSize(20);
    display->setFont(displayFont);
    mainLayout->addWidget(display);
    
    // Create button grid
    QGridLayout *gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);
    
    // Create buttons
    QFont buttonFont;
    buttonFont.setPointSize(16);
    
    // Row 0
    btnClear = new QPushButton("C", this);
    btnClear->setMinimumHeight(60);
    btnClear->setFont(buttonFont);
    gridLayout->addWidget(btnClear, 0, 0);
    
    btnDelete = new QPushButton("DEL", this);
    btnDelete->setMinimumHeight(60);
    btnDelete->setFont(buttonFont);
    gridLayout->addWidget(btnDelete, 0, 1);
    
    btnDivide = new QPushButton("÷", this);
    btnDivide->setMinimumHeight(60);
    btnDivide->setFont(buttonFont);
    gridLayout->addWidget(btnDivide, 0, 2, 1, 2);
    
    // Row 1
    btn7 = new QPushButton("7", this);
    btn7->setMinimumHeight(60);
    btn7->setFont(buttonFont);
    gridLayout->addWidget(btn7, 1, 0);
    
    btn8 = new QPushButton("8", this);
    btn8->setMinimumHeight(60);
    btn8->setFont(buttonFont);
    gridLayout->addWidget(btn8, 1, 1);
    
    btn9 = new QPushButton("9", this);
    btn9->setMinimumHeight(60);
    btn9->setFont(buttonFont);
    gridLayout->addWidget(btn9, 1, 2);
    
    btnMultiply = new QPushButton("×", this);
    btnMultiply->setMinimumHeight(60);
    btnMultiply->setFont(buttonFont);
    gridLayout->addWidget(btnMultiply, 1, 3);
    
    // Row 2
    btn4 = new QPushButton("4", this);
    btn4->setMinimumHeight(60);
    btn4->setFont(buttonFont);
    gridLayout->addWidget(btn4, 2, 0);
    
    btn5 = new QPushButton("5", this);
    btn5->setMinimumHeight(60);
    btn5->setFont(buttonFont);
    gridLayout->addWidget(btn5, 2, 1);
    
    btn6 = new QPushButton("6", this);
    btn6->setMinimumHeight(60);
    btn6->setFont(buttonFont);
    gridLayout->addWidget(btn6, 2, 2);
    
    btnSubtract = new QPushButton("-", this);
    btnSubtract->setMinimumHeight(60);
    btnSubtract->setFont(buttonFont);
    gridLayout->addWidget(btnSubtract, 2, 3);
    
    // Row 3
    btn1 = new QPushButton("1", this);
    btn1->setMinimumHeight(60);
    btn1->setFont(buttonFont);
    gridLayout->addWidget(btn1, 3, 0);
    
    btn2 = new QPushButton("2", this);
    btn2->setMinimumHeight(60);
    btn2->setFont(buttonFont);
    gridLayout->addWidget(btn2, 3, 1);
    
    btn3 = new QPushButton("3", this);
    btn3->setMinimumHeight(60);
    btn3->setFont(buttonFont);
    gridLayout->addWidget(btn3, 3, 2);
    
    btnAdd = new QPushButton("+", this);
    btnAdd->setMinimumHeight(60);
    btnAdd->setFont(buttonFont);
    gridLayout->addWidget(btnAdd, 3, 3);
    
    // Row 4
    btn0 = new QPushButton("0", this);
    btn0->setMinimumHeight(60);
    btn0->setFont(buttonFont);
    gridLayout->addWidget(btn0, 4, 0, 1, 2);
    
    btnDecimal = new QPushButton(".", this);
    btnDecimal->setMinimumHeight(60);
    btnDecimal->setFont(buttonFont);
    gridLayout->addWidget(btnDecimal, 4, 2);
    
    btnEquals = new QPushButton("=", this);
    btnEquals->setMinimumHeight(60);
    btnEquals->setFont(buttonFont);
    gridLayout->addWidget(btnEquals, 4, 3);
}

double Dialog::evaluateExpression()
{
    // Create copies of the operands and operators to work with
    QVector<double> nums = operands;
    QVector<QString> ops = operators;
    
    // First pass: handle multiplication and division (higher precedence)
    int i = 0;
    while (i < ops.size()) {
        if (ops[i] == "×" || ops[i] == "÷") {
            double result;
            if (ops[i] == "×") {
                result = nums[i] * nums[i + 1];
            } else { // ops[i] == "÷"
                if (nums[i + 1] == 0.0) {
                    // Division by zero - will be handled by caller
                    return 0.0;
                }
                result = nums[i] / nums[i + 1];
            }
            // Replace the two operands with the result
            nums[i] = result;
            nums.remove(i + 1);
            ops.remove(i);
            // Don't increment i, check the same position again
        } else {
            i++;
        }
    }
    
    // Second pass: handle addition and subtraction (lower precedence)
    i = 0;
    while (i < ops.size()) {
        double result;
        if (ops[i] == "+") {
            result = nums[i] + nums[i + 1];
        } else { // ops[i] == "-"
            result = nums[i] - nums[i + 1];
        }
        // Replace the two operands with the result
        nums[i] = result;
        nums.remove(i + 1);
        ops.remove(i);
        // Don't increment i, check the same position again
    }
    
    // Should have exactly one number left
    return nums.isEmpty() ? 0.0 : nums[0];
}

void Dialog::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString digit = button->text();
    
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->clear();
        formulaDisplay->clear();
        currentExpression.clear();
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    }
    
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    
    if (display->text() == "0" && digit != "0") {
        display->setText(digit);
    } else if (display->text() != "0") {
        display->setText(display->text() + digit);
    }
    
    // Update the expression display
    currentExpression += digit;
    formulaDisplay->setText(currentExpression);
}

void Dialog::operatorPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    
    QString clickedOperator = button->text();
    double operand = display->text().toDouble();
    
    // If equals was just pressed, start from the result
    if (equalsPressedBefore) {
        equalsPressedBefore = false;
        operands.clear();
        operators.clear();
        currentExpression = QString::number(operand);
        operands.append(operand);
    }
    
    if (waitingForOperand) {
        // If we're waiting for operand (operator pressed immediately after another operator),
        // just replace the last operator
        if (!operators.isEmpty()) {
            operators[operators.size() - 1] = clickedOperator;
            // Update the expression display
            if (!currentExpression.isEmpty() && currentExpression.endsWith(" ")) {
                currentExpression.chop(2); // Remove last operator and space
            }
            currentExpression += clickedOperator + " ";
            formulaDisplay->setText(currentExpression);
        } else {
            // First number followed by operator
            operands.append(operand);
            operators.append(clickedOperator);
            if (currentExpression.isEmpty()) {
                currentExpression = QString::number(operand);
            }
            currentExpression += " " + clickedOperator + " ";
            formulaDisplay->setText(currentExpression);
        }
    } else {
        // Save the current operand and operator
        operands.append(operand);
        operators.append(clickedOperator);
        
        // Add operator to expression
        if (!currentExpression.isEmpty() && !currentExpression.endsWith(" ")) {
            currentExpression += " " + clickedOperator + " ";
        } else if (!currentExpression.isEmpty()) {
            currentExpression += clickedOperator + " ";
        } else {
            currentExpression = QString::number(operand) + " " + clickedOperator + " ";
        }
        formulaDisplay->setText(currentExpression);
    }
    
    waitingForOperand = true;
}

void Dialog::equalsPressed()
{
    double operand = display->text().toDouble();
    
    // If equals was already pressed, repeat the last operation
    if (equalsPressedBefore && !lastOperator.isEmpty()) {
        // Simple single operation repeat (like Windows Calculator)
        double currentValue = display->text().toDouble();
        double result;
        
        if (lastOperator == "+") {
            result = currentValue + lastOperand;
        } else if (lastOperator == "-") {
            result = currentValue - lastOperand;
        } else if (lastOperator == "×") {
            result = currentValue * lastOperand;
        } else if (lastOperator == "÷") {
            if (lastOperand != 0.0) {
                result = currentValue / lastOperand;
            } else {
                display->setText("Error");
                formulaDisplay->setText("Error: Division by zero");
                operands.clear();
                operators.clear();
                waitingForOperand = true;
                currentExpression.clear();
                equalsPressedBefore = false;
                return;
            }
        } else {
            return;
        }
        
        // Update displays
        currentExpression = QString::number(currentValue) + " " + lastOperator + " " + QString::number(lastOperand);
        formulaDisplay->setText(currentExpression);
        display->setText(QString::number(result));
        
    } else if (!operators.isEmpty()) {
        // First time pressing equals - evaluate the full expression
        
        // Add the last operand to complete the expression
        if (!waitingForOperand) {
            operands.append(operand);
            
            // Complete the expression display
            if (!currentExpression.endsWith(" ")) {
                // Expression already complete
            } else {
                currentExpression += QString::number(operand);
            }
        } else if (!operands.isEmpty()) {
            // Operator was pressed but no new operand entered, use the last operand
            operands.append(operands.last());
            currentExpression += QString::number(operands.last());
        }
        
        // Check for division by zero before evaluation
        for (int i = 0; i < operators.size(); i++) {
            if (operators[i] == "÷" && i + 1 < operands.size() && operands[i + 1] == 0.0) {
                display->setText("Error");
                formulaDisplay->setText("Error: Division by zero");
                operands.clear();
                operators.clear();
                waitingForOperand = true;
                currentExpression.clear();
                equalsPressedBefore = false;
                return;
            }
        }
        
        // Evaluate the expression with proper order of operations
        double result = evaluateExpression();
        
        // Save the last operator and operand for repeating
        // For repeating, we use the last operation
        if (!operators.isEmpty() && operands.size() >= 2) {
            lastOperator = operators.last();
            lastOperand = operands.last();
        }
        
        // Show the complete expression in the formula display
        formulaDisplay->setText(currentExpression);
        // Show the result in the main display
        display->setText(QString::number(result));
        
        // Clear the expression data
        operands.clear();
        operators.clear();
        equalsPressedBefore = true;
    }
    
    waitingForOperand = true;
}

void Dialog::clearPressed()
{
    display->setText("0");
    formulaDisplay->clear();
    operands.clear();
    operators.clear();
    waitingForOperand = true;
    currentExpression.clear();
    lastOperand = 0.0;
    lastOperator.clear();
    equalsPressedBefore = false;
}

void Dialog::deletePressed()
{
    QString text = display->text();
    if (text.length() > 1) {
        text.chop(1);
        display->setText(text);
        // Update the expression by removing the last character
        if (!currentExpression.isEmpty()) {
            currentExpression.chop(1);
            formulaDisplay->setText(currentExpression);
        }
    } else {
        display->setText("0");
        waitingForOperand = true;
    }
}

void Dialog::decimalPressed()
{
    // If equals was just pressed, start a new calculation
    if (equalsPressedBefore) {
        display->setText("0.");
        formulaDisplay->clear();
        currentExpression = "0.";
        operands.clear();
        operators.clear();
        equalsPressedBefore = false;
        waitingForOperand = false;
    } else if (waitingForOperand) {
        display->setText("0.");
        waitingForOperand = false;
        currentExpression += "0.";
    } else if (!display->text().contains(".")) {
        display->setText(display->text() + ".");
        currentExpression += ".";
    }
    formulaDisplay->setText(currentExpression);
}
